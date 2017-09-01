%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Gambit}
%define parser_class_name {Parser}

%code requires {
  namespace Gambit {
    class Scanner;
  }
}

%parse-param { Gambit::Scanner &scanner }

%code {

  #include "modules/gambit/scanner.hpp"

  #undef yylex
  #define yylex scanner.yylex

}

%locations

%token       <ival>      T_INTEGER
%token                   T_NEWLINE

%union {
  int ival;
}

%%

root:
   Expressions
  ;

Expressions:
  Expression                        {}
  Expressions Terminator Expression {}
  |                                 {}
  ;

Expression:
  T_INTEGER { std::cout << "Found Integer: " << $1 << std::endl; }
  ;

Terminator:
  T_NEWLINE
  ;

%%

void
Gambit::Parser::error(const location_type& l, const std::string& m )
{
  std::cout << m << std::endl;
}