#!/bin/bash
assert(){
    rm ./tmp
    expected="$1"
    input="$2"
    echo "start compiler $input ..."
    ./do -s ${input} > tmp.s
    cc -o tmp tmp.s
    actual=`./tmp`
    if [ ${actual} = ${expected} ] ; then
        echo "$input => $actual"
    else
        echo "expected '$expected' ,but got '$actual'"
        exit 1
    fi
}
read_dir(){
    for file in `ls $1`
    do
     if [ -d $1"/"$file ] ; then
        read_dir $1"/"$file
     else
        assert "OK" $1"/"$file
     fi
    done
}
install_env(){
    cmake ..
    make
}
install_env
read_dir asmgen
