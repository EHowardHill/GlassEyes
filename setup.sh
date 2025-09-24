#!/bin/bash

# Check if running on Ubuntu or Debian
if [ -f /etc/os-release ]; then
    . /etc/os-release
    if [[ "$ID" != "ubuntu" && "$ID" != "debian" ]]; then
        echo "This script only runs on Ubuntu or Debian."
        exit 1
    fi
else
    echo "Cannot determine OS distribution."
    exit 1
fi

# Check if devkitpro is already installed
if [ -d "/opt/devkitpro" ]; then
    echo "devkitpro is already installed."
    exit 0
fi

sudo apt update -y
sudo apt install -y python3 python3-is-python

wget https://apt.devkitpro.org/install-devkitpro-pacman
sudo chmod +x ./install-devkitpro-pacman
sudo ./install-devkitpro-pacman
sudo dkp-pacman -S gba-dev

export DEVKITPRO=/opt/devkitpro
export DEVKITARM=${DEVKITPRO}/devkitARM
export DEVKITPPC=${DEVKITPRO}/devkitPPC 
export PATH=${DEVKITPRO}/tools/bin:$PATH