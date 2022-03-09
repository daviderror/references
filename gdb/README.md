# gdb

+ [installing](#installing)
+ [removing](#removing)
+ [launching](#launching)
+ [exit](#exit)
+ [commands](#commands)
+ [семихостинг](#семихостинг)
+ [svo](#svo)

## installing

todo

## removing

todo

## launching

`gdb exe_file_name`

После этого будет начата сессия отладки:
```
shimko@simko-PC:/media/shimko/CEF0BAC0F0BAADD91/workspace/references/gdb$ gdb ./.build/max 
GNU gdb (Ubuntu 8.1.1-0ubuntu1) 8.1.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./.build/max...(no debugging symbols found)...done.
(gdb) 
```
в строчку `(gdb)` вводятся команды.

`gdb exe_file_name --tui` - запуск gdb с графичиским вспомогательным окном с исходным кодом. После открытия окна, для оттображения кода нужно дважды нажать enter.

## exit

Выход из gdb  выполняется через команду `quit`. Сокращение: `q`. Смотри [commands](https://github.com/Drakonof/references/tree/main/gdb#commands)

## commands

Можно юзать tab для доавтозаполнения. Но команды можно сокращать, gdb поймет.

### help

Как работать с определенной командой.

`help command_name` 

Сокращение: `h`;

### info

Списк breakpoint'ов.

`info breakpoints` 

Сокращение: `i b`;

### run

Запуск загруженной программы.

`run`

`run 10 'W' "hello` - запуск загруженной программы с аргументами (в отличии от set аргументы устанавливаются разово).

Сокращение: `r`; 

### list

Вывести листинг программы с момента остановки программы. Клавиша Enter будет спукать на строку ниже с момента окончания вывода.

`list `

Сокращение: `l`; 

`list foo_name` - вывести код с момента функции foo_name;

`list num_lines` -вывести num_lines строк с момента остановки программы; 

### set

Задать что либо по дефолту.

`set listsize num_lines` - задать дефолное колличество строк;

`set args 10 'W' "hello"` - задать аргументы программы по дефолту, в примере это 3 аргумента разгого типа.

### break

Постоянный breakpoint.

`break foo_name` - постоянный breakpoint на вход в функцию foo_name. 

`break some_var == 1` - постоянный breakpoint на равенство переменной к комкому-то значению (в примере some_var и 1). 

Сокращение: `b`;

### tbreak

Разовый breakpoint.

`tbreak foo_name` - разовый breakpoint на вход в функцию foo_name. 

Сокращение: `tb`;

### continue

Продолжить выполнение прграммы после остановки по breakpoint.

`continue` 

Сокращение: `cont`;

### until

Выполнить программу до определенной строки. 

`until 66`

Сокращение: `unt`;

### where

Показать функцию и строку остановки программы.

`where`

Сокращение: `whe`;

### print

Значение переменной.

`print var_name` - значение переменной var_name в точке отсановки. 

`print arr_name` - значение всего массива arr_name в точке отсановки.

`print arr_name[index_bum]` - значение index_bum в массиве arr_name в точке отсановки.

`print *p_name` - покажет значение p_name.

`print *(p_name + some_offset)` - значение p_name по смещению some_offset.

Сокращение: `pr`;

### disassemble

Дизасемблироанный код в точке останвки.

`disassemble` 

Сокращение `disas`.

### quit

Выйти из dbg

`quit` 

Сокращение: `q`; 

## семихостинг

todo

## svo

todo