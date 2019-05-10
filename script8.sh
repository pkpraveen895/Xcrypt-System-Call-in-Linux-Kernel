# check base functionality - if password is less than 6 bytes

printf "\nCheck base functionality - if if password is less than 6 bytes \n\n"
make
sh install_module.sh

printf "\nInput is ./xhw1 -p "ABCD" -c /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCD" -c /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt
