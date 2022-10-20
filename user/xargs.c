
#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


#define N 512
/*
xargs 
（1）读取前一个命令的标准输出
（2）读取本命令的参数
（3）处理标准输出与本命令参数
（4）执行

*/


int main(int argc,char *argv[]){
    char buf[N];
    char *p=buf;
    int n;
    while((n=read(0,buf,N))==0);
    
    char *xargv[MAXARG];
    int xargc=0;
    for(int i=1;i<argc;i++){
        xargv[i-1]=argv[i];
        xargc++;
    }

    for(int i=0;i<N;i++){
        if(buf[i]=='\0'){
            break;
        }
        if(buf[i]=='\n'){
            int pid=fork();
            if(pid>0){
                p=&buf[i+1];
                wait(0);
            }else{
                buf[i]='\0';
                xargv[xargc++]=p;
                xargv[xargc]=0;

                exec(xargv[0],xargv);
                exit(0);

            }
        }


    }
    exit(0);


}




// int main(int argc,char *argv[]){
//     sleep(10);
//     char buf[N];
//     read(0,buf,N);



//     char *xargv[MAXARG];
//     int xargc=0;
//     for(int i=1;i<argc;i++){
//         xargv[xargc++]=argv[i];       
//     }
    

//     char *p=buf;
//     for(int i=0;i<N;i++){
//         if(buf[i]==0){
//             break;
//         }
//         if(buf[i]=='\n'){
//             int pid=fork();
//             if(pid>0){
//                 p=&buf[i+1];
//                 wait(0);
//             }else if(pid==0){
                
//                 buf[i]='\0';
                
//                 xargv[xargc++]=p;
//                 xargv[xargc]=0;
//                 for(int i=0;i<xargc;i++){
//                     printf("inp-%s\n",xargv[i]);
//                 }
//                 exec(xargv[0],xargv);
//                 exit(0);
//             }
//         }
//     }
//     exit(0);
// }



// #include "kernel/types.h"
// #include "kernel/param.h"
// #include "kernel/stat.h"
// #include "user/user.h"
// #include "kernel/fs.h"


// #define N 512
/*
xargs 
（1）读取前一个命令的标准输出
（2）读取本命令的参数
（3）处理标准输出与本命令参数
（4）执行

*/


// int main(int argc,char *argv[]){
//     sleep(10);
//     char buf[N];
//     //如果是find，并且使用fprintf输出的，则读取不到。
//     read(0,buf,N);



//     char *xargv[MAXARG];
//     int xargc=0;
//     for(int i=1;i<argc;i++){
//         xargv[xargc]=argv[i];       
       
//         xargc++;
        
//     }
    

//     char *p=buf;
//     for(int i=0;i<N;i++){
//         printf("-a %c\n",buf[i]);
//         if(buf[i]==0){
//             break;
//         }
//         if(buf[i]=='\n'){
//             int pid=fork();
//             if(pid>0){
//                 p=&buf[i+1];
//                 wait(0);
//             }else if(pid==0){
                
//                 buf[i]=0;
                
//                 xargv[xargc]=p;
//                 xargc++;
//                 xargv[xargc]=0;
//             for(int i=0;i<xargc;i++){
//             printf("-t %s\n",xargv[i]);
//             }
//                 // xargc++;
//                 // exec(xargv[0],xargv);
//                 exit(0);
//             }
//         }
//     }
//     // wait(0);
//     exit(0);
// }