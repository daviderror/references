# make

[installation](#installation)

[work_scheme](#work_scheme)

[building](https://github.com/Drakonof/references/tree/main/C#building)

[syntax](#syntax)


## installation

## work_scheme

    +----------+    +----------+    +---------+    +------------+
    | my_lib.h |    | some_lib |    | any_lib |    | my_lib_2.h |
    +----------+    +----------+    +---------+    +------------+
         ^    ^           ^              ^           ^    ^
         |    |           |              |           |    |
         |    +--+        |              |        +--+    |
    +----------+ |        |              |        |  +------------+     
    | my_lib.c | |        |  +-----------+        |  | my_lib_2.c |
    +----------+ |        |  |                    |  +------------+
         ^       |     +--------+                 |       ^         
         |       +-----|        |-----------------+       |
         +-------------| main.c |--------------------------
                       |        |
                       +--------+ 

## building

[building](https://github.com/Drakonof/references/tree/main/C#building)

## syntax
```
targets: prerequisites  # цель: зависимости
    commands            # <tab>команды для исполнения
```
target - что получается в результате выполнения Makefile

prerequisites - исходные данные для порождения target. target зависит от prerequisites

commands - действия выполняемые утилитой

Простой пример:
```
all:
    gcc -Wall Wextra -Werror main.c -c
```
all - target который будет выполняться по команде `make`. Так как он стоит первым (хоть и один), он будет считаться дефолтным.

Дефолтный target - target выполняющийся по команде `make` без явного указания target'а ключем-именем target. Должен стоять первым, может иметь любое имя, в примере его имя "all".
