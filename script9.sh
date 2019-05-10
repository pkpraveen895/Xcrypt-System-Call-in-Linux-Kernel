# check corner case - if zero size files work

printf "\nCheck corner case - if zero size files work,see generated zersosizefileoutput.txt \n\n"

make
sh install_module.sh

printf "\n Input is : \n ./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/zerosizefile.txt /usr/src/hw1-vyelleswarap/CSE-506/zersosizefileoutput.txt \n"

printf "\nResult is : \n"
./xhw1 -p "ABCDEFG" -c /usr/src/hw1-vyelleswarap/CSE-506/zerosizefile.txt /usr/src/hw1-vyelleswarap/CSE-506/zerosizefileoutput.txt
