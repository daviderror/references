## Hardware
1. circuitry
2. PCB layout
3. PCB
4. frame

## FPGA
1. rtl <- tb <- script
2. ip <- tb/test??
3. db_wrapper <- bd
4. top module
5. pin constraints
6. time constraints
7. project recover files
8. gitignore

## Firmware/Software
1. Botloader
2. u-boot
3. kernel config
4. ip/devices/periph drivers <- test
5. app <- test
6. gitignore

--------------------------------------------------

## coding

### hardware
#### module + tb
0.  block scheme
1.  fsm diagramm

0.  subline
1.  meto code (module + tb): `check_syntax`
2.  tcl waveform
3.  bash
4.  modelsim
5.  clear code (module + tb) + deleting all tabs and etc. extra white spaces: `check_syntax`
6.  tcl waveform
7.  modelsim
8.  comments
9.  sphinx
10. git

#### ip
0. module + tb
1. ila + vio
2. git

#### project
todo


### firmware
### LKM

### software
0.  block scheme

0.  subline
1.  raw code
2.  make
3.  gdb
4.  posix
5.  clear code + deleting all tabs and etc. extra white spaces
6.  comments
7.  sphinx
8.  make
9. gdb
10. git

0. lib
1. git

0. app

