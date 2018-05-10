#include <math.h>

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
|                             ColladaKeyframe									 |
\-------------------------------------------------------------------------------*/
ColladaKeyframe::ColladaKeyframe(float time, float x, float y, float z, float w)
{
	this->time = time;
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
/*-------------------------------------------------------------------------------\
|                             ColladaAnimation									 |
\-------------------------------------------------------------------------------*/
ColladaAnimation::ColladaAnimation(string targetId, AnimationType type, float duration)
{
	this->targetId = targetId;
	this->type = type;
	this->duration = duration;
}
/*-------------------------------------------------------------------------------\
|                             getInterpolateKeyFrame_Quaternion					 |
\-------------------------------------------------------------------------------*/
ColladaKeyframe ColladaAnimation::getInterpolateKeyFrame_Quaternion(double time)
{
	ColladaKeyframe currentKf;

	size_t nbKf = listKeyFrames.size();
	if (nbKf == 0)											//little check.
		return currentKf;
	if ((nbKf == 1)||(time <= listKeyFrames.at(0).time))
		return listKeyFrames.at(0);
	if (time >= listKeyFrames.back().time)
		return listKeyFrames.back();


	for (size_t i = 0; i < nbKf; i++)
	{
		if (time == listKeyFrames.at(i).time)
			return listKeyFrames.at(i);
		
		if (time < listKeyFrames.at(i).time)
		{
			ColladaKeyframe &previousKf = listKeyFrames.at(i - 1);
			ColladaKeyframe &nextKf = listKeyFrames.at(i);
			Quaternion prevQuad(previousKf.x, previousKf.y, previousKf.z, previousKf.w);
			Quaternion nextQuad(nextKf.x, nextKf.y, nextKf.z, nextKf.w);

			double factor = (time - previousKf.time) / (nextKf.time - previousKf.time);

			Quaternion currentQuad = Slerp(factor, prevQuad, nextQuad, true);
			//Quaternion currentQuad = Slerp(factor, prevQuad, nextQuad, false);
			currentKf.x = (float)currentQuad.x;
			currentKf.y = (float)currentQuad.y;
			currentKf.z = (float)currentQuad.z;
			currentKf.w = (float)currentQuad.w;

			return currentKf;
		}
	}


	return currentKf;
}
 












/*-------------------------------------------------------------------------------\
|                             Collada											 |
\-------------------------------------------------------------------------------*/
Collada::Collada()
{
	node_library_cameras = node_library_lights = node_library_images = node_library_effects = node_library_materials = node_library_animations = 0;
	doc = 0;

	node_geometries = new TiXmlElement("library_geometries");
	node_library_visual_scenes = new TiXmlElement("library_visual_scenes");

	node_visual_scene = new TiXmlElement("visual_scene");
	node_library_visual_scenes->LinkEndChild(node_visual_scene);
	node_visual_scene->SetAttribute("id", "VisualSceneNode");
	node_visual_scene->SetAttribute("name", "untitled");


	node_scene = new TiXmlElement("scene");

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
	addEffect(name, true, name);
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
TiXmlElement* Collada::createNode(string name, TiXmlElement* parentNode, Vector3 position, Vector3 rotationAngles, string instanceGeometryName, string materialName, bool haveTexture, Common::Vector3 scale)
{
	if (!parentNode)
		parentNode = node_visual_scene;

	
	TiXmlElement* node = new TiXmlElement("node");
	parentNode->LinkEndChild(node);
	node->SetAttribute("id", name);
	node->SetAttribute("name", name);

	addTransformOnNode(node, position, rotationAngles, scale);

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
void Collada::addTransformOnNode(TiXmlElement* node, Common::Vector3 position, Common::Vector3 rotationAngles, Common::Vector3 scale)
{
	TiXmlElement* node_translate = node->FirstChildElement("translate");
	if (!node_translate)
	{
		node_translate = new TiXmlElement("translate");
		node->LinkEndChild(node_translate);
	}

	node_translate->SetAttribute("sid", "transl");
	TiXmlText* text =(TiXmlText*)node_translate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_translate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString((float)position.x) + " " + EMO_BaseFile::FloatToString((float)position.y) + " " + EMO_BaseFile::FloatToString((float)position.z));


	////////////////////////////////////////////
	/*

	///
	TiXmlElement* node_rotate = node->FirstChildElement("rotate");
	if (!node_rotate)
	{
		node_rotate = new TiXmlElement("rotate");
		node->LinkEndChild(node_rotate);
	}

	node_rotate->SetAttribute("sid", "rotateZ");
	text = (TiXmlText*)node_rotate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_rotate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(1) + " " + EMO_BaseFile::FloatToString((float)rotationAngles.x));		//yaw

	///
	node_rotate = node_rotate->NextSiblingElement("rotate");
	if (!node_rotate)
	{
		node_rotate = new TiXmlElement("rotate");
		node->LinkEndChild(node_rotate);
	}

	node_rotate->SetAttribute("sid", "rotateY");
	text = (TiXmlText*)node_rotate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_rotate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(1) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString((float)rotationAngles.y));			//pitch

	
	

	///
	node_rotate = node_rotate->NextSiblingElement("rotate");
	if (!node_rotate)
	{
		node_rotate = new TiXmlElement("rotate");
		node->LinkEndChild(node_rotate);
	}

	node_rotate->SetAttribute("sid", "rotateX");
	text = (TiXmlText*)node_rotate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_rotate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(1) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString((float)rotationAngles.z));			//Roll
	


	*/
	
	///
	TiXmlElement* node_rotate = node->FirstChildElement("rotate");
	
	if (!node_rotate)
	{
		node_rotate = new TiXmlElement("rotate");
		node->LinkEndChild(node_rotate);
	}

	node_rotate->SetAttribute("sid", "rotateX");
	text = (TiXmlText*)node_rotate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_rotate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(1) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString((float)rotationAngles.z));			//Roll


																																																	///
	node_rotate = node_rotate->NextSiblingElement("rotate");
	if (!node_rotate)
	{
		node_rotate = new TiXmlElement("rotate");
		node->LinkEndChild(node_rotate);
	}

	node_rotate->SetAttribute("sid", "rotateY");
	text = (TiXmlText*)node_rotate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_rotate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(1) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString((float)rotationAngles.y));			//pitch

	

	///
	node_rotate = node_rotate->NextSiblingElement("rotate");
	if (!node_rotate)
	{
		node_rotate = new TiXmlElement("rotate");
		node->LinkEndChild(node_rotate);
	}
	node_rotate->SetAttribute("sid", "rotateZ");
	text = (TiXmlText*)node_rotate->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_rotate->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(0) + " " + EMO_BaseFile::FloatToString(1) + " " + EMO_BaseFile::FloatToString((float)rotationAngles.x));		//yaw		

	
																																																	
																																																	
	////////////////////////////////////


	TiXmlElement* node_scale = node->FirstChildElement("scale");
	if (!node_scale)
	{
		node_scale = new TiXmlElement("scale");
		node->LinkEndChild(node_scale);
	}

	node_scale->SetAttribute("sid", "scale");
	text = (TiXmlText*)node_scale->FirstChild();
	if (!text)
	{
		text = new TiXmlText("");
		node_scale->LinkEndChild(text);
	}
	text->SetValue(EMO_BaseFile::FloatToString((float)scale.x) + " " + EMO_BaseFile::FloatToString((float)scale.y) + " " + EMO_BaseFile::FloatToString((float)scale.z));

}
/*-------------------------------------------------------------------------------\
|                             addImage											 |
\-------------------------------------------------------------------------------*/
void Collada::addImage(string name, string filename)
{
	checkRootFor("library_images");
	
	size_t nbMat = listTextureNames.size();
	for (size_t i = 0; i < nbMat; i++)						//avoid duplications
		if (listTextureNames.at(i) == name)
			return;
	listTextureNames.push_back(name);


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

	size_t nbMat = listEffects.size();
	for (size_t i = 0; i < nbMat; i++)						//avoid duplications
		if (listEffects.at(i).name == name)
			return;
	listEffects.push_back(Effect(name));


	TiXmlElement* node_effect = new TiXmlElement("effect");
	node_library_effects->LinkEndChild(node_effect);
	node_effect->SetAttribute("id", name +"_effect");

	listEffects.back().node_effect = node_effect;

	TiXmlElement* node_profile_COMMON = new TiXmlElement("profile_COMMON");
	node_effect->LinkEndChild(node_profile_COMMON);
	listEffects.back().node_profile_COMMON = node_profile_COMMON;



	if (isSampler2D)
		addEffectSampler2D(listEffects.at(listEffects.size() - 1), nameTexture);



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
	node_diffuse->SetAttribute("sid", name + "_effect_diffuse");
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
	node_transparency->SetAttribute("sid", name + "_transparency");
	node_float = new TiXmlElement("float");
	node_transparency->LinkEndChild(node_float);
	node_float->SetAttribute("sid", "float");
	node_float->LinkEndChild(new TiXmlText("1"));

	TiXmlElement* node_index_of_refraction = new TiXmlElement("index_of_refraction");
	node_blinn->LinkEndChild(node_index_of_refraction);
	node_float = new TiXmlElement("float");
	node_index_of_refraction->LinkEndChild(node_float);
	node_float->LinkEndChild(new TiXmlText("1"));
}

/*-------------------------------------------------------------------------------\
|                             addEffectSampler2D								 |
\-------------------------------------------------------------------------------*/
void Collada::addEffectSampler2D(string name, string nameTexture)
{
	size_t nbMat = listEffects.size();
	for (size_t i = 0; i < nbMat; i++)
		if (listEffects.at(i).name == name)
			return addEffectSampler2D(listEffects.at(i), nameTexture);
}
/*-------------------------------------------------------------------------------\
|                             addEffectSampler2D								 |
\-------------------------------------------------------------------------------*/
void Collada::addEffectSampler2D(Effect &effect, string nameTexture)
{
	size_t nbMat = effect.listImageIdName.size();
	for (size_t i = 0; i < nbMat; i++)						//avoid duplications
		if (effect.listImageIdName.at(i) == nameTexture)
			return;
	effect.listImageIdName.push_back(nameTexture);



	TiXmlElement* node_newparam = new TiXmlElement("newparam");
	effect.node_profile_COMMON->LinkEndChild(node_newparam);
	node_newparam->SetAttribute("sid", nameTexture + "_surface");

	TiXmlElement* node_surface = new TiXmlElement("surface");
	node_newparam->LinkEndChild(node_surface);
	node_surface->SetAttribute("type", "2D");

	TiXmlElement* node_init_from = new TiXmlElement("init_from");
	node_surface->LinkEndChild(node_init_from);
	node_init_from->LinkEndChild(new TiXmlText(nameTexture + "_texture"));


	///////////////


	node_newparam = new TiXmlElement("newparam");
	effect.node_profile_COMMON->LinkEndChild(node_newparam);
	node_newparam->SetAttribute("sid", nameTexture + "_sampler");

	TiXmlElement* node_sampler2D = new TiXmlElement("sampler2D");
	node_newparam->LinkEndChild(node_sampler2D);

	TiXmlElement* node_source = new TiXmlElement("source");
	node_sampler2D->LinkEndChild(node_source);
	node_source->LinkEndChild(new TiXmlText(nameTexture + "_surface"));

	TiXmlElement* node_minfilter = new TiXmlElement("minfilter");
	node_sampler2D->LinkEndChild(node_minfilter);
	node_minfilter->LinkEndChild(new TiXmlText("LINEAR_MIPMAP_LINEAR"));

	TiXmlElement* node_magfilter = new TiXmlElement("magfilter");
	node_sampler2D->LinkEndChild(node_magfilter);
	node_magfilter->LinkEndChild(new TiXmlText("LINEAR"));
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
		}
		return;
	}
	if (tagName == "library_effects")
	{
		if (!node_library_effects)
		{
			node_library_effects = new TiXmlElement("library_effects");
		}
		return;
	}
	if (tagName == "library_materials")
	{
		if (!node_library_materials)
		{
			node_library_materials = new TiXmlElement("library_materials");
		}
		return;
	}
	if (tagName == "library_cameras")
	{
		if (!node_library_cameras)
		{
			node_library_cameras = new TiXmlElement("library_cameras");
		}
		return;
	}
	if (tagName == "library_lights")
	{
		if (!node_library_lights)
		{
			node_library_lights = new TiXmlElement("library_lights");
		}
		return;
	}
	if (tagName == "library_animations")
	{
		if (!node_library_animations)
		{
			node_library_animations = new TiXmlElement("library_animations");
		}
		return;
	}
}

/*-------------------------------------------------------------------------------\
|                             save												 |
\-------------------------------------------------------------------------------*/
void Collada::save(string filename)
{
	if (!doc)								// Collada validator want to have things in the good order, and no empty library. As tinyXml can't insert properly a node before another .... we have to link , at the end , so here.
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


		if (node_library_cameras)
			root->LinkEndChild(node_library_cameras);
		if (node_library_lights)
			root->LinkEndChild(node_library_lights);
		if (node_library_images)
			root->LinkEndChild(node_library_images);
		if (node_library_effects)
			root->LinkEndChild(node_library_effects);
		if (node_library_materials)
			root->LinkEndChild(node_library_materials);

		root->LinkEndChild(node_geometries);
		root->LinkEndChild(node_library_visual_scenes);

		if (node_library_animations)
			root->LinkEndChild(node_library_animations);

		root->LinkEndChild(node_scene);
	}
	

	doc->SaveFile(filename);
}



/*-------------------------------------------------------------------------------\
|                             addAnimation										 |
\-------------------------------------------------------------------------------*/
void Collada::addAnimation(ColladaAnimation &animation)
{
	checkRootFor("library_animations");

	
	string targetAnimType = "";
	size_t nbComponents = 0;
	switch (animation.type)
	{
	case ColladaAnimation::AT_Position: targetAnimType = "transl"; nbComponents = 3;  break;
	case ColladaAnimation::AT_Rotation: targetAnimType = "rotate";  nbComponents = 1; break;
	case ColladaAnimation::AT_Scale: targetAnimType = "scale";  nbComponents = 3; break;
	case ColladaAnimation::AT_TextureIndex: targetAnimType = "texture";  nbComponents = 1; break;
	case ColladaAnimation::AT_Transparence: targetAnimType = "float";  nbComponents = 4; break;
	case ColladaAnimation::AT_Transparency: targetAnimType = "float";  nbComponents = 1; break;
	default:
		return;
	}
	
	string animName = animation.targetId + "_anim_" + targetAnimType;
	size_t nbKeyFrames = animation.listKeyFrames.size();



	/////////////////////////////////////////////////////


	TiXmlElement* node_anim = new TiXmlElement("animation");
	node_library_animations->LinkEndChild(node_anim);
	node_anim->SetAttribute("id", animName);
	node_anim->SetAttribute("name", animName);




	/////////////////////////////////////////////////////

	TiXmlElement* node_source = new TiXmlElement("source");
	node_anim->LinkEndChild(node_source);
	node_source->SetAttribute("id", animName + "_times");

	TiXmlElement* node_floats = new TiXmlElement("float_array");
	node_source->LinkEndChild(node_floats);
	node_floats->SetAttribute("id", animName + "_times_floats");
	node_floats->SetAttribute("count", nbKeyFrames);
	string str = "";
	for (size_t i = 0; i < nbKeyFrames; i++)
		str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString(animation.listKeyFrames.at(i).time);
	node_floats->LinkEndChild(new TiXmlText(str));


	TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
	node_source->LinkEndChild(node_technique_common);

	TiXmlElement* node_accessor = new TiXmlElement("accessor");
	node_technique_common->LinkEndChild(node_accessor);
	node_accessor->SetAttribute("count", nbKeyFrames);
	node_accessor->SetAttribute("source", "#" + animName + "_times_floats");
	node_accessor->SetAttribute("stride", "1");

	TiXmlElement* node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("name", "TIME");
	node_param->SetAttribute("type", "float");


	/////////////////////////////////////////////////////



	

	



	switch (animation.type)
	{
	case ColladaAnimation::AT_Position:
	{	
		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values");
		
		TiXmlElement* node_floats = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_floats);
		node_floats->SetAttribute("id", animName + "_values_floats");
		node_floats->SetAttribute("count", nbKeyFrames * 3);
		str = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
		{
			ColladaKeyframe &kf = animation.listKeyFrames.at(i);

			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString(kf.x);
			str += " " + EMO_BaseFile::FloatToString(kf.y);
			str += " " + EMO_BaseFile::FloatToString(kf.z);
		}
		node_floats->LinkEndChild(new TiXmlText(str));


		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_floats");
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
	break;



	case ColladaAnimation::AT_Rotation:
	{
		std::vector<Vector3> listRotationAngle;
		for (size_t i = 0; i < nbKeyFrames; i++)
		{
			listRotationAngle.push_back(Vector3(animation.listKeyFrames.at(i).x, animation.listKeyFrames.at(i).y, animation.listKeyFrames.at(i).z));
			if (i == 0)
				continue;

			keepTaitBryanAnglesGood(listRotationAngle.at(i-1), listRotationAngle.at(i));			//correction to have better interpolations
		}



		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values_rotZ");

		TiXmlElement* node_floats = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_floats);
		node_floats->SetAttribute("id", animName + "_values_floats_rotZ");
		node_floats->SetAttribute("count", nbKeyFrames);
		str = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString((float)listRotationAngle.at(i).x);	//yaw
		node_floats->LinkEndChild(new TiXmlText(str));


		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_floats_rotZ");
		node_accessor->SetAttribute("stride", "1");

		TiXmlElement* node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "ANGLE");
		node_param->SetAttribute("type", "float");



		/////

		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values_rotY");

		node_floats = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_floats);
		node_floats->SetAttribute("id", animName + "_values_floats_rotY");
		node_floats->SetAttribute("count", nbKeyFrames);
		str = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString((float)listRotationAngle.at(i).y);		//Pitch
		node_floats->LinkEndChild(new TiXmlText(str));


		node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_floats_rotY");
		node_accessor->SetAttribute("stride", "1");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "ANGLE");
		node_param->SetAttribute("type", "float");

		/////

		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values_rotX");
		
		node_floats = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_floats);
		node_floats->SetAttribute("id", animName + "_values_floats_rotX");
		node_floats->SetAttribute("count", nbKeyFrames);
		str = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString((float)listRotationAngle.at(i).z);		//Roll
		node_floats->LinkEndChild(new TiXmlText(str));


		node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_floats_rotX");
		node_accessor->SetAttribute("stride", "1");

		node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("name", "ANGLE");
		node_param->SetAttribute("type", "float");

		

		
	}
	break;

	case ColladaAnimation::AT_Scale:
	{
		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values");
		
		TiXmlElement* node_floats = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_floats);
		node_floats->SetAttribute("id", animName + "_values_floats");
		node_floats->SetAttribute("count", nbKeyFrames * 3);
		str = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
		{
			ColladaKeyframe &kf = animation.listKeyFrames.at(i);

			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString(kf.x);
			str += " " + EMO_BaseFile::FloatToString(kf.y);
			str += " " + EMO_BaseFile::FloatToString(kf.z);
		}
		node_floats->LinkEndChild(new TiXmlText(str));


		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_floats");
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
	break;






	case ColladaAnimation::AT_TextureIndex:
	{
		
		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values");
		
		TiXmlElement* node_Name_array = new TiXmlElement("Name_array");
		node_source->LinkEndChild(node_Name_array);
		node_Name_array->SetAttribute("id", animName + "_values_array");
		node_Name_array->SetAttribute("count", nbKeyFrames * 3);
		str = "";
		string imageName = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
		{
			ColladaKeyframe &kf = animation.listKeyFrames.at(i);
			imageName = ((((size_t)kf.x) != 0xFFFFFF) ? std::to_string((size_t)kf.x) : "empty");

			addImage("Mat_" + imageName + "_texture", "texture_" + imageName + ".png");
			addEffectSampler2D(animation.targetId.substr(0, animation.targetId.size() - 15), "Mat_" + imageName);

			str += ((i == 0) ? "" : " ") + string("Mat_") + imageName + "_sampler";
		}
		node_Name_array->LinkEndChild(new TiXmlText(str));


		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_array");
		node_accessor->SetAttribute("stride", "1");

		TiXmlElement* node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("type", "name");
	}
	break;




	case ColladaAnimation::AT_Transparence:
	{
		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values");

		TiXmlElement* node_floats = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_floats);
		node_floats->SetAttribute("id", animName + "_values_floats");
		node_floats->SetAttribute("count", nbKeyFrames * 4);
		str = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
		{
			ColladaKeyframe &kf = animation.listKeyFrames.at(i);

			str += ((i == 0) ? "" : " ") +string("0.0 0.0 0.0 ")+ EMO_BaseFile::FloatToString(kf.x);
		}
		node_floats->LinkEndChild(new TiXmlText(str));


		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_floats");
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
	break;


	case ColladaAnimation::AT_Transparency:
	{
		node_source = new TiXmlElement("source");
		node_anim->LinkEndChild(node_source);
		node_source->SetAttribute("id", animName + "_values");

		TiXmlElement* node_floats = new TiXmlElement("float_array");
		node_source->LinkEndChild(node_floats);
		node_floats->SetAttribute("id", animName + "_values_floats");
		node_floats->SetAttribute("count", nbKeyFrames);
		str = "";
		for (size_t i = 0; i < nbKeyFrames; i++)
			str += ((i == 0) ? "" : " ") + EMO_BaseFile::FloatToString(animation.listKeyFrames.at(i).x);
		node_floats->LinkEndChild(new TiXmlText(str));


		TiXmlElement* node_technique_common = new TiXmlElement("technique_common");
		node_source->LinkEndChild(node_technique_common);

		TiXmlElement* node_accessor = new TiXmlElement("accessor");
		node_technique_common->LinkEndChild(node_accessor);
		node_accessor->SetAttribute("count", nbKeyFrames);
		node_accessor->SetAttribute("source", "#" + animName + "_values_floats");
		node_accessor->SetAttribute("stride", 1);

		TiXmlElement* node_param = new TiXmlElement("param");
		node_accessor->LinkEndChild(node_param);
		node_param->SetAttribute("type", "float");
	}
	break;




	}

	

	/////////////////////////////////////////////////////


	node_source = new TiXmlElement("source");
	node_anim->LinkEndChild(node_source);
	node_source->SetAttribute("id", animName + "_interpolation");

	TiXmlElement* node_Name_array = new TiXmlElement("Name_array");
	node_source->LinkEndChild(node_Name_array);
	node_Name_array->SetAttribute("id", animName + "_interpolation_array");
	node_Name_array->SetAttribute("count", nbKeyFrames * nbComponents);
	str = "";
	for (size_t i = 0; i < nbKeyFrames * nbComponents; i++)
		str += ((i == 0) ? "" : " ") + string("LINEAR");
	node_Name_array->LinkEndChild(new TiXmlText(str));


	node_technique_common = new TiXmlElement("technique_common");
	node_source->LinkEndChild(node_technique_common);

	node_accessor = new TiXmlElement("accessor");
	node_technique_common->LinkEndChild(node_accessor);
	node_accessor->SetAttribute("count", nbKeyFrames);
	node_accessor->SetAttribute("source", "#" + animName + "_interpolation_array");
	node_accessor->SetAttribute("stride", nbComponents);

	node_param = new TiXmlElement("param");
	node_accessor->LinkEndChild(node_param);
	node_param->SetAttribute("type", "name");

	/////////////////////////////////////////////////////




	if (animation.type  != ColladaAnimation::AT_Rotation)
	{

		TiXmlElement* node_sampler = new TiXmlElement("sampler");
		node_anim->LinkEndChild(node_sampler);
		node_sampler->SetAttribute("id", animName + "_sampler");

		TiXmlElement* node_input = new TiXmlElement("input");
		node_sampler->LinkEndChild(node_input);
		node_input->SetAttribute("semantic", "INPUT");
		node_input->SetAttribute("source", "#" + animName + "_times");

		node_input = new TiXmlElement("input");
		node_sampler->LinkEndChild(node_input);
		node_input->SetAttribute("semantic", "OUTPUT");
		node_input->SetAttribute("source", "#" + animName + "_values");

		node_input = new TiXmlElement("input");
		node_sampler->LinkEndChild(node_input);
		node_input->SetAttribute("semantic", "INTERPOLATION");
		node_input->SetAttribute("source", "#" + animName + "_interpolation");


		//////////



		TiXmlElement* node_channel = new TiXmlElement("channel");
		node_anim->LinkEndChild(node_channel);
		node_channel->SetAttribute("source", "#" + animName + "_sampler");
		node_channel->SetAttribute("target", animation.targetId + "/" + targetAnimType);

	}else {

		string str_tmp = "";
		for (size_t i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0: str_tmp = "Z"; break;
			case 1: str_tmp = "X"; break;
			case 2: str_tmp = "Y"; break;
			};

			TiXmlElement* node_sampler = new TiXmlElement("sampler");
			node_anim->LinkEndChild(node_sampler);
			node_sampler->SetAttribute("id", animName + "_sampler_rot"+ str_tmp);

			TiXmlElement* node_input = new TiXmlElement("input");
			node_sampler->LinkEndChild(node_input);
			node_input->SetAttribute("semantic", "INPUT");
			node_input->SetAttribute("source", "#" + animName + "_times");

			node_input = new TiXmlElement("input");
			node_sampler->LinkEndChild(node_input);
			node_input->SetAttribute("semantic", "OUTPUT");
			node_input->SetAttribute("source", "#" + animName + "_values_rot"+ str_tmp);

			node_input = new TiXmlElement("input");
			node_sampler->LinkEndChild(node_input);
			node_input->SetAttribute("semantic", "INTERPOLATION");
			node_input->SetAttribute("source", "#" + animName + "_interpolation");

			TiXmlElement* node_channel = new TiXmlElement("channel");
			node_anim->LinkEndChild(node_channel);
			node_channel->SetAttribute("source", "#" + animName + "_sampler_rot"+ str_tmp);
			node_channel->SetAttribute("target", animation.targetId + "/" + targetAnimType + str_tmp);
		}
	}
}


/*-------------------------------------------------------------------------------\
|                             addAnimationExtraInformations						 |
\-------------------------------------------------------------------------------*/
void Collada::addAnimationExtraInformations(float framePerSecond, float startTime, float endTime)
{
	TiXmlElement* node_extra = new TiXmlElement("extra");
	node_visual_scene->LinkEndChild(node_extra);
	
	TiXmlElement* node_technique = new TiXmlElement("technique");
	node_extra->LinkEndChild(node_technique);
	node_technique->SetAttribute("profile", "MAX3D");
	
	TiXmlElement* node_frame_rate = new TiXmlElement("frame_rate");
	node_technique->LinkEndChild(node_frame_rate);
	node_frame_rate->LinkEndChild(new TiXmlText( EMO_BaseFile::FloatToString(framePerSecond) ));


	node_technique = new TiXmlElement("technique");
	node_extra->LinkEndChild(node_technique);
	node_technique->SetAttribute("profile", "FCOLLADA");

	TiXmlElement* node_start_time = new TiXmlElement("start_time");
	node_technique->LinkEndChild(node_start_time);
	node_start_time->LinkEndChild(new TiXmlText(EMO_BaseFile::FloatToString(startTime)));

	TiXmlElement* node_end_time = new TiXmlElement("end_time");
	node_technique->LinkEndChild(node_end_time);
	node_end_time->LinkEndChild(new TiXmlText(EMO_BaseFile::FloatToString(endTime)));
}
