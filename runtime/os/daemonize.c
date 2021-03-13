#include "colang.h"
// 以守护进程的方式启动
void daemonize()
{

    int null_fd = open("/dev/null", O_RDWR);
    struct sigaction sa;
    int fd0, fd1, fd2;

    umask(0);

    // fork()新的进程
    switch(fork()) {
        case 0:
            break;
        case -1:
            printf("daemo"
                   "n fork 1: %s", strerror(errno));
            exit(1);
        default:
            exit(0);
    }
    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGHUP,  &sa, NULL) < 0) {
        printf("SIGHUP: %s", strerror(errno));
        exit(1);
    }

    switch(fork()) {
        case 0:
            break;
        case -1:
            printf("daemon fork 2: %s", strerror(errno));
            exit(1);
        default:
            exit(0);
    }

    chdir("/");

    // 关闭标准输入，输出，错误
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    fd0 = dup(null_fd);
    fd1 = dup(null_fd);
    fd2 = dup(null_fd);

    if (null_fd != -1)
        close(null_fd);

    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        printf("unexpected fds: %d %d %d", fd0, fd1, fd2);
        exit(1);
    }

    printf("pid: %d", getpid());
}