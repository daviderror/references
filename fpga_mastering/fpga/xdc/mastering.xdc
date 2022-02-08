set_property BITSTREAM.GENERAL.COMPRESS TRUE [current_design]
set_property BITSTREAM.CONFIG.UNUSEDPIN pullUP [current_design]

set_property PACKAGE_PIN H9 [get_ports clk_p]
set_property PACKAGE_PIN G9 [get_ports clk_n]

set_property IOSTANDARD DIFF_SSTL15 [get_ports clk_n]
set_property IOSTANDARD DIFF_SSTL15 [get_ports clk_p]