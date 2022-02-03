## make and gcc

	install gcc and make
	uninstall gcc and make
	compilation stages
	gcc compilation

1.  [install](#install)
2.  [uninstall](#uninstall)
3.  [gcc_compiling](#gcc_compiling)
4.  [make_compilimg](#make_compilimg)


## install

	In the pack:
    	libc6-dev
		libstdc++6-dev 
		gcc 
		g++ 
		make 
		dpkg-dev

1. `$ sudo apt -y install build-essential`
2. `$ whereis gcc make`
3. `$ gcc -v`
4. `$ make -v`
5. `$ sudo apt -y install gcc-snapshot && sudo apt -y install gcc-11g++-11` - updating to the newest vertion

## uninstall

`$ sudo apt purge -y build-essential && sudo apt-y autoremove`

## gcc_compiling
	
	Compilation stages:
		Preprocessing - removing comments, expanding macros, expanding included files
		Compiling     - generates assembly language file from .c file
		Assembly      - convert the assembly code into pure binary code or machine code (zeros and ones). This code is also known as object code.
		Linking       - merges all the object code from multiple modules into a single one. Will link our code with libraries functions code.
					    Static: inserts library functions to the executable file
					    Dynamic: does not copy code, but just places the name of the library in the binary file

1. `$ gcc -E -o programm.i programm.c` - programm.i (preprocessing) |
2. `$ gcc -S programm.i` - programm.s (compiling)                   | translation
3. `$ gcc -c programm.s` - programm.o (assembly)                    |
4. `$ gcc -o rogramm programm.o` - rogramm                            linking  

`$ gcc -E -o programm.i programm.c` - programm.i (preprocessing)

`$ gcc -S programm.c` - programm.s (preprocessing + compiling)

`$ gcc -c programm.c` - programm.o (preprocessing + compiling + assembly)

`$ gcc programm.c` - a.out as default

`$ gcc -o rogramm rogramm.c -std=gnu99` - C99 standard compilation

`$ gcc -o rogramm rogramm.c -Wall -std=gnu99` - C99 standard compilation and warnings Wall (http://staff.mmcs.sfedu.ru/~ulysses/IT/C++/using_gcc.html)

`$ gcc -o rogramm rogramm.c -W -std=gnu99` - C99 standard compilation and warnings Wextra (http://staff.mmcs.sfedu.ru/~ulysses/IT/C++/using_gcc.html)

`$ gcc -o rogramm programm.c` -> rogramm.out. -o key says to use a name that set user ("rogramm_bin" for this case)

`$ gcc -o rogramm lib.c ../libs/lib_1.c programm.c` - creating rogramm.out from several files case 1

	creating rogramm.out from several files case 2:

	lib.c           -> preprocessing -> compiling -> assembly -> |
	../libs/lib_1.c -> preprocessing -> compiling -> assembly -> | linking -> programm
	programm.c      -> preprocessing -> compiling -> assembly -> |

1. `$ gcc -c lib.c`
2. `$ gcc -c ../libs/lib_1.c`
3. `$ gcc -o rogramm programm.c` - #include "lin.h" #include "../libs/lib_1.h"

`$ gcc -O3 -o rogramm rogramm.c` - level 3 optimazed compilation

	-O1 - soft
	-02 - normal
	-O3 - hard
	-O0 - without otimization
	-Os - programm size optimization? goes through -O2

## make_compilimg

	Makefile structure:
		targer: dependences
		"TAB"command

	Makefile process:
		dependences -> command -> targer

	Makefile example:

		TARGET = hello
		PREFIX ?= /usr/local/bin #?= для определения PREFIX, что позволит менять его через окружение
		SRCS = main.c hello.c

		.PHONY: all clean install uninstal

		programm.o: programm.c
			$(CC) -c programm.c      #$(CC) - a default linux compilayor name
		lib.o: lib.c
			$(CC) -c lib.c
		lib_1.o: ../libs/lib_1.c
			$(CC) -c ../libs/lib_1.c
		$(TARGET): programm.o lib.o ../libs/lib_1.o
			mkdir bin	
			$(CC) -o bin/$(TARGET) programm.o lib.o ../libs/lib_1.o
			rm -rf *.o
		all: $(TARGET)

		.c.o:                             #.c.o указывает, каким образом из .c файлов получить .o файлы.
        	$(CC) $(CFLAGS)  -c $< -o $@  # CFLAGS=-g make CFLAGS=-O2 make as defaults
                                          # %< и $@ — это переменные, значение которых содержит имя цели или зависимости.

		clean: 
			rm -rf $(TARGET) *.o
		install:
			install ./$(TARGET) $(PREFIX)
		uninstall:
			rm -rf $(PREFIX)/$(TARGET)

			

	Makefile using:

	Если файл programm уже имеется (остался после предыдущей компиляции) и его реквизиты не были изменены, 
	то команда make ничего не станет пересобирать. Так например, изменив заголовочный файл, случайно не включенный 
	в список реквизитов, можно получить долгие часы головной боли. Поэтому, чтобы гарантированно полностью 
	пересобрать проект, нужно предварительно очистить рабочий каталог

`$ make` - for target "all"

`$ make <target>` - for others targets


