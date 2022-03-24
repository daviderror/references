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
26. [i2cdetect](#i2cdetect)

## ls

ls - list directory contents

ls [options] [directory]

https://man7.org/linux/man-pages/man1/ls.1.html

`$ ls`

<img src="https://drive.google.com/uc?export=view&id=12Qsd1pVQ53_3P_lRkVKAThBCBnqpkeMi" width="1000"> <!--- ls.png -->

`$ ls -l` use a long listing format

<img src="https://drive.google.com/uc?export=view&id=1bZL9znYFJ80woAf0kM1_Fqvqy2bPsw97" width="1000"> <!--- ls_l.png -->

`$ ls -l /etc/network/`

<img src="https://drive.google.com/uc?export=view&id=1YwMXfdTtE0qzSHqD9YFtG-9B7frgBW-e" width="1000"> <!--- ls_dir.png -->


aliases: `$ ll` == `$ ls -l`


## mkdir

mkdir - make directories

mkdir [options] directory name

https://man7.org/linux/man-pages/man1/mkdir.1.html

`$ mkdir some_dir`

<img src="https://drive.google.com/uc?export=view&id=14cCRvElgUA9uixSuS-bK_m5zOkL4nVUi" width="1000"> <!--- mkdir.png -->

`$ mkdir "some_dir"`

<img src="https://drive.google.com/uc?export=view&id=1CqC-wFQFOXY2uwpAkVvvVHGaj3uIkaMw" width="1000"> <!--- mkdir_2.png -->

## cd

cd - change directory

cd [options] [directory]

https://man7.org/linux/man-pages/man1/cd.1p.html

`$ cd` - to home directory

<img src="https://drive.google.com/uc?export=view&id=1YxtDwENCQ_1qTAocQ2cziIvU-qibeS6j" width="1000"> <!--- cd.png -->

`$ cd -` - to previous directory

<img src="https://drive.google.com/uc?export=view&id=1iNAg29-bHiYl8B84Slaw1_BMKdo8MLYz" width="1000"> <!--- cd_prew.png -->

`$ cd ../` - to one below directory

<img src="https://drive.google.com/uc?export=view&id=1kPhF6mjV0DNxz_AxocbkO4tYOGglbzgV" width="1000"> <!--- cd_one_below.png -->

`$ cd ../../` - to two below directories, and so on accordingly number of ../

<img src="https://drive.google.com/uc?export=view&id=1BmLFxNxEexC6anZSQWu7ObYhCLCUkDoL" width="1000"> <!--- cd_two_below.png -->

`$ cd /dir1/dir2/` - in two directories from the root directory, from any directory

<img src="https://drive.google.com/uc?export=view&id=19m0ERWETnHk9vz_RpQNMN2ANQBrb1xYn" width="1000"> <!--- cd_two_dir.png -->

`$ cd /root dir1/root dir2/` - in two directories from the root directory, from any directory

<img src="https://drive.google.com/uc?export=view&id=1BMEUuoqY950Y4qJjTAiqiJEHVjRrxkqO" width="1000"> <!--- cd_two_root_dir.png -->

`$ cd /` - to a root directory, from any directory

<img src="https://drive.google.com/uc?export=view&id=1D1iNnXLtBNU7dXCTRGma2FP8Ju3IJNwS" width="1000"> <!--- cd_root.png -->

 ## whoami

whoami - who am i

whoami [options]

https://man7.org/linux/man-pages/man1/whoami.1.html

`$ whoami`

<img src="https://drive.google.com/uc?export=view&id=1-NNH-d8XFfYuTKxtsCsKcqMQWFoo7tZS" width="1000"> <!--- whoami.png -->

 ## su

 su - run a command with substitute user and group ID 

 su [options] [-] [user [argument...]]

https://man7.org/linux/man-pages/man1/su.1.html

`$ su`

<img src="https://drive.google.com/uc?export=view&id=1sJaAjFg3hr-cf-17Uf-cPNSWXWeWs-eQ" width="1000"> <!--- su.png -->

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

<img src="https://drive.google.com/uc?export=view&id=1rGRhH-Us6YoTAc5YLJ0qz0_idouf27zf" width="1000"> <!---sudo_ls.png  -->

## echo

echo — write arguments to standard output.

echo [options] [string]

https://man7.org/linux/man-pages/man1/echo.1p.html

`$ echo Hello World` - write a string to standard output
`$ echo -n Hello World` - write a string to standard output without a new line after
`$ echo -n Hello World > 'Hello World.txt'` - write a string to a file

<img src="https://drive.google.com/uc?export=view&id=1EPsVRaYAQmLSXazWHv5K2pPECv6WInA5" width="1000"> <!--- echo.png -->

## cat

cat - concatenate files and print on the standard output

cat [options][option]

https://man7.org/linux/man-pages/man1/cat.1.html

`$ cat 'Hello World.txt'`

<img src="https://drive.google.com/uc?export=view&id=1f7k47L5x-_c97dO4vKWQGN8g7QvbIsI4" width="1000"> <!--- cat.png -->

## rm

rm - remove files or directories

rm [options][option]

https://man7.org/linux/man-pages/man1/rm.1.html

`$ rm 'Hello World.txt'` - remove files or empty directories

<img src="https://drive.google.com/uc?export=view&id=18D66rhORRLm0gZXfU8mxBbU02mPCPVLS" width="1000"> <!--- rm_file.png -->

`$ rm -r 'Hello World.txt'`  - remove files or not empty directories

<img src="https://drive.google.com/uc?export=view&id=1J8QHcSqj6s4CSCaz2Dv8IAGIN94JkJB9" width="1000"> <!--- rm_r.png -->

## ps

ps - report a snapshot of the current processes

ps [options]

https://man7.org/linux/man-pages/man1/ps.1.html

`$ ps`

<img src="https://drive.google.com/uc?export=view&id=1BuFP4d_yXY2_fXbvaMO--qaRLRDl8AGz" width="1000"> <!--- ps.png -->

`$ ps -a` - select all processes except both session leaders and processes not associated with a terminal

<img src="https://drive.google.com/uc?export=view&id=19oSZmJg8w2EFP8sQDodmhUj9CzkehHfg" width="1000"> <!--- ps_a.png -->

`$ ps -A` - select all processes

<img src="https://drive.google.com/uc?export=view&id=18-WQRvUi0IG-N3FBl88jmPf6w6KN3TOY" width="1000"> <!--- ps_A.png -->

`$ ps` - just ps output to a file

<img src="https://drive.google.com/uc?export=view&id=1BllfYkpGdpF9PG6XnC5gtD72H143InxD" width="1000"> <!--- ps_to_file.png -->

## kill

kill - terminate a process

kill  [-signal|-s signal|-p]  [-q value] [-a] [--timeout milliseconds signal] [--] pid|name

kill -l [number] | -L

https://man7.org/linux/man-pages/man1/kill.1.html

`$ kill 4455`

<img src="https://drive.google.com/uc?export=view&id=1GD3wu491XEpONZguGRWLI-cuddE2tJpW" width="1000"> <!--- kill.png -->

`$ kill -9 7628` - 100% kill of process

<img src="https://drive.google.com/uc?export=view&id=1JhhPaO7efIFQE7UVsep0hm8RQCLr532F" width="1000"> <!---  kill_9.png-->

## stat

stat - display file or file system status

stat [options] file

https://man7.org/linux/man-pages/man1/stat.1.html

`$ stat 'Hello World.txt`

<img src="https://drive.google.com/uc?export=view&id=1CtQ8pu3HAs5lD4M5g954WBsG9CRCJg8H" width="1000"> <!--- stat.png -->

## alias

alias — define or display aliases in one session

alias [alias-name[=string]]

https://man7.org/linux/man-pages/man1/alias.1p.html

`$ alias ll="ls -la"`

<img src="https://drive.google.com/uc?export=view&id=1fcQHfyvubmSAjokeBZuwTukNB6N76pgE" width="1000"> <!--- alias.png -->

`$ alias` - display aliases

<img src="https://drive.google.com/uc?export=view&id=1Icgt-PErRkM4KmEByH2z6mmLKU5uU9NV" width="1000"> <!--- alias_display.png -->

For comstant setting aliases:

`$ nano ~/.bashrc`

`$ exec bash`

<img src="https://drive.google.com/uc?export=view&id=1gFxn5Pv8UTsjOKI8yI1--2dKvcHB6RyY" width="1000"> <!--- alias_bashrc.png -->
<img src="https://drive.google.com/uc?export=view&id=1gaF_C7yJGt13Thm8ZzmuzMWZqDC0aHWe" width="1000"> <!--- alias_exec.png -->

## grep - NOT COMPLITE

------------------------------------------------------
grep - print lines that match patterns

grep [options] PATTERNS [file]

https://man7.org/linux/man-pages/man1/grep.1.html

`$ grep Hello 'Hello World`

<img src="https://drive.google.com/uc?export=view&id=1PcA9KKxykN0JEVQ3__IHvK5_3GDWChtY" width="1000"> <!--- grep_pattern.png -->

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

<img src="https://drive.google.com/uc?export=view&id=1eY8NPdW8OG8jpiSsVCvRjMVytanDJvzW" width="1000"> <!--- ln.png -->

## df

df - report file system disk space usage

df [options] [file]

https://man7.org/linux/man-pages/man1/df.1.html

`$ df`

<img src="https://drive.google.com/uc?export=view&id=1BvnUqXvUXZM_XuRzdYPJxFdrzSrXU1Xh" width="1000"> <!--- df.png -->

## chmod

chmod - change file mode bits

chmod [options] mode[,mode] file

chmod [options] octal-mode file

chmod [options] --reference=rfile file

https://man7.org/linux/man-pages/man1/chmod.1.html

`$ chmod 777 'Hello World.txt'`

<img src="https://drive.google.com/uc?export=view&id=1PKKQ6cxo6s1d00RziD5UnSPOihDyRjjb" width="1000"> <!--- chmod.png -->

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

<img src="https://drive.google.com/uc?export=view&id=17M3uJc_jI2EM9TEHzewhhBq8Oa3DzYsc" width="1000"> <!--- chmod_2.png -->

## mv

mv — move files

mv [-if] file target_file

mv [-if] file... target_dir

https://man7.org/linux/man-pages/man1/mv.1p.html

`$ mv 'Hello World.txt' 'Hello World'`

<img src="https://drive.google.com/uc?export=view&id=1K7MUnWMyQnMcfc1ULC-gxXspFNZzhyqf" width="1000"> <!--- vm.png -->

## setsid

setsid - run a program in a new session

setsid [options] program [arguments]

`$ setsid konsole` - launch the konsole in a new session

https://man7.org/linux/man-pages/man1/setsid.1.html

<img src="https://drive.google.com/uc?export=view&id=1a2CwYygBXMa8gsq56FLzsS02V366kXIj" width="1000"> <!--- setsid.png -->

## find

find - search for files in a directory hierarchy

find [-H] [-L] [-P] [-D debugopts] [-Olevel] [starting-point...] [expression]

`$ find .|grep Hello` - find Hello files from this dir

https://man7.org/linux/man-pages/man1/setsid.1.html

<img src="https://drive.google.com/uc?export=view&id=1WhGGcGYnkVdc2aKrwVcqi5wgGo4-rqnQ" width="1000"> <!--- find.png -->

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

## i2cdetect
    installing:
```
$ sudo apt-get install i2c-tools
```
    print a list i2c devices:
```
$ sudo i2cdetect -l
```
    print a table of i2c deviced on first i2c bus 
```
$ sudo i2cdetect -y 1
```