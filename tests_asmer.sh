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
    echo "gcc -g *.o -L/usr/local/lib/colib -linternal -lgc -los"
    gcc -g *.o -L/usr/local/lib/colib -linternal -lgc -los
    check
    echo "exec a.out..."
    ./a.out
    check
    rm ./a.out
    rm *.s
    rm *.o
    echo "exec done..."

    return
#    failed "[compile] $input failed"
}
read_dir(){
    $ir = "$1"
    cd $dir
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
    cd ..
}
install_env(){
    cd tests
    if [  "$?" != 0 ]; then
        failed "make failed"
    fi
}
install_env
for dir in `ls`
do
    if [ -d $dir ] ; then
        read_dir $dir
        rm $dir/*.o
        rm $dir/*.s
    fi
done 
log "all passing...."
