#include "modules/gambit/ast/gambitTree.hpp"
#include <iostream>

Gambit::Tree::Tree(std::vector<AST::Node*> nodes)
{
  this->nodes = nodes;
}

Gambit::Tree::~Tree()
{
  std::cout << "Deleting Gambit::Tree" << std::endl;
}

void
Gambit::Tree::pushNodes(std::vector<AST::Node*> nodes)
{
  
}

void
Gambit::Tree::pushNode(AST::Node *node)
{
  this->nodes.push_back(node);
}

int
Gambit::Tree::treeSize()
{
  return 0;
}

void
Gambit::Tree::compile()
{
  std::cout << "Compiling node tree" << std::endl;
  for (auto &n : nodes)
  {
    n->compile();
  }
}