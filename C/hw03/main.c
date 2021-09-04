#include "cpu.h"
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define invalidArgs "Invalid arguments, run ./cpu (run|trace) [stackCapacity] FILE\n"

const char *statusName(enum cpuStatus status)
{
    switch (status) {
    case cpuOK:
        return "cpuOK";
    case cpuHalted:
        return "cpuHalted";
    case cpuIllegalInstruction:
        return "cpuIllegalInstruction";
    case cpuIllegalOperand:
        return "cpuIllegalOperand";
    case cpuInvalidAddress:
        return "cpuInvalidAddress";
    case cpuInvalidStackOperation:
        return "cpuInvalidStackOperation";
    case cpuDivByZero:
        return "cpuDivByZero";
    case cpuIOError:
        return "cpuIOError";
    default:
        fprintf(stderr, "BUG: Unknown status (%d)\n", status);
        abort();
    }
    printf("\n");
}

static void state(struct cpu *cpu)
{
    printf("A: %d, B: %d, C: %d, D: %d\n", cpu->A, cpu->B, cpu->C, cpu->D);

    printf("Stack size: %d\n", cpu->stackSize);
    printf("Stack:");
    for (int i = 0; i < cpu->stackSize; i++) {
        printf(" %d", cpu->stackBottom[-i]);
    }
    printf("\n");
#ifdef BONUS_JMP
    printf("Result: %d\n", cpu->result);
#endif
    printf("Status: %s\n", statusName(cpu->status));
}

int main(int argc, char *argv[])
{
    if (argc > 4 || argc < 3) {
        printf(invalidArgs);
        return 1;
    }

    size_t stackCapacity = 256;
    if (argc == 4) {
        char *end;
        stackCapacity = (size_t) strtol(argv[2], &end, 10);
        if (*end != '\0') {
            printf("Invalid stack capacity\n");
            return 1;
        }
        if (errno == ERANGE) {
            printf("Stack capacity out of range\n");
            return 1;
        }
    }

    FILE *fptr = NULL;
    if ((fptr = fopen(argv[argc - 1], "rb")) == NULL) {
        perror(argv[argc - 1]);
        return 1;
    }
    int32_t *stackPtr = 0;
    // int count = 0; //to be deleted
    int32_t *memory = cpuCreateMemory(fptr, stackCapacity, &stackPtr);
    struct cpu cp = {0};
    // int counter = 0;
    cpuCreate(&cp, memory, stackPtr, stackCapacity);
    // showCpuMemory(&cp, count);
    // printf("read %d ints\n", count);
    if (strcmp(argv[1], "run") == 0) {
        //printf("argument is run\n");
        cpuRun(&cp, UINT_MAX);
        // cpuReset(&cp);
        state(&cp);
        printf("Instruction pointer: %d\n", cp.instructionPointer);

    } else if (strcmp(argv[1], "trace") == 0) {
        printf("Press Enter to execute the next instruction or type 'q' to quit.\n");
        while (true) {
            int c = 0;
            if ((c = getchar()) == '\n') {
                if (cpuStep(&cp) == 0) {
                    state(&cp);
                    printf("finished\n");
                    break;
                }
                state(&cp);
                printf("Instruction pointer: %d\n", cp.instructionPointer);
            } else if (c == 'q') {
                break;
            }
        }
        printf("Instruction pointer: %d\n", cp.instructionPointer);
    } else {
        printf(invalidArgs);
    }
    // printf("finished with: %d\n", counter);
    fclose(fptr);
    cpuDestroy(&cp);
    return 0;
}
