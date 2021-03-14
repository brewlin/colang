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
    log "[compile] co -s $input ..."
    co -s $input
    check
    log "[asmer] cas -p ."
    cas -p .
    echo "start linking..."
    `gcc -c /usr/local/lib/coasm/*.s`
    log "[linker] cld -p ."
    cld -p .
    check
    chmod 777 a.out
    echo "exec a.out..."
    ./a.out
    check
    rm ./a.out
    echo "exec done..."

    return
#    failed "[compile] $input failed"
}
read_dir(){
    for file in `ls *.co`
    do
     if [ -d $file ] ; then
        read_dir $file
     else
         rm *.s
         rm *.o
        assert "OK" $file
        log "[compile] $file passed!\n"
     fi
    done
    rm *.s
    rm *.o
}
install_env(){
    cd tests
    if [  "$?" != 0 ]; then
        failed "make failed"
    fi
}
install_env
read_dir
log "all passing...."
