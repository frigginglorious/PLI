#ifndef __BYTECODEGENERATOR
#define __BYTECODEGENERATOR 1

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "generator/state.hpp"
#include "generator/instructionEmitter.hpp"

namespace Generator
{

  class InstructionEmitter;

  class ByteCode
  {

    protected:
      GENERATORSTATE state = DEFAULT;
      std::string buffer;

    public:
      Generator::InstructionEmitter* emit;
      std::vector<std::string> literals;

      ByteCode();
      ~ByteCode();
      void setState(GENERATORSTATE state);
      void resetState();
      void pushBuffer(std::string instructions);
      int addLiteral(std::string literal);
      std::string getBuffer();
      GENERATORSTATE getState();
  };

}

#endif