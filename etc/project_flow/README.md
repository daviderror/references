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
скорость, атрибуты, асёрты, пайплайн, фанаут, synopsys translate_off

+ jira

#### module and tb
+ fsm diagramm
+ code meta (module and tb): `check_syntax`
+ comments meta
+ tcl waveform
+ bash modelsim
+ gitignore
+ git
+ code clear (module and tb) and deleting all tabs and etc. extra white spaces: `check_syntax`
+ doxygen comments (module and tb)
+ git

#### ip
+ block scheme
+ module and tb
+ ila and vio
+ gitignore
+ firmware/LKM driver and shell test
+ git

#### project
+ creatoin
+ tcl pins
+ tcl timings
+ tcl recovery


### firmware --------------------------------------------------
скорость, атрибуты, барьеры, асёрты

+ jira

+ block diagramm

+ subline
+ code meta
+ comments meta
+ gitignore
+ git meta
+ gdb
+ make cppcheck
+ make misra
+ code clear and deleting all tabs and etc. extra white spaces
+ doxygen comments
+ make doxygen
+ gdb
+ make realese
+ git

+ lib
+ gitignore
+ git

### LKM --------------------------------------------------
скорость, атрибуты, барьеры, асёрты

+ jira

+ subline
+ code meta
+ comments meta
+ make gcc
+ make insmod, rmmod, mknod, rm nod, chmod
+ gitignore
+ git meta
+ gdb
+ bash test
+ cppcheck
+ misra
+ code clear and deleting all tabs and etc. extra white spaces
+ doxygen comments
+ make doxygen
+ gdb
+ make realese
+ gitignore
+ git

+ lib
+ git

### software --------------------------------------------------
скорость, атрибуты, барьеры, асёрты

+ jira

+ block diagramm

+ subline
+ code meta
+ comments meta
+ gitignore
+ git meta
+ gdb
+ make cppcheck
+ make misra
+ make posix
+ clear code and deleting all tabs and etc. extra white spaces
+ doxygen comments
+ make doxygen
+ gdb
+ make realese
+ gitignore
+ git

+ lib
+ gitignore
+ git
