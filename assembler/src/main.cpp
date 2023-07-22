#include <iostream>
#include <fstream>
#include <cstdint>
#include <unordered_map>

namespace fab8{
    std::ifstream assembly_code_file;
    std::ofstream machine_code_file;

    std::string substring;
    bool is_two_byte;

    enum addresing_mode{IMP, IMM, DIR, DIRX, DIRY, PREI, POSI, ABS, ABSX, ABSY};
    std::unordered_map<std::string, std::unordered_map<addresing_mode, uint8_t>> instructions;

    void init_instructions(){
        instructions["nop"][IMP] = 0x00;
        instructions["stop"][IMP] = 0x01;

        instructions["lda"][IMM] = 0x02;
        instructions["lda"][DIR] = 0x03;
        instructions["lda"][DIRX] = 0x04;
        instructions["lda"][DIRY] = 0x05;
        instructions["lda"][PREI] = 0x06;
        instructions["lda"][POSI] = 0x07;
        instructions["lda"][ABS] = 0x08;
        instructions["lda"][ABSX] = 0x09;
        instructions["lda"][ABSY] = 0x0a;

        instructions["ldx"][IMM] = 0x0b;
        instructions["ldx"][DIR] = 0x0c;
        instructions["ldx"][DIRY] = 0x0d;
        instructions["ldx"][POSI] = 0x0e;
        instructions["ldx"][ABS] = 0x0f;
        instructions["ldx"][ABSY] = 0x10;

        instructions["ldy"][IMM] = 0x11;
        instructions["ldy"][DIR] = 0x12;
        instructions["ldy"][DIRX] = 0x13;
        instructions["ldy"][PREI] = 0x14;
        instructions["ldy"][ABS] = 0x15;
        instructions["ldy"][ABSX] = 0x16;

        instructions["ldf"][IMM] = 0x17;

        instructions["sta"][DIR] = 0x18;
        instructions["sta"][DIRX] = 0x19;
        instructions["sta"][DIRY] = 0x1a;
        instructions["sta"][PREI] = 0x1b;
        instructions["sta"][POSI] = 0x1c;
        instructions["sta"][ABS] = 0x1d;
        instructions["sta"][ABSX] = 0x1e;
        instructions["sta"][ABSY] = 0x1f;

        instructions["stx"][DIR] = 0x20;
        instructions["stx"][DIRY] = 0x21;
        instructions["stx"][POSI] = 0x22;
        instructions["stx"][ABS] = 0x23;
        instructions["stx"][ABSY] = 0x24;

        instructions["sty"][DIR] = 0x25;
        instructions["sty"][DIRX] = 0x26;
        instructions["sty"][PREI] = 0x27;
        instructions["sty"][ABS] = 0x28;
        instructions["sty"][ABSX] = 0x29;

        instructions["tax"][IMP] = 0x2a;
        instructions["tay"][IMP] = 0x2b;
        instructions["txa"][IMP] = 0x2c;
        instructions["txy"][IMP] = 0x2d;
        instructions["txsp"][IMP] = 0x2e;
        instructions["txss"][IMP] = 0x2f;
        instructions["tya"][IMP] = 0x30;
        instructions["tyx"][IMP] = 0x31;
        instructions["tyds"][IMP] = 0x32;
        instructions["tyes"][IMP] = 0x33;
        instructions["tspx"][IMP] = 0x34;
        instructions["tssx"][IMP] = 0x35;
        instructions["tdsy"][IMP] = 0x36;
        instructions["tesy"][IMP] = 0x37;

        instructions["ina"][IMP] = 0x38;
        instructions["inx"][IMP] = 0x39;
        instructions["iny"][IMP] = 0x3a;
        instructions["inc"][DIR] = 0x3b;
        instructions["inc"][DIRX] = 0x3c;
        instructions["inc"][ABS] = 0x3d;
        instructions["inc"][ABSY] = 0x3e;

        instructions["dea"][IMP] = 0x3f;
        instructions["dex"][IMP] = 0x40;
        instructions["dey"][IMP] = 0x41;
        instructions["dec"][DIR] = 0x42;
        instructions["dec"][DIRX] = 0x43;
        instructions["dec"][ABS] = 0x44;
        instructions["dec"][ABSY] = 0x45;

        instructions["adc"][IMM] = 0x46;
        instructions["adc"][DIR] = 0x47;
        instructions["adc"][DIRX] = 0x48;
        instructions["adc"][DIRY] = 0x49;
        instructions["adc"][PREI] = 0x4a;
        instructions["adc"][POSI] = 0x4b;
        instructions["adc"][ABS] = 0x4c;
        instructions["adc"][ABSX] = 0x4d;
        instructions["adc"][ABSY] = 0x4e;

        instructions["sbb"][IMM] = 0x4f;
        instructions["sbb"][DIR] = 0x50;
        instructions["sbb"][DIRX] = 0x51;
        instructions["sbb"][DIRY] = 0x52;
        instructions["sbb"][PREI] = 0x53;
        instructions["sbb"][POSI] = 0x54;
        instructions["sbb"][ABS] = 0x55;
        instructions["sbb"][ABSX] = 0x56;
        instructions["sbb"][ABSY] = 0x57;

        instructions["mul"][IMM] = 0x58;
        instructions["mul"][DIR] = 0x59;
        instructions["mul"][DIRX] = 0x5a;
        instructions["mul"][ABS] = 0x5b;
        instructions["mul"][ABSX] = 0x5c;

        instructions["div"][IMM] = 0x5d;
        instructions["div"][DIR] = 0x5e;
        instructions["div"][DIRX] = 0x5f;
        instructions["div"][ABS] = 0x60;
        instructions["div"][ABSX] = 0x61;

        instructions["mod"][IMM] = 0x62;
        instructions["mod"][DIR] = 0x63;
        instructions["mod"][DIRX] = 0x64;
        instructions["mod"][ABS] = 0x65;
        instructions["mod"][ABSX] = 0x66;

        instructions["_and"][IMM] = 0x67;
        instructions["_and"][DIR] = 0x68;
        instructions["_and"][DIRX] = 0x69;
        instructions["_and"][DIRY] = 0x6a;
        instructions["_and"][PREI] = 0x6b;
        instructions["_and"][POSI] = 0x6c;
        instructions["_and"][ABS] = 0x6d;
        instructions["_and"][ABSX] = 0x6e;
        instructions["_and"][ABSY] = 0x6f;

        instructions["_or"][IMM] = 0x70;
        instructions["_or"][DIR] = 0x71;
        instructions["_or"][DIRX] = 0x72;
        instructions["_or"][DIRY] = 0x73;
        instructions["_or"][PREI] = 0x74;
        instructions["_or"][POSI] = 0x75;
        instructions["_or"][ABS] = 0x76;
        instructions["_or"][ABSX] = 0x77;
        instructions["_or"][ABSY] = 0x78;
        instructions["_xor"][IMM] = 0x79;
        instructions["_xor"][DIR] = 0x7a;
        instructions["_xor"][DIRX] = 0x7b;
        instructions["_xor"][DIRY] = 0x7c;
        instructions["_xor"][PREI] = 0x7d;
        instructions["_xor"][POSI] = 0x7e;
        instructions["_xor"][ABS] = 0x7f;
        instructions["_xor"][ABSX] = 0x80;
        instructions["_xor"][ABSY] = 0x81;

        instructions["shla"][IMP] = 0x82;
        instructions["shl"][DIR] = 0x83;
        instructions["shl"][DIRX] = 0x84;
        instructions["shl"][ABS] = 0x85;
        instructions["shl"][ABSX] = 0x86;

        instructions["shra"][IMP] = 0x87;
        instructions["shr"][DIR] = 0x88;
        instructions["shr"][DIRX] = 0x89;
        instructions["shr"][ABS] = 0x8a;
        instructions["shr"][ABSX] = 0x8b;

        instructions["rola"][IMP] = 0x8c;
        instructions["rol"][DIR] = 0x8d;
        instructions["rol"][DIRX] = 0x8e;
        instructions["rol"][ABS] = 0x8f;
        instructions["rol"][ABSX] = 0x90;

        instructions["rora"][IMP] = 0x91;
        instructions["ror"][DIR] = 0x92;
        instructions["ror"][DIRX] = 0x93;
        instructions["ror"][ABS] = 0x94;
        instructions["ror"][ABSX] = 0x95;

        instructions["cmp"][IMM] = 0x96;
        instructions["cmp"][DIR] = 0x97;
        instructions["cmp"][DIRX] = 0x98;
        instructions["cmp"][DIRY] = 0x99;
        instructions["cmp"][PREI] = 0x9a;
        instructions["cmp"][POSI] = 0x9b;
        instructions["cmp"][ABS] = 0x9c;
        instructions["cmp"][ABSX] = 0x9d;
        instructions["cmp"][ABSY] = 0x9e;

        instructions["cpx"][IMM] = 0x9f;
        instructions["cpx"][DIR] = 0xa0;
        instructions["cpx"][DIRY] = 0xa1;
        instructions["cpx"][ABS] = 0xa2;
        instructions["cpx"][ABSY] = 0xa3;

        instructions["cpy"][IMM] = 0xa4;
        instructions["cpy"][DIR] = 0xa5;
        instructions["cpy"][DIRX] = 0xa6;
        instructions["cpy"][ABS] = 0xa7;
        instructions["cpy"][ABSX] = 0xa8;

        instructions["jmp"][ABS] = 0xa9;
        instructions["jc"][ABS] = 0xaa;
        instructions["jnc"][ABS] = 0xab;
        instructions["je"][ABS] = 0xac;
        instructions["jne"][ABS] = 0xad;
        instructions["js"][ABS] = 0xae;
        instructions["jns"][ABS] = 0xaf;
        instructions["jo"][ABS] = 0xb0;
        instructions["jno"][ABS] = 0xb1;
        instructions["ja"][ABS] = 0xb2;
        instructions["jna"][ABS] = 0xb3;
        instructions["jl"][ABS] = 0xb4;
        instructions["jge"][ABS] = 0xb5;
        instructions["jg"][ABS] = 0xb6;
        instructions["jng"][ABS] = 0xb7;

        instructions["loop"][ABS] = 0xb8;

        instructions["call"][ABS] = 0xb9;
        instructions["ret"][IMP] = 0xba;

        instructions["clc"][IMP] = 0xbb;
        instructions["clz"][IMP] = 0xbc;
        instructions["cls"][IMP] = 0xbd;
        instructions["clo"][IMP] = 0xbe;
        instructions["cld"][IMP] = 0xbf;

        instructions["sec"][IMP] = 0xc0;
        instructions["sez"][IMP] = 0xc1;
        instructions["ses"][IMP] = 0xc2;
        instructions["seo"][IMP] = 0xc3;
        instructions["sed"][IMP] = 0xc4;

        instructions["pusha"][IMP] = 0xc5;
        instructions["pushx"][IMP] = 0xc6;
        instructions["pushy"][IMP] = 0xc7;
        instructions["pushf"][IMP] = 0xc8;
        instructions["pushall"][IMP] = 0xc9;
        instructions["push"][IMM] = 0xca;

        instructions["popa"][IMP] = 0xcb;
        instructions["popx"][IMP] = 0xcc;
        instructions["popy"][IMP] = 0xcd;
        instructions["popf"][IMP] = 0xce;
        instructions["popall"][IMP] = 0xcf;
        instructions["pop"][DIR] = 0xd0;
        instructions["pop"][ABS] = 0xd1;

        instructions["lods"][IMP] = 0xd2;
        instructions["stos"][IMP] = 0xd3;
        instructions["movs"][IMP] = 0xd4;

        instructions["intr"][IMM] = 0xd5;
    }

    bool is_one_byte(std::string mnemonic){
        if(instructions[mnemonic].find(IMP) != instructions[mnemonic].end()) return true;
        return false;
    }

    void print_value_from_argument(std::string sub_arg, bool is_two_byte){
        uint16_t value = stoul(sub_arg, nullptr, 0);
        if(is_two_byte){
            char temp_low, temp_high;
            temp_low = (uint8_t)value;
            machine_code_file.write(&temp_low, 1);

            temp_high = value >> 8;
            machine_code_file.write(&temp_high, 1);
        }
        else{
            char temp = (uint8_t)value;
            machine_code_file.write(&temp, 1);
        }
    }

    addresing_mode get_addresing_mode(std::string argument){
        if(argument.find("[[") == 0 && argument.rfind("+x]]") == argument.size() - 4) return PREI;
        if(argument.find("[[") == 0 && argument.rfind("]+y]") == argument.size() - 4) return POSI;
        if(argument.find("[@") == 0 && argument.rfind("+x]") == argument.size() - 3){
            substring = argument.substr(2, argument.find("+x]") - 1);
            is_two_byte = true;
            return ABSX;
        }
        if(argument.find("[@") == 0 && argument.rfind("+y]") == argument.size() - 3){
            substring = argument.substr(2, argument.find("+y]") - 1);
            is_two_byte = true;
            return ABSY;
        }
        if(argument.find("[") == 0 && argument.rfind("+x]") == argument.size() - 3){
            substring = argument.substr(1, argument.find("+x]") - 1);
            is_two_byte = false;
            return DIRX;
        }
        if(argument.find("[") == 0 && argument.rfind("+y]") == argument.size() - 3){
            substring = argument.substr(1, argument.find("+y]") - 1);
            is_two_byte = false;
            return DIRY;
        }
        if(argument.find("[@") == 0 && argument.rfind("]") == argument.size() - 1){
            substring = argument.substr(2, argument.find("]") - 1);
            is_two_byte = true;
            return ABS;
        }
        if(argument.find("[") == 0 && argument.rfind("]") == argument.size() - 1){
            substring = argument.substr(1, argument.find("]") - 1);
            is_two_byte = false;
            return DIR;
        }

        substring = argument;
        is_two_byte = false;
        return IMM;
    }
}

using namespace fab8;
int main()
{
    assembly_code_file.open("code.faba");
    machine_code_file.open("code.bin", std::ofstream::binary);
    
    init_instructions();

    std::string mnemonic;
    addresing_mode addrm;

    while(!assembly_code_file.eof()){
        assembly_code_file >> mnemonic;
        if(is_one_byte(mnemonic)){
            addrm = IMP;
            //printf("%x ", instructions[mnemonic][addrm]);
            char temp = instructions[mnemonic][addrm];
            machine_code_file.write(&temp, 1);
        }
        else
        {
            std::string argument;
            assembly_code_file >> argument;
            addrm = get_addresing_mode(argument);
            char temp = instructions[mnemonic][addrm];
            machine_code_file.write(&temp, 1);

            print_value_from_argument(substring, is_two_byte);
        }
    }

    assembly_code_file.close();
    machine_code_file.close();
}

