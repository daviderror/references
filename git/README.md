# git

1.  [installing](#installing)
2.  [building](#building)
3.  [uninstalling](#uninstalling)
4.  [adding](#adding)
5.  [removing](#removing)
6.  [committing](#committing)

## installing

To install:

`$ sudo apt-get update`

`$ sudo apt-get install git`

To check is it complete:

`$ git --version`

To tell Git who you are, run the following two commands:

`$ git config --global user.name "drakonof"`

`$ git config --global user.email "soikadigital@gmail.com"`

## building

It is alternative way to install of git.

To install:

`$ sudo apt-get update`

`$ sudo apt-get install libcurl4-gnutls-dev libexpat1-dev gettext libz-dev libssl-dev asciidoc xmlto docbook2x`

`$ git clone https://git.kernel.org/pub/scm/git/git.git`

`$ make all doc info prefix=/usr"`

`$ sudo make install install-doc install-html install-info install-man prefix=/usr`

To check is it complete:

`$ git --version`

To tell Git who you are, run the following two commands:

`$ git config --global user.name "drakonof"`

`$ git config --global user.email "soikadigital@gmail.com"`

## uninstalling

`$ sudo apt-get remove git` - just to remove

`$ sudo apt-get remove --auto-remove git` - to remove Git with it's dependents

`$ sudo apt-get purge --auto-remove git` - to remove configuration and data files of Git and it's dependencies

## adding

`$ git add .` - to add all files in a repository

`$ git add /dir/dir_1` - to add all files in a repository

`$ git add file.txt` - to add only one file

`$ git add file.txt file_1.txt file_2.txt` - to add several files

## removing

`$ git rm --cached my-file.ts` - to remove only one file

`$ git rm -r --cached .` - to remove all files from a Git cache repository

## committing

`$ git commit -m "Comment for the commit"` - to commit to the Git repository

## pushing

`$ git push`

## clonning

`$ git clone git@github.com:drakonof/repository.git`

## pulling

`$ git pull`

## initialization

To initialize a new Git repository

`echo "# new_repository_name" >> README.md` - https://github.com/Drakonof/references/tree/main/bash#echo

`git init`

`git add README.md`

`git commit -m "first commit"`

`git remote add origin git@github.com:drakonof/new_repository_name.git`

`git push -u origin master`