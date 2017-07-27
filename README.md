# Programming Language Implementations
Creating a C++ Scanner with Flex

## FlexLexer Header
Flex, when installed or extracted in the util directory, provides a header file called FlexLexer.h. This header contains the definitions to constructing a scanner class with Flex. It's most basic form provides the following:

- void Constructor(istream *in): in - pointer to an input stream
- int yylex(): Parameters vary. We're going to override with by storing the last parsed value (lval) and parse location information (location)

The only properties we'll be utilizing, in a private scope, are yylval (the scanner last value) and the current location.

## Our Class Header
Let's create a file called scanner.hpp (or whichever extension you wish to use).
```bash
touch scanner.hpp
```

And we'll add our standard header definition with the namespace `Frontend` (recall in parser.yy that we're passing in the scanner class?).

```C++
#ifndef __FRONTENDSCANNER_HPP__
#define __FRONTENDSCANNER_HPP__ 1

namespace Frontend {
  
}

#endif
```

## Copyrights
Benjamin J. Anderson - 2017