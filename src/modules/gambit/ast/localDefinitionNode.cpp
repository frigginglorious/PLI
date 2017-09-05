#include <iostream>
#include "modules/gambit/ast/localDefinitionNode.hpp"

Gambit::LocalDefinitionNode::LocalDefinitionNode(std::string className, std::string identifier, AST::Node* expression)
{
  this->identifier = identifier;
  this->className = className;
  this->valueNode = expression;
}

Gambit::LocalDefinitionNode::~LocalDefinitionNode()
{
  if (this->valueNode != nullptr)
  {
    delete(this->valueNode);
  }
}

void
Gambit::LocalDefinitionNode::compile()
{
  std::cout << "Compiling LocalDefinitionNode: " << this->identifier << " " << this->className << std::endl;
  if (this->valueNode != nullptr)
  {
    this->valueNode->compile();
  }
}