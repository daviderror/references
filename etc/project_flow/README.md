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
скорость, атрибуты, асёрты

+ jira

#### module + tb
+ block scheme
+ fsm diagramm
+ gitignore
+ git

+ subline
+ code meta (module + tb): `check_syntax`
+ comments meta
+ gitignore
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
+ gitignore
+ git

#### project
todo



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
+ code clear + deleting all tabs and etc. extra white spaces
+ comments
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
+ gitignore
+ git meta
+ gdb
+ make cppcheck
+ make misra
+ code clear + deleting all tabs and etc. extra white spaces
+ comments
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
+ clear code + deleting all tabs and etc. extra white spaces
+ comments
+ make doxygen
+ gdb
+ make realese
+ gitignore
+ git

+ lib
+ gitignore
+ git
