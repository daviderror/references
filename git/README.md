# git

[installing](#installing)
[building](#building)
[uninstalling](#uninstalling)
[configs](#configs)
[adding](#adding)
[removing](#removing)
[committing](#committing)
[initialization](#initialization)
[pulling](#pulling)
[clonning](#clonning)
[pushing](#pushing)
[gitignore](#gitignore)

## installing

    To install:

`sudo apt-get update`

`sudo apt-get install git`

    To check is it complete:

`git --version`





## building

    It is alternative way to install of git.

    To install:

`sudo apt-get update`

`sudo apt-get install libcurl4-gnutls-dev libexpat1-dev gettext libz-dev libssl-dev asciidoc xmlto docbook2x`

`git clone https://git.kernel.org/pub/scm/git/git.git`

`make all doc info prefix=/usr"`

`sudo make install install-doc install-html install-info install-man prefix=/usr`

    To check is it complete:

`git --version`

## configs

    To tell Git who you are, run the following two commands:
```
git config --global user.name "drakonof"
git config --global user.email "soikadigital@gmail.com"
```

`git config --list --global` - посмотреть глобальные конфмгурации

     Убрать глобальные настройки:
```
git config --unset user.name
git config --unset user.email
```
`git config --remove-section user` - удалить всю секцию пользователя

## uninstalling

`sudo apt-get remove git` - just to remove

`sudo apt-get remove --auto-remove git` - to remove Git with it's dependents

`sudo apt-get purge --auto-remove git` - to remove configuration and data files of Git and it's dependencies

## aliases

`git config --global alias.[alias_name] 'config --unset user.email'` - для команд гита
`git config alias.[alias_name] '!echo "hello"; echo "world"'` - для системных команд. Выполняется через '!'

## adding

`git add .` - to add all files in a repository

`git add /dir/dir_1` - to add all files in a repository

`git add file.txt` - to add only one file

`git add file.txt file_1.txt file_2.txt` - to add several files

## removing

`git rm --cached my-file.ts` - to remove only one file

`git rm -r --cached .` - to remove all files from a Git cache repository

## committing

`git commit -m "Comment for the commit"` - to commit to the Git repository

## pushing

`git push`

## clonning

`git clone git@github.com:drakonof/repository.git`

## pulling

`git pull`

## initialization

    To initialize a new Git repository

`echo "# new_repository_name" >> README.md` - https://github.com/Drakonof/references/tree/main/bash#echo

`git init`

`git add README.md`

`git commit -m "first commit"`

`git remote add origin git@github.com:drakonof/new_repository_name.git`

`git push -u origin master`

## gitignore

    .gitignore file exludes files or dirs from committing to a Git repository

    Example:

`*.hex`

`*.bin`

`src/bin/*.json`

`!src/bin/.sone_json.json`

`dir/build/*`

`!dir/biuld/debug/`