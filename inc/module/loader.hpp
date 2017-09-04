#ifndef __MODULE_LOADER_HPP__
#define __MODULE_LOADER_HPP__ 1

#include <dlfcn.h>
#include <string>
#include <iostream>

namespace Modules
{

  class Loader
  {

    protected:

      std::string moduleName;
      std::string errorMsg;
      bool errored = false;
      void* handle;

    public:

      Loader()=default;

      Loader(std::string moduleName)
      {
        this->moduleName = moduleName;
        this->handle = dlopen(this->moduleName.c_str(), RTLD_NOW);
        if (!this->handle)
        {
          this->errored = true;
          this->errorMsg = std::string(dlerror());
        }
      };

      virtual ~Loader()
      {
        std::cout << "Unloading library " << this->moduleName << std::endl;
        dlclose(this->handle);
      };

      virtual bool load() = 0;

      bool loaded()
      {
        return !this->errored;
      };

      std::string getError()
      {
        return this->errorMsg;
      };

  };
}

#endif