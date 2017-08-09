%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Frontend}
%define parser_class_name {Parser}

%code requires {
  namespace Frontend {
    class Scanner;
  }
}

%parse-param { Frontend::Scanner &scanner }

%code {

#include "scanner.hpp"

#undef yylex
#define yylex scanner.yylex

}

%define api.value.type variant
%define parse.assert

%token <std::string> WORD
%token               NEWLINE
%token               CHAR
%token               END    0     "end of file"


%locations

%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : WORD    { std::cout << "Found WORD" << std::endl; }
  | NEWLINE { /* do nothing yet in c++ */  }
  | CHAR    { /* do nothing yet in c++ */  }
  ;

%%

void 
Frontend::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
