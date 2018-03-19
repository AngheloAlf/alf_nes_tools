//
// Created by anghelo on 23-02-18.
//

#include "instructions.h"

struct instruction* initInstruction(unsigned char opcode, unsigned char bytesAmount, unsigned char byte1, unsigned char byte2, unsigned char type, char cicles, int (*execute)(struct instruction*, struct nesRegisters*, struct nesRam*)){
    struct instruction* instData = malloc(sizeof(struct instruction));

    instData->opcode = opcode;
    instData->byte1 = 0;
    instData->byte2 = 0;
    if(bytesAmount > 0){
        instData->byte1 = byte1;
    }
    if(bytesAmount > 1){
        instData->byte2 = byte2;
    }
    instData->bytesAmount = bytesAmount;
    instData->type = type;

    instData->cycles = cicles;
    instData->execute = execute;

    return instData;
}


struct instruction* control_BRK_Opcodes(unsigned char* inst, char extraCycles){
    // BRK (BReaK)
    //   Affects Flags: B
    // Implied       BRK           $00  1   7

    // BRK causes a non-maskable interrupt and increments the program counter by
    // one.  Therefore an <a href="#RTI">RTI</a> will
    // go to the address of the BRK +2 so that BRK may be used to replace a
    // two-byte instruction for debugging and the subsequent RTI will be correct.

    struct instruction* instData = NULL;
    if(inst[0] == 0x00){
        printf("\tBRK (BReaK)\n");
        instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 7, opcode_00);
    }
    else{
        printf("\tINVALID Control BRK Opcode\n");
        instData = NULL;
    }

    return instData;
}

struct instruction* control_STACK_Opcodes(unsigned char* inst, char extraCycles){
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
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 3, opcode_08);
            break;
        case 0x28:
            printf("\tPLP (PuLl Processor status)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 4, opcode_28);
            break;
        case 0x48:
            printf("\tPHA (PusH Accumulator)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 3, opcode_48);
            break;
        case 0x68:
            printf("\tPLA (PuLl Accumulator)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 4, opcode_68);
            break;
        default:
            printf("\tINVALID CONTROL STACK\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_Branching_Opcodes(unsigned char* inst, char extraCycles){
    // Branch Instructions
    //   Affect Flags: none
    // All branches are relative mode and have a length of two bytes. Syntax is "Bxx
    // Displacement" or (better) "Bxx Label". See the notes on the Program Counter for more on
    // displacements.
    // Branches are dependant on the status of the flag bits when the op code is
    // encountered. A branch not taken requires two machine cycles. Add one if the
    // branch is taken and add one more if the branch crosses a page boundary. 
    // MNEMONIC                       HEX
    // BPL (Branch on PLus)           $10
    // BMI (Branch on MInus)          $30
    // BVC (Branch on oVerflow Clear) $50
    // BVS (Branch on oVerflow Set)   $70
    // BCC (Branch on Carry Clear)    $90
    // BCS (Branch on Carry Set)      $B0
    // BNE (Branch on Not Equal)      $D0
    // BEQ (Branch on EQual)          $F0

    // There is no BRA (BRanch Always) instruction but it can be easily emulated
    // by branching on the basis of a known condition. One of the best flags to use for
    // this purpose is the <a href="#VFLAG">oVerflow</a> which is unchanged
    // by all but addition and subtraction operations.

    // Cicles:
    // not taken: 2+
    // taken: 3+

    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x10:
            printf("\tBranch on PLus\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_10);
            break;
        case 0x30:
            printf("\tBranch on MInus\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_30);
            break;
        case 0x50:
            printf("\tBranch on oVerflow Clear\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_50);
            break;
        case 0x70:
            printf("\tBranch on oVerflow Set\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_70);
            break;
        case 0x90:
            printf("\tBranch on Carry Clear\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_90);
            break;
        case 0xB0:
            printf("\tBranch on Carry Set\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_B0);
            break;
        case 0xD0:
            printf("\tBranch on Not Equal\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_D0);
            break;
        case 0xF0:
            printf("\tBranch on EQual\n");
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_RELATIVE, (char)2 + extraCycles, opcode_F0);
            break;
        default:
            printf("\tINVALID BRANCH\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_BIT_Opcodes(unsigned char* inst, char extraCycles){
    // BIT (test BITs)
    //   Affects Flags: N V Z
    // Zero Page     BIT $44       $24  2   3
    // Absolute      BIT $4400     $2C  3   4

    // BIT sets the Z flag as though the value in the address tested were ANDed
    // with the accumulator. The S and V flags are set to match bits 7 and 6
    // respectively in the value stored at the tested address.

    // Beware: a BIT instruction used in this way as a NOP does have effects: the flags
    // may be modified, and the read of the absolute address, if it happens to access an
    // I/O device, may cause an unwanted action.

    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x24:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_24);
            break;
        case 0x2C:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_2C);
            break;
        default:
            printf("\tINVALID BRANCH\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_Flag_Opcodes(unsigned char* inst, char extraCycles){
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

    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x18:
            printf("\tCLC (CLear Carry) \n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_18); // CLC (CLear Carry)              $18
            break;
        case 0x38:
            printf("\tSEC (SEt Carry)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_38); // SEC (SEt Carry)                $38
            break;
        case 0x58:
            printf("\tCLI (CLear Interrupt)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_58); // CLI (CLear Interrupt)          $58
            break;
        case 0x78:
            printf("\tSEI (SEt Interrupt)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_78); // SEI (SEt Interrupt)            $78
            break;
        case 0xB8:
            printf("\tCLV (CLear oVerflow)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_B8); // CLV (CLear oVerflow)           $B8
            break;
        case 0xD8:
            printf("\tCLD (CLear Decimal)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_D8); // CLD (CLear Decimal)            $D8
            break;
        case 0xF8:
            printf("\tSED (SEt Decimal)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_F8); // SED (SEt Decimal)              $F8
            break;
        default:
            printf("\tINVALID FLAG\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_RTI_Opcodes(unsigned char* inst, char extraCycles){
    // RTI (ReTurn from Interrupt)
    //   Affects Flags: all 
    // Implied       RTI           $40  1   6

    // RTI retrieves the Processor Status Word (flags) and the Program Counter
    // from the stack in that order (interrupts push the PC first and then the PSW).
    // Note that unlike RTS, the return address on the stack is the actual address
    // rather than the address-1.

    struct instruction* instData = NULL;
    if(inst[0] == 0x40){
        printf("\tRTI (ReTurn from Interrupt)\n");
        instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 6, opcode_40);
    }
    else{
        printf("\tINVALID Control RTI Opcode\n");
        instData = NULL;
    }

    return instData;
}

struct instruction* control_JSR_Opcodes(unsigned char* inst, char extraCycles){
    // JSR (Jump to SubRoutine)
    //   Affects Flags: none
    // Absolute      JSR $5597     $20  3   6

    // JSR pushes the address-1 of the next operation on to the stack before
    // transferring program control to the following address. Subroutines are normally
    // terminated by a <a href="#RTS">RTS</a> op
    // code.

    struct instruction* instData = NULL;
    if(inst[0] == 0x20){
        printf("\tJSR (Jump to SubRoutine)\n");
        instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 6, opcode_20);
    }
    else{
        printf("\tINVALID Control JSR Opcode\n");
        instData = NULL;
    }

    return instData;
}

struct instruction* control_JMP_Opcodes(unsigned char* inst, char extraCycles){
    // JMP (JuMP)
    //   Affects Flags: none
    // Absolute      JMP $5597     $4C  3   3
    // Indirect      JMP ($5597)   $6C  3   5

    // JMP transfers program execution to the following address (absolute) or to
    // the location contained in the following address (indirect). Note that there is
    // no carry associated with the indirect jump so: <pre><strong>AN INDIRECT JUMP MUST NEVER USE A
    // VECTOR BEGINNING ON THE LAST BYTE
    // OF A PAGE</strong>
    // For example if address $3000 contains $40, $30FF contains $80, and $3100
    // contains $50, the result of JMP ($30FF) will be a transfer of control to $4080
    // rather than $5080 as you intended i.e. the 6502 took the low byte of the address
    // from $30FF and the high byte from $3000.

    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x4C:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 3, opcode_4C);
            break;
        case 0x6C:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_INDIRECT, 5, opcode_6C);
            break;
        default:
            printf("\tINVALID JMP\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_RTS_Opcodes(unsigned char* inst, char extraCycles){
    // RTS (ReTurn from Subroutine)
    //   Affects Flags: none 
    // Implied       RTS           $60  1   6

    // RTS pulls the top two bytes off the stack (low byte first) and transfers
    // program control to that address+1. It is used, as expected, to exit a subroutine
    // invoked via JSR which
    // pushed the address-1.

    struct instruction* instData = NULL;
    if(inst[0] == 0x60){
        printf("\tRTS (ReTurn from Subroutine)\n");
        instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 6, opcode_60);
    }
    else{
        printf("\tINVALID Control RTS Opcode\n");
        instData = NULL;
    }

    return instData;
}

struct instruction* control_register_Opcodes(unsigned char* inst, char extraCycles){
    // Register Instructions
    //   Affect Flags: S Z
    // These instructions are implied mode, have a length of one byte and require
    // two machine cycles.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x88:
            printf("\tDEY (DEcrement Y)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_88); // DEY (DEcrement Y)        $88
            break;
        case 0x98:
            printf("\tTYA (Transfer Y to A)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_98); // TYA (Transfer Y to A)    $98
            break;
        case 0xA8:
            printf("\tTAY (Transfer A to Y) \n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_A8); // TAY (Transfer A to Y)    $A8
            break;
        case 0xC8:
            printf("\tINY (INcrement Y)\n"); // INY (INcrement Y)        $C8
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_C8); 
            break;
        case 0xE8:
            printf("\tINX (INcrement X)\n"); // INX (INcrement X)        $E8
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_E8); 
            break;
        default:
            printf("\tINVALID Control Register Opcode\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_LDY_Opcodes(unsigned char* inst, char extraCycles){
    // LDY (LoaD Y register)
    //   Affects Flags: S Z
    // + add 1 cycle if page boundary crossed

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xA0:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_A0); // Immediate     LDY #$44      $A0  2   2
            break;
        case 0xA4:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_A4); // Zero Page     LDY $44       $A4  2   3
            break;
        case 0xAC:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_AC); // Absolute      LDY $4400     $AC  3   4
            break;
        case 0xB4:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_B4); // Zero Page,X   LDY $44,X     $B4  2   4
            break;
        case 0xBC:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ZERO_PAGE_X, (char)4 + extraCycles, opcode_BC); // Absolute,X    LDY $4400,X   $BC  3   4+
            break;
        default:
            printf("\tINVALID Control LDY Opcode\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_STY_Opcodes(unsigned char* inst, char extraCycles){
    // STY (STore Y register)
    //   Affects Flags: none
    // Zero Page     STY $44       $84  2   3
    // Absolute      STY $4400     $8C  3   4
    // Zero Page,X   STY $44,X     $94  2   4

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x84:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_84);
            break;
        case 0x8C:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_8C);
            break;
        case 0x94:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_94);
            break;
        default:
            printf("\tINVALID Control STY Opcode\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_SHY_Opcodes(unsigned char* inst, char extraCycles){
    // http://nesdev.com/undocumented_opcodes.txt
    // SHY ()
    //   Affects Flags: None
    // Absolute,X      SHY $4400,X   $9C  3   5

    // AND Y register with the high byte of the target address of the argument
    // + 1. Store the result in memory.

    // M =3D Y AND HIGH(arg) + 1

    struct instruction* instData = NULL;
    if(inst[0] == 0x9C){
        instData = initInstruction(inst[0], 3, inst[1], inst[2], TYPE_ABSOLUTE_X, 5, opcode_9C);
    }
    else{
        printf("\tINVALID Control SHY Opcode\n");
        instData = NULL;
    }
    return instData;
}

struct instruction* control_CPY_Opcodes(unsigned char* inst, char extraCycles){
    // CPY (ComPare Y register)
    //   Affects Flags: S Z C
    // Immediate     CPY #$44      $C0  2   2
    // Zero Page     CPY $44       $C4  2   3
    // Absolute      CPY $4400     $CC  3   4

    // Operation and flag results are identical to equivalent mode accumulator <a href="#CMP">CMP</a> ops.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xC0:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_C0);
            break;
        case 0xC4:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_C4);
            break;
        case 0xCC:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_CC);
            break;
        default:
            printf("\tINVALID Control CPY Opcode\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_CPX_Opcodes(unsigned char* inst, char extraCycles){
    // CPX (ComPare X register)
    //   Affects Flags: S Z C
    // Immediate     CPX #$44      $E0  2   2
    // Zero Page     CPX $44       $E4  2   3
    // Absolute      CPX $4400     $EC  3   4

    // Operation and flag results are identical to equivalent mode accumulator <a href="#CMP">CMP</a> ops.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xE0:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_E0);
            break;
        case 0xE4:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_E4);
            break;
        case 0xEC:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_EC);
            break;
        default:
            printf("\tINVALID Control CPX Opcode\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* control_NOP_Opcodes(unsigned char* inst, char extraCycles){
    struct instruction* instData = NULL;
    unsigned char opcode = inst[0];

    if((opcode & 0b11) == 0b00){
        // Control opcode NOP
        if(opcode == 0x80){
            printf("\tIMMEDIATE NOP\n");
            instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_80);
        }
        else if(((opcode & 0b10011111) == 0b00000100) && ((opcode & 0b01000000) | ~(opcode & 0b00100000))){
            printf("\tZERO PAGE NOP\n");
            if(opcode == 0x04){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE, 2, opcode_04);
            }
            else if(opcode == 0x44){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE, 2, opcode_44);
            }
            else if(opcode == 0x64){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE, 2, opcode_64);
            }
            else{
                printf("\tINVALID ZERO PAGE NOP\n");
            }
        }
        else if(opcode == 0x0C){
            printf("\tABSOLUTE NOP\n");
            instData = initInstruction(opcode, 2, inst[1], inst[2], TYPE_ABSOLUTE, 2, opcode_0C);
        }
        else if(((opcode & 0b00011111) == 0b00010100) && (~(opcode & 0b10000000) | (opcode & 0b01000000))){
            printf("\tZERO PAGE X NOP\n");
            if(opcode == 0x14){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 2, opcode_14);
            }
            else if(opcode == 0x34){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 2, opcode_34);
            }
            else if(opcode == 0x54){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 2, opcode_54);
            }
            else if(opcode == 0x74){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 2, opcode_74);
            }
            else if(opcode == 0xD4){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 2, opcode_D4);
            }
            else if(opcode == 0xF4){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 2, opcode_F4);
            }
            else{
                printf("\tINVALID ZERO PAGE X NOP\n");
            }
        }
        else if(((opcode & 0b00011111) == 0b00011100) && (~(opcode & 0b10000000) | (opcode & 0b01000000))){
            printf("\tABSOLUTE X NOP\n");
            if(opcode == 0x1C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, 2, opcode_1C);
            }
            else if(opcode == 0x3C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, 2, opcode_3C);
            }
            else if(opcode == 0x5C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, 2, opcode_5C);
            }
            else if(opcode == 0x7C){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, 2, opcode_7C);
            }
            else if(opcode == 0xDC){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, 2, opcode_DC);
            }
            else if(opcode == 0xFC){
                instData = initInstruction(opcode, 1, inst[1], inst[2], TYPE_ABSOLUTE_X, 2, opcode_FC);
            }
            else{
                printf("\tINVALID ABSOLUTE X NOP\n");
            }
        }
        else{
            printf("\tINVALID CONTROL NOP\n");
            instData = NULL;
        }
    }

    else{
        printf("\tINVALID NOP\n");
        instData = NULL;
    }

    return instData;
}

//CONTROL
struct instruction* controlInstructionOpcodes(unsigned char* inst, char extraCycles){
    if((inst[0] & 0b11) != 0b00){
        // error
        return NULL;
    }
    struct instruction* instData = NULL;

    if((inst[0] & 0b00011111) == 0b00010000){ // Branching instructions
        printf("\tcontrol Branching Instructions\n");
        instData = control_Branching_Opcodes(inst, extraCycles);
    }
    else if(((inst[0] & 0b00011111) == 0b00011000) && (inst[0] != 0x98)){ // Flag instructions
        printf("\tcontrol Flag Instructions\n");
        instData = control_Flag_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x08 || inst[0] == 0x28 || inst[0] == 0x48 || inst[0] == 0x68){
        printf("\tcontrol Stack Instructions\n");
        instData = control_STACK_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x88 || inst[0] == 0x98 || inst[0] == 0xA8 || inst[0] == 0xC8 || inst[0] == 0xE8){
        printf("\tcontrol Register Instructions\n");
        instData = control_register_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0xA0 || inst[0] == 0xA4 || inst[0] == 0xAC || inst[0] == 0xB4 || inst[0] == 0xBC){
        printf("\tControl LDY Instructions)\n");
        instData = control_LDY_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x20){
        printf("\tControl JSR Instructions)\n");
        instData = control_JSR_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x60){
        printf("\tControl RTS Instructions)\n");
        instData = control_RTS_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x00){
        printf("\tControl BRK Instructions)\n");
        instData = control_BRK_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x24 || inst[0] == 0x2C){
        printf("\tControl BIT Instructions)\n");
        instData = control_BIT_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x40){
        printf("\tControl RTI Instructions)\n");
        instData = control_RTI_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x4C || inst[0] == 0x6C){
        printf("\tControl JMP Instructions)\n");
        instData = control_JMP_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x84 || inst[0] == 0x8C || inst[0] == 0x94){
        printf("\tControl STY Instructions)\n");
        instData = control_STY_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0x9C){
        printf("\tControl undocumented SHY Instructions)\n");
        instData = control_SHY_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0xC0 || inst[0] == 0xC4 || inst[0] == 0xCC){
        printf("\tControl CPY Instructions)\n");
        instData = control_CPY_Opcodes(inst, extraCycles);
    }
    else if(inst[0] == 0xE0 || inst[0] == 0xE4 || inst[0] == 0xEC){
        printf("\tControl CPX Instructions)\n");
        instData = control_CPX_Opcodes(inst, extraCycles);
    }
    else{
        instData = control_NOP_Opcodes(inst, extraCycles);
    }
    return instData;
}



//ALU
struct instruction* ALU_ORA_Opcode(unsigned char* inst, char extraCycles){
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x01:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_01); // Indirect,X    ORA ($44,X)   $01  2   6
            break;
        case 0x05:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_05); // Zero Page     ORA $44       $05  2   3
            break;
        case 0x09:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_09); // Immediate     ORA #$44      $09  2   2
            break;
        case 0x0D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_0D); // Absolute      ORA $4400     $0D  3   4
            break;
        case 0x11:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, (char)5 + extraCycles, opcode_11); // Indirect,Y    ORA ($44),Y   $11  2   5+
            break;
        case 0x15:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_15); // Zero Page,X   ORA $44,X     $15  2   4
            break;
        case 0x19:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_19); // Absolute,Y    ORA $4400,Y   $19  3   4+
            break;
        case 0x1D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, (char)4 + extraCycles, opcode_1D); // Absolute,X    ORA $4400,X   $1D  3   4+
            break;
        default:
            printf("\tINVALID ORA\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_AND_Opcode(unsigned char* inst, char extraCycles){
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x21:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_21); // Indirect,X    AND ($44,X)   $21  2   6
            break;
        case 0x25:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_25); // Zero Page     AND $44       $25  2   3
            break;
        case 0x29:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_29); // Immediate     AND #$44      $29  2   2
            break;
        case 0x2D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_2D); // Absolute      AND $4400     $2D  3   4
            break;
        case 0x31:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, (char)5 + extraCycles, opcode_31); // Indirect,Y    AND ($44),Y   $31  2   5+
            break;
        case 0x35:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_35); // Zero Page,X   AND $44,X     $35  2   4
            break;
        case 0x39:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_39); // Absolute,Y    AND $4400,Y   $39  3   4+
            break;
        case 0x3D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, (char)4 + extraCycles, opcode_3D); // Absolute,X    AND $4400,X   $3D  3   4+
            break;
        default:
            printf("\tINVALID AND\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_EOR_Opcode(unsigned char* inst, char extraCycles){
    // EOR (bitwise Exclusive OR)
    //   Affects Flags: S Z
    // + add 1 cycle if page boundary crossed
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x41:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_41); // Indirect,X    EOR ($44,X)   $41  2   6
            break;
        case 0x45:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_45); // Zero Page     EOR $44       $45  2   3
            break;
        case 0x49:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_49); // Immediate     EOR #$44      $49  2   2
            break;
        case 0x4D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_4D); // Absolute      EOR $4400     $4D  3   4
            break;
        case 0x51:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, (char)5 + extraCycles, opcode_51); // Indirect,Y    EOR ($44),Y   $51  2   5+
            break;
        case 0x55:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_55); // Zero Page,X   EOR $44,X     $55  2   4
            break;
        case 0x59:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_59); // Absolute,Y    EOR $4400,Y   $59  3   4+
            break;
        case 0x5D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, (char)4 + extraCycles, opcode_5D); // Absolute,X    EOR $4400,X   $5D  3   4+
            break;
        default:
            printf("\tINVALID EOR\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_ADC_Opcode(unsigned char* inst, char extraCycles){
    // ADC (ADd with Carry)
    //   AAffects Flags: S V Z C
    // + add 1 cycle if page boundary crossed
    // ADC results are dependant on the setting of the decimal flag. In decimal
    // mode, addition is carried out on the assumption that the values involved are
    // packed BCD (Binary Coded Decimal).

    // There is no way to add without carry.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x61:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_61); // Indirect,X    ADC ($44,X)   $61  2   6
            break;
        case 0x65:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_65); // Zero Page     ADC $44       $65  2   3
            break;
        case 0x69:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_69); // Immediate     ADC #$44      $69  2   2
            break;
        case 0x6D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_6D); // Absolute      ADC $4400     $6D  3   4
            break;
        case 0x71:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, (char)5 + extraCycles, opcode_71); // Indirect,Y    ADC ($44),Y   $71  2   5+
            break;
        case 0x75:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_75); // Zero Page,X   ADC $44,X     $75  2   4
            break;
        case 0x79:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_79); // Absolute,Y    ADC $4400,Y   $79  3   4+
            break;
        case 0x7D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, (char)4 + extraCycles, opcode_7D); // Absolute,X    ADC $4400,X   $7D  3   4+
            break;
        default:
            printf("\tINVALID ADC\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_STA_Opcode(unsigned char* inst, char extraCycles){
    // STA (STore Accumulator) 
    //   Affects Flags: none

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x81:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_81); // Indirect,X    STA ($44,X)   $81  2   6
            break;
        case 0x85:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_85); // Zero Page     STA $44       $85  2   3
            break;
        case 0x89: // NOP
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_89); // NOP // Immediate     ADC #$44      $69  2   2
            break;
        case 0x8D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_8D);  // Absolute      STA $4400     $8D  3   4
            break;
        case 0x91:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, 6, opcode_91); // Indirect,Y    STA ($44),Y   $91  2   6
            break;
        case 0x95:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_95); // Zero Page,X   STA $44,X     $95  2   4
            break;
        case 0x99:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, 5, opcode_99); // Absolute,Y    STA $4400,Y   $99  3   5
            break;
        case 0x9D:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, 5, opcode_9D); // Absolute,X    STA $4400,X   $9D  3   5
            break;
        default:
            printf("\tINVALID STA\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_LDA_Opcode(unsigned char* inst, char extraCycles){
    // LDA (LoaD Accumulator)>
    //   Affects Flags: S Z

    // + add 1 cycle if page boundary crossed

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xA1:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_A1); // Indirect,X    LDA ($44,X)   $A1  2   6
            break;
        case 0xA5:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_A5); // Zero Page     LDA $44       $A5  2   3
            break;
        case 0xA9:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_A9); // Immediate     LDA #$44      $A9  2   2
            break;
        case 0xAD:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_AD); // Absolute      LDA $4400     $AD  3   4
            break;
        case 0xB1:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, (char)5 + extraCycles, opcode_B1); // Indirect,Y    LDA ($44),Y   $B1  2   5+
            break;
        case 0xB5:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_B5); // Zero Page,X   LDA $44,X     $B5  2   4
            break;
        case 0xB9:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_B9); // Absolute,Y    LDA $4400,Y   $B9  3   4+
            break;
        case 0xBD:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, (char)4 + extraCycles, opcode_BD); // Absolute,X    LDA $4400,X   $BD  3   4+
            break;
        default:
            printf("\tINVALID LDA\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_CMP_Opcode(unsigned char* inst, char extraCycles){
    // CMP (CoMPare accumulator) 
    //   Affects Flags: S Z C
    // + add 1 cycle if page boundary crossed

    // Compare sets flags as if a subtraction had been carried out. If the value
    // in the accumulator is equal or greater than the compared value, the Carry will
    // be set. The equal (Z) and sign (S) flags will be set based on equality or lack
    // thereof and the sign (i.e. A&gt;=$80) of the accumulator.


    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xC1:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_C1); // Indirect,X    CMP ($44,X)   $C1  2   6
            break;
        case 0xC5:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_C5); // Zero Page     CMP $44       $C5  2   3
            break;
        case 0xC9:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_C9); // Immediate     CMP #$44      $C9  2   2
            break;
        case 0xCD:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_CD); // Absolute      CMP $4400     $CD  3   4
            break;
        case 0xD1:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, (char)5 + extraCycles, opcode_D1); // Indirect,Y    CMP ($44),Y   $D1  2   5+   $B1  2   5+
            break;
        case 0xD5:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_D5); // Zero Page,X   CMP $44,X     $D5  2   4
            break;
        case 0xD9:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_D9); // Absolute,Y    CMP $4400,Y   $D9  3   4+
            break;
        case 0xDD:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, (char)4 + extraCycles, opcode_DD); // Absolute,X    CMP $4400,X   $DD  3   4+
            break;
        default:
            printf("\tINVALID CMP\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* ALU_SBC_Opcode(unsigned char* inst, char extraCycles){
    // SBC (SuBtract with Carry)
    //   Affects Flags: S V Z C
    // + add 1 cycle if page boundary crossed

    // SBC results are dependant on the setting of the decimal flag. In decimal
    // mode, subtraction is carried out on the assumption that the values involved are
    // packed BCD (Binary Coded Decimal).
    // There is no way to subtract without the carry which works as an inverse
    // borrow. i.e, to subtract you set the carry before the operation. If the carry is
    // cleared by the operation, it indicates a borrow occurred.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xE1:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_X, 6, opcode_E1); // Indirect,X    SBC ($44,X)   $E1  2   6
            break;
        case 0xE5:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_E5); // Zero Page     SBC $44       $E5  2   3
            break;
        case 0xE9:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_E9); // Immediate     SBC #$44      $E9  2   2
            break;
        case 0xED:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_ED); // Absolute      SBC $4400     $ED  3   4
            break;
        case 0xF1:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_INDIRECT_Y, (char)5 + extraCycles, opcode_F1); // Indirect,Y    SBC ($44),Y   $F1  2   5+
            break;
        case 0xF5:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 4, opcode_F5); // Zero Page,X   SBC $44,X     $F5  2   4
            break;
        case 0xF9:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_F9); // Absolute,Y    SBC $4400,Y   $F9  3   4+
            break;
        case 0xFD:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, (char)4 + extraCycles, opcode_FD); // Absolute,X    SBC $4400,X   $FD  3   4+
            break;
        default:
            printf("\tINVALID SBC\n");
            instData = NULL;
            break;
    }
    return instData;
}



// ALU
struct instruction* ALUOpcodes(unsigned char* inst, char extraCycles){
    if((inst[0] & 0b11) != 0b01){
        // Error
        return NULL;
    }
    struct instruction* instData = NULL;
    unsigned char type = (unsigned char)(inst[0] & 0b11100011);

    switch(type){
        case 0b00000001: // 0x00
            printf("\tORA (bitwise OR with Accumulator)\n");
            instData = ALU_ORA_Opcode(inst, extraCycles);
            break;
        case 0b00100001:  // 0x20
            printf("\tAND (bitwise AND with accumulator)\n");
            instData = ALU_AND_Opcode(inst, extraCycles);
            break;
        case 0b01000001: // 0x40
            printf("\tEOR (bitwise Exclusive OR)\n");
            instData = ALU_EOR_Opcode(inst, extraCycles);
            break;
        case 0b01100001: // 0x60
            printf("\tADC (ADd with Carry)\n");
            instData = ALU_ADC_Opcode(inst, extraCycles);
            break;
        case 0b10000001: // 0x80
            printf("\tSTA (STore Accumulator) (or NOP)\n");
            instData = ALU_STA_Opcode(inst, extraCycles);
            break;
        case 0b10100001: // 0xA0
            printf("\tLDA (LoaD Accumulator)\n");
            instData = ALU_LDA_Opcode(inst, extraCycles);
            break;
        case 0b11000001: // 0xC0
            printf("\tCMP (CoMPare accumulator)\n");
            instData = ALU_CMP_Opcode(inst, extraCycles);
            break;
        case 0b11100001: // 0xE0
            printf("\tSBC (SuBtract with Carry)\n");
            instData = ALU_SBC_Opcode(inst, extraCycles);
            break;
        default:
            printf("\tERROR\n");
            instData = NULL;
            break;
    }
    return instData;
}



// RMW
struct instruction* RMW_ASL_Opcodes(unsigned char* inst, char extraCycles){
    // ASL (Arithmetic Shift Left)
    //   Affects Flags: S Z C
    // Zero Page     ASL $44       $06  2   5
    // Accumulator   ASL A         $0A  1   2
    // Absolute      ASL $4400     $0E  3   6
    // Zero Page,X   ASL $44,X     $16  2   6
    // Absolute,X    ASL $4400,X   $1E  3   7
    //
    // ASL shifts all bits left one position. 0 is shifted into bit 0 and the
    // original bit 7 is shifted into the Carry..

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x06:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 5, opcode_06);
            break;
        case 0x0A:
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_ACCUMULATOR, 2, opcode_0A);
            break;
        case 0x0E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 6, opcode_0E);
            break;
        case 0x16:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 6, opcode_16);
            break;
        case 0x1E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, 7, opcode_1E);
            break;
        default:
            printf("\tINVALID ASL\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_ROL_Opcodes(unsigned char* inst, char extraCycles){
    // ROL (ROtate Left)
    //   Affects Flags: S Z C
    // Zero Page     ROL $44       $26  2   5
    // Accumulator   ROL A         $2A  1   2
    // Zero Page,X   ROL $44,X     $36  2   6
    // Absolute      ROL $4400     $2E  3   6
    // Absolute,X    ROL $4400,X   $3E  3   7
    //
    // ROL shifts all bits left one position. The Carry is shifted into bit 0 and
    // the original bit 7 is shifted into the Carry.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x26:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 5, opcode_26);
            break;
        case 0x2A:
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_ACCUMULATOR, 2, opcode_2A);
            break;
        case 0x36:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 6, opcode_36);
            break;
        case 0x2E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 6, opcode_2E);
            break;
        case 0x3E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, 7, opcode_3E);
            break;
        default:
            printf("\tINVALID ROL\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_LSR_Opcodes(unsigned char* inst, char extraCycles){
    // LSR (Logical Shift Right)
    //   Affects Flags: S Z C
    // Zero Page     LSR $44       $46  2   5
    // Accumulator   LSR A         $4A  1   2
    // Absolute      LSR $4400     $4E  3   6
    // Zero Page,X   LSR $44,X     $56  2   6
    // Absolute,X    LSR $4400,X   $5E  3   7
    //
    // LSR shifts all bits right one position. 0 is shifted into bit 7 and the
    // original bit 0 is shifted into the Carry.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x46:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 5, opcode_46);
            break;
        case 0x4A:
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_ACCUMULATOR, 2, opcode_4A);
            break;
        case 0x4E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 6, opcode_4E);
            break;
        case 0x56:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 6, opcode_56);
            break;
        case 0x5E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, 7, opcode_5E);
            break;
        default:
            printf("\tINVALID LSR\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_ROR_Opcodes(unsigned char* inst, char extraCycles){
    // ROR (ROtate Right)
    //   Affects Flags: S Z C
    // ROR shifts all bits right one position. The Carry is shifted into bit 7
    // and the original bit 0 is shifted into the Carry.
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x66:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 5, opcode_66); // Zero Page     ROR $44       $66  2   5
            break;
        case 0x6A:
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_ACCUMULATOR, 2, opcode_6A); // Accumulator   ROR A         $6A  1   2
            break;
        case 0x6E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 6, opcode_6E); // Absolute      ROR $4400     $6E  3   6
            break;
        case 0x76:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 6, opcode_76); // Zero Page,X   ROR $44,X     $76  2   6
            break;
        case 0x7E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, 7, opcode_7E); // Absolute,X    ROR $4400,X   $7E  3   7
            break;
        default:
            printf("\tINVALID ROR\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_LDX_Opcodes(unsigned char* inst, char extraCycles){
    // LDX (LoaD X register)
    //   Affects Flags: S Z
    // + add 1 cycle if page boundary crossed
    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xA2:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_A2); // Immediate     LDX #$44      $A2  2   2
            break;
        case 0xA6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_A6); // Zero Page     LDX $44       $A6  2   3
            break;
        case 0xB6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_Y, 4, opcode_B6); // Zero Page,Y   LDX $44,Y     $B6  2   4
            break;
        case 0xAE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_AE); // Absolute      LDX $4400     $AE  3   4
            break;
        case 0xBE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, (char)4 + extraCycles, opcode_BE); // Absolute,Y    LDX $4400,Y   $BE  3   4+
            break;
        default:
            printf("\tINVALID LDX\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_STX_Opcodes(unsigned char* inst, char extraCycles){
    // STX (STore X register)
    //   Affects Flags: none 

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x86:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 3, opcode_86); // Zero Page     STX $44       $86  2   3
            break;
        case 0x8E:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 4, opcode_8E); // Absolute      STX $4400     $8E  3   4
            break;
        case 0x96:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_Y, 4, opcode_96); // Zero Page,Y   STX $44,Y     $96  2   4
            break;
        default:
            printf("\tINVALID STX\n");
            instData = NULL;
            break;
    }
    return instData;
}

struct instruction* RMW_STACK_Opcodes(unsigned char* inst, char extraCycles){
    // Stack Instructions
    // These instructions are implied mode, have a length of one byte and require
    // machine cycles as indicated. The "PuLl" operations are known as "POP" on most
    // other microprocessors. With the 6502, the stack is always on page one
    // ($100-$1FF) and works top down.

    struct instruction* instData = NULL;

    switch(inst[0]){
        case 0x9A:
            printf("\tTXS (Transfer X to Stack ptr)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_9A); // TXS (Transfer X to Stack ptr)   $9A  2
            break;
        case 0xBA:
            printf("\tTSX (Transfer Stack ptr to X)\n");
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_BA); // TSX (Transfer Stack ptr to X)   $BA  2
            break;
        default:
            printf("\tINVALID RMW STACK\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* RMW_register_Opcodes(unsigned char* inst, char extraCycles){
    // Register Instructions
    //   Affect Flags: S Z
    // These instructions are implied mode, have a length of one byte and require
    // two machine cycles.

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0x8A:
            printf("\tTXA (Transfer X to A)\n"); 
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_8A); // TXA (Transfer X to A)    $8A
            break;
        case 0xAA:
            printf("\tTAX (Transfer A to X)\n"); 
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_AA); // TAX (Transfer A to X)    $AA
            break;
        case 0xCA:
            printf("\tDEX (DEcrement X))\n"); 
            instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_CA); // DEX (DEcrement X)        $CA
            break;
        default:
            printf("\tINVALID RMW REGISTER OPCODE\n"); 
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* RMW_INC_Opcodes(unsigned char* inst, char extraCycles){
    // INC (INCrement memory)
    //   Affects Flags: S Z

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xE6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 5, opcode_E6); // Zero Page     INC $44       $E6  2   5
            break;
        case 0xEE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 6, opcode_EE); // Absolute      INC $4400     $EE  3   6
            break;
        case 0xF6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 6, opcode_F6); // Zero Page,X   INC $44,X     $F6  2   6
            break;
        case 0xFE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, 7, opcode_FE); // Absolute,X    INC $4400,X   $FE  3   7
            break;
        default:
            printf("\tINVALID RMW INC OPCODE\n"); 
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* RMW_DEC_Opcodes(unsigned char* inst, char extraCycles){
    // DEC (DECrement memory)
    //   Affects Flags: S Z
    // Zero Page     DEC $44       $C6  2   5
    // Absolute      DEC $4400     $CE  3   6
    // Zero Page,X   DEC $44,X     $D6  2   6
    // Absolute,X    DEC $4400,X   $DE  3   7

    struct instruction* instData = NULL;
    switch(inst[0]){
        case 0xC6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE, 5, opcode_C6);
            break;
        case 0xCE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE, 6, opcode_CE);
            break;
        case 0xD6:
            instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_ZERO_PAGE_X, 6, opcode_D6);
            break;
        case 0xDE:
            instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_X, 7, opcode_DE);
            break;
        default:
            printf("\tINVALID RMW DEC OPCODE\n");
            instData = NULL;
            break;
    }

    return instData;
}

struct instruction* RMW_NOP_Opcodes(unsigned char* inst, char extraCycles){
    struct instruction* instData = NULL;
    unsigned char opcode = inst[0];

    if(opcode == 0xEA){
        // NOP (No OPeration)
        //   Affects Flags: none
        // NOP is used to reserve space for future modifications or effectively REM
        // out existing code.
        printf("\tofficial NOP\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, 2, opcode_EA); // Implied       NOP           $EA  1   2
    }

    else{
        switch(opcode){
            case 0x82:
                printf("\tRMW IMMEDIATE NOP Opcode\n");
                instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_82);
                break;
            case 0xC2:
                printf("\tRMW IMMEDIATE NOP Opcode\n");
                instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_C2);
                break;
            case 0xE2:
                printf("\tRMW IMMEDIATE NOP Opcode\n");
                instData = initInstruction(inst[0], 1, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_E2);
                break;
            case 0x1A:
                printf("\tRMW IMPLIED NOP Opcode\n");
                instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_1A); 
                break;
            case 0x3A:
                printf("\tRMW IMPLIED NOP Opcode\n");
                instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_3A); 
                break;
            case 0x5A:
                printf("\tRMW IMPLIED NOP Opcode\n");
                instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_5A); 
                break;
            case 0x7A:
                printf("\tRMW IMPLIED NOP Opcode\n");
                instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_7A); 
                break;
            case 0xDA:
                printf("\tRMW IMPLIED NOP Opcode\n");
                instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_DA); 
                break;
            case 0xFA:
                printf("\tRMW IMPLIED NOP Opcode\n");
                instData = initInstruction(inst[0], 0, inst[1], inst[2], TYPE_IMMEDIATE, 2, opcode_FA); 
                break;
            default:
                printf("\tINVALID NOP\n");
                instData = NULL;
                break;
        }
    }

    return instData;
}

struct instruction* RMW_STP_Opcodes(unsigned char* inst, char extraCycles){
    // http://nesdev.com/undocumented_opcodes.txt
    // STP (KIL (JAM) [HLT])
    // =3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
    // Stop program counter (processor lock up).
    // Status flags: -

    // Addressing  |Mnemonics  |Opc|Sz | n
    // ------------|-----------|---|---|---
    // Implied     |KIL        |$02| 1 | -
    // Implied     |KIL        |$12| 1 | -
    // Implied     |KIL        |$22| 1 | -
    // Implied     |KIL        |$32| 1 | -
    // Implied     |KIL        |$42| 1 | -
    // Implied     |KIL        |$52| 1 | -
    // Implied     |KIL        |$62| 1 | -
    // Implied     |KIL        |$72| 1 | -
    // Implied     |KIL        |$92| 1 | -
    // Implied     |KIL        |$B2| 1 | -
    // Implied     |KIL        |$D2| 1 | -
    // Implied     |KIL        |$F2| 1 | -
    struct instruction* instData = NULL;
    unsigned char opcode = inst[0];

    if(opcode == 0x02){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_02); 
    }
    else if(opcode == 0x12){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_12); 
    }
    else if(opcode == 0x22){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_22); 
    }
    else if(opcode == 0x32){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_32); 
    }
    else if(opcode == 0x42){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_42); 
    }
    else if(opcode == 0x52){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_52); 
    }
    else if(opcode == 0x62){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_62); 
    }
    else if(opcode == 0x72){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_72); 
    }
    else if(opcode == 0x92){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_92); 
    }
    else if(opcode == 0xB2){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_B2); 
    }
    else if(opcode == 0xD2){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_D2); 
    }
    else if(opcode == 0xF2){
        printf("\tRMW STP Opcode\n");
        instData = initInstruction(opcode, 0, inst[1], inst[2], TYPE_IMPLIED, -1, opcode_F2); 
    }
    else{
        printf("\tINVALID STP\n");
        instData = NULL;
    }

    return instData;
}

struct instruction* RMW_SHX_Opcodes(unsigned char* inst, char extraCycles){
    // SXA (SHX) [XAS]
    // =3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
    // AND X register with the high byte of the target address of the argument
    // + 1. Store the result in memory.

    // M =3D X AND HIGH(arg) + 1

    // Status flags: -

    // Addressing  |Mnemonics  |Opc|Sz | n
    // ------------|-----------|---|---|---
    // Absolute,Y  |SXA arg,Y  |$9E| 3 | 5

    struct instruction* instData = NULL;
    if(inst[0] == 0x9E){
        printf("\tRMW SHX Opcode\n");
        instData = initInstruction(inst[0], 2, inst[1], inst[2], TYPE_ABSOLUTE_Y, 5, opcode_9E); 
    }
    else{
        instData = NULL;
        printf("\tINVALID SHX Opcode\n");
    }

    return instData;
    
}



// RMW
struct instruction* RMW_Opcodes(unsigned char* inst, char extraCycles){
    if((inst[0] & 0b11) != 0b10){
        // ERROR
        return NULL;
    }

    struct instruction* instData = NULL;
    unsigned char opcode = inst[0];
    if(opcode == 0x06 || opcode == 0x0A || opcode == 0x0E || opcode == 0x16 || opcode == 0x1E){
        printf("\tASL (Arithmetic Shift Left)\n");
        instData = RMW_ASL_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0x2A || opcode == 0x26 || opcode == 0x2E || opcode == 0x36 || opcode == 0x3E){
        printf("\tROL (ROtate Left)\n");
        instData = RMW_ROL_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0x4A || opcode == 0x46 || opcode == 0x2E || opcode == 0x56 || opcode == 0x5E){
        printf("\tLSR (Logical Shift Right)\n");
        instData = RMW_LSR_Opcodes(inst, extraCycles);
    }
    else if(((opcode & 0b11100011) == 0b01100010) && ((opcode & 0b00000100) || (~(opcode & 0b00010000) & (opcode & 0b00001000)))){ // y = C + A'B // C = 0000 0100 // B = 0000 1000 // A = 0001 0000
        printf("\tROR (ROtate Right)\n");
        instData = RMW_ROR_Opcodes(inst, extraCycles);
    }
    else if(((opcode & 0b11100011) == 0b10100010) && (((opcode & 0b00000100) == 0b00000100) | (~((opcode & 0b00010000) == 0b00010000) & ~((opcode & 0b0001000) == 0b00001000)))){
        printf("\tLDX (LoaD X register)\n");
        instData = RMW_LDX_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0x86 || opcode == 0x8E || opcode == 0x96){
        printf("\tSTX (STore X register)\n");
        instData = RMW_STX_Opcodes(inst, extraCycles);
    }
    // else if()
    else if(opcode == 0x9A || opcode == 0xBA){
        printf("\tRMW Stack Instructions\n");
        instData = RMW_STACK_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0x8A || opcode == 0xAA || opcode == 0xCA){
        printf("\tRMW Register Instructions\n");
        instData = RMW_register_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0xE6 || opcode == 0xEE || opcode == 0xF6 || opcode == 0xFE){
        printf("\tRMW INC Instructions\n");
        instData = RMW_INC_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0xC6 || opcode == 0xCE || opcode == 0xD6 || opcode == 0xDE){
        printf("\tRMW DEC Instructions\n");
        instData = RMW_DEC_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0xEA || opcode == 0xFA || opcode == 0xDA || opcode == 0x7A || opcode == 0x5A || opcode == 0x3A || opcode == 0x1A || opcode == 0xE2 || opcode == 0xC2 || opcode == 0x82){
        printf("\tRMW NOP Instructions\n");
        instData = RMW_NOP_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0x02 || opcode == 0x12 || opcode == 0x22 || opcode == 0x32 || opcode == 0x42 || opcode == 0x52 || opcode == 0x62 || opcode == 0x72 || opcode == 0x92 || opcode == 0xB2 || opcode == 0xD2 || opcode == 0xF2){
        printf("\tRMW STP Instructions\n");
        instData = RMW_STP_Opcodes(inst, extraCycles);
    }
    else if(opcode == 0x9E){
        printf("\tRMW SHX Instructions\n");
        instData = RMW_SHX_Opcodes(inst, extraCycles);
    }
    else{
        printf("\t\tERROR\n\n");
        instData = NULL;
    }
    return instData;
}



struct instruction* detectType(unsigned char* inst, char extraCycles){
    unsigned char type = (unsigned char)(inst[0] & 0b11);
    struct instruction* instData = NULL;
    // printf("opcode: %i\ntype: %i\n", (unsigned int)inst[0], (unsigned int)type);
    printf("opcode: $");
    printfCharAsHex(inst[0]);
    printf("\n");
    if(type == 0b00){
        printf("\tControl instruction opcode\n");
        instData = controlInstructionOpcodes(inst, extraCycles);
    }
    else if(type == 0b01){
        printf("\tALU operation opcode\n");
        instData = ALUOpcodes(inst, extraCycles);

    }
    else if(type == 0b10){
        printf("\tread-modify-write (RMW) and data movement instructions opcode\n");
        instData = RMW_Opcodes(inst, extraCycles);
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

    char extraCycles = 0;

    for(size_t i = 0; i < realPrgPageAmount; i++){
        for(j = new_start; j < PRG_ROM_PAGE_SIZE; j++){
            if(j+1 >= PRG_ROM_PAGE_SIZE){
                extraCycles = 1;

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
                extraCycles = 0;
                inst = (unsigned char*)strncpy(aux, (char *)&(rom->prgRom->prgRom[i][j]), 3);
            }
            
            instData = detectType(inst, extraCycles);

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
}

unsigned short loadAddress(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram){
    unsigned short absolulteAddress = instData->byte2<<8 | instData->byte1;
    unsigned short firstAddress;
    unsigned short secondAddress;
    switch(instData->type){
        case TYPE_ACCUMULATOR:
            return 0; // Es asi.
        case TYPE_IMMEDIATE:
            return instData->byte1;
        case TYPE_IMPLIED:
            return 0; // Es asi

        case TYPE_RELATIVE:
            return instData->byte1;
        case TYPE_ABSOLUTE:
            return absolulteAddress;
        case TYPE_ZERO_PAGE:
            return instData->byte1;
        case TYPE_INDIRECT:
            return absolulteAddress;

        case TYPE_ABSOLUTE_X:
            return absolulteAddress + registers->indexX;
        case TYPE_ABSOLUTE_Y:
            return absolulteAddress + registers->indexY;
        case TYPE_ZERO_PAGE_X:
            return instData->byte1 + registers->indexX;
        case TYPE_ZERO_PAGE_Y:
            return instData->byte1 + registers->indexY;
        case TYPE_INDIRECT_X:
            firstAddress = registers->indexX + instData->byte1;
            secondAddress = loadFromRam(ram, (unsigned short)(firstAddress+1))<<8 | loadFromRam(ram, firstAddress);
            return secondAddress;
        case TYPE_INDIRECT_Y:
            firstAddress = loadFromRam(ram, (unsigned short)(instData->byte1+1)<<8) | loadFromRam(ram, instData->byte1);
            secondAddress = firstAddress + (unsigned short)registers->indexY;
            return secondAddress;

        default:
            return 0;
    }
}

unsigned char loadNumberFromRamOrArg(struct instruction *instData, struct nesRegisters *registers, struct nesRam *ram){
    unsigned short address = loadAddress(instData, registers, ram);

    switch(instData->type){
        case TYPE_ACCUMULATOR:
        case TYPE_IMMEDIATE:
        case TYPE_IMPLIED:
        case TYPE_RELATIVE:
        case TYPE_INDIRECT:
            return (unsigned char)address;

        case TYPE_ABSOLUTE:
        case TYPE_ZERO_PAGE:
        case TYPE_ABSOLUTE_X:
        case TYPE_ABSOLUTE_Y:
        case TYPE_ZERO_PAGE_X:
        case TYPE_ZERO_PAGE_Y:
        case TYPE_INDIRECT_X:
        case TYPE_INDIRECT_Y:
            return loadFromRam(ram, address);

        default:
            return 0;
    }
}
