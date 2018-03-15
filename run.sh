#!/usr/bin/env bash
echo make clean
make clean
echo make
make
if [[ $? == 0 ]]; then
	echo "main"
    if [[ $1 == "" ]]; then
        ./out/main roms/smb.nes -printfChr
	else
        ./out/main $1 $2 $3 $4 $5 $6 $7 $8 $9
    fi
fi
