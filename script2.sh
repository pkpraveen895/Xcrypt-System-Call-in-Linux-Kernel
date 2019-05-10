# check base functionality - if encrypt and decrypt works fine or not

printf "\nCheck base functionality - if encrypt and decrypt works fine or not, see generated output2.txt for encrypted data, output3.txt for decrypted data \n\n"

make
sh install_module.sh

printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output2.txt \n"

printf "\nReturned value of encryption is : \n"
./xhw1 -p "ABCDEFG" -e /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output2.txt

printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output2.txt /usr/src/hw1-vyelleswarap/CSE-506/output3.txt \n"

printf "\nResturned value of decryption is : \n"

./xhw1 -p "ABCDEFG" -d /usr/src/hw1-vyelleswarap/CSE-506/output2.txt /usr/src/hw1-vyelleswarap/CSE-506/output3.txt
