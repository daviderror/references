# make

todo gcc flages and etc.. (имплисит рулс не забыть)

+ [installation](#installation)
+ [removing](#removing)
+ [launching](#launching)
+ [work_scheme](#work_scheme)
+ [building_process](https://github.com/Drakonof/references/tree/main/C#building_process)
+ [assignments](#assignments)
+ [rules](#rules)
+ [functions](#functions)
+ [default_target](#default_target)
+ [PHONY](#PHONY)
+ [defines_in_c_code](#defines_in_c_code)
+ [launch](#launch)
+ [recursion](#recursion)
+ [implicit_rules](#implicit_rules)
+ [automatic_dependency](#automatic_dependency)
+ [cpp](#cpp)
+ [example](#example)

## installation
```
sudo apt update
sudo apt install make
make -version
```

## removing

todo

## launching

`make` - для [default target](https://github.com/Drakonof/references/tree/main/make#default_target)

`make target_name` - для запуска определенного [target](https://github.com/Drakonof/references/tree/main/make#syntax)

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

## assignments

`SOME_VAR = some_val` - пример рекурсивной записи в переменую (verbatim assignment);

Рекурсивная запись в переменую - make в процессе сборки, будет отслеживать изменение `some_val` в не Makefile (изменение некой переменной/ссылки и тп в результате исполнения другой программы) и использовать её изменяющееся значение в течении сборки.

`SOME_VAR := some_val` - пример нерекурсивной записи в переменую (simole expantion);

Нерекурсивная запись в переменую - значение переменной устанавливается единажды в момент присваивания и не изменяется в течении сборки.

`SOME_VAR ?= some_val` - условное присваивание (conditional assignment), срабатывает если переменная SOME_VAR еще не была определена, повторное переопределение не сработает, данная переменная будет хранить самое первое значение;

`SOME_VAR != some_val` - присваевание результата выполнения shall команды в переменную. Сначала выполняется дейтсвие с правой стороны от оператора, затем результат выполнения присваевается переменной;
```
SOME_VAR != printf '\043'
SOME_VAR_1 != find . -name '*.c'
```

`SOME_VAR += some_val` - дополнение (append to), добовляет значение в уже проинициализированную переменную;
```
SOME_VAR := a1.c
SOME_VAR += ../some_dir/a2.c \
src/a3.c
SOME_VAR += a4.c
```
Варианты присваивания нескольких значений переменной (пример для нерекурсивного присваивания, но работает и для других типов):

`SOME_VAR := a1.c ../some_dir/a2.c src/a3.c a4.c`
```
SOME_VAR := a1.c \
../some_dir/a2.c \
src/a3.c \
a4.c
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
$(BUILDDIR)/%.o: src/%.c $(BUILDDIR)
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

Переменная хранящая имя компилятора. Можно не объявлять, тк уже предопределена в системе.

```
...
CC ?= gcc
...
$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
    $(CC) -O2 -std=gnu11 $^ -o $@
...
```

### CFLAGC

Переменная хранящая флаги для [gcc](https://github.com/Drakonof/references/tree/main/gcc). 
```
...
CFLAGC := -O2 -g2 -std=gnu11 -Wall -Wextra -Wpedantic -fms-extensions
...
$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
    $(CC) $(CFLAGC) $^ -o $@
...
```
-O - степень [оптимизации](https://github.com/Drakonof/references/tree/main/gcc#optimization); 

-g - уровень дебага;

Важно: чем выше уровень оптимизации тяжелее отлаживаться.

-std - используемый стандарт языка;

-W - какие [warnings]((https://github.com/Drakonof/references/tree/main/warnings#)'и выводить в течении сборки. 

-fms-extensions - todo

## rules
```
targets: prerequisites  # цель: зависимости
    commands            # <tab>команды для исполнения
```
target - что получается в результате выполнения Makefile

prerequisites - исходные данные для порождения target. target зависит от prerequisites

commands - действия выполняемые утилитой

Взять все в текущей папке .c файлы и скомпилировать из в соответвубщие .o файлы:
```
%.o: %.c
    $(CC) $(CFLAGC) $^ -o $@
```
$< - передаст только один самый первый prerequisite из всех prerequisites;
$@ - вставит имя target вместо себя;
$^ - передаст все prerequisite на своё место;
$? - передаст все prerequisite которые изменились;
$| - выполняет prerequisite'ы по очереди (пример ниже строчкой);

Сначало выполнется `$(DIR` и только потом `$(OBJS)`:
```
%(TARGET): $(DIR) | $(OBJS)
    $(CC) -o $@ $^
```

## functions

Бывают: Text functions, filename functions, conditional functions, value function, shell function, control function;

### wildcard
`objects := $(wildcard *.c*)` - получить список всех файлов с исходным текстом программы;

Функция `wildcard` развернет шаблоны со звездочками до реальных имен файлов: `main.сpp file1.с file2.сpp file3.с src/dir2/file4.с`

### addprefix
добавить префикс ко всем значения переменной.
```
SOME_VAR := a1.c a2.c a3.c a4.c
SRC := $(addprefix src_dir/,$(SOME_VAR))
```

### addsuffix
добавить постфикс ко всем значения переменной.
```
SOME_VAR := a1 a2 a3 a4
$(addsuffix /*.c, $(SOME_VAR)
```

### .c=.o
`$(SRCS: .c=.o)` - взять все значения из переменной SRCS и сменить .c на .o;

## default_target

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

$@ - синоним target'a. В примере $@ это $(TARGET);

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

## automatic_dependency

todo

## cpp

todo

## example
```
TARGET ?= max
SRC := main.c mylib.c
CC = gcc
CFLAGC := -O2 -g3 -std=gnu11 -Wall -Wextra -Wpedantic -fms-extensions
LDFLAGS := -ldl -lm -Wl
BUILDDIR := .build
SRCDIRS := src
INCDIRS := inc

.PHONY: all clean tidy

all: $(BUILDDIR)/$(TARGET)

$(BUILDDIR):
    mkdir -p $@

$(BUILDDIR)/$(TARGET): $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))
    $(CC) $(CFLAGC) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIRS)/%.c $(BUILDDIR)
    $(CC) $(CFLAGC) -DA=6 -DB=7 -DDEBUG=0 $(addprefix -I,$(INCDIRS)) -c $< -o $@

clean:
    rm -f $(addprefix $(BUILDDIR)/,$(SRC:.c=.o))

tidy: clean
    rm -rf $(BUILDDIR)
```