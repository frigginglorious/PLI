# Programming Language Implementations
Language Specifications and Code Structure

## Clean Up
In this section we're going to start laying out our project structure and specifying a few language constructs for our virtual machine.

The first step is to delete all files and directories excluding the following:
```
.git/
.gitignore
Makefile
README.md
util/
```

This gives us a clean slate with the current requirements we need for our project (stored in the util directory).

## Our Project Directory Structure
We're going to create the following directories.

### bin
The bin directory will contain our executables and/or any resources. Resources generally include configuration files, data files, etc.

### inc
The inc directory (also can be named include), will contain our public header files. We can also move 3rd-party headers, such as FlexLexer.h, here.

### lib
Any libs that get compiled by the project, third party or any needed in development. We would move the Flex library here prior to installing it on the filesystem. We'll be utilizing this directory extensively for our virtual machine as we'll be making shared libraries for certain aspects of our language. This allows us to create and test newer versions easily.

### obj
All generated object code gets stored here when compiled with make. This is cleared by make clean.

### res
Resources. Can contain anything for our project to process, or files to configure our project.

### src
Our applications source files.

### test
Our top-level test directory will contain source files of our language that will be loaded by our test-suite. The test suite files will be contained in the src directory.

### What about util?
Ideally we would move the FlexLexer header file to our inc directory and install the shared library to our local includes on the filesystem. It entirely depends on how you'd like to configure your system, pointing our includes and shell commands to these directories is perfectly acceptable.



## Copyrights
Benjamin J. Anderson - 2017
