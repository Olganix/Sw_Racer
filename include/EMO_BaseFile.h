// Author : Eternity (See DragonBall Xenoverse (1 or 2) tools for modding)


#ifndef __EMO_BASEFILE_H__
#define __EMO_BASEFILE_H__


#include "common.h"

#define UNUSED(x) (void)(x)

#ifdef _MSC_VER
	#define FUNCNAME    __FUNCSIG__

	// WARNING: not safe
	#define snprintf    _snprintf
	#include "vs/dirent.h"

	#define strncasecmp _strnicmp
	#define strcasecmp _stricmp
#else
	#include <dirent.h>
	#define FUNCNAME    __PRETTY_FUNCTION__

#endif

#ifdef _WIN32
	#include <direct.h>
	#define do_mkdir(a, b) _mkdir(a)
#else
	#define do_mkdir(a, b) mkdir(a, b)
#endif

#undef CreateFile




#ifndef PACKED

#ifdef _MSC_VER
#define PACKED
#else
#define PACKED  __attribute__((packed))
#endif

#endif // PACKED



/********************************************************************************************
*								EMO_BaseFile												*
********************************************************************************************/
class EMO_BaseFile
{
public:

	bool big_endian;
	std::string name;

	uint64_t val64(uint64_t val) const;
	uint32_t val32(uint32_t val) const;
	uint16_t val16(uint16_t val) const;
	float val_float(float val) const;
	float float16ToFloat(uint16_t val) const;
	float float20ToFloat(uint32_t val) const;
	uint32_t floatToFloat20(float val) const;

	void copy_float(void *x, float val) const;
	void copy_float16(void *x, float val) const;
	

	uint8_t *GetOffsetPtr(const void *base, uint32_t offset, bool native = false) const;
	uint8_t *GetOffsetPtr(const void *base, uint32_t *offsets_table, uint32_t idx, bool native = false) const;

	void ModTable(uint32_t *offsets, unsigned int count, int mod_by);
	unsigned int GetHighestValueIdx(uint32_t *values, unsigned int count, bool native = false);
	const char *FindString(const char *list, const char *str, unsigned int num_str);

	
public:
	// Don't make any function abstract, instead let's provide an empty default implementation

	virtual ~EMO_BaseFile() { }

	inline const string &getName() { return name; }

	inline bool IsBigEndian() { return big_endian; }
	inline void SetEndianess(bool big_endian) { this->big_endian = big_endian; }

	virtual bool Load(const uint8_t *buf, unsigned int size) { UNUSED(buf); UNUSED(size); return false; }
	virtual bool LoadFromFile(const std::string &path, bool show_error = true);

	virtual TiXmlDocument *Decompile() const { return nullptr; }
	virtual bool Compile(TiXmlDocument *doc, bool big_endian = false) { UNUSED(doc); UNUSED(big_endian); return NULL; }

	virtual bool DecompileToFile(const std::string &path, bool show_error = true, bool build_path = false);
	virtual bool CompileFromFile(const std::string &path, bool show_error = true, bool big_endian = false);

	virtual uint8_t *CreateFile(unsigned int *psize) { UNUSED(psize); return NULL; }
	virtual bool SaveToFile(const std::string &path, bool show_error = true, bool build_path = false);

	bool SmartLoad(const std::string &path, bool show_error = true, bool xml_big_endian = false);
	bool SmartSave(const std::string &path, bool show_error = true, bool build_path = false);


	/////////////////// from Utils
	static bool FileExists(const std::string & path);
	static bool DirExists(const std::string & path);

	static size_t GetFileSize(const std::string &path);

	static uint8_t *ReadFile(const std::string &path, size_t *psize, bool show_error = true);
	static uint8_t *ReadFileFrom(const std::string &path, size_t from, size_t size, bool show_error = true);

	static size_t WriteFile(const std::string &path, const uint8_t *buf, size_t size, bool show_error = true, bool build_path = false);
	static bool WriteFileBool(const std::string &path, const uint8_t *buf, size_t size, bool show_error = true, bool build_path = false);

	static bool Mkdir(const std::string &str);

	static bool RemoveFile(const std::string &str);

	static bool CreatePath(const std::string &path, bool last_is_directory = false);
	static FILE *fopen_create_path(const std::string &filename, const char *mode);

	static uint32_t DifPointer(const void *ptr1, const void *ptr2) { return (uint32_t)((uint64_t)ptr1 - (uint64_t)ptr2); } // ptr1-ptr2 

	static void TrimString(std::string &str, bool trim_left = true, bool trim_right = true);
	static bool IsEmptyString(const std::string &str);

	static size_t GetMultipleStrings(const std::string &str, std::vector<std::string> &list);
	static std::string ToSingleString(const std::vector<std::string> &list);
	static std::string ToSingleString(const std::vector<uint32_t> &list, bool hexadecimal = false);
	static std::string ToSingleString(const std::vector<uint16_t> &list, bool hexadecimal = false);
	static std::string ToSingleString(const std::vector<uint8_t> &list, bool hexadecimal = false);
	static std::string ToSingleString(const std::vector<float> & list);

	static std::string ToLowerCase(const std::string &str);
	static bool BeginsWith(const std::string &str, const std::string &substr, bool case_sensitive = true);
	static bool EndsWith(const std::string &str, const std::string &substr, bool case_sensitive = true);

	static std::string UnsignedToString(uint32_t value, bool hexadecimal);
	static std::string FloatToString(float value);

	static std::string GUID2String(const uint8_t *guid);

	// std::to_string doesn't work in mingw... lets make a replacer.
	template <typename T>
	static std::string ToString(T val)
	{
		std::stringstream stream;
		stream << val;
		return stream.str();
	}

	static TiXmlElement *FindRoot(TiXmlHandle *handle, const std::string &root_name);

	static uint32_t GetUnsigned(const std::string &str, uint32_t default_value = 0);
	static long long GetUnsigned64(const std::string &str, long long default_value = 0);
	static bool GetBoolean(const std::string &str, bool default_value = false);

	static size_t GetElemCount(const TiXmlElement *root, const char *name);

	static void WriteParamString(TiXmlElement *root, const char *name, const std::string &value);
	static void WriteParamMultipleStrings(TiXmlElement *root, const char *name, const std::vector<std::string> &values);

	static void WriteParamUnsigned(TiXmlElement *root, const char *name, uint32_t value, bool hexadecimal = false);
	static void WriteParamMultipleUnsigned(TiXmlElement *root, const char *name, const std::vector<uint32_t> &values, bool hexadecimal = false);
	static void WriteParamMultipleUnsigned(TiXmlElement *root, const char *name, const std::vector<uint16_t> &values, bool hexadecimal = false);
	static void WriteParamMultipleUnsigned(TiXmlElement *root, const char *name, const std::vector<uint8_t> &values, bool hexadecimal = false);

	static void WriteParamFloat(TiXmlElement *root, const char *name, float value);
	static void WriteParamMultipleFloats(TiXmlElement *root, const char *name, const std::vector<float> &values);

	static void WriteParamGUID(TiXmlElement *root, const char *name, const uint8_t *value);
	static void WriteParamBlob(TiXmlElement *root, const char *name, const uint8_t *value, size_t size);

	static bool ReadAttrString(const TiXmlElement *root, const char *name, std::string & value);
	static bool ReadAttrUnsigned(const TiXmlElement *root, const char *name, uint32_t *value);
	static bool ReadAttrFloat(const TiXmlElement *root, const char *name, float *value);

	static bool ReadParamString(const TiXmlElement *root, const char *name, std::string & value);
	static bool ReadParamMultipleStrings(const TiXmlElement *root, const char *name, std::vector<std::string> & values);

	static bool ReadParamUnsigned(const TiXmlElement *root, const char *name, uint32_t *value);

	static bool ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint32_t> &values);
	static bool ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint16_t> &values);
	static bool ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint8_t> &values);

	static bool ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint32_t *values, size_t count);
	static bool ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint16_t *values, size_t count);
	static bool ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint8_t *values, size_t count);

	static bool ReadParamFloat(const TiXmlElement *root, const char *name, float *value);
	static bool ReadParamMultipleFloats(const TiXmlElement *root, const char *name, std::vector<float> &values);
	static bool ReadParamMultipleFloats(const TiXmlElement *root, const char *name, float *values, size_t count);

	static bool ReadParamGUID(const TiXmlElement *root, const char *name, uint8_t *value);
	static uint8_t *ReadParamBlob(const TiXmlElement *root, const char *name, size_t *psize);

	static bool ReadParamUnsignedWithMultipleNames(const TiXmlElement *root, uint32_t *value, const char *name1, const char *name2, const char *name3 = nullptr, const char *name4 = nullptr, const char *name5 = nullptr);
	static bool ReadParamFloatWithMultipleNames(const TiXmlElement *root, float *value, const char *name1, const char *name2, const char *name3 = nullptr, const char *name4 = nullptr, const char *name5 = nullptr);

	static bool GetParamString(const TiXmlElement *root, const char *name, std::string & value);
	static bool GetParamMultipleStrings(const TiXmlElement *root, const char *name, std::vector<std::string> & values);

	static bool GetParamUnsigned(const TiXmlElement *root, const char *name, uint32_t *value);

	static bool GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint32_t> &values);
	static bool GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint16_t> &values);
	static bool GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint8_t> &values);

	static bool GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint32_t *values, size_t count);
	static bool GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint16_t *values, size_t count);
	static bool GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint8_t *values, size_t count);

	static bool GetParamFloat(const TiXmlElement *root, const char *name, float *value);
	static bool GetParamMultipleFloats(const TiXmlElement *root, const char *name, std::vector<float> &values);
	static bool GetParamMultipleFloats(const TiXmlElement *root, const char *name, float *values, size_t count);

	static bool GetParamGUID(const TiXmlElement *root, const char *name, uint8_t *value);
	static uint8_t *GetParamBlob(const TiXmlElement *root, const char *name, size_t *psize);

	static bool GetParamUnsignedWithMultipleNames(const TiXmlElement *root, uint32_t *value, const char *name1, const char *name2, const char *name3 = nullptr, const char *name4 = nullptr, const char *name5 = nullptr);
	static bool GetParamFloatWithMultipleNames(const TiXmlElement *root, float *value, const char *name1, const char *name2, const char *name3 = nullptr, const char *name4 = nullptr, const char *name5 = nullptr);

	static void WriteComment(TiXmlElement *root, const std::string & comment);

	static std::string ModelFileName(uint32_t cms_entry, uint32_t cms_model_spec_idx, const char *ext);

	static int RandomInt(int min, int max);
	static std::string GetRandomString(size_t len);

	static std::u16string Utf8ToUcs2(const std::string & utf8);
	static std::string Ucs2ToUtf8(const std::u16string & ucs2);

	static std::string Base64Encode(const uint8_t *buf, size_t size, bool add_new_line);
	static uint8_t *Base64Decode(const std::string &data, size_t *ret_size);

	static std::string GetAppData();
	static std::string GetTempFile(const std::string &prefix, const std::string &extension);

	static void RunProgram(const std::string &program, const std::vector<std::string> &args);

	class StringFinder
	{
	private:

		std::string str1;

	public:

		StringFinder(const std::string &str) { str1 = str; }
		bool operator()(const std::string &str2) const
		{
			return (strcasecmp(str1.c_str(), str2.c_str()) == 0);
		}
	};
};

#endif			//__EMO_BASEFILE_H__

