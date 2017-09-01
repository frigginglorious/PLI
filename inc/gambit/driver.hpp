#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <cctype>
#include <fstream>
#include <cassert>

#include "gambit/scanner.hpp"
#include "gambit/parser.tab.hpp"

namespace Gambit
{

  class Driver
  {

    public:

      Driver() = default;
      virtual ~Driver();
      int parse( const char *filename );


    private:

       Gambit::Parser  *parser  = nullptr;
       Gambit::Scanner *scanner = nullptr;
  };

}

#endif