from __future__ import print_function

text = """AAC (ANC) [ANC]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND byte with accumulator. If result is negative then carry is set.
Status flags: N,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Immediate   |AAC #arg   |$0B| 2 | 2
Immediate   |AAC #arg   |$2B| 2 | 2


AAX (SAX) [AXS]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND X register with accumulator and store result in memory. Status
flags: N,Z

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |AAX arg    |$87| 2 | 3
Zero Page,Y |AAX arg,Y  |$97| 2 | 4
(Indirect,X)|AAX (arg,X)|$83| 2 | 6
Absolute    |AAX arg    |$8F| 3 | 4


ARR (ARR) [ARR]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND byte with accumulator, then rotate one bit right in accu-mulator and
check bit 5 and 6:
If both bits are 1: set C, clear V.
If both bits are 0: clear C and V.
If only bit 5 is 1: set V, clear C.
If only bit 6 is 1: set C and V.
Status flags: N,V,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Immediate   |ARR #arg   |$6B| 2 | 2


ASR (ASR) [ALR]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND byte with accumulator, then shift right one bit in accumu-lator.
Status flags: N,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Immediate   |ASR #arg   |$4B| 2 | 2


ATX (LXA) [OAL]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND byte with accumulator, then transfer accumulator to X register.
Status flags: N,Z

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Immediate   |ATX #arg   |$AB| 2 | 2


AXA (SHA) [AXA]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND X register with accumulator then AND result with 7 and store in
memory. Status flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Absolute,Y  |AXA arg,Y  |$9F| 3 | 5
(Indirect),Y|AXA arg    |$93| 2 | 6


AXS (SBX) [SAX]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND X register with accumulator and store result in X regis-ter, then
subtract byte from X register (without borrow).
Status flags: N,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Immediate   |AXS #arg   |$CB| 2 | 2


DCP (DCP) [DCM]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Subtract 1 from memory (without borrow).
Status flags: C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |DCP arg    |$C7| 2 | 5
Zero Page,X |DCP arg,X  |$D7| 2 | 6
Absolute    |DCP arg    |$CF| 3 | 6
Absolute,X  |DCP arg,X  |$DF| 3 | 7
Absolute,Y  |DCP arg,Y  |$DB| 3 | 7
(Indirect,X)|DCP (arg,X)|$C3| 2 | 8
(Indirect),Y|DCP (arg),Y|$D3| 2 | 8



DOP (NOP) [SKB]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
No operation (double NOP). The argument has no signifi-cance. Status
flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |DOP arg    |$04| 2 | 3
Zero Page,X |DOP arg,X  |$14| 2 | 4
Zero Page,X |DOP arg,X  |$34| 2 | 4
Zero Page   |DOP arg    |$44| 2 | 3
Zero Page,X |DOP arg,X  |$54| 2 | 4
Zero Page   |DOP arg    |$64| 2 | 3
Zero Page,X |DOP arg,X  |$74| 2 | 4
Immediate   |DOP #arg   |$80| 2 | 2
Immediate   |DOP #arg   |$82| 2 | 2
Immediate   |DOP #arg   |$89| 2 | 2
Immediate   |DOP #arg   |$C2| 2 | 2
Zero Page,X |DOP arg,X  |$D4| 2 | 4
Immediate   |DOP #arg   |$E2| 2 | 2
Zero Page,X |DOP arg,X  |$F4| 2 | 4


ISC (ISB) [INS]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Increase memory by one, then subtract memory from accu-mulator (with
borrow). Status flags: N,V,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |ISC arg    |$E7| 2 | 5
Zero Page,X |ISC arg,X  |$F7| 2 | 6
Absolute    |ISC arg    |$EF| 3 | 6
Absolute,X  |ISC arg,X  |$FF| 3 | 7
Absolute,Y  |ISC arg,Y  |$FB| 3 | 7
(Indirect,X)|ISC (arg,X)|$E3| 2 | 8
(Indirect),Y|ISC (arg),Y|$F3| 2 | 8


KIL (JAM) [HLT]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Stop program counter (processor lock up).
Status flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Implied     |KIL        |$02| 1 | -
Implied     |KIL        |$12| 1 | -
Implied     |KIL        |$22| 1 | -
Implied     |KIL        |$32| 1 | -
Implied     |KIL        |$42| 1 | -
Implied     |KIL        |$52| 1 | -
Implied     |KIL        |$62| 1 | -
Implied     |KIL        |$72| 1 | -
Implied     |KIL        |$92| 1 | -
Implied     |KIL        |$B2| 1 | -
Implied     |KIL        |$D2| 1 | -
Implied     |KIL        |$F2| 1 | -


LAR (LAE) [LAS]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND memory with stack pointer, transfer result to accu-mulator, X
register and stack pointer.
Status flags: N,Z

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Absolute,Y  |LAR arg,Y  |$BB| 3 | 4 *


LAX (LAX) [LAX]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Load accumulator and X register with memory.
Status flags: N,Z

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |LAX arg    |$A7| 2 | 3
Zero Page,Y |LAX arg,Y  |$B7| 2 | 4
Absolute    |LAX arg    |$AF| 3 | 4
Absolute,Y  |LAX arg,Y  |$BF| 3 | 4 *
(Indirect,X)|LAX (arg,X)|$A3| 2 | 6
(Indirect),Y|LAX (arg),Y|$B3| 2 | 5 *


NOP (NOP) [NOP]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
No operation
Status flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Implied     |NOP        |$1A| 1 | 2
Implied     |NOP        |$3A| 1 | 2
Implied     |NOP        |$5A| 1 | 2
Implied     |NOP        |$7A| 1 | 2
Implied     |NOP        |$DA| 1 | 2
Implied     |NOP        |$FA| 1 | 2


RLA (RLA) [RLA]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Rotate one bit left in memory, then AND accumulator with memory. Status
flags: N,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |RLA arg    |$27| 2 | 5
Zero Page,X |RLA arg,X  |$37| 2 | 6
Absolute    |RLA arg    |$2F| 3 | 6
Absolute,X  |RLA arg,X  |$3F| 3 | 7
Absolute,Y  |RLA arg,Y  |$3B| 3 | 7
(Indirect,X)|RLA (arg,X)|$23| 2 | 8
(Indirect),Y|RLA (arg),Y|$33| 2 | 8


RRA (RRA) [RRA]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Rotate one bit right in memory, then add memory to accumulator (with
carry).

Status flags: N,V,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |RRA arg    |$67| 2 | 5
Zero Page,X |RRA arg,X  |$77| 2 | 6
Absolute    |RRA arg    |$6F| 3 | 6
Absolute,X  |RRA arg,X  |$7F| 3 | 7
Absolute,Y  |RRA arg,Y  |$7B| 3 | 7
(Indirect,X)|RRA (arg,X)|$63| 2 | 8
(Indirect),Y|RRA (arg),Y|$73| 2 | 8


SBC (SBC) [SBC]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
The same as the legal opcode $E9 (SBC #byte)

Status flags: N,V,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Immediate   |SBC #byte  |$EB| 2 | 2


SLO (SLO) [ASO]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Shift left one bit in memory, then OR accumulator with memory. =

Status flags: N,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |SLO arg    |$07| 2 | 5
Zero Page,X |SLO arg,X  |$17| 2 | 6
Absolute    |SLO arg    |$0F| 3 | 6
Absolute,X  |SLO arg,X  |$1F| 3 | 7
Absolute,Y  |SLO arg,Y  |$1B| 3 | 7
(Indirect,X)|SLO (arg,X)|$03| 2 | 8
(Indirect),Y|SLO (arg),Y|$13| 2 | 8


SRE (SRE) [LSE]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Shift right one bit in memory, then EOR accumulator with memory. Status
flags: N,Z,C

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Zero Page   |SRE arg    |$47| 2 | 5
Zero Page,X |SRE arg,X  |$57| 2 | 6
Absolute    |SRE arg    |$4F| 3 | 6
Absolute,X  |SRE arg,X  |$5F| 3 | 7
Absolute,Y  |SRE arg,Y  |$5B| 3 | 7
(Indirect,X)|SRE (arg,X)|$43| 2 | 8
(Indirect),Y|SRE (arg),Y|$53| 2 | 8


SXA (SHX) [XAS]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND X register with the high byte of the target address of the argument
+ 1. Store the result in memory.

M =3D X AND HIGH(arg) + 1

Status flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Absolute,Y  |SXA arg,Y  |$9E| 3 | 5


SYA (SHY) [SAY]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND Y register with the high byte of the target address of the argument
+ 1. Store the result in memory.

M =3D Y AND HIGH(arg) + 1

Status flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Absolute,X  |SYA arg,X  |$9C| 3 | 5


TOP (NOP) [SKW]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
No operation (tripple NOP). The argument has no signifi-cance. Status
flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Absolute    |TOP arg    |$0C| 3 | 4
Absolute,X  |TOP arg,X  |$1C| 3 | 4 *
Absolute,X  |TOP arg,X  |$3C| 3 | 4 *
Absolute,X  |TOP arg,X  |$5C| 3 | 4 *
Absolute,X  |TOP arg,X  |$7C| 3 | 4 *
Absolute,X  |TOP arg,X  |$DC| 3 | 4 *
Absolute,X  |TOP arg,X  |$FC| 3 | 4 *


XAA (ANE) [XAA]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
Exact operation unknown. Read the referenced documents for more
information and observations.

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Immediate   |XAA #arg   |$8B| 2 | 2


XAS (SHS) [TAS]
=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D=3D
AND X register with accumulator and store result in stack pointer, then
AND stack pointer with the high byte of the target address of the
argument + 1. Store result in memory.

S =3D X AND A, M =3D S AND HIGH(arg) + 1

Status flags: -

Addressing  |Mnemonics  |Opc|Sz | n
------------|-----------|---|---|---
Absolute,Y  |XAS arg,Y  |$9B| 3 | 5"""

datos = dict()
modos = dict()

for i in text.split("\n"):
	if "$" in i and "|" in i:
		#print(len(i.split()), i)
		# print(i)

		j = i.replace("|", " ").split()
		# print(j)
		numero = -1
		if j[-1] == "*":
			tim = j[-2]+j[-1]
			numero = -2
		else:
			tim = j[-1]
		size = j[numero-1]
		opcode = j[numero-2]
		# print(opcode)
		if len(j) == 5:
			name = j[numero-3]
			mode = " ".join(j[:numero-3])
		else:
			name = j[numero-4]
			mode = " ".join(j[:numero-4])

		datos[opcode] = {"mode": mode, "size": size, "name": name, "tim":tim}
		if mode not in modos:
			modos[mode] = dict()
		if size not in modos[mode]:
			modos[mode][size] = list()
		modos[mode][size].append(opcode)

for k in modos:
	if len(modos[k]) == 1:
		print(k, " - ", modos[k])
		
for k in modos:
	if len(modos[k]) > 1:
		print(k)
		for otro in modos[k]:
			print("\t", otro, modos[k][otro])

