cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(TinyXML REQUIRED)

include_directories(SYSTEM depends/half)
include_directories(SYSTEM depends/dirent)
include_directories(SYSTEM include)

include_directories(SYSTEM ${TinyXML_INCLUDE_DIRS})
link_libraries(${TinyXML_LIBRARIES})


add_executable(Swr_Pack tools/Pack/main.cpp depends/half/half.cpp src/common.cpp src/EMO_BaseFile.cpp src/Swr_Model.cpp include/Swr_Model.h src/Collada.cpp include/Collada.h)

add_executable(Swr_XmlConverter tools/XmlConverter/main.cpp depends/half/half.cpp src/common.cpp src/EMO_BaseFile.cpp src/Swr_Model.cpp include/Swr_Model.h src/Collada.cpp include/Collada.h)

add_executable(Swr_WxHexEditorColorMaker tools/WxHexEditorColorMaker/main.cpp depends/half/half.cpp src/common.cpp src/EMO_BaseFile.cpp src/Swr_Model.cpp include/Swr_Model.h src/Collada.cpp include/Collada.h)
