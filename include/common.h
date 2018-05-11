

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
		Vector3 operator- () const { return Vector3(-x, -y, -z); }
		Vector3 operator+ (const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
		Vector3 operator- (const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
		double Length() { return sqrt(x *x + y *y + z * z); }
		void Normalize() { double length = Length(); if (length != 0.0) { x /= length; y /= length; z /= length; } }
		static bool equals(Vector3 a, Vector3 b, double eps = 0.000001) { return (a - b).Length() < eps ; }
		static const Vector3 zero;
		static const Vector3 unit;
		static const Vector3 unit_X;
		static const Vector3 unit_Y;
		static const Vector3 unit_Z;
		static const Vector3 unit_nX;
		static const Vector3 unit_nY;
		static const Vector3 unit_nZ;
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
		Quaternion operator* (double fScalar) const { return Quaternion(fScalar*w, fScalar*x, fScalar*y, fScalar*z); }
		//Quaternion operator* (double fScalar, const Quaternion& rkQ){return Quaternion(fScalar*rkQ.w, fScalar*rkQ.x, fScalar*rkQ.y,fScalar*rkQ.z);}
		Quaternion operator- () const {return Quaternion(-w, -x, -y, -z);}
		Quaternion operator+ (const Quaternion& rkQ) const { return Quaternion(w + rkQ.w, x + rkQ.x, y + rkQ.y, z + rkQ.z); }
		Quaternion operator- (const Quaternion& rkQ) const { return Quaternion(w - rkQ.w, x - rkQ.x, y - rkQ.y, z - rkQ.z); }
		inline Quaternion& operator= (const Quaternion& rkQ) { w = rkQ.w; x = rkQ.x; y = rkQ.y; z = rkQ.z; return *this; }
		double Norm() const {return w*w + x*x + y*y + z*z;}
		double Dot(const Quaternion& rkQ) const{ return w*rkQ.w + x*rkQ.x + y*rkQ.y + z*rkQ.z; }
		double normalise(void) { double len = Norm(); double factor = 1.0f / sqrt(len); *this = *this * factor; return len; }
	};
	Vector3 crossProduct(const Vector3& vec, const Vector3& rkVector);
	Quaternion quatMulQuat(const Quaternion &quat, const Quaternion &rkQ);		//from Ogre Quaternion Quaternion::operator* (const Quaternion& rkQ) const
	Quaternion fromAngleAxis(const double& rfAngle, const Vector3& rkAxis);			//from Ogre Quaternion::FromAngleAxis
	Quaternion Slerp(double factor, Quaternion rkP, Quaternion rkQ, bool shortestPath);	//from Ogre Quaternion
	void decomposition4x4(double* transformMatrix, double* resultPosOrientScaleMatrix); //posOrientScaleMatrix is 3x4, orient is a quaternion informations, TransformMatrix is 4x4
	Vector3 giveAngleOrientationForThisOrientationTaitBryan(Quaternion orient);
	void keepTaitBryanAnglesGood(Vector3 previousAngles, Vector3 &currentAngles);
	Vector3 giveAngleOrientationForThisOrientationTaitBryan_XYZ(Quaternion orient);				//same version, but with this order of rotation, the yaw is on the diqs display by pitch rotation.
	void quadToRotationMatrix(Quaternion orient, Vector3 &m0, Vector3 &m1, Vector3 &m2);
	void clampNear(double value, double min = -1, double max = 1, double eps = 0.000001);
	void clampNear(Vector3 value, Vector3 min = Vector3(-1,-1,-1), Vector3 max = Vector3(1,1,1), double eps = 0.000001);
	bool matrixToEulerAnglesZYX(Vector3 m0, Vector3 m1, Vector3 m2, Vector3 &YPR_angles);
}

#endif
