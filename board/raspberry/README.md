+ [ssh](#ssh)
+ [wifi](#wifi)

## ssh

В ТЕРМИНАЛЕ ХОСТА

### при первом запуске
1. создать boot/ssh;
2. выждать больше 30 секунд, может даже пары минут, пока raspberry заработает;
3. `ip addr show` - взять ip из enp3s0, он будет использоваться для задавания диапазона адресов (пример: 192.168.0.104/24);
4. `sudo nmap -sn [ip address]` (пример:  `sudo nmap -sn 192.168.0.104/24` либо можно просто `sudo nmap -sn 192.168.0.*`);
    Лог:
    ```
    Starting Nmap 7.60 ( https://nmap.org ) at 2022-06-21 10:02 MSK
    Nmap scan report for _gateway (192.168.0.1)
    Host is up (0.00012s latency).
    MAC Address: F8:1A:67:56:29:68 (Tp-link Technologies)
    Nmap scan report for 192.168.0.100
    Host is up (0.010s latency).
    MAC Address: 00:18:E7:8A:86:BC (Cameo Communications)
    Nmap scan report for 192.168.0.101
    Host is up (0.010s latency).
    MAC Address: 38:FB:14:A5:60:EA (Unknown)
    Nmap scan report for 192.168.0.105
    Host is up (-0.087s latency).
    MAC Address: B8:27:EB:F5:94:C7 (Raspberry Pi Foundation)
    Nmap scan report for simko-PC (192.168.0.104)
    Host is up.
    Nmap done: 256 IP addresses (5 hosts up) scanned in 3.30 seconds
    ```
    Адрес raspberry представлен как:
    ```
    Nmap scan report for 192.168.0.105
    Host is up (-0.087s latency).
    MAC Address: B8:27:EB:F5:94:C7 (Raspberry Pi Foundation)
    ```
5. `ssh [user]@[raspberry ip address]` (пример: `ssh pi@192.168.0.105`);
6. если нет ошибки:
    ```
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
    Someone could be eavesdropping on you right now (man-in-the-middle attack)!
    It is also possible that a host key has just been changed.
    The fingerprint for the ECDSA key sent by the remote host is
    SHA256:0ZdpU24VGtmabt+it/813m9C4QOAv8fRPyg/3TgKL8k.
    Please contact your system administrator.
    Add correct host key in /home/shimko/.ssh/known_hosts to get rid of this message.
    Offending ECDSA key in /home/shimko/.ssh/known_hosts:6
      remove with:
      ssh-keygen -f "/home/shimko/.ssh/known_hosts" -R "192.168.0.105"
    ECDSA host key for 192.168.0.105 has changed and you have requested strict checking.
    Host key verification failed.
    ```

    если ошибка есть, то (ковычки обязательны):
    `ssh-keygen -f "[address to .ssh/known_hosts]" -R "[raspberry ip address]"` 
    (пример:`ssh-keygen -f "/home/shimko/.ssh/known_hosts" -R "192.168.0.105"`). Потом повторить пункт 5.

7. дальше нужно будет вести пароль (предустановленный свой или стандартный: `raspberrypi`);

### при следующих запусках
1. `sudo nmap -sn [ip address]` (пример:  `sudo nmap -sn 192.168.0.104/24` либо можно просто `sudo nmap -sn 192.168.0.*`);
2. `ssh [user]@[raspberry ip address]` (пример: `ssh pi@192.168.0.105`);
3. `sh://[user]@[raspberry ip address]` (пример: `sh://pi@192.168.0.105`);

## wifi

SSID (Service Set Identifier) — это символьное название беспроводной точки доступа Wi-Fi, имя отображаемое в устройствах.

В ТЕРМИНАЛЕ RASPBERRY

1. `sudo nano /etc/wpa_supplicant/wpa_supplicant.conf`;
2. добавить в конец файла:
    ```
    country=US

    network={
        ssid="[network name)]"
        psk="[password]"
    }
    ```
    Пример:
    ```
    country=US

    network={
        ssid="TP-LINK_562968"
        psk="16975828"
    }
    ```
3. активировать изменения: 
    `sudo ifdown wlan0`
    `sudo ifup wlan0`
    или 
    `sudo reboot`

4. для проверки: `ifconfig`
    Лог:
    ```
    enxb827ebf594c7: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.0.105  netmask 255.255.255.0  broadcast 255.255.255.255
        inet6 fe80::e237:5cfb:8f3:7c7c  prefixlen 64  scopeid 0x20<link>
        ether b8:27:eb:f5:94:c7  txqueuelen 1000  (Ethernet)
        RX packets 80  bytes 12425 (12.1 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 98  bytes 12561 (12.2 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

    lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 16  bytes 2038 (1.9 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 16  bytes 2038 (1.9 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

    wlan0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 192.168.0.106  netmask 255.255.255.0  broadcast 255.255.255.255
        inet6 fe80::cc23:575:d5bd:d714  prefixlen 64  scopeid 0x20<link>
        ether b8:27:eb:a0:c1:92  txqueuelen 1000  (Ethernet)
        RX packets 10  bytes 1212 (1.1 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 35  bytes 5184 (5.0 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
        ```
В ТЕРМИНАЛЕ RASPBERRY - RASPI-CONFIG

1. `sudo raspi-config` 
2. System Option->Wireless LAN
3. `sudo ifdown wlan0`
   `sudo ifup wlan0`
   или 
   `sudo reboot`