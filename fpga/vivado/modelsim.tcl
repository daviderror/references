set_property compxlib.modelsim_compiled_library_dir C:/modeltech64_10.5/lib/xilinx [current_project]
set_property target_simulator ModelSim [current_project]
set_property -name {modelsim.simulate.custom_udo} -value {C:/modeltech64_10.5/tcl/button} -objects [get_filesets sim_1]



set    PROJ_DIR   [get_property DIRECTORY [current_project]]
set    PROJ_NAME  [current_project].srcs
append RADIX_tcl_path $PROJ_DIR/$PROJ_NAME/sim_1/Modelsim_user_scripts.tcl
set_property -name {modelsim.simulate.custom_wave_do} -value [file join $RADIX_tcl_path] -objects [get_filesets sim_1]
unset  PROJ_DIR
unset  PROJ_NAME
unset  RADIX_tcl_path
launch_simulation