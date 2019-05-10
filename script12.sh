# check various file sized data - length 10002

printf "\n check various file sized data - length 10002\n\n"
make
sh install_module.sh

printf "\n copy command, generated output in output10.txt \n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input4.txt /usr/src/hw1-vyelleswarap/CSE-506/output10.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input4.txt /usr/src/hw1-vyelleswarap/CSE-506/output10.txt

printf "\n Encrypt command, generated output in output11.txt\n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input4.txt /usr/src/hw1-vyelleswarap/CSE-506/output11.txt \n"

printf "\nReturned value of encryption is : \n"
./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input4.txt /usr/src/hw1-vyelleswarap/CSE-506/output11.txt

printf "\n Decrypt command, generated output in output12.txt\n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output11.txt /usr/src/hw1-vyelleswarap/CSE-506/output12.txt \n"

printf "\nReturned value of decryption is : \n"

./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output11.txt /usr/src/hw1-vyelleswarap/CSE-506/output12.txt
