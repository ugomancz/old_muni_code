/* Represents a 32-bit processor */
#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdio.h>

enum cpuStatus {
    cpuOK,
    cpuHalted,
    cpuIllegalInstruction,
    cpuIllegalOperand,
    cpuInvalidAddress,
    cpuInvalidStackOperation,
    cpuDivByZero,
    cpuIOError
};

struct cpu {
    int32_t A;
    int32_t B;
    int32_t C;
    int32_t D;
    enum cpuStatus status;
    int32_t stackSize;
    int32_t instructionPointer;
    int32_t *memory;
    int32_t *stackBottom;
    int32_t *stackLimit;
#ifdef BONUS_JMP
    int32_t result;
#endif
};

/**
 * \brief Creates memory for cpu structure to use
 *
 * Reads and saves instructions and their arguments from FILE program.
 * If input file is empty, allocates only enough memory for stack, if
 * input file is empty and stackCapacity is 0, doesn't allocate anything.
 *
 * @param program is input file containing instructions and their arguments
 * @param stackCapacity is number of int32_ts, that are reserved for stack at the end of memory
 * @param stackBottom is a pointer to bottom of stack
 *
 * @return pointer to initiated memory or NULL if function failed
 */
int32_t *cpuCreateMemory(FILE *program, size_t stackCapacity, int32_t **stackBottom);

/**
 * \brief Initiates the cpu structure
 *
 * @param cpu that's to be initiated
 * @param memory is a pointer to memory with instructions and stack
 * @param stackBottom points to bottom of stack
 * @param stackCapacity points to top of stack
 */
void cpuCreate(struct cpu *cpu, int32_t *memory, int32_t *stackBottom, size_t stackCapacity);

/**
 * \brief Destroys the cpu structure
 *
 * Sets all pointers to NULL and values to 0
 */
void cpuDestroy(struct cpu *cpu);

/**
 * Nulls all the registers, sets cpuStatus to cpuOK, empties and
 * nulls the stack
 */
void cpuReset(struct cpu *cpu);

/**
 *
 * @return status code of given cpu structure
 */
int cpuStatus(struct cpu *cpu);

/**
 * \brief Executes one instruction
 *
 * @return 0 on failure, !0 otherwise
 */
int cpuStep(struct cpu *cpu);

/**
 * \brief Executes \a steps of instructions.
 *
 * @param steps is number of instructions to be executed
 * @return number of successfully executed instructions until error state was reached
 */
int cpuRun(struct cpu *cpu, size_t steps);

/**
 *
 * @return value of cpu's register reg
 */
int32_t cpuPeek(struct cpu *cpu, char reg);

#endif
