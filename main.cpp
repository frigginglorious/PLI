#include <fstream>
#include "scanner.hpp"
#include "parser.tab.hh"

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    Frontend::Scanner *scanner;
    Frontend::Parser *parser;
    const char * const fileName = argv[1];
    std::ifstream inFile( fileName );

    if ( !inFile.good() ) { return 2; }

    scanner = new Frontend::Scanner(&inFile);
    parser = new Frontend::Parser(*scanner);

    if ( parser->parse() != 0 ) { return 3; }

    return 0;
  }
  return 1;
}