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

## The Gambit Language
Gambit is a chess opening in which a player risks one or more pawns or a minor piece to gain an advantage in position.

The Gambit language we're going to be building is going to be a statically typed, object-based language. I say object-based because in order to create a fully object-oriented language with all the required features -- it will require quite some time. We will implement inheritance and the ability to do composition. Primitive datatypes, such as integers, will also be objects.

Mutability will also be a core feature. By default, all variables and object properties will be mutable.

### A Few Data Types
The easiest way to start working on our language is to define which data-types will be supported. Gambit supports the following data types:

- Integers : 1,2,-10, Integer.new(10)
- Decimals : 1.2, -2.55555, Decimal.new(10.789)
- Float    : 5.2f, -8.3333f, Float.new(3.2f)
- String   : "this is a string", String.new("String")

More complex data types:

- Array    : Constant::identifier[Integer],            String::my_array[10]
- Hash     : Constant::identifier[Constant,Constant],  Hash::my_hash[String,10]

### Variable Declaration
Variables can be defined by the following syntax:

```
Constant::identifier
Constant::identifier = Expression

String::my_string
String::your_string = "hello world!"

my_string = String.new("Indeed, Hello World!")
```

Array and hash syntax is slightly different as these are complex datatypes

```
Constant::identifier[size]

String::my_string[10]
my_string = ["one", "two", "three"]

Constant::identifier[Constant, Constant]
Hash::my_hash[String, Integer]
my_hash = { "age" => 55, "year" => 2017 }

```

This will give us plenty to work with when we start creating our parser and generating the AST

## Copyrights
Benjamin J. Anderson - 2017
