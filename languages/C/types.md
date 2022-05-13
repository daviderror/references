# types

+ [integer](#integer)
+ [floating_points](#floating_points)
+ [struct](#struct)
+ [enum](#enum)
+ [arrays](#arrays)
+ [union](#union)

byte, short, ushort, int, uint, long, ulong, charp, bool, invbool - kermel param types

## integer

    #include <stdint.h> and <inttypes.h>

    intN_t (N == 8, 16, 32, 64)
    int_leastN_t
    int_fastN_t
    intmax_t
    intptr_t
    uintN_t (uint8_t for byte, not char тк char может быть sign or unsign
    в зависимости от платформы, а байт это unsign)
    uint_leastN_t
    uint_fastN_t
    uintmax_t
    uintptr_t

## floating_points
 
    float (32b  может быть знаковым) 
    знак числа(S=1b) экспонента(E=8b) мантиса(M=23b)
    double (double precision 64b может быть знаковым)
    знак числа(S=1b) экспонента(E=11b) мантиса(M=52b)
    long double (64, 80, 128 (в зависимости от платформы) может быть знаковым)

    Перевод в бинарный вид по формуле: (-1)^S x 1.M x 10^E
    Примеры для float: 
    123.456                       -> 
    1111011.01110101              точка смещается до самой крайней уденицы справа, а само число домнажается, 
                                  на соответвующее колличеству сдвигов, степеней десяти) -> 
    1.11101101110101 x 10^6       самая правая еденица и число 10 отбрасываются -> 
    11101101110101 6              экспонента переводится в бинарный вид -> 
    11101101110101 110            шесть суммируется с 127 для обозначения знака экспоненты тк экспоненты
                                  больше 127 положительные -> 
    11101101110101 10000101       числа заполняю соответвующие поля и дополняются нулями до размерности 
                                  типа данных -> 
    0 10000101 11101101110101000000000

    -123.456                      -> 
    1 10000101 11101101110101000000000

    0.123                         -> 
    0.1111011                     точка смещается до самой крайней уденицы слева, а само число домнажается, 
                                  на соответвующее колличеству сдвигов, степеней десяти со знаком минус) ->
    0111101.1 х 10^(-6)           -> 
    0111101 110                   шесть вычитается из 127 для обозначения знака экспоненты тк экспоненты меньше 
                                  127 это отрицательные ->
    0111101 1111001               ->
    0 1111001 01111010000000000000000

    -0.123                        ->
    1 1111001 01111010000000000000000

    Особый случаи:
    S == 1 и E == 255 и M == 0, то число == -бесконечность
    S == 0 и E == 255 и M == 0, то число == +бесконечность
    S == 0/1 и E == 255 и M != 0, то число == NaN (Not a number)

    Литералы; 0.1 (double), 0.1L (lomg double), 0.1f (float)

    Bad case:
```
#include <stdio.h>

if ((0.1 + 0.2) == 0.3) {
	printf("T");
}
else {
	printf("F");
}
```
    printf log: F
```
printf("%.30lf != %.30lf", 0.1 + 0.2, 0.3);
```
    printf log: 0.3000000000000000444 != 0.2999999999999999888

    Good case:
```
#include <stdio.h>
#include <math.h>
 
double res = 0.1 + 0.2;

const double eps = 1e-8, // эпсилон задающий точность
             comp = 0.3;

if (dabs(res - comp) <= eps) { // fabs для float
	printf("T");
}
else {
	printf("F");
}
```
    printf log: T
    
    Но вообще в stdlib есть платформазависимый DBL_EPSILON дефайн.

## struct

### Объявление обычной структуры
```
struct type_of_struct {
  поля структуры
} name_of_struct;  
```
    Но лучше разносить объявления структуры и типа струтктуры, что бы не объявлять объект структуры глобально.
```
struct type_of_struct {
  char field_0;
  int field_1;
  int *p_field_2;
};  

struct type_of_struct name_of_struct_0 = {}, 
                      name_of_struct_1 = {.field_0 = '0', .field_1 = 1, .p_field_2 = NULL},
                      name_of_struct_2 = {.p_field_2 = &name_of_struct_1.field_1};
```

`sizeof (type_of_struct)` // 9 байт при 32х битном int, но! в памяти (физически) эта структра будет выровнена да 4 байт на каждое поле и займет 12 байт 

### Объявление анонимной структуры

Так делать можно, но не рекомендуется, тк отладчик не сможет с ней работать, также имя и объявление типа не разрывны:
```
struct {
  поля структуры
} name_of_unonimus_struct;
```
Объявление структуры через typedef, используется для закрытых структур, типа дескрипторов, которые ходят между функциями и полльзователю не нужно лезть в нутрь структуры, используется редко.

Анонимная, badcase:
```
typedef struct {
  поля структуры
} new_type_name name_of_unonimus_struct;
```
Именованная, goodcase:
```
typedef struct type_of_struct {
  char field_0;
  int field_1;
  iny *p_field_2;
} new_type_name;

type_of_struct name_of_struct_0 = {}, 
               name_of_struct_1 = {.field_0 = '0', .field_1 = 1, .p_field_2 = NULL},
               name_of_struct_2 = {.p_field_2 = &name_of_struct_1.field_1};
```
### const struct
```
struct defaults_str_t {
    int num;
    size_t size;
};

const struct defaults_str_t defaults {
    .num = 100,
    .size = 10
};
```
### наследование структуры
```
struct str_name {
    int b;
    char a;
}

struct str_name_inc {
    struct str_name;
    char *p_st;
    bool t;
}
```
### Битовые поля
```
struct str_bit_fields {
    int a : 12; // может хранить число мксимум 2^12
    char b : 3; // может хранить число мксимум 2^3
}
```
Теперь размер этой структуры 15 бит, те 2 байта, где 1 бит в этих 2х байтах будет зарезервирован и не использован.

## enum

В первую очередь этот тип характеризуется как int, но последнее слово о типе enum за компилятором. Можно явно задать тип enum'а, но не факт что сработает. Это делается через задавание первого поля. Те если первое поле enum инициализируется как char, то возможно и компилятор определит данный enum как char.

Все поля не статических enum'ов видны как define'ы, поэтому следует придумывать осмысленные относительные к применению имена самих enum'ов и их полей.

### designated_init

Это расширение GCC. На примере вывода ошибок:

```
enum error {
    OK = 0,
    ERROR,
    MEM_FAIL
};

const char *const error_msg[] = {
    [OK] = "ok",
    [ERROR] = "error ocured",
    [MEM_FAIL] = "a memory was failed"
};
```

## arrays
Массивы можно терменировать NULL, что бы не передавть размер массива для работы с ним, как строки, это часто используется в линуксе:
`static const char *uri_group_names[] = {"proto", "ip", "host", "port", "path", NULL};`

## union
Позволяет хранить в одной области памяти разные типы данных, нужно для экономии места в памяти. Минус в том что в один момент времени там может храниться в один тип данных, перезапись которой может привести к UB.

```
union union_axample {
    char a;
    int b;
    float c;
} my_union;
```
Память выделяется под самый большой тип в `union`.