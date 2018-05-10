#include <math.h>

#include "common.h"
#include "EMO_BaseFile.h"



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

	bool fileCheck(string filename)
	{
		FILE *fp = fopen(filename.c_str(), "rb");

		if (fp)
		{
			fclose(fp);
			return true;
		}
		return false;
	}




	std::vector<string> getFilesInFolder(string folderpath)
	{
		std::vector<string> listFilename;

		struct dirent **namelist;

		int n;

		n = scandir(folderpath.c_str(), &namelist, 0, alphasort);

		if (n < 0)
		{
			perror("scandir");
		}else{

			while (n--)
			{
				//printf("%s\n", namelist[n]->d_name);
				if (namelist[n]->d_name[0] != '.')
					listFilename.push_back(namelist[n]->d_name);
				free(namelist[n]);
			}
			free(namelist);
		}
		return listFilename;
	}


	std::vector<std::string> split(const std::string &text, char sep)
	{
		std::vector<std::string> tokens;
		std::size_t start = 0, end = 0;
		while ((end = text.find(sep, start)) != std::string::npos) {
			tokens.push_back(text.substr(start, end - start));
			start = end + 1;
		}
		tokens.push_back(text.substr(start));
		return tokens;
	}
	string toLowerCase(string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}
	string toUpperCase(string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::toupper);
		return str;
	}



	/*-------------------------------------------------------------------------------\
	|                             decomposition4x4		                             |
	\-------------------------------------------------------------------------------*/
	void decomposition4x4(double* transformMatrix, double* resultPosOrientScaleMatrix)//posOrientScaleMatrix is 3x4, orient is a quaternion informations, TransformMatrix is 4x4
	{
		double m00 = transformMatrix[0], m01 = transformMatrix[1], m02 = transformMatrix[2], m03 = transformMatrix[3];
		double m10 = transformMatrix[4], m11 = transformMatrix[5], m12 = transformMatrix[6], m13 = transformMatrix[7];
		double m20 = transformMatrix[8], m21 = transformMatrix[9], m22 = transformMatrix[10], m23 = transformMatrix[11];
		double m30 = transformMatrix[12], m31 = transformMatrix[13], m32 = transformMatrix[14], m33 = transformMatrix[15];

		if (!((abs(m30) <= 0.000001) && (abs(m31) <= 0.000001) && (abs(m32) <= 0.000001) && (abs(m33 - 1) <= 0.000001)))		//assert(isAffine());
			return;

		//position
		resultPosOrientScaleMatrix[0] = transformMatrix[3];
		resultPosOrientScaleMatrix[1] = transformMatrix[7];
		resultPosOrientScaleMatrix[2] = transformMatrix[11];
		resultPosOrientScaleMatrix[3] = transformMatrix[15];


		//Matrix3 matQ;
		//Vector3 vecU;
		//m3x3.QDUDecomposition(matQ, scale, vecU);



		// Factor M = QR = QDU where Q is orthogonal, D is diagonal,
		// and U is upper triangular with ones on its diagonal.  Algorithm uses
		// Gram-Schmidt orthogonalization (the QR algorithm).
		//
		// If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
		//
		//   q0 = m0/|m0|
		//   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
		//   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
		//
		// where |V| indicates length of vector V and A*B indicates dot
		// product of vectors A and B.  The matrix R has entries
		//
		//   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
		//   r10 = 0      r11 = q1*m1  r12 = q1*m2
		//   r20 = 0      r21 = 0      r22 = q2*m2
		//
		// so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
		// u02 = r02/r00, and u12 = r12/r11.

		// Q = rotation
		// D = scaling
		// U = shear

		// D stores the three diagonal entries r00, r11, r22
		// U stores the entries U[0] = u01, U[1] = u02, U[2] = u12


		// build orthogonal matrix Q
		double fInvLength = 1.0 / sqrt(m00 * m00 + m10 * m10 + m20 * m20);
		double kQ_00 = m00 * fInvLength;
		double kQ_10 = m10 * fInvLength;
		double kQ_20 = m20 * fInvLength;

		double fDot = kQ_00 * m01 + kQ_10 * m11 + kQ_20 * m21;
		double kQ_01 = m01 - fDot * kQ_00;
		double kQ_11 = m11 - fDot * kQ_10;
		double kQ_21 = m21 - fDot * kQ_20;
		fInvLength = 1.0 / sqrt(kQ_01 * kQ_01 + kQ_11 * kQ_11 + kQ_21 * kQ_21);
		kQ_01 *= fInvLength;
		kQ_11 *= fInvLength;
		kQ_21 *= fInvLength;

		fDot = kQ_00 * m02 + kQ_10 * m12 + kQ_20 * m22;
		double kQ_02 = m02 - fDot*kQ_00;
		double kQ_12 = m12 - fDot*kQ_10;
		double kQ_22 = m22 - fDot*kQ_20;
		fDot = kQ_01 * m02 + kQ_11 * m12 + kQ_21 * m22;
		kQ_02 -= fDot*kQ_01;
		kQ_12 -= fDot*kQ_11;
		kQ_22 -= fDot*kQ_21;
		fInvLength = 1.0 / sqrt(kQ_02 * kQ_02 + kQ_12 * kQ_12 + kQ_22 * kQ_22);
		kQ_02 *= fInvLength;
		kQ_12 *= fInvLength;
		kQ_22 *= fInvLength;

		// guarantee that orthogonal matrix has determinant 1 (no reflections)
		double fDet = kQ_00 * kQ_11 * kQ_22 + kQ_01 * kQ_12 * kQ_20 + kQ_02 * kQ_10 * kQ_21 - kQ_02 * kQ_11 * kQ_20 - kQ_01 * kQ_10 * kQ_22 - kQ_00 * kQ_12 * kQ_21;

		if (fDet < 0.0)
		{
			kQ_00 = -kQ_00;
			kQ_01 = -kQ_01;
			kQ_02 = -kQ_02;
			kQ_10 = -kQ_10;
			kQ_11 = -kQ_11;
			kQ_12 = -kQ_12;
			kQ_20 = -kQ_20;
			kQ_21 = -kQ_21;
			kQ_22 = -kQ_22;
		}

		// build "right" matrix R
		double kR_00 = kQ_00 * m00 + kQ_10 * m10 + kQ_20 * m20;
		double kR_01 = kQ_00 * m01 + kQ_10 * m11 + kQ_20 * m21;
		double kR_11 = kQ_01 * m01 + kQ_11 * m11 + kQ_21 * m21;
		double kR_02 = kQ_00 * m02 + kQ_10 * m12 + kQ_20 * m22;
		double kR_12 = kQ_01 * m02 + kQ_11 * m12 + kQ_21 * m22;
		double kR_22 = kQ_02 * m02 + kQ_12 * m12 + kQ_22 * m22;

		// the scaling component
		double kD_0 = kR_00;
		double kD_1 = kR_11;
		double kD_2 = kR_22;

		// the shear component
		double fInvD0 = 1.0 / kD_0;
		double kU_0 = kR_01 * fInvD0;
		double kU_1 = kR_02 * fInvD0;
		double kU_2 = kR_12 / kD_1;



		resultPosOrientScaleMatrix[8] = kD_0;
		resultPosOrientScaleMatrix[9] = kD_1;
		resultPosOrientScaleMatrix[10] = kD_2;
		resultPosOrientScaleMatrix[11] = 1.0;




		//orientation = Quaternion(matQ);		//this->FromRotationMatrix(rot);
		// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
		// article "Quaternion Calculus and Fast Animation".

		double fTrace = kQ_00 + kQ_11 + kQ_22;
		double fRoot;

		if (fTrace > 0.0)
		{
			// |w| > 1/2, may as well choose w > 1/2
			fRoot = sqrt(fTrace + 1.0f);  // 2w
			resultPosOrientScaleMatrix[7] = 0.5f*fRoot;					//w
			fRoot = 0.5f / fRoot;  // 1/(4w)
			resultPosOrientScaleMatrix[4] = (kQ_21 - kQ_12)*fRoot;
			resultPosOrientScaleMatrix[5] = (kQ_02 - kQ_20)*fRoot;
			resultPosOrientScaleMatrix[6] = (kQ_10 - kQ_01)*fRoot;
		}
		else
		{
			/*
			// |w| <= 1/2
			static size_t s_iNext[3] = { 1, 2, 0 };
			size_t i = 0;
			if (kQ_11 > kQ_00)
			i = 1;
			if (kQ_22 > kQ_[i][i])
			i = 2;
			size_t j = s_iNext[i];
			size_t k = s_iNext[j];

			fRoot = 1.0 / sqrt(kQ_[i][i] - kQ_[j][j] - kQ_[k][k] + 1.0f);
			double* apkQuat[3] = { &x, &y, &z };
			*apkQuat[i] = 0.5f*fRoot;
			fRoot = 0.5f / fRoot;
			resultPosOrientScaleMatrix[4] = (kQ_[k][j] - kQ_[j][k])*fRoot;		//w
			*apkQuat[j] = (kQ_[j][i] + kQ_[i][j])*fRoot;
			*apkQuat[k] = (kQ_[k][i] + kQ_[i][k])*fRoot;
			*/

			// |w| <= 1/2
			static size_t s_iNext[3] = { 1, 2, 0 };

			if (kQ_11 > kQ_00)
			{
				if (kQ_22 > kQ_11)
				{
					//i = 2;
					//size_t j = 0;
					//size_t k = 1;

					fRoot = sqrt(kQ_22 - kQ_00 - kQ_11 + 1.0);

					resultPosOrientScaleMatrix[6] = 0.5f*fRoot;					//z
					fRoot = 0.5f / fRoot;
					resultPosOrientScaleMatrix[7] = (kQ_10 - kQ_01)*fRoot;		//w
					resultPosOrientScaleMatrix[4] = (kQ_02 + kQ_20)*fRoot;		//x
					resultPosOrientScaleMatrix[5] = (kQ_12 + kQ_21)*fRoot;		//y
				}
				else {
					//i = 1
					//size_t j = 2;
					//size_t k = 0;

					fRoot = sqrt(kQ_11 - kQ_22 - kQ_00 + 1.0);
					resultPosOrientScaleMatrix[5] = 0.5f*fRoot;							//y
					fRoot = 0.5f / fRoot;
					resultPosOrientScaleMatrix[7] = (kQ_02 - kQ_20)*fRoot;		//w
					resultPosOrientScaleMatrix[6] = (kQ_21 + kQ_12)*fRoot;		//z
					resultPosOrientScaleMatrix[4] = (kQ_01 + kQ_10)*fRoot;		//x

				}
			}
			else {

				if (kQ_22 > kQ_00)
				{
					//i = 2;
					//size_t j = 0;
					//size_t k = 1;

					fRoot = sqrt(kQ_22 - kQ_00 - kQ_11 + 1.0);

					resultPosOrientScaleMatrix[6] = 0.5f*fRoot;					//z
					fRoot = 0.5f / fRoot;
					resultPosOrientScaleMatrix[7] = (kQ_10 - kQ_01)*fRoot;		//w
					resultPosOrientScaleMatrix[4] = (kQ_02 + kQ_20)*fRoot;		//x
					resultPosOrientScaleMatrix[5] = (kQ_12 + kQ_21)*fRoot;		//y
				}
				else {
					//i = 0
					//size_t j = 1;
					//size_t k = 2;

					fRoot = sqrt(kQ_00 - kQ_11 - kQ_22 + 1.0f);

					resultPosOrientScaleMatrix[4] = 0.5f*fRoot;					//x
					fRoot = 0.5f / fRoot;
					resultPosOrientScaleMatrix[7] = (kQ_21 - kQ_12)*fRoot;		//w
					resultPosOrientScaleMatrix[5] = (kQ_10 + kQ_01)*fRoot;	//y
					resultPosOrientScaleMatrix[6] = (kQ_20 + kQ_02)*fRoot;	//z
				}

			}
		}

	}

	const Vector2 Vector2::zero(0, 0);
	const Vector3 Vector3::zero(0,0,0);
	const Vector3 Vector3::unit(1, 1, 1);
	const Vector3 Vector3::unit_X(1, 0,0);
	const Vector3 Vector3::unit_Y(0, 1, 0);
	const Vector3 Vector3::unit_Z(0, 0, 1);
	const Vector3 Vector3::unit_nX(-1, 0, 0);
	const Vector3 Vector3::unit_nY(0, -1, 0);
	const Vector3 Vector3::unit_nZ(0, 0, -1);
	const Quaternion Quaternion::iddentity(0, 0, 0, 1);
	
	/*-------------------------------------------------------------------------------\
	|                             crossProduct			                             |
	\-------------------------------------------------------------------------------*/
	Vector3 crossProduct(const Vector3& vec, const Vector3& rkVector)
	{
		return Vector3(
			vec.y * rkVector.z - vec.z * rkVector.y,
			vec.z * rkVector.x - vec.x * rkVector.z,
			vec.x * rkVector.y - vec.y * rkVector.x);
	}
	/*-------------------------------------------------------------------------------\
	|                quatMulVec3									                 |
	\-------------------------------------------------------------------------------*/
	Vector3 Quaternion::quatMulVec3(Vector3 v)						//from Ogre Vector3 Quaternion::operator* (const Vector3& v) const
	{
		// nVidia SDK implementation
		Vector3 uv, uuv;
		Vector3 qvec(x, y, z);
		uv = crossProduct(qvec, v);
		uuv = crossProduct(qvec, uv);
		uv.x = uv.x * (2.0 * w);
		uv.y = uv.y * (2.0 * w);
		uv.z = uv.z * (2.0 * w);
		uuv.x = uuv.x * 2.0;
		uuv.y = uuv.y * 2.0;
		uuv.z = uuv.z * 2.0;

		return Vector3(v.x + uv.x + uuv.x, v.y + uv.y + uuv.y, v.z + uv.z + uuv.z);
	}

	/*-------------------------------------------------------------------------------\
	|                quatMulQuat									                 |
	\-------------------------------------------------------------------------------*/
	Quaternion quatMulQuat(const Quaternion &quat, const Quaternion &rkQ)		//from Ogre Quaternion Quaternion::operator* (const Quaternion& rkQ) const
	{
		// NOTE:  Multiplication is not generally commutative, so in most cases p*q != q*p.

		return Quaternion
		(
			quat.w * rkQ.x + quat.x * rkQ.w + quat.y * rkQ.z - quat.z * rkQ.y,
			quat.w * rkQ.y + quat.y * rkQ.w + quat.z * rkQ.x - quat.x * rkQ.z,
			quat.w * rkQ.z + quat.z * rkQ.w + quat.x * rkQ.y - quat.y * rkQ.x,
			quat.w * rkQ.w - quat.x * rkQ.x - quat.y * rkQ.y - quat.z * rkQ.z
		);
	}
	//-----------------------------------------------------------------------
	Quaternion Slerp(double factor, Quaternion rkP, Quaternion rkQ, bool shortestPath)	//from Ogre Quaternion
	{	
		rkP.normalise();					// Only unit quaternions are valid rotations. Normalize to avoid undefined behavior.
		rkQ.normalise();
		
		double fCos = rkP.Dot(rkQ);			// Compute the cosine of the angle between the two vectors.
		Quaternion rkT;

		// Do we need to invert rotation?
		if (fCos < 0.0f && shortestPath)	// If the dot product is negative, the quaternions  have opposite handed-ness and slerp won't take  the shorter path. Fix by reversing one quaternion.
		{
			fCos = -fCos;
			rkT = -rkQ;
		}else{
			rkT = rkQ;
		}

		if (abs(fCos) < 1 - 0.00000001)
		{
			if (fCos > 1)	// Robustness: Stay within domain of acos()
				fCos = 1;
			if (fCos < -1)
				fCos = -1;
			
			// Standard case (slerp)
			double fSin = sqrt(1 - fCos * fCos);
			double fAngle_rad = atan2(fSin, fCos);
			double fInvSin = 1.0f / fSin;
			double fCoeff0 = sin((1.0f - factor) * fAngle_rad) * fInvSin;
			double fCoeff1 = sin(factor * fAngle_rad) * fInvSin;
			return rkP * fCoeff0 + rkT * fCoeff1;

		}else{
			// There are two situations:
			// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
			//    interpolation safely.
			// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
			//    are an infinite number of possibilities interpolation. but we haven't
			//    have method to fix this case, so just use linear interpolation here.
			Quaternion t = rkP * (1.0f - factor) + rkT * factor;
			// taking the complement requires renormalisation
			t.normalise();
			return t;
		}
	}
	/*-------------------------------------------------------------------------------\
	|                fromAngleAxis									                 |
	\-------------------------------------------------------------------------------*/
	Quaternion fromAngleAxis(const double& rfAngle, const Vector3& rkAxis)			//from Ogre Quaternion::FromAngleAxis
	{
		// assert:  axis[] is unit length
		//
		// The quaternion representing the rotation is
		//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

		double fHalfAngle(0.5*rfAngle);
		double fSin = sin(fHalfAngle *  3.14159265359 /180.0);
		return Quaternion(fSin*rkAxis.x, fSin*rkAxis.y, fSin*rkAxis.z, cos(fHalfAngle *  3.14159265359 / 180.0));			//X,y,z,w
	}


	/*-------------------------------------------------------------------------------\
	|                giveAngleOrientationForThisOrientationTaitBryan                 |
	\-------------------------------------------------------------------------------*
	// to TaitBryan : EulerAngle XZY in Yup.
	Vector3 giveAngleOrientationForThisOrientationTaitBryan(Quaternion orient)
	{
		Vector3 q(0, 0, 0);

		Vector3 dir = orient.quatMulVec3(Vector3(1, 0, 0));

		//1) calcul yaw
		Vector2 vectproj(dir.x, -dir.z);		//projection of the result on (O,x,-z) plane
		if (vectproj.Length() > 0.000001)			//if undefined => by defaut 0;
		{
			vectproj.Normalize();

			q.x = acos(vectproj.x) * 180.0 / 3.14159265359;
			if (vectproj.y < 0)
				q.x = -q.x;
		}

		//2) calcul pitch
		Quaternion rotationInv_Yrot = fromAngleAxis(-q.x, Vector3(0, 1, 0));

		Vector3 dir_tmp = quatMulQuat(rotationInv_Yrot, orient).quatMulVec3(Vector3(1, 0, 0));		//we cancel yaw rotation, the point must be into (O,x,y) plane
		q.y = acos(dir_tmp.x) * 180.0 / 3.14159265359;
		if (dir_tmp.y < 0)
			q.y = -q.y;


		//3) calcul roll
		Quaternion rotationInv_Zrot = fromAngleAxis(-q.y, Vector3(0, 0, 1));
		dir_tmp = quatMulQuat(rotationInv_Zrot, quatMulQuat(rotationInv_Yrot, orient)).quatMulVec3(Vector3(0, 0, 1));		//we cancel the yaw and pitch rotations, the point Vector3::UNIT_Y, after rotation, must be into (O,x,z) plane.
		q.z = acos(dir_tmp.z) * 180.0 / 3.14159265359;
		if (dir_tmp.y > 0)		// the direct direction is from Oy to Oz
			q.z = -q.z;

		return q;
	}


	/*-------------------------------------------------------------------------------\
	|                giveAngleOrientationForThisOrientationTaitBryan                 |
	\-------------------------------------------------------------------------------*/
	// to TaitBryan : EulerAngle XZY, but Zup 
	//( Xfront, Yup ZRight => Xright Yfront Zup )
	// X => Y
	// Y => Z
	// Z => X
	Vector3 giveAngleOrientationForThisOrientationTaitBryan(Quaternion orient)
	{
		Vector3 q(0, 0, 0);

		Vector3 dir = orient.quatMulVec3(Vector3(0, 1, 0));

		//1) calcul yaw
		Vector2 vectproj(dir.y, -dir.x);		//projection of the result on (O,y,-x) plane
		if (vectproj.Length() > 0.000001)			//if undefined => by defaut 0;
		{
			vectproj.Normalize();

			q.x = acos(vectproj.x) * 180.0 / 3.14159265359;
			if (vectproj.y < 0)
				q.x = -q.x;
		}

		//2) calcul pitch
		Quaternion rotationInv_Yrot = fromAngleAxis(-q.x, Vector3(0, 0, 1));

		Vector3 dir_tmp = quatMulQuat(rotationInv_Yrot, orient).quatMulVec3(Vector3(0, 1, 0));		//we cancel yaw rotation, the point must be into (O,y,z) plane
		q.y = acos(dir_tmp.y) * 180.0 / 3.14159265359;
		if (dir_tmp.z < 0)
		q.y = -q.y;


		//3) calcul roll
		Quaternion rotationInv_Zrot = fromAngleAxis(-q.z, Vector3(1, 0, 0));
		dir_tmp = quatMulQuat(rotationInv_Zrot, quatMulQuat(rotationInv_Yrot, orient)).quatMulVec3(Vector3(1, 0, 0));		//we cancel the yaw and pitch rotations, the point Vector3::UNIT_Z, after rotation, must be into (O,y,x) plane.
		q.z = acos(dir_tmp.x) * 180.0 / 3.14159265359;
		if (dir_tmp.z > 0)		// the direct direction is from Oy to Oz
		q.z = -q.z;

		return q;
	}


	/*-------------------------------------------------------------------------------\
	|                keepTaitBryanGood								                 |
	\-------------------------------------------------------------------------------*/
	void keepTaitBryanAnglesGood(Vector3 previousAngles, Vector3 &currentAngles)
	{
		//return;				//test to remove.
		
		
		//here we will try to take care of 360 -> 0 degrees, short path etc. to have better interpolation between keyframes, by adapt the currenAngles.
				
		//first, deal with Yaw.
		double yaw_prev = previousAngles.x + 180.0;			// base range : [-180.0, 180.0] => [0, 360]
		double yaw = currentAngles.x + 180.0;

		double nbLaps_prev = floor(yaw_prev / 360.0);
		double nbLaps = floor(yaw / 360.0);
		currentAngles.x += (nbLaps_prev - nbLaps) * 360.0;	//get the same number of Laps as previous

		yaw_prev = yaw_prev - nbLaps_prev * 360.0;
		yaw = yaw - nbLaps * 360.0;

		double diff = yaw - yaw_prev;
		if (diff - 180.0 > 0.00000001)						//get shortpath
			currentAngles.x -= 360.0;
		if (diff + 180.0 < -0.00000001)                         //if(diff < -180.0)
			currentAngles.x += 360.0;


		//same for Roll
		double roll_prev = previousAngles.z + 180.0;			// base range : [-180.0, 180.0] => [0, 360]
		double roll = currentAngles.z + 180.0;

		nbLaps_prev = floor(roll_prev / 360.0);
		nbLaps = floor(roll / 360.0);
		currentAngles.z += (nbLaps_prev - nbLaps) * 360.0;	//get the same number of Laps as previous

		roll_prev = roll_prev - nbLaps_prev * 360.0;
		roll = roll - nbLaps * 360.0;

		diff = roll - roll_prev;
		if (diff - 180.0 > 0.00000001)						//get shortpath
			currentAngles.z -= 360.0;
		if (diff + 180.0 < -0.00000001)                         //if(diff < -180.0)
			currentAngles.z += 360.0;
	}
	





	/*-------------------------------------------------------------------------------\
	|                giveAngleOrientationForThisOrientationTaitBryan_XYZ             |
	\-------------------------------------------------------------------------------*/
	// to TaitBryan : EulerAngle XZY, but Zup 
	//(  Yup ZRight Xfront, => Zup Yright Xfront   )
	// X => X
	// Y => Z
	// Z => Y
	Vector3 giveAngleOrientationForThisOrientationTaitBryan_XYZ(Quaternion orient)				//same version, but with this order of rotation, the yaw is on the diqs display by pitch rotation.
	{
		//convert into a matrix3x3
		Vector3 m0, m1, m2;
		quadToRotationMatrix(orient, m0, m1, m2);

		//convert matrix3x3 into EulerAngle
		Vector3 q(0, 0, 0);
		matrixToEulerAnglesZYX(m0, m1, m2, q);

		return q;
	}



	/*-------------------------------------------------------------------------------\
	|                quadToRotationMatrix											 |
	\-------------------------------------------------------------------------------*/
	void quadToRotationMatrix(Quaternion orient, Vector3 &m0, Vector3 &m1, Vector3 &m2)
	{
		//normalize quaternion as in https://www.andre-gaschler.com/rotationconverter/ , else we could have infinite + weird result on matrixToEulerAnglesZYX, because of float precision on quaternion.
		double a = sqrt(orient.x * orient.x + orient.y * orient.y + orient.z * orient.z + orient.w * orient.w);
		if (0 == a)
		{
			orient.x = orient.y = orient.z = 0;
			orient.w = 1;
		}else {
			a = 1.0 / a;
			orient.x *= a;
			orient.y *= a;
			orient.z *= a;
			orient.w *= a;
		}



		double fTx = orient.x + orient.x;
		double fTy = orient.y + orient.y;
		double fTz = orient.z + orient.z;
		double fTwx = fTx * orient.w;
		double fTwy = fTy * orient.w;
		double fTwz = fTz * orient.w;
		double fTxx = fTx * orient.x;
		double fTxy = fTy * orient.x;
		double fTxz = fTz * orient.x;
		double fTyy = fTy * orient.y;
		double fTyz = fTz * orient.y;
		double fTzz = fTz * orient.z;

		m0.x = 1.0 - (fTyy + fTzz);
		m0.y = fTxy - fTwz;
		m0.z = fTxz + fTwy;
		m1.x = fTxy + fTwz;
		m1.y = 1.0 - (fTxx + fTzz);
		m1.z = fTyz - fTwx;
		m2.x = fTxz - fTwy;
		m2.y = fTyz + fTwx;
		m2.z = 1.0 - (fTxx + fTyy);
	}

	/*-------------------------------------------------------------------------------\
	|                clamp															 |
	\-------------------------------------------------------------------------------*/
	void clampNear(double value, double min, double max, double eps)
	{
		if ((value < min) && (abs(value - min) < eps))
			value = min;
		if ((value > max) && (abs(value - max) < eps))
			value = max;
	}
	/*-------------------------------------------------------------------------------\
	|                clampNear														 |
	\-------------------------------------------------------------------------------*/
	void clampNear(Vector3 value, Vector3 min, Vector3 max, double eps)
	{
		clampNear(value.x);
		clampNear(value.y);
		clampNear(value.z);
	}


	/*-------------------------------------------------------------------------------\
	|                matrixToEulerAnglesZYX											 |
	\-------------------------------------------------------------------------------*/
	bool matrixToEulerAnglesZYX(Vector3 m0, Vector3 m1, Vector3 m2, Vector3 &YPR_angles)
	{
		// rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
		//        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
		//       -sy              cy*sx           cx*cy

		clampNear(m0);		//few corrections, due to the float precision on quaternion.
		clampNear(m1);
		clampNear(m2);


		YPR_angles.y = asin(-m2.x) * 180.0 / 3.14159265359;
		if (YPR_angles.y < 90.0)
		{
			if (YPR_angles.y > -90.0)
			{
				YPR_angles.x = atan2(m1.x, m0.x) * 180.0 / 3.14159265359;
				YPR_angles.z = atan2(m2.y, m2.z) * 180.0 / 3.14159265359;
				return true;
			}
			else {
				// WARNING.  Not a unique solution.
				double fRmY = atan2(-m0.y, m0.z) * 180.0 / 3.14159265359;
				YPR_angles.z = 0.0;  // any angle works
				//YPR_angles.x = YPR_angles.z - fRmY;
				YPR_angles.x = fRmY - YPR_angles.z;
				return false;
			}

		}else {
			// WARNING.  Not a unique solution.
			double fRpY = atan2(-m0.y, m0.z);
			YPR_angles.z = 0.0;  // any angle works
			YPR_angles.x = fRpY - YPR_angles.z;
			return false;
		}
	}


}
