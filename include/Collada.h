#ifndef COLLADA_H
#define COLLADA_H

#include "common.h"
#include "EMO_BaseFile.h"

#define EMD_VTX_FLAG_POS				0x1
#define EMD_VTX_FLAG_NORM				0x2
#define EMD_VTX_FLAG_TEX				0x4
#define EMD_VTX_FLAG_TEX2				0x8
#define EMD_VTX_FLAG_COLOR				0x40
#define EMD_VTX_FLAG_TANGENT			0x80
#define EMD_VTX_FLAG_BLEND_WEIGHT		0x200

/*-------------------------------------------------------------------------------\
|                             EMDVertex				                             |
\-------------------------------------------------------------------------------*/
class EMDVertex
{
public:
	uint16_t flags;					//we keep the flags to know, what to use.

	float pos_x;
	float pos_y;
	float pos_z;

	float norm_x;					//same is in DBX (may the flags 0x8000),
	float norm_y;					// you have float16 values
	float norm_z;					// we will stock in float (is float32)

	float tang_x;					//same as norm_x, could be in float16 in file
	float tang_y;					// but stock in float32.
	float tang_z;

	float text_u;					//same : text_u could be in float16 in certain files, 
	float text_v;					// but stock in float32.

	float text2_u;					//same as text_u
	float text2_v;

	uint32_t color;

	uint8_t blend[4];
	float blend_weight[4];			//same blend_weight[1] could be a float16 in certain files


	EMDVertex(void) { zero(); }

	void	zero(void);
	bool	operator == (const EMDVertex& vertex);

	void	getColorRGBAFloat(float &r, float &g, float &b, float &a);			//get values into [0,1] ranges
	void	setColorFromRGBAFloat(float r, float g, float b, float a);			//set values from [0,1] ranges

	void	getColorFromRGBAUint8(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a);			//set values from [0,255] ranges
	void	setColorFromRGBAUint8(uint8_t r, uint8_t g, uint8_t b, uint8_t a);			//set values from [0,255] ranges

	string	getColorFromRGBA_str();			//set values from "0.0 0.1 0.5 1.0" ranges
	void	getColorFromRGBA_str(string values);
};


/*-------------------------------------------------------------------------------\
|                             EMDTriangles			                             |
\-------------------------------------------------------------------------------*/
class EMDTriangles
{
public:
	vector<size_t> faces;

	EMDTriangles(void) { }
};





/*-------------------------------------------------------------------------------\
|                             ColladaAnimation		                             |
\-------------------------------------------------------------------------------*/
class ColladaKeyframe
{
public:
	float time;
	float x;
	float y;
	float z;
	float w;

	ColladaKeyframe(float time = 0, float x = 0, float y = 0, float z = 0, float w = 0);
};


/*-------------------------------------------------------------------------------\
|                             ColladaAnimation		                             |
\-------------------------------------------------------------------------------*/
class ColladaAnimation
{
public:
	enum AnimationType
	{
		AT_None = 0,
		AT_Position,
		AT_Rotation,
		AT_Scale,
		AT_TextureIndex,
	};

	string name;										//Notice: on the createAnimationsTags(), all ColladaAnimation with the same name will have the maxduration of all.
	string targetId;
	AnimationType type;
	float duration;

	std::vector<ColladaKeyframe> listKeyFrames;

	ColladaAnimation(string targetId, AnimationType type = AT_None, float duration = 0);
};




/*-------------------------------------------------------------------------------\
|                             Collada											 |
\-------------------------------------------------------------------------------*/
class Collada
{
public:
	string filename;

	TiXmlDocument *doc;
	TiXmlElement* root;

	TiXmlElement* node_library_cameras;
	TiXmlElement* node_library_lights;
	TiXmlElement* node_library_images;
	TiXmlElement* node_library_effects;
	TiXmlElement* node_library_materials;
	TiXmlElement* node_geometries;
	TiXmlElement* node_library_visual_scenes;
	TiXmlElement* node_visual_scene;
	TiXmlElement* node_library_animations;
	TiXmlElement* node_scene;

	std::vector<string> listMaterialNames;

public:
	Collada();
	virtual ~Collada() { if (doc) { delete doc; } }

	//usual function
	void addGeometry(string name, std::vector<EMDVertex> &vertices, std::vector<EMDTriangles> &triangles, string materialName);
	void addTextureMaterial(string name, string filename);
	void addColorMaterial(string name, string color);
	void addAnimation(ColladaAnimation &animation);
	void addAnimationExtraInformations(float framePerSecond, float startTime, float endTime);
	


	TiXmlElement* createNode(string name, TiXmlElement* parentNode = 0, Common::Vector3 position = Common::Vector3::zero, Common::Vector3 rotationAngles = Common::Vector3::zero, string instanceGeometryName = "", string materialName = "", bool haveTexture = false);
	void makeInstanceGeometryOnNode(TiXmlElement* node, string instanceGeometryName, string materialName = "", bool haveTexture = false);
	void addTransformOnNode(TiXmlElement* node = 0, Common::Vector3 position = Common::Vector3::zero, Common::Vector3 rotationAngles = Common::Vector3::zero);

	void save(string filename);

private:
	//macro function
	void addImage(string name, string filename);
	void addEffect(string name, bool isSampler2D = true, string nameTexture = "", string color = "0 0 0 1");
	void addMaterial(string name, string nameEffect);
	void checkRootFor(string tagName);
};

#endif // COLLADA_H
