//
// Created by anghelo on 23-02-18.
//

#include "instructions.h"

unsigned char getInstSizeByType(unsigned char type){
    switch(type){
        case TYPE_ACCUMULATOR:
            return SIZE_ACCUMULATOR;
        case TYPE_IMMEDIATE:
            return SIZE_IMMEDIATE;
        case TYPE_ZERO_PAGE:
            return SIZE_ZERO_PAGE;
        case TYPE_ZERO_PAGE_X:
            return SIZE_ZERO_PAGE_X;
        case TYPE_ZERO_PAGE_Y:
            return SIZE_ZERO_PAGE_Y;
        case TYPE_ABSOLUTE:
            return SIZE_ABSOLUTE;
        case TYPE_ABSOLUTE_X:
            return SIZE_ABSOLUTE_X;
        case TYPE_ABSOLUTE_Y:
            return SIZE_ABSOLUTE_Y;
        case TYPE_INDIRECT:
            return SIZE_INDIRECT;
        case TYPE_INDIRECT_X:
            return SIZE_INDIRECT_X;
        case TYPE_INDIRECT_Y:
            return SIZE_INDIRECT_Y;
        case TYPE_IMPLIED:
            return SIZE_IMPLIED;
        case TYPE_RELATIVE:
            return SIZE_RELATIVE;
        default:
            return HIGH_NIBBLE | LOW_NIBBLE;
    }
}

Instruction *initInstruction(const unsigned char *inst, unsigned char type, char cicles,
                             int (*execute)(Instruction *, NesCPURegisters *, NesRam *)){
    Instruction* instData = malloc(sizeof(Instruction));

    instData->opcode = inst[0];
    instData->byte1 = 0;
    instData->byte2 = 0;
    instData->type = type;
    instData->bytesAmount = getInstSizeByType(type);
    if(instData->bytesAmount > 0){
        instData->byte1 = inst[1];
    }
    if(instData->bytesAmount > 1){
        instData->byte2 = inst[2];
    }

    instData->cycles = cicles;
    instData->execute = execute;

    return instData;
}


Instruction* control_BRK_Opcodes(unsigned char* inst, char extraCycles){
    // BRK (BReaK)
    //   Affects Flags: B
    // Implied       BRK           $00  1   7

    // BRK causes a non-maskable interrupt and increments the program counter by
    // one.  Therefore an <a href="#RTI">RTI</a> will
    // go to the address of the BRK +2 so that BRK may be used to replace a
    // two-byte instruction for debugging and the subsequent RTI will be correct.

    if(inst[0] == 0x00){
        // printf("\tBRK (BReaK)\n");
        return initInstruction(inst, TYPE_IMPLIED, 7, opcode_00);
    }
    printf("\tINVALID Control BRK Opcode\n");
    return NULL;
}

Instruction* control_STACK_Opcodes(unsigned char* inst, char extraCycles){
    /*
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
     */
    switch(inst[0]){
        case 0x08:
            // printf("\tPHP (PusH Processor status)\n");
            return initInstruction(inst, TYPE_IMPLIED, 3, opcode_08);
        case 0x28:
            //printf("\tPLP (PuLl Processor status)\n");
            return initInstruction(inst, TYPE_IMPLIED, 4, opcode_28);
        case 0x48:
            //printf("\tPHA (PusH Accumulator)\n");
            return initInstruction(inst, TYPE_IMPLIED, 3, opcode_48);
        case 0x68:
            // printf("\tPLA (PuLl Accumulator)\n");
            return initInstruction(inst, TYPE_IMPLIED, 4, opcode_68);
        default:
            printf("\tINVALID CONTROL STACK\n");
            return NULL;
    }
}

Instruction* control_Branching_Opcodes(unsigned char* inst, char extraCycles){
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

    switch(inst[0]){
        case 0x10:
            // printf("\tBranch on PLus\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_10);
        case 0x30:
            // printf("\tBranch on MInus\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_30);
        case 0x50:
            // printf("\tBranch on oVerflow Clear\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_50);
        case 0x70:
            // printf("\tBranch on oVerflow Set\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_70);
        case 0x90:
            // printf("\tBranch on Carry Clear\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_90);
        case 0xB0:
            // printf("\tBranch on Carry Set\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_B0);
        case 0xD0:
            // printf("\tBranch on Not Equal\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_D0);
        case 0xF0:
            // printf("\tBranch on EQual\n");
            return initInstruction(inst, TYPE_RELATIVE, (char)(2 + extraCycles), opcode_F0);
        default:
            printf("\tINVALID BRANCH\n");
            return NULL;
    }
}

Instruction* control_BIT_Opcodes(unsigned char* inst, char extraCycles){
    /*
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
    */
    switch(inst[0]){
        case 0x24:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_24);
        case 0x2C:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_2C);
        default:
            printf("\tINVALID BRANCH\n");
            return NULL;
    }
}

Instruction* control_Flag_Opcodes(unsigned char* inst, char extraCycles){
    /*
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
    */
    switch(inst[0]){
        case 0x18:
            // printf("\tCLC (CLear Carry) \n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_18); // CLC (CLear Carry)              $18
        case 0x38:
            // printf("\tSEC (SEt Carry)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_38); // SEC (SEt Carry)                $38
        case 0x58:
            // printf("\tCLI (CLear Interrupt)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_58); // CLI (CLear Interrupt)          $58
        case 0x78:
            // printf("\tSEI (SEt Interrupt)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_78); // SEI (SEt Interrupt)            $78
        case 0xB8:
            // printf("\tCLV (CLear oVerflow)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_B8); // CLV (CLear oVerflow)           $B8
        case 0xD8:
            // printf("\tCLD (CLear Decimal)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_D8); // CLD (CLear Decimal)            $D8
        case 0xF8:
            // printf("\tSED (SEt Decimal)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_F8); // SED (SEt Decimal)              $F8
        default:
            printf("\tINVALID FLAG\n");
            return NULL;
    }
}

Instruction* control_RTI_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // RTI (ReTurn from Interrupt)
    //   Affects Flags: all
    // Implied       RTI           $40  1   6

    // RTI retrieves the Processor Status Word (flags) and the Program Counter
    // from the stack in that order (interrupts push the PC first and then the PSW).
    // Note that unlike RTS, the return address on the stack is the actual address
    // rather than the address-1.
    */

    if(inst[0] == 0x40){
        // printf("\tRTI (ReTurn from Interrupt)\n");
        return initInstruction(inst, TYPE_IMPLIED, 6, opcode_40);
    }
    printf("\tINVALID Control RTI Opcode\n");
    return NULL;
}

Instruction* control_JSR_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // JSR (Jump to SubRoutine)
    //   Affects Flags: none
    // Absolute      JSR $5597     $20  3   6

    // JSR pushes the address-1 of the next operation on to the stack before
    // transferring program control to the following address. Subroutines are normally
    // terminated by a <a href="#RTS">RTS</a> op
    // code.
    */

    if(inst[0] == 0x20){
        // printf("\tJSR (Jump to SubRoutine)\n");
        return initInstruction(inst, TYPE_ABSOLUTE, 6, opcode_20);
    }
    printf("\tINVALID Control JSR Opcode\n");
    return NULL;
}

Instruction* control_JMP_Opcodes(unsigned char* inst, char extraCycles){
    /*
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
     */

    switch(inst[0]){
        case 0x4C:
            return initInstruction(inst, TYPE_ABSOLUTE, 3, opcode_4C);
        case 0x6C:
            return initInstruction(inst, TYPE_INDIRECT, 5, opcode_6C);
        default:
            printf("\tINVALID JMP\n");
            return NULL;
    }
}

Instruction* control_RTS_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // RTS (ReTurn from Subroutine)
    //   Affects Flags: none
    // Implied       RTS           $60  1   6

    // RTS pulls the top two bytes off the stack (low byte first) and transfers
    // program control to that address+1. It is used, as expected, to exit a subroutine
    // invoked via JSR which
    // pushed the address-1.
    */

    if(inst[0] == 0x60){
        // printf("\tRTS (ReTurn from Subroutine)\n");
        return initInstruction(inst, TYPE_IMPLIED, 6, opcode_60);
    }
    printf("\tINVALID Control RTS Opcode\n");
    return NULL;

}

Instruction* control_register_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // Register Instructions
    //   Affect Flags: S Z
    // These instructions are implied mode, have a length of one byte and require
    // two machine cycles.
    */
    switch(inst[0]){
        case 0x88:
            // printf("\tDEY (DEcrement Y)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_88); // DEY (DEcrement Y)        $88
        case 0x98:
            // printf("\tTYA (Transfer Y to A)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_98); // TYA (Transfer Y to A)    $98
        case 0xA8:
            // printf("\tTAY (Transfer A to Y) \n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_A8); // TAY (Transfer A to Y)    $A8
        case 0xC8:
            // printf("\tINY (INcrement Y)\n"); // INY (INcrement Y)        $C8
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_C8);
        case 0xE8:
            // printf("\tINX (INcrement X)\n"); // INX (INcrement X)        $E8
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_E8);
        default:
            printf("\tINVALID Control Register Opcode\n");
            return NULL;
    }
}

Instruction* control_LDY_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // LDY (LoaD Y register)
    //   Affects Flags: S Z
    // + add 1 cycle if page boundary crossed
    */
    switch(inst[0]){
        case 0xA0:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_A0); // Immediate     LDY #$44      $A0  2   2
        case 0xA4:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_A4); // Zero Page     LDY $44       $A4  2   3
        case 0xAC:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_AC); // Absolute      LDY $4400     $AC  3   4
        case 0xB4:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_B4); // Zero Page,X   LDY $44,X     $B4  2   4
        case 0xBC:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, (char)(4 + extraCycles), opcode_BC); // Absolute,X    LDY $4400,X   $BC  3   4+
        default:
            printf("\tINVALID Control LDY Opcode\n");
            return NULL;
    }
}

Instruction* control_STY_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // STY (STore Y register)
    //   Affects Flags: none
    // Zero Page     STY $44       $84  2   3
    // Absolute      STY $4400     $8C  3   4
    // Zero Page,X   STY $44,X     $94  2   4
    */
    switch(inst[0]){
        case 0x84:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_84);
        case 0x8C:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_8C);
        case 0x94:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_94);
        default:
            printf("\tINVALID Control STY Opcode\n");
            return NULL;
    }
}

Instruction* control_SHY_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // http://nesdev.com/undocumented_opcodes.txt
    // SHY ()
    //   Affects Flags: None
    // Absolute,X      SHY $4400,X   $9C  3   5

    // AND Y register with the high byte of the target address of the argument
    // + 1. Store the result in memory.

    // M =3D Y AND HIGH(arg) + 1
    */
    if(inst[0] == 0x9C){
        return initInstruction(inst, TYPE_ABSOLUTE_X, 5, opcode_9C);
    }
    printf("\tINVALID Control SHY Opcode\n");
    return NULL;
}

Instruction* control_CPY_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // CPY (ComPare Y register)
    //   Affects Flags: S Z C
    // Immediate     CPY #$44      $C0  2   2
    // Zero Page     CPY $44       $C4  2   3
    // Absolute      CPY $4400     $CC  3   4

    // Operation and flag results are identical to equivalent mode accumulator <a href="#CMP">CMP</a> ops.
    */
    switch(inst[0]){
        case 0xC0:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_C0);
        case 0xC4:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_C4);
        case 0xCC:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_CC);
        default:
            printf("\tINVALID Control CPY Opcode\n");
            return NULL;
    }
}

Instruction* control_CPX_Opcodes(unsigned char* inst, char extraCycles){
    // CPX (ComPare X register)
    //   Affects Flags: S Z C
    // Immediate     CPX #$44      $E0  2   2
    // Zero Page     CPX $44       $E4  2   3
    // Absolute      CPX $4400     $EC  3   4

    // Operation and flag results are identical to equivalent mode accumulator <a href="#CMP">CMP</a> ops.

    switch(inst[0]){
        case 0xE0:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_E0);
        case 0xE4:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_E4);
        case 0xEC:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_EC);
        default:
            printf("\tINVALID Control CPX Opcode\n");
            return NULL;
    }
}

Instruction* control_NOP_Opcodes(unsigned char* inst, char extraCycles){
    if((inst[0] & (BIT_1 | BIT_0)) != 0x0){
        printf("\tINVALID NOP\n");
        return NULL;
    }

    switch(inst[0]){
        case 0x80:
            // printf("\tIMMEDIATE NOP\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_80);
        case 0x04:
            return initInstruction(inst, TYPE_ZERO_PAGE, 2, opcode_04);
        case 0x44:
            return initInstruction(inst, TYPE_ZERO_PAGE, 2, opcode_44);
        case 0x64:
            return initInstruction(inst, TYPE_ZERO_PAGE, 2, opcode_64);
        case 0x0C:
            // printf("\tABSOLUTE NOP\n");
            return initInstruction(inst, TYPE_ABSOLUTE, 2, opcode_0C);
        case 0x14:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 2, opcode_14);
        case 0x34:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 2, opcode_34);
        case 0x54:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 2, opcode_54);
        case 0x74:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 2, opcode_74);
        case 0xD4:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 2, opcode_D4);
        case 0xF4:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 2, opcode_F4);
        case 0x1C:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 2, opcode_1C);
        case 0x3C:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 2, opcode_3C);
        case 0x5C:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 2, opcode_5C);
        case 0x7C:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 2, opcode_7C);
        case 0xDC:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 2, opcode_DC);
        case 0xFC:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 2, opcode_FC);

        default:
            printf("\tINVALID CONTROL NOP\n");
            return NULL;
    }
}

//CONTROL
Instruction* controlInstructionOpcodes(unsigned char* inst, char extraCycles){
    if((inst[0] & (BIT_1 | BIT_0)) != 0x0){
        // error
        return NULL;
    }
    switch(inst[0]){
        case 0x10:
        case 0x30:
        case 0x50:
        case 0x70:
        case 0x90:
        case 0xB0:
        case 0xD0:
        case 0xF0:
            // printf("\tcontrol Branching Instructions\n");
            return control_Branching_Opcodes(inst, extraCycles);
        case 0x18:
        case 0x38:
        case 0x58:
        case 0x78:
        case 0xB8:
        case 0xD8:
        case 0xF8:
            // printf("\tcontrol Flag Instructions\n");
            return control_Flag_Opcodes(inst, extraCycles);
        case 0x08:
        case 0x28:
        case 0x48:
        case 0x68:
            // printf("\tcontrol Stack Instructions\n");
            return control_STACK_Opcodes(inst, extraCycles);
        case 0x88:
        case 0x98:
        case 0xA8:
        case 0xC8:
        case 0xE8:
            // printf("\tcontrol Register Instructions\n");
            return control_register_Opcodes(inst, extraCycles);
        case 0xA0:
        case 0xA4:
        case 0xAC:
        case 0xB4:
        case 0xBC:
            // printf("\tControl LDY Instructions)\n");
            return control_LDY_Opcodes(inst, extraCycles);
        case 0x24:
        case 0x2C:
            // printf("\tControl BIT Instructions)\n");
            return control_BIT_Opcodes(inst, extraCycles);
        case 0x4C:
        case 0x6C:
            // printf("\tControl JMP Instructions)\n");
            return control_JMP_Opcodes(inst, extraCycles);
        case 0x84:
        case 0x8C:
        case 0x94:
            // printf("\tControl STY Instructions)\n");
            return control_STY_Opcodes(inst, extraCycles);
        case 0xC0:
        case 0xC4:
        case 0xCC:
            // printf("\tControl CPY Instructions)\n");
            return control_CPY_Opcodes(inst, extraCycles);
        case 0xE0:
        case 0xE4:
        case 0xEC:
            // printf("\tControl CPX Instructions)\n");
            return control_CPX_Opcodes(inst, extraCycles);
        case 0x20:
            // printf("\tControl JSR Instructions)\n");
            return control_JSR_Opcodes(inst, extraCycles);
        case 0x60:
            // printf("\tControl RTS Instructions)\n");
            return control_RTS_Opcodes(inst, extraCycles);
        case 0x00:
            // printf("\tControl BRK Instructions)\n");
            return control_BRK_Opcodes(inst, extraCycles);
        case 0x40:
            // printf("\tControl RTI Instructions)\n");
            return control_RTI_Opcodes(inst, extraCycles);
        case 0x9C:
            // printf("\tControl undocumented SHY Instructions)\n");
            return control_SHY_Opcodes(inst, extraCycles);
        default:
            return control_NOP_Opcodes(inst, extraCycles);
    }
}


//ALU
Instruction* ALU_ORA_Opcode(unsigned char* inst, char extraCycles){
    switch(inst[0]){
        case 0x01:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_01); // Indirect,X    ORA ($44,X)   $01  2   6
        case 0x05:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_05); // Zero Page     ORA $44       $05  2   3
        case 0x09:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_09); // Immediate     ORA #$44      $09  2   2
        case 0x0D:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_0D); // Absolute      ORA $4400     $0D  3   4
        case 0x11:
            return initInstruction(inst, TYPE_INDIRECT_Y, (char)(5 + extraCycles), opcode_11); // Indirect,Y    ORA ($44),Y   $11  2   5+
        case 0x15:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_15); // Zero Page,X   ORA $44,X     $15  2   4
        case 0x19:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_19); // Absolute,Y    ORA $4400,Y   $19  3   4+
        case 0x1D:
            return initInstruction(inst, TYPE_ABSOLUTE_X, (char)(4 + extraCycles), opcode_1D); // Absolute,X    ORA $4400,X   $1D  3   4+
        default:
            printf("\tINVALID ORA\n");
            return NULL;
    }
}

Instruction* ALU_AND_Opcode(unsigned char* inst, char extraCycles){
    switch(inst[0]){
        case 0x21:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_21); // Indirect,X    AND ($44,X)   $21  2   6
        case 0x25:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_25); // Zero Page     AND $44       $25  2   3
        case 0x29:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_29); // Immediate     AND #$44      $29  2   2
        case 0x2D:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_2D); // Absolute      AND $4400     $2D  3   4
        case 0x31:
            return initInstruction(inst, TYPE_INDIRECT_Y, (char)(5 + extraCycles), opcode_31); // Indirect,Y    AND ($44),Y   $31  2   5+
        case 0x35:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_35); // Zero Page,X   AND $44,X     $35  2   4
        case 0x39:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_39); // Absolute,Y    AND $4400,Y   $39  3   4+
        case 0x3D:
            return initInstruction(inst, TYPE_ABSOLUTE_X, (char)(4 + extraCycles), opcode_3D); // Absolute,X    AND $4400,X   $3D  3   4+
        default:
            printf("\tINVALID AND\n");
            return NULL;
    }
}

Instruction* ALU_EOR_Opcode(unsigned char* inst, char extraCycles){
    // EOR (bitwise Exclusive OR)
    //   Affects Flags: S Z
    // + add 1 cycle if page boundary crossed
    switch(inst[0]){
        case 0x41:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_41); // Indirect,X    EOR ($44,X)   $41  2   6
        case 0x45:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_45); // Zero Page     EOR $44       $45  2   3
        case 0x49:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_49); // Immediate     EOR #$44      $49  2   2
        case 0x4D:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_4D); // Absolute      EOR $4400     $4D  3   4
        case 0x51:
            return initInstruction(inst, TYPE_INDIRECT_Y, (char)(5 + extraCycles), opcode_51); // Indirect,Y    EOR ($44),Y   $51  2   5+
        case 0x55:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_55); // Zero Page,X   EOR $44,X     $55  2   4
        case 0x59:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_59); // Absolute,Y    EOR $4400,Y   $59  3   4+
        case 0x5D:
            return initInstruction(inst, TYPE_ABSOLUTE_X, (char)(4 + extraCycles), opcode_5D); // Absolute,X    EOR $4400,X   $5D  3   4+
        default:
            printf("\tINVALID EOR\n");
            return NULL;
    }
}

Instruction* ALU_ADC_Opcode(unsigned char* inst, char extraCycles){
    // ADC (ADd with Carry)
    //   AAffects Flags: S V Z C
    // + add 1 cycle if page boundary crossed
    // ADC results are dependant on the setting of the decimal flag. In decimal
    // mode, addition is carried out on the assumption that the values involved are
    // packed BCD (Binary Coded Decimal).

    // There is no way to add without carry.

    switch(inst[0]){
        case 0x61:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_61); // Indirect,X    ADC ($44,X)   $61  2   6
        case 0x65:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_65); // Zero Page     ADC $44       $65  2   3
        case 0x69:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_69); // Immediate     ADC #$44      $69  2   2
        case 0x6D:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_6D); // Absolute      ADC $4400     $6D  3   4
        case 0x71:
            return initInstruction(inst, TYPE_INDIRECT_Y, (char)(5 + extraCycles), opcode_71); // Indirect,Y    ADC ($44),Y   $71  2   5+
        case 0x75:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_75); // Zero Page,X   ADC $44,X     $75  2   4
        case 0x79:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_79); // Absolute,Y    ADC $4400,Y   $79  3   4+
        case 0x7D:
            return initInstruction(inst, TYPE_ABSOLUTE_X, (char)(4 + extraCycles), opcode_7D); // Absolute,X    ADC $4400,X   $7D  3   4+
        default:
            printf("\tINVALID ADC\n");
            return NULL;
    }
}

Instruction* ALU_STA_Opcode(unsigned char* inst, char extraCycles){
    // STA (STore Accumulator)
    //   Affects Flags: none

    switch(inst[0]){
        case 0x81:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_81); // Indirect,X    STA ($44,X)   $81  2   6
        case 0x85:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_85); // Zero Page     STA $44       $85  2   3
        case 0x89: // NOP
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_89); // NOP // Immediate     ADC #$44      $69  2   2
        case 0x8D:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_8D);  // Absolute      STA $4400     $8D  3   4
        case 0x91:
            return initInstruction(inst, TYPE_INDIRECT_Y, 6, opcode_91); // Indirect,Y    STA ($44),Y   $91  2   6
        case 0x95:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_95); // Zero Page,X   STA $44,X     $95  2   4
        case 0x99:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, 5, opcode_99); // Absolute,Y    STA $4400,Y   $99  3   5
        case 0x9D:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 5, opcode_9D); // Absolute,X    STA $4400,X   $9D  3   5
        default:
            printf("\tINVALID STA\n");
            return NULL;
    }
}

Instruction* ALU_LDA_Opcode(unsigned char* inst, char extraCycles){
    // LDA (LoaD Accumulator)>
    //   Affects Flags: S Z

    // + add 1 cycle if page boundary crossed

    switch(inst[0]){
        case 0xA1:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_A1); // Indirect,X    LDA ($44,X)   $A1  2   6
        case 0xA5:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_A5); // Zero Page     LDA $44       $A5  2   3
        case 0xA9:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_A9); // Immediate     LDA #$44      $A9  2   2
        case 0xAD:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_AD); // Absolute      LDA $4400     $AD  3   4
        case 0xB1:
            return initInstruction(inst, TYPE_INDIRECT_Y, (char)(5 + extraCycles), opcode_B1); // Indirect,Y    LDA ($44),Y   $B1  2   5+
        case 0xB5:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_B5); // Zero Page,X   LDA $44,X     $B5  2   4
        case 0xB9:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_B9); // Absolute,Y    LDA $4400,Y   $B9  3   4+
        case 0xBD:
            return initInstruction(inst, TYPE_ABSOLUTE_X, (char)(4 + extraCycles), opcode_BD); // Absolute,X    LDA $4400,X   $BD  3   4+
        default:
            printf("\tINVALID LDA\n");
            return NULL;
    }
}

Instruction* ALU_CMP_Opcode(unsigned char* inst, char extraCycles){
    // CMP (CoMPare accumulator)
    //   Affects Flags: S Z C
    // + add 1 cycle if page boundary crossed

    // Compare sets flags as if a subtraction had been carried out. If the value
    // in the accumulator is equal or greater than the compared value, the Carry will
    // be set. The equal (Z) and sign (S) flags will be set based on equality or lack
    // thereof and the sign (i.e. A&gt;=$80) of the accumulator.
    switch(inst[0]){
        case 0xC1:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_C1); // Indirect,X    CMP ($44,X)   $C1  2   6
        case 0xC5:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_C5); // Zero Page     CMP $44       $C5  2   3
        case 0xC9:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_C9); // Immediate     CMP #$44      $C9  2   2
        case 0xCD:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_CD); // Absolute      CMP $4400     $CD  3   4
        case 0xD1:
            return initInstruction(inst, TYPE_INDIRECT_Y, (char)(5 + extraCycles), opcode_D1); // Indirect,Y    CMP ($44),Y   $D1  2   5+   $B1  2   5+
        case 0xD5:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_D5); // Zero Page,X   CMP $44,X     $D5  2   4
        case 0xD9:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_D9); // Absolute,Y    CMP $4400,Y   $D9  3   4+
        case 0xDD:
            return initInstruction(inst, TYPE_ABSOLUTE_X, (char)(4 + extraCycles), opcode_DD); // Absolute,X    CMP $4400,X   $DD  3   4+
        default:
            printf("\tINVALID CMP\n");
            return NULL;
    }
}

Instruction* ALU_SBC_Opcode(unsigned char* inst, char extraCycles){
    // SBC (SuBtract with Carry)
    //   Affects Flags: S V Z C
    // + add 1 cycle if page boundary crossed

    // SBC results are dependant on the setting of the decimal flag. In decimal
    // mode, subtraction is carried out on the assumption that the values involved are
    // packed BCD (Binary Coded Decimal).
    // There is no way to subtract without the carry which works as an inverse
    // borrow. i.e, to subtract you set the carry before the operation. If the carry is
    // cleared by the operation, it indicates a borrow occurred.

    switch(inst[0]){
        case 0xE1:
            return initInstruction(inst, TYPE_INDIRECT_X, 6, opcode_E1); // Indirect,X    SBC ($44,X)   $E1  2   6
        case 0xE5:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_E5); // Zero Page     SBC $44       $E5  2   3
        case 0xE9:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_E9); // Immediate     SBC #$44      $E9  2   2
        case 0xED:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_ED); // Absolute      SBC $4400     $ED  3   4
        case 0xF1:
            return initInstruction(inst, TYPE_INDIRECT_Y, (char)(5 + extraCycles), opcode_F1); // Indirect,Y    SBC ($44),Y   $F1  2   5+
        case 0xF5:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 4, opcode_F5); // Zero Page,X   SBC $44,X     $F5  2   4
        case 0xF9:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_F9); // Absolute,Y    SBC $4400,Y   $F9  3   4+
        case 0xFD:
            return initInstruction(inst, TYPE_ABSOLUTE_X, (char)(4 + extraCycles), opcode_FD); // Absolute,X    SBC $4400,X   $FD  3   4+
        default:
            printf("\tINVALID SBC\n");
            return NULL;
    }
}



// ALU
Instruction* ALUOpcodes(unsigned char* inst, char extraCycles){
    if((inst[0] & (BIT_1 | BIT_0)) != BIT_0){
        // Error
        return NULL;
    }
    unsigned char type = (unsigned char)(inst[0] & (BIT_7 | BIT_6 | BIT_5));
    switch(type){
        case 0x00:
            // printf("\tORA (bitwise OR with Accumulator)\n");
            return ALU_ORA_Opcode(inst, extraCycles);
        case 0x20:
            // printf("\tAND (bitwise AND with accumulator)\n");
            return ALU_AND_Opcode(inst, extraCycles);
        case 0x40:
            // printf("\tEOR (bitwise Exclusive OR)\n");
            return ALU_EOR_Opcode(inst, extraCycles);
        case 0x60:
            // printf("\tADC (ADd with Carry)\n");
            return ALU_ADC_Opcode(inst, extraCycles);
        case 0x80:
            // printf("\tSTA (STore Accumulator) (or NOP)\n");
            return ALU_STA_Opcode(inst, extraCycles);
        case 0xA0:
            // printf("\tLDA (LoaD Accumulator)\n");
            return ALU_LDA_Opcode(inst, extraCycles);
        case 0xC0:
            // printf("\tCMP (CoMPare accumulator)\n");
            return ALU_CMP_Opcode(inst, extraCycles);
        case 0xE0:
            // printf("\tSBC (SuBtract with Carry)\n");
            return ALU_SBC_Opcode(inst, extraCycles);
        default:
            printf("\tERROR\n");
            return NULL;
    }
}



// RMW
Instruction* RMW_ASL_Opcodes(unsigned char* inst, char extraCycles){
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

    switch(inst[0]){
        case 0x06:
            return initInstruction(inst, TYPE_ZERO_PAGE, 5, opcode_06);
        case 0x0A:
            return initInstruction(inst, TYPE_ACCUMULATOR, 2, opcode_0A);
        case 0x0E:
            return initInstruction(inst, TYPE_ABSOLUTE, 6, opcode_0E);
        case 0x16:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 6, opcode_16);
        case 0x1E:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 7, opcode_1E);
        default:
            printf("\tINVALID ASL\n");
            return NULL;
    }
}

Instruction* RMW_ROL_Opcodes(unsigned char* inst, char extraCycles){
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

    switch(inst[0]){
        case 0x26:
            return initInstruction(inst, TYPE_ZERO_PAGE, 5, opcode_26);
        case 0x2A:
            return initInstruction(inst, TYPE_ACCUMULATOR, 2, opcode_2A);
        case 0x36:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 6, opcode_36);
        case 0x2E:
            return initInstruction(inst, TYPE_ABSOLUTE, 6, opcode_2E);
        case 0x3E:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 7, opcode_3E);
        default:
            printf("\tINVALID ROL\n");
            return NULL;
    }
}

Instruction* RMW_LSR_Opcodes(unsigned char* inst, char extraCycles){
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

    switch(inst[0]){
        case 0x46:
            return initInstruction(inst, TYPE_ZERO_PAGE, 5, opcode_46);
        case 0x4A:
            return initInstruction(inst, TYPE_ACCUMULATOR, 2, opcode_4A);
        case 0x4E:
            return initInstruction(inst, TYPE_ABSOLUTE, 6, opcode_4E);
        case 0x56:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 6, opcode_56);
        case 0x5E:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 7, opcode_5E);
        default:
            printf("\tINVALID LSR\n");
            return NULL;
    }
}

Instruction* RMW_ROR_Opcodes(unsigned char* inst, char extraCycles){
    // ROR (ROtate Right)
    //   Affects Flags: S Z C
    // ROR shifts all bits right one position. The Carry is shifted into bit 7
    // and the original bit 0 is shifted into the Carry.
    switch(inst[0]){
        case 0x66:
            return initInstruction(inst, TYPE_ZERO_PAGE, 5, opcode_66); // Zero Page     ROR $44       $66  2   5
        case 0x6A:
            return initInstruction(inst, TYPE_ACCUMULATOR, 2, opcode_6A); // Accumulator   ROR A         $6A  1   2
        case 0x6E:
            return initInstruction(inst, TYPE_ABSOLUTE, 6, opcode_6E); // Absolute      ROR $4400     $6E  3   6
        case 0x76:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 6, opcode_76); // Zero Page,X   ROR $44,X     $76  2   6
        case 0x7E:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 7, opcode_7E); // Absolute,X    ROR $4400,X   $7E  3   7
        default:
            printf("\tINVALID ROR\n");
            return NULL;
    }
}

Instruction* RMW_LDX_Opcodes(unsigned char* inst, char extraCycles){
    // LDX (LoaD X register)
    //   Affects Flags: S Z
    // + add 1 cycle if page boundary crossed
    switch(inst[0]){
        case 0xA2:
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_A2); // Immediate     LDX #$44      $A2  2   2
        case 0xA6:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_A6); // Zero Page     LDX $44       $A6  2   3
        case 0xB6:
            return initInstruction(inst, TYPE_ZERO_PAGE_Y, 4, opcode_B6); // Zero Page,Y   LDX $44,Y     $B6  2   4
        case 0xAE:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_AE); // Absolute      LDX $4400     $AE  3   4
        case 0xBE:
            return initInstruction(inst, TYPE_ABSOLUTE_Y, (char)(4 + extraCycles), opcode_BE); // Absolute,Y    LDX $4400,Y   $BE  3   4+
        default:
            printf("\tINVALID LDX\n");
            return NULL;
    }
}

Instruction* RMW_STX_Opcodes(unsigned char* inst, char extraCycles){
    // STX (STore X register)
    //   Affects Flags: none

    switch(inst[0]){
        case 0x86:
            return initInstruction(inst, TYPE_ZERO_PAGE, 3, opcode_86); // Zero Page     STX $44       $86  2   3
        case 0x8E:
            return initInstruction(inst, TYPE_ABSOLUTE, 4, opcode_8E); // Absolute      STX $4400     $8E  3   4
        case 0x96:
            return initInstruction(inst, TYPE_ZERO_PAGE_Y, 4, opcode_96); // Zero Page,Y   STX $44,Y     $96  2   4
        default:
            printf("\tINVALID STX\n");
            return NULL;
    }
}

Instruction* RMW_STACK_Opcodes(unsigned char* inst, char extraCycles){
    // Stack Instructions
    // These instructions are implied mode, have a length of one byte and require
    // machine cycles as indicated. The "PuLl" operations are known as "POP" on most
    // other microprocessors. With the 6502, the stack is always on page one
    // ($100-$1FF) and works top down.

    switch(inst[0]){
        case 0x9A:
            // printf("\tTXS (Transfer X to Stack ptr)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_9A); // TXS (Transfer X to Stack ptr)   $9A  2
        case 0xBA:
            // printf("\tTSX (Transfer Stack ptr to X)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_BA); // TSX (Transfer Stack ptr to X)   $BA  2
        default:
            printf("\tINVALID RMW STACK\n");
            return NULL;
    }
}

Instruction* RMW_register_Opcodes(unsigned char* inst, char extraCycles){
    // Register Instructions
    //   Affect Flags: S Z
    // These instructions are implied mode, have a length of one byte and require
    // two machine cycles.

    switch(inst[0]){
        case 0x8A:
            // printf("\tTXA (Transfer X to A)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_8A); // TXA (Transfer X to A)    $8A
        case 0xAA:
            // printf("\tTAX (Transfer A to X)\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_AA); // TAX (Transfer A to X)    $AA
        case 0xCA:
            // printf("\tDEX (DEcrement X))\n");
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_CA); // DEX (DEcrement X)        $CA
        default:
            printf("\tINVALID RMW REGISTER OPCODE\n");
            return NULL;
    }
}

Instruction* RMW_INC_Opcodes(unsigned char* inst, char extraCycles){
    // INC (INCrement memory)
    //   Affects Flags: S Z

    switch(inst[0]){
        case 0xE6:
            return initInstruction(inst, TYPE_ZERO_PAGE, 5, opcode_E6); // Zero Page     INC $44       $E6  2   5
        case 0xEE:
            return initInstruction(inst, TYPE_ABSOLUTE, 6, opcode_EE); // Absolute      INC $4400     $EE  3   6
        case 0xF6:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 6, opcode_F6); // Zero Page,X   INC $44,X     $F6  2   6
        case 0xFE:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 7, opcode_FE); // Absolute,X    INC $4400,X   $FE  3   7
        default:
            printf("\tINVALID RMW INC OPCODE\n");
            return NULL;
    }
}

Instruction* RMW_DEC_Opcodes(unsigned char* inst, char extraCycles){
    // DEC (DECrement memory)
    //   Affects Flags: S Z
    // Zero Page     DEC $44       $C6  2   5
    // Absolute      DEC $4400     $CE  3   6
    // Zero Page,X   DEC $44,X     $D6  2   6
    // Absolute,X    DEC $4400,X   $DE  3   7

    switch(inst[0]){
        case 0xC6:
            return initInstruction(inst, TYPE_ZERO_PAGE, 5, opcode_C6);
        case 0xCE:
            return initInstruction(inst, TYPE_ABSOLUTE, 6, opcode_CE);
        case 0xD6:
            return initInstruction(inst, TYPE_ZERO_PAGE_X, 6, opcode_D6);
        case 0xDE:
            return initInstruction(inst, TYPE_ABSOLUTE_X, 7, opcode_DE);
        default:
            printf("\tINVALID RMW DEC OPCODE\n");
            return NULL;
    }
}

Instruction* RMW_NOP_Opcodes(unsigned char* inst, char extraCycles){
    switch(inst[0]){
        case 0xEA:
            /*
            // NOP (No OPeration)
            //   Affects Flags: none
            // NOP is used to reserve space for future modifications or effectively REM
            // out existing code.
            // printf("\tofficial NOP\n");
             */
            return initInstruction(inst, TYPE_IMPLIED, 2, opcode_EA); // Implied       NOP           $EA  1   2
        case 0x82:
            // printf("\tRMW IMMEDIATE NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_82);
        case 0xC2:
            // printf("\tRMW IMMEDIATE NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_C2);
        case 0xE2:
            // printf("\tRMW IMMEDIATE NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_E2);
        case 0x1A:
            // printf("\tRMW IMPLIED NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_1A);
        case 0x3A:
            // printf("\tRMW IMPLIED NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_3A);
        case 0x5A:
            // printf("\tRMW IMPLIED NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_5A);
        case 0x7A:
            // printf("\tRMW IMPLIED NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_7A);
        case 0xDA:
            // printf("\tRMW IMPLIED NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_DA);
        case 0xFA:
            // printf("\tRMW IMPLIED NOP Opcode\n");
            return initInstruction(inst, TYPE_IMMEDIATE, 2, opcode_FA);
        default:
            printf("\tINVALID NOP\n");
            return NULL;
    }
}

Instruction* RMW_STP_Opcodes(unsigned char* inst, char extraCycles){
    /*
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
    */

    // printf("\tRMW STP Opcode\n");
    if(inst[0] == 0x02){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_02);
    }
    else if(inst[0] == 0x12){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_12);
    }
    else if(inst[0] == 0x22){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_22);
    }
    else if(inst[0] == 0x32){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_32);
    }
    else if(inst[0] == 0x42){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_42);
    }
    else if(inst[0] == 0x52){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_52);
    }
    else if(inst[0] == 0x62){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_62);
    }
    else if(inst[0] == 0x72){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_72);
    }
    else if(inst[0] == 0x92){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_92);
    }
    else if(inst[0] == 0xB2){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_B2);
    }
    else if(inst[0] == 0xD2){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_D2);
    }
    else if(inst[0] == 0xF2){
        return initInstruction(inst, TYPE_IMPLIED, -1, opcode_F2);
    }
    else{
        printf("\tINVALID STP\n");
    }

    return NULL;
}

Instruction* RMW_SHX_Opcodes(unsigned char* inst, char extraCycles){
    /*
    // SXA (SHX) [XAS]
    // =3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
    // AND X register with the high byte of the target address of the argument
    // + 1. Store the result in memory.

    // M =3D X AND HIGH(arg) + 1

    // Status flags: -

    // Addressing  |Mnemonics  |Opc|Sz | n
    // ------------|-----------|---|---|---
    // Absolute,Y  |SXA arg,Y  |$9E| 3 | 5
     */

    if(inst[0] == 0x9E){
        // printf("\tRMW SHX Opcode\n");
        return initInstruction(inst, TYPE_ABSOLUTE_Y, 5, opcode_9E);
    }

    printf("\tINVALID SHX Opcode\n");
    return NULL;

}


// RMW
Instruction* RMW_Opcodes(unsigned char* inst, char extraCycles){
    if((inst[0] & (BIT_1 | BIT_0)) != BIT_1){
        // ERROR
        return NULL;
    }
    switch(inst[0]){
        case 0x06:
        case 0x0A:
        case 0x0E:
        case 0x16:
        case 0x1E:
            // printf("\tASL (Arithmetic Shift Left)\n");
            return RMW_ASL_Opcodes(inst, extraCycles);
        case 0x2A:
        case 0x26:
        case 0x2E:
        case 0x36:
        case 0x3E:
            // printf("\tROL (ROtate Left)\n");
            return RMW_ROL_Opcodes(inst, extraCycles);
        case 0x46:
        case 0x4A:
        case 0x4E:
        case 0x56:
        case 0x5E:
            // printf("\tLSR (Logical Shift Right)\n");
            return RMW_LSR_Opcodes(inst, extraCycles);
        case 0x66:
        case 0x6A:
        case 0x6E:
        case 0x76:
        case 0x7E:
            // printf("\tROR (ROtate Right)\n");
            return RMW_ROR_Opcodes(inst, extraCycles);
        case 0xA2:
        case 0xA6:
        case 0xAE:
        case 0xB6:
        case 0xBE:
            // printf("\tLDX (LoaD X register)\n");
            return RMW_LDX_Opcodes(inst, extraCycles);
        case 0x86:
        case 0x8E:
        case 0x96:
            // printf("\tSTX (STore X register)\n");
            return RMW_STX_Opcodes(inst, extraCycles);
        case 0x9A:
        case 0xBA:
            // printf("\tRMW Stack Instructions\n");
            return RMW_STACK_Opcodes(inst, extraCycles);
        case 0x8A:
        case 0xAA:
        case 0xCA:
            // printf("\tRMW Register Instructions\n");
            return RMW_register_Opcodes(inst, extraCycles);
        case 0xE6:
        case 0xEE:
        case 0xF6:
        case 0xFE:
            // printf("\tRMW INC Instructions\n");
            return RMW_INC_Opcodes(inst, extraCycles);
        case 0xC6:
        case 0xCE:
        case 0xD6:
        case 0xDE:
            // printf("\tRMW DEC Instructions\n");
            return RMW_DEC_Opcodes(inst, extraCycles);
        case 0xEA:
        case 0xFA:
        case 0xDA:
        case 0x7A:
        case 0x5A:
        case 0x3A:
        case 0x1A:
        case 0xE2:
        case 0xC2:
        case 0x82:
            // printf("\tRMW NOP Instructions\n");
            return RMW_NOP_Opcodes(inst, extraCycles);
        case 0x02:
        case 0x12:
        case 0x22:
        case 0x32:
        case 0x42:
        case 0x52:
        case 0x62:
        case 0x72:
        case 0x92:
        case 0xB2:
        case 0xD2:
        case 0xF2:
            // printf("\tRMW STP Instructions\n");
            return RMW_STP_Opcodes(inst, extraCycles);
        case 0x9E:
            // printf("\tRMW SHX Instructions\n");
            return RMW_SHX_Opcodes(inst, extraCycles);
        default:
            return NULL;
    }
}


Instruction* detectType(unsigned char* inst, char extraCycles){
    unsigned char type = (unsigned char)(inst[0] & (BIT_1 | BIT_0));
    if(type == 0){
        // printf("\tControl instruction opcode\n");
        return controlInstructionOpcodes(inst, extraCycles);
    }
    else if(type == BIT_0){
        // printf("\tALU operation opcode\n");
        return ALUOpcodes(inst, extraCycles);
    }
    else if(type == BIT_1){
        // printf("\tread-modify-write (RMW) and data movement instructions opcode\n");
        return RMW_Opcodes(inst, extraCycles);
    }
    else{
        printf("\tunoficial opcode\n");
        return NULL;
    }
}

unsigned short loadAddress(Instruction* instData, NesCPURegisters* registers, NesRam* ram){
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

unsigned char loadNumberFromRamOrArg(Instruction *instData, NesCPURegisters *registers, NesRam *ram){
    unsigned short address = loadAddress(instData, registers, ram);

    switch(instData->type){
        case TYPE_ACCUMULATOR:
        case TYPE_IMMEDIATE:
        case TYPE_IMPLIED:
        case TYPE_RELATIVE:
        case TYPE_ABSOLUTE:
            return (unsigned char)address;

        case TYPE_INDIRECT:
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

void printfOpcodeSyntax(Instruction* instData){
    printfCharAsHex(instData->opcode);
    if(instData->bytesAmount > 1){
        printf(" ");
        printfCharAsHex(instData->byte2);
    }
    if(instData->bytesAmount > 0){
        printf(" ");
        printfCharAsHex(instData->byte1);
    }
    printf("\n");
}

void printfInstruction(Instruction* instData){
    printf("Opcode: ");
    printfOpcodeSyntax(instData);
    printf("Type: %hhu\nCycles: %hi\n", instData->type, instData->cycles);
}

