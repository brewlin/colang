#!/bin/bash
assert(){
    expected="$1"
    input="$2"
    echo "start compiler $input ..."
    ./do -s $input
    if [  "$?" = 0 ]; then
        actual=`./a.out`
        echo "output:"
        echo "$actual"
        rm ./a.out
        return
    fi
    echo "\033[31m [compile] $input failed \033[0m"
    exit 1
}
read_dir(){
    for file in `ls $1`
    do
     if [ -d $1"/"$file ] ; then
        read_dir $1"/"$file
     else
        assert "OK" $1"/"$file
        echo "\033[32m [compile] $file pass! \033[0m \n"
     fi
    done
}
install_env(){
    cmake ..
    make
}
install_env
read_dir asmgen
echo
echo "\033[32m all passing..... \033[0m"
