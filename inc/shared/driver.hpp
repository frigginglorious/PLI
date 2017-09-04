#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <iostream>

namespace AST
{
  class Tree;
}

namespace Extensions
{

  class Driver
  {

    public:
      virtual int parse( const char *filename )=0;
      virtual AST::Tree* getTree()=0;
      virtual ~Driver(){
        std::cout << "Deleting Ext::Driver" << std::endl;
      };

  };

}

#endif