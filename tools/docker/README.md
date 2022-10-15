# docker

## install

https://docs.docker.com/engine/install/ubuntu/


## flow

+ Dockerfile writing;
+ Build;
+ Run;
+ Working in a container;

if dir was not mounted

+ Copy files form the container to a host;

### Set up the repository

`sudo apt-get update`
`sudo apt-get ca-certificates curl gnupg lsb-release`
`sudo mkdir -p /etc/apt/keyrings`
`curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg`
`echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null`

 ### Install Docker Engine

`sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin`

`apt-cache madison docker-ce`  - VERSION_STRING>

`sudo apt-get install docker-ce=<VERSION_STRING> docker-ce-cli=<VERSION_STRING> containerd.io docker-compose-plugin`

`sudo service docker start` - Verify that Docker Engine is installed correctly by running the hello-world image
`sudo docker run hello-world`

## uninstall

`sudo apt-get remove docker docker-engine docker.io containerd runc`

## setting

### Start on boot
```
sudo systemctl enable docker.service
sudo systemctl enable docker.service
```
Disable start on boot
```
sudo systemctl disable docker.service
sudo systemctl disable docker.service
```

### Ограничение по объёму и числу log журналов
`sudo nano /etc/docker/daemon,json`

Туда ввести (пример для максимум 3х журналов по 10МБ):
```
{
    "log-driver": "json-file",
    "log-opts": {
      "max-size": "10m",
      "max-file": "3"
    }
}
```

### TCP/IP доступ
`sudo systemctl edit docker.service`

Туда ввести:
```
[Service]
Execstart=
ExecStart=/usr/bin/docker -H fd:// -H tcp://192.168.1.123:2375
```

```
sudo systemctl daemon-reload
sudo systemctl restart docker.service
```

## upgrade

## Dockerfile

Нужен для создания образа docker'а, как альтернатива скачиванию образа из docker хаба.

```
mkdir dockerfile
cd dockerfile
touch Dockerfile
nano Dockerfile
```

### Синтаксис
```
# базовый образ
# если нужен пустой базовый образ, то испольхуется команда scratch
FROM ubuntu

MAINTAINER Artem Shimko <artyom.shimko@gmail.com>

# для обновления базового образа, если это нужно
RUN apt-get update
```


## build

`docker build [dockefile_dir_path]` - просто собрать образ

`docker build [image_name] [dockefile_dir_path]` - просто собрать образ

`docker build -t [image_name]:1.0 [dockefile_dir_path]` - просто собрать образ с тегом 1.0


## image

### удалить имадж
`sudo docker image rm [OPTIONS] IMAGE [IMAGE...]`

`sudo docker image rm -f IMAGE` - force

### показать все существующие имаджи
`docker images` 

или

`docker ps -a `

### показать все запущенные имаджи
`docker ps`


## run


### простой запуск
`docker run <image_id>`


## Copy

`docker cp [IMAGE_ID]:[/file/path/within/container] [/host/path/target]`