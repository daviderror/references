# C 
[building_process](#building_process)

[types](https://github.com/Drakonof/references/blob/main/C/types.md)

[functions](https://github.com/Drakonof/references/blob/main/C/functions.md)

[preprocessor](https://github.com/Drakonof/references/blob/main/C/preprocessor.md) 

[implementation_defined_behavior](#implementation_defined_behavior)

[unspecified_behavior](#unspecified_behavior)

[undefined_behavior](#undefined_behavior)

[programm_arguments](#programm_arguments)

[getopt](#getopt)

[getopt_long](#getopt_long)

[getopt_long_only](#getopt_long_only)

## building_process

   building_process == (compilator && assembler && linker)

               gcc -E                     gcc -S                 gcc -c       libraries  gcc -o
               +---------------------+    +-----------------+    +-----------------+ |   +-----------------------+ 
               | C preprocessor      |    | C compiler      |    | Assembler       | |   | Linker                |
    c code  -> |                     |    |                 |    |                 | +-> |                       |
               | (includes, defines, | -> |                 | -> |                 |     |                       | -> .out
    headers -> |  ifdef and comments |    |                 |    |                 |     |                       |
               |  deleting)          |    | (assembly code) |    | (object code)   | --> | (executable programm) |
               +---------------------+    +-----------------+    +-----------------+     +-----------------------+

   `ldd name_of_execution_file` - покажет из каких библиотек состоит исполняемый файл

## types

https://github.com/Drakonof/references/blob/main/C/types.md 

## functions

https://github.com/Drakonof/references/blob/main/C/functions.md

## preprocessor

https://github.com/Drakonof/references/blob/main/C/preprocessor.md
 
## implementation_defined_behavior
    
Компилятор должен выбрать вариант, документировать его и придерживаться его.

Пример: размер int'а

## unspecified_behavior
    
Компилятор выбирает любой из вариантов, причем каждый раз новый.

Пример: порядок вычисления аргументов функции

## undefined_behavior

Неопределенное поведение (UB, Undefined behavior) - маргинальная ситуация, поведение, которое может возникать в результате использования ошибочных программных конструкций или некорректных данных, на которые Международный Стандарт не налагает никаких требований (зависит от реализации компилятора, библиотеки, микросхемы и случайных факторов наподобие состояния памяти). 

Это свойство некоторых языков программирования в определенных ситуациях выдавать результат, зависящий от реализации компилятора или заданных ключей оптимизации, то есть спецификация не определяет поведение языка в любых возможных ситуациях, а говорит: "при условии А результат операции Б не определен". Такая программа не будет кроссплатформенной и может приводить к сбоям на другой машине, в другой ОС и даже на других настройках компилятора, а может и работат как полагается, это не определенно.

Неопределенное поведение нельзя путать с неуточняемым поведением (unspecified behavior, см. пункт unspecified behavior), при котором спецификация разрешает не любое поведение, а только ограниченный диапазон вариантов реализации.

Любая из ниже приведенный ошибочных программных конструкций приводит к широким диапазонам оптимизации кода и ведет за собой ряд неопределенных провидений программы и неожиданные результаты.

a. Использование не инициализированной переменной: 

статические и глобальные переменные автоматически инициализируются нулем компилятором, но локальные не статические так не инициализируются так как находятся в кадре стека и хранит изначально мусор.  
b. Переполнение знаковой целой переменной: 

в этом случае значение переменной будет не определён, так к примеру для int INT_MAX + 1 не гарантированно будет равен INT_MIN так как, взависимости от платформы и/или ОС, INT_MAX + 1 будет равно отрицательному нулю или расширится на соседние ячейки памяти. 
c. Сдвиг на величину, большую, чем разрядность переменной: 

это связанно с различием реализаций разных аппаратных платформ и соответственно с различиями в обработки данной операции. 
d. Разыменование «диких» указателей и доступ за пределы массива: 

разыменование произвольного указателя (указателя на перераспределенную память) и случай доступа к массиву с выходом за его границы является распространенным багом. Чтобы устранить этот источник неопределенного поведения, при доступе к массиву должна производиться проверка диапазона. Это связанно с тем, что дикие указатели могут не явно ссылаться на используемую область или наоборот на мусор.   
e. Разыменование NULL-указателя: 

разыменование нулевого указателя в C не определено так как если обратиться по адресу 0, это не приведет к доступу к этой странице. Так же можно при разыменование «volatile» указатель на null получить аварийный останов.
f. Правила нарушения типа: 

преобразование int* в float* с последующим разыменованием (доступом к «int» как если бы это был «float»). Язык C требует, чтобы такой тип преобразования происходил через memcpy: использование преобразования указателей некорректно и результаты не определены. 
g. Двойная оценка в макрасах.
       Пример:  
 ```    
       #define  SOME_MACROS(b) (b) * (b)

       // foo() и i++ будут расширены не верно.
       a = SOME_MACROS(foo());  
       b = SOME_MACROS(i++);
```     
h. Переменная несколько раз изменяется в рамках одной точки следования. Пример:  
       i++ = i++  
i. Создание имени идентификатора более 63 символов так как компилятор может не распозновть более 64 символов.

Если будут созданные две переменные с именем 64 символа отличные только 	последним символом, комплитор может воспринять их  как две разные 	переменные, а может не воспринять и посчитать их как одну.
     
j. Использование не верных спецификаторов в printf и scanf: 
```
       int f = 5.4;
       printf(“%d”, f);
```     
k. Переназначение константы
```
const int c = 10;

const_cast<int&> (c) = 11;
```

## programm_arguments

```
// argc - arguments counter, number of the arguments
// argv - указатель на массив строк аргументов
int main(int argc, char *argv[]){                 
    for (int i = 0; i < argc; i++){
        printf("Argument %d: %s\n", i, argv[i]);
    };
}
```

## getopt

[Функция](https://github.com/Drakonof/references/blob/main/C/functions.md) getopt принимает [параметры argc и argv](#programm_arguments) в том виде, в каком они передаются функции main в программе, и строку спецификатора опций, которая сообщает getopt, какие опции определены для программы и есть ли у них связанные с ними значения. optstring — это просто список символов, каждый из которых представляет односимвольную опцию. Если за символом следует двоеточие, это означает, что у опции есть ассоциированное значение, которое будет принято как следующий аргумент.

[Прототип функции](https://github.com/Drakonof/references/blob/main/C/functions.md#prototype): `int getopt(int argc, char *const argv[], const char *optstring);`

Пример:

`./argopt_example -i -lr 'hi there' -f some_file_for_example.с -q`

Код примера:

```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    int opt = 0;
    
    /*
    Если первый символ optstring:
    ':' - getopt не будет выводить сообщение об ошибке, и позволит получать ':' и '?' как
          значения возврата (аргумент не найден и не известный аргумент соответсвенно); 

    Если cимвол ввода отсутствует в параметре optstring, getopt возвращает "?".
    И помещает неправильный символ в глобальную переменную optopt;

    По умолчанию getopt выводит сообщения об ошибках в стандартный поток ошибок;
    
    После аргумента:
    ':' - требуется указать значение для аргумента;
    '::' - не обязательный аргумент, можно упустить;
    */
    while (-1 != (opt = getopt(argc, argv, ":if:lr"))) {
        switch(opt) {
        case 'i':
        case 'l':
        case 'r':
             printf("option: %c\n", opt);
        break;
        case 'f':
             printf("filename: %s\n", optarg);
        break;
        case ':':
            printf("option needs a value\n");
        break;
        case '?':
            printf("unknown option: %c\n", optopt);
        break;
        default:
            printf("also as in ? unknown option: %c\n", optopt);
        break
        }
    }

    exit(EXIT_SUCCES);
}
```
log примера:

    option: i
    option: l
    option: r
    filename: some_file_for_example.c
    unknown option: q
    argument: hi there

Присер многократно вызывает функцию getopt для обработки аргументов-опций до тех пор, пока не останется ни одного, в этот момент getopt вернет -1. Для каждой опции выбирается подходящее действие, включая обработку неизвестных опций и пропущенных значений.

