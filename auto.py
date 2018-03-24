datos = ["void opcode_", "(struct instruction* instData, struct nesRegisters* registers, struct nesRam* ram)"]
extra = '{\n    printf("\\tinstruction %x not implemented", instData->opcode);\n}\n'

i = 3
while i < 256:
	valor = hex(i)[2:]
	if(len(valor) == 1):
		valor = "0"+valor
	print(valor.upper().join(datos)+";")# extra)
	i += 4
