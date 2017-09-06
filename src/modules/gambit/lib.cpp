#include "modules/gambit/driver.hpp"
#include "dev/debugnew/debug_new.h"

extern "C" Gambit::Driver* create()
{
    return new Gambit::Driver();
}

extern "C" void destroy(Gambit::Driver* Tl)
{
   delete Tl ;
}