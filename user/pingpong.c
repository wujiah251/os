# include "kernel/types.h"
# include "user.h"

// 只需要发送1byte

int main()
{
    int parent_fd[2], child_fd[2];
    // 分别是父进程和子进程用于写的管道
    int pid;
    char buf[2];
    pipe(parent_fd);
    pipe(child_fd);
    if(fork()==0){
        // 表明这是一个子进程
        close(parent_fd[1]);
        close(child_fd[0]);
        pid = getpid();
        // 获得自己的id
        read(parent_fd[0],buf,1);
        if(buf[0]=='p'){
            printf("%d: received ping\n", pid);
        }
        write(child_fd[1],"s",1);
        close(parent_fd[0]);
        close(child_fd[1]);
    }
    else{
        // 父进程
        close(parent_fd[0]);
        close(child_fd[1]);
        pid = getpid();
        write(parent_fd[1],"p",1);
        read(child_fd[0],buf,1);
        if(buf[0]=='s'){
            printf("%d: received pong\n", pid);
        }
        close(parent_fd[1]);
        close(child_fd[0]);
    }
    exit(0);
}