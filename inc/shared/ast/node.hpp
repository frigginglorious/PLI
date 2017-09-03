#pragma once

#ifndef __AST_NODE
#define __AST_NODE 1

namespace AST
{

  class Node
  {
    public:

      virtual void compile() = 0;

  };

}

#endif