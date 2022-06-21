+ [ssh](#ssh)

## ssh

### при первом запуске
1. пустой ssh файлик в папку boot в корне флешки для включения ssh;
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