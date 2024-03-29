# kernel space

+ [kernel_vs_user](#kernel_vs_user)
+ [install](#install)
+ [reinstall](#reinstall)
+ [insmod](#insmod)
+ [rmmod](#rmmod)
+ [dmesg](#dmesg)
+ [echo_printk](#echo_printk)
+ [modinfo](#modinfo)
+ [lsmode](#lsmod)
+ [intrance](#intrance)
+ [format](#format)

+ [system_calls](#system_calls) 

+ [net_devices](#net_devices)
+ [block_devices](#block_devices)
+ [char_devices](#char_devices)

+ [hot_plug](#hot_plug)

+ [gdb](gdb)

+ [module_parameters](#module_parameters)
+ [kmalloc](#kmalloc)
+ [jiffie ](#jiffie)
+ [tasklets](#tasklets)
+ [threads](#threads)
+ [conteiners](#conteiners)
+ [work_queue](#work_queue)

## kernel_vs_user

Первое отличие кода модуля от пользовательского приложения состоит в том, что ему позволено выполнять супервизорные действия: привилегированные команды, операции с аппаратными портами, реакцию на прерывания. Вторым важным качественным отличием будет то, что пользовательское приложение может позволить себе определённую небрежность в завершении: не освобождать динамически выделенную память, не закрывать открытые файловые дескрипторы и тд - после завершения приложения такие действия за него «подчистит» ядро операционной системы. Следы же некорректных действий модуля останутся на всё время жизни системы (до её перезагрузки): выделенная, но не освобождённая модулю память, например, останется на всё это время как область с потерянными путями доступа, и не может быть освобождена. 

## preparing
### host
```
sudo apt-get install build-essential linux-headers-$(uname -r)
sudo apt-get install linux-source
sudo apt update
sudo apt upgrade
```
### raspberry pi
```
sudo apt-get install build-essential raspberry-linux-headers
sudo apt update
sudo apt upgrade
```

## reinstall
### host
```
sudo apt install --reinstall linux-headers-$(uname -r)
sudo apt update
sudo apt upgrade
```
### raspberry pi
```
sudo apt install --reinstall raspberry-linux-headers
sudo apt update
sudo apt upgrade
```

## insmod

`sudo insmod module.ko`

## rmmod

`sudo rmmod module` - without .ko

## dmesg

`asmlinkage int printk( const char * fmt, ... )` - used for printk to the journal from a code. Направляет выводимую строку демону системного журнала.

Первому параметру (форматной строке) может предшествовать (а может и не предшествовать) константа квалификатор, определяющая уровень сообщений. Определения констант для 8 уровней сообщений для printk:
```
> #define KERN_EMERG      "<0>"   /* system is unusable                   */
> #define KERN_ALERT      "<1>"   /* action must be taken immediately     */
> #define KERN_CRIT       "<2>"   /* critical conditions                  */
> #define KERN_ERR        "<3>"   /* error conditions                     */
> #define KERN_WARNING    "<4>"   /* warning conditions                   */
> #define KERN_NOTICE     "<5>"   /* normal but significant condition     */
> #define KERN_INFO       "<6>"   /* informational                        */
> #define KERN_DEBUG      "<7>"   /* debug-level messages                 */
```
examples:
```
printk( KERN_WARNING "string" );
printk( "<4>" "string" );
printk( "<4>string" );
printk( "string" );
```

`int pr_info( const char * fmt, ... )` - более современный аналог printk

Предшествующая константа конкатенируется с первым параметром.

`sudo dmesg` - show all journal messages

`dmesg | tail -n2` - show only two tail journal messages

`dmesg -n 5` - show only KERN_NOTICE level messeges. A defaul level is KERN_INFO (6)

## echo_printk

Альтернативный способ dmesg'у для вывода сообщений из ядра

`echo 8 > /proc/sys/kernel/printk`

## modinfo

`sudo modinfo ./module.ko` 

## lsmod

`lsmod` - show all insmoded modules

`lsmod  | head -n2` - show only two head insmoded modules

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
```
.text — код модуля (инструкуции);
.init.text — код инициализации модуля
.exit.text  — код завершения модуля; 
.modinfo — текст макросов модуля;
.data — инициализированные данные;
.bss — не инициализированные данные (Block Started Symbol)
```
.ko has several objects more then .o. Tnem used for loading of a module.

## system_calls

Системные вызовы позволяют доступ в драйвер из userspace. Ситемные вызовы: open, read, write, close;

## net_devices

чтение/запись от 1 байта пакетами

## block_devices

чтения/запись фиксированныим по размеру блоками

## char_devices

Самый распространённый тип устройств. Наиболее эффективный и лёгкий способ проложить интерфейс от kernelspace к userspace. Минимальный размер чтения/записи 1 байт потоком.

`int (*open)(struct inode *, struct file *);` - открыть символьное устройство для работы с ним.

Идентификаторы устройств:
Major - вендор

Minor - тип устройства

Префикс 'c' перед правами доступа к устройству говорит о типе символьного устройства.
TODO картинка

Ручное присваевание major устройств и minor, но dev_t нужно получить из макроса MKDEV:
```
#define <linux/fs.h>

int register_chrdev_region(dev_t first, unsigned int count, char *name);
```

Автоматическое присваевание major устройству:
```
#define <linux/fs.h>

int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
```

Что бы перевести major и minir в int из dev_t:
```
#include <linux/types.h>
#include <linux/kdev_t.h>

MAJOR(dev_t dev);
MINOR(dev_t dev);

```

Наоборот что бы перевести major и minir в dev_t из int:
```
#include <linux/types.h>
#include <linux/kdev_t.h>

MKDEV(int major, int minor);

```

`void unregister_chrdev_region(dev_t first, usigned int count);` - отрегистрировать символььное устройство по завершению

node - 

В модуле должны быть определны операции с фаломи file operations.

Есть два пути нинициализации символьного устройства: статическая и динамическая.

Статическая инициализация:
```
#include <linux/cdev.h>

struct cdev *cdev_alloc (void);
void cdev_init(struct cdev *cdev, struct file_operations *fops);
int cdev_add(struct cdev *cdev, dev_t dev, unsigned count);
```

`void cdev_del(struct cdev *cdev);` - удаление символьного устройства;

После `insmod` нужно сождать node:
```
mknod -m a=r xwrand c 248 0 
```
где: хз (all=read те всем можно только читать) (имя девайса) (тип c==char) MAJOR MINOR

## hot_plug

+ обнаружение устройства
+ поиск драйвера
+ загрузка драйвера

Для автомвтической загрузки драйвера устройсва в модуле определяется соответвующая структура через `MODULE_DEVICE_TABLE(type, name);`, на примере `pci_device_id` и вымышленных MAJOR 0x10ff и MINOR 0x0001 0x0002:
```
static int my_major = 0x10ff, my_minor_1 = 0x0001, my_minor_2 = 0x0002;

static const struct pci_device_id table[] = {
	{PCI_DEVICE(my_major, my_minor_1)},
	{PCI_DEVICE(my_major, my_minor_2)},
    {0}
};

MODULE_DEVICE_TABLE(pci, table);

```

## gdb

можно юзать, поищи как и потренируйся на распберри и цинке. ну и конечно потом законспектируй

Аналоги: kdb, kgdb, crash, file system;

## module_parameters

Требует: `#include <linux/moduleparam.h>`

Для передачи типов как параметров в модуль используется макрос:
+ обычные типы: module_param(name, type, perm);
+ именновынны типов: module_param_named(name, value, type, perm);
+ массивы: module_param_array(name, type, num, perm);
+ строки: module_param_string(name, string, len, perm);

```
/*
 * @ name - имя параметра;
 * @ type - тип передаваемого параметра: byte, short, ushort, int, uint, long, ulong, charp, bool, invbool;
 * @ perm - флаги прав доступа к параметру, 
 * отображаемому как путевое имя в системе /sys: S_IRWXU 00700     
 *                                               S_IWUSR 00200
 *                                               S_IXUSR 00100
 *                                               S_IRWXG 00070
 *                                               S_IRGRP 00040
 *                                               S_IWGRP 00020
 *                                               S_IXGRP 00010
 *                                               S_IRWXO 00007
 *                                               S_IROTH 00004
 *                                               S_IWOTH 00002
 *                                               S_IXOTH 00001
 */

module_param(name, type, perm); 
```
Пример: `module_param(thread_cnt, ulong, S_IRUSR | S_IRGRP | S_IROTH);`

```
/*
 * @ name - символическое имя параметра;
 * @ value - идентифицирует в списке параметров передаваемую переменную (?);
 * @ type - тип передаваемого параметра;
 * @ perm - флаги прав доступа к параметру;
 */

module_param_named(name, value, type, perm); 
```
Пример: `module_param_named(some_string, "some_string", charp, 0);`

```
/*
 * @ name - символическое имя параметра;
 * @ type - тип передаваемого параметра;
 * @ num  - размер массива (опционально, можно задать как NULL);
 * @ perm - флаги прав доступа к параметру;
 */

module_param_array(name, type, num, perm); 
```
Пример: `module_param_array(arr, int, NULL, S_IRUSR|S_IWUSR);`

```
/*
 * @ name - символическое имя строки;
 * @ string - строка;
 * @ len  - размер строки;
 * @ perm - флаги прав доступа к параметру;
 */

module_param_string(name, string, len, perm); 
```
Пример: 
```
static char func_name[NAME_MAX] = "do_fork";
module_param_string(func, func_name, NAME_MAX, S_IRUGO);
```

1. создать переменную для получения параметра (должна быть `static` и `__initdata`), `__initdata` - говорит о том что память переменной может быть освобождена после выполнения `__init` функции;
2. принять входной аргумент через макрос module_param;
3. описать входной аргумент через `MODULE_PARM_DESC`;

```
/*
 * Пример
 */
static int __initdata param = 0;
module_param(param, int, 0); 
MODULE_PARM_DESC(param, "Some param");

static int __initdata myintArray [ARR_SIZE] = {0};
module_param_array(myintArray, int, ARR_SIZE, 0);
MODULE_PARM_DESC(myintArray, "An array of integers");
```

## kmalloc

Всегда нужно освобождать, тк в отличие от userspace где память освобождается после завершения программы, в kernelspace, память остаётся выделенной.

Выделение из стандартного пула ядра:
```
#define KBUF_SIZE 1024

char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
```

## tasklets

TODO

## jiffie 

TODO

BogoMIPS - величена скорости производительности процессора, инструкций в секунду.

## threads

Используется для выполнеия операций в фоне. Тк драйверы ядра являются асинхронными, то они регируют на события и выполняют соответвующую функцию, но иногда требуются более сложные операции (расчеты и тп), где и используются потоки ядра. Имеют доступ к памяти ядра.

Требует: `#include <linux/kthread.h>`

```
/*
 * Первый способ созданияе потока ядра.
 *
 * @ int (*threadfn)(void *data)) - указатель на функцию для запуска в потоке;
 * @ void *data - данные для потока;
 * @ const char namefmt[] - имя потока;
 * @ ... - формат имени потока (как в printf);
 *
 * @ return - handler потока или ERR_PTR(-ENIMEM или -EINTR);
 */
struct task_struct *kthread_create(int (*threadfn)(void *data)), void *data, const char namefmt[], ...); 
```

Поток по умолчанию, после создания, спит. Для его запуска используется функция `void wake_up_process(struct task_struct *)`

```
struct task_struct *p_k = thread_create(p_thread_foo, data, THREAD_NAME);

if (0 == IS_ERR(p_k)) {
	wake_up_process(p_k);
}
```
На самом деле `kthread_create` является хэлпером для функции `kthread_create_on_node` в которую указывается конкретный номер (NUMA - non-uniform memory access) cpu, точнее его память, для запуска потока или NUMA_NO_NODE если не важно на каком ядре запускать поток.

TODO: откуда взять списк NUMA?

Но если нужно создать и сразу запустить поток используется хэлпер функция (в данном случае это макрос) `kthread_run()`. По факту этот макрос есть сочетание `kthread_create` и `wake_up_process`. 

```
/*
 * Второй и обще принятый способ созданияе потока ядра.
 *
 * @ int (*threadfn)(void *data)) - указатель на функцию для запуска в потоке;
 * @ void *data - данные для потока;
 * @ const char namefmt[] - имя потока;
 * @ ... - формат имени потока (как в printf);
 *
 * @ return - handler потока или ERR_PTR(-ENIMEM или -EINTR);
 */
struct task_struct *kthread_run(int (*threadfn)(void *data)), void *data, const char namefmt[], ...);
```
Чтобы выйти из потока можно использовать `return` или `do_exit(some_ret_code)`.

Что бы остановить поток используются `int kthread_stop(struct task_struct *k)` и `int kthread_should_stop(void)`.

## conteiners

TODO

## work_queue

work queue - очереди работ, абстракция отложенной работы на базе потоков, один из механизмов bottom half;

В отличии от taskled может спать, эти и решеается выбор межу task и work queue. Те если нужно будет спать то work queue иначе task. Хэндлеры work queue укладываются в связанный списк для создание очереди для выполнения, после этого поток выполнения просыпается, достаёт хэндлер из списка, извлекает функцию выполнения из хэндлера, после удаляется из списк хэндлер, выполняет функцию, после засыпает.

(?)Два способа создания work queue (статическая и динамическкая). После инициализации work queue можно отправить в очередь (можно сразу, а можно с задержкой).

`void flush_scheduled_work(void);` - принудительное выполнение всех задиспаченных work queue.
`int cancel_delayed_work(struct work_struct *work);` - остановить и закончить определённый work queue.