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

Next we need to include the FlexLexer header file for our scanner class to extend. We have to ensure that it is included only once, otherwise Flex will fail to compile!

```C++
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
```

We also need to store scanning/parsing location information and import our token definitions from the parser (ie `%token <std::string> WORD` from parser.yy). We could redefine them for our scanner, but Flex and Bison make is easy to share information. The two header files, `parser.tab.hh` contains the token information, and `location.hh` contains our location scanning/parsing location.

```C++
#include "parser.tab.hh"
#include "location.hh"
```

### Generating location.hh
In order to generate the locations information, we need to define the locations directive in our parser. Simply add `%locations` and regenerate the bison parser.


### Scanner Definition
After generating the parser locations and including the needed headers: we can create our scanner definition.

```C++
#ifndef __FRONTENDSCANNER_HPP__
#define __FRONTENDSCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.tab.hh"
#include "location.hh"

namespace Frontend {
  class Scanner : public yyFlexLexer {

    private:
      Frontend::Parser::semantic_type *yylval = nullptr;
      Frontend::Parser::location_type *loc    = nullptr;
    public:

      Scanner(std::istream *in) : yyFlexLexer(in) {
        loc = new MC::MC_Parser::location_type();
      };
 
      using FlexLexer::yylex;
      virtual int yylex(Frontend::Parser::semantic_type * const lval, Frontend::Parser::location_type *location);
  };
}

#endif
```

## Copyrights
Benjamin J. Anderson - 2017