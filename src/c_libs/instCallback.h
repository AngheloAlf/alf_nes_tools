//
// Created by anghelo on 25-02-18.
//

#ifndef ALF_NES_TOOLS_INSTCALLBACK_H
#define ALF_NES_TOOLS_INSTCALLBACK_H

#include "instructions.h"
#include "cpu.h"
#include "ram.h"

struct instruction;
typedef struct instruction Instruction;
struct nesRegisters;
typedef struct nesRegisters NesCPURegisters;
struct nesRam;

/*
return values:
    retVal > 0: cycles of instruction
    retVal == 0: not implemented
    retVal < 0: error code
*/


// Control instructions
int opcode_00(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_04(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_08(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_0C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_10(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_14(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_18(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_1C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_20(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_24(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_28(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_2C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_30(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_34(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_38(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_3C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_40(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_44(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_48(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_4C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_50(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_54(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_58(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_5C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_60(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_64(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_68(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_6C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_70(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_74(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_78(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_7C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_80(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_84(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_88(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_8C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_90(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_94(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_98(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_9C(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A0(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A4(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A8(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_AC(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B0(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B4(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B8(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_BC(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C0(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C4(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C8(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_CC(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D0(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D4(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D8(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_DC(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E0(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E4(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E8(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_EC(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F0(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F4(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F8(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_FC(Instruction* instData, NesCPURegisters* registers, NesRam* ram);


// ALU opcodes
int opcode_01(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_05(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_09(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_0D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_11(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_15(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_19(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_1D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_21(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_25(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_29(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_2D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_31(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_35(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_39(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_3D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_41(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_45(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_49(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_4D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_51(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_55(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_59(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_5D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_61(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_65(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_69(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_6D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_71(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_75(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_79(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_7D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_81(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_85(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_89(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_8D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_91(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_95(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_99(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_9D(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A1(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A5(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A9(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_AD(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B1(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B5(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B9(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_BD(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C1(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C5(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C9(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_CD(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D1(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D5(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D9(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_DD(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E1(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E5(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E9(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_ED(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F1(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F5(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F9(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_FD(Instruction* instData, NesCPURegisters* registers, NesRam* ram);


// RMW opcodes
int opcode_02(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_06(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_0A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_0E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_12(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_16(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_1A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_1E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_22(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_26(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_2A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_2E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_32(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_36(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_3A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_3E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_42(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_46(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_4A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_4E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_52(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_56(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_5A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_5E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_62(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_66(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_6A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_6E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_72(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_76(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_7A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_7E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_82(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_86(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_8A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_8E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_92(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_96(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_9A(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_9E(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A2(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A6(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_AA(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_AE(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B2(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B6(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_BA(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_BE(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C2(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C6(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_CA(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_CE(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D2(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D6(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_DA(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_DE(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E2(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E6(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_EA(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_EE(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F2(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F6(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_FA(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_FE(Instruction* instData, NesCPURegisters* registers, NesRam* ram);


// unofficial opcodes
int opcode_03(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_07(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_0B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_0F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_13(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_17(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_1B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_1F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_23(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_27(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_2B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_2F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_33(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_37(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_3B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_3F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_43(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_47(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_4B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_4F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_53(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_57(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_5B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_5F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_63(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_67(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_6B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_6F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_73(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_77(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_7B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_7F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_83(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_87(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_8B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_8F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_93(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_97(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_9B(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_9F(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A3(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_A7(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_AB(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_AF(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B3(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_B7(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_BB(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_BF(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C3(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_C7(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_CB(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_CF(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D3(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_D7(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_DB(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_DF(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E3(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_E7(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_EB(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_EF(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F3(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_F7(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_FB(Instruction* instData, NesCPURegisters* registers, NesRam* ram);
int opcode_FF(Instruction* instData, NesCPURegisters* registers, NesRam* ram);

#endif //ALF_NES_TOOLS_INSTCALLBACK_H
