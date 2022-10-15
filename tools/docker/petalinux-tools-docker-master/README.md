# Xilinx PetaLinux tools 18.02 into docker image

> For legal distribution reasons, the Petalinux Tools files cannot be included with any public materials. To obtain a free legal copy of the PetaLinux 2018.2 Installer, please download it from the Xilinx website:  
> [Downloads - Xilinx](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html)  
> For the same reason you cannot push this Petalinux Docker image to the [Docker Hub](https://hub.docker.com/)

## Versions
- PetaLinux version: 2018.2
- Base image: Ubuntu:16.04

## Features
- The default working directory is `/workspace`, you can mount a volume to there to save your data in your local path.

## Pre-Build
- Enable experimental functions of the docker daemon.  
See [Run Docker with experimental functions](#run-docker-with-experimental-functions) section for more information.
- Download `petalinux-v2018.2-final-installer.run` from Xilinx, copy into this directory and set the executable permissions:
```shell
chmod a+x petalinux-v2018.2-final-installer.run
```

## Build image
You can use `build-image.sh` to build the image, which do `docker build` with the option `--squash` to save the newly built layers into a single new layer and save disk space.
This option is experimental and need to be activated in the docker deamon.

## Run image to work with Petalinux
To run a container and work with PetaLinux:
```shell
$ ./tools/petalinux_docker_start.sh <local working directory>
```
In the container you have developer.developer(1000:1000) permission and you work into /workspace directory:
```shell
$ petalinux-create -t project -s <path-to-bsp> -n <project-name>
$ cd <project-name>
$ petalinux-build  # this will take a long time
```

## Run XSDK
The first time you have to allow the container access to the host xserver:
```shell
$ xhost +local:root
```

To directly run XSDK unless enter into docker container shell you can run:
```shell
$ ./tools/xsdk_docker_start.sh <local working directory>
```
This script starts XSDK with root permission. This is necessary to directly program the Xilinx boards or to use an external JTAG from USB.
Automatically also relocates the root home directory into your current working directory. This is necessary to store all SDK preference contained into the ~/.Xilinx directory.

## TODOs
- XSDK execution with root permission is BAD...  
We need to find a way to access to the USB peripheral from container as developer.developer. This will improve speed with cooperation between
container and local directory.

## PetaLinux reference
[ug1144-petalinux-tools-reference-guide](https://www.xilinx.com/support/documentation/sw_manuals/xilinx2018_2/ug1144-petalinux-tools-reference-guide.pdf)

## Run Docker with experimental functions
To turn on experimental docker functions create following file by:
```shell
sudo nano /etc/docker/daemon.json
```
and add below content to it
```shell
{
    "experimental": true
}
```
and save file (by CTRL+X and Enter ) and exit.  
Reboot the docker daemon.  
If you are in a linux system like Ubuntu:
```shell
sudo service docker restart
```
Or if you use a systemd based distribution:
```shell
sudo systemctl restart docker
```


To check that experimental funcions are ON, type in terminal:
```shell
docker version
```
And you should see  
```shell
...
Experimental: true
```

# Happy hacking and give me feedback please. Any help is welcome!
