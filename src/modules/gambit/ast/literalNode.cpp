#include "modules/gambit/ast/literalNode.hpp"
#include <iostream>

Gambit::LiteralNode::LiteralNode(int value, DATATYPE type)
{
  this->type = type;
  this->intValue = value;
}

Gambit::LiteralNode::~LiteralNode()
{
  std::cout << "Destructor Literal Node" << std::endl;
}

void
Gambit::LiteralNode::compile()
{
  switch(this->type)
  {
    case INTEGER:
      std::cout << "Compiling Type: " << this->type << " with value: " << intValue << " Addr: " <<  this <<std::endl;
      break;
    default:
      std::cout << "Compiling datatype node" << std::endl;
      break;
  }
}