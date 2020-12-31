#!/bin/bash
log(){
    str="$1"
    echo -e "\033[32m$str \033[0m "
}
failed(){
    str="$1"
    echo -e "\033[31m$str \033[0m"
    exit 1
}
check(){
    if [  "$?" != 0 ]; then
#        actual=`./a.out`
#        if [  "$?" != 0 ]; then
        failed "exec failed"
#        fi
#        rm ./a.out
    fi

}
assert(){
    expected="$1"
    input="$2"
    log "[compile] ./co-compiler -s $input ..."
    ./co-compiler -s $input
    check
    gcc -g *.s -L./src/internal -linternal -L./src/gc -lgc
    check
    ./a.out
    check
    rm ./a.out
    rm *.s

    return
#    failed "[compile] $input failed"
}
read_dir(){
    for file in `ls *.co`
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
    cd tests
    cmake ..
    make

    if [  "$?" != 0 ]; then
        failed "make failed"
    fi
    rm *.s
}
install_env
read_dir
log "all passing...."
