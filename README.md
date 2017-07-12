# Programming Language Implementations
Parsing with Bison

## What is Bison?
Bison is a parser generator that can output a variety of parser types. In our case, we're going to be generating an LALR1 parser. This simply means it parses a file from the Top-down and from Left-to-Right with the ability to look ahead for tokens. When we hook Flex and Bison together, we get end up with a Lexical Analyzer and a Syntax Analyzer. As opposed to simply finding tokens and associating a value with the found token; Bison will try to make sense of what these tokens mean in our language. After which, we can construct our Abstract Syntax Tree (AST) and compile or interpret the nodes. 

## Installing Bison
This repository includes Bison v3.0.4 in the `util` directory. Most Linux and MacOSX distributions already include Bison by default. Newer and older versions of Bison may not be compatible with this tutorial. 

1. In order to install the version of Bison included in this repository, navigate to the `util` directory.

2. The Bison package is compressed using a gunzip and tarball compressor, use any standard tarball archive utility or run the following command

```bash
cd util/
tar xvzf file.tar.gz
```

The `x` flag tells the archive utility to extract the files.

`v` means "verbose", which will list all of the files one-by-one.

`z` The z option is very important and tells the tar command to uncompress the file (gzip).

`f` tells the archive utility that we're going to supply the file to extract.

3. Navigate to the Flex directory and run the configure command. This will ensure all dependencies are available in order to install Flex.

```bash
cd bison-3.0.4
./configure
```

Note:

You may have to resolve any dependencies that are not installed on your system. A quick google search of the error and your operating system will generally give you a good idea on how to install the missing dependency. If you are unable to resolve the issue, send me an issue on Github.


4. Build Bison
In order to build Bison, and to continue through this series, we need a tool called `Make`. You can read more about it and install it [here](https://www.gnu.org/software/make/). Most Linux and MacOSX distributions already come with make installed. You can test this by running ` make -v`.

If you're using Windows, you'll have to utilize `nmake`. You can read more about name [here](https://msdn.microsoft.com/en-us/library/dd9y37ha.aspx).

5. (Optional) Installing Bison
After running the make command, an executable called `bison` will be present. If you don't want to overwrite your systems installed version and header files; you can simply type in the path to this executable when running the `flex` command. IE `./util/bison-3.0.4/src/bison someFileName`. In the future we will also have to include some header files if you choose not to install this version of bison on your system.

To install Bison, run the following command:

```bash
make install
```

This will move the Bison executable and headers to their final destination.



## Copyrights
Benjamin J. Anderson - 2017