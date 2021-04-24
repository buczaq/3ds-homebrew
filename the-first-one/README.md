# Lady in the Dark - 3DS homebrew example

## Building
Simply call `make` :)

## Building .cia file

To build .cia file:

`arm-none-eabi-strip the-first-one.elf`

`../makerom -f cia -o the-first-one.cia -rsf cia.rsf -target d -exefslogo -elf the-first-one.elf -icon the-first-one.smdh -banner ../banner.bin -ignoresign`

## Gameplay

[https://youtu.be/Zc_93zneMGE](https://youtu.be/Zc_93zneMGE)

## Known issues

Sound probably won't play on Citra emulator. However, it works on real hardware ready for homebrew launching. You just need to copy `.3dsx`, `.elf`, `.smdh` files and `audio` directory to the destination where homebrew is read (typically `3ds/` directory on your SD root).
