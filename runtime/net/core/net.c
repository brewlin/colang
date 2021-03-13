#include "net.h"
#include "connection.h"
#include "config.h"
#include "log.h"
#include "event.h"

net_t *NET;
module_t* modules[] = {
    &http_core_module,
    &event_core_module,
};

// 以守护进程的方式启动
static void daemonize(net_t *net) {
    
    if(!net->is_daemon)
        return;

    int null_fd = open("/dev/null", O_RDWR);
    struct sigaction sa;
    int fd0, fd1, fd2;

    umask(0);

    // fork()新的进程
    switch(fork()) {
        case 0:
            break;
        case -1:
            log_error(net->log, "daemon fork 1: %s", strerror(errno));
            exit(1);
        default:
            exit(0);
    }
    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGHUP,  &sa, NULL) < 0) {
        log_error(net->log, "SIGHUP: %s", strerror(errno));
        exit(1);
    }

    switch(fork()) {
        case 0:
            break;
        case -1:
            log_error(net->log, "daemon fork 2: %s", strerror(errno));
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
        log_error(net->log, "unexpected fds: %d %d %d", fd0, fd1, fd2);
        exit(1);
    }

    log_info(net->log, "pid: %d", getpid());
} 


//创建初始化net 全局结构体
static net_t * init()
{
    net_t * net = (net_t*) gc_malloc(sizeof(net_t));
    memzero(net,sizeof(net_t));
    NET = net;//global net

    net->listening = NULL;
    // 打开日志文件
    net->log = gc_malloc(sizeof(log_t));
    net->log->use_logfile = 1;
    log_open(net->log, "./run.log");

    //开启守护进程
    net->is_daemon = 0;
    daemonize(net);

    return net;

}
//模拟nginx模块注册流程
static void init_module(net_t *net)
{
    log_info(net->log,"net: init module");
    net->modules_n = 2;
    net->modules = modules;
}
//启动模块
int_t start_module(net_t *net){
    log_info(net->log,"net: start module");
    for(int i = 0;i < net->modules_n ; i++){
        //http 注册tcp监听端口
        //event 模块创建epoll  epoll_events
        if(net->modules[i]->init_process(net) != OK){
            log_error(net->log,"net: start module init process error");
            return ERROR;
        }
    }
    return OK;
}

net_t* init_net(){
    //初始化全局结构体
    net_t* net = init();

    //初始化模块
    init_module(net);

    //启动模块
    if(start_module(net) != OK){
        return net;
    }

    //epoll wait 分发事件
    while(1){
        if(process_events(net,event_flags) == ERROR){
            goto end;
        }
    }
end:
    close_listening_sockets(net);
    
    return net;
}