#ifndef __OPCODES
#define __OPCODES 1

#include <string>

enum OPCODE{
  NOOP,
  PUSH_INTEGER,
  SET_LOCAL,
  POP
};

#define EMIT_0(opcode)                                      \
{                                                           \
  instructions.append("\t")                                 \
    .append(opInstructions[opcode]).append("\n");           \
}

#define EMIT_1(opcode, operand1)                            \
{                                                           \
  instructions.append("\t")                                 \
    .append(opInstructions[opcode]).append(" ")             \
      .append(operand1).append("\n");                       \
}

#define EMIT_2(opcode, operand1, operand2)                  \
{                                                           \
  instructions.append("\t")                                 \
    .append(opInstructions[opcode]).append(" ")             \
    .append(" ").append(operand1).append(" ")               \
      .append(operand2).append("\n");                       \
}

#endif