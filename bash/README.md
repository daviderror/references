# Useful Bash scripts

1. [ls](#ls)
2. [mkdir](#mkdir)
3. [cd](#cd)
4. [whoami](#whoami)
5. [su](#su)
6. [sudo](#sudo)
7. [echo](#echo)
8. [cat]


## ls

ls - list directory contents

ls [options] [directory]

https://man7.org/linux/man-pages/man1/ls.1.html

`$ ls`

<img src="https://github.com/Drakonof/references/tree/main/bash/docls.png" width="1000"> 

`$ ls -l` use a long listing format

<img src="https://github.com/Drakonof/references/tree/main/bash/docls_l.png" width="1000"> 

`$ ls -l /etc/network/`

<img src="https://github.com/Drakonof/references/tree/main/bash/docls_l_dir.png" width="1000"> 


aliases: `$ ll` == `$ ls -l`


## mkdir

mkdir - make directories

mkdir [options] directory name

https://man7.org/linux/man-pages/man1/mkdir.1.html

`$ mkdir some_dir`

<img src="https://github.com/Drakonof/references/tree/main/bash/docmkdir.png" width="1000"> 

`$ mkdir "some_dir"`

<img src="https://github.com/Drakonof/references/tree/main/bash/docmkdir 2.png" width="1000">

## cd

cd - change directory

cd [options] [directory]

https://man7.org/linux/man-pages/man1/cd.1p.html

`$ cd` - to home directory

<img src="https://github.com/Drakonof/references/tree/main/bash/doccd.png" width="1000">

`$ cd -` - to previous directory

<img src="https://github.com/Drakonof/references/tree/main/bash/doccd_prew.png" width="1000">

`$ cd ../` - to one below directory

<img src="https://github.com/Drakonof/references/tree/main/bash/doccd_one_below.png" width="1000">

`$ cd ../../` - to two below directories, and so on accordingly number of ../

<img src="https://github.com/Drakonof/references/tree/main/bash/doccd_two_below.png" width="1000">

`$ cd /dir1/dir2/` - in two directories from the root directory, from any directory

 <img src="https://github.com/Drakonof/references/tree/main/bash/doccd_two_dir.png" width="1000">

`$ cd /root dir1/root dir2/` - in two directories from the root directory, from any directory

 <img src="https://github.com/Drakonof/references/tree/main/bash/doccd_two_root_dir.png" width="1000">

`$ cd /` - to a root directory, from any directory

<img src="https://github.com/Drakonof/references/tree/main/bash/doccd_root.png" width="1000">

 ## whoami

whoami - who am i

whoami [options]

https://man7.org/linux/man-pages/man1/whoami.1.html

`$ whoami`

<img src="https://github.com/Drakonof/references/tree/main/bash/docwhoami.png" width="1000">

 ## su

 su - run a command with substitute user and group ID 

 su [options] [-] [user [argument...]]

https://man7.org/linux/man-pages/man1/su.1.html

`$ su`

<img src="https://github.com/Drakonof/references/tree/main/bash/docsu.png" width="1000">

cntr + d - to leaving su

## sudo

sudo — execute a command as another user

sudo -h | -K | -k | -V

sudo -v [-ABknS] [-g group] [-h host] [-p prompt] [-u user]

sudo -l [-ABknS] [-g group] [-h host] [-p prompt] [-U user][-u user] [command]

sudo [-ABbEHnPS] [-C num] [-D directory] [-g group] [-h host][-p prompt] [-R directory] [-T timeout] [-u user] [VAR=value][-i | -s] [command]

https://man7.org/linux/man-pages/man8/sudo.8.html

`$ sudo ls`

<img src="https://github.com/Drakonof/references/tree/main/bash/docsudo ls.png" width="1000">

## echo

echo — write arguments to standard output.

echo [option(s)] [string(s)]

https://man7.org/linux/man-pages/man1/echo.1p.html

`$ echo Hello World` - write a string to standard output
`$ echo -n hello world` - write a string to standard output without a new line after
`$ echo -n hello world > hello.txt` - write a string to a file

