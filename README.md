# WLang
__This is a programing language i made for fun__  
__This programming language is currently undocumented__  
__For an example check test.wlang__

# Usage
## Building
>[!IMPORTANT]
> Edits to lang/Makefile and Makefile may be needed  
> These edits are  
> [lang/Makefile](/lang/Makefile)  
>&emsp;&ensp;Change in LDFLAGS "-L/opt/will/lib" - To "-L\<libpath\>" with \<libpath\>  
>&emsp;&ensp;Being wherever libfl (Flex Library) is located  
> [Makefile](/Makefile)  
>&emsp;&ensp;Change DESTDIR to the directory you would like to install to (absolute path)   
   
To build `flex` `bison` and a C Compiler are needed  
As well as a POSIX Comptible OS (Most OSes other than Windows)  
To do building + installing run this   
```sh
make # Builds
sudo make install # Installs
```  

## Command usage  
Usage: wlang \[Input.wlang\] \[Output\] \[Options\]  
Normal behavior: Generate IR, Transpile to C, Compile  
Options:  
&emsp;&emsp;-h, --help&emsp;&emsp;&emsp;Show this help message  
&emsp;&emsp;-c&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&ensp;Only IR Generation and Transpiling to C  
&emsp;&emsp;-i&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Only IR Generation  
&emsp;&emsp;-v, --version&emsp;&emsp;Show program info  

# License
WLang - A Simple Programming Languge
Copyright (C) 2025  Wdboyes13

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.