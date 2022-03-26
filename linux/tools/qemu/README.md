# qemu

+ [preparing](#preparing)
+ [installing](#installing)
+ [utils](#utils)
+ [hdd_creation](#hdd_creation)
+ [OS_installing](#OS_installing)
+ [launch](#launch)
+ [additionally](#additionally)

## preparing

Включить поддержку виртуализации в БИОС.

## installing
```
$ sudo apt update 
$ sudo apt install qemu-kvm qemu
```

## utils

    Эмулятор qemu создает много команд, но их можно разделить на группы:
        qemu-архитектура - эмуляция окружения пользователя для указанной архитектуры;
        qqemu-system-архитектура - эмуляция полной системы для архитектуры;
        qqemu-img - утилита для работы с дисками;
        qqemu-io - утилита для работы с вводом/выводом на диск;
        qqemu-user - оболочка для qemu-архитектура, позволяет запускать программы других архитектур в этой системе;
        qqemu-system - оболочка для qemu-system-архитектура, позволяет полностью эмулировать систему нужной архитектуры.

## hdd_creation
```
$ sudo qemu-img create -f qcow2 virt_hdd_name.qcow2 40G
```
     qemu-img             : утилита для работы с дисками;
     -f                   : файл создаётся новый;
     qcow2                : тип файла виртуального диска;
     <virt_hdd_name>.qcow2: имя файла виртуального диска с расширением;
     <40>G                : размер виртуального диска;

     Типы файлов: 

     Суффиксы для размера виртуального диска: k, M, G, T, P => kilo-, mega-, giga-, tera-, peta-

## OS_installing
```
$ sudo qemu-system-x86_64 -hda virt_hdd_name.qcow2 -boot d -cdrom /full_path_for_os_mane/os_name.iso -m 8196 -enable-kvm
```
     qemu-system-x86_64                          : эмуляция полной системы для архитектуры;
     -hda <virt_hdd_name>.qcow2                  : имя виртуального диска;
     -boot d                                     : 
     -cdrom </full_path_for_os_mane/os_name>.iso : полный путь до образа ОС;
     -m <8196>                                   : колличество выделяемой оперативнорй памяти;
     -enable-kvm                                 : значительно ускаряет работу qemu;

     Следующим шагом установка ОС. Для Ubuntu: TODO ссылка.

## launch
```
$ sudo qemu-system-x86_64 -hda virt_hdd_name.qcow2 -m 8196 -enable-kvm
```

## additionally

`sudo systemctl get-default` - текущее состояние;

`systemctl set-default multi-user.target` - отключить графику:

`systemctl set-default graphical.target` - включить графику
