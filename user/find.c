#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/*
    流程
        isDir
            recursion
        isFile
            處理邏輯
                比較，一一對應，則輸出

*/

void splicing(char *p,char *q){
    while(*q!='\0'){
        *p++=*q++;
    }
    *p='\0';
}

void find(char *path,char *target){
    char buf[512];
    struct stat st;
    int fd=open(path,0);
   
    if(fd<0){
        fprintf(2,"open error\n");
        exit(1);
    }
    if(fstat(fd,&st)<0){
        close(fd);
        fprintf(2,"fstat error\n");
        exit(1);
    }

    if(st.type==T_FILE){    
        char *p;
        for(p=path+strlen(path);p>=path&&(*p)!='/';p--);
        p++;
        int res=strcmp(p,target);
        if(res==0){
            //xargs中的实验，非常惨痛的教训，printf和fprintf是有区别的。并且两者又不对，对后面的xargs有影响。
            // fprintf(2,"%s\n",path); 
            //当使用管道命令|时，find  xx|B command ，如果find命令内部实现，选择的是fprintf，则它是写不进管道的。所以会导致xargs实现的错误。
             printf("%s\n",path);
        }
        
    }else if(st.type==T_DIR){
       


        struct dirent dir;
        
        strcpy(buf,path);
        char *p=buf+strlen(buf);
        *p++='/';
        while(read(fd,&dir,sizeof(dir))==sizeof(dir)){
            //inum==0,爲空目錄項
            if(dir.inum==0){
                continue;
            }
            memmove(p,dir.name,DIRSIZ);
            // splicing(p,dir.name);
            if(strcmp(dir.name,".")==0||strcmp(dir.name,"..")==0){
                continue;
            }
            find(buf,target);
        }

    }
    //小坑，这里一定要关闭，不关闭的话，因为递归，占用了很多描述符表，因此描述符表会耗尽。最终open出错。
    close(fd);
}

int main(int argc, char *argv[]){
    if(argc<3){
        fprintf(2, "find error\n");
        exit(1);
    }
    find(argv[1],argv[2]);
    exit(0);
}

