#!/bin/bash
log(){
    str="$1"
    echo -e "\033[32m $str \033[0m "
}
failed(){
    str="$1"
    echo -e "\033[31m $str \033[0m"
    exit 1
}
assert(){
    expected="$1"
    input="$2"
    log "[compile] ./do -s $input ..."
    ./do run $input
    if [  "$?" != 0 ]; then
#        actual=`./a.out`
#        if [  "$?" != 0 ]; then
        rm ./a.out
        failed "exec failed"
#        fi
#        rm ./a.out
    fi
    return
#    failed "[compile] $input failed"
}
read_dir(){
    for file in `ls *.do`
    do
     if [ -d $file ] ; then
        read_dir $file
     else
        assert "OK" $file
        log "[compile] $file passed!"
     fi
    done
}
install_env(){
    cmake ..
    make

    if [  "$?" != 0 ]; then
        failed "make failed"
    fi
}
install_env
read_dir
log "all passing...."
