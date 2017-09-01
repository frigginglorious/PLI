#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include "shared/driver.hpp"

using namespace std;

int main( const int argc, const char **argv )
{
  if ( argc == 2 )
  {
    void *handle;
    handle = dlopen("./lib/gambit.so", RTLD_NOW);
    if (!handle)
    {
      printf("The error is %s", dlerror());
    }

    typedef Extensions::Driver* create_t();
    typedef void destroy_t(Extensions::Driver*);

    create_t* creat=(create_t*)dlsym(handle,"create");
    destroy_t* destroy=(destroy_t*)dlsym(handle,"destroy");

    if (!creat)
    {
           cout<<"The error is %s"<<dlerror();
    }
    if (!destroy)
    {
           cout<<"The error is %s"<<dlerror();
    }

    Extensions::Driver* driver = creat();

    driver->parse(argv[1]);

    destroy(driver);

  }
  return 1;
}