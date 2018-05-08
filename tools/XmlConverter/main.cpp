


#include "Swr_Model.h"

using namespace Common;




int main(int argc, char** argv)
{

	printf("*******************************************************************\n");
	if (argc < 2)
	{
printf("This tool is for convert some files of StarwarsRacer into a Xml version,\n\
 Usage: 'XmlConverter.exe [options] file.ext file2.ext ...' or 'XmlConverter.exe [options] folder' \n\
 Files formats supported : bin for model.\n\
 Notice, for model, for tests, we export a extracted collada file (same for collision mesh).\n\
 Also, because size of datas and tinyXml, if there is more than one model, that will split model into a folder before convert into Xml.\n\
 Also, if the case of a file, it will create a Xml with the list of Texture (Section5), for help the TextureExtractor (JayFoxRox python script).\n\
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
			model->save_Xml(filename, true);
			delete model;

		}else if (extension == ""){												//folder

			std::vector<string> listFilename = getFilesInFolder(filename);
			size_t nbFiles = listFilename.size();
			for (size_t j = 0; j < nbFiles; j++)
			{
				string filenameb = listFilename.at(j);
				string extensionb = extensionFromFilename(filenameb, true);
				string basefilenameb = filenameb.substr(0, filenameb.length() - (extensionb.size() + 1));
				string nameb = Common::nameFromFilename(basefilenameb);

				if (extensionb == "bin")
				{
					if (toLowerCase(nameb).find("model") != std::string::npos)				//it's a model
					{
						Swr_Model* model = new Swr_Model();
						model->save_Xml(filename +"/"+ filenameb, false);
						delete model;
					}
				}
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
