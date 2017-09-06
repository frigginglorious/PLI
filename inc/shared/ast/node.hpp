#pragma once

#ifndef __AST_NODE
#define __AST_NODE 1

#include <iostream>
#include "generator/bytecode.hpp"

namespace Generator
{
  class ByteCode;
}

namespace AST
{

  class Node
  {
    public:
      virtual ~Node(){};
      virtual void compile(Generator::ByteCode* bcGenerator) = 0;

  };

}

#endif