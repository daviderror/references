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

## coding

### hardware --------------------------------------------------
#### module + tb
+ block scheme
+ fsm diagramm
+ git

+ subline
+ code meta (module + tb): `check_syntax`
+ comments meta
+ git meta
+ tcl waveform
+ bash modelsim
+ code clear (module + tb) + deleting all tabs and etc. extra white spaces: `check_syntax`
+ tcl waveform
+ bash modelsim
+ comments
+ doxygen
+ bash modelsim
+ git

#### ip
+ module + tb
+ ila + vio
+ git

#### project
todo



### firmware --------------------------------------------------
+ block diagramm

+ subline
+ code meta
+ comments meta
+ git meta
+ make gdb
+ make cppcheck
+ make misra
+ code clear + deleting all tabs and etc. extra white spaces
+ comments
+ doxygen ??через make?? 
+ make gdb
+ make
+ git

+ lib
+ git

### LKM --------------------------------------------------
+ 

+ subline
+ code meta
+ comments meta
+ git meta
+ make gdb
+ make cppcheck
+ make misra (?)
+ code clear + deleting all tabs and etc. extra white spaces
+ comments
+ doxygen ??через make?? 
+ make gdb
+ make
+ git

+ lib
+ git

### software --------------------------------------------------
+ block diagramm

+ subline
+ raw code
+ make
+ make 
+ posix
+ clear code + deleting all tabs and etc. extra white spaces
+ comments
+ sphinx
+ make
+ gdb
+ git

+ lib
+ git
