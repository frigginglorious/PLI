#ifndef __BYTECODEGENERATOR
#define __BYTECODEGENERATOR 1

#include <string>
#include <vector>
#include <iomanip>
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
      std::string instructionBuffer;
      std::string outputBuffer;

    public:
      Generator::InstructionEmitter* emit;
      std::vector<std::string> literals;
      int instructionCount = 0;

      ByteCode();
      ~ByteCode();
      void setState(GENERATORSTATE state);
      void resetState();
      void compile();
      void incrementInstructionCount(int amt);
      void emitSection(std::string label);
      void pushBuffer(std::string instructions);
      int addLiteral(std::string literal);
      std::string getBuffer();
      GENERATORSTATE getState();
  };

}

#endif