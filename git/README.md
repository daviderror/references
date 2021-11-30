# git

1.  [install](#install)
2.  [building](#building)
3.  [uninstall](#uninstall)
4.  [add files](#add\files)

## install

`$ sudo apt-get update`

`$ sudo apt-get install git`

`$ git --version`

`$ git config --global user.name "drakonof"`

`$ git config --global user.email "soikadigital@gmail.com"`

## building

It is alternative way to install of git.

`$ sudo apt-get update`

`$ sudo apt-get install libcurl4-gnutls-dev libexpat1-dev gettext libz-dev libssl-dev asciidoc xmlto docbook2x`

`$ git clone https://git.kernel.org/pub/scm/git/git.git`

`$ make all doc info prefix=/usr"`

`$ sudo make install install-doc install-html install-info install-man prefix=/usr`

`$ git --version`

`$ git config --global user.name "drakonof"`

`$ git config --global user.email "soikadigital@gmail.com"`

## uninstall

`$ sudo apt-get remove git` - just to remove

`$ sudo apt-get remove --auto-remove git` - to remove git with it's dependents

`$ sudo apt-get purge --auto-remove git` - to remove configuration and data files of git and it's dependencies

## add files