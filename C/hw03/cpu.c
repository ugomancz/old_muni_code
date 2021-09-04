#include "cpu.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef enum numFuncs {ADD, SUB, MUL, DIV, INC, DEC} numFuncs;
typedef enum IO {LOAD, STORE} IO;

static int32_t* getReg(struct cpu *cpu, int32_t reg) { // returns pointer to given register
    assert(cpu != NULL);
    switch (reg) {
        case 0:
            return &cpu->A;
        case 1:
            return &cpu->B;
        case 2:
            return &cpu->C;
        case 3:
            return &cpu->D;
#ifdef BONUS_JMP
        case 4:
            return &cpu->result;
#endif
        default: // invalid register
            cpu->status = cpuIllegalOperand;
            return NULL;
    }
}

/* Here come instructions */

void cpuNop(struct cpu *cpu) { // does nothing
    ++cpu->instructionPointer;
}

void cpuHalt(struct cpu *cpu) { // sets the cpuHalted state
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    cpu->status = cpuHalted;
    ++cpu->instructionPointer;
    return;
}

/**
 * Helper function, works in place of ADD, SUB, MUL, DIV, INC and DEC functions
 *
 * @param func tells which instruction is to be executed
 */
static void cpuNumOps(struct cpu *cpu, int32_t reg, numFuncs func) {
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t* newReg = getReg(cpu, reg);
    if (newReg == NULL) { // invalid register
        return;
    }
    switch (func) {
        case ADD:
            cpu->A += *newReg;
            break;
        case SUB:
            cpu->A -= *newReg;
            break;
        case MUL:
            cpu->A *= *newReg;
            break;
        case DIV:
            if (*newReg == 0) {
                cpu->status = cpuDivByZero;
                return;
            }
            cpu->A /= *newReg;
            break;
        case INC:
            ++(*newReg);
#ifdef BONUS_JMP
            cpu->result = *newReg;
#endif
            cpu->instructionPointer += 2;
            return;
        case DEC:
            --(*newReg);
#ifdef BONUS_JMP
            cpu->result = *newReg;
#endif
            cpu->instructionPointer += 2;
            return;
    }
    cpu->instructionPointer += 2;
#ifdef BONUS_JMP
    cpu->result = cpu->A;
#endif
}

/**
 * Helper function, works in place of LOAD and STORE functions
 * @param reg represents given register
 * @param (num + D)th index from top of stack
 * @param ins LOAD or STORE
 */
static void cpuIO(struct cpu *cpu, int32_t reg, int32_t num, IO ins) {
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 2 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t index = cpu->D + num;
    if (index >= cpu->stackSize || index < 0) { // index not pointing inside the stack
        cpu->status = cpuInvalidStackOperation;
        return;
    }
    int32_t* newReg = getReg(cpu, reg);
    if (newReg == NULL) { // invalid register
        return;
    }
    switch (ins) {
        case LOAD:
#ifdef BONUS_JMP
            if (newReg == &cpu->result) { // register result is read only
                cpu->status = cpuIllegalOperand;
                break;
            }
#endif
            *newReg = *(cpu->stackBottom - cpu->stackSize + index + 1);
            break;
        case STORE:
            *(cpu->stackBottom - cpu->stackSize + index + 1) = *newReg;
            break;
    }
    cpu->instructionPointer += 3;
}

/*
 * Next eight functions are wrapper functions using cpuNumOps and cpuIO
 */

void cpuAdd(struct cpu *cpu) { // ads given register's value to register A
    assert(cpu != NULL);
    cpuNumOps(cpu, cpu->memory[cpu->instructionPointer + 1], ADD);
}

void cpuSub(struct cpu *cpu) { // subtracts given register's value from register A
    assert(cpu != NULL);
    cpuNumOps(cpu, cpu->memory[cpu->instructionPointer + 1], SUB);
}

void cpuMul(struct cpu *cpu) { // multiplies register A by given register's value
    assert(cpu != NULL);
    cpuNumOps(cpu, cpu->memory[cpu->instructionPointer + 1], MUL);
}

void cpuDiv(struct cpu *cpu) { // divides register A by given register's value
    assert(cpu != NULL);
    cpuNumOps(cpu, cpu->memory[cpu->instructionPointer + 1], DIV);
}

void cpuInc(struct cpu *cpu) { // increases given register's value by 1
    assert(cpu != NULL);
    cpuNumOps(cpu, cpu->memory[cpu->instructionPointer + 1], INC);
}

void cpuDec(struct cpu *cpu) { // decreases given register's value by 1
    assert(cpu != NULL);
    cpuNumOps(cpu, cpu->memory[cpu->instructionPointer + 1], DEC);
}

void cpuLoad(struct cpu *cpu) { // loads value from stack to given register
    assert(cpu != NULL);
    cpuIO(cpu, cpu->memory[cpu->instructionPointer + 1], cpu->memory[cpu->instructionPointer + 2], LOAD);
}

void cpuStore(struct cpu *cpu) { // stores value from given register to stack
    assert(cpu != NULL);
    cpuIO(cpu, cpu->memory[cpu->instructionPointer + 1], cpu->memory[cpu->instructionPointer + 2], STORE);
}

void cpuLoop(struct cpu *cpu) { // jumps to instruction on cpu->memory[index] if register C != 0
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    if (cpu->C == 0) {
        cpu->instructionPointer += 2;
        return;
    }
    cpu->instructionPointer = cpu->memory[cpu->instructionPointer + 1];
}

void cpuMovr(struct cpu *cpu) { // saves num to given register
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 2 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t* newReg = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
    if (newReg == NULL) {
        return;
    }
#ifdef BONUS_JMP
    if (newReg == &cpu->result) {
        cpu->status = cpuIllegalOperand;
        cpu->instructionPointer += 3;
        return;
    }
#endif
    *newReg = cpu->memory[cpu->instructionPointer + 2];
    cpu->instructionPointer += 3;
}

void cpuIn(struct cpu *cpu) { // saves int32_t from stdin to given register
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t *newReg = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
#ifdef BONUS_JMP
    if (newReg == &cpu->result) {
        cpu->status = cpuIllegalOperand;
        cpu->instructionPointer += 2;
        return;
    }
#endif
    if (scanf("%d]", newReg) != 1) { // couldn't read a number from input
        if (feof(stdin)) { // EOF on input
            cpu->C = 0;
            *newReg = -1;
            cpu->instructionPointer += 2;
            return;
        }
        cpu->status = cpuIOError; // non-number on input
        return;
    }
    cpu->instructionPointer += 2;
}

void cpuGet(struct cpu *cpu) { // saves one byte from stdin to given register
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int byte;
    int32_t* newReg = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
#ifdef BONUS_JMP
    if (newReg == &cpu->result) {
        cpu->status = cpuIllegalOperand;
        cpu->instructionPointer += 2;
        return;
    }
#endif
    if (newReg == NULL) { // invalid register
        return;
    }
    if ((byte = getchar()) == EOF) { // no bytes on input
        cpu->C = 0;
        *newReg = -1;
        cpu->instructionPointer += 2;
        return;
    }
    *newReg = (int32_t) byte;
    cpu->instructionPointer += 2;
}

void cpuOut(struct cpu *cpu) { // prints given register's value to stdin as a number
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t* newReg = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
    if (newReg == NULL) { // invalid register
        return;
    }
    printf("%d", *newReg);
    cpu->instructionPointer += 2;
}

void cpuPut(struct cpu *cpu) { // if given register's value is 0 <= value < 256, prints the value to stdin as char
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t* newReg = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
    if (newReg == NULL) { // invalid register
        return;
    }
    if (*newReg < 256 && *newReg >= 0) {
        printf("%c", *newReg);
        cpu->instructionPointer += 2;
        return;
    }
    cpu->status = cpuIllegalOperand;
}

void cpuSwap(struct cpu *cpu) { // swaps values in two given registers
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 2 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t* regOne = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
    int32_t* regTwo = getReg(cpu, cpu->memory[cpu->instructionPointer + 2]);
    int32_t temp;
    if (regOne == NULL || regTwo == NULL) { // one of given registers isn't valid
        return;
    }
#ifdef BONUS_JMP
    if (regOne == &cpu->result || regTwo == &cpu->result) { // register result is read only
        cpu->status = cpuIllegalOperand;
        return;
    }
#endif
    temp = *regOne;
    *regOne = *regTwo;
    *regTwo = temp;
    cpu->instructionPointer += 3;
}

void cpuPush(struct cpu *cpu) { // puts given register's value on stack
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t* newReg = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
    if (newReg == NULL) { // invalid register
        return;
    }
    if (cpu->stackBottom - cpu->stackSize <= cpu->stackLimit) { // stack is full
        cpu->status = cpuInvalidStackOperation;
        return;
    }
    *(cpu->stackBottom - cpu->stackSize) = *newReg;
    ++cpu->stackSize;
    cpu->instructionPointer += 2;
}

void cpuPop(struct cpu *cpu) { // pops value from stack and saves it to given register
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    if (cpu->stackSize < 1) { // if stack is empty
        cpu->status = cpuInvalidStackOperation;
        return;
    }
    int32_t* newReg = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
#ifdef BONUS_JMP
    if (newReg == &cpu->result) { // register result is read only
        cpu->status = cpuIllegalOperand;
        return;
    }
#endif
    if (newReg == NULL) { // invalid register
        return;
    }
    *newReg = *(cpu->stackBottom - cpu->stackSize + 1);
    --cpu->stackSize;
    cpu->instructionPointer += 2;
}

/* Instructions from the first bonus, BONUS_JMP */

#ifdef BONUS_JMP
void cpuCmp(struct cpu *cpu) { // compares values of two given registers and saves the result to register result
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 2 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    int32_t *regOne = getReg(cpu, cpu->memory[cpu->instructionPointer + 1]);
    int32_t *regTwo = getReg(cpu, cpu->memory[cpu->instructionPointer + 2]);
    if (regOne == NULL || regTwo == NULL) { // one of the given registers isn't valid
        return;
    }
    cpu->result = *regOne - *regTwo;
    cpu->instructionPointer += 3;
}

void cpuJmp(struct cpu *cpu) { // unconditional jump to given instruction index
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    cpu->instructionPointer = cpu->memory[cpu->instructionPointer + 1];
}

void cpuJz(struct cpu *cpu) { // if register result == 0, jumps to given instruction index
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    if (cpu->result == 0) {
        cpu->instructionPointer = cpu->memory[cpu->instructionPointer + 1];
        return;
    }
    cpu->instructionPointer += 2;
}

void cpuJnz(struct cpu *cpu) { // if register result != 0, jumps to given instruction index
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    if (cpu->result != 0) {
        cpu->instructionPointer = cpu->memory[cpu->instructionPointer + 1];
        return;
    }
    cpu->instructionPointer += 2;
}

void cpuJgt(struct cpu *cpu) { // if register result > 0, jumps to given instruction index
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    if (cpu->result > 0) {
        cpu->instructionPointer = cpu->memory[cpu->instructionPointer + 1];
        return;
    }
    cpu->instructionPointer += 2;
}
#endif

/* Instructions from the second bonus, BONUS_CALL */

#ifdef BONUS_CALL
void cpuCall(struct cpu *cpu) { // saves next instruction's index to stack, then jumps to given instruction index
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return;
    }
    if (cpu->memory + cpu->instructionPointer + 1 > cpu->stackLimit) { // instruction operand on stack
        cpu->status = cpuInvalidAddress;
        return;
    }
    if (cpu->stackBottom - cpu->stackSize <= cpu->stackLimit) { // stack is full
        cpu->status = cpuInvalidStackOperation;
        return;
    }
    *(cpu->stackBottom - cpu->stackSize) = cpu->instructionPointer + 2;
    ++cpu->stackSize;
    cpu->instructionPointer = cpu->memory[cpu->instructionPointer + 1];
}

void cpuRet(struct cpu *cpu) { // jumps to the instruction index saved on the top of stack
    if (cpu->stackSize < 1) { // if stack is empty
        cpu->status = cpuInvalidStackOperation;
        return;
    }
    cpu->instructionPointer = *(cpu->stackBottom - cpu->stackSize + 1);
    --cpu->stackSize;
}
#endif

/* Here come CPU functions */

/**
 * Dynamically allocates memory based on stackCapacity
 *
 * @returns allocated memory or NULL if allocation failed
 */
int32_t *onlyStack(size_t stackCapacity, int32_t **stackBottom) {
    int32_t *memory = NULL;
    int stackSize = (int) stackCapacity;
    size_t memorySize = 0;
    int counter = 0;
    while (stackSize > 0) {
        memorySize += 1024;
        int32_t *newMemory = realloc(memory, memorySize * sizeof (int32_t));
        if (newMemory == NULL) {
            free(memory);
            return NULL;
        }
        memory = newMemory;
        stackSize -= 1024;
        ++counter;
    }
    *stackBottom = (memory + (counter * 1024) - 1);
    return memory;
}

int32_t *cpuCreateMemory(FILE *program, size_t stackCapacity, int32_t **stackBottom) {
    assert(program != NULL);
    assert(stackBottom != NULL);
    static const int fourKB = 4096;
    size_t memorySize = 0;
    char *memory = NULL;
    int counter = 0;
    int byte = 0;
    while ((byte = fgetc(program)) != EOF) {
        if ((counter + (stackCapacity * sizeof (int32_t))) >= memorySize) { // needs more memory
            memorySize += fourKB;
            char *newMemory = realloc(memory, memorySize * sizeof (char));
            if (newMemory == NULL) {
                free(memory);
                return NULL;
            }
            memory = newMemory;
            memset(memory + memorySize - fourKB, '\0', fourKB);
        }
        memory[counter] = (char) byte;
        ++counter;
    }
    if (memory == NULL && stackCapacity != 0) { // allocating only stack
        return onlyStack(stackCapacity, stackBottom);
    }
    if (counter % sizeof (int32_t) != 0 || counter == 0) {
        free(memory);
        return NULL;
    }
    *stackBottom = ((int32_t*) (memory + memorySize)) - 1;
    return (int32_t*) memory;
}

void cpuCreate(struct cpu *cpu, int32_t *memory, int32_t *stackBottom, size_t stackCapacity) {
    assert(cpu != NULL);
    assert(memory != NULL);
    assert(stackBottom != NULL);
    memset(cpu, 0, sizeof (struct cpu));
    cpu->memory = memory;
    cpu->stackBottom = stackBottom;
    if (stackBottom - stackCapacity < memory) {
        cpu->stackLimit = memory;
    } else {
        cpu->stackLimit = stackBottom - stackCapacity;
    }
}

void cpuDestroy(struct cpu *cpu) {
    assert(cpu != NULL);
    free(cpu->memory);
    memset(cpu, 0, sizeof (struct cpu));
}

void cpuReset(struct cpu *cpu) {
    assert(cpu != NULL);
    cpu->A = 0;
    cpu->B = 0;
    cpu->C = 0;
    cpu->D = 0;
    cpu->instructionPointer = 0;
    cpu->status = (enum cpuStatus) 0;
    memset(cpu->stackLimit + 1, '\0', (size_t) (cpu->stackBottom - cpu->stackLimit) * sizeof(int32_t));
    cpu->stackLimit = cpu->stackBottom;
    cpu->stackSize = 0;
#ifdef BONUS_JMP
    cpu->result = 0;
#endif
}

int cpuStatus(struct cpu *cpu) {
    assert(cpu != NULL);
    return cpu->status;
}

int cpuStep(struct cpu *cpu) {
    assert(cpu != NULL);
    /* if instructionPointer points behind instruction memory or in front of it */
    if ((cpu->memory + cpu->instructionPointer) > cpu->stackLimit || cpu->instructionPointer < 0) {
        cpu->status = cpuInvalidAddress;
    }
    int32_t instructionCode = cpu->memory[cpu->instructionPointer];
    if (cpu->status != cpuOK) {
        return 0;
    }
#if defined(BONUS_JMP) && defined(BONUS_CALL)
    int numOfFuncs = 25;
#endif // both bonuses are defined
#if defined(BONUS_JMP) && !defined(BONUS_CALL)
    int numOfFuncs = 23;
#endif // only BONUS_JMP is defined
#if !defined(BONUS_JMP) && defined(BONUS_CALL)
    int numOfFuncs = 25;
#endif // only BONUS_CALL is defined
#if !defined(BONUS_JMP) && !defined(BONUS_CALL)
    int numOfFuncs = 18;
#endif // none is defined
    void (*fun_ptr[])(struct cpu*) = {cpuNop, cpuHalt, cpuAdd, cpuSub, cpuMul, cpuDiv, cpuInc, cpuDec,
            cpuLoop, cpuMovr, cpuLoad, cpuStore, cpuIn, cpuGet, cpuOut, cpuPut, cpuSwap, cpuPush, cpuPop
#if defined(BONUS_JMP) && !defined(BONUS_CALL)
    , cpuCmp, cpuJmp, cpuJz, cpuJnz, cpuJgt
#endif // only BONUS_JUMP is defined
#if !defined(BONUS_JMP) && defined(BONUS_CALL)
    , NULL, NULL, NULL, NULL, NULL, cpuCall, cpuRet
#endif // only BONUS_CALL is defined
#if defined(BONUS_JMP) && defined(BONUS_CALL)
    , cpuCmp, cpuJmp, cpuJz, cpuJnz, cpuJgt, cpuCall, cpuRet
#endif // both are defined
    };
    if (instructionCode > numOfFuncs || instructionCode < 0) { // unknown instruction code
        cpu->status = cpuIllegalInstruction;
        return 0;
    }
    /* a little workaround to be able to use an array of function
     * pointers when only the second bonus, BONUS_CALL, is defined */
#if !defined(BONUS_JMP) && defined(BONUS_CALL)
    if (*fun_ptr[instructionCode] == NULL) {
        cpu->status = cpuIllegalInstruction;
        return 0;
    }
#endif
    (*fun_ptr[instructionCode])(cpu); // executes the instruction
    if (cpu->status != cpuOK) { // instruction couldn't be executed
        return 0;
    }
    return 1;
}

int cpuRun(struct cpu *cpu, size_t steps) {
    assert(cpu != NULL);
    if (cpu->status != cpuOK) {
        return 0;
    }
    int index = 1;
    while (cpuStep(cpu) != 0) {
        if ((size_t) index == steps) {
            break;
        }
        ++index;
    }
    if (cpuStatus(cpu) != cpuHalted && cpuStatus(cpu) != cpuOK) { // cpu in an error state
        return -index;
    }
    return index;
}

int32_t cpuPeek(struct cpu *cpu, char reg) {
    assert(cpu != NULL);
    switch (reg) {
        case 'A':
            return cpu->A;
        case 'B':
            return cpu->B;
        case 'C':
            return cpu->C;
        case 'D':
            return cpu->D;
        case 'S':
            return cpu->stackSize;
        case 'I':
            return cpu->instructionPointer;
#ifdef BONUS_JMP
        case 'R':
            return cpu->result;
#endif
        default: // invalid register
            return 0;
    }
}
