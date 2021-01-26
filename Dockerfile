FROM rikorose/gcc-cmake:gcc-7

MAINTAINER brewlin <97404667@qq.com>

ADD . /root/colang

RUN cd /root/colang/tests \
        && cmake ../  \
        && make

ENV CO_SRC=/root/colang/runtime

WORKDIR /root/colang
#ENTRYPOINT ["sh","auto_tests_compiler.sh"]


