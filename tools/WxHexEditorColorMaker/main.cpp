


#include "Swr_Model.h"

using namespace Common;


int main(int argc, char** argv)
{

	printf("*******************************************************************\n");
	if (argc < 2)
	{		
printf("This tool is for Color/tag some binaries with the help of WxHexEditor (creation of .tags files).\n\
 It's for help to discover/debugging structurs and take care of file format: starswars's models.\n\
 Please consider the result as Debug to share information and test if All files are All colored.\n\
 There is also warning when one bytes is taggued 2 time or on overflow, so that could help\n\
 Usage: 'WxHexEditorColorMaker.exe [options] file.ext file2.ext ...'\n\
 Options : '-NoWait', '-AlwaysWait', '-WaitOnError' (default), or '-WaitOnWarning'.\n\
*******************************************************************\n\
Press Enter to continue.\n");
		getchar();
		return 1;
	}

	
	std::vector<string> arguments = initApplication(argc, argv);

	if (arguments.size() == 0)
	{
		printf("Error not enougth arguments.\n");
		notifyError();
		waitOnEnd();
		return 1;
	}

	
	


	size_t nbArg = arguments.size();
	for (size_t i = 0; i < nbArg; i++)
	{
		string filename = arguments.at(i);
		string extension = extensionFromFilename(filename, true);
		string basefilename = filename.substr(0, filename.length() - (extension.size() + 1)) ;
		string extension2 = extensionFromFilename(basefilename, true);
		string basefilename2 = basefilename.substr(0, basefilename.length() - (extension2.size() + 1));
		string extension3 = extensionFromFilename(basefilename2, true);
		string basefilename3 = basefilename2.substr(0, basefilename2.length() - (extension3.size() + 1));
	

		/////////////////////////////////////////////////////////////
		if (extension == "bin")
		{
			if (toLowerCase(nameFromFilename(filename)).find("model") != std::string::npos)				//it's a model
			{
				printf("Start with file :%s.\nPlease Wait ...\n", filename.c_str());

				Swr_Model* model = new Swr_Model();
				model->save_Coloration(filename);
			}
		}
	}

	printf("finished.\n");
	waitOnEnd();
	return 0;
}