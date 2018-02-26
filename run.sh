#!/usr/bin/env bash
echo make clean
make clean
echo make
make
if [[ $? == 0 ]]; then
	echo "main"
	./out/main roms/lesson3.nes -printfInst
fi
