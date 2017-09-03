#ifndef __AST_TREE
#define __AST_TREE 1

#include <vector>

#include "shared/ast/node.hpp"

namespace AST
{

  class Tree
  {

    public:
      virtual ~Tree() = default;
      virtual void push_nodes(std::vector<AST::Node*> nodes) = 0;
      virtual void pushNode(AST::Node *node) = 0;
      virtual int treeSize() = 0;
      virtual void compile() = 0;

    private:
      std::vector<AST::Node*> nodes;

  };

}

#endif