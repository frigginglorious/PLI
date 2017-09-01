#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include "module/driverLoader.hpp"

using namespace std;

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    Modules::DriverLoader* driver = new Modules::DriverLoader();
    driver->load();
    if (driver->loaded())
    {
      driver->getDriver()->parse(argv[1]);
    }
    delete(driver);
  }
  return 1;
}