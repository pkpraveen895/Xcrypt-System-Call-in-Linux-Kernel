# check various file sized data - length 5002

printf "\n check various file sized data - length 5002\n\n"
make
sh install_module.sh

printf "\n copy command, generated output in output7.txt \n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input3.txt /usr/src/hw1-vyelleswarap/CSE-506/output7.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input3.txt /usr/src/hw1-vyelleswarap/CSE-506/output7.txt

printf "\n Encrypt command, generated output in output8.txt\n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input3.txt /usr/src/hw1-vyelleswarap/CSE-506/output8.txt \n"

printf "\nReturned value of encryption is : \n"
./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input3.txt /usr/src/hw1-vyelleswarap/CSE-506/output8.txt

printf "\n Decrypt command, generated output in output9.txt\n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output8.txt /usr/src/hw1-vyelleswarap/CSE-506/output9.txt \n"

printf "\nReturned value of decryption is : \n"

./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output8.txt /usr/src/hw1-vyelleswarap/CSE-506/output9.txt
