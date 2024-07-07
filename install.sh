#!/bin/bash
RED="\e[1;31m"
GREEN="\e[1;32m"
END="\e[0m"

echo -e "${RED}Install Package SSH${END}"
&>/dev/null sudo apt install openssh-server -y
echo -e "${GREEN}Package Install Success${END}"

echo -e "${RED}Start Package SSH${END}"
&>/dev/null sudo systemctl enable ssh.service
&>/dev/null sudo systemctl start ssh.service
echo -e "${GREEN}Package Start Success${END}"

echo -e "${GREEN}All Success${END}"
