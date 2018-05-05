#ifndef SWR_MODELFILE_H
#define SWR_MODELFILE_H

#include "common.h"
#include "EMO_BaseFile.h"


#ifdef _MSC_VER
#pragma pack(push,1)
#endif

#define SWR_MODEL_SIGNATURE_COMPRESSED "Comp"

#define SWR_MODEL_SIGNATURE_MODEL "Modl"
#define SWR_MODEL_SIGNATURE_TRACK "Trak"
#define SWR_MODEL_SIGNATURE_POD "Podd"
#define SWR_MODEL_SIGNATURE_PART "Part"
#define SWR_MODEL_SIGNATURE_SCENE "Scen"
#define SWR_MODEL_SIGNATURE_MAlt "MAlt"
#define SWR_MODEL_SIGNATURE_Pupp "Pupp"

#define SWR_MODEL_SIGNATURE_DATA "Data"
#define SWR_MODEL_SIGNATURE_ANIM "Anim"
#define SWR_MODEL_SIGNATURE_ALTN "AltN"
#define SWR_MODEL_SIGNATURE_HEND "HEnd"


struct SWR_MODELHeader
{
	uint32_t offset_Section1;	// 0		//MAterials or Textures descriptors
	uint32_t offset_Section2;	// 4
} PACKED;
static_assert(sizeof(SWR_MODELHeader) == 0x8, "Incorrect structure size.");


struct SWR_MODELHeader_Used				//it's the really used because we will get the offset_section1 of the next header to have size. (and there is a a last elment for the end of file.) 
{										//=> SWR_MODELHeader is for size

	uint32_t offset_Section1;	// 0		//Materials or Textures descriptors
	uint32_t offset_Section2;	// 4
	uint32_t offset_NextHeader_Section1;	// 8
} PACKED;
static_assert(sizeof(SWR_MODELHeader_Used) == 0xC, "Incorrect structure size.");




///////////////////////////////////////////



struct SWR_Data
{
	uint8_t unk0;				// 0 
	uint8_t unk1;				// 0 
	uint8_t unk2;				// 0 
	uint8_t unk3;				// 0 
} PACKED;
static_assert(sizeof(SWR_Data) == 0x4, "Incorrect structure size.");


///////////////////////////////////////////


struct SWR_MODEL_Section2_Header
{
	char signature[4];			// 0
} PACKED;
static_assert(sizeof(SWR_MODEL_Section2_Header) == 0x4, "Incorrect structure size.");



struct SWR_AltN_Header
{
	uint32_t flags;				// 0  0x4xxx bit for for "have Child" Todo better understand and split
	uint32_t unk0;				// 4
	uint32_t unk1;				// 8
	uint8_t unk2_a;				// C
	uint8_t unk2_b;				// D
	uint16_t unk3;				// E
	uint32_t unk4;				// 10
	uint32_t nb_Childs;			// 14
	uint32_t offset_Childs;		// 18
} PACKED;
static_assert(sizeof(SWR_AltN_Header) == 0x1C, "Incorrect structure size.");




///////////////////////////////////////////

struct SWR_AltN_0x5065			//after SWR_AltN_Header
{
	uint32_t unk_0;				// 0
} PACKED;
static_assert(sizeof(SWR_AltN_0x5065) == 0x4, "Incorrect structure size.");


struct SWR_AltN_0x5066
{
	float distLod_0;			// 0
	float distLod_1;			// 4
	float distLod_2;			// 8
	float distLod_3;			// C
	float distLod_4;			// 10
	float distLod_5;			// 14
	float distLod_6;			// 18
	float distLod_7;			// 1C

	float unk_8;				// 20
	float unk_9;				// 24
	float unk_10;				// 28
} PACKED;
static_assert(sizeof(SWR_AltN_0x5066) == 0x2C, "Incorrect structure size.");


struct SWR_AltN_0xD064
{
	float m00;					// 0	Matrix3x3 Todo check the order !! the problem is we can't test with the game (else to rebuild the file)
	float m01;					// 4
	float m02;					// 8
	float m10;					// C
	float m11;					// 10
	float m12;					// 14
	float m20;					// 18
	float m21;					// 1C
	float m22;					// 20

	float posX;					// 24
	float posY;					// 28
	float posZ;					// 2C
} PACKED;
static_assert(sizeof(SWR_AltN_0xD064) == 0x30, "Incorrect structure size.");


struct SWR_AltN_0xD065			//Transform part apparently
{
	float m00;					// 0	Matrix3x3 Todo check the order !! the problem is we can't test with the game (else to rebuild the file)
	float m01;					// 4
	float m02;					// 8
	float m10;					// C
	float m11;					// 10
	float m12;					// 14
	float m20;					// 18
	float m21;					// 1C
	float m22;					// 20

	float posX;					// 24
	float posY;					// 28
	float posZ;					// 2C

	float unk12_X;				// 30
	float unk12_Y;				// 34
	float unk12_Z;				// 38
} PACKED;
static_assert(sizeof(SWR_AltN_0xD065) == 0x3C, "Incorrect structure size.");


struct SWR_AltN_0xD066
{
	uint16_t unk_0;				// 0
	uint16_t unk_1;				// 2

	float unk_2;				// 4
	float unk_3;				// 8
	float unk_4;				// C
} PACKED;
static_assert(sizeof(SWR_AltN_0xD066) == 0x10, "Incorrect structure size.");





///////////////////////////////////////////

struct SWR_AltN_0x3064			//after SWR_AltN_Header
{
	float minX;					// 0
	float minY;					// 4
	float minZ;					// 8
	float maxX;					// C
	float maxY;					// 10
	float maxZ;					// 14
	uint32_t unk0;				// 18
	uint32_t unk1;				// 1C
} PACKED;
static_assert(sizeof(SWR_AltN_0x3064) == 0x20, "Incorrect structure size.");



struct SWR_MODEL_Section3		// struct_V16. after SWR_AltN_0x3064
{
	uint32_t offset_section4;	// 0
	uint32_t offset_section7;	// 4
	float minX;					// 8
	float minY;					// C
	float minZ;					// 10
	float maxX;					// 14
	float maxY;					// 18
	float maxZ;					// 1C
	uint16_t nbElementV90;			// 0x20	nbElement
	uint16_t typeMode;			// 0x22	Some mode, {3,4,5} are typical values : mode 3 = 3*unk32;			mode 4 = 4*unk32;		mode 5 = Count for V90
	uint32_t offset_V90;		// 0x24	Pointer to uint32_t[], for mode 5, summed up is the count of unk40 (stripsize?)
	uint32_t offset_unk40;		// 0x28	Pointer to uint16_t[] (indices?)
	uint32_t offset_unk44;		// 0x2C Pointer to uint16_t[]
	uint32_t offset_unk48;
	uint32_t offset_unk52;
	uint16_t nbElementV44;			// 0x38 Count for unk44
	uint16_t nbElementV52;				// 0x3A
	uint16_t unk60;				// 0x3C
	uint16_t unk62;				// 0x3E

} PACKED;
static_assert(sizeof(SWR_MODEL_Section3) == 0x40, "Incorrect structure size.");



struct SWR_MODEL_Section4		// struct_V17
{
	uint32_t unk0;				// 0
	uint16_t unk4;				// 4
	uint16_t unk6;				// 6
	uint32_t offset_section5;	// 8
	uint32_t offset_section6;	// C
} PACKED;
static_assert(sizeof(SWR_MODEL_Section4) == 0x10, "Incorrect structure size.");


struct SWR_MODEL_Section5		// struct_V19
{
	uint32_t unk0;				// 0
	uint16_t unk4;				// 4
	uint16_t unk6;				// 6
	uint16_t unk8[2];			// 8
	uint8_t  unk12;				// C
	uint8_t  unk13;				// D
	uint8_t  unk14[2];			// E
	uint16_t unk16;				// 10
	uint16_t unk18;				// 12
	uint16_t unk20;				// 14
	uint16_t unk22;				// 16
	uint16_t unk24;				// 18
	uint16_t unk26;				// 1A
	uint32_t offset_Section5_b[5]; // 1C
	uint32_t unk48;				// 30
	uint32_t unk52;				// 34
	uint32_t textureMaskAndIndex;// 38	0xFF000000 for having the mask.
	uint32_t unk60;				// 3C
} PACKED;
static_assert(sizeof(SWR_MODEL_Section5) == 0x40, "Incorrect structure size.");



struct SWR_MODEL_Section5_b
{
	uint16_t unk0;				// 0
	uint8_t	 unk2;				// 2
	uint8_t	 unk3;				// 3
	uint8_t	 unk4;				// 4
	uint8_t	 unk5;				// 5
	uint8_t unk6_a;				// 6
	uint8_t unk6_b;				// 7
	uint32_t unk8;				// 8
	uint16_t unk12;				// C
	uint16_t unk14;				// E
} PACKED;
static_assert(sizeof(SWR_MODEL_Section5_b) == 0x10, "Incorrect structure size.");

/* ///////////////////////////////// JayFoxRox about texture and Section5.


a1 = SWR_MODEL_Section5.unk12 and
a2 = SWR_MODEL_Section5.unk13
a1	a2	Storage	Format
0	3	A4R4G4B4	A8R8G8B8 from file ?
5	1	A4R4G4B4	A8 from file, RGB = 0xFFF
5	3	A4R4G4B4	A4R4G4B4 from file ?
4		A4R4G4B4	FIXME
4	0	A4R4G4B4	Read 4 bit and duplicate in all channels
3	0	A4R4G4B4	A4 from file, RGB = 0xFFF
A1R5G5B5	(Any other format than those listed above)
2	0	A1R5G5B5	Loaded as A1R5G5B5 from file using I4 palette ?
2	1	A1R5G5B5	Loaded as A1R5G5B5 from file ?
5	2	A1R5G5B5	R5G5B5 from file, A = 0x1
5	7	A1R5G5B5	R5 from file, GB = 0xFF A = 0x1 ? ? ? ? unsure
THIS LIST IS INCOMPLETE, I BELIEVE THERE ARE AT LEAST 2 MORE FORMATS MISSING

This is based on ongoing research in https://github.com/OpenSWE1R/swe1r-re/pull/12

---------------------------------------------------------


//I found that it's addressed relative in the texture loader:
struct A1Unk
{
	uint8_t unk_pad0[3];			// +0
	uint8_t unk3;					// +3
};
struct A1							// Probably part of the model structure
{
	uint8_t unk_pad_neg56[12];		// -56 (-14*4) // 0x0
	uint8_t unk_neg44;				// -44 (-14*4 + 12) // 0xC
	uint8_t unk_neg43;				// -43 (-14*4 + 13) // 0xD
	uint8_t unk_pad_neg42[2];		// -42 // 0xE
	uint16_t unk_neg40;				// -40 // 0x10
	uint16_t unk_neg38;				// -38 // 0x12
	uint8_t unk_pad_neg36[8];		// -36 // 0x14
	A1Unk* unk_neg28;				// -28 (-14*4 + 28) //  0x1C
	uint8_t unk_pad_neg24[24];		// -24 // 0x20
	void* texture_data;				// 0 [a1 points here] // 0x38
	void* optional_texture_data;	// 4 [a2 should point here] // 0x3C
}; 

//How it is used in the texture loader :
uint16_t v4 = swap16(a1->unk_neg40);

if (a1->unk_neg28)
{
	uint16_t v3 = swap16(a1->unk_neg38);

	// Get width and height as POT
	int v6 = sub_445C90(v4);
	int v7 = sub_445C90(v3);

	// Process texture data
	sub_445EE0(
		a1->unk_neg44, // ?
		a1->unk_neg43, // ?
		v4, // NPOT Width
		v3, // NPOT Height
		v6, // POT Width
		v7, // POT Height
		_a1, // Texture data
		_a2, // Optional texture data
		1, // ?
		a1->unk_neg28->unk3); // ?
}

//The new research reveals the following:
//-Section5.offset_Section5_b[0] = Must exist or texture data will not be parsed correctly(? )
//-Section5.offset_Section5_b[0]->unk3 = Flags of some sort, only 0x10 and 0x01 are used.They seem to double the resolution vertically and horizontally(maybe to mirror / unfold textures while loading ? ).
//-Section5.unk16 = NPOT Width
//-Section5.unk18 = NPOT Height
//-Section5.unk12[0] = Something to do with texture, seems to control pixel format
//-Section5.unk12[1] = Something to do with texture, seems to control pixel format
//-Section5.textureMaskAndIndex = Index to texture and pointer to pixel data(section a) at load - time(unsure: might be replaced with other data later)
//-Section5.unk60 = Pointer to pixel data(section b) at load - time, presumably garbage if b == 0 (unsure: might be replaced with other data later)
//-(Where section a and b refer to the first and second section in the out_textureblock table)

//////////////////////////////////*/





struct SWR_MODEL_Section6		// struct_V36
{
	uint32_t unk0;				// 0
	uint16_t unk4;				// 4
	uint32_t unk6[2];			// 6
	uint32_t unk14[2];			// E
	uint8_t  unk22[2];			// 16
	uint32_t unk24;				// 18
	uint32_t unk28;				// 1C
	uint16_t unk32;				// 20
	uint16_t unk34;				// 22
	uint16_t unk36;				// 24
	uint16_t unk38;				// 26
	uint32_t unk40;				// 28
	uint32_t unk44;				// 2C
	uint32_t unk48;				// 30
} PACKED;
static_assert(sizeof(SWR_MODEL_Section6) == 0x34, "Incorrect structure size.");



struct SWR_MODEL_Section7		// struct_V46
{
	uint16_t unk0;				// 0
	uint8_t  unk2[4];			// 2
	uint16_t unk6;				// 6
	uint16_t unk8;				// 8
	uint16_t unk10;				// A
	uint8_t  unk12[8];			// C

	float unk20;				// 14
	float unk24;				// 18
	float unk28;				// 1C
	float unk32;				// 20
	float unk36;				// 24
	
	uint32_t unk40;				// 28
	uint32_t unk44;				// 2c
	uint16_t unk48;				// 30
	uint16_t unk50;				// 32
	uint32_t unk52;				// 34
	uint32_t unk56;				// 38
	uint32_t offset_section8;	// 3C startoffset list of struct_V47
} PACKED;
static_assert(sizeof(SWR_MODEL_Section7) == 0x40, "Incorrect structure size.");




struct SWR_MODEL_Section7_b
{
	uint32_t unk0;				// 0
	uint32_t unk1;				// 4
	uint32_t unk2;				// 8
} PACKED;
static_assert(sizeof(SWR_MODEL_Section7_b) == 0xC, "Incorrect structure size.");



struct SWR_MODEL_Section8		// struct_V47
{
	float unk0[3];				// 0
	float unk12[3];				// C
	
	float unk24;				// 18
	float unk28;				// 1C
	uint32_t offset_AltN;		// 20
	uint16_t unk36;				// 24
	uint16_t unk38;				// 26
	uint32_t offset_next_section8; // 28
} PACKED;
static_assert(sizeof(SWR_MODEL_Section8) == 0x2C, "Incorrect structure size.");





struct SWR_MODEL_Section40
{
	uint32_t unk0;				// 0
	uint16_t unk1;				// 4
	uint16_t unk2;				// 6
	uint32_t unk3;				// 8
} PACKED;
static_assert(sizeof(SWR_MODEL_Section40) == 0xC, "Incorrect structure size.");




struct SWR_MODEL_Section48_Header
{
	uint8_t unk0;				// 0
	uint8_t unk1;				// 1
	uint8_t unk2;				// 2
	uint8_t unk3;				// 3
	uint32_t offset_EndSection;	// 4
} PACKED;
static_assert(sizeof(SWR_MODEL_Section48_Header) == 0x8, "Incorrect structure size.");


struct SWR_MODEL_Section48
{
	uint8_t unk0;				// 0
	uint8_t unk1;				// 1
	uint8_t unk2;				// 2
	uint8_t unk3;				// 3
	uint32_t unk4;				// 4  //a kind of offset (over the current model)
} PACKED;
static_assert(sizeof(SWR_MODEL_Section48) == 0x8, "Incorrect structure size.");






struct SWR_MODEL_Section52		//Visual Geometry
{
	uint16_t posX;				// 0
	uint16_t posY;				// 2
	uint16_t posZ;				// 4
	uint16_t unk_padding;		// 6
	uint16_t uvU;				// 8
	uint16_t uvV;				// A
	uint8_t colorR;				// C		// normalDirectionX
	uint8_t colorG;				// D		// normalDirectionY
	uint8_t colorB;				// E		// normalDirectionZ
	uint8_t colorA;				// F		//specular factor
} PACKED;
static_assert(sizeof(SWR_MODEL_Section52) == 0x10, "Incorrect structure size.");




///////////////////////////////////////////




struct SWR_Anim_Header
{
	uint32_t unk0[61];			// 0	//always 0
	float unk1_0;				// F4
	float unk1_1;				// F8
	float unk1_2;				// FC
	uint8_t unk2;				// 100
	uint8_t unk3;				// 101
	uint8_t unk4;				// 102
	uint8_t flags;				// 103	// 1, B or C => 1 component;  4 => 2 comp; 7, 9 or A => 3 comp; 6 or 8 => 4 comp;
	uint32_t nbKeyFrames;		// 104
	float unk5_0;				// 108
	float unk5_1;				// 10C
	float unk5_2;				// 110
	uint32_t unk6;				// 114
	uint32_t unk7;				// 118
	uint32_t offset_times;		// 11C
	uint32_t offset_values;		// 120
	uint32_t offset_AltN;		// 124	// target the object witch have the animation
	uint32_t unk8;				// 128	// could be relative to a number of child, sibling object concerned by the animation ?
} PACKED;
static_assert(sizeof(SWR_Anim_Header) == 0x12C, "Incorrect structure size.");




struct SWR_Anim_Values_case2_Header
{
	uint32_t offset_section4;	// 0
	uint32_t unk0;				// 4
} PACKED;
static_assert(sizeof(SWR_Anim_Values_case2_Header) == 0x8, "Incorrect structure size.");

struct SWR_Anim_Values_case2
{
	uint32_t unk0;				// 0
	uint16_t unk1;				// 4
	uint16_t unk2;				// 6
	uint32_t unk3;				// 8
	uint32_t unk4;				// C
	uint16_t unk5;				// 10
	uint16_t unk6;				// 12
	uint16_t unk7;				// 14
	uint16_t unk8;				// 16
	uint32_t unk9;				// 18
	uint32_t offset_anim2_b;	// 1C
	uint32_t unk11;				// 20
	uint32_t unk12;				// 24
	uint32_t unk13;				// 28
	uint32_t unk14;				// 2C
	uint32_t unk15;				// 30
	uint32_t unk16;				// 34
	uint32_t unk17;				// 38
	uint32_t unk18;				// 3C
} PACKED;
static_assert(sizeof(SWR_Anim_Values_case2) == 0x40, "Incorrect structure size.");



struct SWR_Anim_Values_case2_b
{
	uint32_t unk0;				// 0
	uint16_t unk1;				// 4
	uint16_t unk2;				// 6
	uint32_t unk3;				// 8
	uint32_t unk4;				// C
} PACKED;
static_assert(sizeof(SWR_Anim_Values_case2_b) == 0x10, "Incorrect structure size.");



#ifdef _MSC_VER
#pragma pack(pop)
#endif







//todo put this class in it own files.
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
|                             Collada											 |
\-------------------------------------------------------------------------------*/
//todo put this class in it own files.
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
	
	TiXmlElement* createNode(string name, TiXmlElement* parentNode = 0, float transX = 0, float transY = 0, float transZ = 0, float rotAxisX = 0, float rotAxisY = 1, float rotAxisZ = 0, float rotAngle = 0, string instanceGeometryName = "", string materialName = "", bool haveTexture = false);
	void makeInstanceGeometryOnNode(TiXmlElement* node, string instanceGeometryName, string materialName = "", bool haveTexture = false);
	void addTransformOnNode(TiXmlElement* node = 0, float transX = 0, float transY = 0, float transZ = 0, float rotAxisX = 0, float rotAxisY = 1, float rotAxisZ = 0, float rotAngle = 0);

	void save(string filename);

private:
	//macro function
	void addImage(string name, string filename);
	void addEffect(string name, bool isSampler2D = true, string nameTexture = "", string color = "0 0 0 1");
	void addMaterial(string name, string nameEffect);
};











/*-------------------------------------------------------------------------------\
|                             Swr_Model											 |
\-------------------------------------------------------------------------------*/
class Swr_Model : public EMO_BaseFile
{
public:
	string originefilename;

private:
	std::vector<std::vector<std::vector<string>>> listTagColors;	// by Section, param, and font/background.
	

public:
	Swr_Model();
	virtual ~Swr_Model() { Reset(); }

	void Reset();
	virtual bool load(string filename) { return this->SmartLoad(filename); }

	//debug version
	void save_Xml(string filename, bool show_error = true);
	void write_Xml(TiXmlElement *parent, const uint8_t *buf, size_t size, string filename, Collada* collada);

	void save_Coloration(string filename, bool show_error = false);		//create a file for wxHexEditor, for add tag and color on section of the file.
	void write_Coloration(TiXmlElement *parent, const uint8_t *buf, size_t size);
	void write_Coloration_Tag(string paramName, string paramType, string paramComment, size_t startOffset, size_t size, string sectionName, TiXmlElement* parent, size_t idTag, size_t sectionIndex, size_t paramIndex, std::vector<size_t> &listBytesAllreadyTagged, size_t sectionIndexInList = (size_t)-1, bool checkAllreadyTaggued = true);
	void write_Coloration_Gaps(size_t startOffsetToConsidere, size_t endOffsetToConsidere, size_t sizeFilter, size_t start_idTag, string sectionName, TiXmlElement* parent, std::vector<size_t> &listBytesAllreadyTagged);

private:
	bool checkDuplication(size_t offset, std::vector<size_t> &listToAvoidDuplication);
	bool checkDuplication_Malt_recursion(size_t offset, std::vector<size_t> &listToAvoidDuplication, const uint8_t *buf, size_t size, size_t offset_Section2);
};





#endif // SWR_MODELFILE_H
