# check 

printf "\n check \n\n"
make
sh install_module.sh

printf "\n copy command, generated output in output13.txt \n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input5.txt /usr/src/hw1-vyelleswarap/CSE-506/output13.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input5.txt /usr/src/hw1-vyelleswarap/CSE-506/output13.txt

printf "\n Encrypt command, generated output in output14.txt\n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input5.txt /usr/src/hw1-vyelleswarap/CSE-506/output14.txt \n"

printf "\nReturned value of encryption is : \n"
./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input5.txt /usr/src/hw1-vyelleswarap/CSE-506/output14.txt

printf "\n Decrypt command, generated output in output15.txt\n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output14.txt /usr/src/hw1-vyelleswarap/CSE-506/output15.txt \n"

printf "\nReturned value of decryption is : \n"

./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output14.txt /usr/src/hw1-vyelleswarap/CSE-506/output15.txt
