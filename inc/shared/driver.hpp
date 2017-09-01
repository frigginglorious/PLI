#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

namespace Extensions
{
  class Driver
  {
    public:
      virtual int parse( const char *filename )=0;
  };
}

#endif