--std=08            - vhdl standart 2008
--ieee=synopsys     - addind synopsys for ieee.std_logic_textio.all  
--max-stack-alloc=0 -

## syntax check

`$ ghdl -s --std=08 --max-stack-alloc=0 --ieee=synopsys file.vhd`

## analazing

`$ ghdl -a --std=08 --max-stack-alloc=0 --work=work file_1_dir/file_1.vhd file_2.vhd file_n.vhdl` - add files to a work lib if needed

`$ ghdl -a --std=08 --max-stack-alloc=0 --ieee=synopsys file.vhd`

## elaborating

`$ ghdl -e --std=08 --max-stack-alloc=0 --ieee=synopsys some_file` - without a file extension

## creation of .vcd file and simulation in GHDL

`$ ghdl -r --std=08 --max-stack-alloc=0 --ieee=synopsys some_file --vcd=some_file.vcd`

## simulation in GTFWave

`$ gtkwave some_file.vcd`

<img src="https://github.com/Drakonof/references/tree/main/bash/doc/mkdir.png" width="1000">
<img src="https://github.com/Drakonof/references/tree/main/bash/doc/mkdir.png" width="1000">
<img src="https://github.com/Drakonof/references/tree/main/bash/doc/mkdir.png" width="1000">
<img src="https://github.com/Drakonof/references/tree/main/bash/doc/mkdir.png" width="1000">