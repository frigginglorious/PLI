%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Gambit}
%define parser_class_name {Parser}

%code requires {

  #include <vector>
  #include "dev/debugnew/debug_new.h"
  #include "shared/datatypes.hpp"

  namespace AST
  {
    class Tree;
    class Node;
  }

  namespace Gambit {
    class Scanner;
    class Tree;
    class LiteralNode;
    class Driver;
  }
}

%parse-param { Gambit::Scanner &scanner }
%parse-param { Gambit::Driver  &driver  }

%code {

  #include "modules/gambit/driver.hpp"
  #include "modules/gambit/scanner.hpp"
  #include "modules/gambit/ast/gambitTree.hpp"
  #include "modules/gambit/ast/literalNode.hpp"

  #undef yylex
  #define yylex scanner.yylex

}

%destructor { std::cout << "Delete Parser" << std::endl; if ($$)  { delete ($$); ($$) = nullptr; } } <tree> <node>

%locations

%token                   END          0  "end of file"
%token       <ival>      T_INTEGER
%token                   T_NEWLINE

%union {
  int ival;
  DATATYPE type;
  AST::Tree *tree;
  AST::Node *node;
}

%type <tree>    Expressions
%type <node>    Expression Literals

%%

root:
  END
  | Expressions END                     { driver.setTree($1); }
  ;

Expressions:
  Expression                        {
                                      std::vector<AST::Node *> nodes;
                                      nodes.push_back($1);
                                      $$ = new Gambit::Tree(nodes);
                                      
                                    }
  | Expressions Terminator Expression {
                                        $1->pushNode($3);
                                        $$ = $1;
                                      }

  | Expressions Terminator          { $$ = $1; }
  ;

Expression:
    Literals
  ;

Literals:
  T_INTEGER                           {
                                        $$ = new Gambit::LiteralNode($1, INTEGER);
                                        std::cout << "Found integer" << " Addr: " << $$ << std::endl;
                                      }
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