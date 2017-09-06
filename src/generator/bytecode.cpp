#include "generator/bytecode.hpp"
#include "dev/debugnew/debug_new.h"

Generator::ByteCode::ByteCode()
{
  this->emit = new Generator::InstructionEmitter(this);
}

Generator::ByteCode::~ByteCode()
{
  delete(this->emit);
}

void
Generator::ByteCode::setState(GENERATORSTATE state)
{
  this->state = state;
}

void
Generator::ByteCode::resetState()
{
  this->state = DEFAULT;
}

void
Generator::ByteCode::pushBuffer(std::string instructions)
{
  this->buffer.append(instructions);
}

std::string
Generator::ByteCode::getBuffer()
{
  return this->buffer;
}

int
Generator::ByteCode::addLiteral(std::string literal)
{
  auto pred = [literal](std::string & search)
  {
    return search == literal;
  };
  auto index = std::find_if(this->literals.begin(), this->literals.end(), pred);
  if(index != this->literals.end())
  {
    return index - this->literals.begin();
  }
  this->literals.push_back(literal);
  return this->literals.size() - 1;
}

GENERATORSTATE
Generator::ByteCode::getState()
{
  return this->state;
}