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

		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind;
		hFind = FindFirstFileA((folderpath + "\\*.*").c_str(), &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			while (FindNextFileA(hFind, &FindFileData) != 0)
			{
				const char *name = FindFileData.cFileName;
				if (name[0] == '.')
					continue;

				string str = ToString(name);
				if(fileCheck(folderpath + "\\" + str))
					listFilename.push_back(str);
			};
			FindClose(hFind);
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
}
