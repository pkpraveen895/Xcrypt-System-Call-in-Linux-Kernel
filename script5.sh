
# check error functionality - when input and output files point to the same file

printf "\n Check error functionality - when input and output files point to the same file \n\n"

make
sh install_module.sh

printf "\n Input is  ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/input1.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/input1.txt /usr/src/hw1-vyelleswarap/CSE-506/input1.txt
