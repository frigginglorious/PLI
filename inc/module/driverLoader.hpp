#ifndef __DRIVERMODULE_LOADER_HPP__
#define __DRIVERMODULE_LOADER_HPP__ 1

#include "shared/ast/tree.hpp"
#include "shared/driver.hpp"
#include "module/loader.hpp"

typedef Extensions::Driver* createDriverT();
typedef void destroyDriverT(Extensions::Driver*);

namespace Modules
{

  class DriverLoader : public Modules::Loader
  {
    private:
      Extensions::Driver* driver;
      createDriverT* create;
      destroyDriverT* destroy;

    public:

      using Loader::Loader;

      DriverLoader();
      virtual ~DriverLoader();
      bool load();
      Extensions::Driver* getDriver();
  };
}

#endif