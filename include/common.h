

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


// Common Includes		TODO making good for linux.
#include "half.h"
#include <algorithm>
#include <iomanip>
#include <vector>

#include "tinyxml.h"

using namespace std;


#include <sstream>
#include <deque>
#include <iostream>
#include <ctime>
#include "dirent.h"

using namespace std;

template< class Type >
string ToString( Type value ) {
   stringstream s;
   s << value;
   return s.str();
}

template <class T>
bool FromString(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}









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
	bool fileCheck(string filename);
	std::vector<string> getFilesInFolder(string folderpath);
	
	//string
	std::vector<std::string> split(const std::string &text, char sep);
	string toLowerCase(string str);
	string toUpperCase(string str);

	//math
	void decomposition4x4(double* transformMatrix, double* resultPosOrientScaleMatrix); //posOrientScaleMatrix is 3x4, orient is a quaternion informations, TransformMatrix is 4x4
}

#endif
