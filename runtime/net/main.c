#include "net.h"


int main()
{
    net_t * net = init_net();
    //程序结束 回收内存池内存    
    if(net->connections){
        free(net->connections);
    }
    if(net->read_events){
        free(net->read_events);
    }
    if(net->write_events){
        free(net->write_events);
    }
    free(net);
}