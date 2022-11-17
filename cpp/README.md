# C/C++ samples

This CMake project provides the following C/C++ samples: 
* **id3An2KSampleCLI**

## Build requirements

* CMake >= 2.8.12
* [Linux] gcc
* [Windows] Visual Studio >= 15

## Before to build

There are some source code modifications to make before to build.

### License path

To run the sample you will need a license file. To retrieve this file you can use the CLI tool to get your hardware ID and then use either the windows activation tool to retrieve the file or contact id3 with it.

id3 An2K SDK needs to check this license before any other operation. You need to fill in the path to your license in the source files:

    std::string license_path = "your_license_path_here";

## Linux build steps

### id3An2KSampleCLI

To build and run **id3An2KSampleCLI**, use the following command lines:

```bash
mkdir build
cd build
cmake -DLINUX_BUILD=ON ..
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../../bin/linux/x64
./id3An2KSampleCLI
```

## Windows build steps

### id3An2KSampleCLI

To build **id3An2KSampleCLI**, use the following command lines:
```bat
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" -DWINDOWS_BUILD=ON ..
cmake --build .
```