#include "kernel/types.h"

#include "user/user.h"

int main(){
    int pid,fd[2];
    int ret=pipe(fd);
  
    char buf[8];
    pid=fork();
    if(pid>0){
        
        write(fd[1],"s",1);
        sleep(10);
        
        ret=read(fd[0],buf,sizeof(buf));
        if(ret<0){
            fprintf(2, "read error\n");
            exit(1);
        }
        pid=getpid();
        fprintf(2,"%d: %s\n",pid,"received pong");
    
    }else if(pid==0){
        
        ret=read(fd[0],buf,sizeof(buf));
        if(ret < 0){
            fprintf(2, "read error\n");
            exit(1);
        }        
        
        pid=getpid();
        fprintf(2,"%d: %s\n",pid,"received ping");
        // close(fd[0]);
        write(fd[1],"s",1);
        
    } else{
        exit(1);
    }
    exit(0);
}