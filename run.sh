#!/usr/bin/env bash
echo make
make
if [[ $? == 0 ]]; then
	echo "main"
	./out/main roms/smb.nes
fi
