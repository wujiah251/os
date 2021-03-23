#include"kernel/types.h"
#include "user/user.h"


int main(int argc,char** argv)
{
    if(argc < 2){
        fprintf(2,"need more parameters!\n");
        //标准错误输出
        exit(0);
    }
    int time=atoi(argv[1]);
    // 秒
    if(sleep(time)<0){
        fprintf(2,"failed to sleep % ticks.\n", argv[1]);
        exit(0);
    }
    exit(0);
}