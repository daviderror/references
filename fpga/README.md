# fpga

+ [abstraction](#abstraction)
+ [digital_abstraction](#digital_abstraction)
+ [number_systems](#number_systems)
+ [byte](#byte)

## abstraction

**абстаркция** - исключение из рассмотрения тех элементов системы, которые в данном конкретно случае несущественны для понимания работы этой системы.

**termenal** - контакт электронного устройства.

**analog circuits** - аналоговые схемы в которых полупродниковые устройства соединены в функцианальные компоненты, значения на входе и выходе которых измеряются в непрерывном диапозоне.

**digital circuits** - схемы в которых полупродниковые устройства соединены в функцианальные компоненты, значения на входе и выходе которых измеряются в дискретных уровнях напряжения (логические 0 и 1).

**Операционная система** - программа управляющая операциями нижнего уровня и управлением памятью.

**Иерархичность** - разделение системы на отдельные модули, а далее разделение этих модулей на подмодули и так далее до удобного уровня понимания системы.

**Модульность** - каждый модуль в системе имеет четко определенную функциональность и набор интерфейсов для соединения с другими модулями без побочных эфектов.

**Регулярность** - соблюдение единобразия при проектировании модулей системы.

## digital_abstraction

**Бит** - от binary digital, двоичный разряд. D = lnN (D - объём информации) => ln2 = 1 те 2 значения (0 и 1) умещаются в 1 бит информации.

**Будева логика** - логика испоьзующая двоичные переменные (истина и ложь, 1 и 0, true и false, high и low).

## number_systems

Распространённые системы счисления по основанию (base): двоичные(binary 0, 1), десятичные(decimal 0-9), восьмеричные(0-7), шестнадцатеричные(hexadecimal 0-9 и далее a-f);

Преобразование чисел из одной системы счисления в другую:
```
Пример для числа 22:

2 -> 10: 10110 == 22
         10110 = 1*2^4 + 0*2^3 + 1*2^2 + 1*2^1 + 0*2^0 = 16 + 0 + 4 + 2 + 0 = 22;
2 -> 16: 10110 == 16
         10110 = 0001 и 0110 = 0*2^3 + 0*2^2 + 0*2^1 + 1*2^0 и 0*2^3 + 1*2^2 + 1*2^1 + 0*2^0 = 1 и 6 = 16

10 -> 2: 22 == 10110
         4 наибольшая степень 2х в числе 22 то в разряде 4 будет 1 
         22 - 16 = 6 тк 2^3 = 8 > 6ти то в разряде 3 будет 0
         2 наибольшая степень 2х в числе 6 то в разряде 2 будет 1
         6 - 4 = 2 >= 2х, это 2 в степени 1, то в разряде 1 будет 1
         2 - 2 = 0 то в разряде 0 будет 0
10 -> 16: 22 == 16
          1 наибольшая степень 16ти в числе 22 то в разряде 1 будет 1
          22 - 16 = 6 то в разряде 0 будет 6

16 -> 10: 16 == 22
          16 = 1 * 16^1 + 6*16^0 = 16 + 6 = 22
16 -> 2: 16 == 10110
         2 - 1 = 1 то в разряде 0 старшего нибла будет 1 и
         8 > 6ти то в разряде 3 будет 0 
         2 наибольшая степень 2х в числе 6 то в разряде 2 будет 1
         6 - 4 = 2, это 2 в степени 1, то в разряде 1 будет 1
         2 - 2 = 0 то в разряде 0 младшего нибла будет 0 
```

## byte

**байт (byte)** - группа из 8ми [бит](#digital_abstraction).

Байт представляет 2^8 = 256 цифровых комбинаций.

**Полубайт (nibble)*** - группа из 4х бит.

Полубайт представляет 2^4 = 16 цифровых комбинаций.

**Слово (word)** - величена, размер которой, определяется архитектурой конкретного процессора.

**Наименее значимый бит (lsb, least significant bit)** - самый младший правый(в LE)/левый(в BE) бит слова.

**Наиболее значимый бит (msb, most significant bit)** - самый старший левый(в LE)/правый(в BE) бит слова.

**Наименее значимый байт (LSB, least significant bit)** - самый младший правый(в LE)/левый(в BE) байт слова.

**Наиболее значимый байт (MSB, most significant bit)** - самый старший левый(в LE)/правый(в BE) байт слова.

Килобит(Кб) = 2^10 = 1024 бит, Мегабит(Мб) = 2^20 = 1048576 бит, Гигобит(Гб) = 2^30 = 1073741824 бит, Терабит(Тб) = 2^40 = 1099511627776 бит;

Килобайт(КБ) = 2^10 = 1024 байт = 8192 бит, Мегабайт(МБ) = 2^20 = 1048576 байт = 8388608 бит, Гигобайт(ГБ) = 2^30 = 1073741824 байт = 8589934592 бит, Терабайт(ТБ) = 2^40 = 1099511627776 байт = 8796093022208‬ бит;

Обычно объём памятей измеряется в байтах, а скорость передачи информации в битах.


## Комбинационная логика
