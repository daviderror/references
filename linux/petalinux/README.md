## install
```
sudo apt get install tofrodos iproute gawk gcc git-core make net-tools ncurses-dev tftpd zlib1g-dev flex bison a32-libs lib32ncursesw5 lib32gomp1 
sudo chmod +x ~/Downloads/petalinux-v2017.4-final-installer.run
sudo chmod 755 petalinux_install_dir/
sudo chmod 755 /tmp <- просто так надо
~/Downloads/petalinux-v2017.4-final-installer.run petalinux_install_dir/
```

`source petalinux_install_dir/settings.sh`


## petalinux_create

### via bsp
`petalinux-create -t project -s dir_to_paltform_bsp/some_platform_bsp.bsp`


## petalinux_config

`petalinux-config` - общая config настройка

## petalinux_build

`petalinux-build`

## petalinux_boot

`petalinux-boot --qemu --kernel` - быстрая эмуляция из папкис проектом