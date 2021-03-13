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


//创建初始化net 全局结构体
//放回给co不需要包装，因为co也是只存储不进行运算
net_t * cnet_init()
{
    net_t * net = (net_t*) gc_malloc(sizeof(net_t));
    memzero(net,sizeof(net_t));
    NET = net;//global net
    net->listening = NULL;
    // 打开日志文件
    net->log = gc_malloc(sizeof(log_t));
    net->log->use_logfile = 1;
    log_open(net->log, "./run.log");

    //初始化模块
    log_info(net->log,"net: init module");
    net->modules_n = 2;
    net->modules = modules;
    return net;
}
//启动模块
Value* start_module(net_t *net){
    log_info(net->log,"net: start module");
    for(int i = 0;i < net->modules_n ; i++){
        //http 注册tcp监听端口
        //event 模块创建epoll  epoll_events
        if(net->modules[i]->init_process(net) != OK){
            log_error(net->log,"net: start module init process error");
            return ERROR;
        }
    }
    Value* ret = gc_malloc(sizeof(Value));
    ret->type  = Int;
    ret->data  = OK;
    return ret;
}
Value* net_process_events(net_t* net) {
    Value* ret = gc_malloc(sizeof(Value));
    ret->type  = Int;
    ret->data  = process_events(net, event_flags);
    return ret;
}
