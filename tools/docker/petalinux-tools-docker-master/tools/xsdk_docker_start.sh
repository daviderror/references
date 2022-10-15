#!/bin/bash

if [ -z $1 ]; then
	echo "usage: petalinux_docker_start.sh <local working directory>"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "local working directory not exist!"
	exit 2
fi

HOST_WORKING_DIR=$1

docker run \
	-i -t \
	--rm \
	--privileged \
	-v /dev/bus/usb:/dev/bus/usb \
	-e DISPLAY=$DISPLAY \
	-v /tmp/.X11-unix:/tmp/.X11-unix \
       	-v $HOST_WORKING_DIR:/workspace petalinux:2018.2 \
	/opt/internal_cmd_docker/__start_xsdk.sh

exit $?
