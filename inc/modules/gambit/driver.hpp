#ifndef __GAMBIT_DRIVER_HPP__
#define __GAMBIT_DRIVER_HPP__ 1

#include <cctype>
#include <fstream>
#include <cassert>

#include "shared/driver.hpp"
#include "modules/gambit/scanner.hpp"
#include "modules/gambit/parser.tab.hpp"

namespace Gambit
{

  class Driver : public Extensions::Driver
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