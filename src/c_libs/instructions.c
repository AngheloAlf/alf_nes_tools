//
// Created by anghelo on 23-02-18.
//

#include "instructions.h"

struct instruction* initInstruction(unsigned char opcode, unsigned char bytesAmount, unsigned char byte1, unsigned char byte2, unsigned char type, void (*execute)(struct instruction*, struct nesRegisters*, struct nesRam*)){
    struct instruction** instData = malloc(sizeof(struct instruction*));
    *instData = malloc(sizeof(struct instruction));

    (*instData)->opcode = opcode;
    (*instData)->byte1 = 0;
    (*instData)->byte2 = 0;
    if(bytesAmount > 0){
        (*instData)->byte1 = byte1;
    }
    if(bytesAmount > 1){
        (*instData)->byte2 = byte2;
    }
    (*instData)->bytesAmount = bytesAmount;
    (*instData)->type = type;

    (*instData)->execute = execute;

    return (*instData);
}

struct instruction* NOP_Opcodes(unsigned char* inst){
    struct instruction* instData = NULL;
    unsigned char opcode = inst[0];

    if(opcode == 0xEA){
        // NOP (No OPeration)
        //   Affects Flags: none
        // NOP is used to reserve space for future modifications or effectively REM
        // out existing code.
        printf("\tofficial NOP\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, opcode_EA); // Implied       NOP           $EA  1   2
    }

    else if((opcode & 0b11) == 0b00){
        // Control opcode NOP
        if(opcode == 0x80){
            printf("\tIMMEDIATE NOP\n");
            instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_IMMEDIATE, opcode_80);
        }
        else if(((opcode & 0b10011111) == 0b00000100) && ((opcode & 0b01000000) | ~(opcode & 0b00100000))){
            printf("\tZERO PAGE NOP\n");
            if(opcode == 0x04){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_04);
            }
            else if(opcode == 0x44){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_44);
            }
            else if(opcode == 0x64){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_64);
            }
            else{
                printf("\tINVALID ZERO PAGE NOP\n");
            }
        }
        else if(opcode == 0x0C){
            printf("\tABSOLUTE NOP\n");
            instData = initInstruction(opcode, 2, inst[1], inst[2], TYPE_ABSOLUTE, opcode_0C);
        }
        else if(((opcode & 0b00011111) == 0b00010100) && (~(opcode & 0b10000000) | (opcode & 0b01000000))){
            printf("\tZERO PAGE X NOP\n");
            if(opcode == 0x14){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_14);
            }
            else if(opcode == 0x34){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_34);
            }
            else if(opcode == 0x54){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_54);
            }
            else if(opcode == 0x74){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_74);
            }
            else if(opcode == 0xD4){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_D4);
            }
            else if(opcode == 0xF4){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_F4);
            }
            else{
                printf("\tINVALID ZERO PAGE X NOP\n");
            }
        }
        else if(((opcode & 0b00011111) == 0b00011100) && (~(opcode & 0b10000000) | (opcode & 0b01000000))){
            printf("\tABSOLUTE X NOP\n");
            if(opcode == 0x1C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_1C);
            }
            else if(opcode == 0x3C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_3C);
            }
            else if(opcode == 0x5C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_5C);
            }
            else if(opcode == 0x7C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_7C);
            }
            else if(opcode == 0xDC){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_DC);
            }
            else if(opcode == 0xFC){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_FC);
            }
            else{
                printf("\tABSOLUTE X NOP\n");
            }
        }
        else{
            printf("\tINVALID CONTROL NOP\n");
            instData = NULL;
        }
    }

    else{
        // printf("\tINVALID NOP\n");
        instData = NULL;
    }

    return instData;
}

struct instruction* control_STACK_Opcodes(unsigned char* inst){
    // Stack Instructions
    // These instructions are implied mode, have a length of one byte and require
    // machine cycles as indicated. The "PuLl" operations are known as "POP" on most
    // other microprocessors. With the 6502, the stack is always on page one
    // ($100-$1FF) and works top down. 
    // MNEMONIC                        HEX TIM
    // PHP (PusH Processor status)     $08  3
    // PLP (PuLl Processor status)     $28  4
    // PHA (PusH Accumulator)          $48  3
    // PLA (PuLl Accumulator)          $68  4
    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x08:
            printf("\tPHP (PusH Processor status)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_08);
            break;
        case 0x28:
            printf("\tPLP (PuLl Processor status)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_28);
            break;
        case 0x48:
            printf("\tPHA (PusH Accumulator)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_48);
            break;
        case 0x68:
            printf("\tPLA (PuLl Accumulator)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_68);
            break;
        default:
            printf("\tINVALID CONTROL STACK\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_Branching_Opcodes(unsigned char* inst){
    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x10:
            printf("\tBranch on PLus\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_10);
            break;
        case 0x30:
            printf("\tBranch on MInus\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_30);
            break;
        case 0x50:
            printf("\tBranch on oVerflow Clear\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_50);
            break;
        case 0x70:
            printf("\tBranch on oVerflow Set\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_70);
            break;
        case 0x90:
            printf("\tBranch on Carry Clear\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_90);
            break;
        case 0xB0:
            printf("\tBranch on Carry Set\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_B0);
            break;
        case 0xD0:
            printf("\tBranch on Not Equal\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_D0);
            break;
        case 0xF0:
            printf("\tBranch on EQual\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_BRANCH, opcode_F0);
            break;
        default:
            printf("\tINVALID BRANCH\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_Flag_Opcodes(unsigned char* inst){
    // Flag (Processor Status) Instructions
    //   Affect Flags: as noted
    // These instructions are implied mode, have a length of one byte and require
    // two machine cycles.

    // Notes:
        // <p><a name="IFLAG">&nbsp;</a> The Interrupt flag is used to prevent (SEI) or
        // enable (CLI) maskable interrupts (aka IRQ's). It does not signal the presence or
        // absence of an interrupt condition. The 6502 will set this flag automatically in
        // response to an interrupt and restore it to its prior status on completion of the
        // interrupt service routine. If you want your interrupt service routine to permit
        // other maskable interrupts, you must clear the I flag in your code.
        // </p><p><a name="DFLAG">&nbsp;</a> The Decimal flag controls how the 6502 adds and
        // subtracts. If set, arithmetic is carried out in packed binary coded decimal.
        // This flag is unchanged by interrupts and is unknown on power-up. The implication
        // is that a CLD should be included in boot or interrupt coding.
        // </p><p><a name="VFLAG">&nbsp;</a> The Overflow flag is generally misunderstood and
        // therefore under-utilised. After an ADC or SBC instruction, the overflow flag
        // will be set if the twos complement result is less than -128 or greater than
        // +127, and it will cleared otherwise. In twos complement, $80 through $FF
        // represents -128 through -1, and $00 through $7F represents 0 through +127.
        // Thus, after:
        // </p><pre>  CLC
        //   LDA #$7F ;   +127
        //   ADC #$01 ; +   +1
        // </pre>
        // the overflow flag is 1 (+127 + +1 = +128), and after:
        // <pre>  CLC
        //   LDA #$81 ;   -127
        //   ADC #$FF ; +   -1
        // </pre>
        // the overflow flag is 0 (-127 + -1 = -128). The overflow flag is not
        // affected by increments, decrements, shifts and logical operations i.e. only
        // ADC, BIT, CLV, PLP, RTI and SBC affect it. There is no op code to set the
        // overflow but a BIT test on an RTS instruction will do the trick.

    /*
    CLC (CLear Carry)              $18
    SEC (SEt Carry)                $38
    CLI (CLear Interrupt)          $58
    SEI (SEt Interrupt)            $78
    CLV (CLear oVerflow)           $B8
    CLD (CLear Decimal)            $D8
    SED (SEt Decimal)              $F8
    */

    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x18:
            printf("\tCLear Carry\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_18);
            break;
        case 0x38:
            printf("\tSEt Carry\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_38);
            break;
        case 0x58:
            printf("\tCLear Interrupt\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_58);
            break;
        case 0x78:
            printf("\tSEt Interrupt\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_78);
            break;
        case 0xB8:
            printf("\tCLear oVerflow\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_B8);
            break;
        case 0xD8:
            printf("\tCLear Decimal\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_D8);
            break;
        case 0xF8:
            printf("\tSEt Decimal\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_F8);
            break;
        default:
            printf("\tINVALID FLAG\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_register_Opcodes(unsigned char* inst){
    // Register Instructions
    //   Affect Flags: S Z
    // These instructions are implied mode, have a length of one byte and require
    // two machine cycles.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x88:
            printf("\tDEY (DEcrement Y)\n"); // DEY (DEcrement Y)        $88
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_88);
            break;
        case 0x98:
            printf("\tTYA (Transfer Y to A)\n"); // TYA (Transfer Y to A)    $98
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_98);
            break;
        case 0xA8:
            printf("\tTAY (Transfer A to Y) \n"); // TAY (Transfer A to Y)    $A8
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_A8);
            break;
        case 0xC8:
            printf("\tINY (INcrement Y)\n"); // INY (INcrement Y)        $C8
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_C8);
            break;
        case 0xE8:
            printf("\tINX (INcrement X)\n"); // INX (INcrement X)        $E8
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_E8);
            break;
        default:
            break;
    }

    return instData;
}

struct instruction* controlInstructionOpcodes(unsigned char* inst){
    if((inst[0] & 0b11) != 0b00){
        // error
        return NULL;
    }
    struct instruction* instData = NULL;


    if((inst[0] & 0b00011111) == 0b00010000){ // Branching instructions
        instData = control_Branching_Opcodes(inst);
    }
    else if(((inst[0] & 0b00011111) == 0b00011000) && (inst[0] != 0x98)){ // Flag instructions
        instData = control_Flag_Opcodes(inst);
    }
    else if(inst[0] == 0x08 || inst[0] == 0x28 || inst[0] == 0x48 || inst[0] == 0x68){
        instData = control_STACK_Opcodes(inst);
    }
    else if(inst[0] == 0x88 || inst[0] == 0x98 || inst[0] == 0xA8 || inst[0] == 0xC8 || inst[0] == 0xE8){
        printf("\tcontrol Register Instructions\n");
        instData = control_register_Opcodes(inst);
    }

    else if(inst[0] == 0x00){
        instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_00);
    }
    else if(inst[0] == 0x08){
        instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_08);
    }
    else if(inst[0] == 0xc0){
        instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, opcode_C0);
    }
    else{
        instData = NOP_Opcodes(inst);
    }
    return instData;
}

struct instruction* ALU_AND_Opcode(unsigned char* inst){
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x21:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, opcode_21); // Indirect,X    AND ($44,X)   $21  2   6
            break;
        case 0x25:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_25); // Zero Page     AND $44       $25  2   3
            break;
        case 0x29:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, opcode_29); // Immediate     AND #$44      $29  2   2
            break;
        case 0x2D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, opcode_2D); // Absolute      AND $4400     $2D  3   4
            break;
        case 0x31:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, opcode_31); // Indirect,Y    AND ($44),Y   $31  2   5+
            break;
        case 0x35:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_35); // Zero Page,X   AND $44,X     $35  2   4
            break;
        case 0x39:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, opcode_39); // Absolute,Y    AND $4400,Y   $39  3   4+
            break;
        case 0x3D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_3D); // Absolute,X    AND $4400,X   $3D  3   4+
            break;
        default:
            printf("\tINVALID AND\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_ORA_Opcode(unsigned char* inst){
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x01:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, opcode_01); // Indirect,X    ORA ($44,X)   $01  2   6
            break;
        case 0x05:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_05); // Zero Page     ORA $44       $05  2   3
            break;
        case 0x09:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, opcode_09); // Immediate     ORA #$44      $09  2   2
            break;
        case 0x0D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, opcode_0D); // Absolute      ORA $4400     $0D  3   4
            break;
        case 0x11:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, opcode_11); // Indirect,Y    ORA ($44),Y   $11  2   5+
            break;
        case 0x15:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_15); // Zero Page,X   ORA $44,X     $15  2   4
            break;
        case 0x19:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, opcode_19); // Absolute,Y    ORA $4400,Y   $19  3   4+
            break;
        case 0x1D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_1D); // Absolute,X    ORA $4400,X   $1D  3   4+
            break;
        default:
            printf("\tINVALID ORA\n");
            instData = NULL;
            break;
    }
    return instData;
}


struct instruction* ALUOpcodes(unsigned char* inst){
    if((inst[0] & 0b11) != 0b01){
        // Error
        return NULL;
    }
    struct instruction* instData = NULL;
    unsigned char type = (unsigned char)(inst[0] & 0b11100011);

    switch(type){
        case 0b00000001: // 0x00
            printf("\tORA (bitwise OR with Accumulator)\n");
            instData = ALU_ORA_Opcode(inst);
            break;
        case 0b00100001:  // 0x20
            printf("\tAND (bitwise AND with accumulator)\n");
            instData = ALU_AND_Opcode(inst);
            break;
        case 0b01000001: // 0x40
            printf("\tEOR (bitwise Exclusive OR)\n");
            break;
        case 0b01100001: // 0x60
            printf("\tADC (ADd with Carry) (or NOP)\n");
            break;
        case 0b10000001: // 0x80
            printf("\tSTA (STore Accumulator)\n");
            break;
        case 0b10100001: // 0xA0
            printf("\tLDA (LoaD Accumulator)\n");
            break;
        case 0b11000001: // 0xC0
            printf("\tCMP (CoMPare accumulator)\n");
            break;
        case 0b11100001: // 0xE0
            printf("\tSBC (SuBtract with Carry)\n");
            break;
        default:
            printf("\tERROR\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_ROR_Opcodes(unsigned char* inst){
    // ROR (ROtate Right)
    //   Affects Flags: S Z C
    // ROR shifts all bits right one position. The Carry is shifted into bit 7
    // and the original bit 0 is shifted into the Carry.
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x66:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_66); // Zero Page     ROR $44       $66  2   5
            break;
        case 0x6A:
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_ACCUMULATOR, opcode_6A); // Accumulator   ROR A         $6A  1   2
            break;
        case 0x6E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, opcode_6E); // Absolute      ROR $4400     $6E  3   6
            break;
        case 0x76:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, opcode_66); // Zero Page,X   ROR $44,X     $76  2   6
            break;
        case 0x7E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, opcode_7E); // Absolute,X    ROR $4400,X   $7E  3   7
            break;
        default:
            printf("\tINVALID ROR\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_LDX_Opcodes(unsigned char* inst){
    // LDX (LoaD X register)
    //   Affects Flags: S Z
    // + add 1 cycle if page boundary crossed
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xA2:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, opcode_A2); // Immediate     LDX #$44      $A2  2   2
            break;
        case 0xA6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_A6); // Zero Page     LDX $44       $A6  2   3
            break;
        case 0xB6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_Y, opcode_B6); // Zero Page,Y   LDX $44,Y     $B6  2   4
            break;
        case 0xAE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, opcode_AE); // Absolute      LDX $4400     $AE  3   4
            break;
        case 0xBE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, opcode_BE); // Absolute,Y    LDX $4400,Y   $BE  3   4+
            break;
        default:
            printf("\tINVALID LDX\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_STX_Opcodes(unsigned char* inst){
    // STX (STore X register)
    // Affects Flags: none 
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x86:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, opcode_86); // Zero Page     STX $44       $86  2   3
            break;
        case 0x8E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, opcode_8E); // Absolute      STX $4400     $8E  3   4
            break;
        case 0x96:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_Y, opcode_96); // Zero Page,Y   STX $44,Y     $96  2   4
            break;
        default:
            printf("\tINVALID STX\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_STACK_Opcodes(unsigned char* inst){
    // Stack Instructions
    // These instructions are implied mode, have a length of one byte and require
    // machine cycles as indicated. The "PuLl" operations are known as "POP" on most
    // other microprocessors. With the 6502, the stack is always on page one
    // ($100-$1FF) and works top down. 
    // MNEMONIC                        HEX TIM
    // TXS (Transfer X to Stack ptr)   $9A  2
    // TSX (Transfer Stack ptr to X)   $BA  2
    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x9A:
            printf("\tTXS (Transfer X to Stack ptr)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_9A);
            break;
        case 0xBA:
            printf("\tTSX (Transfer Stack ptr to X)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_BA);
            break;
        default:
            printf("\tINVALID RMW STACK\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* RMW_register_Opcodes(unsigned char* inst){
    // Register Instructions
    //   Affect Flags: S Z
    // These instructions are implied mode, have a length of one byte and require
    // two machine cycles.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x8A:
            printf("\tDEY (DEcrement Y)\n"); 
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_8A); // TXA (Transfer X to A)    $8A
            break;
        case 0xAA:
            printf("\tTYA (Transfer Y to A)\n"); 
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_AA); // TAX (Transfer A to X)    $AA
            break;
        case 0xCA:
            printf("\tTAY (Transfer A to Y) \n"); 
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, opcode_CA); // DEX (DEcrement X)        $CA
            break;
        default:
            break;
    }

    return instData;
}


struct instruction* RMW_Opcodes(unsigned char* inst){
    if((inst[0] & 0b11) != 0b10){
        // ERROR
        return NULL;
    }

    struct instruction* instData = NULL;
    unsigned char opcode = inst[0];
    if(((opcode & 0b11100011) == 0b01100010) && ((opcode & 0b00000100) || (~(opcode & 0b00010000) & (opcode & 0b00001000)))){ // y = C + A'B // C = 0000 0100 // B = 0000 1000 // A = 0001 0000
        printf("\tROR (ROtate Right)\n");
        instData = RMW_ROR_Opcodes(inst);
    }
    else if(((opcode & 0b11100011) == 0b10100010) && (((opcode & 0b00000100) == 0b00000100) | (~((opcode & 0b00010000) == 0b00010000) & ~((opcode & 0b0001000) == 0b00001000)))){
        printf("\tLDX (LoaD X register)\n");
        instData = RMW_LDX_Opcodes(inst);
    }
    else if(opcode == 0x86 || opcode == 0x8E || opcode == 0x96){
        printf("\tSTX (STore X register)\n");
        instData = RMW_STX_Opcodes(inst);
    }
    // else if()
    else if(opcode == 0x9A || opcode == 0xBA){
        printf("\tRMW Stack Instructions\n");
        instData = RMW_STACK_Opcodes(inst);
    }
    else if(opcode == 0x8A || opcode == 0xAA || opcode == 0xCA){
        printf("\tRMW Register Instructions\n");
        RMW_register_Opcodes(inst);
    }
    else{
        printf("\t\tERROR\n\n");
        instData = NULL;
    }
    return instData;
}


struct instruction* detectType(unsigned char* inst){
    unsigned char type = (unsigned char)(inst[0] & 0b11);
    struct instruction* instData = NULL;
    // printf("opcode: %i\ntype: %i\n", (unsigned int)inst[0], (unsigned int)type);
    printf("opcode: $");
    printfCharAsHex(inst[0]);
    printf("\n");
    if(type == 0b00){
        printf("\tControl instruction opcode\n");
        instData = controlInstructionOpcodes(inst);
    }
    else if(type == 0b01){
        printf("\tALU operation opcode\n");
        instData = ALUOpcodes(inst);

    }
    else if(type == 0b10){
        printf("\tread-modify-write (RMW) and data movement instructions opcode\n");
        instData = RMW_Opcodes(inst);
    }
    else{ // if(type == 0b11)
        printf("\tunoficial opcode\n");
    }
    return instData;
}

void printfInstructions(struct nesRom* rom){
    printf("pages: %i\n", rom->header->realPrgPageAmount);
    // sleep(5);

    for(unsigned int i = 0; i < rom->header->realPrgPageAmount*1024; i++){
        for(unsigned int j = 0; j < 16; j++){
            /*
            if(rom->prgRom[i*16 + j] < 0x10){
                printf("0");
            }
            printf("%x ", rom->prgRom[i*16 + j]);
            */
        }

        //printf("  |  ");
        /*
        for(unsigned int j = 0; j < 16; j++){
            if(rom->prgRom[i*16 + j] == '\n'){
                printf("\\n ");
            }
            else if(rom->prgRom[i*16 + j] == '\t'){
                printf("\\t ");
            }
            else{
                printf("%c ", rom->prgRom[i*16 + j]);
            }
        }
        */

        //printf("|");

        //printf("\n");

        if((i+1)%8 == 0){
            // sleep(1);
            //printf("\n");
        }
    }
}

void iterateInstructions(struct nesRom* rom){
    printf("\nIterating instructions: \n\n");
    unsigned char* inst;// = malloc(sizeof(unsigned char) * 4);
    //inst[3] = '\0';
    struct instruction* instData;
    unsigned int realPrgPageAmount = rom->header->realPrgPageAmount*16*1024;
    char aux[4] = "\0\0\0";

    size_t new_start = 0;
    size_t j = 0;

    for(size_t i = 0; i < realPrgPageAmount; i++){
        for(j = new_start; j < PRG_ROM_PAGE_SIZE; j++){
            if(j+1 >= PRG_ROM_PAGE_SIZE){
                inst = malloc(sizeof(unsigned char) * 3);
                inst[0] = rom->prgRom->prgRom[i][j];
                if(j+1 == PRG_ROM_PAGE_SIZE){
                    inst[1] = rom->prgRom->prgRom[i+1][0];
                    inst[2] = rom->prgRom->prgRom[i+1][1];
                }
                else if(j+2 == PRG_ROM_PAGE_SIZE){
                    inst[1] = rom->prgRom->prgRom[i][j+1];
                    inst[2] = rom->prgRom->prgRom[i+1][0];
                }
            }
            else{
                inst = (unsigned char*)strncpy(aux, (char *)&(rom->prgRom->prgRom[i][j]), 3);
            }
            
            instData = detectType(inst);
            printf("\n");
            if(instData == NULL){
                printf("\tunknow opcode: 0x%x - %i\n", inst[0], inst[0]);
                printf("\ti: %i - j: %i\n", (int)i, (int)j);
                break;
            }

            printf("opcode sintax: ");
            printfCharAsHex(instData->opcode);
            if(instData->bytesAmount > 0){
                printf(" ");
                printfCharAsHex(instData->byte1);
            }
            if(instData->bytesAmount > 1){
                printf(" ");
                printfCharAsHex(instData->byte2);
            }

            printf("\n\n");

            j += instData->bytesAmount;
        }
        new_start = j - PRG_ROM_PAGE_SIZE;
    }
    return;
}