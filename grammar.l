%{
  
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "scanner.hpp"
#undef  YY_DECL
#define YY_DECL int Frontend::Scanner::yylex( Frontend::Parser::semantic_type * const lval, Frontend::Parser::location_type *location )

/* using "token" to make the returns for the tokens shorter to type */
using token = Frontend::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching 
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);
*/

%}

%option debug
%option nodefault
%option yyclass="Frontend::Scanner"
%option noyywrap
%option c++

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

[a-zA-Z]+   {
               yylval->build< std::string >( yytext );
               return( token::WORD );
            }

\n          {
               /** Update line number **/
               loc->lines();
               return( token::NEWLINE );
            }

.           {
               return( token::CHAR );
            }
%%