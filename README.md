# sc4-dll-utilities

Various utilities that are commonly used by SimCity 4 DLL Plugins.

## Usage

The source code in this repository is intended to be referenced as a git submodule from a SimCity 4 DLL project
with the source files referenced in your project, similar to what is commonly done with gzcom-dll.

It is assumed that you will already have included the gzcom-dll headers for interacting with SimCity 4.
You will also need to include the following dependencies through git submodules or your preferred C++ package manager (e.g. vcpkg):

* [Windows Implementation Library (WIL)](https://github.com/microsoft/wil)
  * This header-only library is used for Windows API error handling.

# License

This project is licensed under the terms of the GNU Lesser General Public License version 2.1 or (at your option) any later version published by the Free Software Foundation.    
See [LICENSE.txt](LICENSE.txt) for more information.

## 3rd party code

[gzcom-dll](https://github.com/nsgomez/gzcom-dll) - LGPL 2.1 or later License.   
[Windows Implementation Library](https://github.com/microsoft/wil) - MIT License    

# Source Code

## Prerequisites

* Visual Studio 2022
* `git submodule update --init`
* [VCPkg](https://github.com/microsoft/vcpkg) with the Visual Studio integration
