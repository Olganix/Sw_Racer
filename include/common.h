

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


// Common Includes
#include "half.h"
#include <algorithm>
#include <iomanip>
#include <vector>

// For sqrt
#include <cmath>

#include "tinyxml.h"

using namespace std;


#include <sstream>
#include <deque>
#include <iostream>
#include <ctime>
#ifdef _MSC_VER
#include "vs/dirent.h"
#else
#include <dirent.h>
#endif


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
	struct Vector2
	{
		double x; double y;
		Vector2(double x = 0, double y = 0) { this->x = x; this->y = y;}
		double Length() { return sqrt(x *x + y *y); }
		void Normalize() { double length = Length(); if (length != 0.0) { x /= length; y /= length; } }
		static const Vector2 zero;
	};
	struct Vector3
	{
		double x; double y; double z;
		Vector3(double x = 0, double y = 0, double z = 0) { this->x = x; this->y = y; this->z = z;}
		double Length() { return sqrt(x *x + y *y + z * z); }
		void Normalize() { double length = Length(); if (length != 0.0) { x /= length; y /= length; z /= length; } }
		static const Vector3 zero;
	};
	struct Quaternion
	{
		double x;
		double y;
		double z;
		double w;
		Quaternion(double x = 0, double y = 0, double z = 0, double w = 1) { this->x = x; this->y = y; this->z = z; this->w = w;}
		Vector3 quatMulVec3(Vector3 vect);
		static const Quaternion iddentity;
	};
	Vector3 crossProduct(const Vector3& vec, const Vector3& rkVector);
	Quaternion quatMulQuat(const Quaternion &quat, const Quaternion &rkQ);		//from Ogre Quaternion Quaternion::operator* (const Quaternion& rkQ) const
	Quaternion fromAngleAxis(const double& rfAngle, const Vector3& rkAxis);			//from Ogre Quaternion::FromAngleAxis
	void decomposition4x4(double* transformMatrix, double* resultPosOrientScaleMatrix); //posOrientScaleMatrix is 3x4, orient is a quaternion informations, TransformMatrix is 4x4
	Vector3 giveAngleOrientationForThisOrientationTaitBryan(Quaternion orient);
	void keepTaitBryanAnglesGood(Vector3 previousAngles, Vector3 &currentAngles);
	
}

#endif
