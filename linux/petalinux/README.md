
## about

Petalinux - набор программных инструментов для конфигурации и оптимихации Linux для процессорных систем компании Xilinx.

Рабочий процесс состоит из нескольких этапов в которых задействованы Vivado и SDK/Vitis, при этом сам Petalinux является финалным элментом.

## install
```
sudo apt get install tofrodos iproute gawk gcc git-core make net-tools ncurses-dev tftpd zlib1g-dev flex bison a32-libs lib32ncursesw5 lib32gomp1 libssl-dev libselinux1 gnupg wget diffstat chrpath socal xterm autoconf libtool tar unzip texinfo gcc-multilib  build-essential libsdl1.2-dev libglib2.0-dev zlib1g:386 screen pax gzip
sudo chmod +x ~/Downloads/petalinux-v2017.4-final-installer.run
sudo chmod 755 petalinux_install_dir/
sudo chmod 755 /tmp <- просто так надо
~/Downloads/petalinux-v2017.4-final-installer.run petalinux_install_dir/
```

`source petalinux_install_dir/settings.sh`

## flow

+ Подготовка (по одному из сценариев)
+ Сборка и прожжег

### Подготовка Сценарий 1
+ vivado 
	* project
	* export hardware
+ SDK 
	* petalinuxrepository
	* FSBL
	* BSP
	* config BSP for u-boot and Linux 

### Подготовка Сценарий 2
+ create template project or based on exist BSP
+ config
    * FSBL	
    * u-boot
	* config
	* kernel
	* rootfs

###  Настройка компонентов
+ Добавление программ
+ Добавление модулей ядра
+ Активировать программы и модули через `petalinux-config -c rootfs`

### Сборка и прожжег
+ build
+ package
+ Platform booting


## petalinux_create
`source /tools/Xilinx/Vivado/2019.1/settings64.sh`

Далее по одному из сценариев

### Сценарий 1
`petalinux-create -t project -s <bsp-path>`

### Сценарий 2
`petalinux-create -t project --template <platform> -n <project-name>`


## petalinux_config
Далее по одному из сценариев.

### Первая конфигурация после создания проекта
`petalinux-config --get-hw-description=<hdf-path>` - настройка параметров системного уровня и обновлениеконфигурации оборудования.

### Последующие конфигурации
`petalinux-config` - настройка параметров системного уровня.


## petalinux_build
`petalinux-build`

## petalinux_boot

### Быстрая эмуляция из папкис проектом
`petalinux-boot --qemu --kernel`

### Формирование BOOT.bin для платформы
`petalinux-package --boot --fsbl images/linux/zynqmp_fsbl.elf --u-boot images/linux/u-boot.elf --pmufw images/linux/pmufw.elf --fpga images/linux/*bit -force`


## apps_add

+ `petalinux-create -t apps -n mpsochello --enable`
+ `cd <petalinux-proj-path>/project-spec/meta-user/recipes-apps/mpsochello`
+ Заменить `mpsochello.c` на свой собственный файл.
+ Отредактировать `mpsochello.bb` для автозапуска программы. todo: пример 

## module_add

+ `petalinux-create -t modules -n harddriver`
+ `cd <petalinux-proj-path>/project-spec/meta-user/recipes-modules/harddriver`
+ Заменить `harddriver.c` на свой собственные файлы.

## image_writing_to_board

+ INITRAMFS
	* отформатировать память в FAT32
	* записать в неё BOOT.bin и image.ub
+ INITSD
	* разделить память на 2 раздела. 1 (500MB)- отформатировать в FAT32 , 2 - отформатировать в ext4.
	* записать в FAT32 раздел BOOT.bin и image.ub, а в ext4 файл rootfs.tar.gz (находится в папке с BOOT.bin)