# Useful Bash scripts

1.  [ls](#ls)
2.  [mkdir](#mkdir)
3.  [cd](#cd)
4.  [whoami](#whoami)
5.  [su](#su)
6.  [sudo](#sudo)
7.  [echo](#echo)
8.  [cat](#cat)
9.  [rm](#rm)
10. [ps](#ps)
11. [kill](#kill)
12. [stat](#stat)
13. [alias](#alias)
14. [grep](#grep)
15. [man](#man)
16. [ln](#ln)
17. [df](#df)
18. [chmod](#chmod)
19. [mv](#mv)
20. [setsid](#setsid)
21. [find](#find)
22. [halt](#halt)
23. [poweroff](#poweroff)
24. [reboot](#reboot)
25. [shutdown](#shutdown)

## ls

ls - list directory contents

ls [options] [directory]

https://man7.org/linux/man-pages/man1/ls.1.html

`$ ls`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ls.png" width="1000"> 

`$ ls -l` use a long listing format

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ls_l.png" width="1000"> 

`$ ls -l /etc/network/`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ls_l_dir.png" width="1000"> 


aliases: `$ ll` == `$ ls -l`


## mkdir

mkdir - make directories

mkdir [options] directory name

https://man7.org/linux/man-pages/man1/mkdir.1.html

`$ mkdir some_dir`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/mkdir.png" width="1000"> 

`$ mkdir "some_dir"`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/mkdir 2.png" width="1000">

## cd

cd - change directory

cd [options] [directory]

https://man7.org/linux/man-pages/man1/cd.1p.html

`$ cd` - to home directory

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cd.png" width="1000">

`$ cd -` - to previous directory

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cd_prew.png" width="1000">

`$ cd ../` - to one below directory

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cd_one_below.png" width="1000">

`$ cd ../../` - to two below directories, and so on accordingly number of ../

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cd_two_below.png" width="1000">

`$ cd /dir1/dir2/` - in two directories from the root directory, from any directory

 <img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cd_two_dir.png" width="1000">

`$ cd /root dir1/root dir2/` - in two directories from the root directory, from any directory

 <img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cd_two_root_dir.png" width="1000">

`$ cd /` - to a root directory, from any directory

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cd_root.png" width="1000">

 ## whoami

whoami - who am i

whoami [options]

https://man7.org/linux/man-pages/man1/whoami.1.html

`$ whoami`

<img src="https://drive.google.com/uc?export=view&id=1-NNH-d8XFfYuTKxtsCsKcqMQWFoo7tZS" width="1000">

 ## su

 su - run a command with substitute user and group ID 

 su [options] [-] [user [argument...]]

https://man7.org/linux/man-pages/man1/su.1.html

`$ su`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/su.png" width="1000">

To leaving su:
cntr + d

## sudo

sudo — execute a command as another user

sudo -h | -K | -k | -V

sudo -v [-ABknS] [-g group] [-h host] [-p prompt] [-u user]

sudo -l [-ABknS] [-g group] [-h host] [-p prompt] [-U user][-u user] [command]

sudo [-ABbEHnPS] [-C num] [-D directory] [-g group] [-h host][-p prompt] [-R directory] [-T timeout] [-u user] [VAR=value][-i | -s] [command]

https://man7.org/linux/man-pages/man8/sudo.8.html

`$ sudo ls`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/sudo ls.png" width="1000">

## echo

echo — write arguments to standard output.

echo [options] [string]

https://man7.org/linux/man-pages/man1/echo.1p.html

`$ echo Hello World` - write a string to standard output
`$ echo -n Hello World` - write a string to standard output without a new line after
`$ echo -n Hello World > 'Hello World.txt'` - write a string to a file

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/echo.png" width="1000">

## cat

cat - concatenate files and print on the standard output

cat [options][option]

https://man7.org/linux/man-pages/man1/cat.1.html

`$ cat 'Hello World.txt'`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/cat.png" width="1000">

## rm

rm - remove files or directories

rm [options][option]

https://man7.org/linux/man-pages/man1/rm.1.html

`$ rm 'Hello World.txt'` - remove files or empty directories

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/rm file.png" width="1000">

`$ rm -r 'Hello World.txt'`  - remove files or not empty directories

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/rm r.png" width="1000">

## ps

ps - report a snapshot of the current processes

ps [options]

https://man7.org/linux/man-pages/man1/ps.1.html

`$ ps`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ps.png" width="1000">

`$ ps -a` - select all processes except both session leaders and processes not associated with a terminal

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ps -a.png" width="1000">

`$ ps -A` - select all processes

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ps -A.png" width="1000">

`$ ps` - just ps output to a file

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ps to file.png" width="1000">

## kill

kill - terminate a process

kill  [-signal|-s signal|-p]  [-q value] [-a] [--timeout milliseconds signal] [--] pid|name

kill -l [number] | -L

https://man7.org/linux/man-pages/man1/kill.1.html

`$ kill 4455`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/kill.png" width="1000">

`$ kill -9 4455` - 100% kill of process

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/kill -9.png" width="1000">

## stat

stat - display file or file system status

stat [options] file

https://man7.org/linux/man-pages/man1/stat.1.html

`$ stat 'Hello World.txt`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/stat.png" width="1000">

## alias

alias — define or display aliases in one session

alias [alias-name[=string]]

https://man7.org/linux/man-pages/man1/alias.1p.html

`$ alias ll="ls -la"`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/alias.png" width="1000">

`$ alias` - display aliases

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/alias display.png" width="1000">

For comstant setting aliases:

`$ nano ~/.bashrc`

`$ exec bash`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/alias bashrc.png" width="1000">
<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/alias exec.png" width="1000">

## grep - NOT COMPLITE

------------------------------------------------------
grep - print lines that match patterns

grep [options] PATTERNS [file]

https://man7.org/linux/man-pages/man1/grep.1.html

`$ grep Hello 'Hello World`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/grep pattern.png" width="1000">

ps -ax | grep nano
------------------------------------------------------

## man 

man - an interface to the system reference manuals

man [man options] [[section] page]

man -k [apropos options] regexp

man -K [man options] [section] term

man -f [whatis options] page

man -l [man options] file

man -w|-W [man options] page

https://man7.org/linux/man-pages/man1/man.1.html

`$ man ls` - display a manual of ls command

## ln

ln - make links between files

ln [options] [-T] target link_name

ln [options] target

ln [options] target directory

ln [options] -t directory target

https://man7.org/linux/man-pages/man1/ln.1.html

`$ ln "hello World.txt Hello.txt"`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/ln.png" width="1000">

## df

df - report file system disk space usage

df [options] [file]

https://man7.org/linux/man-pages/man1/df.1.html

`$ df`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/df.png" width="1000">

## chmod

chmod - change file mode bits

chmod [options] mode[,mode] file

chmod [options] octal-mode file

chmod [options] --reference=rfile file

https://man7.org/linux/man-pages/man1/chmod.1.html

`$ chmod 777 'Hello World.txt'`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/chmod.png" width="1000">

777:

N   Description                      ls   binary  

0   No permissions at all            ---  000

1   Only execute                     --x  001

2   Only write                       -w-  010

3   Write and execute                -wx  011

4   Only read                        r--  100

5   Read and execute                 r-x  101

6   Read and write                   rw-  110

7   Read, write, and execute         rwx  111

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/chmod 2.png" width="1000">

## mv

mv — move files

mv [-if] file target_file

mv [-if] file... target_dir

https://man7.org/linux/man-pages/man1/mv.1p.html

`$ mv 'Hello World.txt' 'Hello World'`

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/vm.png" width="1000">

## setsid

setsid - run a program in a new session

setsid [options] program [arguments]

`$ setsid konsole` - launch the konsole in a new session

https://man7.org/linux/man-pages/man1/setsid.1.html

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/setsid.png" width="1000">

## find

find - search for files in a directory hierarchy

find [-H] [-L] [-P] [-D debugopts] [-Olevel] [starting-point...] [expression]

`$ find .|grep Hello` - find Hello files from this dir

https://man7.org/linux/man-pages/man1/setsid.1.html

<img src="https://drive.google.com/drive/folders/1r9imgDOkOCUT06yPJ4HFIO8wOT4kzC5p?usp=sharing/fnd.png" width="1000">

## halt

halt - instructs hardware to stop CPU functions

halt [options]

https://man7.org/linux/man-pages/man8/halt.8.html

`$ halt`

`$ halt -p`

`$ halt --reboot`


## poweroff

poweroff - instructs the system to power down

poweroff [options]

https://man7.org/linux/man-pages/man8/halt.8.html

`$ poweroff`

`$ poweroff --halt`

`$ poweroff --reboot`

## reboot

reboot - restarts or reboots the system

https://man7.org/linux/man-pages/man8/halt.8.html

`$ reboot --halt`

`$ reboot -p`

`$ reboot`

## shutdown

shutdown - halt, power-off or reboot the machine

shutdown [options] [time] [wall]

`$ sudo shutdown 11:00` - will schedule system shutdown at 11 A.M

`$ sudo shutdown +10` - will schedule system shutdown in 10 minutes from now

`$ sudo shutdown now` - shuts down a system immediately

`$ sudo shutdown +30 "Hardware upgrade"` - will shut down the system in 30 minutes from now and notify the users that a hardware upgrade will be performed

`$ sudo shutdown -r` - reboots the system

`$ sudo shutdown -c` - cancel and stop shutdown