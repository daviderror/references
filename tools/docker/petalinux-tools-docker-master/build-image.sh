#!/usr/bin/env bash 

echo "Start to build petalinux tools docker image ..."
echo "-----------------------------------------------"

docker build --squash -t petalinux:2018.2 .

echo "---------------"
echo "  Finish. ^_^  "
echo "---------------"
