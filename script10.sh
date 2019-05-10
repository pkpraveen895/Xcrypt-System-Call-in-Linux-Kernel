# check various file sized data - length 1002

printf "\n check various file sized data - length 1002 \n\n"
make
sh install_module.sh

printf "\n copy command, generated output in output4.txt \n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input2.txt /usr/src/hw1-vyelleswarap/CSE-506/output4.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input2.txt /usr/src/hw1-vyelleswarap/CSE-506/output4.txt

printf "\n Encrypt command, generated output in output5.txt \n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input2.txt /usr/src/hw1-vyelleswarap/CSE-506/output5.txt \n"

printf "\nReturned value of encryption is : \n"
./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input2.txt /usr/src/hw1-vyelleswarap/CSE-506/output5.txt

printf "\n Decrypt command, generated output in output6.txt\n"
printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output5.txt /usr/src/hw1-vyelleswarap/CSE-506/output6.txt \n"

./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output5.txt /usr/src/hw1-vyelleswarap/CSE-506/output6.txt
