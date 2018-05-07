


#include "Swr_Model.h"

using namespace Common;




int main(int argc, char** argv)
{

	printf("*******************************************************************\n");
	if (argc < 2)
	{
printf("This tool is for extract/repack some files of StarwarsRacer,\n\
 Usage: 'Pack.exe [options] file.bin ...'\n\
 Files formats supported : bin for model ('model' must be inside the filename).\n\
 Notice: a listFiles.xml will be generated. it's to keep the same order for repack.\n\
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
		string name = Common::nameFromFilename(basefilename);

		printf("Process on %s. Please Wait...\n", filename.c_str());

		if (extension == "bin")											//it's a file to unpack
		{
			if (name.find("model") != std::string::npos)				//it's a model
			{
				Swr_Model* model = new Swr_Model();
				model->splitModelFile(filename, true);
				delete model;
			}

			//todo texture.

		}else if (extension == "") {									//it's a folder to pack
			
			if (name.find("model") != std::string::npos)				//it's a model
			{
				Swr_Model* model = new Swr_Model();
				model->unsplitModelFile(filename, true);
				delete model;
			}
		}else {
			printf("Error on arguments.\n");
			notifyError();
		}
	}

	printf("finished.\n");
	waitOnEnd();
	return 0;
}