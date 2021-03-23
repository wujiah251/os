#include "kernel/types.h"
#include "user.h"

void process(int fd[])
{
    // fd是自己作为子进程的读管道
    // 自己作为父进程的写管道
    int child_fd[2];
    pipe(child_fd);

    int first_num=0,len=0,index=0;
    int nums[34];
    close(fd[1]);
    len = read(fd[0],&first_num,sizeof(int));
    if(len>0){
        printf("prime %d\n",first_num);
    }
    while((len = read(fd[0],&nums[index],sizeof(int)))>0){
        if(nums[index]%first_num)++index;
    }
    close(fd[0]);
    if(index==0){
        // 说明没有数字了，结束进程
        exit(0);
    }
    if(fork() == 0){
        process(child_fd);
        exit(0);
    }
    else{
        // 父进程
        close(child_fd[0]);
        for(int i=0;i<index;++i)
            write(child_fd[1],&nums[i],sizeof(int));
        close(child_fd[1]);
        wait(0);
        exit(0);
    }
}

int main(int argc,char** argv)
{
    int fd[2];
    pipe(fd);
    if(fork()==0){
        process(fd);
    }
    else{
        // 初始父进程
        close(fd[0]);
        for(int i=2;i<=35;++i){
            write(fd[1],&i,sizeof(int));
        }
        close(fd[1]);
        wait(0);//等待子进程结束
    }
    exit(0);
}