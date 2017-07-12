# Programming Language Implementations
Lexical Analysis with Flex

## What is Lexical Analysis / Flex?
Lexical Analysis is the process of breaking down a programming languages syntax into a series of tokens. If content supplied to a lexical analyzer, like Flex, and has no rules or patterns to match it; the lexical analyzer will fail. For example, if we wanted to express the number "1" as a token, the most common definition is an `integer`. A psuedocode rule to parse integers would look something like this:

```
# regex pattern           token to return
[0-9]+                    { return INTEGER; }
```

## Installing Flex
This repository includes Flex v2.5.37 in the `util` directory. Most Linux and MacOSX distributions already include Flex by default. Newer and older versions of Flex may not be compatible with this tutorial. 

1. In order to install the version of Flex included in this repository, navigate to the `util` directory.

2. The Flex package is compressed using a bZip2 compressor, use any standard tarball archive utility or run the following command

```bash
cd util/
tar xvjf flex-2.5.37.tar.bz2
```

The `x` flag tells the archive utility to extract the files.

`v` means "verbose", which will list all of the files one-by-one.

`j` will decompress a bzip2 file

`f` tells the archive utility that we're going to supply the file to extract.

3. Navigate to the Flex directory and run the configure command. This will ensure all dependencies are available in order to install Flex.

```bash
cd flex-2.5.37
./configure
```

Note:

You may have to resolve any dependencies that are not installed on your system. A quick google search of the error and your operating system will generally give you a good idea on how to install the missing dependency. If you are unable to resolve the issue, send an issue on Github.


4. Build Flex
In order to build Flex, and to continue through this series, we need a tool called `Make`. You can read more about it and install it [here](https://www.gnu.org/software/make/). Most Linux and MacOSX distributions already come with make installed. You can test this by running ` make -v`.

If you're using Windows, you'll have to utilize `nmake`. You can read more about name [here](https://msdn.microsoft.com/en-us/library/dd9y37ha.aspx).

5. (Optional) Installing Flex
After running the make command, an executable called `flex` will be present. If you don't want to overwrite your systems installed version and header files; you can simply type in the path to this executable when running the `flex` command. IE `./util/flex-2.5.37/flex someFileName`. In the future we will also have to include some header files if you choose not to install this version of flex on your system.

To install Flex, run the following command:

```bash
make install
```

This will move the Flex executable and headers to their final destination.

## Building Our First Program with Flex
Flex is a library written in C with some header files that provides an interface for us to extend with C++. Due to this being the first introduction to Flex, we're not going to go into utilizing these headers just yet. Instead, I'm going to expose you to the grammar flex utilizes called the ANSI C grammar. Read more [here](http://www.quut.com/c/ANSI-C-grammar-l-1999.html).

### Parsing Integers
There are a number of ways to define what token and value will be parsed by Flex. The most common approaches include strings(character arrays) and regex. To get started, we must define a lex file for Flex to parse. We'll call this file "grammar.l"

```bash
# ensure you're at the root of this project
cd ../
touch grammar.l
```

Open grammar.l with your tool of choice. Note that syntax highlighting will generally not work.


To define Lex grammar for flex in a file, we begin and close the syntax block with `%%`

```c
// normal C/C++ code here
%%
  // flex grammar here
%%
// normal C/C++ code here
```

The general format for the flex grammar goes as follows:

```c

%%
  pattern to match { token to return }
%%

```

Currently we only care about integers. When parsing integers, a nice way to match the pattern is through regex. The regex pattern would be defined like so: `[0-9]+`. This states that any numbers, 0 through 9 ([0-9]), in a sequence (+) will be an integer. In future parsing where Regex is utilized, I will provide a description of what the Regex is matching.


For simplicity, we'll simply print out the token we'd want and the value when an integer is parsed.

```c
// grammar.l

{%
  // include basic C++ headers
  #include <iostream>
  using namespace std;
  #define YY_DECL extern "C" int yylex()
%}

%%

[0-9]+          { cout << "Found an integer:" << yytext << endl; }

%%

```

So where is the variable "yytext" coming from? yytext is provided by Flex and contains the current parsed value that a token represents. For example, if a file has the number "10" in it, the token is parsed, and yytext would equal "10".


We can currently compile this grammar file if we so chose to. For brevity, we can also include our `main` function in the same file.

```c
// grammar.l

%{
  // C++ headers

  #include <iostream>
  using namespace std;
  #define YY_DECL extern "C" int yylex()
%}

%%

[0-9]+          { cout << "Found an integer:" << yytext << endl; }

%%

int main() {
    yylex();
    return 0;
}

```

Flex provides a C function, `yylex`, that parses any input provided to it. In order to expose this function to C++, we can define `YY_DECL` macro and point it to the default yylex() function.

We can't compile the grammar file just yet. It must be first pre-processed by flex

```bash
./util/flex-2.5.37/flex --outfile=lex.yy.cpp grammar.l
```

The output will be sent to `lex.yy.cpp`. You may browse the lexer if you wish.

Once the generated file is created, we can then compile the file with any C++ compiler (I'm using g++ in this example).

```bash
g++ lex.yy.cpp -Lutil/flex-2.5.37 -lfl -o lex
```

To compile `lex.yy.cpp`, we must statically link the flex lexer to our program. If you ran `make install`, you can exclude `-Lutil/flex-2.5.37` as the shared library should be in a location the compiler can find by default. 

`-L` tells the compiler to look in a specified directory for libraries to include.

`-lfl` states to include the `fl` library, which should be named `libfl.a` or `libfl.so`. If you look in your flex directory, you should see libfl.a.

After successfully compiling `lex.yy.cpp`, you can run the executable with

```bash
./lex
```

A prompt will be open, and if you type in any integer, you should get output like the following below:

```
1
Found an integer:1

10
Found an integer:10
```

## Copyrights
Benjamin J. Anderson - 2017