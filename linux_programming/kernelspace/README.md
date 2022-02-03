# kernel space

0.  [kernel_vs_user](#kernel_vs_user)
1.  [install](#install)
2.  [reinstall](#reinstall)
3.  [insmod](#insmod)
4.  [rmmod](#rmmod)
5.  [dmesg](#dmesg)
6.  [echo_printk](#echo_printk)
7.  [modinfo](#modinfo)
8.  [lsmode](#lsmod)
9.  [intrance](#intrance)
10. [format](#format)

## kernel_vs_user

Первое отличие кода модуля от пользовательского приложения состоит в том, что ему позволено выполнять супервизорные действия: привилегированные команды, операции с аппаратными портами, реакцию на прерывания. Вторым важным качественным отличием будет то, что пользовательское приложение может позволить себе определённую небрежность в завершении: не освобождать динамически выделенную память, не закрывать открытые файловые дескрипторы и тд - после завершения приложения такие действия за него «подчистит» ядро операционной системы. Следы же некорректных действий модуля останутся на всё время жизни системы (до её перезагрузки): выделенная, но не освобождённая модулю память, например, останется на всё это время как область с потерянными путями доступа, и не может быть освобождена. 

## preparing

`$ sudo apt-get install build-essential linux-headers-$(uname -r)`

`$ sudo apt-get install linux-source`

`$ sudo apt update`

## reinstall

`$ sudo apt install --reinstall linux-headers-$(uname -r)`

`$ sudo apt update`

## insmod

`$ sudo insmod module.ko`

## rmmod

`$ sudo rmmod module` - without .ko

## dmesg

`asmlinkage int printk( const char * fmt, ... )` - used for printk to the journal from a code. Направляет выводимую строку демону системного журнала.

Первому параметру (форматной строке) может предшествовать (а может и не предшествовать) константа квалификатор, определяющая уровень сообщений. Определения констант для 8 уровней сообщений для printk:

    > #define KERN_EMERG      "<0>"   /* system is unusable                   */
    > #define KERN_ALERT      "<1>"   /* action must be taken immediately     */
    > #define KERN_CRIT       "<2>"   /* critical conditions                  */
    > #define KERN_ERR        "<3>"   /* error conditions                     */
    > #define KERN_WARNING    "<4>"   /* warning conditions                   */
    > #define KERN_NOTICE     "<5>"   /* normal but significant condition     */
    > #define KERN_INFO       "<6>"   /* informational                        */
    > #define KERN_DEBUG      "<7>"   /* debug-level messages                 */

examples:
     printk( KERN_WARNING "string" );
     printk( "<4>" "string" );
     printk( "<4>string" );
     printk( "string" );

Предшествующая константа конкатенируется с первым параметром.

`$ sudo dmesg` - show all journal messages

`$ dmesg | tail -n2` - show only two tail journal messages

`$ dmesg -n 5` - show only KERN_NOTICE level messeges. A defaul level is KERN_INFO (6)

## echo_printk

Альтернативный способ dmesg'у для вывода сообщений из ядра

`$ echo 8 > /proc/sys/kernel/printk`

## modinfo

`$ sudo modinfo ./module.ko` 

## lsmod

`$ lsmod` - show all insmoded modules

`$ lsmod  | head -n2` - show only two head insmoded modules

## intrance

An intrance point: `static int __init module_init(void)  {...}` and `module_init(hello_init);`

An exit point: `static int __init module_exit(void)  {...}` and `module_exit(hello_exit);` - both are not necessary 

Функция завершения по своему прототипу не имеет возвращаемого значения, и, поэтому, она даже не может сообщить о невозможности каких-либо действий, когда она уже начала выполняться. Идея состоит в том, что система при rmmod сама проверит допустимость вызова функции завершения, и если они не соблюдены, просто не вызовет эту функцию.

Ещё один не документированный способ описания этих функций: воспользоваться непосредственно их предопределёнными именами, а именно init_module() и cleanup_module(). Это может быть записано так:

`int init_module( void ) {...} `

`void cleanup_module( void ) {...}`

При такой записи необходимость в использовании макросов module_init() и module_exit() отпадает, а использовать квалификатор static с этими функциями нельзя (они должны быть известны при связывании модуля с ядром). Но это не очень хорошая практика тк читаемость кода ухудшается.

## format

`$ objdump -t module.ko` - shows an information about .ko files

.ko it is ELF. 

    > .text — код модуля (инструкуции);
    > .init.text — код инициализации модуля
    > .exit.text  — код завершения модуля; 
    > .modinfo — текст макросов модуля;
    > .data — инициализированные данные;
    > .bss — не инициализированные данные (Block Started Symbol)

.ko has several objects more then .o. Tnem used for loading of a module.