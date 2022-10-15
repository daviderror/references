#!/usr/bin/env expect
set timeout -1
set petalinux_installer [lindex $argv 0]
set install_dir [lindex $argv 1]

spawn ./$petalinux_installer $install_dir
expect "Press Enter to display the license agreements"
send "\r"
expect "*>*"
send "y\r"
expect "*>*"
send "y\r"
expect "*>*"
send "y\r"
expect eof
