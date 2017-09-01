#include <fstream>
#include "gambit/driver.hpp"

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    Gambit::Driver gambitDriver;
    return gambitDriver.parse(argv[1]);
  }
  return 1;
}