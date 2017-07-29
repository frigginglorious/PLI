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

Here we extend yyFlexLexer defined in FlexLexer.h. We pass in a stream pointer to our constructor and initialize it with the parent constructor. We also initialize the yylval pointer to null. The only function we need to define is yylex. yylex will be generated from our output of when we run flex on grammar.l. We've defined yylex as virtual, which may cause an override error. To work around this error, we stated that we're using Flexlexer::yylex. This tells the compiler that we're defining our own yylex function as opposed to utilizing the default in yyFlexLexer.

## A New Grammar File
The next step for our counter program is to clear out the grammar.l file so we can start from scratch. Our first step is our includes section. To count words, we'll require some string functions. We also need to include our scanner class that will extend yyFlexLexer.

You'll also notice we undefined YY_DECL and redefined it to point to our scanner class yylex method. If we don't define the yylex function in YY_DECL, flex will used the default yylex function, which doesn't support location tracking.

YY_USER_ACTION executes code after every lex action (parsing a character, number etc.). In our case, we want to update the location and current column.

```C++

%{
  
#include <string>
#include "scanner.hpp"

#undef  YY_DECL
#define YY_DECL int Frontend::Scanner::yylex( Frontend::Parser::semantic_type * const lval, Frontend::Parser::location_type *location )

/* using "token" to make the returns for the tokens shorter to type */
using token = Frontend::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

```


Next, we need to set some options so flex knows we're generating a C++ scanner:

```C++
%option debug
%option nodefault
%option yyclass="Frontend::Scanner"
%option noyywrap
%option c++
```

We need to specify nodefault to override yylex, add some debug options with %debug, specify our class name, and that we're utilizing C++. We can then generate our scanner:

```bash
./util/flex-2.5.37/flex --outfile=lex.yy.cpp grammar.l
```

Next tutorial we'll be joining Flex and Bison together with a Driver, which will also contain the counting results fro, Bison.

## Copyrights
Benjamin J. Anderson - 2017