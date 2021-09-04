/** @A **/

#include <cstdint>
#include <unordered_map>
#include <vector>

constexpr int INSTRUCTION_SIZE = 4 * sizeof(int32_t); // instruction size in bytes


/* In this task, you will implement a simple register machine (i.e.
 * a simple model of a computer). The machine has an arbitrary
 * number of integer registers and byte-addressed memory. Registers
 * are indexed from 1 to ‹INT_MAX›. Each instruction takes 2
 * register numbers (indices) and an ‘immediate’ value (an integral
 * constant). Each register can hold a single value of type
 * ‹int32_t› (i.e. the size of the machine word is 4 bytes).  In
 * memory, words are stored LSB-first. The entire memory and all
 * registers start out as 0.
 *
 * The machine has the following instructions (whenever ‹reg_x› is
 * used in the «description», it means the «value» stored in ‹reg_x›,
 * not the index of the register itself; unlike the column ‹reg_2›
 * which refers to the register index):
 *
 *  │ opcode │‹reg_2›│ description                                 │
 *  ├────────┼───────┼─────────────────────────────────────────────┤
 *  │ ‹mov›  │  ≥ 1  │ copy a value from ‹reg_2› to ‹reg_1›        │
 *  │        │  = 0  │ set_word ‹reg_1› to ‹immediate›             │
 *  │ ‹add›  │  ≥ 1  │ store ‹reg_1 + reg_2› in ‹reg_1›            │
 *  │        │  = 0  │ add ‹immediate› to ‹reg_1›                  │
 *  │ ‹mul›  │  ≥ 1  │ store ‹reg_1 * reg_2› in ‹reg_1›            │
 *  │ ‹jmp›  │  = 0  │ jump to the address stored in ‹reg_1›       │
 *  │ ‹jnz›  │  ≥ 1  │ jump to ‹reg_1› if ‹reg_2› is nonzero       │
 *  │ ‹load› │  ≥ 1  │ copy value from addr. ‹reg_2› into ‹reg_1›  │
 *  │ ‹stor› │  ≥ 1  │ copy ‹reg_1› to memory address ‹reg_2›      │
 *  │ ‹hlt›  │  = 0  │ halt the machine with result ‹reg_1›        │
 *
 * Each instruction is stored in memory as 4 words (addresses
 * increase from left to right). Executing a non-jump instruction
 * increments the program counter by 4 words.
 *
 *  ┌────────┬───────┬───────┬───────────┐
 *  │ opcode │ reg_1 │ reg_2 │ immediate │
 *  └────────┴───────┴───────┴───────────┘
 */

enum class opcode {
    mov, add, mul, jmp, jnz, load, stor, hlt
};

class machine_memory {
private:
    std::vector<uint8_t> memory;
public:
    int32_t get_word(int32_t addr) const;

    void set_word(int32_t addr, int32_t v);

    std::tuple<opcode, int32_t, int32_t, int32_t> get_instruction(int32_t addr) const;
};

class machine {
private:
    int mem_ptr = 0;
    machine_memory memory;
    std::unordered_map<unsigned int, int32_t> registers;

    void op_mov(unsigned int reg1, unsigned int reg2, int immediate);

    void op_add(unsigned int reg1, unsigned int reg2, int immediate);

    void op_mul(unsigned int reg1, unsigned int reg2);

    bool op_jmp(unsigned int reg1, unsigned int reg2);

    bool op_jnz(unsigned int reg1, unsigned int reg2);

    void op_load(unsigned int reg1, unsigned int reg2);

    void op_stor(unsigned int reg1, unsigned int reg2);

public:
    /* Read and write memory, one word at a time. */
    int32_t get(int32_t addr) const;

    void set(int32_t addr, int32_t v);

    /* Start executing the program, starting from address zero.
     * Return the value of ‹reg_1› given to the ‹hlt› instruction
     * which halted the computation. */
    int32_t run();
};
