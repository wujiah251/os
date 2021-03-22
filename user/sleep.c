#include"kernel/types.h"
#include "user/user.h"


int main(int argc,char** argv)
{
    if(argc < 2){
        printf("need more parameters!\n");
    }
    int time=atoi(argv[1]);
    // 秒
    sleep(time);
    exit(0);
}