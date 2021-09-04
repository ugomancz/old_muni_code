#include <cassert>
#include <iostream>
#include "machine.hpp"


int32_t machine_memory::get_word(int32_t addr) const {
    assert(addr >= 0);
    int32_t result = 0;
    /** dávalo by trochu větší smysl číst to zleva… ale je to skoro jedno **/
    for (size_t i : {3, 2, 1, 0}) {
        if (static_cast<size_t>(addr) + i >= memory.size()) { // emulating "uninitialized memory contains 0"
            continue;
        }
        result |= (memory[addr + i] << (i * 8));
    }
    return result;
}

void machine_memory::set_word(int32_t addr, int32_t v) {
    assert(addr >= 0);
    if (memory.size() <= static_cast<size_t>(addr) + 3) {
        memory.resize(addr + 4);
    }
    memory[addr] = v;
    memory[addr + 1] = v >> 8;
    memory[addr + 2] = v >> 16;
    memory[addr + 3] = v >> 24;
}

std::tuple<opcode, int32_t, int32_t, int32_t> machine_memory::get_instruction(int32_t addr) const {
    assert(addr >= 0);
    return {static_cast<opcode>(get_word(addr)), get_word(addr + INSTRUCTION_SIZE / 4),
            get_word(addr + INSTRUCTION_SIZE / 2), get_word(addr + INSTRUCTION_SIZE * 3 / 4)};
}


int32_t machine::get(const int32_t addr) const {
    return memory.get_word(addr);
}

void machine::set(const int32_t addr, const int32_t v) {
    memory.set_word(addr, v);
}

int32_t machine::run() {
    while (true) {
        const auto[op, reg1, reg2, im] = memory.get_instruction(mem_ptr);
        switch (op) {
            case opcode::mov:
                op_mov(reg1, reg2, im);
                break;
            case opcode::add:
                op_add(reg1, reg2, im);
                break;
            case opcode::mul:
                op_mul(reg1, reg2);
                break;
            case opcode::jmp:
                if (op_jmp(reg1, reg2)) {
                    continue;
                }
                break;
            case opcode::jnz:
                if (op_jnz(reg1, reg2)) {
                    continue;
                }
                break;
            case opcode::load:
                op_load(reg1, reg2);
                break;
            case opcode::stor:
                op_stor(reg1, reg2);
                break;
            case opcode::hlt:
                return registers[reg1];
        }
        mem_ptr += INSTRUCTION_SIZE;
    }
}

void machine::op_mov(const unsigned int reg1, const unsigned int reg2, const int immediate) {
    if (reg2 == 0) {
        registers[reg1] = immediate;
    } else {
        registers[reg1] = registers[reg2];
    }
}

void machine::op_add(const unsigned int reg1, const unsigned int reg2, const int immediate) {
    if (reg2 == 0) {
        registers[reg1] += immediate;
    } else {
        registers[reg1] += registers[reg2];
    }
}

void machine::op_mul(const unsigned int reg1, const unsigned int reg2) {
    if (reg2 >= 1) {
        registers[reg1] *= registers[reg2];
    }
}

bool machine::op_jmp(const unsigned int reg1, const unsigned int reg2) {
    if (reg2 == 0) {
        mem_ptr = registers[reg1];
        return true;
    }
    return false;
}

bool machine::op_jnz(const unsigned int reg1, const unsigned int reg2) {
    if (reg2 >= 1 && registers[reg2] != 0) {
        mem_ptr = registers[reg1];
        return true;
    }
    return false;
}

void machine::op_load(const unsigned int reg1, const unsigned int reg2) {
    if (reg2 >= 1) {
        registers[reg1] = memory.get_word(registers[reg2]);
    }
}

void machine::op_stor(const unsigned int reg1, const unsigned int reg2) {
    if (reg2 >= 1) {
        memory.set_word(registers[reg2], registers[reg1]);
    }
}

int main() {
    /* tests go here */
}
