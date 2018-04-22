

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


// Common Includes		TODO making good for linux.
#include "half.h"
#include <algorithm>
#include <iomanip>
#include <vector>

#include "tinyxml.h"

using namespace std;









namespace Common
{
	//help for application preference conditions of ending
	enum ApplicationEndWait
	{
		AEW_None = 0,
		AEW_OnError,
		AEW_OnWarning,
		AEW_Always,
	};

	extern bool HAVE_WARNINGS;
	extern bool HAVE_ERRORS;
	extern ApplicationEndWait applicationEndWait;

	void setWarningErrorsFalse();
	void notifyWarning();
	void notifyError();
	void setApplicationEndWait(ApplicationEndWait aew);
	bool haveToWait();
	void waitOnEnd();

	std::vector<string> initApplication(int argc, char** argv, ApplicationEndWait applicationEndWait = AEW_OnError);


	//Files
	string extensionFromFilename(string filename, bool last_dot = false);
	string nameFromFilename(string filename);
	string nameFromFilenameNoExtension(string filename, bool last_dot = false);
	string folderFromFilename(string filename);
	string filenameNoExtension(string filename);
}

#endif