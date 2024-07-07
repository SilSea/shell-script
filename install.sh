#!/bin/bash
RED="\e[1;31m"
GREEN="\e[1;32m"
END="\e[0m"

echo -e "${RED}Install Package SSH${END}"
sudo apt install openssh-server -y
echo -e "${GREEN}Package Install Success${END}"

echo -e "${RED}Start Package SSH${END}"
sudo systemctl enable ssh.service
sud systemctl start ssh.service
echo -e "${GREEN}Package Start Success${END}"

echo -e "${GREEN}All Success${END}"