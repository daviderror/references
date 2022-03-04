# make

todo gcc flages and etc.. (имплисит рулс не забыть)

[installation](#installation)

[work_scheme](#work_scheme)

[building_process](https://github.com/Drakonof/references/tree/main/C#building_process)

[variables](#variables)

[syntax](#syntax)

[PHONY](#PHONY)

[defines_in_c_code](#defines_in_c_code)

[launch](#launch)

[recursion](#recursion)

[implicit_rules](#implicit_rules)

[cpp](#cpp)

## installation
```
sudo apt update
sudo apt install make
make -version
```

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

## building_process

[building_process](https://github.com/Drakonof/references/tree/main/C#building_process)

## variables

`SOME_VAR = some_val` - пример рекурсивной записи в переменую;

Рекурсивная запись в переменую - make в процессе сборки, будет отслеживать изменение some_val в не Makefile (изменение некой переменной/ссылки и тп в результате исполнения другой программы) и использовать её изменяющееся значение в течении сборки;

`SOME_VAR := some_val` - пример нерекурсивной записи в переменую;

Нерекурсивная запись в переменую - значение переменной устанавливается единажды в момент присваивания и не изменяется в течении сборки.

`SOME_VAR ?= some_val` - условное присваивание, срабатывает если переменная SOME_VAR еще не была определена;

Варианты присваивания нескольких значений переменной (пример для нерекурсивного присваивания, но работает и для других типов):

`SOME_VAR := a1.c ../some_dir/a2.c src/a3.c a4.c`
```
SOME_VAR := a1.c \
../some_dir/a2.c \
src/a3.c \
a4.c
```
```
SOME_VAR := a1.c
SOME_VAR += ../some_dir/a2.c \
src/a3.c
SOME_VAR += a4.c
```
Если размер имени переменной больше чем один символ, то, в коде имя этой переменной рекомендуется заключать в скобки (для поддержания хорошего стиля), так же синтаксис Makefile требует устаноки символа '$' перед именем переменной (которая больше одного символа), но ошибкой не будет устанока $ перед такой переменной и заключение её в скобки для поддержания хорошего стиля кода.

`$(SOME_VAR): $(SOME_VAR) ...`

### TARGER

Переменная хранящая имя результата сборки (собранный бинарный файл).

```
...
TARGET ?= target_name
...
$(TARGET): $(SRC:.c=.o)
     gcc -O2 -std=gnu11 $^ -o $@
...
```

### BUILDDIR

Переменная хранящая имя директории сборки.

```
...
BUILD_DIR := ./some/build/dir
...
$(BUILD_DIR)/$(TARGET): $(BUILD_DIR)/$(SRC:.c=.o)
    $(CC) $(CFLAGC) $^ -o $@
...
```

### INCDIRS

Переменная хранящая имя директории .h файлов.

```
...
INCDIRS := ./inc
...
$(BUILDDIR)/%.o: srz/%.c $(BUILDDIR)
    gcc -O2 -std=gnu11 $(addprefix -I,$(INCDIRS)) -c $< -o $@
...
```

### SRCDIRS

Переменная хранящая имя директории .c файлов.

```
...
SRCDIRS := ./src
...
$(BUILDDIR)/%.o: $(SRCDIRS)/%.c $(BUILDDIR)
    gcc -O2 -std=gnu11 $^ -o $@
...
```

### CC

Переменная хранящая имя компилятора. 

```
...
CC = gcc
...
$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
    $(CC) -O2 -std=gnu11 $^ -o $@
...
```

### CFLAGC

Переменная хранящая флаги для компилятора. 
```
...
CFLAGC := -O2 -std=gnu11 -Wall -Wextra -Wpedantic -fms-extensions
...
$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
    $(CC) $(CFLAGC) $^ -o $@
...
```

## syntax
```
targets: prerequisites  # цель: зависимости
    commands            # <tab>команды для исполнения
```
target - что получается в результате выполнения Makefile

prerequisites - исходные данные для порождения target. target зависит от prerequisites

commands - действия выполняемые утилитой

## default target

Target выполняющийся по команде `make` без явного указания target'а ключем-именем target. Должен стоять первым, может иметь любое имя, в примере его имя "all".

Простой пример:
```
all:
    gcc -Wall Wextra -Werror main.c -c
```
all - target который будет выполняться по команде `make`. Так как он стоит первым (хоть и один), он будет считаться дефолтным.

Пример передачи всех prerequisites в targets через $^

```
TARGET ?= hello
SRC := src/main.c \
       src/mylib.c
CC = gcc
CFLAGC := -O2 -std=gnu11

$(TARGET): $(SRC:.c=.o)
    $(CC) $(CFLAGC) $^ -o $@
```
-o - куда делать аутпут собранного бинарника (т.е. куда собрать бинарник). В данном случае это $@;

$@ - синоним $(TARGET). В примере $@ это $(TARGET);

### Проверка на правильность табов

`cat -e -t -v Makefile`
Напечатает символ '^I' на месте табов, иначе будут отступы.

Неправильный Makefile прверенный через `cat -e -t -v Makefile`, при команде `make` выдает ошибку `Makefile:7: *** missing separator.  Stop.`:
```
TARGET ?= hello$
SRC := src/main.c src/mylib.c$
CC = gcc$
CFLAGC := -O2 -std=gnu18$
$
$(TARGET): $(SRC:.c=.o)$
    $(CC) $(CFLAGC) $^ -o $@
```
Правильный Makefile прверенный через `cat -e -t -v Makefile`:
```
TARGET ?= hello$
SRC := src/main.c src/mylib.c$
CC = gcc$
CFLAGC := -O2 -std=gnu18$
$
$(TARGET): $(SRC:.c=.o)$
^I$(CC) $(CFLAGC) $^ -o $@
```

### Переопределение Implicit Rules

[Implicit Rules](https://github.com/Drakonof/references/tree/main/make#implicit_rules);

```
%.o: %.c
    $(CC) $(CFLAGC) -c $< -o $@
```
Запись означает, преобразовать все .c в .o, по ниже описаному правилу.

$< замена $^, но этот оператор передаст только один самый первый prerequisite из всех prerequisites.

Target %.o позволяет собрать объектный файл из любого из prerequisites .c  файла.

Пример:
```
make mylob.o
```

### Target clean 

Удаляет все артифакты сборки и оставить толко результат.

### Tidy

Удаляет всё, и артифакты, и результаты.

## PHONY

Служебный target использующийся чтобы указать цели, которые не порождают файламы и сами при этом ими не являются. Порядок указания target'ов не важен и не определяет default target.

Используется для: 
1. Что бы make не искал файлы с установленными в .PHONY target'ами. 
2. В рекурсивном вызове make TODO


## defines_in_c_code

Можно переопределить в программе на этапе сборки, define'ы, но  в самом коде программы эти define'ы, должны быть заключенны в #ifndef, иначе они будут иметь дефолтные относительно программы значения.

```
%.o: %.c
    $(CC) $(CFLAGC) -DSOME_DEF_0=0 -DSOME_DEF_1=1 -c $< -o $@
```

## launch

`make` - автоматически подхватывает Makefile лежащий в папке запуска. [Дефолтный таргет](#syntax).

`make -f some_file` - запускает some_file вместо MAkefile, но это считается плохим тоном.

`make some_target` - для запуска конкретной цели сборки 

## recursion

todo

## implicit_rules

todo

## cpp

todo