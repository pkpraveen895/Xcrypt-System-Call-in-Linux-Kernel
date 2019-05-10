# check base functionality - if copy works fine or not

printf "\nCheck base functionality - if copy works fine or not, see generated output1.txt \n\n"
make
sh install_module.sh

printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/output1.txt
