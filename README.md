


### Sw_Racer
*Tools to understand file format of the 1999 Game ["Star Wars: Episode 1 Racer"](https://en.wikipedia.org/wiki/Star_Wars_Episode_I:_Racer)*


### Details

-WxHexEditorColorMaker : Create a .tags file for Model's bin file. tags files are readed by WxHexEditor when open the file with the same name.
-XmlConverter: convert the Model's bin file into Xml. (and for test, extract the 3D datas into Collada (.dae) for testing into a 3d sofware)
To use it, just drag and drop (or using command line) the model.bin files.

You will still need the original game for its art assets: levels, sounds, ...


### Goal

Try to help on the project : https://github.com/OpenSWE1R/openswe1r
And better understand the files formats.


### Requirements

**Toolchain**

* [git](https://git-scm.com/)
* [CMake](https://cmake.org/)
* C11 toolchain

### Building


This project use 
-Cmake (3.11.1)
-and as dependencies: TinyXml from vcpkg (https://github.com/Microsoft/vcpkg). 
As vcpkg have troubles with old Visual Studio, I advice to use Visual Studio 2017.


#### Install vcpk and dependencies :

From your desired insatllation folder, run:
```
git clone https://github.com/Microsoft/vcpkg
cd vcpkg
bootstrap-vcpkg.bat
```
(or on linus/macOs: bootstrap-vcpkg.sh)
```
vcpkg install tinyxml
vcpkg integrate install
```
copy the path -DCMAKE_TOOLCHAIN_FILE=XXXX for CMake.
Informations about using vcpk : https://docs.microsoft.com/en-us/cpp/vcpkg


#### pull project from Git:

From your desired project folder, run:

```
git clone https://github.com/Olganix/Sw_Racer.git
cd Sw_Racer
```

#### Cmake :

-on Cmake-Gui / windows / visual studio 2017:
	-create a folder "build". 
	-put the path of the project inside "source", and the path of "build" for "build the binaries".
	-click on configuration, Select "Visual Studio 15 2017" AND "Specify toolchain file for corss-compiling".
	-you should paste the path gived by "vcpkg integrate install". and "Finish"
	-click on configure, a second time. Now on generate.
	normally it's detect automatically the dependecies.
	-open .sln, and compile.
	
-on Cmake command line:
```
mkdir build
cd build
cmake ..
make
```
(and on windows : 
```
cmake -G "Visual Studio 15 2017" -DCMAKE_TOOLCHAIN_FILE=C:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```
or for x64:
```
cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_TOOLCHAIN_FILE=C:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake ..
```
)


### Running

Drag and drop the model's bin file into a tool.

### Development

Development happens on GitHub at https://github.com/Olganix/Sw_Racer

## Requirements

* CMake
* C++ toolchain
* vcpkg
* TinyXML
