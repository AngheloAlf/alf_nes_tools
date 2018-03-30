//
// Created by anghelo on 25-02-18.
//

#ifndef ALF_NES_TOOLS_INSTCALLBACK_H
#define ALF_NES_TOOLS_INSTCALLBACK_H

#include "instructions.h"
#include "cpu.h"
#include "ram.h"

struct instruction;
struct nesRegisters;
struct nesRam;


/*
return values:
    retVal > 0: cycles of instruction
    retVal == 0: not implemented
    retVal < 0: error code

errors codes:
    -1: not implemented
    -2: writeOnReadOnly
    -3:
    -4:
    -5: mapper not implemented
    -6: can't read rom
    -7: can't read save
    -8: size of save less than expected
    -9: wrong implementation of mapper

*/


// Control instructions
int opcode_00(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_04(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_08(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_0C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_10(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_14(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_18(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_1C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_20(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_24(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_28(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_2C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_30(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_34(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_38(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_3C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_40(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_44(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_48(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_4C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_50(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_54(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_58(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_5C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_60(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_64(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_68(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_6C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_70(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_74(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_78(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_7C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_80(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_84(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_88(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_8C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_90(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_94(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_98(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_9C(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_AC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_BC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_CC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_DC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_EC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F0(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F4(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F8(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_FC(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);


// ALU opcodes
int opcode_01(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_05(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_09(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_0D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_11(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_15(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_19(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_1D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_21(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_25(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_29(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_2D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_31(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_35(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_39(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_3D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_41(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_45(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_49(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_4D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_51(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_55(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_59(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_5D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_61(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_65(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_69(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_6D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_71(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_75(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_79(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_7D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_81(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_85(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_89(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_8D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_91(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_95(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_99(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_9D(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_AD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_BD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_CD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_DD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_ED(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F1(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F5(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F9(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_FD(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);


// RMW opcodes
int opcode_02(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_06(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_0A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_0E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_12(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_16(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_1A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_1E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_22(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_26(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_2A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_2E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_32(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_36(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_3A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_3E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_42(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_46(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_4A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_4E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_52(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_56(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_5A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_5E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_62(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_66(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_6A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_6E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_72(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_76(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_7A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_7E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_82(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_86(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_8A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_8E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_92(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_96(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_9A(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_9E(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_AA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_AE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_BA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_BE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_CA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_CE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_DA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_DE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_EA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_EE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F2(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F6(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_FA(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_FE(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);


// unofficial opcodes
int opcode_03(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_07(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_0B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_0F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_13(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_17(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_1B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_1F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_23(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_27(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_2B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_2F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_33(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_37(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_3B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_3F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_43(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_47(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_4B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_4F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_53(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_57(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_5B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_5F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_63(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_67(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_6B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_6F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_73(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_77(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_7B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_7F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_83(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_87(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_8B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_8F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_93(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_97(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_9B(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_9F(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_A7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_AB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_AF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_B7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_BB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_BF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_C7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_CB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_CF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_D7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_DB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_DF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_E7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_EB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_EF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F3(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_F7(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_FB(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);
int opcode_FF(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram);

#endif //ALF_NES_TOOLS_INSTCALLBACK_H
