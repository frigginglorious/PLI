#include "module/driverLoader.hpp"
#include "dev/debugnew/debug_new.h"
#include <iostream>

Modules::DriverLoader::DriverLoader()
{
  this->moduleName = "./lib/gambit.so";
  this->handle = dlopen(this->moduleName.c_str(), RTLD_NOW);
}

Modules::DriverLoader::~DriverLoader()
{
  if (this->destroy && this->driver)
  {
    this->destroy(this->driver);
    this->driver = nullptr;
  }
}

bool
Modules::DriverLoader::load()
{
  this->create  = (createDriverT*)dlsym(handle,"create");
  this->destroy = (destroyDriverT*)dlsym(handle,"destroy");
  if (!this->create || !this->destroy)
  {
    this->errored = true;
    this->errorMsg = std::string(dlerror());
    return false;
  }
  this->driver = this->create();
  return true;
}

Extensions::Driver*
Modules::DriverLoader::getDriver()
{
  return this->driver;
}