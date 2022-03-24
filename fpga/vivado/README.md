# vivado

todo: разобраться с кодом файла в setting_modelsim_as_default_simulator

+ [compile_simulation_libraries](#compile_simulation_libraries)
+ [customize_commands](#customize_commands)
+ [setting_modelsim_as_default_simulator](#setting_modelsim_as_default_simulator)

## compile_simulation_libraries

1. vivado -> Tools -> Compile Simulation Libraries..;
2. Compile Simulation Libraries -> Simulator: <- ModelSim Simulator;
3. Compile Simulation Libraries -> Compiled library location: <- директория куда скомпилировать библиотеки;
4. Compile Simulation Libraries -> Simulator executable path: <- путь до бинарника modelsim;
5. Compile Simulation Libraries -> Compile
6. Путь до скомпилированных библиотек -> modelsim.ini <- открыть редактором;
7. modelsim.ini -> скопировать все пути до библиотек (secureip = C:/modeltech64_10.5/lib/Xilinx/secureip и тд, их много);
8. В папке modelsim найти modelsim.ini -> свойства <- снять галочку "только чтение";
9. открыть на редактирование modelsim.ini (в корне modelsim) <- скопированные пути до библиотек (после строки vital12000 = $MODEL_TECH/../vital12000);
10. Закрыть modelsim.ini (в корне modelsim) и вернуть галочку "только чтение";

## customize_commands
1. RMB в пустом пространстве toolbar'а с run, Generate Bitstream ... -> Customize Commands
2. Customize Commands -> Menu name: <- имя команды;
3. Customize Commands -> Description, Icon file path (по желанию);
4. Source Tcl file: <- tcl файлик со скриптами

## setting_modelsim_as_default_simulator

1. Положить в vivado -> scripts -> name_my_scripts_dir <- modelsim.tcl (написанный ручками срипт);
2. [Customize Commands](#customize_commands) со скриптом modelsim.tcl;

modelsim.tcl (нужно поменять пути):
```
set_property compxlib.modelsim_compiled_library_dir C:/modeltech64_10.5/lib/Vivado_2020_2 [current_project]
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
```
