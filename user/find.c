#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

// echo > b
// mkdir a
// echo > a/b
// find . b
// ./b
// ./a/b

// find指令用于查找文件
// find 搜索路径 搜索内容
// 比如 find . b 就是在本文件夹中查找b文件
// 会递归查找子文件夹

void
find(char *path, char *t)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';

        if(de.inum == 0){
            continue;
        }
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("find: cannot stat %s\n", buf);
            continue;
        }
        
        switch(st.type){
        case T_FILE:
            if(strcmp(t, de.name) == 0){
                printf("%s\n", buf);
            }
            break;
        case T_DIR:
            // recursion to descend into sub-directories.
            if(strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0){
                find(buf, t);
            }
            break;
        }
    }
    close(fd);
}

int
main(int argc, char *argv[])
{
    if(argc < 3){
        fprintf(2, "Usage:find path expression\n");
        exit(0);
    }

    find(argv[1], argv[2]);
    exit(0);
}