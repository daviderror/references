#!/bin/bash 

if [ ! -d /workspace/home/root ]; then
	mkdir /workspace/home/
	sudo cp -fr /root /workspace/home/
fi

sudo rm -fr /root
sudo ln -s /workspace/home/root /root

sudo /opt/pkg/petalinux/tools/hsm/bin/xsdk

sleep infinity
