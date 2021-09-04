#include <vector>
#include <string>
#include <cassert>
#include <sstream>

/* Write a simple parser for an assembly-like language with one
 * instruction per line (each taking 2 operands, separated by
 * spaces, where the first is always a register and the second is
 * either a register or an ‘immediate’ number).
 *
 * The opcodes (instructions) are: ‹add›, ‹mul›, ‹jnz›, the
 * registers are ‹rax›, ‹rbx› and ‹rcx›. The result is a vector of
 * ‹instruction› instances (see below). Set ‹r_2› to
 * ‹reg::immediate› if the second operand is a number.
 *
 * If the input does not conform to the expected format, throw
 * ‹no_parse›, which includes a line number with the first erroneous
 * instruction and the kind of error (see ‹enum error›), as public
 * attributes ‹line› and ‹type›, respectively. If multiple errors
 * appear on the same line, give the one that comes first in the
 * definition of ‹error›. You can add attributes or methods to the
 * structures below, but do not change the enumerations. */

enum class opcode { add, mul, jnz };
enum class reg { rax, rbx, rcx, immediate };
enum class error { bad_opcode, bad_register, bad_immediate,
                   bad_structure };

struct instruction
{
    opcode op;
    reg r_1, r_2;
    int32_t immediate;
};

struct no_parse
{
    int line;
    error type;
};

opcode parse_op(const std::string &in) {
    if (in == "add") {
        return opcode::add;
    }
    if (in == "mul") {
        return opcode::mul;
    }
    if (in == "jnz") {
        return opcode::jnz;
    }
    throw no_parse{0, error::bad_opcode};
}

reg parse_reg(const std::string &in) {
    if (in == "rax") {
        return reg::rax;
    }
    if (in == "rbx") {
        return reg::rbx;
    }
    if (in == "rcx") {
        return reg::rcx;
    }
    throw no_parse{0, error::bad_register};
}

reg parse_reg_or_immediate(const std::string &in) {
    try {
        return parse_reg(in);
    } catch (no_parse &ex) {}
    size_t pos = 0;
    try {
        std::stoi(in, &pos);
    } catch (...) {
        throw no_parse{0, error::bad_register};
    }
    if (pos != in.length()) {
        throw no_parse{0, error::bad_immediate};
    }
    return reg::immediate;
}

instruction parse_line(const std::string &line) {
    instruction i{};
    std::istringstream in(line);
    std::string w;
    in >> w;
    try {
        i.op = parse_op(w);
        in >> w;
        i.r_1 = parse_reg(w);
        in >> w;
        i.r_2 = parse_reg_or_immediate(w);
    } catch (no_parse &ex) {
        throw;
    }
    if (i.r_2 == reg::immediate) {
        i.immediate = std::stoi(w);
    }
    if (in.rdbuf()->in_avail() > 0) {
        throw no_parse{0, error::bad_structure};
    }
    return i;
}

std::vector<instruction> parse(const std::string &input) {
    std::vector<instruction> output;
    std::istringstream is(input);
    std::string line;
    int line_count = 0;
    while (std::getline(is, line)) {
        line_count++;
        try {
            output.emplace_back(parse_line(line));
        } catch (no_parse &ex) {
            throw no_parse{line_count, ex.type};
        }
    }
    return output;
}

#include <iostream>

int main()
{
    try {
        auto p_1 = parse( "add rax 7\n"
                          "mul rax  rbx\n" );
    assert( p_1[ 0 ].op  == opcode::add );
    assert( p_1[ 0 ].r_1 == reg::rax );
    assert( p_1[ 0 ].r_2 == reg::immediate );
    assert( p_1[ 1 ].op  == opcode::mul );
    assert( p_1[ 1 ].r_2 == reg::rbx );

    }
    catch ( no_parse np )
    {
        std::cerr << np.line << " " << int( np.type ) << std::endl;
    }

    try
    {
        parse( "add rax 7\n"
               "mul rax  rbx\n"
               "mul rax rrx\n" );
        assert( false );
    }
    catch ( const no_parse &np )
    {
        assert( np.line == 3 );
        assert( np.type == error::bad_register );
    }

    try
    {
        parse( "add rax 7\n"
               "mul rax rax rbx\n"
               "mul rax rrx\n" );
        assert( false );
    }
    catch ( const no_parse &np )
    {
        assert( np.line == 2 );
        assert( np.type == error::bad_structure );
    }

    try
    {
        parse( "add rax 7z\n" );
        assert( false );
    }
    catch ( const no_parse &np )
    {
        assert( np.line == 1 );
        assert( np.type == error::bad_immediate );
    }

    try
    {
        parse( "add rax 7\n"
               "hlt rax 7z\n"
               "add rax rox\n" );
        assert( false );
    }
    catch ( const no_parse &np )
    {
        assert( np.line == 2 );
        assert( np.type == error::bad_opcode );
    }

    try
    {
        parse( "add 7 rax\n" );
        assert( false );
    }
    catch ( const no_parse &np )
    {
        assert( np.line == 1 );
        assert( np.type == error::bad_register );
    }
}
