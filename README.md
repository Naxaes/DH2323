# DH2323 Project template
This is a project template for the course DH2323 Computer Graphics and Interaction. It's for the first lab, and for lab 2 and 3 in the *Rendering* track.

## Setup

Great IDE's are [Visual Studio](https://visualstudio.microsoft.com/downloads/) for Windows or [CLion](https://www.jetbrains.com/clion/download/) for Mac. They both use [CMake](https://cmake.org/) as build system.

Once you got either and have downloaded this template, opening the project with the IDE should be enough for it to detect it's a CMake project. If not, right-click on the `CMakeLists` file and select *"Generate cache for ..."* or *"Reload Cmake Project"*.

When the cache is generated, you should be able to see and select the labs/tests in "Select Startup Item" in Visual Studio or "Edit Configurations" in CLion. The following targets already exists and should work right out of the box:

* Lab1
* Lab2
* Lab3
* other
* test1

## Tips and tricks

### CLion professional is free
Clion has a free community edition but also a professional version that's [free for students](https://www.jetbrains.com/community/education/#students), if you sign up with your KTH account.


### Build in release mode
Debug mode is the default, and it's slow but allows attaching a debugger. For some labs you want to be able to move the camera around so you don't want each frame to take several seconds. In these cases, build in release. 

* CLion: https://www.jetbrains.com/help/clion/cmake-profile.html
* Visual Studio: https://docs.microsoft.com/en-us/cpp/build/customize-cmake-settings?view=msvc-160


### Add tests
I've included a simple test header file. In the folder `tests/` you can see some examples of how it's used.

To add a test, create a cpp file in the folder `tests/` as the examples show. Then go to the bottom of the `CMakeLists` file and add the name of the cpp file (without the cpp extension) to the variable `TESTS`. Doing so should create a new runnable target with the name of the file. 


### You don't need to store libraries in the repository
I ultimately decided to have the libraries SDL2 and GLM in the repository, but this isn't needed. Using git, you can add them using [submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules), i.e. with `git submodule add <url-to-repository>`.

Or, if you don't want to use git, you can do it manually. In the folder `scripts` are the scripts `download_libraries` what you would've run in order to download the libraries.

#### Macos
    chmod +x download_libraries.sh
    ./download_libraries.sh

#### Windows
    ./download_libraries.bat
