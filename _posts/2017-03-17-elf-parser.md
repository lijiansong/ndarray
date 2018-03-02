---
layout: post
title: ELF Parser
date:   2017-03-17 11:02:15 +0800
categories: Cpp
comments: true
tags:
    - platform tool
---
<div class="message">
In Unix-like system, the Executable and Linkable Format (ELF, formerly called Extensible Linking Format) is a common standard file format for executables, object code, shared libraries, and core dumps. 
</div>
  <!-- more -->

First published in the System V Release 4 (SVR4) Application Binary Interface (ABI) specification,and later in the Tool Interface Standard, it was quickly accepted among different vendors of Unix systems, such as Linux and etc.
ELF is flexible and extensible by design, and it is not bound to any particular processor or architecture. This has allowed it to be adopted by many different operating systems on many different platforms.

Each ELF file is made up of one ELF header, followed by file data. The file data can include:
- Program header table, describing zero or more segments
- Section header table, describing zero or more sections
- Data referred to by entries in the program header table or section header table

The segments contain information that is necessary for runtime execution of the file, while sections contain important data for linking and relocation. Any byte in the entire file can be owned by at most one section, and there can be orphan bytes which are not owned by any section.
More details about ELF, see [here...](https://web.archive.org/web/20130403001804/http://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/binary-formats.html)
Many tools can be taken use of to parse the ELF file, such as `readelf, elfutils, elfdump, objdump`...

Here I implement a my own elf-parser. There is nothing difficult to implement it, the whole work is mainly about `file IO & string parsing`...
You can follow the following steps to build it...

##Build
```
$ cd xxx_dir
$ make
$ ./elf-parser ./test-cases/hello/hello
$ make clean
```
To generate the assembly code, you can type the following cmds:
```
$ g++ -E hello.cpp -o hello.i
$ g++ -S hello.cpp -o hello.s
$ g++ -c hello.s -o hello.o
```

For more details about the src, see [here...](https://github.com/lijiansong/Postgraduate-Course/tree/master/tools/elf-parser)

Any questions or suggestions, feel free to open an issue @[here](https://github.com/lijiansong/Postgraduate-Course/issues) or e-mail me to *lijiansong@ict.ac.cn*.