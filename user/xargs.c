#include "kernel/types.h"
#include "kernel/param.h"
#include "user.h"

// 讲标准输入作为另一个函数的参数



int main(int argc,char** argv)
{
    if (argc < 2)
    {
        fprintf(2, "Usage:xargs command ...\n");
        exit(0);
    }
    // argv[0]="xargs"
    // argv[1]是另一个函数
    // argv[2:]是另一个函数自带参数
    int i,j,flag,len;
    // i定位args第几个参数
    // j定位argv第几个参数
    // flag用来记录是不是空格
    // len用来记录每次从标准输入读取的字符数
    char c, args[MAXARG][32];
    // MAXARG是exec的最大参数个数
    char *m[MAXARG];
    while(1){
        memset(args, 0,MAXARG*32);
        for(i=0,j=1;j<argc && i<MAXARG - 1;++i,++j){
            strcpy(args[i],argv[j]);
        }
        // 先把已有的参数复制进来
        j = 0;
        flag = 0;
        // 表明前面是空格
        while((len=read(0, &c, 1)) > 0 && c != '\n' && i < MAXARG - 1){
            if(c==' '){
                if(flag){
                    ++i;
                    j = 0;
                    flag = 0;
                }
                // 表明一个参数已经结束
                continue;
            }
            args[i][j++]=c;
            flag=1;
        }
        // 表面这遇到了ctrl+D
        if(len <= 0){
            wait(0);
            exit(0);
        }

        for(i = 0; i < MAXARG - 1;++i)
            m[i]=args[i];
        m[MAXARG-1]=0;
        if(fork()==0){
            exec(m[0], m);
            exit(0);
        }
    }
    exit(0);
}