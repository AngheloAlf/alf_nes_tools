from __future__ import print_function

text = """<a href="http://www.6502.org/tutorials/6502opcodes.html">src</a>


<a name="ADC">&nbsp;</a>
ADC (ADd with Carry)
  Affects flagsInts: S V Z C
Immediate     ADC #$44      $69  2   2
Zero Page     ADC $44       $65  2   3
Zero Page,X   ADC $44,X     $75  2   4
Absolute      ADC $4400     $6D  3   4
Absolute,X    ADC $4400,X   $7D  3   4+
Absolute,Y    ADC $4400,Y   $79  3   4+
Indirect,X    ADC ($44,X)   $61  2   6
Indirect,Y    ADC ($44),Y   $71  2   5+

+ add 1 cycle if page boundary crossed

ADC results are dependant on the setting of the decimal flag. In decimal
mode, addition is carried out on the assumption that the values involved are
packed BCD (Binary Coded Decimal).

There is no way to add without carry.

<a name="AND">&nbsp;</a>
AND (bitwise AND with accumulator)
  Affects flagsInts: S Z
Immediate     AND #$44      $29  2   2
Zero Page     AND $44       $25  2   3
Zero Page,X   AND $44,X     $35  2   4
Absolute      AND $4400     $2D  3   4
Absolute,X    AND $4400,X   $3D  3   4+
Absolute,Y    AND $4400,Y   $39  3   4+
Indirect,X    AND ($44,X)   $21  2   6
Indirect,Y    AND ($44),Y   $31  2   5+

+ add 1 cycle if page boundary crossed


<a name="ASL">&nbsp;</a>
ASL (Arithmetic Shift Left)
  Affects flagsInts: S Z C
Accumulator   ASL A         $0A  1   2
Zero Page     ASL $44       $06  2   5
Zero Page,X   ASL $44,X     $16  2   6
Absolute      ASL $4400     $0E  3   6
Absolute,X    ASL $4400,X   $1E  3   7

ASL shifts all bits left one position. 0 is shifted into bit 0 and the
original bit 7 is shifted into the Carry.


<a name="BIT">&nbsp;</a>
BIT (test BITs)
  Affects flagsInts: N V Z
Zero Page     BIT $44       $24  2   3
Absolute      BIT $4400     $2C  3   4

BIT sets the Z flag as though the value in the address tested were ANDed
with the accumulator. The S and V flagsInts are set to match bits 7 and 6
respectively in the value stored at the tested address.


Beware: a BIT instruction used in this way as a NOP does have effects: the flagsInts
may be modified, and the read of the absolute address, if it happens to access an
I/O device, may cause an unwanted action.


<a name="BCC">&nbsp;</a> <a name="BCS">&nbsp;</a> <a name="BEQ">&nbsp;</a> <a name="BNE">&nbsp;</a> <a name="BMI">&nbsp;</a> <a name="BPL">&nbsp;</a> <a name="BVC">&nbsp;</a> <a name="BVS">&nbsp;</a> <a name="BRA">&nbsp;</a>
Branch Instructions
  Affect flagsInts: none
All branches are relative mode and have a length of two bytes. Syntax is "Bxx
Displacement" or (better) "Bxx Label". See the notes on the Program Counter for more on
displacements.
Branches are dependant on the status of the flag bits when the op code is
encountered. A branch not taken requires two machine cycles. Add one if the
branch is taken and add one more if the branch crosses a page boundary. 
MNEMONIC                       HEX
BPL (Branch on PLus)           $10
BMI (Branch on MInus)          $30
BVC (Branch on oVerflow Clear) $50
BVS (Branch on oVerflow Set)   $70
BCC (Branch on Carry Clear)    $90
BCS (Branch on Carry Set)      $B0
BNE (Branch on Not Equal)      $D0
BEQ (Branch on EQual)          $F0

There is no BRA (BRanch Always) instruction but it can be easily emulated
by branching on the basis of a known condition. One of the best flagsInts to use for
this purpose is the <a href="#VFLAG">oVerflow</a> which is unchanged
by all but addition and subtraction operations.


<a name="BRK">&nbsp;</a>
BRK (BReaK)
  Affects flagsInts: B
Implied       BRK           $00  1   7

BRK causes a non-maskable interrupt and increments the program counter by
one.  Therefore an <a href="#RTI">RTI</a> will
go to the address of the BRK +2 so that BRK may be used to replace a
two-byte instruction for debugging and the subsequent RTI will be correct.

<a name="CMP">&nbsp;</a>
CMP (CoMPare accumulator) 
  Affects flagsInts: S Z C
Immediate     CMP #$44      $C9  2   2
Zero Page     CMP $44       $C5  2   3
Zero Page,X   CMP $44,X     $D5  2   4
Absolute      CMP $4400     $CD  3   4
Absolute,X    CMP $4400,X   $DD  3   4+
Absolute,Y    CMP $4400,Y   $D9  3   4+
Indirect,X    CMP ($44,X)   $C1  2   6
Indirect,Y    CMP ($44),Y   $D1  2   5+

+ add 1 cycle if page boundary crossed


Compare sets flagsInts as if a subtraction had been carried out. If the value
in the accumulator is equal or greater than the compared value, the Carry will
be set. The equal (Z) and sign (S) flagsInts will be set based on equality or lack
thereof and the sign (i.e. A&gt;=$80) of the accumulator.



<a name="CPX">&nbsp;</a>
CPX (ComPare X register)
  Affects flagsInts: S Z C
Immediate     CPX #$44      $E0  2   2
Zero Page     CPX $44       $E4  2   3
Absolute      CPX $4400     $EC  3   4


Operation and flag results are identical to equivalent mode accumulator <a href="#CMP">CMP</a> ops.

<a name="CPY">&nbsp;</a>
CPY (ComPare Y register)
  Affects flagsInts: S Z C
Immediate     CPY #$44      $C0  2   2
Zero Page     CPY $44       $C4  2   3
Absolute      CPY $4400     $CC  3   4

Operation and flag results are identical to equivalent mode accumulator <a href="#CMP">CMP</a> ops.


<a name="DEC">&nbsp;</a>
DEC (DECrement memory)
  Affects flagsInts: S Z
Zero Page     DEC $44       $C6  2   5
Zero Page,X   DEC $44,X     $D6  2   6
Absolute      DEC $4400     $CE  3   6
Absolute,X    DEC $4400,X   $DE  3   7



<p><a name="EOR">&nbsp;</a>
EOR (bitwise Exclusive OR)
  Affects flagsInts: S Z
Immediate     EOR #$44      $49  2   2
Zero Page     EOR $44       $45  2   3
Zero Page,X   EOR $44,X     $55  2   4
Absolute      EOR $4400     $4D  3   4
Absolute,X    EOR $4400,X   $5D  3   4+
Absolute,Y    EOR $4400,Y   $59  3   4+
Indirect,X    EOR ($44,X)   $41  2   6
Indirect,Y    EOR ($44),Y   $51  2   5+

+ add 1 cycle if page boundary crossed



<a name="CLC">&nbsp;</a> <a name="SEC">&nbsp;</a> <a name="CLD">&nbsp;</a> <a name="SED">&nbsp;</a> <a name="CLI">&nbsp;</a> <a name="SEI">&nbsp;</a> <a name="CLV">&nbsp;</a>
Flag (Processor Status) Instructions
  Affect flagsInts: as noted
These instructions are implied mode, have a length of one byte and require
two machine cycles.
MNEMONIC                       HEX
CLC (CLear Carry)              $18
SEC (SEt Carry)                $38
CLI (CLear Interrupt)          $58
SEI (SEt Interrupt)            $78
CLV (CLear oVerflow)           $B8
CLD (CLear Decimal)            $D8
SED (SEt Decimal)              $F8

Notes:
<p><a name="IFLAG">&nbsp;</a> The Interrupt flag is used to prevent (SEI) or
enable (CLI) maskable interrupts (aka IRQ's). It does not signal the presence or
absence of an interrupt condition. The 6502 will set this flag automatically in
response to an interrupt and restore it to its prior status on completion of the
interrupt service routine. If you want your interrupt service routine to permit
other maskable interrupts, you must clear the I flag in your code.
</p><p><a name="DFLAG">&nbsp;</a> The Decimal flag controls how the 6502 adds and
subtracts. If set, arithmetic is carried out in packed binary coded decimal.
This flag is unchanged by interrupts and is unknown on power-up. The implication
is that a CLD should be included in boot or interrupt coding.
</p><p><a name="VFLAG">&nbsp;</a> The Overflow flag is generally misunderstood and
therefore under-utilised. After an ADC or SBC instruction, the overflow flag
will be set if the twos complement result is less than -128 or greater than
+127, and it will cleared otherwise. In twos complement, $80 through $FF
represents -128 through -1, and $00 through $7F represents 0 through +127.
Thus, after:
</p><pre>  CLC
  LDA #$7F ;   +127
  ADC #$01 ; +   +1
</pre>
the overflow flag is 1 (+127 + +1 = +128), and after:
<pre>  CLC
  LDA #$81 ;   -127
  ADC #$FF ; +   -1
</pre>
the overflow flag is 0 (-127 + -1 = -128). The overflow flag is not
affected by increments, decrements, shifts and logical operations i.e. only
ADC, BIT, CLV, PLP, RTI and SBC affect it. There is no op code to set the
overflow but a BIT test on an RTS instruction will do the trick.
<p>
</p>


<a name="INC">&nbsp;</a>
INC (INCrement memory)
  Affects flagsInts: S Z
Zero Page     INC $44       $E6  2   5
Zero Page,X   INC $44,X     $F6  2   6
Absolute      INC $4400     $EE  3   6
Absolute,X    INC $4400,X   $FE  3   7



<a name="JMP">&nbsp;</a>
JMP (JuMP)
  Affects flagsInts: none
Absolute      JMP $5597     $4C  3   3
Indirect      JMP ($5597)   $6C  3   5

JMP transfers program execution to the following address (absolute) or to
the location contained in the following address (indirect). Note that there is
no carry associated with the indirect jump so: <pre><strong>AN INDIRECT JUMP MUST NEVER USE A
VECTOR BEGINNING ON THE LAST BYTE
OF A PAGE</strong>
For example if address $3000 contains $40, $30FF contains $80, and $3100
contains $50, the result of JMP ($30FF) will be a transfer of control to $4080
rather than $5080 as you intended i.e. the 6502 took the low byte of the address
from $30FF and the high byte from $3000.




<a name="JSR">&nbsp;</a>
JSR (Jump to SubRoutine)
  Affects flagsInts: none
Absolute      JSR $5597     $20  3   6

JSR pushes the address-1 of the next operation on to the stack before
transferring program control to the following address. Subroutines are normally
terminated by a <a href="#RTS">RTS</a> op
code.



<a name="LDA">&nbsp;</a>
LDA (LoaD Accumulator)>
  Affects flagsInts: S Z
Immediate     LDA #$44      $A9  2   2
Zero Page     LDA $44       $A5  2   3
Zero Page,X   LDA $44,X     $B5  2   4
Absolute      LDA $4400     $AD  3   4
Absolute,X    LDA $4400,X   $BD  3   4+
Absolute,Y    LDA $4400,Y   $B9  3   4+
Indirect,X    LDA ($44,X)   $A1  2   6
Indirect,Y    LDA ($44),Y   $B1  2   5+

+ add 1 cycle if page boundary crossed


<a name="LDX">&nbsp;</a>
LDX (LoaD X register)
  Affects flagsInts: S Z
Immediate     LDX #$44      $A2  2   2
Zero Page     LDX $44       $A6  2   3
Zero Page,Y   LDX $44,Y     $B6  2   4
Absolute      LDX $4400     $AE  3   4
Absolute,Y    LDX $4400,Y   $BE  3   4+

+ add 1 cycle if page boundary crossed


<a name="LDY">&nbsp;</a>
LDY (LoaD Y register)
  Affects flagsInts: S Z
Immediate     LDY #$44      $A0  2   2
Zero Page     LDY $44       $A4  2   3
Zero Page,X   LDY $44,X     $B4  2   4
Absolute      LDY $4400     $AC  3   4
Absolute,X    LDY $4400,X   $BC  3   4+

+ add 1 cycle if page boundary crossed



<a name="LSR">&nbsp;</a>
LSR (Logical Shift Right)
  Affects flagsInts: S Z C
Accumulator   LSR A         $4A  1   2
Zero Page     LSR $44       $46  2   5
Zero Page,X   LSR $44,X     $56  2   6
Absolute      LSR $4400     $4E  3   6
Absolute,X    LSR $4400,X   $5E  3   7

LSR shifts all bits right one position. 0 is shifted into bit 7 and the
original bit 0 is shifted into the Carry.


<a name="WRAP">&nbsp;</a>
Wrap-Around
<p>Use caution with indexed zero page operations as they are subject to
wrap-around. For example, if the X register holds $FF and you execute LDA $80,X
you will not access $017F as you might expect; instead you access $7F i.e.
$80-1. This characteristic can be used to advantage but make sure your code is
well commented.
</p><p>
It is possible, however, to access $017F when X = $FF by using the Absolute,X
addressing mode of LDA $80,X. That is, instead of:
</p><pre>
  LDA $80,X    ; ZeroPage,X - the resulting object code is: B5 80
</pre>
which accesses $007F when X=$FF, use:
<pre>
  LDA $0080,X  ; Absolute,X - the resulting object code is: BD 80 00
</pre>
which accesses $017F when X = $FF (a at cost of one additional byte and one
additional cycle). All of the ZeroPage,X and ZeroPage,Y instructions except
STX ZeroPage,Y and STY ZeroPage,X have a corresponding Absolute,X and
Absolute,Y instruction. Unfortunately, a lot of 6502 assemblers don't have an
easy way to force Absolute addressing, i.e. most will assemble a LDA $0080,X
as B5 80.  One way to overcome this is to insert the bytes using the .BYTE
pseudo-op (on some 6502 assemblers this pseudo-op is called DB or DFB,
consult the assembler documentation) as follows:
<pre>
  .BYTE $BD,$80,$00  ; LDA $0080,X (absolute,X addressing mode)
</pre>
The comment is optional, but highly recommended for clarity.
<p>In cases where you are writing code that will be relocated you must consider
wrap-around when assigning dummy values for addresses that will be adjusted.
Both zero and the semi-standard $FFFF should be avoided for dummy labels. The
use of zero or zero page values will result in assembled code with zero page
opcodes when you wanted absolute codes. With $FFFF, the problem is in
addresses+1 as you wrap around to page 0.</p>



<a name="PC">&nbsp;</a>
Program Counter
<p>When the 6502 is ready for the next instruction it increments the program
counter before fetching the instruction. Once it has the op code, it increments
the program counter by the length of the operand, if any. This must be accounted
for when calculating branches or when pushing bytes to create a false return
address (i.e. jump table addresses are made up of addresses-1 when it is
intended to use an RTS rather than a JMP).
</p><p>The program counter is loaded least signifigant byte first. Therefore the
most signifigant byte must be pushed first when creating a false return address.

</p><p>When calculating branches a forward branch of 6 skips the following 6 bytes
so, effectively the program counter points to the address that is 8 bytes beyond
the address of the branch opcode; and a backward branch of $FA (256-6) goes to
an address 4 bytes before the branch instruction.
</p>

<a name="TIMES">&nbsp;</a>
</p><h2>Execution Times</h2>
<p>Op code execution times are measured in machine cycles; one machine cycle
equals one clock cycle. Many instructions require one extra cycle for
execution if a page boundary is crossed; these are indicated by a + following
the time values shown.
</p>


<a name="NOP">&nbsp;</a>
NOP (No OPeration)
  Affects flagsInts: none
Implied       NOP           $EA  1   2

NOP is used to reserve space for future modifications or effectively REM
out existing code.


<a name="ORA">&nbsp;</a>
ORA (bitwise OR with Accumulator)
  Affects flagsInts: S Z
Immediate     ORA #$44      $09  2   2
Zero Page     ORA $44       $05  2   3
Zero Page,X   ORA $44,X     $15  2   4
Absolute      ORA $4400     $0D  3   4
Absolute,X    ORA $4400,X   $1D  3   4+
Absolute,Y    ORA $4400,Y   $19  3   4+
Indirect,X    ORA ($44,X)   $01  2   6
Indirect,Y    ORA ($44),Y   $11  2   5+

+ add 1 cycle if page boundary crossed



<a name="TAX">&nbsp;</a> <a name="TXA">&nbsp;</a> <a name="TAY">&nbsp;</a> <a name="TYA">&nbsp;</a> <a name="INX">&nbsp;</a> <a name="DEX">&nbsp;</a> <a name="INY">&nbsp;</a> <a name="DEY">&nbsp;</a>
Register Instructions
  Affect flagsInts: S Z
These instructions are implied mode, have a length of one byte and require
two machine cycles.
MNEMONIC                 HEX
TAX (Transfer A to X)    $AA
TXA (Transfer X to A)    $8A
DEX (DEcrement X)        $CA
INX (INcrement X)        $E8
TAY (Transfer A to Y)    $A8
TYA (Transfer Y to A)    $98
DEY (DEcrement Y)        $88
INY (INcrement Y)        $C8



<a name="ROL">&nbsp;</a>
ROL (ROtate Left)
  Affects flagsInts: S Z C
Accumulator   ROL A         $2A  1   2
Zero Page     ROL $44       $26  2   5
Zero Page,X   ROL $44,X     $36  2   6
Absolute      ROL $4400     $2E  3   6
Absolute,X    ROL $4400,X   $3E  3   7

ROL shifts all bits left one position. The Carry is shifted into bit 0 and
the original bit 7 is shifted into the Carry.



<a name="ROR">&nbsp;</a>
ROR (ROtate Right)
  Affects flagsInts: S Z C
Accumulator   ROR A         $6A  1   2
Zero Page     ROR $44       $66  2   5
Zero Page,X   ROR $44,X     $76  2   6
Absolute      ROR $4400     $6E  3   6
Absolute,X    ROR $4400,X   $7E  3   7

ROR shifts all bits right one position. The Carry is shifted into bit 7
and the original bit 0 is shifted into the Carry.

<a name="RTI">&nbsp;</a>
RTI (ReTurn from Interrupt)
  Affects flagsInts: all 
Implied       RTI           $40  1   6

RTI retrieves the Processor Status Word (flagsInts) and the Program Counter
from the stack in that order (interrupts push the PC first and then the PSW).
<p>Note that unlike RTS, the return address on the stack is the actual address
rather than the address-1.
</p>


<a name="RTS">&nbsp;</a>
RTS (ReTurn from Subroutine)
Affects flagsInts: none 
Implied       RTS           $60  1   6

RTS pulls the top two bytes off the stack (low byte first) and transfers
program control to that address+1. It is used, as expected, to exit a subroutine
invoked via <a href="#JSR">JSR</a> which
pushed the address-1.



<a name="SBC">&nbsp;</a>
SBC (SuBtract with Carry)
  Affects flagsInts: S V Z C
Immediate     SBC #$44      $E9  2   2
Zero Page     SBC $44       $E5  2   3
Zero Page,X   SBC $44,X     $F5  2   4
Absolute      SBC $4400     $ED  3   4
Absolute,X    SBC $4400,X   $FD  3   4+
Absolute,Y    SBC $4400,Y   $F9  3   4+
Indirect,X    SBC ($44,X)   $E1  2   6
Indirect,Y    SBC ($44),Y   $F1  2   5+

+ add 1 cycle if page boundary crossed

SBC results are dependant on the setting of the decimal flag. In decimal
mode, subtraction is carried out on the assumption that the values involved are
packed BCD (Binary Coded Decimal).
There is no way to subtract without the carry which works as an inverse
borrow. i.e, to subtract you set the carry before the operation. If the carry is
cleared by the operation, it indicates a borrow occurred.

<a name="STA">&nbsp;</a>
STA (STore Accumulator) 
  Affects flagsInts: none
Zero Page     STA $44       $85  2   3
Zero Page,X   STA $44,X     $95  2   4
Absolute      STA $4400     $8D  3   4
Absolute,X    STA $4400,X   $9D  3   5
Absolute,Y    STA $4400,Y   $99  3   5
Indirect,X    STA ($44,X)   $81  2   6
Indirect,Y    STA ($44),Y   $91  2   6

<a name="TXS">&nbsp;</a> <a name="TSX">&nbsp;</a> <a name="PHA">&nbsp;</a> <a name="PLA">&nbsp;</a> <a name="PHP">&nbsp;</a> <a name="PLP">&nbsp;</a> <a name="STACK">&nbsp;</a>
Stack Instructions
These instructions are implied mode, have a length of one byte and require
machine cycles as indicated. The "PuLl" operations are known as "POP" on most
other microprocessors. With the 6502, the stack is always on page one
($100-$1FF) and works top down. 
MNEMONIC                        HEX TIM
TXS (Transfer X to Stack ptr)   $9A  2
TSX (Transfer Stack ptr to X)   $BA  2
PHA (PusH Accumulator)          $48  3
PLA (PuLl Accumulator)          $68  4
PHP (PusH Processor status)     $08  3
PLP (PuLl Processor status)     $28  4


<a name="STX">&nbsp;</a>
STX (STore X register)
Affects flagsInts: none 
Zero Page     STX $44       $86  2   3
Zero Page,Y   STX $44,Y     $96  2   4
Absolute      STX $4400     $8E  3   4


<a name="STY">&nbsp;</a>
STY (STore Y register)
  Affects flagsInts: none
Zero Page     STY $44       $84  2   3
Zero Page,X   STY $44,X     $94  2   4
Absolute      STY $4400     $8C  3   4

"""


text2 = ""
lista = []

for i in text.split("\n"):
    if "$" in i:
        if i.find("  ") == -1:
            continue
        if i[:2] == "  ":
            continue
        text2+= i+"\n"
        lista.append(i)

branchsInts = ["$10", "$30", "$50", "$70", "$90", "$B0", "$D0", "$F0"]
flagsInts = ["$18", "$38", "$58", "$78", "$B8", "$D8", "$F8"]
registersInts = ["$AA", "$8A", "$CA", "$E8", "$A8", "$98", "$88", "$C8"]

# print(text2)
# print(len(lista))
ultimateList = []
for j in lista:
    # print("-------------------")
    k = j.split(" ")
    opcode = ""
    length = 0
    tim = 0
    sintax = ""
    mode = ""
    if("$" in k[-6]):
        # print(k[-6], k)

        opcode = k[-6]
        tim = k[-1]
        length = k[-4]
        coso = 0
        for x in k[-7::-1]:
            if coso >= 0 and coso <= 1:
                if x == "":
                    if coso == 1:
                        coso = 2
                    continue
                coso = 1
                if sintax == "":
                    sintax = x
                else:
                    sintax = x + " " + sintax
            if coso >= 2:
                if x == "":
                    continue
                if mode == "":
                    mode = x
                else:
                    mode = x + " " + mode
            # print(x)
    elif "$" in k[-1]:
        # print(k[-1], j)
        opcode = k[-1]
        sintax = k[0]
        # mode = j[5:j.find(")")]
        if opcode in branchsInts:
          mode = "Relative"
          tim = "2"
          length = "2"
        elif opcode in flagsInts or opcode in registersInts:
          mode = "Implied"
          tim = "2"
          length = "1"
        else:
          mode = ""
    elif "$" in k[-3]:
        # print(k[-3], j)
        opcode = k[-3]
        tim = k[-1]
        sintax = k[0]
        if opcode in branchsInts:
          mode = "Relative"
          tim = "2"
          length = "2"
        elif opcode in flagsInts or opcode in registersInts:
          mode = "Implied"
          tim = "2"
          length = "1"
        else:
          mode = ""
    else:
        print(k)
        continue
    ultimateList.append((opcode, length, tim, sintax, mode))

ultimateList.sort()
modes = dict()
for i in ultimateList:
  if i[4] not in modes:
    modes[i[4]] = dict()
  if i[1] not in modes[i[4]]:
    modes[i[4]][i[1]] = list()
  modes[i[4]][i[1]].append(i[0])

for j in modes:
  if(len(modes[j]) == 1):
    print(j, " - ", modes[j])

print("-"*10)
for j in modes:
  if(len(modes[j]) > 1):
    print(j)
    for k in modes[j]:
      print("\t", k, modes[j][k])
# types = set()
# for i in ultimateList:
#     types.add(i[-1])
#     cosote = int(i[0][1:], 16)
#     if "{0:b}".format(cosote)[-2:] == "11":
#         print(cosote)
         
    # print("{0:b}".format(cosote)[-2:])
