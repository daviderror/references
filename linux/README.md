# linux_mastering

ebpf, modbus, ubus, mqtt

bc, menuconfig

Линукс - ядро, набор исходников и бинарников, загружаемых по старту компьютера.

Дистрибутив - набор утилит и програм идущие с ядром. Могут отличаться пакетными менеджерами (?).

RPM пакеты в: Red Hat Enterprise Linux, Fedora, CentOS
DEB        в: Open Suse, Debian, Ubuntu, Gentoo

Подготовка: `sudo apt-get install build-essential vim git bc libncurses5-dev`

kernel.org, lwn.net, lxr.free-electrons.com, vger.kernel.org, linuxfoundation.org, lkml.org, kernelnewbies.org, tldp.org, ibm.com/developerworks/linux


## keyboard layout

По дефолту: super+space (виндовс+пробел)

```
sudo apt install gnome-tweaks
gsettings set org.gnome.desktop.input-sources xkb-options "['grp:alt_shift_toggle']"
```

## terminal

`dconf write /org/gnome/desktop/sound/event-sounds false` - выключить звук в терминале
`dconf write /org/gnome/desktop/sound/event-sounds true` - включить звук в терминале

## PATH
 
`export PATH=$PATH:/app_dir/bin` - разово для текущего сеанса

Такой синтаксис используется для добавления нового пути в переменную. Символ : является символом разделения путей в linux.

`nano ~/.bashrc`

В конец этого файла export PATH=$PATH:/app_dir/bin и затем `source ~/.bashrc`. Проверить, что всё прописалось: `echo $PATH`