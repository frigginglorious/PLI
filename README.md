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

4.5 (Optional) Installing Flex
After running the make command, an executable called `flex` will be present. If you don't want to overwrite your systems installed version and header files; you can simply type in the path to this executable when running the `flex` command. IE `./util/flex-2.5.37/flex someFileName`. In the future we will also have to include some header files if you choose not to install this version of flex on your system.

To install Flex, run the following command:

```bash
make install
```

This will move the Flex executable and headers to their final destination.

## Building Our First Program with Flex
TODO

## Copyrights
Benjamin J. Anderson - 2017