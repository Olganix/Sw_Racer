


#include "Swr_Model.h"

using namespace Common;




int main(int argc, char** argv)
{

	printf("*******************************************************************\n");
	if (argc < 2)
	{
printf("This tool is for convert some files of StarwarsRacer into a Xml version,\n\
 Usage: 'XmlConverter.exe [options] file.ext file2.ext ...'\n\
 Files formats supported : bin for model.\n\
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

		printf("Process on %s. Please Wait...\n", filename.c_str());

		if (extension == "bin")
		{
			Swr_Model* model = new Swr_Model();
			model->save_Xml(filename);
			delete model;

		}else {
			printf("Error on arguments.\n");
			notifyError();
		}
	}

	printf("finished.\n");
	waitOnEnd();
	return 0;
}