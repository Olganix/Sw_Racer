

#include "common.h"



namespace Common
{

	bool HAVE_WARNINGS = false;
	bool HAVE_ERRORS = false;
	ApplicationEndWait applicationEndWait = AEW_OnError;



	void setWarningErrorsFalse() { HAVE_WARNINGS = false; HAVE_ERRORS = false; }
	void notifyWarning() { HAVE_WARNINGS = true; }
	void notifyError() { HAVE_ERRORS = true; }
	void setApplicationEndWait(ApplicationEndWait aew) { applicationEndWait = aew; }
	bool haveToWait()
	{
		if (applicationEndWait == AEW_Always)
			return true;
		else if (applicationEndWait == AEW_None)
			return false;
		else if (applicationEndWait == AEW_OnError)
			return HAVE_ERRORS;
		else if (applicationEndWait == AEW_OnWarning)
			return HAVE_WARNINGS;
		return false;
	}
	void waitOnEnd() { if (haveToWait()) { printf("press Enter to continue ...\n");  getchar(); } }




	std::vector<string> initApplication(int argc, char** argv, ApplicationEndWait applicationEndWait)
	{
		setWarningErrorsFalse();
		setApplicationEndWait(applicationEndWait);

		std::vector<string> arguments;
		string str_tmp = "";
		string str2_tmp = "";
		for (int i = 1; i < argc; i++)									//detection of options, remove then from arguments list, plus take care of folder with spaces inside (use " ")
		{
			str_tmp = ToString(argv[i]);
			if ((str2_tmp.length() == 0) && (str_tmp.length() == 0))
				continue;

			if (str_tmp == "-NoWait")
			{
				setApplicationEndWait(AEW_None);
				continue;
			}
			else if (str_tmp == "-AlwaysWait") {
				setApplicationEndWait(AEW_Always);
				continue;
			}
			else if (str_tmp == "-WaitOnError") {
				setApplicationEndWait(AEW_OnError);
				continue;
			}
			else if (str_tmp == "-WaitOnWarning") {
				setApplicationEndWait(AEW_OnWarning);
				continue;
			}

			if ((str2_tmp.length() == 0) && (str_tmp[0] == '"'))
			{
				if (str_tmp[str_tmp.length() - 1] != '"')
				{
					str2_tmp = str_tmp.substr(1);
				}
				else {
					str2_tmp = str_tmp.substr(1, str_tmp.length() - 2);
					arguments.push_back(str2_tmp);
					str2_tmp = "";
				}
				continue;

			}
			else if (str2_tmp.length() != 0) {

				str2_tmp += " " + str_tmp;

				if (str_tmp[str_tmp.length() - 1] == '"')
				{
					arguments.push_back(str2_tmp.substr(0, str2_tmp.length() - 1));
					str2_tmp = "";
				}
				continue;
			}

			arguments.push_back(str_tmp);
		}
		if (str2_tmp.length() != 0)					//put the last argument if they miss a " at the end
			arguments.push_back(str2_tmp);

		return arguments;
	}



	string extensionFromFilename(string filename, bool last_dot)
	{
		string name = filename;
		size_t sep = name.find_last_of("\\/");
		if (sep != std::string::npos) {
			name = name.substr(sep + 1, name.size() - sep - 1);
		}

		size_t dot = string::npos;
		if (last_dot) dot = name.find_last_of(".");
		else dot = name.find_first_of(".");

		if (dot != string::npos) {
			name = name.substr(dot + 1, name.size() - dot - 1);
		}
		else {
			name = "";
		}

		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		return name;
	}

	string nameFromFilename(string filename)
	{
		string name = filename;
		size_t sep = name.find_last_of("\\/");
		if (sep != std::string::npos) {
			name = name.substr(sep + 1, name.size() - sep - 1);
		}
		return name;
	}

	string nameFromFilenameNoExtension(string filename, bool last_dot)
	{
		string name = filename;
		size_t sep = name.find_last_of("\\/");
		if (sep != std::string::npos) {
			name = name.substr(sep + 1, name.size() - sep - 1);
		}

		size_t dot = string::npos;
		if (last_dot) dot = name.find_last_of(".");
		else dot = name.find_first_of(".");

		if (dot != string::npos) {
			name = name.substr(0, dot);
		}

		return name;
	}

	string filenameNoExtension(string filename)
	{
		string name = filename;

		size_t dot = string::npos;
		dot = name.find_last_of(".");

		if (dot != string::npos) {
			name = name.substr(0, dot);
		}

		return name;
	}

	string folderFromFilename(string filename)
	{
		size_t sep = filename.find_last_of("\\/");
		if (sep != std::string::npos) {
			return filename.substr(0, sep + 1);
		}

		return "";
	}

}