#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main()
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    int buf[34];
    if (pid > 0)
    {
        close(fd[0]);
        int index = 0;
        for (int i = 2; i <= 35; i++)
        {
            buf[index++] = i;
        }
        write(fd[1], buf, index*4);
        close(fd[1]);
        wait(0);
    }
    else if (pid == 0)
    {
        
        
        int npid = 0;
        int size=34*4;
       
        
        while (1)
        {
        
            if(npid>0){
                close(fd[0]);
                close(fd[1]);
                wait(0);
                break;
            }
            
            if (npid == 0)
            {
                int len=size/4;
            
               
                read(fd[0], buf, size);
                
                int divisor=buf[0],cnt=0;
                
                printf("prime %d\n",buf[0]);
                for (int i = 1; i < len; i++)
                {
                    if (buf[i] % divisor != 0)
                    {
                        buf[cnt++] = buf[i];
                    }
                }
                if(cnt==0){
                   
                    break;
                }
                size=cnt*4;
               
                write(fd[1], buf, size);
             
                npid = fork();
            }
         
        }
        
    }
    
    exit(0);
}