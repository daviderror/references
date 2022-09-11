# magus
+ [schedule](#schedule)
+ [fpga](#fpga)
+ [firmware](#programming)
+ [software](#linux)
+ [devopps](#ceo)




## schedule
```
magus --+-- fpga
        |
        +-- firmware
        |
        +-- software
        |
        +-- devopps
```




## fpga

| aprentice       | master          | adept     |
| :---            | :---            | :---      |
| ~~viv~~ado >        | power supply    | fpga_3 >! |
| modelsim >!     | oscilloscopes   |           |
| ~~systemverilog~~ > | bandwidth       |           |
| FPGA arch >     | chose fpga      |           |
| Harris          | fpga_2 >        |           |
| fpga_1 >        | signal gen      |           |
| scheme reading  | race conditions |           |
|                 |                 |           |


| vivado         | fpga_1             | fpga_2              | modelsim     | systemverilog | fpga_3   | FPGA arch |
| :---           | :---               | :---                | :---         | :---          |:---      |:---       |
| SoC burning    | counter            | 1G (PHY,LL,NL,TL)   |              | stdlib        |          | LUT       |
| FPGA burning   | fifo (sync, async) | 10G (PHY,LL,NL,TL)  |              | primitives    |          | MIO       |
| VIO            | clockmeter         | PCIE                |              | modules       |          | EMIO      |
| ILA            | piso               | axi (full)          |              | fsm           |          | BRAM      |
| Floar planning | sipo               | DDR3                |              | tb            |          | DSP       |
| Schems         | gray counter       | ARM core            |              | interrupts    |          | clock dom |
| tcl            | single port bram   | 40G (PHY,LL,NL,TL)  |              | block diagrms |          | ...??     |
| BD             | dualport bram      | DMA                 |              | fsm diagramms |          |           |
| rebulding      | true dual bram     | 100G (PHY,LL,NL,TL) |              | fanout        |          |           |
| IPs            | uart               | mailbox             |              | piplining     |          |           |
| compilation    | i2c                | JESD                |              | fixed-point   |          |           |
| optimization   | spi                | ADC                 |              |               |          |           |
| pin constrs    | timer              | DAC                 |              |               |          |           |
| time constrs   | random generator   | HyperRAM            |              |               |          |           |
| ecoflow        | gpio               | NIC                 |              |               |          |           |
| physcl constrs | axi (lite,stream)  | SDRAM               |              |               |          |           |
|                | primitives         | DDR4                |              |               |          |           |
|                | serdes             | SSRAM               |              |               |          |           |
|                |                    |                     |              |               |          |           |




## firmware

| aprentice      | master            | adept |
| :---           | :---              | :---  |
| eclipse >!     | firm_2            |       |
| C >!           | timings           |       |
| firm_1 >       | logix anlz        |       |
| ARM arch       | chose device      |       |
| libs           | race conditions   |       |
| schemes        | ipc (openAMP)     |       |
| FreeRTOS >!    | deadlocks         |       |
| multithreading | resourc mangment  |       |
| multiprocesing | asm               |       |
| make           | yocto >           |       |
| compilatioin   | linux arch        |       |
| doxygen        |                   |       |
| cppcheck       | ebpf              |       |
| gcc            | ubus              |       |
| optimizatiom   | modbus            |       |
| gdb            |                   |       |
|                |                   |       |


| eclipse        | C           | firm_1                      | firm_2         | stndln drv | LKM drv    | PS     | PS    | devces |yocto      |
| :---           | :---        | :---                        | :---           | :---       | :---       | :---   | :---  |  :---  | :---      |
|                | std lib     | bootloader (AVR,Zynq,MB)    | 1G (NL,TL,AL)  | PS >>      | PS >>      | spi    |       |        | petalinux |
|                | prgrm strct | u-boot                      | 10G (NL,TL,AL) | PL >>      | PL >>      | i2c    |       |        | u-boot    |
|                | metprgrmmng | stndln drv (AVR,Zynq,MB) >> | bluetooth      | my_PL >>!  | my_PL >>!  | timers |       |        | BSP       |
|                | optmizatiom | LKM drv (Zynq) >>           | wi-fi          | devces >>! | devces >>! | gpio   |       |        | devicetree|
|                | fixed point | lwip                        | micro-services |            |            | uart   |       |        |           |
|                | non std lib |                             | MQTT           |            |            | EEPROM |       |        |           |
|                | misra       |                             | FTP            |            |            |        |       |        |           |
|                | posix       | atmega8a_clock              | HTTPS          |            |            |        |       |        |           |
|                | sockets     | more AVR apps!              | DNS            |            |            |        |       |        |           |
|                |             | more Zynq apps!             |                |            |            |        |       |        |           |
|                |             | more Zynq network apps!     |                |            |            |        |       |        |           |
|                |             | zynq7000_warehouse          |                |            |            |        |       |        |           |
|                |             |                             |                |            |            |        |       |        |           |




## software

| aprentice           | master  | adept |
| :---                | :---    | :---  |
| subline             | json    |       |
| python              | yaml    |       |
| base algorithms     |         |       |
| base data str       |         |       |
| block schem         |         |       |
| design patterns     |         |       |
|                     |         |       |


| ?    | ?    | soft_1     | 1G (AL) |
| :--- | :--- | :---       | :---    |
|      |      | 1G (AL) >> | MQTT    |
|      |      | soccets    | HTTPS   |
|      |      | TCP server | FTP     |
|      |      | UDP server | DNS     |
|      |      | ssh        |         |
|      |      |            |         |





## devopps

| aprentice   | master        | adept       |
| :---        | :---          | :---        |
| git_1 >     | git_2 >       |             |
| jira        |               |             |
| docker      | agile         |             |
| qemu        | azure         |             |
| github      | confluence    |             |
| linux adm > |               |             |
| bash        |               |             |
| eng interm  | eng up-interm | eng advance |
|             |               |             |


| git_1     | git_2      | linux adm |
| :---      | :---       | :---      |
| clone     | rebase     | ssh       |
| pull      | chery pick | bios      |
| push      | conflicts  | grub      |
| add       | submodules |           |
| commit    | reset      |           |
| branch    | .git       |           |
| gitignore |            |           |
| checkout  |            |           |
| switch    |            |           |
| config    |            |           |
| aliases   |            |           |
| fetch     |            |           |
| merge     |            |           |
| log       |            |           |
| status    |            |           |
| claen     |            |           |
|           |            |           |




## todo

c++11, c++14, C++17, hft, C++ code timings 