


### Sw_Racer

*Tools to understand file format of the 1999 Game ["Star Wars: Episode 1 Racer"](https://en.wikipedia.org/wiki/Star_Wars_Episode_I:_Racer)*

![Screenshot of Model 001, Boota's Classic, extracted in collada, view in Blender ](https://i.imgur.com/YZKW7L2.jpg)

### Goal

Try to help on the project : https://github.com/OpenSWE1R/openswe1r
And better understand the files formats. Could extract to have data in a 3d sofware, and may be could rebuild the data after modifications.


### Building

#### Requirements

* [git](https://git-scm.com/)
* [CMake](https://cmake.org/) up to 3.1
* C11 toolchain
* TinyXML by vcpkg (https://github.com/Microsoft/vcpkg) for Windows case. 
In case of using visual studio, as vcpkg have troubles with old Visual Studio, I advice to use Visual Studio 2017.

You will still need the original game for its art assets: levels, sounds, ...


##### Install vcpk and dependencies :

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


##### pull project from Git:

From your desired project folder, run:

```
git clone https://github.com/Olganix/Sw_Racer.git
cd Sw_Racer
```

##### Cmake :

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


#### Running

Drag and drop the model's bin file into a tool. Or use command line.

-WxHexEditorColorMaker : Create a .tags file for Model's bin file. tags files are readed by WxHexEditor when open the file with the same name.
-XmlConverter: convert the Model's bin file into Xml. (and for test, also extract the 3D datas into Collada (.dae) for testing into a 3d sofware)


 


### Development

Development happens on GitHub at https://github.com/Olganix/Sw_Racer
You can help by reviewing other peoples Pull-Requests or sending your own after forking.

If you want to contribute, you'll have to [sign our Contributor License Agreement (CLA)](https://cla-assistant.io/OpenSWE1R/openswe1r).
The CLA allows us to easily switch to other [licenses the FSF classifies as Free Software License](https://www.gnu.org/licenses/license-list.html) and which are [approved by the OSI as Open Source licenses](https://opensource.org/licenses), if the need should ever arise ([more information](https://github.com/OpenSWE1R/openswe1r/pull/95)).

---

**© 2017 Swr_Racer Maintainers**

Source code licensed under GPLv2 or any later version.
Binaries which link against the default Unicorn-Engine backend must be licensed under GPLv2.

Swr_Racer is not affiliated with, endorsed by, or sponsored by The Walt Disney Company, Twenty-First Century Fox, the games original developers, publishers or any of their affiliates or subsidiaries.
All product and company names are trademarks™ or registered® trademarks of their respective holders. Use of them does not imply any affiliation with or endorsement by them.

Reverse engineering of the original software is done to achieve interoperability with other computing platforms.
In the process, excerpts of the reverse engineered source code might be shown for educational purposes.

No copyright infringement is intended at any stage during development of Swr_Racer.
