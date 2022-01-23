#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int count = 1;
    char line[2048];
    char *array[128];
    const char* cd ="cd";
    char ext[] = "exit";
    while (count){
        printf("Input a command$ ");
        fgets(line, sizeof line, stdin);
        char *token = strtok(line, " \n");
        int i =0;
        while( token != NULL){
            array[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        array[i] = NULL;
        if(strcmp(array[0], cd) == 0){
            chdir(array[0]);
            if(chdir(array[1]) == -1){
                perror("broke");
            }else{
                printf("yay");
            }
        }else if (strcmp(array[0],ext)==0)
        {
            exit(0);
        }else{
            pid_t pid = fork();
            if(pid ==0){
                execvp(array[0], array);
                perror("exec");
                exit(1);
            } else{
                wait(NULL);
            }
        }
    }
    return 0;
}
