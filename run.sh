#!/usr/bin/env bash
echo make clean
make clean
echo make
make
if [[ $? == 0 ]]; then
	echo "main"
	if [[ $1 == "" ]]; then
		./out/main roms/lesson3.nes -printfInst
	else
		./out/main $1 $2
	fi
fi
