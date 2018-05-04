// Author : Eternity (See DragonBall Xenoverse (1 or 2) tools for modding)

#include <math.h>
#include <sys/stat.h>

#include "common.h"
#include "EMO_BaseFile.h"
#include "EMO_common.h"

using namespace Common;


uint64_t EMO_BaseFile::val64(uint64_t val) const
{
#ifdef __BIG_ENDIAN__
	return (big_endian) ? val : LE64(val)
#else
	return (big_endian) ? BE64(val) : val;
#endif
}

uint32_t EMO_BaseFile::val32(uint32_t val) const
{
#ifdef __BIG_ENDIAN__
	return (big_endian) ? val : LE32(val)
#else
	return (big_endian) ? BE32(val) : val;
#endif
}

uint16_t EMO_BaseFile::val16(uint16_t val) const
{
#ifdef __BIG_ENDIAN__
	return (big_endian) ? val : LE16(val)
#else
	return (big_endian) ? BE16(val) : val;
#endif
}

float EMO_BaseFile::val_float(float val) const
{
	uint32_t *p = (uint32_t *)&val;

	*p = val32(*p);

	return val;
}

float EMO_BaseFile::float16ToFloat(uint16_t val) const
{
	uint16_t uint16_tmp = val16(val);			//solve if bigEndian
	uint32_t u_32 = half_to_float(uint16_tmp);	//convert uint16_t with float16 => uint32_t with float32
	return *((float*)&u_32);					//considere the uint32 have float bits;
}



float EMO_BaseFile::float20ToFloat(uint32_t val) const
{
	//Olganix : Sorry, I'm not expert on float structure datas, 
	//and I didn't find a implementation for 20 bits floating point.
	//So if you could do better than this, please do it.
	//http://liu.diva-portal.org/smash/get/diva2:386252/FULLTEXT01.pdf
	//http://www.ntu.edu.sg/home/ehchua/programming/java/datarepresentation.html


	val = val & 0xFFFFF;						//filter to only use 20 bits from the right of uint32

	double sign = (((val & 0x80000) == 0) ? 1.0 : -1.0);
	uint32_t exposant = (val >> 13) & 0x3F;
	int biais = 0x3F / 2;						//6 bits pour l'exposant => 63 au max => 63 /2 = 31
	uint32_t mantisse = val & 0x1FFF;

	double fraction = 0.0;
	for (size_t i = 0; i < 13; i++)
	{
		double aa = ((mantisse >> (12 - i)) & 0x1) / pow(2.0, i + 1);
		fraction += ((mantisse >> (12 - i)) & 0x1) / pow(2.0, i+1);
	}
	
	double result = sign * (1.0 + fraction) * pow(2.0, exposant- biais);

	return (float)result;
}


uint32_t EMO_BaseFile::floatToFloat20(float val) const
{
	//Olganix : Sorry, I'm not expert on float structure datas, 
	//and I didn't find a implementation for 20 bits floating point.
	//So if you could do better than this, please do it.
	//http://liu.diva-portal.org/smash/get/diva2:386252/FULLTEXT01.pdf
	//http://www.ntu.edu.sg/home/ehchua/programming/java/datarepresentation.html

	double val_tmp = (double)val;
	double sign = ((val_tmp > 0) ? 1.0 : -1.0);
	val_tmp *= sign;
	int biais = 0x3F / 2;						//6 bits pour l'exposant => 63 au max => 63 /2 = 31
	
	uint32_t exposant = (int)floor(log(val_tmp) / log(2.0)) + biais;
	val_tmp /= pow(2.0, exposant - biais);
	double fraction = val_tmp - 1.0;

	uint32_t mantisse = 0;
	for (size_t i = 0; i < 13; i++)
	{
		double val2_tmp = 1.0 / pow(2.0, i+1);
		if (fraction - val2_tmp >= 0)
		{
			mantisse += (0x1 << (12 - i));
			fraction -= val2_tmp;
		}
	}
	mantisse = (mantisse & 0x1FFF);		//secu

	if (exposant > 0x3F)				//up to the limit => inifinity
		exposant = 0x3F;

	uint32_t result = 0;
	result += (((sign >= 0.0) ? 0 : 1) << 19) | (exposant << 13) | (mantisse);

	return result;
}



void EMO_BaseFile::copy_float(void *x, float val) const
{
	uint32_t *p = (uint32_t *)&val;
	*(uint32_t *)x = val32(*p);
}

void EMO_BaseFile::copy_float16(void *x, float val) const
{
	uint32_t u_32 = *((uint32_t*)&val);
	*(uint16_t *)x = val16(half_from_float(u_32));
}

uint8_t *EMO_BaseFile::GetOffsetPtr(const void *base, uint32_t offset, bool native) const
{
	if (native)
		return ((uint8_t *)base + offset);

	return ((uint8_t *)base + val32(offset));
}

uint8_t *EMO_BaseFile::GetOffsetPtr(const void *base, uint32_t *offsets_table, uint32_t idx, bool native) const
{
	if (native)
		return ((uint8_t *)base + offsets_table[idx]);

	return ((uint8_t *)base + val32(offsets_table[idx]));
}

void EMO_BaseFile::ModTable(uint32_t *offsets, unsigned int count, int mod_by)
{
	for (unsigned int i = 0; i < count; i++)
	{
		offsets[i] = val32(val32(offsets[i]) + mod_by);
	}
}

unsigned int EMO_BaseFile::GetHighestValueIdx(uint32_t *values, unsigned int count, bool native)
{
	unsigned int max_idx = 0xFFFFFFFF;
	uint32_t max = 0;

	for (unsigned int i = 0; i < count; i++)
	{
		uint32_t val = (native) ? values[i] : val32(values[i]);

		if (val > max)
		{
			max = val;
			max_idx = i;
		}
	}

	return max_idx;
}

const char *EMO_BaseFile::FindString(const char *list, const char *str, unsigned int num_str)
{
	for (unsigned int i = 0; i < num_str; i++)
	{
		if (strcmp(list, str) == 0)
			return list;

		list += strlen(list) + 1;
	}

	printf("Iiiiiiiiiiiiiiincoming crash.\n");
	return NULL; // shouldn't happen... s h o u l d n ' t
}


bool EMO_BaseFile::LoadFromFile(const std::string &path, bool show_error)
{
	uint8_t *buf;
	size_t size;

	buf = ReadFile(path, &size, show_error);
	if (!buf)
		return false;

	bool ret = Load(buf, size);
	delete[] buf;

	return ret;
}

bool EMO_BaseFile::SaveToFile(const std::string &path, bool show_error, bool build_path)
{
	unsigned int size;

	uint8_t *buf = CreateFile(&size);

	if (!buf)
		return false;

	bool ret = WriteFileBool(path, buf, size, show_error, build_path);
	delete[] buf;

	return ret;
}

bool EMO_BaseFile::DecompileToFile(const std::string &path, bool show_error, bool build_path)
{
	TiXmlDocument *doc = Decompile();

	if (!doc)
	{
		if (show_error)
		{
			printf("Decompilation of file \"%s\" failed.\n", path.c_str());
			notifyError();
		}

		return false;
	}

	if (build_path)
	{
		if (!CreatePath(path))
		{
			if (show_error)
			{
				printf("Cannot create path for file \"%s\"\n", path.c_str());
				notifyError();
			}

			return false;
		}
	}

	bool ret = doc->SaveFile(path);
	delete doc;

	if (!ret && show_error)
	{
		printf("Cannot create/write file \"%s\"\n", path.c_str());
		notifyError();
	}

	return ret;
}

bool EMO_BaseFile::CompileFromFile(const std::string &path, bool show_error, bool big_endian)
{
	TiXmlDocument doc;

	if (!doc.LoadFile(path))
	{
		if (show_error)
		{
			if (doc.ErrorId() == TiXmlBase::TIXML_ERROR_OPENING_FILE)
			{
				printf("Cannot open file \"%s\"\n", path.c_str());
				notifyError();
			}
			else
			{
				printf("Error parsing file \"%s\". This is what tinyxml has to say: %s. Row=%d, col=%d.\n", path.c_str(), doc.ErrorDesc(), doc.ErrorRow(), doc.ErrorCol());
				notifyError();
			}
		}

		return false;
	}

	bool ret = Compile(&doc, big_endian);

	if (!ret && show_error)
	{
		printf("Compilation of file \"%s\" failed.\n", path.c_str());
		notifyError();
	}

	return ret;
}

bool EMO_BaseFile::SmartLoad(const std::string &path, bool show_error, bool xml_big_endian)
{
	std::string path_tmp = path;
	name = nameFromFilenameNoExtension(path_tmp);

	if (EndsWith(path, ".xml", false))
		return CompileFromFile(path, show_error, xml_big_endian);

	return LoadFromFile(path, show_error);
}

bool EMO_BaseFile::SmartSave(const std::string &path, bool show_error, bool build_path)
{
	if (EndsWith(path, ".xml", false))
		return DecompileToFile(path, show_error, build_path);

	return SaveToFile(path, show_error, build_path);
}


bool EMO_BaseFile::FileExists(const std::string &path)
{
	struct stat info;

	return (stat(path.c_str(), &info) == 0 && S_ISREG(info.st_mode));
}

bool EMO_BaseFile::DirExists(const std::string &path)
{
	struct stat info;

	return (stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode));
}

size_t EMO_BaseFile::GetFileSize(const std::string &path)
{
	struct stat info;

	if (stat(path.c_str(), &info) != 0)
		return (size_t)-1;

	return info.st_size;
}

uint8_t *EMO_BaseFile::ReadFile(const std::string &path, size_t *psize, bool show_error)
{
	FILE *f = fopen(path.c_str(), "rb");
	if (!f)
	{
		if (show_error)
		{
			printf("Cannot open file \"%s\" for reading.\n", path.c_str());
			notifyError();
		}

		return NULL;
	}

	size_t size, rd;

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);

	uint8_t *buf = new uint8_t[size];
	if (!buf)
	{
		printf("%s: Memory allocation error.", FUNCNAME);
		notifyError();
		fclose(f);
		return NULL;
	}

	rd = fread(buf, 1, size, f);
	fclose(f);

	if (rd != size)
	{
		if (show_error)
		{
			printf("Read failure on file \"%s\"\n", path.c_str());
			notifyError();
		}

		delete[] buf;
		return NULL;
	}

	*psize = size;
	return buf;
}

uint8_t *EMO_BaseFile::ReadFileFrom(const std::string &path, size_t from, size_t size, bool show_error)
{
	FILE *f = fopen(path.c_str(), "rb");
	if (!f)
	{
		if (show_error)
		{
			printf("Cannot open file \"%s\" for reading.\n", path.c_str());
			notifyError();
		}

		return NULL;
	}

	size_t rd;

	fseek(f, from, SEEK_SET);

	uint8_t *buf = new uint8_t[size];
	if (!buf)
	{
		printf("%s: Memory allocation error.", FUNCNAME);
		notifyError();
		fclose(f);
		return NULL;
	}

	rd = fread(buf, 1, size, f);
	fclose(f);

	if (rd != size)
	{
		if (show_error)
		{
			printf("Read failure on file \"%s\"\n", path.c_str());
			notifyError();
		}

		delete[] buf;
		return NULL;
	}

	return buf;
}

size_t EMO_BaseFile::WriteFile(const std::string &path, const uint8_t *buf, size_t size, bool show_error, bool write_path)
{
	FILE *f = (write_path) ? EMO_BaseFile::fopen_create_path(path, "wb") : fopen(path.c_str(), "wb");

	if (!f)
	{
		if (show_error)
		{
			printf("Cannot open for write/create file \"%s\"\n", path.c_str());
			notifyError();
		}

		return -1;
	}

	size_t wd = fwrite(buf, 1, size, f);
	fclose(f);

	return wd;
}

bool EMO_BaseFile::WriteFileBool(const std::string &path, const uint8_t *buf, size_t size, bool show_error, bool write_path)
{
	size_t written = EMO_BaseFile::WriteFile(path, buf, size, show_error, write_path);

	if ((int)written < 0)
		return false;

	if (written != size)
	{
		if (show_error)
		{
			printf("Couldn't write same amount of bytes as requestedto file \"%s\" (disk full?)\n", path.c_str());
			notifyError();
		}

		return false;
	}

	return true;
}

bool EMO_BaseFile::Mkdir(const std::string &path)
{
	if (do_mkdir(path.c_str(), 0777) != 0)
	{
		if (errno != EEXIST)
			return false;
	}

	return true;
}

bool EMO_BaseFile::RemoveFile(const std::string &path)
{
	if (remove(path.c_str()) == 0)
		return true;

	return (errno == ENOENT);
}

bool EMO_BaseFile::CreatePath(const std::string &path, bool last_is_directory)
{
	size_t pos = std::string::npos;
	size_t prev_pos = std::string::npos;

	while ((pos = path.find_first_of("/\\", pos + 1)) != std::string::npos)
	{
		std::string current_dir;

		std::string dir = path.substr(0, pos);

		if (prev_pos != std::string::npos)
		{
			current_dir = dir.substr(prev_pos);
		}
		else
		{
			current_dir = dir;
		}

		if (current_dir.find_first_of("%:") == std::string::npos)
		{
			if (do_mkdir(dir.c_str(), 0777) != 0)
			{
				if (errno != EEXIST)
				{
					//printf("returning false on %s\n", dir.c_str());
					return false;
				}
			}
		}

		prev_pos = pos;
	}

	if (!last_is_directory)
		return true;

	if (do_mkdir(path.c_str(), 0777) != 0)
	{
		return (errno == EEXIST);
	}

	return true;
}

FILE *EMO_BaseFile::fopen_create_path(const std::string &filename, const char *mode)
{
	if (!EMO_BaseFile::CreatePath(filename))
		return nullptr;

	return fopen(filename.c_str(), mode);
}

std::string EMO_BaseFile::UnsignedToString(uint32_t value, bool hexadecimal)
{
	char temp[16];
	std::string str;

	if (hexadecimal)
	{
		sprintf(temp, "0x%x", value);
	}
	else
	{
		sprintf(temp, "%u", value);
	}

	str = temp;
	return str;
}

std::string EMO_BaseFile::FloatToString(float value)
{
	char temp[32];
	std::string str;

	sprintf(temp, "%.9g", value);
	str = temp;

	if (str.find('.') == std::string::npos && str.find('e') == std::string::npos)
	{
		str = str + ".0";
	}

	return str;
}

void EMO_BaseFile::TrimString(std::string & str, bool trim_left, bool trim_right)
{
	size_t pos = 0;

	if (trim_left)
	{
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] > ' ' || str[i] < 0)
			{
				pos = i;
				break;
			}
		}

		if (pos != 0)
		{
			str = str.substr(pos);
		}
	}

	if (trim_right)
	{
		pos = str.length() - 1;

		for (size_t i = str.length() - 1; i != std::string::npos; i--)
		{
			if (str[i] > ' ' || str[i] < 0)
			{
				pos = i;
				break;
			}
		}

		if (pos != (str.length() - 1))
		{
			str = str.substr(0, pos + 1);
		}
	}
}

bool EMO_BaseFile::IsEmptyString(const std::string & str)
{
	for (char c : str)
	{
		if (c > ' ' || c < 0)
			return false;
	}

	return true;
}

size_t EMO_BaseFile::GetMultipleStrings(const std::string & str_param, std::vector<std::string> & list)
{
	size_t pos;
	std::string str = str_param;

	list.clear();

	if (str.length() == 0 || str == "NULL")
	{
		return 0;
	}

	while ((pos = str.find(',')) != std::string::npos)
	{
		std::string this_string = str.substr(0, pos);

		if (!IsEmptyString(this_string))
		{
			EMO_BaseFile::TrimString(this_string);
			list.push_back(this_string);
		}

		str = str.substr(pos + 1);
	}

	// Add the last string, 
	if (!IsEmptyString(str))
	{
		EMO_BaseFile::TrimString(str);
		list.push_back(str);
	}

	return list.size();
}

std::string EMO_BaseFile::ToSingleString(const std::vector<std::string> &list)
{
	std::string ret;

	for (const std::string &s : list)
	{
		if (ret.length() != 0)
			ret += ", ";

		ret += s;
	}

	return ret;
}

std::string EMO_BaseFile::ToSingleString(const std::vector<uint32_t> &list, bool hexadecimal)
{
	std::string ret;

	for (uint32_t u : list)
	{
		if (ret.length() != 0)
			ret += ", ";

		ret += UnsignedToString(u, hexadecimal);
	}

	return ret;
}

std::string EMO_BaseFile::ToSingleString(const std::vector<uint16_t> &list, bool hexadecimal)
{
	std::string ret;

	for (uint16_t u : list)
	{
		if (ret.length() != 0)
			ret += ", ";

		ret += UnsignedToString(u, hexadecimal);
	}

	return ret;
}

std::string EMO_BaseFile::ToSingleString(const std::vector<uint8_t> &list, bool hexadecimal)
{
	std::string ret;

	for (uint8_t u : list)
	{
		if (ret.length() != 0)
			ret += ", ";

		ret += UnsignedToString(u, hexadecimal);
	}

	return ret;
}

std::string EMO_BaseFile::ToSingleString(const std::vector<float> &list)
{
	std::string ret;

	for (float f : list)
	{
		if (ret.length() != 0)
			ret += ", ";

		ret += FloatToString(f);
	}

	return ret;
}

std::string EMO_BaseFile::ToLowerCase(const std::string & str)
{
	std::string ret = str;

	for (char &c : ret)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c = c + ('a' - 'A');
		}
	}

	return ret;
}

bool EMO_BaseFile::BeginsWith(const std::string &str, const std::string &substr, bool case_sensitive)
{
	size_t len1 = str.length();
	size_t len2 = substr.length();

	if (len2 > len1)
		return false;

	if (case_sensitive)
		return (str.substr(0, len2) == substr);

	std::string lstr = ToLowerCase(str);
	std::string lsubstr = ToLowerCase(substr);

	return (lstr.substr(0, len2) == lsubstr);
}

bool EMO_BaseFile::EndsWith(const std::string &str, const std::string &substr, bool case_sensitive)
{
	size_t len1 = str.length();
	size_t len2 = substr.length();
	size_t pos;

	if (len2 > len1)
		return false;

	if (case_sensitive)
	{
		pos = str.rfind(substr);
	}
	else
	{
		std::string lstr = ToLowerCase(str);
		std::string lsubstr = ToLowerCase(substr);

		pos = lstr.rfind(lsubstr);
	}

	return (pos == (len1 - len2));
}

std::string EMO_BaseFile::GUID2String(const uint8_t *guid)
{
	std::string ret;

	for (int i = 0; i < 16; i++)
	{
		uint8_t h, l;
		char ch;

		h = guid[i] >> 4;
		l = guid[i] & 0xF;

		if (h <= 9)
			ch = h + '0';
		else
			ch = (h - 10) + 'a';

		ret += ch;

		if (l <= 9)
			ch = l + '0';
		else
			ch = (l - 10) + 'a';

		ret += ch;

		if (i == 3 || i == 5 || i == 7 || i == 9)
			ret += '-';
	}

	return ret;
}

uint32_t EMO_BaseFile::GetUnsigned(const std::string &str, uint32_t default_value)
{
	uint32_t ret = 0;
	size_t len = str.length();

	if (len == 0)
	{
		//printf("WARNING: length of integer string = 0 (param \"%s\"), setting value to 0.\n", param_name.c_str());
		return default_value;
	}

	if (str[0] == '0')
	{
		if (len == 1)
			return 0;

		if (str[1] != 'x')
		{
			/*printf("WARNING: Integer format error on \"%s\". "
			"Value must be decimal values without any 0 on the left, or hexadecimal values with 0x prefix. "
			"Octal values not allowed (offending_string = %s). "
			"Setting value to 0.\n", param_name.c_str(), str.c_str());*/

			return default_value;
		}

		if (len == 2)
		{
			//printf("WARNING: nothing on the right of hexadecimal prefix (on param \"%s\"). Setting value to 0.\n", param_name.c_str());
			return default_value;
		}

		if (sscanf(str.c_str() + 2, "%x", &ret) != 1)
		{
			//printf("sscanf failed on param \"%s\", offending string = \"%s\"\n. Setting value to 0.", param_name.c_str(), str.c_str());
			return default_value;
		}
	}
	else
	{
		if (sscanf(str.c_str(), "%u", &ret) != 1)
		{
			//printf("sscanf failed on param \"%s\", offending string = \"%s\"\n. Setting value to 0.", param_name.c_str(), str.c_str());
			return default_value;
		}
	}

	return ret;
}


long long EMO_BaseFile::GetUnsigned64(const std::string &str, long long default_value)
{
	long long ret = 0;
	size_t len = str.length();

	if (len == 0)
	{
		//printf("WARNING: length of integer string = 0 (param \"%s\"), setting value to 0.\n", param_name.c_str());
		return default_value;
	}

	if (str[0] == '0')
	{
		if (len == 1)
			return 0;

		if (str[1] != 'x')
		{
			/*printf("WARNING: Integer format error on \"%s\". "
			"Value must be decimal values without any 0 on the left, or hexadecimal values with 0x prefix. "
			"Octal values not allowed (offending_string = %s). "
			"Setting value to 0.\n", param_name.c_str(), str.c_str());*/

			return default_value;
		}

		if (len == 2)
		{
			//printf("WARNING: nothing on the right of hexadecimal prefix (on param \"%s\"). Setting value to 0.\n", param_name.c_str());
			return default_value;
		}

		if (sscanf(str.c_str() + 2, "%x", &ret) != 1)
		{
			//printf("sscanf failed on param \"%s\", offending string = \"%s\"\n. Setting value to 0.", param_name.c_str(), str.c_str());
			return default_value;
		}
	}
	else
	{
		if (sscanf(str.c_str(), "%llu", &ret) != 1)
		{
			//printf("sscanf failed on param \"%s\", offending string = \"%s\"\n. Setting value to 0.", param_name.c_str(), str.c_str());
			return default_value;
		}
	}

	return ret;
}

bool EMO_BaseFile::GetBoolean(const std::string &str, bool default_value)
{
	std::string boolean_str = EMO_BaseFile::ToLowerCase(str);

	if (boolean_str == "false" || boolean_str == "0")
		return false;

	if (boolean_str == "true" || GetUnsigned(str) > 0)
		return true;

	return default_value;
}

TiXmlElement *EMO_BaseFile::FindRoot(TiXmlHandle *handle, const std::string &root_name)
{
	for (TiXmlElement *elem = handle->FirstChildElement().Element(); elem != nullptr; elem = elem->NextSiblingElement())
	{
		std::string name = elem->ValueStr();

		if (name == root_name)
		{
			return elem;
		}
	}

	return nullptr;
}

size_t EMO_BaseFile::GetElemCount(const TiXmlElement *root, const char *name)
{
	size_t count = 0;

	for (const TiXmlElement *elem = root->FirstChildElement(); elem; elem = elem->NextSiblingElement())
	{
		if (elem->ValueStr() == name)
		{
			count++;
		}
	}

	return count;
}

void EMO_BaseFile::WriteParamString(TiXmlElement *root, const char *name, const std::string & value)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", value);
	root->LinkEndChild(param);
}

void EMO_BaseFile::WriteParamMultipleStrings(TiXmlElement *root, const char *name, const std::vector<std::string> & values)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", ToSingleString(values));
	root->LinkEndChild(param);
}

void EMO_BaseFile::WriteParamUnsigned(TiXmlElement *root, const char *name, uint32_t value, bool hexadecimal)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", UnsignedToString(value, hexadecimal));
	root->LinkEndChild(param);
}

void EMO_BaseFile::WriteParamMultipleUnsigned(TiXmlElement *root, const char *name, const std::vector<uint32_t> &values, bool hexadecimal)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", ToSingleString(values, hexadecimal));
	root->LinkEndChild(param);
}

void EMO_BaseFile::WriteParamMultipleUnsigned(TiXmlElement *root, const char *name, const std::vector<uint16_t> &values, bool hexadecimal)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", ToSingleString(values, hexadecimal));
	root->LinkEndChild(param);
}

void EMO_BaseFile::WriteParamMultipleUnsigned(TiXmlElement *root, const char *name, const std::vector<uint8_t> &values, bool hexadecimal)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", ToSingleString(values, hexadecimal));
	root->LinkEndChild(param);
}


void EMO_BaseFile::WriteParamFloat(TiXmlElement *root, const char *name, float value)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", FloatToString(value));
	root->LinkEndChild(param);
}

void EMO_BaseFile::WriteParamMultipleFloats(TiXmlElement *root, const char *name, const std::vector<float> &values)
{
	TiXmlElement *param = new TiXmlElement(name);
	param->SetAttribute("value", ToSingleString(values));
	root->LinkEndChild(param);
}

void EMO_BaseFile::WriteParamGUID(TiXmlElement *root, const char *name, const uint8_t *value)
{
	std::string str = EMO_BaseFile::GUID2String(value);
	WriteParamString(root, name, str);
}

void EMO_BaseFile::WriteParamBlob(TiXmlElement *root, const char *name, const uint8_t *value, size_t size)
{
	TiXmlElement *param = new TiXmlElement(name);
	TiXmlText *base64 = new TiXmlText(Base64Encode(value, size, true));

	base64->SetCDATA(true);
	param->LinkEndChild(base64);
	root->LinkEndChild(param);
}

bool EMO_BaseFile::ReadAttrString(const TiXmlElement *root, const char *name, std::string & value)
{
	if (root->QueryStringAttribute(name, &value) != TIXML_SUCCESS)
		return false;

	return true;
}

bool EMO_BaseFile::ReadAttrUnsigned(const TiXmlElement *root, const char *name, uint32_t *value)
{
	std::string str;

	if (root->QueryStringAttribute(name, &str) != TIXML_SUCCESS)
		return false;

	*value = GetUnsigned(str.c_str());
	return true;
}

bool EMO_BaseFile::ReadAttrFloat(const TiXmlElement *root, const char *name, float *value)
{
	std::string str;

	if (root->QueryFloatAttribute(name, value) != TIXML_SUCCESS)
		return false;

	return true;
}

bool EMO_BaseFile::ReadParamString(const TiXmlElement *root, const char *name, std::string & value)
{
	bool found = false;

	for (const TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string str;

		str = elem->ValueStr();

		if (str == name)
		{
			if (elem->QueryStringAttribute("value", &value) != TIXML_SUCCESS)
				return false;

			found = true;
			break;
		}
	}

	return found;
}

bool EMO_BaseFile::ReadParamMultipleStrings(const TiXmlElement *root, const char *name, std::vector<std::string> & values)
{
	std::string str;

	if (!ReadParamString(root, name, str))
		return false;

	GetMultipleStrings(str, values);
	return true;
}

bool EMO_BaseFile::ReadParamUnsigned(const TiXmlElement *root, const char *name, uint32_t *value)
{
	std::string str;

	if (!ReadParamString(root, name, str))
		return false;

	*value = GetUnsigned(str.c_str());
	return true;
}

bool EMO_BaseFile::ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint32_t> &values)
{
	std::vector<std::string> values_str;

	values.clear();

	if (!ReadParamMultipleStrings(root, name, values_str))
		return false;

	values.reserve(values_str.size());

	for (const std::string &s : values_str)
	{
		values.push_back(GetUnsigned(s.c_str()));
	}

	return true;
}

bool EMO_BaseFile::ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint16_t> &values)
{
	std::vector<std::string> values_str;

	values.clear();

	if (!ReadParamMultipleStrings(root, name, values_str))
		return false;

	values.reserve(values_str.size());

	for (const std::string &s : values_str)
	{
		uint32_t value = GetUnsigned(s.c_str());

		if (value > 0xFFFF)
			return false;

		values.push_back(value);
	}

	return true;
}

bool EMO_BaseFile::ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint8_t> &values)
{
	std::vector<std::string> values_str;

	values.clear();

	if (!ReadParamMultipleStrings(root, name, values_str))
		return false;

	values.reserve(values_str.size());

	for (const std::string &s : values_str)
	{
		uint32_t value = GetUnsigned(s.c_str());

		if (value > 0xFF)
			return false;

		values.push_back(value);
	}

	return true;
}

bool EMO_BaseFile::ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint32_t *values, size_t count)
{
	std::vector<uint32_t> vec;

	if (!ReadParamMultipleUnsigned(root, name, vec))
		return false;

	if (vec.size() != count)
		return false;

	memcpy(values, vec.data(), count*sizeof(uint32_t));
	return true;
}

bool EMO_BaseFile::ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint16_t *values, size_t count)
{
	std::vector<uint16_t> vec;

	if (!ReadParamMultipleUnsigned(root, name, vec))
		return false;

	if (vec.size() != count)
		return false;

	memcpy(values, vec.data(), count*sizeof(uint16_t));
	return true;
}

bool EMO_BaseFile::ReadParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint8_t *values, size_t count)
{
	std::vector<uint8_t> vec;

	if (!ReadParamMultipleUnsigned(root, name, vec))
		return false;

	if (vec.size() != count)
		return false;

	memcpy(values, vec.data(), count*sizeof(uint8_t));
	return true;
}

bool EMO_BaseFile::ReadParamFloat(const TiXmlElement *root, const char *name, float *value)
{
	bool found = false;

	for (const TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string str;

		str = elem->ValueStr();

		if (str == name)
		{
			if (elem->QueryFloatAttribute("value", value) != TIXML_SUCCESS)
				return false;

			found = true;
			break;
		}
	}

	return found;
}

bool EMO_BaseFile::ReadParamMultipleFloats(const TiXmlElement *root, const char *name, std::vector<float> &values)
{
	std::vector<std::string> values_str;

	values.clear();

	if (!ReadParamMultipleStrings(root, name, values_str))
		return false;

	values.reserve(values_str.size());

	for (const std::string &s : values_str)
	{
		float value;

		if (sscanf(s.c_str(), "%f", &value) != 1)
			return false;

		values.push_back(value);
	}

	return true;
}

bool EMO_BaseFile::ReadParamMultipleFloats(const TiXmlElement *root, const char *name, float *values, size_t count)
{
	std::vector<float> vec;

	if (!ReadParamMultipleFloats(root, name, vec))
		return false;

	if (vec.size() != count)
		return false;

	memcpy(values, vec.data(), count*sizeof(float));
	return true;
}

bool EMO_BaseFile::ReadParamGUID(const TiXmlElement *root, const char *name, uint8_t *value)
{
	std::string guid;

	if (!ReadParamString(root, name, guid))
		return false;

	TrimString(guid);

	if (guid.length() != 36)
		return false;

	bool high_flag = true;
	uint8_t h = 0;

	for (size_t i = 0, j = 0; i < guid.length(); i++)
	{
		if (i == 8 || i == 13 || i == 18 || i == 23)
		{
			if (guid[i] != '-')
				return false;
		}
		else
		{
			uint8_t d;

			if (guid[i] >= '0' && guid[i] <= '9')
			{
				d = guid[i] - '0';
			}
			else if (guid[i] >= 'a' && guid[i] <= 'f')
			{
				d = guid[i] - 'a' + 10;
			}
			else if (guid[i] >= 'A' && guid[i] <= 'F')
			{
				d = guid[i] - 'A' + 10;
			}
			else
			{
				return false;
			}

			if (high_flag)
			{
				h = d << 4;
			}
			else
			{
				value[j++] = h | d;
			}

			high_flag = !high_flag;
		}
	}

	return true;
}

uint8_t *EMO_BaseFile::ReadParamBlob(const TiXmlElement *root, const char *name, size_t *psize)
{
	for (const TiXmlElement *elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		std::string str;

		str = elem->ValueStr();

		if (str == name)
		{
			std::string base64_data = elem->GetText();
			return Base64Decode(base64_data, psize);
		}
	}

	return nullptr;
}

bool EMO_BaseFile::ReadParamUnsignedWithMultipleNames(const TiXmlElement *root, uint32_t *value, const char *name1, const char *name2, const char *name3, const char *name4, const char *name5)
{
	if (ReadParamUnsigned(root, name1, value))
		return true;

	if (ReadParamUnsigned(root, name2, value))
		return true;

	if (name3 && ReadParamUnsigned(root, name3, value))
		return true;

	if (name4 && ReadParamUnsigned(root, name4, value))
		return true;

	return (name5 && ReadParamUnsigned(root, name5, value));
}

bool EMO_BaseFile::ReadParamFloatWithMultipleNames(const TiXmlElement *root, float *value, const char *name1, const char *name2, const char *name3, const char *name4, const char *name5)
{
	if (ReadParamFloat(root, name1, value))
		return true;

	if (ReadParamFloat(root, name2, value))
		return true;

	if (name3 && ReadParamFloat(root, name3, value))
		return true;

	if (name4 && ReadParamFloat(root, name4, value))
		return true;

	return (name5 && ReadParamFloat(root, name5, value));
}

bool EMO_BaseFile::GetParamString(const TiXmlElement *root, const char *name, std::string & value)
{
	if (!ReadParamString(root, name, value))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleStrings(const TiXmlElement *root, const char *name, std::vector<std::string> & values)
{
	if (!ReadParamMultipleStrings(root, name, values))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamUnsigned(const TiXmlElement *root, const char *name, uint32_t *value)
{
	if (!ReadParamUnsigned(root, name, value))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint32_t> &values)
{
	if (!ReadParamMultipleUnsigned(root, name, values))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint16_t> &values)
{
	if (!ReadParamMultipleUnsigned(root, name, values))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, std::vector<uint8_t> &values)
{
	if (!ReadParamMultipleUnsigned(root, name, values))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint32_t *values, size_t count)
{
	if (!ReadParamMultipleUnsigned(root, name, values, count))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint16_t *values, size_t count)
{
	if (!ReadParamMultipleUnsigned(root, name, values, count))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleUnsigned(const TiXmlElement *root, const char *name, uint8_t *values, size_t count)
{
	if (!ReadParamMultipleUnsigned(root, name, values, count))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamFloat(const TiXmlElement *root, const char *name, float *value)
{
	if (!ReadParamFloat(root, name, value))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleFloats(const TiXmlElement *root, const char *name, std::vector<float> &values)
{
	if (!ReadParamMultipleFloats(root, name, values))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamMultipleFloats(const TiXmlElement *root, const char *name, float *values, size_t count)
{
	if (!ReadParamMultipleFloats(root, name, values, count))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamGUID(const TiXmlElement *root, const char *name, uint8_t *value)
{
	if (!ReadParamGUID(root, name, value))
	{
		printf("Cannot read parameter \"%s\"\n", name);
		return false;
	}

	return true;
}

uint8_t *EMO_BaseFile::GetParamBlob(const TiXmlElement *root, const char *name, size_t *psize)
{
	uint8_t *ret = ReadParamBlob(root, name, psize);
	if (!ret)
	{
		printf("Cannot read parameter \"%s\"\n", name);
	}

	return ret;
}

bool EMO_BaseFile::GetParamUnsignedWithMultipleNames(const TiXmlElement *root, uint32_t *value, const char *name1, const char *name2, const char *name3, const char *name4, const char *name5)
{
	if (!ReadParamUnsignedWithMultipleNames(root, value, name1, name2, name3, name4, name5))
	{
		printf("Cannot read parameter \"%s\"\n", name1);
		return false;
	}

	return true;
}

bool EMO_BaseFile::GetParamFloatWithMultipleNames(const TiXmlElement *root, float *value, const char *name1, const char *name2, const char *name3, const char *name4, const char *name5)
{
	if (!ReadParamFloatWithMultipleNames(root, value, name1, name2, name3, name4, name5))
	{
		printf("Cannot read parameter \"%s\"\n", name1);
		return false;
	}

	return true;
}

void EMO_BaseFile::WriteComment(TiXmlElement *root, const std::string & comment)
{
	TiXmlComment *tx_comment = new TiXmlComment();

	tx_comment->SetValue(comment);
	root->LinkEndChild(tx_comment);
}

std::string EMO_BaseFile::ModelFileName(uint32_t cms_entry, uint32_t cms_model_spec_idx, const char *ext)
{
	char filename[48];

	snprintf(filename, sizeof(filename), "0x%x_%d%s", cms_entry, cms_model_spec_idx, ext);
	return std::string(filename);
}

int EMO_BaseFile::RandomInt(int min, int max)
{
	static bool started = false;

	if (max <= min)
		return 0;

	if (!started)
	{
		std::srand((unsigned int)std::time(0));
		started = true;
	}

	int rnd = std::rand() % (max - min);
	return rnd + min;
}

std::string EMO_BaseFile::GetRandomString(size_t len)
{
	static bool started = false;
	std::string s;

	if (!started)
	{
		std::srand((unsigned int)std::time(0));
		started = true;
	}

	for (unsigned int i = 0; i < len; i++)
	{
		char ch;

		if (std::rand() & 1)
		{
			ch = 'A';
		}
		else
		{
			ch = 'a';
		}

		ch += (std::rand() % 26);
		s += ch;
	}

	return s;
}

static int utf8_to_ucs2(const unsigned char * input, const unsigned char ** end_ptr)
{
	*end_ptr = input;
	if (input[0] == 0) {
		return -1;
	}
	if (input[0] < 0x80) {
		/* One byte (ASCII) case. */
		*end_ptr = input + 1;
		return input[0];
	}
	if ((input[0] & 0xE0) == 0xE0) {
		/* Three byte case. */
		if (input[1] < 0x80 || input[1] > 0xBF ||
			input[2] < 0x80 || input[2] > 0xBF) {
			return -1;
		}
		*end_ptr = input + 3;
		return
			(input[0] & 0x0F) << 12 |
			(input[1] & 0x3F) << 6 |
			(input[2] & 0x3F);
	}
	if ((input[0] & 0xC0) == 0xC0) {
		/* Two byte case. */
		if (input[1] < 0x80 || input[1] > 0xBF) {
			return -1;
		}
		*end_ptr = input + 2;
		return
			(input[0] & 0x1F) << 6 |
			(input[1] & 0x3F);
	}
	return -1;
}

std::u16string EMO_BaseFile::Utf8ToUcs2(const std::string & utf8)
{
	if (utf8.length() == 0)
	{
		return std::u16string(); // Empty string
	}

	const char *c_utf8 = utf8.c_str();
	std::u16string ucs2;
	int ret;

	while (*c_utf8 != 0 && (ret = utf8_to_ucs2((const unsigned char *)c_utf8, (const unsigned char **)&c_utf8)) != -1)
	{
		if (ret < 0x10000)
			ucs2.push_back((char16_t)ret);
	}

	return ucs2;
}

static int ucs2_to_utf8(int ucs2, unsigned char * utf8)
{
	if (ucs2 < 0x80) {
		utf8[0] = ucs2;
		utf8[1] = '\0';
		return 1;
	}
	if (ucs2 >= 0x80 && ucs2 < 0x800) {
		utf8[0] = (ucs2 >> 6) | 0xC0;
		utf8[1] = (ucs2 & 0x3F) | 0x80;
		utf8[2] = '\0';
		return 2;
	}
	if (ucs2 >= 0x800 && ucs2 < 0xFFFF) {
		if (ucs2 >= 0xD800 && ucs2 <= 0xDFFF) {
			/* Ill-formed. */
			return -1;
		}
		utf8[0] = ((ucs2 >> 12)) | 0xE0;
		utf8[1] = ((ucs2 >> 6) & 0x3F) | 0x80;
		utf8[2] = ((ucs2)& 0x3F) | 0x80;
		utf8[3] = '\0';
		return 3;
	}
	if (ucs2 >= 0x10000 && ucs2 < 0x10FFFF) {
		/* http://tidy.sourceforge.net/cgi-bin/lxr/source/src/utf8.c#L380 */
		utf8[0] = 0xF0 | (ucs2 >> 18);
		utf8[1] = 0x80 | ((ucs2 >> 12) & 0x3F);
		utf8[2] = 0x80 | ((ucs2 >> 6) & 0x3F);
		utf8[3] = 0x80 | ((ucs2 & 0x3F));
		utf8[4] = '\0';
		return 4;
	}
	return -1;;
}

std::string EMO_BaseFile::Ucs2ToUtf8(const std::u16string & ucs2)
{
	if (ucs2.length() == 0)
		return "";

	std::string utf8;

	for (char16_t c : ucs2)
	{
		char c_utf8[5];

		if (ucs2_to_utf8(c, (unsigned char *)c_utf8) < 0)
			break;

		utf8 += c_utf8;
	}

	return utf8;
}

static const std::string base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string EMO_BaseFile::Base64Encode(const uint8_t *buf, size_t size, bool add_new_line)
{
	std::string ret;
	size_t written = 0;

	if (add_new_line)
		ret += '\n';

	for (size_t i = 0; i < size; i += 3)
	{
		unsigned int st;

		st = (buf[i] & 0xFC) >> 2;
		ret += base64_table[st];
		written++;

		st = (buf[i] & 3) << 4;

		if (i + 1 < size)
		{
			st |= (buf[i + 1] & 0xF0) >> 4;
			ret += base64_table[st];
			written++;

			st = (buf[i + 1] & 0xF) << 2;

			if (i + 2 < size)
			{
				st |= (buf[i + 2] & 0xC0) >> 6;
				ret += base64_table[st];

				st = buf[i + 2] & 0x3F;
				ret += base64_table[st];
				written += 2;
			}
			else
			{
				ret += base64_table[st];
				ret += '=';
				written += 2;
			}
		}
		else
		{
			ret += base64_table[st];
			ret += "==";
			written += 3;
		}

		if (((written % 76) == 0) && (i + 3 < size))
			ret += '\n';
	}

	if (add_new_line && ret[ret.length() - 1] != '\n')
		ret += '\n';

	return ret;
}

uint8_t *EMO_BaseFile::Base64Decode(const std::string &data, size_t *ret_size)
{
	char empty_chars[33];

	for (int c = 1; c < 33; c++)
		empty_chars[c - 1] = c;

	empty_chars[32] = 0;

	size_t empty_count = 0;
	size_t pos = data.find_first_of(empty_chars);

	while (pos != std::string::npos)
	{
		empty_count++;
		pos = data.find_first_of(empty_chars, pos + 1);
	}

	size_t data_len = data.length() - empty_count;

	if ((data_len % 4) != 0)
		return nullptr;

	*ret_size = (data_len * 3) / 4;

	if (data.rfind('=') != std::string::npos)
	{
		size_t pos = data.find_last_not_of(empty_chars);

		if (pos == std::string::npos)
			*ret_size = *ret_size - data.length();
		else
			*ret_size = *ret_size - (pos + 1 - data.find('='));
	}

	uint8_t *buf = new uint8_t[*ret_size];
	if (!buf)
	{
		printf("%s: Memory allocation error 0x%x\n", FUNCNAME, *ret_size);
		notifyError();
		return nullptr;
	}

	size_t st[4];
	size_t n = 0;
	size_t i = 0;

	while (i < data.length())
	{
		if (data[i] <= ' ')
		{
			i++;
			continue;
		}

		for (size_t j = 0; j < 4; j++)
		{
			st[j] = base64_table.find(data[i + j]);
			if (st[j] == std::string::npos)
			{
				if (data[i + j] != '=' || i + j < (data_len - 2))
				{
					//printf("Fail: %x\n", data[i+j]);
					delete[] buf;
					return nullptr;
				}
			}
		}

		buf[n++] = (st[0] << 2) | (st[1] >> 4);
		if (st[2] != std::string::npos)
		{
			buf[n++] = (st[1] << 4) | (st[2] >> 2);
			if (st[3] != std::string::npos)
			{
				buf[n++] = (st[2] << 6) | st[3];
			}
		}

		i += 4;
	}

	assert(n == *ret_size);

	return buf;
}

std::string EMO_BaseFile::GetAppData()
{
	char *appdata = getenv("APPDATA");

	if (!appdata)
	{
		printf("APPDATA doesn't exist in this system.\n");
		notifyError();
		throw std::runtime_error("APPDATA doesn't exist in this system.\n");
	}

	return std::string(appdata);
}

#ifdef _WIN32

#include <windows.h>

std::string EMO_BaseFile::GetTempFile(const std::string &prefix, const std::string &extension)
{
	char path[MAX_PATH - 14];
	char file[MAX_PATH];

	if (GetTempPathA(sizeof(path), path) == 0)
		return "<NULL>";

	if (GetTempFileNameA(path, prefix.c_str(), RandomInt(0, INT_MAX), file) == 0)
		return "<NULL>";

	return std::string(file) + extension;
}

#endif

void EMO_BaseFile::RunProgram(const std::string &program, const std::vector<std::string> &args)
{
	std::string cmd;

	cmd = program;

	for (const std::string &s : args)
	{
		cmd += " \"" + s + '"';
	}

	system(cmd.c_str());
}
