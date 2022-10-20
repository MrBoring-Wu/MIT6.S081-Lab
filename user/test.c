#include "kernel/types.h"
#include "user/user.h"

int main(){
    int pid;
    pid=fork();
    printf("fork() %d",pid);
    if(pid==0){
        printf("child\n");
    }else{
        printf("parent\n");
    }
    return 0;
}