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
        loc = new Frontend::Parser::location_type();
      };

      using FlexLexer::yylex;
      virtual int yylex(Frontend::Parser::semantic_type * const lval, Frontend::Parser::location_type *location);
  };

}

#endif