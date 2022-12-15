# magus
+ [schedule](#schedule)
+ [fpga](#fpga)
+ [firmware](#firmware)
+ [software](#software)
+ [linux](#linux)
+ [devopps](#devopps)




## schedule
```
magus --+-- fpga
        |
        +-- firmware
        |
        +-- software
        |
        +-- linux
        |
        +-- devopps
```

## languages

| profesional          | added                 | just to help           |
| :---                 | :---                  | :---                   |
| SystemVerilog (FPGA) | chisel                | tcl (Vivado, Modelsim) |
| C (firmware, LKM)    | asm (firmware)        | yaml (CI/CD, Docker)   |
| Python (software)    | C++ (linux userspace) | bash (linux adm)       |


## fpga

| aprentice             | master              | adept         |
| :---                  | :---                | :---          |
| ~~v~~ivado >          | power supply        | fpga_3 >!     |
| modelsim >!           | oscilloscopes       |               |
| ~~s~~ystemverilog >   | bandwidth           |               |
| FPGA arch >           | chose fpga          |               |
| Harris                | fpga_2 >            |               |
| fpga_1 >              | signal gen          |               |
| scheme reading        | race conditions     |               |
| ~~m~~etastability     | tcl                 |               |
| crossing clock domens |                     |               |



| vivado             | fpga_1                 | fpga_2                  | modelsim | systemverilog     | fpga_3 | FPGA arch     |
| :---               | :---                   | :---                    | :---     | :---              |:---    |:---           |
| SoC burning        | counter                | 1G (PHY,LL,NL,TL)       |          | stdlib            |        | LUT           |
| FPGA burning       | fifo (sync, async)     | 10G (PHY,LL,NL,TL)      |          | primitives        |        | MIO           |
| VIO                | clockmeter             | PCIE                    |          | modules           |        | EMIO          |
| ILA                | piso                   | axi (full)              |          | fsm               |        | BRAM          |
| Floar planning     | sipo                   | DDR3                    |          | tb                |        | DSP           |
| Schems             | gray counter           | ARM core                |          | interrupts        |        | clock dom     |
| tcl                | single port bram       | 40G (PHY,LL,NL,TL)      |          | block diagrms     |        | ...??         |
| BD                 | dualport bram          | DMA                     |          | fsm diagramms     |        | отлч семейств |
| rebulding          | true dual bram         | 100G (PHY,LL,NL,TL)     |          | fanout            |        |               |
| IPs                | uart                   | mailbox                 |          | piplining         |        |               |
| compilation        | i2c                    | JESD                    |          | fixed-point       |        |               |
| optimization       | spi                    | ADC                     |          |                   |        |               |
| pin constrs        | timer                  | DAC                     |          |                   |        |               |
| time constrs       | random generator       | HyperRAM                |          |                   |        |               |
| ecoflow            | gpio                   | NIC                     |          |                   |        |               |
| physcl constrs     | axi (lite,stream)      | SDRAM                   |          |                   |        |               |
|                    | primitives             | DDR4                    |          |                   |        |               |
|                    | serdes                 | SSRAM                   |          |                   |        |               |




## firmware

| aprentice          | master                | adept |
| :---               | :---                  | :---  |
| SDK >!             | firm_2                |       |
| C >!               | timings               |       |
| firm_1 >           | logix anlz            |       |
| ARM arch           | chose device          |       |
| C libs             | race conditions       |       |
| schemes            | ipc (openAMP)         |       |
| FreeRTOS >         | deadlocks             |       |
| make               | resourc mangment      |       |
| gcc                | asm                   |       |
| gdb                |                       |       |
| compilatioin       |                       |       |
| doxygen            | own C compilator      |       |
| cppcheck           |                       |       |
|                    |                       |       |
| optimizatiom       |                       |       |
|                    |                       |       |
| cross-compilng     |                       |       |


| SDK  | C               | firm_1                          | firm_2             | stndln drv     | PS         | PS   | devces     | FreeRTOS     |
| :--- | :---            | :---                            | :---               | :---           | :---       | :--- |  :---      |  :---        |
|      | std lib         | bootloader (AVR,Zynq,MB)        | 1G (NL,TL,AL)      | PS >>          | spi        |      | led        | tasks        |
|      | prgrm strct     | u-boot                          | 10G (NL,TL,AL)     | PL >>          | i2c        |      | button     | button       |
|      | metprgrmmng     | stndln drv (AVR,Zynq,MB) >>     | bluetooth          | my_PL >>!      | timers     |      |            |              |
|      | optmizatiom     |                                 | wi-fi              | devces >>!     | gpio       |      |            |              |
|      | fixed point     | lwip                            | micro-services     |                | uart       |      |            |              |
|      | non std lib     |                                 | MQTT               |                | EEPROM     |      |            |              |
|      | misra           |                                 | FTP                |                |            |      |            |              |
|      | posix           | atmega8a_clock                  | HTTPS              |                |            |      |            |              |
|      | ~~s~~ockets     | more AVR apps!                  | DNS                |                |            |      |            |              |
|      | atomic          | more Zynq apps!                 | OPC UA             |                |            |      |            |              |
|      | гонка сигналов  | more Zynq network apps!         |                    |                |            |      |            |              |
|      | FSM             |                                 |                    |                |            |      |            |              |
|      | #include ".c"   |                                 |                    |                |            |      |            |              |
|      | барьеры памямти |                                 |                    |                |            |      |            |              |
|      | атрибуты        |                                 |                    |                |            |      |            |              |
|      | асёрты          |                                 |                    |                |            |      |            |              |
|      | интрисики       |                                 |                    |                |            |      |            |              |
|      |                 |                                 |                    |                |            |      |            |              |


## linux

| aprentice          | master      | adept |
| :---               | :---        | :---  |
| eclipse            | timings     |       |
| C++ >              | ~~y~~octo > |       |
| LKM drv >          | ebpf        |       |
| linux arch         | ubus        |       |
| g++                | modbus      |       |
| multithreading     |             |       |
| multiprocesing     |             |       |
| make               |             |       |
| compilatioin       |             |       |
| optimizatiom       |             |       |
| C++ libs           |             |       |
| FHS                |             |       |
| regex              |             |       |


| LKM drv        | yocto         |
| :---           | :---          |
| PS >>          | ~~peta~~linux |
| PL >>          | u-boot        |
| my_PL >>!      | BSP           |
| devces >>!     | devicetree    |
|                | yocto         |

zynq7000_warehouse

## software

| aprentice          | master   | adept |
| :---               | :---     | :---  |
| subline            |          |       |
| python             | yaml     |       |
| base algorithms    |          |       |
| base data str      |          |       |
| block schem        |          |       |
| design patterns    |          |       |


| ?    | ?    | soft_1         | 1G (AL)  |
| :--- | :--- | :---           | :---     |
|      |      | 1G (AL) >>     | MQTT     |
|      |      | soccets        | HTTPS    |
|      |      | TCP server     | FTP      |
|      |      | UDP server     | DNS      |
|      |      | ssh            |          |


## devopps

| aprentice   | master            | adept           |
| :---        | :---              | :---            |
| ~~gi~~t_1 > | git_2 >           |                 |
| ~~d~~ocker  | remote conect     |                 |
| jira        | agile             |                 |
| qemu        | azure             |                 |
| github      | confluence        |                 |
| linux adm > |                   |                 |
| bash        |                   |                 |
| eng interm  | eng up-interm     | eng advance     |


| git_1             | git_2          | linux adm     |
| :---              | :---           | :---          |
| ~~cl~~one         | rebase         | ssh           |
| ~~pu~~ll          | chery pick     | bios          |
| ~~pu~~sh          | conflicts      | grub          |
| ~~ad~~d           | submodules     | тчка встн     |
| ~~co~~mmit        | reset          | fops arch     |
| ~~br~~anch        | .git           |               |
| ~~gi~~tignore     | diff           |               |
| ~~ch~~eckout      | trics          |               |
| ~~sw~~itch        | squash         |               |
| ~~co~~nfig        | aliases        |               |
| ~~st~~atus        | log            |               |
| ~~fe~~tch         |                |               |
| ~~me~~rge         |                |               |


## todo

c++11, c++14, C++17, hft, C++ code timings, json, monit


## current_plan

01.09.22 - 30.11.22

english: 09:00 - 10:00 proffesional listening 
work   : 10:00 - 04:00 
pet    : 04:00 - 06:00 fgga -> firmware -> embedded
english: 19:00 - 20:00 speaking
devopps: 09:00 - 10:00 references/(git -> docker -> azure -> linyx adm)

interrupts: python, bash, asm