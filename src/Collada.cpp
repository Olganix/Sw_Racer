
#include "Collada.h"

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
	node_library_cameras = node_library_lights = node_library_images = node_library_effects = node_library_materials = 0;
	
	
	doc = new TiXmlDocument();
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc->LinkEndChild(decl);

	root = new TiXmlElement("COLLADA");
	doc->LinkEndChild(root);
	root->SetAttribute("xmlns", "http://www.collada.org/2005/11/COLLADASchema");
	root->SetAttribute("version", "1.4.1");

	TiXmlElement* node_asset = new TiXmlElement("asset");
	root->LinkEndChild(node_asset);


	
	TiXmlElement* node_contributor = new TiXmlElement("contributor");
	node_asset->LinkEndChild(node_contributor);

	TiXmlElement* node_author = new TiXmlElement("author");
	node_contributor->LinkEndChild(node_author);
	node_author->LinkEndChild(new TiXmlText("Olganix, JayFoxRox"));

	TiXmlElement* node_authoring_tool = new TiXmlElement("authoring_tool");
	node_contributor->LinkEndChild(node_authoring_tool);
	node_authoring_tool->LinkEndChild(new TiXmlText("Swr_Racer"));

	TiXmlElement* node_source_data = new TiXmlElement("source_data");
	node_contributor->LinkEndChild(node_source_data);
	node_source_data->LinkEndChild(new TiXmlText("https://github.com/Olganix/Sw_Racer"));


	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%dT%I:%M:%S", timeinfo);
	std::string str(buffer);


	TiXmlElement* node_created = new TiXmlElement("created");
	node_asset->LinkEndChild(node_created);
	node_created->LinkEndChild(new TiXmlText(str));

	TiXmlElement* node_modified = new TiXmlElement("modified");
	node_asset->LinkEndChild(node_modified);
	node_modified->LinkEndChild(new TiXmlText(str));

	TiXmlElement* node_unit = new TiXmlElement("unit");
	node_asset->LinkEndChild(node_unit);
	node_unit->SetAttribute("meter", "0.01");
	node_unit->SetAttribute("name", "centimeter");

	TiXmlElement* node_up_axis = new TiXmlElement("up_axis");
	node_asset->LinkEndChild(node_up_axis);
	node_up_axis->LinkEndChild(new TiXmlText("Z_UP"));



	node_geometries = new TiXmlElement("library_geometries");
	root->LinkEndChild(node_geometries);

	node_library_visual_scenes = new TiXmlElement("library_visual_scenes");
	root->LinkEndChild(node_library_visual_scenes);


	node_visual_scene = new TiXmlElement("visual_scene");
	node_library_visual_scenes->LinkEndChild(node_visual_scene);
	node_visual_scene->SetAttribute("id", "VisualSceneNode");
	node_visual_scene->SetAttribute("name", "untitled");


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
	bool haveNormal = vertices.at(0).flags & EMD_VTX_FLAG_NORM;
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


	/////////////////////////////////////////////////////



	if (haveNormal)
	{
		TiXmlElement* node_source = new TiXmlElement("source");
		node_mesh->LinkEndChild(node_source);
		node_source->SetAttribute("id", name + "_normals");
		node_source->SetAttribute("name", name + "_normals");

		TiXmlElement* node_listFloat = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_listFloat);
		node_listFloat->SetAttribute("id", name + "_normals_floats");
		node_listFloat->SetAttribute("count", nbVertex * 3);
		str = "";
		for (size_t i = 0; i < nbVertex; i++)
		{
			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString(vertices.at(i).norm_x);
			str += " " + EMO_BaseFile::FloatToString(vertices.at(i).norm_y);
			str += " " + EMO_BaseFile::FloatToString(vertices.at(i).norm_z);
		}
		node_listFloat->LinkEndChild(new TiXmlText(str));

		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbVertex);
		node_accessor->SetAttribute("offset", "0");
		node_accessor->SetAttribute("source", "#" + name + "_normals_floats");
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

	if (havePosition)
	{
		TiXmlElement * node_input = new TiXmlElement("input");
		node_vertices->LinkEndChild(node_input);
		node_input->SetAttribute("semantic", "POSITION");
		node_input->SetAttribute("source", "#" + name + "_positions");
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

		if (haveNormal)
		{
			TiXmlElement* node_input = new TiXmlElement("input");
			node_polylist->LinkEndChild(node_input);
			node_input->SetAttribute("offset", "0");
			node_input->SetAttribute("semantic", "NORMAL");
			node_input->SetAttribute("set", "0");
			node_input->SetAttribute("source", "#" + name + "_normal");
		}
		
		if (haveUv)
		{
			TiXmlElement* node_input = new TiXmlElement("input");
			node_polylist->LinkEndChild(node_input);
			node_input->SetAttribute("offset", "0");
			node_input->SetAttribute("semantic", "TEXCOORD");
			node_input->SetAttribute("set", "0");
			node_input->SetAttribute("source", "#" + name + "_uv");
		}

		/*
		if (haveColor)
		{
			TiXmlElement* node_input = new TiXmlElement("input");
			node_polylist->LinkEndChild(node_input);
			node_input->SetAttribute("semantic", "COLOR");
			node_input->SetAttribute("offset", "0");
			node_input->SetAttribute("set", "0");
			node_input->SetAttribute("source", "#" + name + "_color");
		}
		*/

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

	addImage(name + "_texture", filename);
	addEffect(name, true, name + "_texture");
	addMaterial(name, name + "_effect");
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
	addMaterial(name, name + "_effect");
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
	checkRootFor("library_images");
	
	TiXmlElement* node_image = new TiXmlElement("image");
	node_library_images->LinkEndChild(node_image);
	node_image->SetAttribute("id", name);
	node_image->SetAttribute("name", name);
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
	checkRootFor("library_effects");

	TiXmlElement* node_effect = new TiXmlElement("effect");
	node_library_effects->LinkEndChild(node_effect);
	node_effect->SetAttribute("id", name +"_effect");

	TiXmlElement* node_profile_COMMON = new TiXmlElement("profile_COMMON");
	node_effect->LinkEndChild(node_profile_COMMON);

	if (isSampler2D)
	{

		TiXmlElement* node_newparam = new TiXmlElement("newparam");
		node_profile_COMMON->LinkEndChild(node_newparam);
		node_newparam->SetAttribute("sid", name + "_surface");

		TiXmlElement* node_surface = new TiXmlElement("surface");
		node_newparam->LinkEndChild(node_surface);
		node_surface->SetAttribute("type", "2D");

		TiXmlElement* node_init_from = new TiXmlElement("init_from");
		node_surface->LinkEndChild(node_init_from);
		node_init_from->LinkEndChild(new TiXmlText(name +"_texture"));


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

	}

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
	node_float->LinkEndChild(new TiXmlText("50"));

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
	checkRootFor("library_materials");

	TiXmlElement* node_material = new TiXmlElement("material");
	node_library_materials->LinkEndChild(node_material);
	node_material->SetAttribute("id", name);
	node_material->SetAttribute("name", name);

	TiXmlElement* node_instance_effect = new TiXmlElement("instance_effect");
	node_material->LinkEndChild(node_instance_effect);
	node_instance_effect->SetAttribute("url", "#" + nameEffect);
}
/*-------------------------------------------------------------------------------\
|                             checkRootFor										 |
\-------------------------------------------------------------------------------*/
void Collada::checkRootFor(string tagName)
{
	//the problem is the validator don't like to have empty library-xxxxx. So we have to add them if necessary.

	if (tagName == "library_images")
	{
		if (!node_library_images)
		{
			node_library_images = new TiXmlElement("library_images");
			root->LinkEndChild(node_library_images);
		}
		return;
	}
	if (tagName == "library_effects")
	{
		if (!node_library_effects)
		{
			node_library_effects = new TiXmlElement("library_effects");
			root->LinkEndChild(node_library_effects);
		}
		return;
	}
	if (tagName == "library_materials")
	{
		if (!node_library_materials)
		{
			node_library_materials = new TiXmlElement("library_materials");
			root->LinkEndChild(node_library_materials);
		}
		return;
	}
	if (tagName == "library_cameras")
	{
		if (!node_library_cameras)
		{
			node_library_cameras = new TiXmlElement("library_cameras");
			root->LinkEndChild(node_library_cameras);
		}
		return;
	}
	if (tagName == "library_lights")
	{
		if (!node_library_lights)
		{
			node_library_lights = new TiXmlElement("library_lights");
			root->LinkEndChild(node_library_lights);
		}
		return;
	}
	if (tagName == "library_animations")
	{
		if (!node_library_animations)
		{
			node_library_animations = new TiXmlElement("library_animations");
			root->LinkEndChild(node_library_animations);
		}
		return;
	}
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
	/////////////////////////////////////////////////////


	TiXmlElement* node_library_animations = new TiXmlElement("library_animations");
	root->LinkEndChild(node_library_animations);


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

}
*/

