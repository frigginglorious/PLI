#include <fstream>
#include "gambit/scanner.hpp"
#include "gambit/parser.tab.hpp"

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    const char * const fileName = argv[1];
    std::ifstream inFile( fileName );

    if ( !inFile.good() ) { return 2; }

    Gambit::Scanner scanner( &inFile );
    Gambit::Parser parser( scanner );

    if ( parser.parse() != 0 ) { return 3; }

    return 0;
  }
  return 1;
}