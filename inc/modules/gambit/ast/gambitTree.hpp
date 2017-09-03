#ifndef __GAMBIT_TREE_HPP__
#define __GAMBIT_TREE_HPP__ 1

#include "shared/ast/tree.hpp"

namespace Gambit
{

  class Tree : public AST::Tree
  {
      public:
        Tree() = default;
        virtual ~Tree();
        void push_nodes(std::vector<AST::Node*> nodes);
        void pushNode(AST::Node *node);
        int treeSize();
        void compile();
  };

}

#endif