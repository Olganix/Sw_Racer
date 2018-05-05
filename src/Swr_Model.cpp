#include <math.h>

#include "Swr_Model.h"

using namespace Common;








/*-------------------------------------------------------------------------------\
|                             zero					                             |
\-------------------------------------------------------------------------------*/
void EMDVertex::zero(void)
{
	flags = 0;
	pos_x = pos_y = pos_z = norm_x = norm_z = tang_y = tang_z = text_u = text_v = text2_u = text2_v = blend_weight[0] = blend_weight[1] = blend_weight[2] = blend_weight[3] = 0.0f;
	norm_y = tang_x = 1.0f;
	color = 0;
	blend[0] = blend[1] = blend[2] = blend[3] = 0;
}
/*-------------------------------------------------------------------------------\
|                             opeartor ==			                             |
\-------------------------------------------------------------------------------*/
bool EMDVertex::operator == (const EMDVertex& vertex)
{
	if (this->flags != vertex.flags) return false;

	if ((this->flags & EMD_VTX_FLAG_POS) && ((this->pos_x != vertex.pos_x) || (this->pos_y != vertex.pos_y) || (this->pos_z != vertex.pos_z)))
		return false;

	if ((this->flags & EMD_VTX_FLAG_NORM) && ((this->norm_x != vertex.norm_x) || (this->norm_y != vertex.norm_y) || (this->norm_z != vertex.norm_z)))
		return false;

	if ((this->flags & EMD_VTX_FLAG_TANGENT) && ((this->tang_x != vertex.tang_x) || (this->tang_y != vertex.tang_y) || (this->tang_z != vertex.tang_z)))
		return false;

	if ((this->flags & EMD_VTX_FLAG_TEX) && ((this->text_u != vertex.text_u) || (this->text_v != vertex.text_v)))
		return false;

	if ((this->flags & EMD_VTX_FLAG_TEX2) && ((this->text2_u != vertex.text2_u) || (this->text2_v != vertex.text2_v)))
		return false;

	if ((this->flags & EMD_VTX_FLAG_COLOR) && (this->color != vertex.color))
		return false;


	if (flags & EMD_VTX_FLAG_BLEND_WEIGHT)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (this->blend[i] != vertex.blend[i]) return false;
			if (this->blend_weight[i] != vertex.blend_weight[i]) return false;
		}
	}

	return true;
}
/*-------------------------------------------------------------------------------\
|                             getColorRGBAFloat		                             |
\-------------------------------------------------------------------------------*/
//	get values into [0,1] ranges
void EMDVertex::getColorRGBAFloat(float &r, float &g, float &b, float &a)
{
	uint32_t color_tmp = color;

	r = ((float)((color_tmp >> 24) & 0xFF)) / 255.0f;
	g = ((float)((color_tmp >> 16) & 0xFF)) / 255.0f;
	b = ((float)((color_tmp >> 8) & 0xFF)) / 255.0f;
	a = ((float)(color_tmp & 0xFF)) / 255.0f;
}
/*-------------------------------------------------------------------------------\
|                             setColorFromRGBAFloat		                         |
\-------------------------------------------------------------------------------*/
//	set values from [0,1] ranges
void EMDVertex::setColorFromRGBAFloat(float r, float g, float b, float a)
{
	color = 0;
	color += (((int)floorf(max(min(r, 1.0f), 0.0f) * 255.0f)) & 0xFF) << 24;
	color += (((int)floorf(max(min(g, 1.0f), 0.0f) * 255.0f)) & 0xFF) << 16;
	color += (((int)floorf(max(min(b, 1.0f), 0.0f) * 255.0f)) & 0xFF) << 8;
	color += (((int)floorf(max(min(a, 1.0f), 0.0f) * 255.0f)) & 0xFF);
}
/*-------------------------------------------------------------------------------\
|                             getColorFromRGBAUint8		                         |
\-------------------------------------------------------------------------------*/
//	get values into [0,255] ranges
void EMDVertex::getColorFromRGBAUint8(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
{
	uint32_t color_tmp = color;
	r = (color_tmp >> 24) & 0xFF;
	g = (color_tmp >> 16) & 0xFF;
	b = (color_tmp >> 8) & 0xFF;
	a = color_tmp & 0xFF;;
}
/*-------------------------------------------------------------------------------\
|                             setColorFromRGBAUint8		                         |
\-------------------------------------------------------------------------------*/
//	set values from [0,255] ranges
void EMDVertex::setColorFromRGBAUint8(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	color = 0;
	color += r << 24;
	color += g << 16;
	color += b << 8;
	color += a;
}
/*-------------------------------------------------------------------------------\
|                             getColorFromRGB_str		                         |
\-------------------------------------------------------------------------------*/
//	get values into "0.0 0.1 0.2 0.3"
string EMDVertex::getColorFromRGBA_str()
{
	float r, g, b, a;
	getColorRGBAFloat(r, g, b, a);
	return EMO_BaseFile::FloatToString(r) + " " + EMO_BaseFile::FloatToString(g) + " " + EMO_BaseFile::FloatToString(b) + " " + EMO_BaseFile::FloatToString(a);
}
/*-------------------------------------------------------------------------------\
|                             getColorFromRGB_str		                         |
\-------------------------------------------------------------------------------*/
//	set values into "0.0 0.1 0.2 0.3"
void EMDVertex::getColorFromRGBA_str(string values)
{
	float r = 0;
	float g = 0;
	float b = 0;
	float a = 0;
	
	std::vector<std::string> sv = Common::split(values, ' ');
	size_t nbElements = sv.size();
	if (nbElements > 0)
		r = stof(sv.at(0));
	if (nbElements > 1)
		g = stof(sv.at(1));
	if (nbElements > 2)
		b = stof(sv.at(2));
	if (nbElements > 3)
		a = stof(sv.at(3));
	
	setColorFromRGBAFloat(r, g, b, a);
}







/*-------------------------------------------------------------------------------\
|                             Collada											 |
\-------------------------------------------------------------------------------*/
Collada::Collada()
{
	doc = new TiXmlDocument();
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc->LinkEndChild(decl);

	root = new TiXmlElement("COLLADA");
	doc->LinkEndChild(root);
	root->SetAttribute("xmlns", "http://www.collada.org/2005/11/COLLADASchema");
	root->SetAttribute("version", "1.4.1");

	TiXmlElement* node_asset = new TiXmlElement("asset");
	root->LinkEndChild(node_asset);

	TiXmlElement* node_unit = new TiXmlElement("unit");
	node_asset->LinkEndChild(node_unit);
	node_unit->SetAttribute("meter", "0.01");
	node_unit->SetAttribute("name", "centimeter");

	TiXmlElement* node_up_axis = new TiXmlElement("up_axis");
	node_asset->LinkEndChild(node_up_axis);
	node_up_axis->LinkEndChild(new TiXmlText("Z_UP"));


	node_library_cameras = new TiXmlElement("library_cameras");
	root->LinkEndChild(node_library_cameras);

	node_library_lights = new TiXmlElement("library_lights");
	root->LinkEndChild(node_library_lights);

	node_library_images = new TiXmlElement("library_images");
	root->LinkEndChild(node_library_images);

	node_library_effects = new TiXmlElement("library_effects");
	root->LinkEndChild(node_library_effects);

	node_library_materials = new TiXmlElement("library_materials");
	root->LinkEndChild(node_library_materials);

	node_geometries = new TiXmlElement("library_geometries");
	root->LinkEndChild(node_geometries);

	node_library_visual_scenes = new TiXmlElement("library_visual_scenes");
	root->LinkEndChild(node_library_visual_scenes);


	node_visual_scene = new TiXmlElement("visual_scene");
	node_library_visual_scenes->LinkEndChild(node_visual_scene);
	node_visual_scene->SetAttribute("id", "VisualSceneNode");
	node_visual_scene->SetAttribute("name", "untitled");


	node_library_animations = new TiXmlElement("library_animations");
	root->LinkEndChild(node_library_animations);

	node_scene = new TiXmlElement("scene");
	root->LinkEndChild(node_scene);

	TiXmlElement* node_instance_visual_scene = new TiXmlElement("instance_visual_scene");
	node_scene->LinkEndChild(node_instance_visual_scene);
	node_instance_visual_scene->SetAttribute("url", "#VisualSceneNode");
}

/*-------------------------------------------------------------------------------\
|                             addGeometry										 |
\-------------------------------------------------------------------------------*/
void Collada::addGeometry(string name, std::vector<EMDVertex> &vertices, std::vector<EMDTriangles> &triangles, string materialName)
{
	size_t nbVertex = vertices.size();
	if (nbVertex == 0)
		return;

	string str = "";

	bool havePosition = vertices.at(0).flags & EMD_VTX_FLAG_POS;
	bool haveUv = vertices.at(0).flags & EMD_VTX_FLAG_TEX;
	bool haveColor = vertices.at(0).flags & EMD_VTX_FLAG_COLOR;

	TiXmlElement* node_geometry = new TiXmlElement("geometry");
	node_geometries->LinkEndChild(node_geometry);
	node_geometry->SetAttribute("id", name);
	node_geometry->SetAttribute("name", name);

	TiXmlElement* node_mesh = new TiXmlElement("mesh");
	node_geometry->LinkEndChild(node_mesh);

	if (havePosition)
	{
		TiXmlElement* node_source = new TiXmlElement("source");
		node_mesh->LinkEndChild(node_source);
		node_source->SetAttribute("id", name + "_positions");
		node_source->SetAttribute("name", name + "_positions");

		TiXmlElement* node_listFloat = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_listFloat);
		node_listFloat->SetAttribute("id", name + "_positions_floats");
		node_listFloat->SetAttribute("count", nbVertex * 3);
		str = "";
		for (size_t i = 0; i < nbVertex; i++)
		{
			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString(vertices.at(i).pos_x);
			str += " " + EMO_BaseFile::FloatToString(vertices.at(i).pos_y);
			str += " " + EMO_BaseFile::FloatToString(vertices.at(i).pos_z);
		}
		node_listFloat->LinkEndChild(new TiXmlText(str));

		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbVertex);
		node_accessor->SetAttribute("offset", "0");
		node_accessor->SetAttribute("source", "#" + name + "_positions_floats");
		node_accessor->SetAttribute("stride", "3");

		TiXmlElement* node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "X");
		node_param->SetAttribute("type", "float");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "Y");
		node_param->SetAttribute("type", "float");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "Z");
		node_param->SetAttribute("type", "float");
	}


	/*/////////////////////////////////////////////////////

	node_source = new TiXmlElement("source");
	node_mesh->LinkEndChild(node_source);
	node_source->SetAttribute("id", name + "_normals");
	node_source->SetAttribute("name", name + "_normal");

	node_listFloat = new TiXmlElement("float_array");
	node_source->LinkEndChild(node_listFloat);
	node_listFloat->SetAttribute("id", name + "_normals_floats");
	node_listFloat->SetAttribute("count", "72");
	node_listFloat->LinkEndChild(new TiXmlText("0 0 1 0 0 1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 0 1 0 0 -1 0 0 -1 0 0 -1 0 0 -1 0 -1 0 0 -1 0 0 -1 0 0 -1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 0 0 -1 0 0 -1 0 0 -1 0 0 -1"));

	node_technique_common = new TiXmlElement("technique_common");
	node_source->LinkEndChild(node_technique_common);

	node_accessor = new TiXmlElement("accessor");
	node_technique_common->LinkEndChild(node_accessor);
	node_accessor->SetAttribute("count", "24");
	node_accessor->SetAttribute("offset", "0");
	node_accessor->SetAttribute("source", "#"+ name + "_normals_floats");
	node_accessor->SetAttribute("stride", "3");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "X");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "Y");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "Z");
	node_param->SetAttribute("type", "float");



	/////////////////////////////////////////////////////*/

	if (haveUv)
	{
		TiXmlElement* node_source = new TiXmlElement("source");
		node_mesh->LinkEndChild(node_source);
		node_source->SetAttribute("id", name + "_uv");
		node_source->SetAttribute("name", name + "_uv");

		TiXmlElement* node_listFloat = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_listFloat);
		node_listFloat->SetAttribute("id", name + "_uv_floats");
		node_listFloat->SetAttribute("count", nbVertex * 2);
		str = "";
		for (size_t i = 0; i < nbVertex; i++)
		{
			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString(vertices.at(i).text_u);
			str += " " + EMO_BaseFile::FloatToString(vertices.at(i).text_v);
		}
		node_listFloat->LinkEndChild(new TiXmlText(str));

		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbVertex);
		node_accessor->SetAttribute("offset", "0");
		node_accessor->SetAttribute("source", "#" + name + "_uv");
		//node_accessor->SetAttribute("stride", "3");
		node_accessor->SetAttribute("stride", "2");

		TiXmlElement* node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "S");
		node_param->SetAttribute("type", "float");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "T");
		node_param->SetAttribute("type", "float");

		/*
		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "P");
		node_param->SetAttribute("type", "float");
		*/
	}

	/////////////////////////////////////////////////////

	if (haveColor)
	{
		TiXmlElement* node_source = new TiXmlElement("source");
		node_mesh->LinkEndChild(node_source);
		node_source->SetAttribute("id", name + "_color");
		node_source->SetAttribute("name", name + "_color");

		TiXmlElement* node_listFloat = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_listFloat);
		node_listFloat->SetAttribute("id", name + "_color_floats");
		node_listFloat->SetAttribute("count", nbVertex * 4);
		str = "";
		for (size_t i = 0; i < nbVertex; i++)
			str += ((i == 0) ? "" : " ") + vertices.at(i).getColorFromRGBA_str();
		node_listFloat->LinkEndChild(new TiXmlText(str));

		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbVertex);
		node_accessor->SetAttribute("offset", "0");
		node_accessor->SetAttribute("source", "#" + name + "_color_floats");
		node_accessor->SetAttribute("stride", "4");

		TiXmlElement* node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "R");
		node_param->SetAttribute("type", "float");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "G");
		node_param->SetAttribute("type", "float");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "B");
		node_param->SetAttribute("type", "float");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "A");
		node_param->SetAttribute("type", "float");
	}

	/////////////////////////////////////////////////////

	TiXmlElement* node_vertices = new TiXmlElement("vertices");
	node_mesh->LinkEndChild(node_vertices);
	node_vertices->SetAttribute("id", name + "_vertices");

	size_t incOffset = 0;
	if (havePosition)
	{
		TiXmlElement * node_input = new TiXmlElement("input");
		node_vertices->LinkEndChild(node_input);
		node_input->SetAttribute("semantic", "POSITION");
		node_input->SetAttribute("source", "#" + name + "_positions");
		++incOffset;
	}

	if (haveUv)
	{
		TiXmlElement* node_input = new TiXmlElement("input");
		node_vertices->LinkEndChild(node_input);
		node_input->SetAttribute("semantic", "TEXCOORD");
		node_input->SetAttribute("offset", incOffset);
		node_input->SetAttribute("set", "1");
		node_input->SetAttribute("source", "#" + name + "_uv");
		++incOffset;
	}

	if (haveColor)
	{
		TiXmlElement* node_input = new TiXmlElement("input");
		node_vertices->LinkEndChild(node_input);
		node_input->SetAttribute("semantic", "COLOR");
		node_input->SetAttribute("offset", incOffset);
		node_input->SetAttribute("set", "0");
		node_input->SetAttribute("source", "#" + name + "_color");
		++incOffset;
	}

	/////////////////////////////////////////////////////


	size_t nbTriangles = triangles.size();
	for (size_t i = 0; i < nbTriangles; i++)
	{
		EMDTriangles &triangle = triangles.at(i);
		size_t nbFaceIndices = triangle.faces.size();

		TiXmlElement* node_polylist = new TiXmlElement("triangles");			// it's for "tristrips" strip. but we coudl also use "triangles", "polylist" for list of group.
		node_mesh->LinkEndChild(node_polylist);
		node_polylist->SetAttribute("count", nbFaceIndices / 3);
		node_polylist->SetAttribute("material", materialName);

		TiXmlElement* node_input = new TiXmlElement("input");
		node_polylist->LinkEndChild(node_input);
		node_input->SetAttribute("offset", "0");
		node_input->SetAttribute("semantic", "VERTEX");
		node_input->SetAttribute("source", "#" + name + "_vertices");

		TiXmlElement* node_p = new TiXmlElement("p");
		node_polylist->LinkEndChild(node_p);
		str = "";
		for (size_t j = 0; j < nbFaceIndices; j++)
			str += ((j == 0) ? "" : " ") + std::to_string(triangle.faces.at(j));
		node_p->LinkEndChild(new TiXmlText(str));
	}
}


/*-------------------------------------------------------------------------------\
|                             addTextureMaterial								 |
\-------------------------------------------------------------------------------*/
void Collada::addTextureMaterial(string name, string filename)
{
	size_t nbMat = listMaterialNames.size();
	for (size_t i = 0; i < nbMat; i++)						//avoid duplications
		if (listMaterialNames.at(i) == name)
			return;

	listMaterialNames.push_back(name);

	addImage(name, filename);
	addEffect(name, true, name);
	addMaterial(name, name);
}
/*-------------------------------------------------------------------------------\
|                             addColorMaterial									 |
\-------------------------------------------------------------------------------*/
void Collada::addColorMaterial(string name, string color)
{
	size_t nbMat = listMaterialNames.size();
	for (size_t i = 0; i < nbMat; i++)						//avoid duplications
		if (listMaterialNames.at(i) == name)
			return;

	listMaterialNames.push_back(name);

	addEffect(name, false, "", color);
	addMaterial(name, name);
}


/*-------------------------------------------------------------------------------\
|                             createNode										 |
\-------------------------------------------------------------------------------*/
TiXmlElement* Collada::createNode(string name, TiXmlElement* parentNode, float transX, float transY, float transZ, float rotAxisX, float rotAxisY, float rotAxisZ, float rotAngle, string instanceGeometryName, string materialName, bool haveTexture)
{
	if (!parentNode)
		parentNode = node_visual_scene;

	
	TiXmlElement* node = new TiXmlElement("node");
	parentNode->LinkEndChild(node);
	node->SetAttribute("id", name);
	node->SetAttribute("name", name);

	addTransformOnNode(node, transX, transY, transZ, rotAxisX, rotAxisY, rotAxisZ, rotAngle);

	if (instanceGeometryName.length() != 0)
		makeInstanceGeometryOnNode(node, instanceGeometryName, materialName, haveTexture);

	return node;
}
/*-------------------------------------------------------------------------------\
|                             makeInstanceGeometryOnNode						 |
\-------------------------------------------------------------------------------*/
void Collada::makeInstanceGeometryOnNode(TiXmlElement* node, string instanceGeometryName, string materialName, bool haveTexture)
{
	TiXmlElement* node_instance_geometry = new TiXmlElement("instance_geometry");
	node->LinkEndChild(node_instance_geometry);
	node_instance_geometry->SetAttribute("url", "#" + instanceGeometryName);

	if (materialName.length() != 0)
	{
		TiXmlElement* node_material = new TiXmlElement("bind_material");
		node_instance_geometry->LinkEndChild(node_material);

		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_material->LinkEndChild(node_technique_common);

		TiXmlElement* node_instance_material = new TiXmlElement("instance_material");
		node_technique_common->LinkEndChild(node_instance_material);
		node_instance_material->SetAttribute("symbol", materialName);
		node_instance_material->SetAttribute("target", "#" + materialName);

		if (haveTexture)
		{
			TiXmlElement* node_bind_vertex_input = new TiXmlElement("bind_vertex_input");
			node_instance_material->LinkEndChild(node_bind_vertex_input);
			node_bind_vertex_input->SetAttribute("semantic", "TEX0");
			node_bind_vertex_input->SetAttribute("input_semantic", "TEXCOORD");
			node_bind_vertex_input->SetAttribute("input_set", "0");
		}
	}
}
/*-------------------------------------------------------------------------------\
|                             addTransformOnNode								 |
\-------------------------------------------------------------------------------*/
void Collada::addTransformOnNode(TiXmlElement* node, float transX, float transY, float transZ, float rotAxisX, float rotAxisY, float rotAxisZ, float rotAngle)
{
	TiXmlElement* node_translate = node->FirstChildElement("translate");
	if (!node_translate)
	{
		node_translate = new TiXmlElement("translate");
		node->LinkEndChild(node_translate);
	}

	node_translate->SetAttribute("sid", "translate");
	TiXmlText* text =(TiXmlText*)node_translate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_translate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(transX) + " " + EMO_BaseFile::FloatToString(transY) + " " + EMO_BaseFile::FloatToString(transZ));

	
	TiXmlElement* node_rotate = node->FirstChildElement("rotate");
	if (!node_rotate)
	{
		node_rotate = new TiXmlElement("rotate");
		node->LinkEndChild(node_rotate);
	}

	node_rotate->SetAttribute("sid", "rotate");
	text = (TiXmlText*)node_rotate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_rotate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(rotAxisX) + " " + EMO_BaseFile::FloatToString(rotAxisY) + " " + EMO_BaseFile::FloatToString(rotAxisZ) + " " + EMO_BaseFile::FloatToString(rotAngle));
}
/*-------------------------------------------------------------------------------\
|                             addImage											 |
\-------------------------------------------------------------------------------*/
void Collada::addImage(string name, string filename)
{
	TiXmlElement* node_image = new TiXmlElement("image");
	node_library_images->LinkEndChild(node_image);
	node_image->SetAttribute("id", name + "_texture");
	node_image->SetAttribute("name", name + "_texture");
	node_image->SetAttribute("depth", "1");

	TiXmlElement* node_init_from = new TiXmlElement("init_from");
	node_image->LinkEndChild(node_init_from);
	node_init_from->LinkEndChild(new TiXmlText(filename));
}
/*-------------------------------------------------------------------------------\
|                             addEffect											 |
\-------------------------------------------------------------------------------*/
void Collada::addEffect(string name, bool isSampler2D, string nameTexture, string color)
{
	TiXmlElement* node_effect = new TiXmlElement("effect");
	node_library_effects->LinkEndChild(node_effect);
	node_effect->SetAttribute("id", name);

	TiXmlElement* node_profile_COMMON = new TiXmlElement("profile_COMMON");
	node_effect->LinkEndChild(node_profile_COMMON);

	TiXmlElement* node_newparam = new TiXmlElement("newparam");
	node_profile_COMMON->LinkEndChild(node_newparam);
	node_newparam->SetAttribute("sid", name + "_surface");

	TiXmlElement* node_surface = new TiXmlElement("surface");
	node_newparam->LinkEndChild(node_surface);
	node_surface->SetAttribute("type", "2D");

	TiXmlElement* node_init_from = new TiXmlElement("init_from");
	node_surface->LinkEndChild(node_init_from);
	node_init_from->LinkEndChild(new TiXmlText(name +"_texture"));

	TiXmlElement* node_format = new TiXmlElement("format");
	node_surface->LinkEndChild(node_format);
	node_format->LinkEndChild(new TiXmlText("A8R8G8B8"));

	///////////////


	node_newparam = new TiXmlElement("newparam");
	node_profile_COMMON->LinkEndChild(node_newparam);
	node_newparam->SetAttribute("sid", name + "_sampler");

	TiXmlElement* node_sampler2D = new TiXmlElement("sampler2D");
	node_newparam->LinkEndChild(node_sampler2D);

	TiXmlElement* node_source = new TiXmlElement("source");
	node_sampler2D->LinkEndChild(node_source);
	node_source->LinkEndChild(new TiXmlText(name + "_surface"));

	TiXmlElement* node_minfilter = new TiXmlElement("minfilter");
	node_sampler2D->LinkEndChild(node_minfilter);
	node_minfilter->LinkEndChild(new TiXmlText("LINEAR_MIPMAP_LINEAR"));

	TiXmlElement* node_magfilter = new TiXmlElement("magfilter");
	node_sampler2D->LinkEndChild(node_magfilter);
	node_magfilter->LinkEndChild(new TiXmlText("LINEAR"));

	///////////////


	TiXmlElement* node_technique = new TiXmlElement("technique");
	node_profile_COMMON->LinkEndChild(node_technique);
	node_technique->SetAttribute("sid", "common");						//could personalize for 3dsmax, maya , etc ....

	TiXmlElement* node_blinn = new TiXmlElement("blinn");
	node_technique->LinkEndChild(node_blinn);


	TiXmlElement* node_emission = new TiXmlElement("emission");
	node_blinn->LinkEndChild(node_emission);
	TiXmlElement* node_color = new TiXmlElement("color");
	node_emission->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));


	TiXmlElement* node_ambient = new TiXmlElement("ambient");
	node_blinn->LinkEndChild(node_ambient);
	node_color = new TiXmlElement("color");
	node_ambient->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText( (!isSampler2D) ? color : "0 0 0 1"));


	TiXmlElement* node_diffuse = new TiXmlElement("diffuse");
	node_blinn->LinkEndChild(node_diffuse);
	if (isSampler2D)
	{
		TiXmlElement* node_texture = new TiXmlElement("texture");
		node_diffuse->LinkEndChild(node_texture);
		node_texture->SetAttribute("texture", name + "_sampler");
		node_texture->SetAttribute("texcoord", "TEX0");
	}else {
		node_color = new TiXmlElement("color");
		node_diffuse->LinkEndChild(node_color);
		node_color->LinkEndChild(new TiXmlText(color));
	}

	TiXmlElement* node_specular = new TiXmlElement("specular");
	node_blinn->LinkEndChild(node_specular);
	node_color = new TiXmlElement("color");
	node_specular->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));


	TiXmlElement* node_shininess = new TiXmlElement("shininess");
	node_blinn->LinkEndChild(node_shininess);
	TiXmlElement* node_float = new TiXmlElement("float");
	node_shininess->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("0.3"));

	TiXmlElement* node_reflective = new TiXmlElement("reflective");
	node_blinn->LinkEndChild(node_reflective);
	node_color = new TiXmlElement("color");
	node_reflective->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));

	TiXmlElement* node_reflectivity = new TiXmlElement("reflectivity");
	node_blinn->LinkEndChild(node_reflectivity);
	node_float = new TiXmlElement("float");
	node_reflectivity->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("0.5"));


	TiXmlElement* node_transparent = new TiXmlElement("transparent");
	node_blinn->LinkEndChild(node_transparent);
	node_color = new TiXmlElement("color");
	node_transparent->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));

	TiXmlElement* node_transparency = new TiXmlElement("transparency");
	node_blinn->LinkEndChild(node_transparency);
	node_float = new TiXmlElement("float");
	node_transparency->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("1"));

	TiXmlElement* node_index_of_refraction = new TiXmlElement("index_of_refraction");
	node_blinn->LinkEndChild(node_index_of_refraction);
	node_float = new TiXmlElement("float");
	node_index_of_refraction->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("1"));
}
/*-------------------------------------------------------------------------------\
|                             addMaterial										 |
\-------------------------------------------------------------------------------*/
void Collada::addMaterial(string name, string nameEffect)
{
	TiXmlElement* node_material = new TiXmlElement("material");
	node_library_materials->LinkEndChild(node_material);
	node_material->SetAttribute("id", name);
	node_material->SetAttribute("name", name);

	TiXmlElement* node_instance_effect = new TiXmlElement("instance_effect");
	node_material->LinkEndChild(node_instance_effect);
	node_instance_effect->SetAttribute("url", "#" + nameEffect);
}



/*-------------------------------------------------------------------------------\
|                             save												 |
\-------------------------------------------------------------------------------*/
void Collada::save(string filename)
{
	doc->SaveFile(filename);
}





/*
{
	//test Collada
	TiXmlDocument *doc = new TiXmlDocument();
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc->LinkEndChild(decl);

	TiXmlElement* root = new TiXmlElement("COLLADA");
	doc->LinkEndChild(root);
	root->SetAttribute("xmlns", "http://www.collada.org/2005/11/COLLADASchema");
	root->SetAttribute("version", "1.4.1");


	/////////////////////////////////////////////////////

	TiXmlElement* node_asset = new TiXmlElement("asset");
	root->LinkEndChild(node_asset);

	TiXmlElement* node_unit = new TiXmlElement("unit");
	node_asset->LinkEndChild(node_unit);
	node_unit->SetAttribute("meter", "1");
	node_unit->SetAttribute("name", "meter");

	TiXmlElement* node_up_axis = new TiXmlElement("up_axis");
	node_asset->LinkEndChild(node_up_axis);
	node_up_axis->LinkEndChild(new TiXmlText("Y_UP"));


	/////////////////////////////////////////////////////

	root->LinkEndChild(new TiXmlElement("library_cameras"));
	root->LinkEndChild(new TiXmlElement("library_lights"));



	/////////////////////////////////////////////////////

	TiXmlElement* node_library_images = new TiXmlElement("library_images");
	root->LinkEndChild(node_library_images);

	TiXmlElement* node_image = new TiXmlElement("image");
	node_library_images->LinkEndChild(node_image);
	node_image->SetAttribute("id", "texture_0");
	node_image->SetAttribute("name", "texture_0");
	node_image->SetAttribute("depth", "1");


	TiXmlElement* node_init_from = new TiXmlElement("init_from");
	node_image->LinkEndChild(node_init_from);
	node_init_from->LinkEndChild(new TiXmlText("./duckCM.tga"));


	/////////////////////////////////////////////////////


	TiXmlElement* node_library_effects = new TiXmlElement("library_effects");
	root->LinkEndChild(node_library_effects);

	TiXmlElement* node_effect = new TiXmlElement("effect");
	node_library_effects->LinkEndChild(node_effect);
	node_effect->SetAttribute("id", "effect_0");

	TiXmlElement* node_profile_COMMON = new TiXmlElement("profile_COMMON");
	node_effect->LinkEndChild(node_profile_COMMON);

	TiXmlElement* node_newparam = new TiXmlElement("newparam");
	node_profile_COMMON->LinkEndChild(node_newparam);
	node_newparam->SetAttribute("sid", "surface_0");

	TiXmlElement* node_surface = new TiXmlElement("surface");
	node_newparam->LinkEndChild(node_surface);
	node_surface->SetAttribute("type", "2D");

	node_init_from = new TiXmlElement("init_from");
	node_surface->LinkEndChild(node_init_from);
	node_init_from->LinkEndChild(new TiXmlText("texture_0"));

	TiXmlElement* node_format = new TiXmlElement("format");
	node_surface->LinkEndChild(node_format);
	node_format->LinkEndChild(new TiXmlText("A8R8G8B8"));

	///////////////


	node_newparam = new TiXmlElement("newparam");
	node_profile_COMMON->LinkEndChild(node_newparam);
	node_newparam->SetAttribute("sid", "sampler_0");

	TiXmlElement* node_sampler2D = new TiXmlElement("sampler2D");
	node_newparam->LinkEndChild(node_sampler2D);

	TiXmlElement* node_source = new TiXmlElement("source");
	node_sampler2D->LinkEndChild(node_source);
	node_source->LinkEndChild(new TiXmlText("surface_0"));

	TiXmlElement* node_minfilter = new TiXmlElement("minfilter");
	node_sampler2D->LinkEndChild(node_minfilter);
	node_minfilter->LinkEndChild(new TiXmlText("LINEAR_MIPMAP_LINEAR"));

	TiXmlElement* node_magfilter = new TiXmlElement("magfilter");
	node_sampler2D->LinkEndChild(node_magfilter);
	node_magfilter->LinkEndChild(new TiXmlText("LINEAR"));

	///////////////


	TiXmlElement* node_technique = new TiXmlElement("technique");
	node_profile_COMMON->LinkEndChild(node_technique);
	node_technique->SetAttribute("sid", "common");

	TiXmlElement* node_blinn = new TiXmlElement("blinn");
	node_technique->LinkEndChild(node_blinn);


	TiXmlElement* node_emission = new TiXmlElement("emission");
	node_blinn->LinkEndChild(node_emission);
	TiXmlElement* node_color = new TiXmlElement("color");
	node_emission->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));


	TiXmlElement* node_ambient = new TiXmlElement("ambient");
	node_blinn->LinkEndChild(node_ambient);
	node_color = new TiXmlElement("color");
	node_ambient->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));


	TiXmlElement* node_diffuse = new TiXmlElement("diffuse");
	node_blinn->LinkEndChild(node_diffuse);
	TiXmlElement* node_texture = new TiXmlElement("texture");
	node_diffuse->LinkEndChild(node_texture);
	node_texture->SetAttribute("texture", "sampler_0");
	node_texture->SetAttribute("texcoord", "TEX0");

	TiXmlElement* node_specular = new TiXmlElement("specular");
	node_blinn->LinkEndChild(node_specular);
	node_color = new TiXmlElement("color");
	node_specular->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));


	TiXmlElement* node_shininess = new TiXmlElement("shininess");
	node_blinn->LinkEndChild(node_shininess);
	TiXmlElement* node_float = new TiXmlElement("float");
	node_shininess->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("0.3"));

	TiXmlElement* node_reflective = new TiXmlElement("reflective");
	node_blinn->LinkEndChild(node_reflective);
	node_color = new TiXmlElement("color");
	node_reflective->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));

	TiXmlElement* node_reflectivity = new TiXmlElement("reflectivity");
	node_blinn->LinkEndChild(node_reflectivity);
	node_float = new TiXmlElement("float");
	node_reflectivity->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("0.5"));


	TiXmlElement* node_transparent = new TiXmlElement("transparent");
	node_blinn->LinkEndChild(node_transparent);
	node_color = new TiXmlElement("color");
	node_transparent->LinkEndChild(node_color);
	node_color->LinkEndChild(new TiXmlText("0 0 0 1"));

	TiXmlElement* node_transparency = new TiXmlElement("transparency");
	node_blinn->LinkEndChild(node_transparency);
	node_float = new TiXmlElement("float");
	node_transparency->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("1"));

	TiXmlElement* node_index_of_refraction = new TiXmlElement("index_of_refraction");
	node_blinn->LinkEndChild(node_index_of_refraction);
	node_float = new TiXmlElement("float");
	node_index_of_refraction->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("1"));

	/////////////////////////////////////////////////////


	TiXmlElement* node_library_materials = new TiXmlElement("library_materials");
	root->LinkEndChild(node_library_materials);

	TiXmlElement* node_material = new TiXmlElement("material");
	node_library_materials->LinkEndChild(node_material);
	node_material->SetAttribute("id", "mat_0");
	node_material->SetAttribute("name", "mat_0");


	TiXmlElement* node_instance_effect = new TiXmlElement("instance_effect");
	node_material->LinkEndChild(node_instance_effect);
	node_instance_effect->SetAttribute("url", "#effect_0");


	/////////////////////////////////////////////////////


	TiXmlElement* node_geometries = new TiXmlElement("library_geometries");
	root->LinkEndChild(node_geometries);


	TiXmlElement* node_geometry = new TiXmlElement("geometry");
	node_geometries->LinkEndChild(node_geometry);
	node_geometry->SetAttribute("id", "box-lib");
	node_geometry->SetAttribute("name", "box");

	TiXmlElement* node_mesh = new TiXmlElement("mesh");
	node_geometry->LinkEndChild(node_mesh);


	node_source = new TiXmlElement("source");
	node_mesh->LinkEndChild(node_source);
	node_source->SetAttribute("id", "box-lib-positions");
	node_source->SetAttribute("name", "position");

	TiXmlElement* node_listFloat = new TiXmlElement("float_array");
	node_source->LinkEndChild(node_listFloat);
	node_listFloat->SetAttribute("id", "box-lib-positions-array");
	node_listFloat->SetAttribute("count", "24");
	node_listFloat->LinkEndChild(new TiXmlText("-50 50 50 50 50 50 -50 -50 50 50 -50 50 -50 50 -50 50 50 -50 -50 -50 -50 50 -50 -50"));

	TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
	node_source->LinkEndChild(node_technique_common);

	TiXmlElement* node_accessor = new TiXmlElement("accessor");
	node_technique_common->LinkEndChild(node_accessor);
	node_accessor->SetAttribute("count", "8");
	node_accessor->SetAttribute("offset", "0");
	node_accessor->SetAttribute("source", "#box-lib-positions-array");
	node_accessor->SetAttribute("stride", "3");

	TiXmlElement* node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "X");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "Y");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "Z");
	node_param->SetAttribute("type", "float");

	/////////////////////////////////////////////////////

	node_source = new TiXmlElement("source");
	node_mesh->LinkEndChild(node_source);
	node_source->SetAttribute("id", "box-lib-normals");
	node_source->SetAttribute("name", "normal");

	node_listFloat = new TiXmlElement("float_array");
	node_source->LinkEndChild(node_listFloat);
	node_listFloat->SetAttribute("id", "box-lib-normals-array");
	node_listFloat->SetAttribute("count", "72");
	node_listFloat->LinkEndChild(new TiXmlText("0 0 1 0 0 1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 0 1 0 0 -1 0 0 -1 0 0 -1 0 0 -1 0 -1 0 0 -1 0 0 -1 0 0 -1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 0 0 -1 0 0 -1 0 0 -1 0 0 -1"));

	node_technique_common = new TiXmlElement("technique_common");
	node_source->LinkEndChild(node_technique_common);

	node_accessor = new TiXmlElement("accessor");
	node_technique_common->LinkEndChild(node_accessor);
	node_accessor->SetAttribute("count", "24");
	node_accessor->SetAttribute("offset", "0");
	node_accessor->SetAttribute("source", "#box-lib-normals-array");
	node_accessor->SetAttribute("stride", "3");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "X");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "Y");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "Z");
	node_param->SetAttribute("type", "float");



	/////////////////////////////////////////////////////

	node_source = new TiXmlElement("source");
	node_mesh->LinkEndChild(node_source);
	node_source->SetAttribute("id", "box-lib-uv");
	node_source->SetAttribute("name", "uv");

	node_listFloat = new TiXmlElement("float_array");
	node_source->LinkEndChild(node_listFloat);
	node_listFloat->SetAttribute("id", "box-lib-uv-array");
	node_listFloat->SetAttribute("count", "24");
	node_listFloat->LinkEndChild(new TiXmlText("0 0 0 1 0 0 1 1 0 0 1 0 0 0 0 1 0 0 1 1 0 0 1 0"));

	node_technique_common = new TiXmlElement("technique_common");
	node_source->LinkEndChild(node_technique_common);

	node_accessor = new TiXmlElement("accessor");
	node_technique_common->LinkEndChild(node_accessor);
	node_accessor->SetAttribute("count", "8");
	node_accessor->SetAttribute("offset", "0");
	node_accessor->SetAttribute("source", "#box-lib-uv-array");
	node_accessor->SetAttribute("stride", "3");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "S");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "T");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "P");
	node_param->SetAttribute("type", "float");


	/////////////////////////////////////////////////////

	node_source = new TiXmlElement("source");
	node_mesh->LinkEndChild(node_source);
	node_source->SetAttribute("id", "box-lib-color");
	node_source->SetAttribute("name", "color");

	node_listFloat = new TiXmlElement("float_array");
	node_source->LinkEndChild(node_listFloat);
	node_listFloat->SetAttribute("id", "box-lib-color-array");
	node_listFloat->SetAttribute("count", "32");
	node_listFloat->LinkEndChild(new TiXmlText("0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1"));

	node_technique_common = new TiXmlElement("technique_common");
	node_source->LinkEndChild(node_technique_common);

	node_accessor = new TiXmlElement("accessor");
	node_technique_common->LinkEndChild(node_accessor);
	node_accessor->SetAttribute("count", "8");
	node_accessor->SetAttribute("offset", "0");
	node_accessor->SetAttribute("source", "#box-lib-color-array");
	node_accessor->SetAttribute("stride", "4");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "R");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "G");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "B");
	node_param->SetAttribute("type", "float");

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "A");
	node_param->SetAttribute("type", "float");

	/////////////////////////////////////////////////////

	TiXmlElement* node_vertices = new TiXmlElement("vertices");
	node_mesh->LinkEndChild(node_vertices);
	node_vertices->SetAttribute("id", "box-lib-vertices");

	TiXmlElement * node_input = new TiXmlElement("input");
	node_vertices->LinkEndChild(node_input);
	node_input->SetAttribute("semantic", "POSITION");
	node_input->SetAttribute("source", "#box-lib-positions");


	node_input = new TiXmlElement("input");
	node_vertices->LinkEndChild(node_input);
	node_input->SetAttribute("semantic", "TEXCOORD");
	node_input->SetAttribute("offset", "1");
	node_input->SetAttribute("set", "1");
	node_input->SetAttribute("source", "#box-lib-uv");


	node_input = new TiXmlElement("input");
	node_vertices->LinkEndChild(node_input);
	node_input->SetAttribute("semantic", "COLOR");
	node_input->SetAttribute("offset", "2");
	node_input->SetAttribute("set", "0");
	node_input->SetAttribute("source", "#box-lib-color");


	/////////////////////////////////////////////////////

	TiXmlElement* node_polylist = new TiXmlElement("polylist");			// it's for "tristrips" strip. but we coudl also use "triangles", "polylist" for list of group.
	node_mesh->LinkEndChild(node_polylist);
	node_polylist->SetAttribute("count", "6");
	node_polylist->SetAttribute("material", "mat_0");


	node_input = new TiXmlElement("input");
	node_polylist->LinkEndChild(node_input);
	node_input->SetAttribute("offset", "0");
	node_input->SetAttribute("semantic", "VERTEX");
	node_input->SetAttribute("source", "#box-lib-vertices");

	node_input = new TiXmlElement("input");
	node_polylist->LinkEndChild(node_input);
	node_input->SetAttribute("offset", "1");
	node_input->SetAttribute("semantic", "NORMAL");
	node_input->SetAttribute("source", "#box-lib-normals");

	TiXmlElement* node_vcount = new TiXmlElement("vcount");
	node_polylist->LinkEndChild(node_vcount);
	node_vcount->LinkEndChild(new TiXmlText("4 4 4 4 4 4"));

	TiXmlElement* node_p = new TiXmlElement("p");
	node_polylist->LinkEndChild(node_p);
	node_p->LinkEndChild(new TiXmlText("0 0 2 1 3 2 1 3 0 4 1 5 5 6 4 7 6 8 7 9 3 10 2 11 0 12 4 13 6 14 2 15 3 16 7 17 5 18 1 19 5 20 7 21 6 22 4 23"));


	/////////////////////////////////////////////////////


	TiXmlElement* node_scene = new TiXmlElement("library_visual_scenes");
	root->LinkEndChild(node_scene);

	TiXmlElement* node_visual_scene = new TiXmlElement("visual_scene");
	node_scene->LinkEndChild(node_visual_scene);
	node_visual_scene->SetAttribute("id", "VisualSceneNode");
	node_visual_scene->SetAttribute("name", "untitled");

	TiXmlElement* node = new TiXmlElement("node");
	node_visual_scene->LinkEndChild(node);
	node->SetAttribute("id", "Box");
	node->SetAttribute("name", "Box");

	TiXmlElement* node_translate = new TiXmlElement("translate");
	node->LinkEndChild(node_translate);
	node_translate->SetAttribute("sid", "translate");
	node_translate->LinkEndChild(new TiXmlText("-500 1000 400"));

	TiXmlElement* node_rotate = new TiXmlElement("rotate");
	node->LinkEndChild(node_rotate);
	node_rotate->SetAttribute("sid", "rotateY");
	node_rotate->LinkEndChild(new TiXmlText("0 1 0 45"));

	/*
	<rotate sid="rotateZ">0 0 1 0</rotate>
	<rotate sid="rotateY">0 1 0 0</rotate>
	<rotate sid="rotateX">1 0 0 0</rotate>
	*//*

	TiXmlElement* node_instance_geometry = new TiXmlElement("instance_geometry");
	node->LinkEndChild(node_instance_geometry);
	node_instance_geometry->SetAttribute("url", "#box-lib");

	node_material = new TiXmlElement("bind_material");
	node_instance_geometry->LinkEndChild(node_material);

	node_technique_common = new TiXmlElement("technique_common");
	node_material->LinkEndChild(node_technique_common);

	TiXmlElement* node_instance_material = new TiXmlElement("instance_material");
	node_technique_common->LinkEndChild(node_instance_material);
	node_instance_material->SetAttribute("symbol", "mat_0");
	node_instance_material->SetAttribute("target", "#mat_0");

	TiXmlElement* node_bind_vertex_input = new TiXmlElement("bind_vertex_input");
	node_instance_material->LinkEndChild(node_bind_vertex_input);
	node_bind_vertex_input->SetAttribute("semantic", "TEX0");
	node_bind_vertex_input->SetAttribute("input_semantic", "TEXCOORD");
	node_bind_vertex_input->SetAttribute("input_set", "0");


	/////////////////////////////////////////////////////


	TiXmlElement* node_library_animations = new TiXmlElement("library_animations");
	root->LinkEndChild(node_library_animations);

	/*

	<animation id="Box001-anim" name="Box001"></animation>
	<animation>
	<source id="Box001-rotateX.ANGLE-input">
	<float_array id="Box001-rotateX.ANGLE-input-array" count="2">0.033333 11.966667</float_array>
	<technique_common>
	<accessor source="#Box001-rotateX.ANGLE-input-array" count="2" stride="1">
	<param type="float"></param>
	</accessor>
	</technique_common>
	</source>
	<source id="Box001-rotateX.ANGLE-output">
	<float_array id="Box001-rotateX.ANGLE-output-array" count="2">0.000000 0.000000</float_array>
	<technique_common>
	<accessor source="#Box001-rotateX.ANGLE-output-array" count="2" stride="1">
	<param type="float"></param>
	</accessor>
	</technique_common>
	</source>
	<source id="Box001-rotateX.ANGLE-interpolation">
	<Name_array id="Box001-rotateX.ANGLE-interpolation-array" count="2">LINEAR LINEAR</Name_array>
	<technique_common>
	<accessor source="#Box001-rotateX.ANGLE-interpolation-array" count="2" stride="1">
	<param type="name"></param>
	</accessor>
	</technique_common>
	</source>
	<sampler id="Box001-rotateX.ANGLE">
	<input semantic="INPUT" source="#Box001-rotateX.ANGLE-input"></input>
	<input semantic="OUTPUT" source="#Box001-rotateX.ANGLE-output"></input>
	<input semantic="INTERPOLATION" source="#Box001-rotateX.ANGLE-interpolation"></input>
	</sampler>
	<channel source="#Box001-rotateX.ANGLE" target="Box001/rotateX.ANGLE"></channel>
	</animation>

	//another for Box001-rotateY.ANGLE and Z ....

	<library_visual_scenes>
	<visual_scene id="Array Test 001" name="Array Test 001">
	<node name="Box001" id="Box001" sid="Box001"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box001-Pivot" name="Box001-Pivot"><translate>0.185947 0.000000 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box001-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box002" id="Box002" sid="Box002"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box002-Pivot" name="Box002-Pivot"><translate>0.185947 1.891823 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box002-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box003" id="Box003" sid="Box003"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box003-Pivot" name="Box003-Pivot"><translate>0.185946 3.783642 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box003-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box004" id="Box004" sid="Box004"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box004-Pivot" name="Box004-Pivot"><translate>0.185944 5.675461 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box004-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box005" id="Box005" sid="Box005"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box005-Pivot" name="Box005-Pivot"><translate>0.185942 7.567280 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box005-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box006" id="Box006" sid="Box006"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box006-Pivot" name="Box006-Pivot"><translate>0.185939 9.459099 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box006-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box007" id="Box007" sid="Box007"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box007-Pivot" name="Box007-Pivot"><translate>0.185935 11.350918 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box007-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box008" id="Box008" sid="Box008"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box008-Pivot" name="Box008-Pivot"><translate>0.185931 13.242737 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box008-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box009" id="Box009" sid="Box009"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box009-Pivot" name="Box009-Pivot"><translate>0.185927 15.134556 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box009-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box010" id="Box010" sid="Box010"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box010-Pivot" name="Box010-Pivot"><translate>0.185922 17.026375 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box010-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box011" id="Box011" sid="Box011"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box011-Pivot" name="Box011-Pivot"><translate>0.185916 18.918194 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box011-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box012" id="Box012" sid="Box012"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box012-Pivot" name="Box012-Pivot"><translate>0.185910 20.810013 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box012-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box013" id="Box013" sid="Box013"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box013-Pivot" name="Box013-Pivot"><translate>0.185903 22.701832 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box013-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box014" id="Box014" sid="Box014"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box014-Pivot" name="Box014-Pivot"><translate>0.185895 24.593651 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box014-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box015" id="Box015" sid="Box015"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box015-Pivot" name="Box015-Pivot"><translate>0.185887 26.485470 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box015-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box016" id="Box016" sid="Box016"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box016-Pivot" name="Box016-Pivot"><translate>0.185879 28.377289 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box016-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box017" id="Box017" sid="Box017"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box017-Pivot" name="Box017-Pivot"><translate>0.185870 30.269108 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box017-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box018" id="Box018" sid="Box018"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box018-Pivot" name="Box018-Pivot"><translate>0.185860 32.160927 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box018-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box019" id="Box019" sid="Box019"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box019-Pivot" name="Box019-Pivot"><translate>0.185850 34.052746 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box019-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box020" id="Box020" sid="Box020"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box020-Pivot" name="Box020-Pivot"><translate>0.185839 35.944565 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box020-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box021" id="Box021" sid="Box021"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box021-Pivot" name="Box021-Pivot"><translate>0.185827 37.836384 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box021-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box022" id="Box022" sid="Box022"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box022-Pivot" name="Box022-Pivot"><translate>0.185815 39.728203 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box022-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box023" id="Box023" sid="Box023"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box023-Pivot" name="Box023-Pivot"><translate>0.185803 41.620022 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box023-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box024" id="Box024" sid="Box024"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box024-Pivot" name="Box024-Pivot"><translate>0.185790 43.511841 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box024-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box025" id="Box025" sid="Box025"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box025-Pivot" name="Box025-Pivot"><translate>0.185776 45.403660 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box025-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box026" id="Box026" sid="Box026"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box026-Pivot" name="Box026-Pivot"><translate>0.185762 47.295479 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box026-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box027" id="Box027" sid="Box027"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box027-Pivot" name="Box027-Pivot"><translate>0.185747 49.187302 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box027-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box028" id="Box028" sid="Box028"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box028-Pivot" name="Box028-Pivot"><translate>0.185731 51.079117 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box028-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box029" id="Box029" sid="Box029"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box029-Pivot" name="Box029-Pivot"><translate>0.185715 52.970940 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box029-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box030" id="Box030" sid="Box030"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box030-Pivot" name="Box030-Pivot"><translate>0.185699 54.862755 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box030-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box031" id="Box031" sid="Box031"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box031-Pivot" name="Box031-Pivot"><translate>0.185682 56.754578 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box031-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box032" id="Box032" sid="Box032"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box032-Pivot" name="Box032-Pivot"><translate>0.185664 58.646393 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box032-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box033" id="Box033" sid="Box033"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box033-Pivot" name="Box033-Pivot"><translate>0.185646 60.538216 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box033-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box034" id="Box034" sid="Box034"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box034-Pivot" name="Box034-Pivot"><translate>0.185627 62.430031 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box034-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box035" id="Box035" sid="Box035"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box035-Pivot" name="Box035-Pivot"><translate>0.185607 64.321854 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box035-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box036" id="Box036" sid="Box036"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box036-Pivot" name="Box036-Pivot"><translate>0.185587 66.213669 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box036-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box037" id="Box037" sid="Box037"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box037-Pivot" name="Box037-Pivot"><translate>0.185567 68.105492 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box037-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box038" id="Box038" sid="Box038"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box038-Pivot" name="Box038-Pivot"><translate>0.185546 69.997307 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box038-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box039" id="Box039" sid="Box039"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box039-Pivot" name="Box039-Pivot"><translate>0.185524 71.889122 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box039-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box040" id="Box040" sid="Box040"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box040-Pivot" name="Box040-Pivot"><translate>0.185502 73.780952 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box040-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box041" id="Box041" sid="Box041"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box041-Pivot" name="Box041-Pivot"><translate>0.185479 75.672768 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box041-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box042" id="Box042" sid="Box042"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box042-Pivot" name="Box042-Pivot"><translate>0.185456 77.564583 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box042-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box043" id="Box043" sid="Box043"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box043-Pivot" name="Box043-Pivot"><translate>0.185432 79.456398 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box043-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box044" id="Box044" sid="Box044"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box044-Pivot" name="Box044-Pivot"><translate>0.185407 81.348228 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box044-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box045" id="Box045" sid="Box045"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box045-Pivot" name="Box045-Pivot"><translate>0.185382 83.240044 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box045-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box046" id="Box046" sid="Box046"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box046-Pivot" name="Box046-Pivot"><translate>0.185356 85.131859 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box046-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box047" id="Box047" sid="Box047"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box047-Pivot" name="Box047-Pivot"><translate>0.185330 87.023674 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box047-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box048" id="Box048" sid="Box048"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box048-Pivot" name="Box048-Pivot"><translate>0.185303 88.915504 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box048-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box049" id="Box049" sid="Box049"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box049-Pivot" name="Box049-Pivot"><translate>0.185276 90.807320 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box049-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box050" id="Box050" sid="Box050"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box050-Pivot" name="Box050-Pivot"><translate>0.185248 92.699135 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box050-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box051" id="Box051" sid="Box051"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box051-Pivot" name="Box051-Pivot"><translate>0.185219 94.590950 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box051-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box052" id="Box052" sid="Box052"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box052-Pivot" name="Box052-Pivot"><translate>0.185190 96.482780 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box052-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box053" id="Box053" sid="Box053"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box053-Pivot" name="Box053-Pivot"><translate>0.185160 98.374596 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box053-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box054" id="Box054" sid="Box054"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box054-Pivot" name="Box054-Pivot"><translate>0.185130 100.266403 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box054-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box055" id="Box055" sid="Box055"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box055-Pivot" name="Box055-Pivot"><translate>0.185099 102.158218 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box055-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box056" id="Box056" sid="Box056"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box056-Pivot" name="Box056-Pivot"><translate>0.185068 104.050034 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box056-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box057" id="Box057" sid="Box057"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box057-Pivot" name="Box057-Pivot"><translate>0.185036 105.941849 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box057-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box058" id="Box058" sid="Box058"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box058-Pivot" name="Box058-Pivot"><translate>0.185003 107.833664 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box058-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box059" id="Box059" sid="Box059"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box059-Pivot" name="Box059-Pivot"><translate>0.184970 109.725479 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box059-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box060" id="Box060" sid="Box060"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box060-Pivot" name="Box060-Pivot"><translate>0.184936 111.617294 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box060-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box061" id="Box061" sid="Box061"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box061-Pivot" name="Box061-Pivot"><translate>0.184902 113.509109 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box061-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box062" id="Box062" sid="Box062"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box062-Pivot" name="Box062-Pivot"><translate>0.184867 115.400925 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box062-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box063" id="Box063" sid="Box063"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box063-Pivot" name="Box063-Pivot"><translate>0.184832 117.292740 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box063-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra><node name="Box064" id="Box064" sid="Box064"><rotate sid="rotateZ">0 0 1 0.000003</rotate><rotate sid="rotateY">0 1 0 -0.000000</rotate><rotate sid="rotateX">1 0 0 0.000000</rotate><node id="Box064-Pivot" name="Box064-Pivot"><translate>0.184796 119.184555 0.000000</translate><rotate>0.000000 0.000000 0.000000 0.000000</rotate><instance_geometry url="#Box064-lib"/></node><extra><technique profile="FCOLLADA"><visibility>1.000000</visibility></technique></extra></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node></node>
	<extra><technique profile="MAX3D"><frame_rate>30.000000</frame_rate></technique><technique profile="FCOLLADA"><start_time>0.000000</start_time><end_time>11.966667</end_time></technique></extra>
	</visual_scene>
	</library_visual_scenes>


	*//*



	/////////////////////////////////////////////////////


	TiXmlElement* node_instanceScene = new TiXmlElement("scene");
	root->LinkEndChild(node_instanceScene);

	TiXmlElement* node_instance_visual_scene = new TiXmlElement("instance_visual_scene");
	node_instanceScene->LinkEndChild(node_instance_visual_scene);
	node_instance_visual_scene->SetAttribute("url", "#VisualSceneNode");





	doc->SaveFile(filename + ".dae");

	delete doc;

	return;
}
*/





/*-------------------------------------------------------------------------------\
|                             Swr_Model											 |
\-------------------------------------------------------------------------------*/
Swr_Model::Swr_Model()
{
	//section 0 - SWR_MODELHeader : black/grey
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#232323");			//background color
	listTagColors.back().back().push_back("#FFFFFF");			//font color (just to possibility read from background color)
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#464646");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 1 - SWR_MODELUnk0AEntry : red
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC0000");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC7777");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 2 - SWR_MODELUnk0BEntry : green
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#00CC00");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#77CC77");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 3 - SWR_MODELUnk1Entry : bleu
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#0000CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#7777CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f




	//section 5 - SWR_MODELUnk2Entry : yellow
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CCCC00");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CCCC77");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f


	//section 6 - SWR_MODELUnk3Entry : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#00CCCC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#77CCCC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 7 - SWR_MODELUnk3Entry indexes : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#009999");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#339999");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f


	//section 8 - SWR_MODELUnk4Entry : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC00CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC77CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f


	//section 9 - SWR_MODELUnk4Entry_Next : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#990099");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#993399");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f



	//section 10 - SWR_MODELUnk4Entry_Next_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9900CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9933CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 11 - SWR_MODELUnk4Entry_Next_c : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC0099");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC3399");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 12 - SWR_MODELUnk4Entry_Next_d : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9900AA");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9933AA");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 13 - SWR_MODELUnk4Entry_Next_e : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA0099");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA3399");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f



	//section 14 - SWR_MODELUnk4Entry_Next2 : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#770077");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#773377");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 15 - SWR_MODELUnk4Entry_Next2_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#550055");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#553355");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f





	//section 16 - SWR_MODELUnk4Entry_Next2 : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA00FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA33FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 17 - SWR_MODELUnk4Entry_Next2_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9900FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9933FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 18 - SWR_MODELUnk4Entry_Next2 : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#7700FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#7733FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 19 - SWR_MODELUnk4Entry_Next2_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#5500FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#5533FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f




	//section 20 - SWR_MODELUnk5Entry : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CCCCCC");			//bg
	listTagColors.back().back().push_back("#000000");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AAAAAA");			//bg
	listTagColors.back().back().push_back("#000000");			//f


	//section 21 - SWR_MODELUnk5Entry_Box : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#999999");			//bg
	listTagColors.back().back().push_back("#000000");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#777777");			//bg
	listTagColors.back().back().push_back("#000000");			//f
}
/*-------------------------------------------------------------------------------\
|                             Reset					                             |
\-------------------------------------------------------------------------------*/
void Swr_Model::Reset()
{
	/*
	mListPart.clear();

	size_t nbText = mListTextureUnit.size();
	for (size_t i = 0; i < nbText; i++)
		delete mListTextureUnit.at(i);
	mListTextureUnit.clear();
	*/
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Xml First Version for Debug ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*-------------------------------------------------------------------------------\
|                             save_Xml				                             |
\-------------------------------------------------------------------------------*/
void Swr_Model::save_Xml(string filename, bool show_error)
{
	//Xml conversion make files bigger. and TinyXml take huge memory in ram. So, here a split of Files ONLY IF many model inside the filename
	std::vector<string> listFilename;
	listFilename.push_back(filename);

	
	//Split , because of TinyXml, Todo commment.
	{
		big_endian = true;
		
		uint8_t *buf;
		size_t size;

		buf = ReadFile(filename, &size, show_error);
		if (!buf)
			return;


		std::vector<size_t> listBytesAllreadyTagged;
		listBytesAllreadyTagged.resize(size, (size_t)-1);				//to check override of the same byte (overflow)

		size_t nbModels = val32(*(uint32_t*)buf);
		if (nbModels > 1)
		{
			printf("There is %i models. to avoid troubles with memory and size of Xml, we split the file by model.\n", nbModels);
			listFilename.clear();

			size_t offset = sizeof(uint32_t);
			size_t startoffsetModelHeader = offset;
			for (size_t i = 0; i < nbModels; i++)
			{
				offset = startoffsetModelHeader + i * sizeof(SWR_MODELHeader);

				SWR_MODELHeader_Used* hdr = (SWR_MODELHeader_Used*)(buf + offset);
				hdr->offset_Section1 = val32(hdr->offset_Section1);
				hdr->offset_Section2 = val32(hdr->offset_Section2);
				size_t offset_NextHeader_Section1 = val32(hdr->offset_NextHeader_Section1);

				size_t sizeSection1 = hdr->offset_Section2 - hdr->offset_Section1;
				size_t sizeSection2 = offset_NextHeader_Section1 - hdr->offset_Section2;

				{
					size_t filesize = 4 * sizeof(uint32_t) + sizeSection1 + sizeSection2;

					uint8_t *buf_tmp = new uint8_t[filesize];
					if (!buf_tmp)
					{
						printf("%s: Memory allocation error (0x%x)\n", FUNCNAME, filesize);
						notifyError();
						return;
					}
					uint32_t* buf_u32 = (uint32_t*)buf_tmp;
					buf_u32[0] = val32(1);
					buf_u32[1] = val32(0x10);
					buf_u32[2] = val32(0x10 + sizeSection1);
					buf_u32[3] = val32(0x10 + sizeSection1 + sizeSection2);
					memcpy(buf_tmp + 4 * sizeof(uint32_t), buf + hdr->offset_Section1, sizeSection1);
					memcpy(buf_tmp + 4 * sizeof(uint32_t) + sizeSection1, buf + hdr->offset_Section2, sizeSection2);


					listFilename.push_back(filename + "_" + UnsignedToString(i, false) + ".bin");
					bool ret = WriteFileBool(listFilename.back(), buf_tmp, filesize);
					delete[] buf_tmp;
				}
			}
		}

		delete[] buf;
	}

	
	
	size_t nbFiles = listFilename.size();
	for (size_t i = 0; i < nbFiles; i++)
	{
		string name = listFilename.at(i);
		printf("******************* Model : %s\n", name.c_str());

		
		uint8_t *buf;
		size_t size;

		buf = ReadFile(name, &size, show_error);
		if (!buf)
			return;

		TiXmlDocument *doc = new TiXmlDocument();
		TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
		doc->LinkEndChild(decl);

		TiXmlElement* root = new TiXmlElement("Swr_Model");
		EMO_BaseFile::WriteParamString(root, "path", name);
		doc->LinkEndChild(root);

		Collada* collada = new Collada();
		collada->addColorMaterial("Default", "1 0 0 1");
		Collada* collada_collision = new Collada();
		collada_collision->addColorMaterial("Default", "0 0 1 1");

		write_Xml(root, buf, size, name, collada, collada_collision);

		doc->SaveFile(name + ".xml");
		collada->save(name + ".dae");
		collada_collision->save(name + "_collision.dae");

		delete[] buf;
		delete doc;
		delete collada;
		delete collada_collision;
	}

	return;
}


/*-------------------------------------------------------------------------------\
|                             write_Xml						                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Xml(TiXmlElement *parent, const uint8_t *buf, size_t size, string filename, Collada* collada, Collada* collada_collision)
{
	bool XMLTEST_SoKeepSmaller = false;
	bool XMLTEST_UseHierarchy = true;


	big_endian = true;
	
	size_t offset = 0;
	size_t nbModels = val32(*(uint32_t*)buf);
	offset += sizeof(uint32_t);


	TiXmlElement* node;
	TiXmlElement* node_models = new TiXmlElement("Models");
	parent->LinkEndChild(node_models);

  

	
	size_t startoffsetModelHeader = offset;
	for (size_t i = 0; i < nbModels; i++)
	{
		size_t incUniqueID = 0;													//to avoid give the same name twice for bones and mesh, same if offsets couuld target the same structure.
		
		
		offset = startoffsetModelHeader + i * sizeof(SWR_MODELHeader);

		SWR_MODELHeader_Used* hdr = (SWR_MODELHeader_Used*)(buf + offset);
		hdr->offset_Section1 = val32(hdr->offset_Section1);
		hdr->offset_Section2 = val32(hdr->offset_Section2);
		size_t offset_NextHeader_Section1 = val32(hdr->offset_NextHeader_Section1);
		offset += sizeof(SWR_MODELHeader);


		TiXmlElement* node_model = new TiXmlElement("Model");
		node_models->LinkEndChild(node_model);





		//Section1 		
		std::vector<uint32_t> dataSection1;
		uint32_t* section1 = (uint32_t*)GetOffsetPtr(buf, hdr->offset_Section1, true);
		offset = hdr->offset_Section1;
		
		size_t nbSection1Elements = (hdr->offset_Section2 - hdr->offset_Section1) / sizeof(uint32_t);
		for (size_t j = 0; j < nbSection1Elements; j++)
		{
			dataSection1.push_back(section1[j]);
			offset += sizeof(uint32_t);
		}

		
		//Section2
		SWR_MODEL_Section2_Header* hdr_section2 = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, hdr->offset_Section2, true);
		offset = hdr->offset_Section2;
		offset += sizeof(SWR_MODEL_Section2_Header);
		size_t sizeSection2 = offset_NextHeader_Section1 - hdr->offset_Section2;
		
		if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_COMPRESSED, 4) == 0)		//Todo after : take care of "Comp" Compressed
		{
			::printf("Warning: Comp (for Compressed data) is not take care. did you use data from Pc version ? skipped.\n");
			notifyWarning();
			continue;
		}


		//todo take care of Comp (case N64)


		if ((memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MODEL, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_TRACK, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_POD, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_PART, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_SCENE, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MAlt, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_Pupp, 4) != 0)
			)
		{
			::printf("Warning: Unknowed Section2_header Signature :%c%c%c%c skipped.\n", hdr_section2->signature[0], hdr_section2->signature[1], hdr_section2->signature[2], hdr_section2->signature[3]);
			notifyWarning();
			continue;
		}


		

		if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MODEL, 4) == 0)
			node_model->SetAttribute("Type", "Model");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_TRACK, 4) == 0)
			node_model->SetAttribute("Type", "Track");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_POD, 4) == 0)
			node_model->SetAttribute("Type", "Pod");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_PART, 4) == 0)
			node_model->SetAttribute("Type", "Part");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_SCENE, 4) == 0)
			node_model->SetAttribute("Type", "Scene");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MAlt, 4) == 0)
			node_model->SetAttribute("Type", "Malt");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_Pupp, 4) == 0)
			node_model->SetAttribute("Type", "Pupp");
		


		std::vector<size_t> listPointer_AltN;
		std::vector<size_t> listPointer_Anim;

		TiXmlElement* node_listRefMalt_1 = new TiXmlElement("ListRefMalt_1");
		if(!XMLTEST_SoKeepSmaller)
			node_model->LinkEndChild(node_listRefMalt_1);

		uint32_t* section2_unknowParts = (uint32_t*)GetOffsetPtr(buf, offset, true);
		while (*section2_unknowParts != 0xFFFFFFFF)
		{
			if ((*section2_unknowParts != 0) && (val32(*section2_unknowParts) < sizeSection2) && (!checkDuplication_Malt_recursion(val32(*section2_unknowParts) + hdr->offset_Section2, listPointer_AltN, buf, size, hdr->offset_Section2)))
			{
				listPointer_AltN.push_back(val32(*section2_unknowParts) + hdr->offset_Section2);
				
				node = new TiXmlElement("Ref"); node->SetAttribute("offset", UnsignedToString(val32(*section2_unknowParts) + hdr->offset_Section2, true)); node_listRefMalt_1->LinkEndChild(node);
			}

			offset += sizeof(uint32_t);
			section2_unknowParts++;
		}
		offset += sizeof(uint32_t);

		


		bool endFound = false;
		while (!endFound)
		{

			SWR_MODEL_Section2_Header* hdr_section2_sub = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, offset, true);
			offset += sizeof(SWR_MODEL_Section2_Header);

			if ((memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_HEND, 4) != 0)
				)
			{
				::printf("Warning: Unknowed Section2_SubHeader Signature :%c%c%c%c skipped.\n", hdr_section2_sub->signature[0], hdr_section2_sub->signature[1], hdr_section2_sub->signature[2], hdr_section2_sub->signature[3]);
				notifyWarning();
				break;

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) == 0) {


				size_t startoffset_Anim = offset;
				uint32_t* listOffsetAnim = (uint32_t*)GetOffsetPtr(buf, startoffset_Anim, true);

				size_t inc_Anim = 0;
				while (listOffsetAnim[inc_Anim] != 0)
				{
					listOffsetAnim[inc_Anim] = val32(listOffsetAnim[inc_Anim]);

					if (!checkDuplication(listOffsetAnim[inc_Anim] + hdr->offset_Section2, listPointer_Anim))
						listPointer_Anim.push_back(listOffsetAnim[inc_Anim] + hdr->offset_Section2);

					offset += sizeof(uint32_t);
					inc_Anim++;

					if (listOffsetAnim[inc_Anim] == 0)
						break;
				}
				offset += sizeof(uint32_t);



			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) == 0) {

				size_t startoffset_Data = offset;

				size_t nbDatas = val32(*(uint32_t*)GetOffsetPtr(buf, startoffset_Data, true));
				offset += sizeof(uint32_t);

				SWR_Data* datas = (SWR_Data*)GetOffsetPtr(buf, offset, true);

				TiXmlElement* node_data = new TiXmlElement("Datas");
				if(!XMLTEST_SoKeepSmaller)
					node_model->LinkEndChild(node_data);

				for (size_t j = 0; j < nbDatas; j++)
				{
					TiXmlElement* node = new TiXmlElement("Data"); node->SetAttribute("unk0", UnsignedToString(datas[j].unk0, true)); node->SetAttribute("unk1", UnsignedToString(datas[j].unk1, true)); node->SetAttribute("unk2", UnsignedToString(datas[j].unk2, true)); node->SetAttribute("unk3", UnsignedToString(datas[j].unk3, true)); node_data->LinkEndChild(node);
					offset += 4 * sizeof(uint8_t);
				}

				//todo understand data is for what ? linked to another files ?

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) == 0) {


				TiXmlElement* node_listRefMalt_2 = new TiXmlElement("ListRefMalt_2");
				if (!XMLTEST_SoKeepSmaller)
					node_model->LinkEndChild(node_listRefMalt_2);


				size_t startoffset_AltN = offset;
				uint32_t* listOffsetAltN = (uint32_t*)GetOffsetPtr(buf, startoffset_AltN, true);

				size_t inc_AltN = 0;
				while (listOffsetAltN[inc_AltN] != 0)
				{
					listOffsetAltN[inc_AltN] = val32(listOffsetAltN[inc_AltN]);

					if (!checkDuplication_Malt_recursion(listOffsetAltN[inc_AltN] + hdr->offset_Section2, listPointer_AltN, buf, size, hdr->offset_Section2))
					{
						listPointer_AltN.push_back(listOffsetAltN[inc_AltN] + hdr->offset_Section2);

						node = new TiXmlElement("Ref"); node->SetAttribute("offset", UnsignedToString(listOffsetAltN[inc_AltN] + hdr->offset_Section2, true)); node_listRefMalt_2->LinkEndChild(node);
					}

					offset += sizeof(uint32_t);
					inc_AltN++;

					if (listOffsetAltN[inc_AltN] == 0)
						break;
				}
				offset += sizeof(uint32_t);

			}else {		// else "Hend" => normal exit.
				endFound = true;
			}
		}



		
		//saddely , it's could have a Malt just after Hend, never referenced (cf Model_115), So we test to add it.
		// hope the filter on first flags could avoid trouble.
		//Another problem is for model_001 by checking the first Malt on the last, previously offsets are child of the first. So, we have to reverse the check:
		std::vector<size_t> reverseCheck_listPointer_AltN;
		reverseCheck_listPointer_AltN.push_back(offset);					//offset of the first.

		size_t nbMalt_tmp = listPointer_AltN.size();
		for (size_t j = 0; j < nbMalt_tmp; j++)								//check all references, previously gived.
		{
			if (!checkDuplication_Malt_recursion(listPointer_AltN.at(j), reverseCheck_listPointer_AltN, buf, size, hdr->offset_Section2))
				reverseCheck_listPointer_AltN.push_back(listPointer_AltN.at(j));
		}
		listPointer_AltN = reverseCheck_listPointer_AltN;





		//-----------------------  Malt /AltN :

		string modelName = nameFromFilenameNoExtension(filename) + "_" + std::to_string(i);

		TiXmlElement* node_listMalt = new TiXmlElement("ListMalt_Node");
		if (!XMLTEST_SoKeepSmaller)
			node_model->LinkEndChild(node_listMalt);			//test Anima Todo unComment

		TiXmlElement* collada_ModelNode = collada->createNode(modelName);
		TiXmlElement* collada_collision_ModelNode = collada_collision->createNode(modelName);
		
		

		std::vector<size_t> listAltN_offset;								//both for link animation, with bone/node name (instead of offset.)
		std::vector<string> listAltN_BonesName;


		size_t nbAltN = listPointer_AltN.size();
		for (size_t inc_AltN = 0; inc_AltN< nbAltN; inc_AltN++)
		{	
			size_t startSectionAltN = listPointer_AltN.at(inc_AltN);
			offset = startSectionAltN;


			std::vector<size_t> listRecusiveAltN;
			listRecusiveAltN.push_back(offset);
			std::vector<TiXmlElement*> listRecusiveAltN_Xml;
			listRecusiveAltN_Xml.push_back(node_listMalt);

			std::vector<TiXmlElement*> listRecusiveAltN_ColladaParentNode;
			listRecusiveAltN_ColladaParentNode.push_back(collada_ModelNode);
			std::vector<TiXmlElement*> listRecusiveAltN_Collada_collisionParentNode;
			listRecusiveAltN_Collada_collisionParentNode.push_back(collada_collision_ModelNode);

			
			

			for (size_t j = 0; j<listRecusiveAltN.size(); j++)
			{
				offset = listRecusiveAltN.at(j);

				if (*(uint32_t*)GetOffsetPtr(buf, offset, true) == 0)
				{
					//Todo why offset = 0 ?
					continue;
				}
				string uniqueId_str = std::to_string((int)(incUniqueID++));
				string maltNodeName = modelName + "__" + uniqueId_str;

				TiXmlElement* collada_node = collada->createNode(maltNodeName, listRecusiveAltN_ColladaParentNode.at(j));
				TiXmlElement* collada_collision_node = collada_collision->createNode(maltNodeName, listRecusiveAltN_Collada_collisionParentNode.at(j));
				

				listAltN_offset.push_back(offset);
				listAltN_BonesName.push_back(maltNodeName);


				TiXmlElement* node_Malt = new TiXmlElement("Malt_Node");
				if (!XMLTEST_SoKeepSmaller)
				{
					node_Malt->SetAttribute("startOffset_id", UnsignedToString(offset, true));
					node_Malt->SetAttribute("uniqueName", maltNodeName);
				}
				if (!XMLTEST_SoKeepSmaller)
					listRecusiveAltN_Xml.at(j)->LinkEndChild(node_Malt);

				
				
				SWR_AltN_Header* hdr_AltN = (SWR_AltN_Header*)GetOffsetPtr(buf, offset, true);
				hdr_AltN->flags = val32(hdr_AltN->flags);
				hdr_AltN->nb_Childs = val32(hdr_AltN->nb_Childs);
				hdr_AltN->offset_Childs = val32(hdr_AltN->offset_Childs);
				offset += sizeof(SWR_AltN_Header);

				node = new TiXmlElement("flags"); node->SetAttribute("u32", UnsignedToString(hdr_AltN->flags, true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(hdr_AltN->unk0), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk1"); node->SetAttribute("u32", UnsignedToString(val32(hdr_AltN->unk1), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk2_a"); node->SetAttribute("u8", UnsignedToString(val32(hdr_AltN->unk2_a), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk2_b"); node->SetAttribute("u8", UnsignedToString(val32(hdr_AltN->unk2_b), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk3"); node->SetAttribute("u16", UnsignedToString(val32(hdr_AltN->unk3), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk4"); node->SetAttribute("u32", UnsignedToString(val32(hdr_AltN->unk4), true)); node_Malt->LinkEndChild(node);
				

				//todo: better understand flags to avoid the big switch, if it's possible.

				switch (hdr_AltN->flags)
				{
				case 0x3064:
				{
					size_t startOffset_Alt = offset;
					SWR_AltN_0x3064* section = (SWR_AltN_0x3064*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0x3064);

					TiXmlElement* node_section = new TiXmlElement("Section_3064_Mesh");
					if (!XMLTEST_SoKeepSmaller)
						node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("AABB"); 
					node->SetAttribute("minX", FloatToString(val_float(section->minX))); 
					node->SetAttribute("minY", FloatToString(val_float(section->minY)));
					node->SetAttribute("minZ", FloatToString(val_float(section->minZ)));
					node->SetAttribute("maxX", FloatToString(val_float(section->maxX)));
					node->SetAttribute("maxY", FloatToString(val_float(section->maxY)));
					node->SetAttribute("maxZ", FloatToString(val_float(section->maxZ)));
					if (!XMLTEST_SoKeepSmaller)
						node_section->LinkEndChild(node);
					node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section->unk0), true)); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk1"); node->SetAttribute("u32", UnsignedToString(val32(section->unk1), true)); node_section->LinkEndChild(node);

					
					
					



					size_t startoffset_Section3_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
					offset = startoffset_Section3_listOffset;

					uint32_t* listOffsetAltN_Section3 = (uint32_t*)GetOffsetPtr(buf, offset, true);

					TiXmlElement* node_listSection3 = new TiXmlElement("ListSection3_SubMesh");
					node_section->LinkEndChild(node_listSection3);

					for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
					{
						size_t startoffset_section3 = val32(listOffsetAltN_Section3[k]) + hdr->offset_Section2;
						offset = startoffset_section3;

						SWR_MODEL_Section3* section3 = (SWR_MODEL_Section3*)GetOffsetPtr(buf, offset, true);
						offset += sizeof(SWR_MODEL_Section3);
						section3->offset_section4 = val32(section3->offset_section4);
						section3->offset_section7 = val32(section3->offset_section7);
						section3->nbElementV90 = val16(section3->nbElementV90);
						section3->typeMode = val16(section3->typeMode);
						section3->nbElementV44 = val16(section3->nbElementV44);
						section3->nbElementV52 = val16(section3->nbElementV52);
						section3->offset_V90 = val32(section3->offset_V90);
						section3->offset_unk40 = val32(section3->offset_unk40);
						section3->offset_unk44 = val32(section3->offset_unk44);
						section3->offset_unk48 = val32(section3->offset_unk48);
						section3->offset_unk52 = val32(section3->offset_unk52);


						TiXmlElement* node_section3 = new TiXmlElement("Section3_SubMesh");
						node_section3->SetAttribute("startOffset", UnsignedToString(startoffset_section3, true));			//debug, todo remove
						node_listSection3->LinkEndChild(node_section3);

						node = new TiXmlElement("AABB");
						node->SetAttribute("minX", FloatToString(val_float(section3->minX)));
						node->SetAttribute("minY", FloatToString(val_float(section3->minY)));
						node->SetAttribute("minZ", FloatToString(val_float(section3->minZ)));
						node->SetAttribute("maxX", FloatToString(val_float(section3->maxX)));
						node->SetAttribute("maxY", FloatToString(val_float(section3->maxY)));
						node->SetAttribute("maxZ", FloatToString(val_float(section3->maxZ)));
						node_section3->LinkEndChild(node);

						node = new TiXmlElement("typeMode"); node->SetAttribute("u16", UnsignedToString(section3->typeMode, true)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("unk60"); node->SetAttribute("u16", UnsignedToString(val16(section3->unk60), true)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("unk62"); node->SetAttribute("u16", UnsignedToString(val16(section3->unk62), true)); node_section3->LinkEndChild(node);


						//todo removes that after debug be sure about While on Section44
						node = new TiXmlElement("nbElementV90"); node->SetAttribute("u16", UnsignedToString(section3->nbElementV90, false)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("nbElementV44"); node->SetAttribute("u16", UnsignedToString(section3->nbElementV44, false)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("nbElementV52"); node->SetAttribute("u16", UnsignedToString(section3->nbElementV52, false)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("offset_unk40"); node->SetAttribute("u32", UnsignedToString(val32(section3->offset_unk40), true)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("offset_unk44"); node->SetAttribute("u32", UnsignedToString(val32(section3->offset_unk44), true)); node_section3->LinkEndChild(node);
						
						
						float s3MinX = val_float(section3->minX);
						float s3MinY = val_float(section3->minY);
						float s3MinZ = val_float(section3->minZ);
						float s3MaxX = val_float(section3->maxX);
						float s3MaxY = val_float(section3->maxY);
						float s3MaxZ = val_float(section3->maxZ);



						string materialName = "Default";
						std::vector<EMDVertex> listVertex;
						std::vector<EMDTriangles> listTriangles;
						std::vector<EMDVertex> listVertex_collision;
						std::vector<EMDTriangles> listTriangles_collision;





						
						if (section3->offset_V90)									//it's a list of numberElements for next parts.
						{
							TiXmlElement* node_section90 = new TiXmlElement("Section90_ListGroup");
							if (!XMLTEST_SoKeepSmaller)
								node_section3->LinkEndChild(node_section90);

							size_t startoffset_sectionV90 = section3->offset_V90 + hdr->offset_Section2;
							offset = startoffset_sectionV90;

							uint32_t* listValues = (uint32_t*)GetOffsetPtr(buf, offset, true);

							size_t numberTotal = 0;
							size_t numberTotal_b = 0;
							size_t nbVertexTmp = 0;
							for (size_t m = 0; m < section3->nbElementV90; m++)
							{
								nbVertexTmp = val32(listValues[m]);
								numberTotal += nbVertexTmp;
								numberTotal_b += nbVertexTmp;
								if((nbVertexTmp > 32) && (section3->nbElementV52 != 0))
									//numberTotal_b += 2 * (nbVertexTmp / 32);
									numberTotal_b += 2 * (size_t)round(nbVertexTmp / 32.0);						//round it's a no-sense, but it's the case of Model 177: 364 vertex, and only one group with 342. adding +2 each 32, give 362. 342 / 32 = 10.6875. and it's can't be 16 instead 32, because lots of group under 32, and up to 16 is not concerned. or may be, 16  begin after first 32. ... but strange. Todo just add 2 for case in the last.

								node = new TiXmlElement("Group"); 
								node->SetAttribute("index", m);
								node->SetAttribute("nbElements", UnsignedToString(val32(listValues[m]), false)); 
								node->SetAttribute("total", UnsignedToString(numberTotal, false));
								if(section3->nbElementV52 != 0)
									node->SetAttribute("total_32", UnsignedToString(numberTotal_b, false));
								node_section90->LinkEndChild(node);
								offset += sizeof(uint32_t);
							}

							if( ((section3->nbElementV52!=0) && (numberTotal_b != section3->nbElementV52)) || ((section3->nbElementV52 == 0) && (section3->nbElementV44 != 0) && (numberTotal_b != section3->nbElementV44)) )
							{
								printf((string("Error of hyp (in case section3->offset_V90!=0, typeMode %i): the ")+ ((section3->nbElementV52!=0) ? "section3->nbElementV52" : "section3->nbElementV44") +" != sum of all group (%i != %i).\n").c_str(), section3->typeMode, (section3->nbElementV52!=0) ? section3->nbElementV52 : section3->nbElementV44, numberTotal_b);
								notifyError();
							}
						}
						



						string submeshName = maltNodeName + "_submesh_" + std::to_string(k);


						//--------------------------------  Visual Geometry
						if (section3->offset_unk52)
						{
							size_t startoffset_section52 = section3->offset_unk52 + hdr->offset_Section2;
							offset = startoffset_section52;

							TiXmlElement* node_listSection52 = new TiXmlElement("ListSection52_ListVertex");
							if (!XMLTEST_SoKeepSmaller)
								node_listSection52->SetAttribute("uniqueName", submeshName);
							node_section3->LinkEndChild(node_listSection52);



							for (size_t m = 0; m < section3->nbElementV52; m++)
							{
								SWR_MODEL_Section52* section52 = (SWR_MODEL_Section52*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section52);

								node_listSection52->LinkEndChild(new TiXmlComment( string("index: " + std::to_string(m)).c_str() ));

								TiXmlElement* node_section52 = new TiXmlElement("Vertex");
								node_listSection52->LinkEndChild(node_section52);
								node = new TiXmlElement("Position");
								node_section52->LinkEndChild(node);
								node->SetAttribute("x", FloatToString((float)(int16_t)val16(section52->posX)));
								node->SetAttribute("y", FloatToString((float)(int16_t)val16(section52->posY)));
								node->SetAttribute("z", FloatToString((float)(int16_t)val16(section52->posZ)));
								node = new TiXmlElement("Uv");
								node_section52->LinkEndChild(node);
								//FIXME: Might be `uv / 0xFFFF * 16.0f` instead
								float u = (int16_t)val16(section52->uvU) / (float)0xFFF;
								float v = (int16_t)val16(section52->uvV) / (float)0xFFF;
								node->SetAttribute("u", FloatToString(u));
								node->SetAttribute("v", FloatToString(v));
								node = new TiXmlElement("Color");
								node_section52->LinkEndChild(node);
								node->SetAttribute("r", FloatToString((float)section52->colorR / 255.0f));
								node->SetAttribute("g", FloatToString((float)section52->colorG / 255.0f));
								node->SetAttribute("b", FloatToString((float)section52->colorB / 255.0f));
								node->SetAttribute("a", FloatToString((float)section52->colorA / 255.0f));

								
								EMDVertex vertex;
								vertex.flags = EMD_VTX_FLAG_POS | EMD_VTX_FLAG_TEX | EMD_VTX_FLAG_COLOR;
								vertex.pos_x = (float)(int16_t)val16(section52->posX);
								vertex.pos_y = (float)(int16_t)val16(section52->posY);
								vertex.pos_z = (float)(int16_t)val16(section52->posZ);
								vertex.text_u = u;
								vertex.text_v = v;
								//in reality ColorRGB give the look like of normal directions, and ColorA look like specular.
								vertex.color = (section52->colorR << 24) + (section52->colorG << 16) + (section52->colorB << 8) + section52->colorA;
								listVertex.push_back(vertex);
							}



							size_t incVertex = 0;
							size_t nbVertex = 0;

							uint32_t* listNbElementsByGroup = (section3->offset_V90) ? (uint32_t*)GetOffsetPtr(buf, section3->offset_V90 + hdr->offset_Section2, true) : 0;
							size_t nbGroup = section3->nbElementV90;

							if (!listNbElementsByGroup)				//some check
							{
								if ((section3->nbElementV52 / nbGroup) * nbGroup != section3->nbElementV52)
								{
									printf("Warning of hyp (in case section3->offset_V90==0): the section3->nbElementV52 / nbGroup (%i/%i) is not a integer. using nbGroup = 1\n", section3->nbElementV52, nbGroup);
									notifyWarning();
									nbGroup = 1;
								}

								if ((section3->typeMode != 5) && ((section3->nbElementV52 / nbGroup) % section3->typeMode != 0))
								{
									printf("Warning of hyp (in case section3->offset_V90==0, typeMode %i): the section3->nbElementV52 / nbGroup (%i / %i = %i) is not a modulo of %i. using nbGroup = 1\n", section3->typeMode, section3->nbElementV52, nbGroup, section3->nbElementV52 / nbGroup, section3->typeMode);
									notifyWarning();
									nbGroup = 1;
								}
							}

							for (size_t m = 0; m < nbGroup; m++)
							{
								nbVertex = (listNbElementsByGroup) ? val32(listNbElementsByGroup[m]) : (section3->nbElementV52 / nbGroup);



								if ((section3->typeMode != 5) && ((nbVertex) % section3->typeMode != 0))
								{
									printf((string("Warning of hyp (in case  section3->offset_V90") + ((listNbElementsByGroup) ? "!=" : "==") + "0, typeMode %i): the nbVertex = %i is not a modulo of %i. \n").c_str(), section3->typeMode, nbVertex, section3->typeMode);
									notifyWarning();
								}


							
								EMDTriangles emdTriangle;

								if (section3->typeMode == 3)			//simple triangles 
								{
									for (size_t n = 0; n + 2 < nbVertex; n += 3)
									{
										emdTriangle.faces.push_back(incVertex + n);
										emdTriangle.faces.push_back(incVertex + n + 1);
										emdTriangle.faces.push_back(incVertex + n + 2);
									}
								}else if (section3->typeMode == 4) {    //simple quads

									for (size_t n = 0; n + 3 < nbVertex; n += 4)					//test case diagonale come from 0 to 2 (1 and 3 are neighbour of 0) => diagonal is good.
									{
										//triangle A
										emdTriangle.faces.push_back(incVertex + n);
										emdTriangle.faces.push_back(incVertex + n + 1);
										emdTriangle.faces.push_back(incVertex + n + 2);

										//triangle B
										emdTriangle.faces.push_back(incVertex + n);
										emdTriangle.faces.push_back(incVertex + n + 2);
										emdTriangle.faces.push_back(incVertex + n + 3);
									}

								}else {									//case 5 : triangle strip  https://en.wikipedia.org/wiki/Triangle_strip


									if(nbVertex > 32)					//I notify some artefacts on stage meshes, and also sometime, the sum of nbvertex into V90 list is not equal with nbSection52.
										//nbVertex += 2 * (nbVertex / 32);	//apparently it's about passing each 32 vertex. 
										nbVertex += 2 * (size_t)round(nbVertex / 32.0);	//apparently it's about passing each 32 vertex. //round it's a no-sense, but it's the case of Model 177: 364 vertex, and only one group with 342. adding +2 each 32, give 362. 342 / 32 = 10.6875. and it's can't be 16 instead 32, because lots of group under 32, and up to 16 is not concerned. or may be, 16  begin after first 32. ... but strange.

									for (size_t n = 0; n + 2 < nbVertex; n++)
									{
										if (n % 2 == 0)
										{
											emdTriangle.faces.push_back(incVertex + n);
											emdTriangle.faces.push_back(incVertex + n + 1);
											emdTriangle.faces.push_back(incVertex + n + 2);
										}else {
											emdTriangle.faces.push_back(incVertex + n);
											emdTriangle.faces.push_back(incVertex + n + 2);
											emdTriangle.faces.push_back(incVertex + n + 1);
										}
									}
								}

								if (emdTriangle.faces.size() == 0)
								{
									printf("Error number of face is 0. skipped\n");
									notifyError();
								}else {
									listTriangles.push_back(emdTriangle);
								}

								incVertex += nbVertex;
							}
						}


						//--------------------------------  Collision Geometry
						if (section3->offset_unk44)
						{
							size_t startoffset_section44 = section3->offset_unk44 + hdr->offset_Section2;
							offset = startoffset_section44;

							TiXmlElement* node_section44 = new TiXmlElement("Section44_Collision_Geometry");
							node_section44->SetAttribute("startOffset", UnsignedToString(offset, true));
							if (!XMLTEST_SoKeepSmaller)
								node_section3->LinkEndChild(node_section44);


							size_t incVertex = 0;
							size_t nbVertex = 0;

							uint32_t* listNbElementsByGroup = (section3->offset_V90) ? (uint32_t*)GetOffsetPtr(buf, section3->offset_V90 + hdr->offset_Section2, true) : 0;
							size_t nbGroup = section3->nbElementV90;

							if (!listNbElementsByGroup)				//some check
							{
								if ((section3->nbElementV44 / nbGroup) * nbGroup != section3->nbElementV44)
								{
									printf("Error of hyp (in case Sect44, section3->offset_V90==0): the section3->nbElementV44 / nbGroup (%i/%i) is not a integer. \n", section3->nbElementV44, nbGroup);
									notifyError();
								}

								if ((section3->typeMode != 5) && ((section3->nbElementV44 / nbGroup) % section3->typeMode != 0))
								{
									printf("Warning of hyp (in case Sect44,section3->offset_V90==0, typeMode %i): the section3->nbElementV44 / nbGroup (%i / %i = %i) is not a modulo of %i. using nbGroup=1.\n", section3->typeMode, section3->nbElementV44, nbGroup, section3->nbElementV44 / nbGroup, section3->typeMode);
									notifyWarning();
									nbGroup = 1;
								}
							}


							uint16_t* values_u16 = (uint16_t*)GetOffsetPtr(buf, offset, true);
							size_t valueIndex = 0;

							for (size_t m = 0; m < nbGroup; m++)
							{
								nbVertex = (listNbElementsByGroup) ? val32(listNbElementsByGroup[m]) : (section3->nbElementV44 / nbGroup);

								//if (offset == 0x1f4)
								//	nbVertex = nbVertex * 2;					//test Todo remove.

								float posX, posY, posZ;
								for (size_t n = 0; n < nbVertex; n++)
								{
									posX = (float)(int16_t)val16(values_u16[valueIndex++]);
									posY = (float)(int16_t)val16(values_u16[valueIndex++]);
									posZ = (float)(int16_t)val16(values_u16[valueIndex++]);

									EMDVertex vertex;
									vertex.flags = EMD_VTX_FLAG_POS;
									vertex.pos_x = posX;
									vertex.pos_y = posY;
									vertex.pos_z = posZ;
									listVertex_collision.push_back(vertex);

									node = new TiXmlElement("Vertex");
									node->SetDoubleAttribute("posX", posX);
									node->SetDoubleAttribute("posY", posY);
									node->SetDoubleAttribute("posZ", posZ);
									node_section44->LinkEndChild(node);
								}

								
								EMDTriangles emdTriangle;

								if (section3->typeMode == 3)			//simple triangles 
								{
									for (size_t n = 0; n + 2 < nbVertex; n += 3)
									{
										emdTriangle.faces.push_back(incVertex + n);
										emdTriangle.faces.push_back(incVertex + n + 1);
										emdTriangle.faces.push_back(incVertex + n + 2);
									}

								}
								else if (section3->typeMode == 4) {    //simple quads

									for (size_t n = 0; n + 3 < nbVertex; n += 4)					//test case diagonale come from 0 to 2 (1 and 3 are neighbour of 0) => diagonal is good.
									{
										//triangle A
										emdTriangle.faces.push_back(incVertex + n);
										emdTriangle.faces.push_back(incVertex + n + 1);
										emdTriangle.faces.push_back(incVertex + n + 2);

										//triangle B
										emdTriangle.faces.push_back(incVertex + n);
										emdTriangle.faces.push_back(incVertex + n + 2);
										emdTriangle.faces.push_back(incVertex + n + 3);
									}

								}else {									//case 5 : triangle strip  https://en.wikipedia.org/wiki/Triangle_strip


									for (size_t n = 0; n + 2 < nbVertex; n++)
									{
										if (n % 2 == 0)
										{
											emdTriangle.faces.push_back(incVertex + n);
											emdTriangle.faces.push_back(incVertex + n + 1);
											emdTriangle.faces.push_back(incVertex + n + 2);
										}
										else {
											emdTriangle.faces.push_back(incVertex + n);
											emdTriangle.faces.push_back(incVertex + n + 2);
											emdTriangle.faces.push_back(incVertex + n + 1);
										}
									}
								}

								if (emdTriangle.faces.size() == 0)
								{
									printf("Error number of face is 0. skipped\n");
									notifyError();
								}else {
									listTriangles_collision.push_back(emdTriangle);
								}

								incVertex += nbVertex;
							}
						}


						size_t incSection48 = 0;
						if (section3->offset_unk48)
						{
							size_t startoffset_section48 = section3->offset_unk48 + hdr->offset_Section2;
							offset = startoffset_section48;

							SWR_MODEL_Section48* section48 = (SWR_MODEL_Section48*)GetOffsetPtr(buf, offset, true);

							TiXmlElement* node_section48 = new TiXmlElement("Section48");
							node_section48->SetAttribute("startOffset", UnsignedToString(startoffset_section48, true));
							if (!XMLTEST_SoKeepSmaller)
								node_section3->LinkEndChild(node_section48);

							incSection48 = 0;
							while (section48->unk0 != 0xDF)
							{
								node = new TiXmlElement("Value");
								node->SetAttribute("unk0", UnsignedToString(section48->unk0, true));
								node->SetAttribute("unk1", UnsignedToString(section48->unk1, true));
								node->SetAttribute("unk2", UnsignedToString(section48->unk2, true));
								node->SetAttribute("unk3", UnsignedToString(section48->unk3, true));
								node->SetAttribute("unk4", UnsignedToString(val32(section48->unk4), true));
								node_section48->LinkEndChild(node);

								offset += sizeof(SWR_MODEL_Section48);
								section48++;
								incSection48++;
							}
							offset += 2 * sizeof(uint32_t);

							node_section48->SetAttribute("debugNbElements", incSection48);
						}


						if (section3->offset_unk40)
						{
							size_t startoffset_section40 = section3->offset_unk40 + hdr->offset_Section2;
							offset = startoffset_section40;

							SWR_MODEL_Section40* section40 = (SWR_MODEL_Section40*)GetOffsetPtr(buf, offset, true);
							offset += sizeof(SWR_MODEL_Section40);

							TiXmlElement* node_section40 = new TiXmlElement("Section40");
							if (!XMLTEST_SoKeepSmaller)
								node_section3->LinkEndChild(node_section40);

							node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section40->unk0), true)); node_section40->LinkEndChild(node);
							node = new TiXmlElement("unk1"); node->SetAttribute("u16", UnsignedToString(val16(section40->unk1), true)); node_section40->LinkEndChild(node);
							node = new TiXmlElement("unk2"); node->SetAttribute("u16", UnsignedToString(val16(section40->unk2), true)); node_section40->LinkEndChild(node);
							node = new TiXmlElement("unk3"); node->SetAttribute("u32", UnsignedToString(val32(section40->unk3), true)); node_section40->LinkEndChild(node);
						}





						if (section3->offset_section4)
						{

							size_t startoffset_section4 = section3->offset_section4 + hdr->offset_Section2;
							offset = startoffset_section4;

							SWR_MODEL_Section4* section4 = (SWR_MODEL_Section4*)GetOffsetPtr(buf, offset, true);
							offset += sizeof(SWR_MODEL_Section4);
							section4->offset_section5 = val32(section4->offset_section5);
							section4->offset_section6 = val32(section4->offset_section6);


							TiXmlElement* node_section4 = new TiXmlElement("Section4");
							if (!XMLTEST_SoKeepSmaller)
								node_section3->LinkEndChild(node_section4);

							node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section4->unk0), true)); node_section4->LinkEndChild(node);
							node = new TiXmlElement("unk4"); node->SetAttribute("u32", UnsignedToString(val32(section4->unk4), true)); node_section4->LinkEndChild(node);
							node = new TiXmlElement("unk6"); node->SetAttribute("u32", UnsignedToString(val32(section4->unk6), true)); node_section4->LinkEndChild(node);


							// material or texture.
							if (section4->offset_section5)
							{
								size_t startoffset_section5 = section4->offset_section5 + hdr->offset_Section2;
								offset = startoffset_section5;

								SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section5);


								TiXmlElement* node_section5 = new TiXmlElement("Section5");
								node_section4->LinkEndChild(node_section5);

								node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk0), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk4"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk4), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk6"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk6), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk8_0"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[0]), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk8_1"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[1]), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk12"); node->SetAttribute("u8", UnsignedToString(section5->unk12, true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk13"); node->SetAttribute("u8", UnsignedToString(section5->unk13, true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk14_0"); node->SetAttribute("u8", UnsignedToString(section5->unk14[0], true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk14_1"); node->SetAttribute("u8", UnsignedToString(section5->unk14[1], true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk16"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk16), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk18"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk18), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk20"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk20), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk22"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk22), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk24"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk24), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk26"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk26), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk48"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk48), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("textureMask"); node->SetAttribute("u8", UnsignedToString((val32(section5->textureMaskAndIndex) >> 24) & 0xFF, true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("textureIndex"); node->SetAttribute("u24", UnsignedToString(val32(section5->textureMaskAndIndex) & 0x00FFFFFF, true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk60"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk60), true)); node_section5->LinkEndChild(node);


								materialName = "MatTexture_" + UnsignedToString(val32(section5->textureMaskAndIndex) & 0x00FFFFFF, true);
								collada->addTextureMaterial(materialName, "texture_"+ UnsignedToString(val32(section5->textureMaskAndIndex) & 0x00FFFFFF, false) +".png");
								collada_collision->addTextureMaterial(materialName, "texture_" + UnsignedToString(val32(section5->textureMaskAndIndex) & 0x00FFFFFF, false) + ".png");

								/*
								if (emdSubMesh)
								{
									
								}else {
									printf("Warning/Error: there is a Section5 with a effective textureIndex, but there is no Visual Vertex (Section52). strange ...\n");
									notifyError();
								}
								*/

								

								for (size_t m = 0; m < 5; m++)
								{
									if (!section5->offset_Section5_b[m])
										continue;

									size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
									offset = startoffset_section5_b;

									SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

									offset += sizeof(SWR_MODEL_Section5_b);

									TiXmlElement* node_section5b = new TiXmlElement("Section5b");
									node_section5->LinkEndChild(node_section5b);

									node = new TiXmlElement("unk0"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk0), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk2"); node->SetAttribute("u8", UnsignedToString(section5_b->unk2, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk3"); node->SetAttribute("u8", UnsignedToString(section5_b->unk3, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk4"); node->SetAttribute("u8", UnsignedToString(section5_b->unk4, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk5"); node->SetAttribute("u8", UnsignedToString(section5_b->unk5, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk6_a"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_a), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk6_b"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_b), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk8"); node->SetAttribute("u32", UnsignedToString(val32(section5_b->unk8), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk12"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk12), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk14"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk14), true)); node_section5b->LinkEndChild(node);
								}

							}


							if (section4->offset_section6)
							{
								size_t startoffset_section6 = section4->offset_section6 + hdr->offset_Section2;
								offset = startoffset_section6;

								SWR_MODEL_Section6* section6 = (SWR_MODEL_Section6*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section6);

								TiXmlElement* node_section6 = new TiXmlElement("Section6");
								if (!XMLTEST_SoKeepSmaller)
									node_section4->LinkEndChild(node_section6);

								node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk0), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk4"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk4), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk6_0"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk6[0]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk6_1"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk6[1]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk14_0"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk14[0]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk14_1"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk14[1]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk22_0"); node->SetAttribute("u8", UnsignedToString(section6->unk22[0], true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk22_1"); node->SetAttribute("u8", UnsignedToString(section6->unk22[1], true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk24"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk24), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk28"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk28), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk32"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk32), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk34"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk34), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk36"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk36), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk38"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk38), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk40"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk40), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk44"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk44), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk48"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk48), true)); node_section6->LinkEndChild(node);
							}

							//reinverse for another time.
							section4->offset_section5 = val32(section4->offset_section5);
							section4->offset_section6 = val32(section4->offset_section6);
						}



						if (section3->offset_section7)
						{
							size_t startoffset_section7 = section3->offset_section7 + hdr->offset_Section2;
							offset = startoffset_section7;

							SWR_MODEL_Section7* section7 = (SWR_MODEL_Section7*)GetOffsetPtr(buf, offset, true);
							offset += sizeof(SWR_MODEL_Section7);

							
							TiXmlElement* node_section7 = new TiXmlElement("Section7");
							if (!XMLTEST_SoKeepSmaller)
								node_section3->LinkEndChild(node_section7);

							node = new TiXmlElement("unk0"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk0), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_0"); node->SetAttribute("u8", UnsignedToString(section7->unk2[0], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_1"); node->SetAttribute("u8", UnsignedToString(section7->unk2[1], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_2"); node->SetAttribute("u8", UnsignedToString(section7->unk2[2], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_3"); node->SetAttribute("u8", UnsignedToString(section7->unk2[3], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk6"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk6), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk8"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk8), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk10"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk10), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_0"); node->SetAttribute("u8", UnsignedToString(section7->unk12[0], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_1"); node->SetAttribute("u8", UnsignedToString(section7->unk12[1], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_2"); node->SetAttribute("u8", UnsignedToString(section7->unk12[2], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_3"); node->SetAttribute("u8", UnsignedToString(section7->unk12[3], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_4"); node->SetAttribute("u8", UnsignedToString(section7->unk12[4], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_5"); node->SetAttribute("u8", UnsignedToString(section7->unk12[5], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_6"); node->SetAttribute("u8", UnsignedToString(section7->unk12[6], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_7"); node->SetAttribute("u8", UnsignedToString(section7->unk12[7], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk20"); node->SetAttribute("float", FloatToString(val_float(section7->unk20))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk24"); node->SetAttribute("float", FloatToString(val_float(section7->unk24))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk28"); node->SetAttribute("float", FloatToString(val_float(section7->unk28))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk32"); node->SetAttribute("float", FloatToString(val_float(section7->unk32))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk36"); node->SetAttribute("float", FloatToString(val_float(section7->unk36))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk40"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk40), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk44"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk44), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk48"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk48), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk50"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk50), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk52"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk52), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk56"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk56), true)); node_section7->LinkEndChild(node);


							if ((val32(section7->unk52) & 0xFFFF) == 0x6C3C)			//apparently, it's work on all files.
							{
								size_t startoffset_section7b = offset;

								SWR_MODEL_Section7_b* section7_b = (SWR_MODEL_Section7_b*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section7_b);

								TiXmlElement* node_section7b = new TiXmlElement("Section7b");
								node_section7->LinkEndChild(node_section7b);

								node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section7_b->unk0), true)); node_section7b->LinkEndChild(node);
								node = new TiXmlElement("unk1"); node->SetAttribute("u32", UnsignedToString(val32(section7_b->unk1), true)); node_section7b->LinkEndChild(node);
								node = new TiXmlElement("unk2"); node->SetAttribute("u32", UnsignedToString(val32(section7_b->unk2), true)); node_section7b->LinkEndChild(node);
							}


							TiXmlElement* node_Listsection8 = new TiXmlElement("ListSection8");
							node_section7->LinkEndChild(node_Listsection8);

							std::vector<size_t> listOffsetSection8;
							listOffsetSection8.push_back(val32(section7->offset_section8));

							for (size_t m = 0; m < listOffsetSection8.size(); m++)
							{
								if (!listOffsetSection8.at(m))
									continue;

								size_t startoffset_section8 = listOffsetSection8.at(m) + hdr->offset_Section2;
								offset = startoffset_section8;

								SWR_MODEL_Section8* section8 = (SWR_MODEL_Section8*)GetOffsetPtr(buf, offset, true);
								
								TiXmlElement* node_section8 = new TiXmlElement("Section8");
								node_section8->SetAttribute("startOffset", UnsignedToString(offset, true));
								node_Listsection8->LinkEndChild(node_section8);

								offset += sizeof(SWR_MODEL_Section8);

								node = new TiXmlElement("unk0_0"); node->SetAttribute("float", FloatToString(val_float(section8->unk0[0]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk0_1"); node->SetAttribute("float", FloatToString(val_float(section8->unk0[1]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk0_2"); node->SetAttribute("float", FloatToString(val_float(section8->unk0[2]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk12_0"); node->SetAttribute("float", FloatToString(val_float(section8->unk12[0]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk12_1"); node->SetAttribute("float", FloatToString(val_float(section8->unk12[1]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk12_2"); node->SetAttribute("float", FloatToString(val_float(section8->unk12[2]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk24"); node->SetAttribute("float", FloatToString(val_float(section8->unk24))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk28"); node->SetAttribute("float", FloatToString(val_float(section8->unk28))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("offset_AltN"); node->SetAttribute("u32", UnsignedToString(val32(section8->offset_AltN + hdr->offset_Section2), true)); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk36"); node->SetAttribute("u16", UnsignedToString(val16(section8->unk36), true)); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk38"); node->SetAttribute("u16", UnsignedToString(val16(section8->unk38), true)); node_section8->LinkEndChild(node);
								node = new TiXmlElement("offset_nextSection8"); node->SetAttribute("u32", UnsignedToString(val32(section8->offset_next_section8), true)); node_section8->LinkEndChild(node);

								listOffsetSection8.push_back(val32(section8->offset_next_section8));
							}
						}


						


						if ((listVertex.size())&& (listTriangles.size()))
						{
							collada->addGeometry(submeshName, listVertex, listTriangles, materialName);
							collada->makeInstanceGeometryOnNode(collada_node, submeshName, materialName, materialName != "Default");
						}

						if ((listVertex_collision.size()) && (listTriangles_collision.size()))
						{
							collada_collision->addGeometry(submeshName, listVertex_collision, listTriangles_collision, materialName);
							collada_collision->makeInstanceGeometryOnNode(collada_collision_node, submeshName, materialName, materialName != "Default");
						}

						
						





						//test of case possibles, to create warning			//todo remove
						node_section3->SetAttribute("Cases", "Test_M" + std::to_string(section3->typeMode) + "_" +
							((section3->offset_V90) ? "v90_" : "") +
							((section3->nbElementV90) ? "nb90_" : "") +
							((section3->offset_unk44) ? "v44_" : "") +
							((section3->nbElementV44) ? "nb44_" : "") +
							((section3->offset_unk52) ? "v52_" : "") +
							((section3->nbElementV52) ? "nb52_" : "") +
							((section3->offset_unk48) ? "v48_" : "") +
							((section3->offset_unk40) ? "v40_" : "") +
							(((!section3->offset_unk44) && (((section3->typeMode == 3) || (section3->typeMode == 4)) && ((section3->nbElementV52 % section3->typeMode) == 0))) ? "Nb52Mod_" : "")
						);



						//reinverse for a another time
						section3->offset_section4 = val32(section3->offset_section4);
						section3->offset_section7 = val32(section3->offset_section7);
						section3->nbElementV90 = val16(section3->nbElementV90);
						section3->typeMode = val16(section3->typeMode);
						section3->nbElementV44 = val16(section3->nbElementV44);
						section3->nbElementV52 = val16(section3->nbElementV52);
						section3->offset_V90 = val32(section3->offset_V90);
						section3->offset_unk40 = val32(section3->offset_unk40);
						section3->offset_unk44 = val32(section3->offset_unk44);
						section3->offset_unk48 = val32(section3->offset_unk48);
						section3->offset_unk52 = val32(section3->offset_unk52);
					}

				}
				break;

				case 0x5065:
				{
					SWR_AltN_0x5065* section = (SWR_AltN_0x5065*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0x5065);

					TiXmlElement* node_section = new TiXmlElement("Section_5065");
					if (!XMLTEST_SoKeepSmaller)
						node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("unk_0"); node->SetAttribute("u32", UnsignedToString(val32(section->unk_0), true)); node_section->LinkEndChild(node);
				}
				break;


				case 0x5066:
				{
					SWR_AltN_0x5066* section = (SWR_AltN_0x5066*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0x5066);

					TiXmlElement* node_section = new TiXmlElement("Section_5066");
					if (!XMLTEST_SoKeepSmaller)
						node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("distLod_0"); node->SetAttribute("float", FloatToString(val_float(section->distLod_0))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_1"); node->SetAttribute("float", FloatToString(val_float(section->distLod_1))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_2"); node->SetAttribute("float", FloatToString(val_float(section->distLod_2))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_3"); node->SetAttribute("float", FloatToString(val_float(section->distLod_3))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_4"); node->SetAttribute("float", FloatToString(val_float(section->distLod_4))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_5"); node->SetAttribute("float", FloatToString(val_float(section->distLod_5))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_6"); node->SetAttribute("float", FloatToString(val_float(section->distLod_6))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_7"); node->SetAttribute("float", FloatToString(val_float(section->distLod_7))); node_section->LinkEndChild(node);

					node = new TiXmlElement("unk_8"); node->SetAttribute("float", FloatToString(val_float(section->unk_8))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_9"); node->SetAttribute("float", FloatToString(val_float(section->unk_9))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_10"); node->SetAttribute("float", FloatToString(val_float(section->unk_10))); node_section->LinkEndChild(node);
				}
				break;


				case 0xD064:
				{
					SWR_AltN_0xD064* section = (SWR_AltN_0xD064*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0xD064);

					TiXmlElement* node_section = new TiXmlElement("Section_D064_Transform");
					if (!XMLTEST_SoKeepSmaller)
						node_Malt->LinkEndChild(node_section);
					TiXmlElement* node_matrix = new TiXmlElement("Matrix3x3");
					node_section->LinkEndChild(node_matrix);

					node = new TiXmlElement("m0");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m00)));
					node->SetAttribute("c1", FloatToString(val_float(section->m01)));
					node->SetAttribute("c2", FloatToString(val_float(section->m02)));

					node = new TiXmlElement("m1");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m10)));
					node->SetAttribute("c1", FloatToString(val_float(section->m11)));
					node->SetAttribute("c2", FloatToString(val_float(section->m12)));

					node = new TiXmlElement("m2");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m20)));
					node->SetAttribute("c1", FloatToString(val_float(section->m21)));
					node->SetAttribute("c2", FloatToString(val_float(section->m22)));


					node = new TiXmlElement("Position");
					node_section->LinkEndChild(node);
					node->SetAttribute("x", FloatToString(val_float(section->posX)));
					node->SetAttribute("y", FloatToString(val_float(section->posY)));
					node->SetAttribute("z", FloatToString(val_float(section->posZ)));


					//todo simplify this.
					float rotAxisX = 0;
					float rotAxisY = 0;
					float rotAxisZ = 0;
					float rotAngle = 0;

					{
						double skinning_matrix_b[12];						//special tranformation from observation between skinningMatrix and transformMatrix
						double resultTransformMatrix[16];
						resultTransformMatrix[0] = val_float(section->m00);
						resultTransformMatrix[1] = val_float(section->m01);
						resultTransformMatrix[2] = val_float(section->m02);
						resultTransformMatrix[3] = val_float(section->posX);

						resultTransformMatrix[4] = val_float(section->m10);
						resultTransformMatrix[5] = val_float(section->m11);
						resultTransformMatrix[6] = val_float(section->m12);
						resultTransformMatrix[7] = val_float(section->posY);

						resultTransformMatrix[8] = val_float(section->m20);
						resultTransformMatrix[9] = val_float(section->m21);
						resultTransformMatrix[10] = val_float(section->m22);
						resultTransformMatrix[11] = val_float(section->posZ);

						resultTransformMatrix[12] = 0;
						resultTransformMatrix[13] = 0;
						resultTransformMatrix[14] = 0;
						resultTransformMatrix[15] = 1.0;

						Common::decomposition4x4(&resultTransformMatrix[0], &skinning_matrix_b[0]);
						double quaternionX = skinning_matrix_b[4];
						double quaternionY = skinning_matrix_b[5];
						double quaternionZ = skinning_matrix_b[6];
						double quaternionW = skinning_matrix_b[7];

						double lenghtAxis = sqrt( quaternionX * quaternionX + quaternionY * quaternionY + quaternionZ * quaternionZ);
						if (lenghtAxis > 0.0001)
						{
							rotAxisX = (float)(quaternionX / lenghtAxis);
							rotAxisY = (float)(quaternionY / lenghtAxis);
							rotAxisZ = (float)(quaternionZ / lenghtAxis);
							rotAngle = (float)(acos(quaternionW) * 2.0);
						}
					}

					collada->addTransformOnNode(collada_node, val_float(section->posX), val_float(section->posY), val_float(section->posZ), rotAxisX, rotAxisY, rotAxisZ, rotAngle);
					collada_collision->addTransformOnNode(collada_collision_node, val_float(section->posX), val_float(section->posY), val_float(section->posZ), rotAxisX, rotAxisY, rotAxisZ, rotAngle);
				}
				break;

				case 0xD065:
				{
					SWR_AltN_0xD065* section = (SWR_AltN_0xD065*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0xD065);

					TiXmlElement* node_section = new TiXmlElement("Section_D065_Transform_b");
					if (!XMLTEST_SoKeepSmaller)
						node_Malt->LinkEndChild(node_section);

					TiXmlElement* node_matrix = new TiXmlElement("Matrix3x3");
					node_section->LinkEndChild(node_matrix);

					node = new TiXmlElement("m0");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m00))); 
					node->SetAttribute("c1", FloatToString(val_float(section->m01)));
					node->SetAttribute("c2", FloatToString(val_float(section->m02)));
					
					node = new TiXmlElement("m1");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m10)));
					node->SetAttribute("c1", FloatToString(val_float(section->m11)));
					node->SetAttribute("c2", FloatToString(val_float(section->m12)));

					node = new TiXmlElement("m2");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m20)));
					node->SetAttribute("c1", FloatToString(val_float(section->m21)));
					node->SetAttribute("c2", FloatToString(val_float(section->m22)));


					node = new TiXmlElement("Position");
					node_section->LinkEndChild(node);
					node->SetAttribute("x", FloatToString(val_float(section->posX)));
					node->SetAttribute("y", FloatToString(val_float(section->posY)));
					node->SetAttribute("z", FloatToString(val_float(section->posZ)));

					node = new TiXmlElement("Unknow12_Vector3");
					node_section->LinkEndChild(node);
					node->SetAttribute("x", FloatToString(val_float(section->unk12_X)));
					node->SetAttribute("y", FloatToString(val_float(section->unk12_Y)));
					node->SetAttribute("z", FloatToString(val_float(section->unk12_Z)));


					//todo simplify this.
					float rotAxisX = 0;
					float rotAxisY = 0;
					float rotAxisZ = 0;
					float rotAngle = 0;

					{
						double skinning_matrix_b[12];						//special tranformation from observation between skinningMatrix and transformMatrix
						double resultTransformMatrix[16];
						resultTransformMatrix[0] = val_float(section->m00);
						resultTransformMatrix[1] = val_float(section->m01);
						resultTransformMatrix[2] = val_float(section->m02);
						resultTransformMatrix[3] = val_float(section->posX);

						resultTransformMatrix[4] = val_float(section->m10);
						resultTransformMatrix[5] = val_float(section->m11);
						resultTransformMatrix[6] = val_float(section->m12);
						resultTransformMatrix[7] = val_float(section->posY);

						resultTransformMatrix[8] = val_float(section->m20);
						resultTransformMatrix[9] = val_float(section->m21);
						resultTransformMatrix[10] = val_float(section->m22);
						resultTransformMatrix[11] = val_float(section->posZ);

						resultTransformMatrix[12] = 0;
						resultTransformMatrix[13] = 0;
						resultTransformMatrix[14] = 0;
						resultTransformMatrix[15] = 1.0;

						Common::decomposition4x4(&resultTransformMatrix[0], &skinning_matrix_b[0]);
						double quaternionX = skinning_matrix_b[4];
						double quaternionY = skinning_matrix_b[5];
						double quaternionZ = skinning_matrix_b[6];
						double quaternionW = skinning_matrix_b[7];

						double lenghtAxis = sqrt(quaternionX * quaternionX + quaternionY * quaternionY + quaternionZ * quaternionZ);
						if (lenghtAxis > 0.0001)
						{
							rotAxisX = (float)(quaternionX / lenghtAxis);
							rotAxisY = (float)(quaternionY / lenghtAxis);
							rotAxisZ = (float)(quaternionZ / lenghtAxis);
							rotAngle = (float)(acos(quaternionW) * 2.0);
						}
					}

					collada_collision->addTransformOnNode(collada_collision_node, val_float(section->posX), val_float(section->posY), val_float(section->posZ), rotAxisX, rotAxisY, rotAxisZ, rotAngle);
				}
				break;

				case 0xD066:
				{
					SWR_AltN_0xD066* section = (SWR_AltN_0xD066*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0xD066);

					TiXmlElement* node_section = new TiXmlElement("Section_D066");
					if (!XMLTEST_SoKeepSmaller)
						node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("unk_0"); node->SetAttribute("u16", UnsignedToString(val16(section->unk_0), true)); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_1"); node->SetAttribute("u16", UnsignedToString(val16(section->unk_1), true)); node_section->LinkEndChild(node);

					node = new TiXmlElement("unk_2"); node->SetAttribute("float", FloatToString(val_float(section->unk_2))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_3"); node->SetAttribute("float", FloatToString(val_float(section->unk_3))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_4"); node->SetAttribute("float", FloatToString(val_float(section->unk_4))); node_section->LinkEndChild(node);
				}
				break;

				default:
					break;
				}



				// Recursively parse children if this has any ???
				if ((hdr_AltN->flags & 0x4000) && (hdr_AltN->offset_Childs))				// 0x5xxx or 0xDxxxx (for 0x3xxx the child are struct_V16)
				{
					size_t startoffset_Child_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
					offset = startoffset_Child_listOffset;

					uint32_t* listOffsetAltN_Child = (uint32_t*)GetOffsetPtr(buf, offset, true);

					TiXmlElement* node_section = new TiXmlElement("ListChild");
					if (!XMLTEST_SoKeepSmaller)
						node_Malt->LinkEndChild(node_section);

					for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
					{
						offset += sizeof(uint32_t);

						if (listOffsetAltN_Child[k] == 0)
							continue;

						listRecusiveAltN.push_back(val32(listOffsetAltN_Child[k]) + hdr->offset_Section2);
						listRecusiveAltN_ColladaParentNode.push_back(collada_node);
						listRecusiveAltN_Collada_collisionParentNode.push_back(collada_collision_node);
						if (XMLTEST_UseHierarchy)
						{
							listRecusiveAltN_Xml.push_back(node_section);						//to have hierarchy.
						}else {
							node = new TiXmlElement("Child"); node->SetAttribute("offset", UnsignedToString(val32(listOffsetAltN_Child[k]) + hdr->offset_Section2, true)); node_section->LinkEndChild(node);
							listRecusiveAltN_Xml.push_back(node_listMalt);						//better for analyze value
						}
					}
				}

				//reinverse for another pass on the same
				hdr_AltN->flags = val32(hdr_AltN->flags);
				hdr_AltN->nb_Childs = val32(hdr_AltN->nb_Childs);
				hdr_AltN->offset_Childs = val32(hdr_AltN->offset_Childs);
			}
		}





		//-----------------------  Anim :

		
		TiXmlElement* node_listAnim = new TiXmlElement("ListAnim");
		if (!XMLTEST_SoKeepSmaller)
			node_model->LinkEndChild(node_listAnim);


		size_t nbAnim = listPointer_Anim.size();
		for (size_t inc_Anim = 0; inc_Anim < nbAnim; inc_Anim++)
		{
			size_t startSectionAnim = listPointer_Anim.at(inc_Anim);
			offset = startSectionAnim;

			SWR_Anim_Header* hdr_anim = (SWR_Anim_Header*)GetOffsetPtr(buf, offset, true);
			offset += sizeof(SWR_Anim_Header);
			hdr_anim->nbKeyFrames = val32(hdr_anim->nbKeyFrames);
			hdr_anim->offset_times = val32(hdr_anim->offset_times);
			hdr_anim->offset_values = val32(hdr_anim->offset_values);
			hdr_anim->offset_AltN = val32(hdr_anim->offset_AltN);


			TiXmlElement* node_Anim = new TiXmlElement("Anim");
			node_listAnim->LinkEndChild(node_Anim);
			
			
			//node = new TiXmlElement("unk0");				//always 0, so don't care.
			//for(size_t j=0;j<61;j++)
			//	node->SetAttribute(string("i_") + std::to_string(j), UnsignedToString(val32(hdr_anim->unk0[j]), true));
			//node_Anim->LinkEndChild(node);
			

			node = new TiXmlElement("unk1_0"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk1_0))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk1_1"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk1_1))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk1_2"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk1_2))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk2"); node->SetAttribute("u8", UnsignedToString(hdr_anim->unk2, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk3"); node->SetAttribute("u8", UnsignedToString(hdr_anim->unk3, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk4"); node->SetAttribute("u8", UnsignedToString(hdr_anim->unk4, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("flags_a"); node->SetAttribute("u4", UnsignedToString((hdr_anim->flags & 0xF0) >> 4, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("flags_b"); node->SetAttribute("u4", UnsignedToString((hdr_anim->flags & 0x0F), true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk5_0"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk5_0))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk5_1"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk5_1))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk5_2"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk5_2))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk6"); node->SetAttribute("u32", UnsignedToString(val32(hdr_anim->unk6), true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk7"); node->SetAttribute("u32", UnsignedToString(val32(hdr_anim->unk7), true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk8"); node->SetAttribute("u32", UnsignedToString(val32(hdr_anim->unk8), true)); node_Anim->LinkEndChild(node);

			//todo remove after solve case flags 2, 12, and 35
			node = new TiXmlElement("nbKeyFrames"); node->SetAttribute("u32", UnsignedToString(hdr_anim->nbKeyFrames, false)); node_Anim->LinkEndChild(node);
			
			std::vector<float> listKeyframesTimes;
			if (hdr_anim->offset_times)
			{
				size_t startSectionAnim_Times = hdr_anim->offset_times + hdr->offset_Section2;
				offset = startSectionAnim_Times;

				float* values = (float*)GetOffsetPtr(buf, offset, true);
				for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
				{
					listKeyframesTimes.push_back(val_float(values[j]));
					offset += sizeof(float);

					/*
					if ((size_t)(listKeyframesTimes.back() * 60.0f) > ean_anim.frame_count)
						ean_anim.frame_count = (size_t)(listKeyframesTimes.back() * 60.0f);
					*/
				}
			}

			if (hdr_anim->offset_values)
			{
				size_t startSectionAnim_Values = hdr_anim->offset_values + hdr->offset_Section2;
				offset = startSectionAnim_Values;

				size_t nbComponents = 0;
				switch (hdr_anim->flags & 0x0F)
				{
				case 1: case 0xB: case 0xC:	nbComponents = 1; break;
				case 4:						nbComponents = 2; break;
				case 7: case 9: case 0xA:	nbComponents = 3; break;
				case 6: case 8:				nbComponents = 4; break;


				case 2:
				{
					offset = hdr_anim->offset_AltN + hdr->offset_Section2;
					SWR_Anim_Values_case2_Header* hdr_anim2 = (SWR_Anim_Values_case2_Header*)GetOffsetPtr(buf, offset, true);

					TiXmlElement* node_listKeyframes = new TiXmlElement("ListKeyframes");
					node_listKeyframes->SetAttribute("offset_section4_targeted", UnsignedToString(val32(hdr_anim2->offset_section4), true));
					node_listKeyframes->SetAttribute("case2__unk0", UnsignedToString(val32(hdr_anim2->unk0), true) );
					node_Anim->LinkEndChild(node_listKeyframes);


					offset = hdr_anim->offset_values + hdr->offset_Section2;
					uint32_t* listOffset = (uint32_t*)GetOffsetPtr(buf, offset, true);
					
					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						size_t startoffset_section5 = val32(listOffset[j]) + hdr->offset_Section2;
						offset = startoffset_section5;

						TiXmlElement* node_Kf = new TiXmlElement("Keyframe");
						node_listKeyframes->LinkEndChild(node_Kf);

						node_Kf->SetAttribute("time", FloatToString(listKeyframesTimes.at(j)));

						SWR_Anim_Values_case2* section = (SWR_Anim_Values_case2*)GetOffsetPtr(buf, offset, true);

						SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);
						offset += sizeof(SWR_MODEL_Section5);


						TiXmlElement* node_section5 = new TiXmlElement("Section5");
						node_Kf->LinkEndChild(node_section5);

						node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk0), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk4"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk4), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk6"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk6), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk8_0"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[0]), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk8_1"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[1]), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk12"); node->SetAttribute("u8", UnsignedToString(section5->unk12, true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk13"); node->SetAttribute("u8", UnsignedToString(section5->unk13, true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk14_0"); node->SetAttribute("u8", UnsignedToString(section5->unk14[0], true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk14_1"); node->SetAttribute("u8", UnsignedToString(section5->unk14[1], true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk16"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk16), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk18"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk18), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk20"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk20), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk22"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk22), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk24"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk24), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk26"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk26), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk48"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk48), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk52"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk52), true)); node_section5->LinkEndChild(node);						
						node = new TiXmlElement("textureMask"); node->SetAttribute("u8", UnsignedToString((val32(section5->textureMaskAndIndex) >> 24) & 0xFF, true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("textureIndex"); node->SetAttribute("u24", UnsignedToString(val32(section5->textureMaskAndIndex) & 0x00FFFFFF, true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk60"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk60), true)); node_section5->LinkEndChild(node);

						for (size_t m = 0; m < 5; m++)
						{
							if (!section5->offset_Section5_b[m])
								continue;
							
							size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
							offset = startoffset_section5_b;

							SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

							offset += sizeof(SWR_MODEL_Section5_b);

							TiXmlElement* node_section5b = new TiXmlElement("Section5b");
							node_section5->LinkEndChild(node_section5b);

							node = new TiXmlElement("unk0"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk0), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk2"); node->SetAttribute("u8", UnsignedToString(section5_b->unk2, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk3"); node->SetAttribute("u8", UnsignedToString(section5_b->unk3, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk4"); node->SetAttribute("u8", UnsignedToString(section5_b->unk4, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk5"); node->SetAttribute("u8", UnsignedToString(section5_b->unk5, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk6_a"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_a), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk6_b"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_b), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk8"); node->SetAttribute("u32", UnsignedToString(val32(section5_b->unk8), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk12"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk12), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk14"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk14), true)); node_section5b->LinkEndChild(node);
						}

						
					}
				}

				case 5:
				{
					// strange things for offset_values and offset_AltN Todo test if it's float16:
					node = new TiXmlElement("offset_values_case5"); node->SetAttribute("u32", UnsignedToString(hdr_anim->offset_values, true)); node_Anim->LinkEndChild(node);
					node = new TiXmlElement("offset_AltN_case5"); node->SetAttribute("u32", UnsignedToString(hdr_anim->offset_AltN, true)); node_Anim->LinkEndChild(node);
				}break;

				default:
				{
					::printf("Warning: Unknowed animation flags for component %s. skipped.\n", UnsignedToString(hdr_anim->flags, true).c_str());
					notifyWarning();
				}break;
				}

				//nbComponents = 0;		//test Anima Todo remove


				TiXmlElement* node_listKeyframes = new TiXmlElement("ListKeyframes");
				node_listKeyframes->SetAttribute("nbComponents", nbComponents);
				node_Anim->LinkEndChild(node_listKeyframes);

				if (nbComponents != 0)
				{
					/*
					//find ean bone and create a ean Node to animate the bone.
					size_t isfound = (size_t)-1;

					size_t nbAlt = listAltN_offset.size();
					for (size_t j = 0; j < nbAlt; j++)
					{
						if (hdr_anim->offset_AltN + hdr->offset_Section2 == listAltN_offset.at(j))
						{
							isfound = esk->getBoneIndex(listAltN_BonesName.at(j));
							node_listKeyframes->SetAttribute("bone", listAltN_BonesName.at(j));
							break;
						}
					}

					
					EANAnimationNode* ean_animNode = 0;
					if (isfound != (size_t)-1)
					{
						size_t nbNodes = ean_anim.nodes.size();
						for (size_t j = 0; j < nbNodes; j++)
						{
							if (ean_anim.nodes.at(j).bone_index == isfound)
							{
								ean_animNode = &ean_anim.nodes.at(j);
								break;
							}
						}
						if (!ean_animNode)
						{
							ean_anim.nodes.push_back(EANAnimationNode());
							ean_anim.nodes.back().bone_index = isfound;
							ean_animNode = &ean_anim.nodes.at(nbNodes);
						}
					}
					
					
					//Now it's about the type of animation: position/orientation/scale
					EANKeyframedAnimation* eanKfAnim = 0;
					if (ean_animNode)
					{
						if (nbComponents == 4)
						{
							ean_animNode->keyframed_animations.push_back(EANKeyframedAnimation());
							eanKfAnim = &ean_animNode->keyframed_animations.at(ean_animNode->keyframed_animations.size() - 1);
							eanKfAnim->flag = LIBXENOVERSE_EAN_KEYFRAMED_ANIMATION_FLAG_ROTATION;

						}else{
							
							//todo analyze to make the difference between position and scale.
							if ((hdr_anim->flags & 0x0F) == 9)
							{
								ean_animNode->keyframed_animations.push_back(EANKeyframedAnimation());
								eanKfAnim = &ean_animNode->keyframed_animations.at(ean_animNode->keyframed_animations.size() - 1);
								eanKfAnim->flag = LIBXENOVERSE_EAN_KEYFRAMED_ANIMATION_FLAG_POSITION;
							}
						}
					}
					*/


					
					float* values = (float*)GetOffsetPtr(buf, offset, true);
					size_t inc = 0;

					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						TiXmlElement* node_Kf = new TiXmlElement("Keyframe");
						node_listKeyframes->LinkEndChild(node_Kf);

						node_Kf->SetAttribute("time", FloatToString(listKeyframesTimes.at(j)));

						if (nbComponents != 4)
						{
							float x = 0.0;
							float y = 0.0;
							float z = 0.0;
							
							x = val_float(values[inc++]);
							node_Kf->SetAttribute( (nbComponents != 1) ? "x" : "value", FloatToString(x));
							offset += sizeof(float);

							if (nbComponents > 1)
							{
								y = val_float(values[inc++]);
								node_Kf->SetAttribute("y", FloatToString(y));
								offset += sizeof(float);
							}
							if (nbComponents > 2)
							{
								z = val_float(values[inc++]);
								node_Kf->SetAttribute("z", FloatToString(z));
								offset += sizeof(float);
							}

							/*
							if (eanKfAnim)
							{
								EANKeyframe eanKf((int)(listKeyframesTimes.at(j) * 60.0f), x, y, z);	//because ean time is NumFrame, and is done for 60fps
								eanKfAnim->keyframes.push_back(eanKf);
							}
							*/

						}else{			//apparently it's quaternion, and the order is W XYZ, to be simple ...

							float axisX = val_float(values[inc++]);
							float axisY = val_float(values[inc++]);
							float axisZ = val_float(values[inc++]);
							float angle = val_float(values[inc++]);
							offset += 4 * sizeof(float);

							/*
							if (eanKfAnim)
							{
								FbxQuaternion quad_tmp(FbxVector4(axisX, axisY, axisZ), angle);

								EANKeyframe eanKf((int)(listKeyframesTimes.at(j) * 60.0f), (float)quad_tmp[0], (float)quad_tmp[1], (float)quad_tmp[2], (float)quad_tmp[3]);	//because ean time is NumFrame, and is done for 60fps
								eanKfAnim->keyframes.push_back(eanKf);
							}
							*/

							node_Kf->SetAttribute("x", FloatToString(axisX));
							node_Kf->SetAttribute("y", FloatToString(axisY));
							node_Kf->SetAttribute("z", FloatToString(axisZ));
							node_Kf->SetAttribute("angle", FloatToString(angle));
						}
					}
				}
			}

			//reinverse for another time
			hdr_anim->nbKeyFrames = val32(hdr_anim->nbKeyFrames);
			hdr_anim->offset_times = val32(hdr_anim->offset_times);
			hdr_anim->offset_values = val32(hdr_anim->offset_values);
			hdr_anim->offset_AltN = val32(hdr_anim->offset_AltN);
		}
	}

	
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// wxHexEditor coloration ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*-------------------------------------------------------------------------------\
|                             save_Coloration		                             |
\-------------------------------------------------------------------------------*/
void Swr_Model::save_Coloration(string filename, bool show_error)
{
	//Xml conversion make files bigger. and TinyXml take huge memory in ram. So, here a split of Files ONLY IF many model inside the filename
	std::vector<string> listFilename;
	listFilename.push_back(filename);


	//Split , because of TinyXml, Todo commment.
	{
		big_endian = true;

		uint8_t *buf;
		size_t size;

		buf = ReadFile(filename, &size, show_error);
		if (!buf)
			return;


		std::vector<size_t> listBytesAllreadyTagged;
		listBytesAllreadyTagged.resize(size, (size_t)-1);				//to check override of the same byte (overflow)

		size_t nbModels = val32(*(uint32_t*)buf);
		if (nbModels > 1)
		{
			printf("There is %i models. to avoid troubles with memory and size of Xml, we split the file by model.\n", nbModels);
			listFilename.clear();

			size_t offset = sizeof(uint32_t);
			size_t startoffsetModelHeader = offset;
			for (size_t i = 0; i < nbModels; i++)
			{
				offset = startoffsetModelHeader + i * sizeof(SWR_MODELHeader);

				SWR_MODELHeader_Used* hdr = (SWR_MODELHeader_Used*)(buf + offset);
				hdr->offset_Section1 = val32(hdr->offset_Section1);
				hdr->offset_Section2 = val32(hdr->offset_Section2);
				size_t offset_NextHeader_Section1 = val32(hdr->offset_NextHeader_Section1);

				size_t sizeSection1 = hdr->offset_Section2 - hdr->offset_Section1;
				size_t sizeSection2 = offset_NextHeader_Section1 - hdr->offset_Section2;

				{
					size_t filesize = 4 * sizeof(uint32_t) + sizeSection1 + sizeSection2;

					uint8_t *buf_tmp = new uint8_t[filesize];
					if (!buf_tmp)
					{
						printf("%s: Memory allocation error (0x%x)\n", FUNCNAME, filesize);
						notifyError();
						return;
					}
					uint32_t* buf_u32 = (uint32_t*)buf_tmp;
					buf_u32[0] = val32(1);
					buf_u32[1] = val32(0x10);
					buf_u32[2] = val32(0x10 + sizeSection1);
					buf_u32[3] = val32(0x10 + sizeSection1 + sizeSection2);
					memcpy(buf_tmp + 4 * sizeof(uint32_t), buf + hdr->offset_Section1, sizeSection1);
					memcpy(buf_tmp + 4 * sizeof(uint32_t) + sizeSection1, buf + hdr->offset_Section2, sizeSection2);


					listFilename.push_back(filename + "_" + UnsignedToString(i, false) + ".bin");
					bool ret = WriteFileBool(listFilename.back(), buf_tmp, filesize);
					delete[] buf_tmp;
				}
			}
		}

		delete[] buf;
	}



	size_t nbFiles = listFilename.size();
	for (size_t i = 0; i < nbFiles; i++)
	{
		string name = listFilename.at(i);
		printf("******************* Model : %s\n", name.c_str());

		uint8_t *buf;
		size_t size;

		buf = ReadFile(name, &size, show_error);
		if (!buf)
			return;

		TiXmlDocument *doc = new TiXmlDocument();
		TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
		doc->LinkEndChild(decl);

		TiXmlElement *root = new TiXmlElement("wxHexEditor_XML_TAG");


		TiXmlElement* filename_node = new TiXmlElement("filename");
		EMO_BaseFile::WriteParamString(filename_node, "path", name);


		try
		{
			write_Coloration(filename_node, buf, size);
		}catch (...) {

		}


		root->LinkEndChild(filename_node);
		doc->LinkEndChild(root);

		doc->SaveFile(name + ".tags");

		delete[] buf;
		delete doc;
	}
	return;
}




/*-------------------------------------------------------------------------------\
|                             write_Coloration				                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Coloration(TiXmlElement *parent, const uint8_t *buf, size_t size)
{
	big_endian = true;
	std::vector<size_t> listBytesAllreadyTagged;
	listBytesAllreadyTagged.resize(size, (size_t)-1);				//to check override of the same byte (overflow)

	size_t idTag = 0;
	size_t offset = 0;
	size_t incSection = 0;
	size_t incParam = 0;



	std::vector<bool> isTextureArray;						//map all the binary, to test if a Texture is forgetted.
	isTextureArray.resize(size, false);


	
	size_t nbModels = val32(*(uint32_t*)buf);

	write_Coloration_Tag("nbModels", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

	size_t startoffsetModelHeader = offset;
	for (size_t i = 0; i < nbModels; i++)
	{
		incSection = 0;
		incParam = 0;
		
		offset = startoffsetModelHeader + i * sizeof(SWR_MODELHeader);

		SWR_MODELHeader_Used* hdr = (SWR_MODELHeader_Used*)(buf + offset);
		hdr->offset_Section1 = val32(hdr->offset_Section1);
		hdr->offset_Section2 = val32(hdr->offset_Section2);
		size_t offset_NextHeader_Section1 = val32(hdr->offset_NextHeader_Section1);

		write_Coloration_Tag("offset_Section1", "uint32_t", "Materials or Textures descriptors/mask", offset, sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, i); offset += sizeof(uint32_t);
		write_Coloration_Tag("offset_Section2", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, i); offset += sizeof(uint32_t);
		


		//Section1 
		std::vector<uint32_t> dataSection1;
		uint32_t* section1 = (uint32_t*)GetOffsetPtr(buf, hdr->offset_Section1, true);
		offset = hdr->offset_Section1;
		incSection++;
		incParam = 0;
				
		size_t nbSection1Elements = (hdr->offset_Section2 - hdr->offset_Section1) / sizeof(uint32_t);
		for (size_t j = 0; j < nbSection1Elements; j++)
		{
			dataSection1.push_back(val32(section1[j]));
			write_Coloration_Tag("bitMaskForMaterialOrTexture", "uint32_t", "", offset, sizeof(uint32_t), "Section1", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
		}



		//Section2
		SWR_MODEL_Section2_Header* hdr_section2 = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, hdr->offset_Section2, true);
		offset = hdr->offset_Section2;
		size_t sizeSection2 = offset_NextHeader_Section1 - hdr->offset_Section2;

		incSection++;
		incParam = 0;
		write_Coloration_Tag("signature", "string", "", offset, 4 * sizeof(char), "Section2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, i);	offset += 4 * sizeof(char);

		if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_COMPRESSED, 4) == 0)
		{
			::printf("Warning: Comp (for Compressed data) is not take care. did you use data from Pc version ? skipped.\n");
			notifyWarning();
			continue;
		}

		//Todo after : take care of "Comp" Compressed
		

		uint32_t* section2_u32 = (uint32_t*)GetOffsetPtr(buf, hdr->offset_Section2, true);
	
		size_t nbUint32Section2 = sizeSection2 / 4;
		size_t nbGroup32Uint32 = nbUint32Section2 / 32;
		for (size_t j = 0; j < nbGroup32Uint32; j++)					//each bit of Section1 representing presence of Texture for one uint32_t of Section2
		{
			for (size_t k = 0; k < 31; k++)
			{
				if ((dataSection1.at(j) & (1 << (31 - k))) == 0)			//31 - j to begin on the left bit.
					continue;

				size_t index = j * 32 + k;

				isTextureArray.at(index * 4 + hdr->offset_Section2) = true;
			}
		}

		



		if ((memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MODEL, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_TRACK, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_POD, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_PART, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_SCENE, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MAlt, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_Pupp, 4) != 0)
			)
		{
			::printf("Warning: Unknowed Section2_header Signature :%c%c%c%c skipped.\n", hdr_section2->signature[0], hdr_section2->signature[1], hdr_section2->signature[2], hdr_section2->signature[3]);
			notifyWarning();
			continue;
		}



		std::vector<size_t> listPointer_AltN;
		std::vector<size_t> listPointer_Anim;

		uint32_t* section2_unknowParts = (uint32_t*)GetOffsetPtr(buf, offset, true);
		while (*section2_unknowParts != 0xFFFFFFFF)
		{
			if ((*section2_unknowParts != 0)&&(val32(*section2_unknowParts)<sizeSection2)&&(!checkDuplication(val32(*section2_unknowParts) + hdr->offset_Section2, listPointer_AltN)))
				listPointer_AltN.push_back(val32(*section2_unknowParts) + hdr->offset_Section2);
			
			isTextureArray.at(offset) = false;
			write_Coloration_Tag("possible_offset_section", "uint32_t", (*section2_unknowParts != 0) ? (" => "+ UnsignedToString(val32(*section2_unknowParts) + hdr->offset_Section2, true)): "", offset, sizeof(uint32_t), "Section2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

			section2_unknowParts++;
		}
		write_Coloration_Tag("EndListPointer", "uint32_t", "", offset, sizeof(uint32_t), "Section2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);




		bool endFound = false;
		while (!endFound)
		{
			incSection++;
			incParam = 0;

			SWR_MODEL_Section2_Header* hdr_section2_sub = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, offset, true);
			write_Coloration_Tag("signature", "string", "", offset, 4 * sizeof(char), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged);	offset += 4 * sizeof(char);

			if ((memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_HEND, 4) != 0)
				)
			{
				::printf("Warning: Unknowed Section2_SubHeader Signature :%c%c%c%c skipped.\n", hdr_section2_sub->signature[0], hdr_section2_sub->signature[1], hdr_section2_sub->signature[2], hdr_section2_sub->signature[3]);
				notifyWarning();
				break;

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) == 0) {

				
				size_t startoffset_Anim = offset;
				uint32_t* listOffsetAnim = (uint32_t*)GetOffsetPtr(buf, startoffset_Anim, true);

				size_t inc_Anim = 0;
				while (listOffsetAnim[inc_Anim] != 0)
				{
					listOffsetAnim[inc_Anim] = val32(listOffsetAnim[inc_Anim]);

					if (!checkDuplication(listOffsetAnim[inc_Anim] + hdr->offset_Section2, listPointer_Anim))
						listPointer_Anim.push_back(listOffsetAnim[inc_Anim] + hdr->offset_Section2);

					isTextureArray.at(startoffset_Anim + inc_Anim * sizeof(uint32_t)) = false;
					write_Coloration_Tag("offset_SectionAltN", "uint32_t", " => 0x" + UnsignedToString(listOffsetAnim[inc_Anim] + hdr->offset_Section2, true), startoffset_Anim + inc_Anim * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);

					inc_Anim++;

					if (listOffsetAnim[inc_Anim] == 0)
					{
						isTextureArray.at(startoffset_Anim + inc_Anim * sizeof(uint32_t)) = false;
						break;
					}
				}
				write_Coloration_Tag("EndOfList", "uint32_t", "", startoffset_Anim + inc_Anim * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);



			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) == 0){


				size_t startoffset_Data = offset;
				
				size_t nbDatas = val32(*(uint32_t*)GetOffsetPtr(buf, startoffset_Data, true));
				write_Coloration_Tag("nbDatas", "uint32_t", "", offset, sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
				
				SWR_Data* datas = (SWR_Data*)GetOffsetPtr(buf, offset, true);
				
				for (size_t j = 0; j < nbDatas; j++)
				{
					write_Coloration_Tag("unk0", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
					write_Coloration_Tag("unk1", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
					write_Coloration_Tag("unk2", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
					write_Coloration_Tag("unk3", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
				}

				//todo understand data is for what ? linked to another files ?

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) == 0) {


				size_t startoffset_AltN = offset;
				uint32_t* listOffsetAltN = (uint32_t*)GetOffsetPtr(buf, startoffset_AltN, true);

				size_t inc_AltN = 0;
				while (listOffsetAltN[inc_AltN] != 0)
				{
					listOffsetAltN[inc_AltN] = val32(listOffsetAltN[inc_AltN]);

					if (!checkDuplication(listOffsetAltN[inc_AltN] + hdr->offset_Section2, listPointer_AltN))
						listPointer_AltN.push_back(listOffsetAltN[inc_AltN] + hdr->offset_Section2);

					isTextureArray.at(offset) = false;
					write_Coloration_Tag("offset_SectionAltN", "uint32_t", " => 0x" + UnsignedToString(listOffsetAltN[inc_AltN] + hdr->offset_Section2, true), startoffset_AltN + inc_AltN * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_AltN); offset += sizeof(uint32_t);

					inc_AltN++;
					
					if (listOffsetAltN[inc_AltN] == 0)
					{
						isTextureArray.at(offset) = false;
						break;
					}
				}
				write_Coloration_Tag("EndOfList", "uint32_t", "", startoffset_AltN + inc_AltN * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

			}else {		// else "Hend" => normal exit.
				endFound = true;
			}
		}
		

		//saddely , it's could have a Malt just after Hend, never referenced (cf Model_115), So we test to add it.
		// hope the filter on first flags could avoid trouble.
		if (!checkDuplication(offset, listPointer_AltN))
			listPointer_AltN.push_back(offset);

		
		
		//-----------------------  Malt /AltN :

		std::vector<size_t> listToAvoidDuplication;

		size_t nbAltN = listPointer_AltN.size();
		for(size_t inc_AltN = 0; inc_AltN< nbAltN ; inc_AltN++)
		{
			size_t startSectionAltN = listPointer_AltN.at(inc_AltN);
			offset = startSectionAltN;

			incSection = 3;			//for having 4 in for
			incParam = 0;

			std::vector<size_t> listRecusiveAltN;
			listRecusiveAltN.push_back(offset);

			for(size_t j=0;j<listRecusiveAltN.size();j++)
			{
				offset = listRecusiveAltN.at(j);

				if (checkDuplication(offset, listToAvoidDuplication))
					continue;
				listToAvoidDuplication.push_back(offset);


				incSection++;
				incParam = 0;

				if (*(uint32_t*)GetOffsetPtr(buf, offset, true) == 0)
				{
					//write_Coloration_Tag("badPointerComeHere", "uint32_t", " Todo why ?", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j);
					continue;
				}

				SWR_AltN_Header* hdr_AltN = (SWR_AltN_Header*)GetOffsetPtr(buf, offset, true);
				hdr_AltN->flags = val32(hdr_AltN->flags);
				hdr_AltN->nb_Childs = val32(hdr_AltN->nb_Childs);
				hdr_AltN->offset_Childs = val32(hdr_AltN->offset_Childs);

				write_Coloration_Tag("flags", "uint32_t", "values founded : 0x3064 (most x7680, look like geometry), 0x5064 (third x 1795, look like just a node in hiererachy, without extra datas than Malt Header), 0x5065 (x52, 0 1 -1 ?), 0x5066 (x75, look like Lod definitions, and be linked to 0xd064), 0xd064 (x75, it's a Transform, look like be linked to 0x5066),  0xd065 (second x5413, look like tranform + a unknow Position), 0xd066 (x78)", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("unk0", "uint32_t", "look like flags, 0xffffffff (most)", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("unk1", "uint32_t", "look also like flags, 0xfffffffd (most) ", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("unk_2_a", "uint8_t", "look like could be splitted in 2 uint4 : 0 (most), 1 or 2 for the first. 0 (most) 3 or 0xb for the second. So it's look like flags.", offset, sizeof(uint8_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
				write_Coloration_Tag("unk_2_b", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
				write_Coloration_Tag("unk3", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
				write_Coloration_Tag("unk4", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("nb_Childs", "uint32_t", "", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				isTextureArray.at(offset) = false;
				write_Coloration_Tag("offset_Childs", "uint32_t", " => 0x"+ UnsignedToString(hdr_AltN->offset_Childs + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);


				//todo: better understand flags to avoid the big switch, if it's possible.

				switch (hdr_AltN->flags)
				{
					case 0x3064:
					{
						SWR_AltN_0x3064* section = (SWR_AltN_0x3064*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("minX", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("minY", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("minZ", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("maxX", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("maxY", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("maxZ", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk0", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk1", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

						size_t startoffset_Section3_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
						offset = startoffset_Section3_listOffset;

						uint32_t* listOffsetAltN_Section3 = (uint32_t*)GetOffsetPtr(buf, offset, true);

						for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
						{
							incSection++;
							incParam = 0;
							
							listOffsetAltN_Section3[k] = val32(listOffsetAltN_Section3[k]);

							isTextureArray.at(startoffset_Section3_listOffset + k * sizeof(uint32_t)) = false;
							write_Coloration_Tag("offset_Section3", "uint32_t", " => 0x" + UnsignedToString(listOffsetAltN_Section3[k] + hdr->offset_Section2, true), startoffset_Section3_listOffset + k * sizeof(uint32_t), sizeof(uint32_t), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k);
							
							size_t startoffset_section3 = listOffsetAltN_Section3[k] + hdr->offset_Section2;
							offset = startoffset_section3;

							

							SWR_MODEL_Section3* section3 = (SWR_MODEL_Section3*)GetOffsetPtr(buf, offset, true);
							section3->offset_section4 = val32(section3->offset_section4);
							section3->offset_section7 = val32(section3->offset_section7);
							section3->nbElementV90 = val16(section3->nbElementV90);
							section3->typeMode = val16(section3->typeMode);
							section3->nbElementV44 = val16(section3->nbElementV44);
							section3->nbElementV52 = val16(section3->nbElementV52);
							section3->offset_V90 = val32(section3->offset_V90);
							section3->offset_unk40 = val32(section3->offset_unk40);
							section3->offset_unk44 = val32(section3->offset_unk44);
							section3->offset_unk48 = val32(section3->offset_unk48);
							section3->offset_unk52 = val32(section3->offset_unk52);
							
							isTextureArray.at(offset) = false;
							write_Coloration_Tag("offset_section4", "uint32_t", " => "+ UnsignedToString(section3->offset_section4 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							isTextureArray.at(offset) = false;
							write_Coloration_Tag("offset_section7", "uint32_t", " => " + UnsignedToString(section3->offset_section7 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("minX", "float", "also a AABB => So Section3 is a subMesh, or a SubModel", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("minY", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("minZ", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("maxX", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("maxY", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("maxZ", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("nbElementV90", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("typeMode", "uint16_t", "3 => 3 *float (or uint16); 4 => 4*float (or uint16); 5 (most) => Count for V90", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							isTextureArray.at(offset) = false;
							write_Coloration_Tag("offset_V90", "uint32_t", " => " + UnsignedToString(section3->offset_V90 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							isTextureArray.at(offset) = false;
							write_Coloration_Tag("offset_unk40", "uint32_t", " => " + UnsignedToString(section3->offset_unk40 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							isTextureArray.at(offset) = false;
							write_Coloration_Tag("offset_unk44", "uint32_t", " => " + UnsignedToString(section3->offset_unk44 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							isTextureArray.at(offset) = false;
							write_Coloration_Tag("offset_unk48", "uint32_t", " => " + UnsignedToString(section3->offset_unk48 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							isTextureArray.at(offset) = false;
							write_Coloration_Tag("offset_unk52", "uint32_t", " => " + UnsignedToString(section3->offset_unk52 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("nbElementV44", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("nbElementV52", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk60", "uint16_t", "always 0.0", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk62", "uint16_t", "[0 (most), 0xa] + 0xc 0xe", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);




							if (section3->offset_V90)								//group of vertex.
							{
								incSection++;
								incParam = 0;

								size_t startoffset_sectionV90 = section3->offset_V90 + hdr->offset_Section2;
								offset = startoffset_sectionV90;

								uint32_t* listValues = (uint32_t*)GetOffsetPtr(buf, offset, true);

								for (size_t m = 0; m < section3->nbElementV90; m++)
								{
									listValues[m] = val32(listValues[m]);
									write_Coloration_Tag("values", "uint32_t", " v90 is a list of number of Element by group.", offset, sizeof(uint32_t), "SWR_MODEL_V90", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, m); offset += sizeof(uint32_t);
								}
							}


							if (section3->offset_unk52)
							{
								incSection++;
								incParam = 0;

								size_t startoffset_section52 = section3->offset_unk52 + hdr->offset_Section2;
								offset = startoffset_section52;

								for (size_t m = 0; m < section3->nbElementV52; m++)
								{
									SWR_MODEL_Section52* section52 = (SWR_MODEL_Section52*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("posX", "uint16_t", "Vertex for Visual. it's a int16 directly", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("posY", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("posZ", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk_padding", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("uvU", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("uvV", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("colorR", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("colorG", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("colorB", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("colorA", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								}
							}


							if (section3->offset_unk44)
							{
								incSection++;
								incParam = 0;

								size_t startoffset_section44 = section3->offset_unk44 + hdr->offset_Section2;
								offset = startoffset_section44;

								uint16_t* section44 = (uint16_t*)GetOffsetPtr(buf, offset, true);
								for (size_t m = 0; m < section3->nbElementV44; m++)
								{
									write_Coloration_Tag("posX", "uint16_t", "vertex for Collision. it's int16 directly", offset, sizeof(uint16_t), "SWR_MODEL_section44", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, m); offset += sizeof(uint16_t);
									write_Coloration_Tag("posY", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_section44", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, m); offset += sizeof(uint16_t);
									write_Coloration_Tag("posZ", "uint16_t", ". ", offset, sizeof(uint16_t), "SWR_MODEL_section44", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, m); offset += sizeof(uint16_t);
								}
							}

							









							if ((section3->offset_unk40) && (!checkDuplication(section3->offset_unk40 + hdr->offset_Section2, listToAvoidDuplication)))
							{
								listToAvoidDuplication.push_back(section3->offset_unk40 + hdr->offset_Section2);

								incSection++;
								incParam = 0;

								size_t startoffset_section40 = section3->offset_unk40 + hdr->offset_Section2;
								offset = startoffset_section40;

								SWR_MODEL_Section40* section40 = (SWR_MODEL_Section40*)GetOffsetPtr(buf, offset, true);

								write_Coloration_Tag("unk0", "uint32_t", "Todo analyze", offset, sizeof(uint32_t), "SWR_MODEL_Section40", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk1", "uint16_t", "Todo analyze", offset, sizeof(uint16_t), "SWR_MODEL_Section40", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk2", "uint16_t", "Todo analyze", offset, sizeof(uint16_t), "SWR_MODEL_Section40", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk3", "uint32_t", "Todo analyze", offset, sizeof(uint32_t), "SWR_MODEL_Section40", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							}





							if ((section3->offset_section4)&&(!checkDuplication(section3->offset_section4 + hdr->offset_Section2, listToAvoidDuplication)))
							{
								listToAvoidDuplication.push_back(section3->offset_section4 + hdr->offset_Section2);

								incSection++;
								incParam = 0;

								size_t startoffset_section4 = section3->offset_section4 + hdr->offset_Section2;
								offset = startoffset_section4;

								SWR_MODEL_Section4* section4 = (SWR_MODEL_Section4*)GetOffsetPtr(buf, offset, true);
								section4->offset_section5 = val32(section4->offset_section5);
								section4->offset_section6 = val32(section4->offset_section6);

								write_Coloration_Tag("unk0", "uint32_t", "could be splitted int uint8 or flags: (second from right) 0(most), 1, 4 or 5. (first from right) 4, 6, 7, 0xc, 0xe, 0xf(most) ", offset, sizeof(uint32_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk4", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk6", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								isTextureArray.at(offset) = false;
								write_Coloration_Tag("offset_section5", "uint32_t", " => " + UnsignedToString(section4->offset_section5 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								isTextureArray.at(offset) = false;
								write_Coloration_Tag("offset_section6", "uint32_t", " => " + UnsignedToString(section4->offset_section6 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);


								if ((section4->offset_section5) && (!checkDuplication(section4->offset_section5 + hdr->offset_Section2, listToAvoidDuplication)))
								{
									listToAvoidDuplication.push_back(section4->offset_section5 + hdr->offset_Section2);

									incSection++;
									incParam = 0;
									
									size_t startoffset_section5 = section4->offset_section5 + hdr->offset_Section2;
									offset = startoffset_section5;

									SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0", "uint32_t", "0, 1 (most), 0x41, 0x49", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk4", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0xfc, 0x100 (most), 0x128, 0x138, 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk6", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0x8c, 0xb8, 0xbc, 0x100 (most), 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk8_0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk8_1", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk12", "uint8_t", "0, 2 (most), 4, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk13", "uint8_t", "0 (most), 1, 3, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk14_0", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk14_1", "uint8_t", "0 (most), 4", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk16", "uint16_t", "4, 8, 0x10, 0x20, 0x3f, 0x40 (most), 0x4a, 0x4e, 0x80. look like flgas", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk18", "uint16_t", "0x4, 0x8, 0x10, 0x20, 0x23, 0x2e, 0x2f, 0x40 (most), 0x80. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk20", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x7e00, 0x8000 (most), 0x9400, 0x9c00. todo splitted uint8", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk22", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x4600, 0x5c00, 0x5e00, 0x8000 (most)", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk24", "uint16_t", "0x0, 0x40, 0x80, 0x100, 0x200 (most), 0x2ab, 0x400, 0x800", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk26", "uint16_t", "0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x16f, 0x1f7, 0x1ff, 0x2aa, 0x365, 0x3ff (most), 0x7ff, 0xd78f", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("offset_Section5_b_0", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[0]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("offset_Section5_b_1", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[1]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("offset_Section5_b_2", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[2]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("offset_Section5_b_3", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[3]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("offset_Section5_b_4", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[4]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk48", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("unk52", "uint32_t", "always 0. the TextureFlags some of unk52 as havingTexture. So unk52 (and may be also unk48) could be offset_Section5_b_X, or as textureMaskAndIndex (but never used in practice).", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									bool haveTexture = isTextureArray.at(offset);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("textureMaskAndIndex", "uint32_t", string(" mask is on 0xFF000000. ")+ (haveTexture ? "haveTexture" : ""), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk60", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);

									for (size_t m = 0; m < 5; m++)
									{
										if (!section5->offset_Section5_b[m])
											continue;

										if (checkDuplication(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2, listToAvoidDuplication))
											continue;
										listToAvoidDuplication.push_back(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2);

										incSection++;
										incParam = 0;

										size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
										offset = startoffset_section5_b;

										SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

										write_Coloration_Tag("unk0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
										write_Coloration_Tag("unk2", "uint8_t", "1, 2, 4 (most), 5, 8, 0x10. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk3", "uint8_t", "it's 2 uint4: 0 (most), 1, 2.  and for the second (right) 0(most), 1, 2", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk4", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk5", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk6_a", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk6_b", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk8", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
										write_Coloration_Tag("unk12", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0xfc (most), 0x124, 0x134, 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
										write_Coloration_Tag("unk14", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0x88, 0xb8, 0xfc (most), 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									}
								}


								if ((section4->offset_section6) && (!checkDuplication(section4->offset_section6 + hdr->offset_Section2, listToAvoidDuplication)))
								{
									listToAvoidDuplication.push_back(section4->offset_section6 + hdr->offset_Section2);
								
									incSection++;
									incParam = 0;
									
									size_t startoffset_section6 = section4->offset_section6 + hdr->offset_Section2;
									offset = startoffset_section6;

									SWR_MODEL_Section6* section6 = (SWR_MODEL_Section6*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0", "uint32_t", "0x0 (second), 0x1 (most), 0x8, 0x9. is flags", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk4", "uint16_t", "0x1, 0x2 (most)", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk6_0", "uint32_t", "(notice , it's seam few values are inversed on bytes order, Todo check) 4 x unint8: (first left) 1 (most), 2, 3, 4, 6. (second left)  1 or 0x1f (most). (third left) 1, 3, 4 (most), d. (the last) 1 or 0x1f (most).", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk6_1", "uint32_t", "4 x unint8: (first left) 1, 2, 3, 4, 6, 7(most). (second left)  1, 3, 7(most). (third left) 0, 1, 3, 4, 7(most). (the last) 1(most), 3, 4 (second), 6, 7.", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk14_0", "uint32_t", "(notice , it's seam few values are inversed on bytes order, Todo check) 4 x unint8: (first left) 0(most), 1 , 3, 4. (second left)  0x1f. (third left) 0, 3(most), 4. (the last) 0x1f.", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk14_1", "uint32_t", "4 x uint8: 0, 7(most).   7.     3, 4, 7(most).  0(most), 4, 6, 7 ", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk22_0", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk22_1", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk24", "uint32_t", "0xc8000000, 0x00442078, 0x0c080000, 0x0c080001, 0x0c082008. look like flags", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk28", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk32", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk34", "uint16_t", "0 (second), 0xffff (most, None), but after there is progressive hig values, may be offsets.", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk36", "uint16_t", "it's 2 x uint8: progressive values  with holes in [0(most) , 0xFF] (could be a index) .     0(most), 1, 0x40, 0xff (look like flags)", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk38", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk40", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk44", "uint32_t", "0 (most), 0x8080, look like flags", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk48", "uint32_t", "0 (most), 0x80100000", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								}
							}



							if (section3->offset_section7)
							{
								incSection++;
								incParam = 0;
								
								size_t startoffset_section7 = section3->offset_section7 + hdr->offset_Section2;
								offset = startoffset_section7;

								SWR_MODEL_Section7* section7 = (SWR_MODEL_Section7*)GetOffsetPtr(buf, offset, true);
								
								write_Coloration_Tag("unk0", "uint16_t", "0(most), 2, 4, 0x10, 0x12, 0x14, 0x20, 0x24. flags", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk2_0", "uint8_t", "0 (most), 1, 2, 3, 4, 5, 7, 0xb, 0xc", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk2_1", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk2_2", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk2_3", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk6", "uint16_t", "0, 1, 3, 0x3d9, 0x3de, 0x3e1, 0x3e2, 0x3e3, 0x3e4 (most), 0x2838, 0x7200, 0x94b0, 0xd830", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk8", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk10", "uint16_t", "0(most), 1, 3, 6, 7, 0xb, 0xf, 0x17. flags", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk12_0", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_1", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_2", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_3", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_4", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_5", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_6", "uint8_t", "0x3d is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_7", "uint8_t", "0 is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk20", "float", "-14000.0, -5580.0, -4800.0, -3147.0, -2953.0, -2629.0, -1482.0, -329.265991, 0.0 (most), 1.0, 1500.0, 4152.0, 8000.0, 8600.0, 11168.097656, 27813.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk24", "float", "-12101.0, -9000.0, -3998.197998, -3800.0, -3364.0, 0.0 (most), 1.0, 2.0, 3765.0, 4426.0, 7633.0, 8390.0, 9115.0, 9300.0, 14800.0, 42000.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk28", "float", "-4712.958008, -3000.0, -1.0 (most), 100.0, 453.0, 557.0, 560.0, 695.0, 891.0, 1273.0, 2800.0, 5934.678223, 6500.0, 21305.0, 30000.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk32", "float", "-1.0, 0.0 (most), 1.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk36", "float", "-1.0, 0.0, 1.0 (most)", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk40", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk44", "uint32_t", "4 x uint8:      0(most), 2.     0(most),1,2.         0(most), 1, 2, 4, 5, 6, 8, 0x10, 0x11, 0x18, 0x20, 0x24, 0x40, 0x80, 0x83, 0x88.      0(most),1,2,4,5,8,0x20, 0x24 0x40, 0x42, 0x48, 0x88,  ", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk48", "uint16_t", "0x0 (most), 0x1, 0x100a", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk50", "uint16_t", "0x1, 0x2, 0x594c (most), 0xa86c, 0xf280", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk52", "uint32_t", "0 the most. look like color RGBA (with lot of alpha at 0)", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk56", "uint32_t", "same", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								isTextureArray.at(offset) = false;
								write_Coloration_Tag("offset_section8", "uint32_t", " => " + UnsignedToString(val32(section7->offset_section8) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);

								

								if ((val32(section7->unk52) & 0xFFFF) == 0x6C3C)			//todo test if it's work on all files.
								{
									size_t startoffset_section7_b = offset;

									SWR_MODEL_Section7_b* section7_b = (SWR_MODEL_Section7_b*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0", "uint32_t", "0, 0xbffc00, 0x1fffc00, 0x5dffc00", offset, sizeof(uint32_t), "SWR_MODEL_Section7b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk1", "uint32_t", "0, 0x400200, 0x2200200, 0x6000200", offset, sizeof(uint32_t), "SWR_MODEL_Section7b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("unk2", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section7b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								}


								std::vector<size_t> listOffsetSection8;
								listOffsetSection8.push_back(val32(section7->offset_section8));

								for (size_t m = 0; m < listOffsetSection8.size(); m++)
								{
									if (!listOffsetSection8.at(m))
										continue;
									
									incSection++;
									incParam = 0;

									size_t startoffset_section8 = listOffsetSection8.at(m) + hdr->offset_Section2;
									offset = startoffset_section8;

									SWR_MODEL_Section8* section8 = (SWR_MODEL_Section8*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0_0", "float", "[-9983.669922, 9733.980469]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk0_1", "float", "[-8403.759766, 16209.339844]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk0_2", "float", "[-2920.409912, 1069.109985]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk12_0", "float", "[-1.0, 1.0]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk12_1", "float", "[-1.0, 1.0]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk12_2", "float", "-0.27, -0.05, -0.02, -0.01, 0.0 (most), 0.06, 0.09", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk24", "float", "[6.44, 532.820007], 270.350006 is the most", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk28", "float", "[6.67,319.540009], 108.32 is the most", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("offset_AltN", "uint32_t", " => "+ UnsignedToString(val32(section8->offset_AltN) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk36", "uint16_t", "0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0xca, 0xcb, 0xd0, 0xd3 (most), 0xd4, 0xd5, 0x12d, 0x130, 0x132, 0x133, 0x134, 0x136, 0x13a, 0x1f5, 0x1f7", offset, sizeof(uint16_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk38", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("offset_next_section8", "uint32_t", " => " + UnsignedToString(val32(section8->offset_next_section8) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);

									listOffsetSection8.push_back(val32(section8->offset_next_section8));
								}
							}


							if (section3->offset_unk48)
							{
								incSection++;
								incParam = 0;

								size_t startoffset_section48 = section3->offset_unk48 + hdr->offset_Section2;
								offset = startoffset_section48;

								

								SWR_MODEL_Section48* section48 = (SWR_MODEL_Section48*)GetOffsetPtr(buf, offset, true);

								size_t inc = 0;
								while (section48->unk0 != 0xDF)
								{
									write_Coloration_Tag("unk0", "uint8_t", "1, 3, 5, 6 (most). it's clearly a type, because others unkX change of values ranges with that.", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk1", "uint8_t", "only paire values in [0(most), 0x3e]", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk2", "uint8_t", "only paire values in [0(most), 0x3e] + 0x40, 0x50, 0x60, ... 0xf0. it's 2x uint4.", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk3", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc); offset += sizeof(uint8_t);
									bool haveTexture = isTextureArray.at(offset);
									isTextureArray.at(offset) = false;
									write_Coloration_Tag("unk4", "uint32_t", "(when it's not 0) seam to target Section52, if(unk0==1) it's on the same model, but else, it's look for another model : offsetS52Abs = (unk4 + hdr->offsetSection2); take the model with the offsetSEction2 just under offsetS52Abs (into out_modelblock.bin); offsetS52_relativeToSection2 =  offsetS52Abs - modelX_outModel.hdr->offset; open ModelX.bin; offsetS52_AbsModelX = offsetS52_relativeToSection2 + ModelX.hdr->offsetSection2; ", offset, sizeof(uint32_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc); offset += sizeof(uint32_t);
									
									section48++;
									inc++;
								}
								write_Coloration_Tag("End", "2 x uint32_t", "", offset, 2 * sizeof(uint32_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += 2 * sizeof(uint32_t);

							}
						}

					}
					break;

					case 0x5065:
					{
						SWR_AltN_0x5065* section = (SWR_AltN_0x5065*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("unk_0", "uint32_t", "0, 1 or 0xffffffff. => 0 1 -1 ?", offset, sizeof(uint32_t), "SWR_AltN_0x5065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
					}
					break;


					case 0x5066:
					{
						SWR_AltN_0x5066* section = (SWR_AltN_0x5066*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("distLod_0", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_1", "float", "3.0, 40.0 (most), 2000.0. unk_0 to unk_4 look like LodDistance ranges", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_2", "float", "40.0, 60.0 (most), 4000.0. ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_3", "float", "60.0, 100.0 (most), 6000.0. ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_4", "float", "100.0, 120.0, 8000.0, 1000000.0 (most).  ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_5", "float", "-1.0 (most) or 1000000.0, ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_6", "float", "always -1.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_7", "float", "always -1.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("unk_8", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_9", "float", "always -0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_10", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;


					case 0xD064:
					{
						SWR_AltN_0xD064* section = (SWR_AltN_0xD064*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("m00", "float", "always 0.0160000008. Matrix3x3 for orientation + scale. apparently Section_0xD064 is a Transform (as D065). Todo Check if there is a direct link with 5066", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m01", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m02", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("m10", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m11", "float", "always 0.0160000008", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m12", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						
						write_Coloration_Tag("m20", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m21", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m22", "float", "always 0.0160000008", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("posX", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posY", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posZ", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;

					case 0xD065:
					{
						SWR_AltN_0xD065* section = (SWR_AltN_0xD065*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("m00", "float", "Matrix3x3 for orientation + scale. apparently Section_0xD065 is a Transform", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m01", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m02", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("m10", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m11", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m12", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						
						write_Coloration_Tag("m20", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m21", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m22", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("posX", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posY", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posZ", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("unk12_X", "float", "0.0 is the most (it's like D064, else the '5' is for adding this part apparently)", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk12_Y", "float", "0.0 is the most", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk12_Z", "float", "0.0 is the most", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;

					case 0xD066:
					{
						SWR_AltN_0xD066* section = (SWR_AltN_0xD066*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("unk_0", "uint16_t", "0 (most) or 1", offset, sizeof(uint16_t), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk_1", "uint16_t", "0 or 1 (most, exactly always the inverse of unk_1)", offset, sizeof(uint16_t), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint16_t);

						write_Coloration_Tag("unk_2", "float", "always 0", offset, sizeof(float), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_3", "float", "always 0", offset, sizeof(float), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_4", "float", "always 1.0", offset, sizeof(float), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;

					default:
						break;
				}



				// Recursively parse children if this has any ???
				if ((hdr_AltN->flags & 0x4000)&&(hdr_AltN->offset_Childs))				// 0x5xxx or 0xDxxxx (for 0x3xxx the child are struct_V16)
				{
					size_t startoffset_Child_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
					offset = startoffset_Child_listOffset;

					uint32_t* listOffsetAltN_Child = (uint32_t*)GetOffsetPtr(buf, offset, true);

					for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
					{
						listOffsetAltN_Child[k] = val32(listOffsetAltN_Child[k]);

						isTextureArray.at(offset) = false;
						write_Coloration_Tag("offset_Child_SectionAltN", "uint32_t", " => 0x" + UnsignedToString(listRecusiveAltN.back(), true), offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
						
						if (listOffsetAltN_Child[k] == 0)
							continue;

						listRecusiveAltN.push_back(listOffsetAltN_Child[k] + hdr->offset_Section2);						
					}
				}
			}

		}

		



		//-----------------------  Anim :
		
		size_t nbAnim = listPointer_Anim.size();
		for (size_t inc_Anim = 0; inc_Anim < nbAnim; inc_Anim++)
		{
			size_t startSectionAnim = listPointer_Anim.at(inc_Anim);
			offset = startSectionAnim;

			incSection++;
			incParam = 0;

			SWR_Anim_Header* hdr_anim = (SWR_Anim_Header*)GetOffsetPtr(buf, offset, true);
			hdr_anim->nbKeyFrames = val32(hdr_anim->nbKeyFrames);
			hdr_anim->offset_times = val32(hdr_anim->offset_times);
			hdr_anim->offset_values = val32(hdr_anim->offset_values);
			hdr_anim->offset_AltN = val32(hdr_anim->offset_AltN);
			
			write_Coloration_Tag("unk0__0_To_60", "61 x uint32_t", "start of Anim. always 0", offset, 61 * sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += 61 * sizeof(uint32_t);
			write_Coloration_Tag("unk1_0", "float", "[0.0333329998, 240.0], 42.1666679 most. SOME the values offset is 0.0333, like if it's a diff time for 30 fps animations. [JayFoxRox:] unk1_ and unk5_ : Something to do with playback length; NOT a XYZ vector ", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk1_1", "float", "always the same value as unk1_X. it's a scale ? ", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk1_2", "float", "always the same value as unk1_X. it's a scale ? ", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk2", "uint8_t", "always 11.", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("unk3", "uint8_t", "always 0.", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("unk4", "uint8_t", "0 (most), 0x10", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("flags", "uint8_t", " with mask 0x0F, give the number of Components: 1, 0xB or 0xC => 1 component;  4 => 2 comp; 7, 9 or 0xA => 3 comp; 6 or 8 (most) => 4 comp;   5 => strange values instead of offset of values and objects.     0x12 give something strange.   with filter 0xF0, we have 0, 1, 2, or 3(most).", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("nbKeyFrames", "uint32_t", "", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("unk5_0", "float", "[0.0333329998, 240.0], 42.1666679 most. LOTS OF values offset is 0.0333, like if it's a diff time for 30 fps animations", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk5_1", "float", "always the same value as unk1_X.", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk5_2", "float", "always 1.0. [JayFoxRox:] Maybe playback rate / speed?", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk6", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("unk7", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			isTextureArray.at(offset) = false;
			write_Coloration_Tag("offset_times", "uint32_t", " => "+ UnsignedToString(hdr_anim->offset_times + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			isTextureArray.at(offset) = false;
			write_Coloration_Tag("offset_values", "uint32_t", " => " + UnsignedToString(hdr_anim->offset_values + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			isTextureArray.at(offset) = false;
			write_Coloration_Tag("offset_AltN", "uint32_t", "target the object at address => " + UnsignedToString(hdr_anim->offset_AltN + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("unk8", "uint32_t", "1 (most), 4, 5, 6, 0x22, 0x34, 0x3a.", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);

			if (hdr_anim->offset_times)
			{
				incSection++;
				incParam = 0;

				size_t startSectionAnim_Times = hdr_anim->offset_times + hdr->offset_Section2;
				offset = startSectionAnim_Times;

				float* values = (float*)GetOffsetPtr(buf, offset, true);
				for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
				{
					write_Coloration_Tag("timesValues", "float", "", offset, sizeof(float), "SWR_Anim_Times", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
				}
			}

			if (hdr_anim->offset_values)
			{
				incSection++;
				incParam = 0;

				size_t startSectionAnim_Values = hdr_anim->offset_values + hdr->offset_Section2;
				offset = startSectionAnim_Values;

				size_t nbComponents = 0;
				switch(hdr_anim->flags & 0x0F)
				{
				case 1: case 0xB: case 0xC:	nbComponents = 1; break;
				case 4:						nbComponents = 2; break;
				case 7: case 9: case 0xA:	nbComponents = 3; break;
				case 6: case 8:				nbComponents = 4; break;

				case 2:								//To anime a Section4, by replacing the Section5 + section5_b
				{
					offset = hdr_anim->offset_AltN + hdr->offset_Section2;
					SWR_Anim_Values_case2_Header* hdr_anim2 = (SWR_Anim_Values_case2_Header*)GetOffsetPtr(buf, offset, true);

					isTextureArray.at(offset) = false;
					write_Coloration_Tag("offset_section4", "uint32_t", " => "+ UnsignedToString(val32(hdr_anim2->offset_section4) + hdr->offset_Section2, true) , offset, sizeof(uint32_t), "SWR_Anim_Values_case2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
					isTextureArray.at(offset) = false;
					write_Coloration_Tag("unk0", "uint32_t", " always 0", offset, sizeof(uint32_t), "SWR_Anim_Values_case2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

					incSection++;
					incParam = 0;

					offset = hdr_anim->offset_values + hdr->offset_Section2;

					uint32_t* listOffset = (uint32_t*)GetOffsetPtr(buf, offset, true);
					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("offset_sectionAnim2", "uint32_t", " => " + UnsignedToString(val32(listOffset[j]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Values_case2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
					}

					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						size_t startoffset_section5 = val32(listOffset[j]) + hdr->offset_Section2;
						offset = startoffset_section5;


						//notice: it's possible (specially on the first and last keyframe) that the offset reference to original Section5.
						if (checkDuplication(offset, listToAvoidDuplication))
							continue;
						listToAvoidDuplication.push_back(offset);

						incSection++;
						incParam = 0;


						SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("unk0", "uint32_t", "0, 1 (most), 0x41, 0x49", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk4", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0xfc, 0x100 (most), 0x128, 0x138, 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk6", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0x8c, 0xb8, 0xbc, 0x100 (most), 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk8_0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk8_1", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk12", "uint8_t", "0, 2 (most), 4, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk13", "uint8_t", "0 (most), 1, 3, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk14_0", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk14_1", "uint8_t", "0 (most), 4", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk16", "uint16_t", "4, 8, 0x10, 0x20, 0x3f, 0x40 (most), 0x4a, 0x4e, 0x80. look like flgas", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk18", "uint16_t", "0x4, 0x8, 0x10, 0x20, 0x23, 0x2e, 0x2f, 0x40 (most), 0x80. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk20", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x7e00, 0x8000 (most), 0x9400, 0x9c00. todo splitted uint8", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk22", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x4600, 0x5c00, 0x5e00, 0x8000 (most)", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk24", "uint16_t", "0x0, 0x40, 0x80, 0x100, 0x200 (most), 0x2ab, 0x400, 0x800", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk26", "uint16_t", "0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x16f, 0x1f7, 0x1ff, 0x2aa, 0x365, 0x3ff (most), 0x7ff, 0xd78f", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("offset_Section5_b_0", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[0]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("offset_Section5_b_1", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[1]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("offset_Section5_b_2", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[2]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("offset_Section5_b_3", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[3]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("offset_Section5_b_4", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[4]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk48", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("unk52", "uint32_t", "always 0. the TextureFlags some of unk52 as havingTexture. So unk52 (and may be also unk48) could be offset_Section5_b_X, or as textureMaskAndIndex (but never used in practice).", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						bool haveTexture = isTextureArray.at(offset);
						isTextureArray.at(offset) = false;
						write_Coloration_Tag("textureMaskAndIndex", "uint32_t", string(" mask is on 0xFF000000. ")+ (haveTexture ? "haveTexture" : ""), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk60", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);

						for (size_t m = 0; m < 5; m++)
						{
							if (!section5->offset_Section5_b[m])
								continue;

							if (checkDuplication(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2, listToAvoidDuplication))
								continue;

							listToAvoidDuplication.push_back(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2);

							incSection++;
							incParam = 0;

							size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
							offset = startoffset_section5_b;

							SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

							write_Coloration_Tag("unk0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk2", "uint8_t", "1, 2, 4 (most), 5, 8, 0x10. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk3", "uint8_t", "it's 2 uint4: 0 (most), 1, 2.  and for the second (right) 0(most), 1, 2", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk4", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk5", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk6_a", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk6_b", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk8", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
							write_Coloration_Tag("unk12", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0xfc (most), 0x124, 0x134, 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk14", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0x88, 0xb8, 0xfc (most), 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						}
					}
				}

				case 5:
				{
					//I think the case 5 use splines animations : offset_values and offset_AltN may be are offset for the spline. Todo check

					::printf("Anim flag 5 (nbKf: %d) offset for spline ? offVal : %s, offAlt: %s. skipped.\n", hdr_anim->nbKeyFrames, UnsignedToString(hdr_anim->offset_values, true).c_str(), UnsignedToString(hdr_anim->offset_AltN, true).c_str());
					notifyWarning();

				}break;

				default:
				{
					::printf("Warning: Unknowed animation flags for component %s. skipped.\n", UnsignedToString(hdr_anim->flags, true).c_str());
					notifyWarning();
				}break;
				}



				if (nbComponents != 0)
				{
					float* values = (float*)GetOffsetPtr(buf, offset, true);
					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						if (nbComponents != 4)
						{
							write_Coloration_Tag(string("Value") + ((nbComponents != 1) ? "_X" : ""), "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							if (nbComponents > 1)
							{
								write_Coloration_Tag("Value_Y", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							}
							if (nbComponents > 2)
							{
								write_Coloration_Tag("Value_Z", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							}

						}
						else {			//apparently it's Axis + Angle
							write_Coloration_Tag("Value_X", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							write_Coloration_Tag("Value_Y", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							write_Coloration_Tag("Value_Z", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							write_Coloration_Tag("Value_Angle", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
						}
					}
				}
			}
		}



	}

	write_Coloration_Tag("Offset_EndOfFile", "uint32_t", " to have Section2 size of the last Model.", startoffsetModelHeader + nbModels * sizeof(SWR_MODELHeader), sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, 0, 0, listBytesAllreadyTagged);




	//here we will test if all bytes of Sectio2 tagged HaveTexture are all used
	incSection++;
	incParam = 0;

	for(size_t i=0;i<size;i+=4)
	{
		if(isTextureArray.at(i))
			write_Coloration_Tag("TEXTURE_NOT_USED", "uint32_t", UnsignedToString(i, true), i, sizeof(uint32_t), "SWR_TextureCheck", parent, idTag++, 0, 0, listBytesAllreadyTagged, 0, false);
	}



	write_Coloration_Gaps(0x0, (size_t)-1,  sizeof(uint32_t) + sizeof(uint16_t), idTag, "Empty", parent, listBytesAllreadyTagged);		//test Empty/gaps/holes.
}





/*-------------------------------------------------------------------------------\
|                             write_Coloration_Tag			                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Coloration_Tag(string paramName, string paramType, string paramComment, size_t startOffset, size_t size, string sectionName, TiXmlElement* parent, size_t idTag, size_t sectionIndex, size_t paramIndex, std::vector<size_t> &listBytesAllreadyTagged, size_t sectionIndexInList, bool checkAllreadyTaggued)
{
	TiXmlElement* tag_node = new TiXmlElement("TAG");

	tag_node->SetAttribute("id", UnsignedToString(idTag, false));


	TiXmlElement* start_offset_node = new TiXmlElement("start_offset");
	TiXmlText* text = new TiXmlText(std::to_string(startOffset));
	start_offset_node->LinkEndChild(text);
	tag_node->LinkEndChild(start_offset_node);

	TiXmlElement* end_offset_node = new TiXmlElement("end_offset");
	text = new TiXmlText(std::to_string(startOffset + size - 1));
	end_offset_node->LinkEndChild(text);
	tag_node->LinkEndChild(end_offset_node);

	TiXmlElement* text_node = new TiXmlElement("tag_text");
	text = new TiXmlText(sectionName + ((sectionIndexInList != (size_t)-1) ? "[" + std::to_string(sectionIndexInList) + "]" : "") + "." + paramName + " (" + paramType + ") : " + paramComment);
	text_node->LinkEndChild(text);
	tag_node->LinkEndChild(text_node);





	if (listTagColors.size() == 0)
	{
		listTagColors.push_back(std::vector<std::vector<string>>());
		listTagColors.back().push_back(std::vector<string>());
		listTagColors.back().back().push_back("#000000");			//background color
		listTagColors.back().back().push_back("#FFFFFF");			//font color (just to possibility read from background color)
	}

	size_t sectionIndex_tmp = sectionIndex % listTagColors.size();
	std::vector<std::vector<string>> &sectionColorlist = listTagColors.at(sectionIndex_tmp);
	size_t paramIndex_tmp = paramIndex % sectionColorlist.size();
	std::vector<string> &paramColors = sectionColorlist.at(paramIndex_tmp);

	TiXmlElement* font_colour_node = new TiXmlElement("font_colour");
	text = new TiXmlText(paramColors.at(1));
	font_colour_node->LinkEndChild(text);
	tag_node->LinkEndChild(font_colour_node);

	TiXmlElement* bg_colour_node = new TiXmlElement("note_colour");
	text = new TiXmlText(paramColors.at(0));
	bg_colour_node->LinkEndChild(text);
	tag_node->LinkEndChild(bg_colour_node);

	parent->LinkEndChild(tag_node);




	//un check d'overide , pour savoir si des blocks se chevauche.
	size_t index;
	size_t limit = listBytesAllreadyTagged.size();
	for (size_t i = 0; i < size; i++)
	{
		index = startOffset + i;
		if (index >= limit)
		{
			::printf("Error on tagID %i : overflow %s >= %s.\n", idTag, UnsignedToString(index, true).c_str(), UnsignedToString(limit, true).c_str());
			notifyError();
			throw("overflow");
			continue;
		}

		if ((checkAllreadyTaggued) && (listBytesAllreadyTagged.at(index)!=-1))
		{
			::printf("warning on tagID %i : the byte %s allready taggued, may be a overflow between blocks (tag: %i). Infos : %s. \n", idTag, UnsignedToString(index, true).c_str(), listBytesAllreadyTagged.at(index), (sectionName + ((sectionIndexInList != (size_t)-1) ? "[" + std::to_string(sectionIndexInList) + "]" : "") + "." + paramName + " (" + paramType + ") : " + paramComment).c_str());
			notifyError();
			throw("overide Byte");
		}

		listBytesAllreadyTagged.at(index) = idTag;
	}
}




/*-------------------------------------------------------------------------------\
|                             write_Coloration_Gaps			                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Coloration_Gaps(size_t startOffsetToConsidere, size_t endOffsetToConsidere, size_t sizeFilter, size_t start_idTag, string sectionName, TiXmlElement* parent, std::vector<size_t> &listBytesAllreadyTagged)
{
	size_t nbBytes = listBytesAllreadyTagged.size();
	if ((nbBytes == 0) || (startOffsetToConsidere >= nbBytes) || (startOffsetToConsidere > endOffsetToConsidere))
		return;

	if (endOffsetToConsidere >= nbBytes)
		endOffsetToConsidere = nbBytes - 1;


	size_t sectionStart = (size_t)-1;
	size_t inc = 0;
	bool isByteTagged = false;
	for (size_t i = startOffsetToConsidere; i <= endOffsetToConsidere; i++)			//detection of the Hole
	{
		isByteTagged = listBytesAllreadyTagged.at(i) != (size_t)-1;

		if ((!isByteTagged) && (sectionStart == (size_t)-1))
		{
			sectionStart = i;

		}else if (((isByteTagged) || (i == endOffsetToConsidere)) && (sectionStart != (size_t)-1)) {		//if end of Section, or end of range.

			size_t size = i - sectionStart;

			if (size > sizeFilter)
			{
				TiXmlElement* tag_node = new TiXmlElement("TAG");

				tag_node->SetAttribute("id", UnsignedToString(start_idTag++, false));


				TiXmlElement* start_offset_node = new TiXmlElement("start_offset");
				TiXmlText* text = new TiXmlText(std::to_string(sectionStart));
				start_offset_node->LinkEndChild(text);
				tag_node->LinkEndChild(start_offset_node);

				start_offset_node = new TiXmlElement("start_offset_Hexa");
				text = new TiXmlText(UnsignedToString(sectionStart, true));
				start_offset_node->LinkEndChild(text);
				tag_node->LinkEndChild(start_offset_node);

				TiXmlElement* end_offset_node = new TiXmlElement("end_offset");
				text = new TiXmlText(std::to_string(sectionStart + size - 1));
				end_offset_node->LinkEndChild(text);
				tag_node->LinkEndChild(end_offset_node);

				TiXmlElement* text_node = new TiXmlElement("tag_text");
				text = new TiXmlText(sectionName + "[" + std::to_string(inc++) + "]. Size=" + std::to_string(size));
				text_node->LinkEndChild(text);
				tag_node->LinkEndChild(text_node);

				TiXmlElement* font_colour_node = new TiXmlElement("font_colour");
				text = new TiXmlText("#000000");
				font_colour_node->LinkEndChild(text);
				tag_node->LinkEndChild(font_colour_node);

				TiXmlElement* bg_colour_node = new TiXmlElement("note_colour");
				text = new TiXmlText("#FF0000");
				bg_colour_node->LinkEndChild(text);
				tag_node->LinkEndChild(bg_colour_node);

				parent->LinkEndChild(tag_node);
			}

			sectionStart = (size_t)-1;
		}
	}
}

/*-------------------------------------------------------------------------------\
|                             checkDuplication				                     |
\-------------------------------------------------------------------------------*/
bool Swr_Model::checkDuplication(size_t offset, std::vector<size_t> &listToAvoidDuplication)
{
	size_t nbElement = listToAvoidDuplication.size();
	for (size_t i = 0; i < nbElement; i++)
		if (listToAvoidDuplication.at(i) == offset)
			return true;
	return false;
};


/*-------------------------------------------------------------------------------\
|                             checkDuplication				                     |
\-------------------------------------------------------------------------------*/
bool Swr_Model::checkDuplication_Malt_recursion(size_t offset, std::vector<size_t> &listToAvoidDuplication, const uint8_t *buf, size_t size, size_t offset_Section2)
{
	//first, we try with only offset allready put in the list.
	size_t nbElement = listToAvoidDuplication.size();
	for (size_t i = 0; i < nbElement; i++)
		if (listToAvoidDuplication.at(i) == offset)
			return true;


	//but now, we will make a new list with all Malt child offset.
	std::vector<size_t> listChildOffset;
	for (size_t i = 0; i < nbElement; i++)
		listChildOffset.push_back(listToAvoidDuplication.at(i));

	SWR_AltN_Header* hdr_AltN;
	for (size_t i = 0; i < listChildOffset.size(); i++)
	{
		if (listChildOffset.at(i) == offset)
			return true;

		hdr_AltN = (SWR_AltN_Header*)(buf + listChildOffset.at(i));

		if ((val32(hdr_AltN->flags) & 0x4000) && (val32(hdr_AltN->offset_Childs)))				// 0x5xxx or 0xDxxxx (for 0x3xxx the child are struct_V16)
		{
			size_t startoffset_Child_listOffset = val32(hdr_AltN->offset_Childs) + offset_Section2;
			uint32_t* listOffsetAltN_Child = (uint32_t*)GetOffsetPtr(buf, startoffset_Child_listOffset, true);

			size_t nbChilds = val32(hdr_AltN->nb_Childs);
			size_t offset_tmp;
			for (size_t k = 0; k < nbChilds; k++)
			{
				offset_tmp = val32(listOffsetAltN_Child[k]);
				if (offset_tmp == 0)
					continue;

				listChildOffset.push_back(offset_tmp + offset_Section2);
			}
		}

	}

	return false;
};

