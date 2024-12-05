#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "ls_command.h"
#define MAX_LINE 80
#define MAX_ARGS 10

int main(){
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while(1){
        printf("myshell>");

        // read command
        fgets(input,MAX_LINE,stdin);
        printf("%s\n",input);

        token=strtok(input, " \n\t");
        int i=0;
        while(token!=NULL){
            argv[i++]=token;
            token=strtok(NULL, " \n\t");
        }
        argv[i]=NULL;

        if(argv[0]==NULL){
            continue;
        }

        if(strcmp(argv[0],"exit")==0){
            printf("good bye~");
            exit(0);
        } else if(strcmp(argv[0],"cd")==0){
            chdir(argv[1]);
        } else if(strcmp(argv[0],"pwd")==0){
            getcwd(input,MAX_LINE);
            printf("%s\n",input);
        } else if(strcmp(argv[0],"ls")==0){
            my_ls();
        } else if(strcmp(argv[0],"cat")==0){
            for (int j = 1; argv[j] != NULL; j++) {
                    int fd = open(argv[j], O_RDONLY); 
                    if (fd == -1) {
                        perror("cat");
                        continue;
                    }

                    char buffer[MAX_LINE];
                    ssize_t bytes_read;
                    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
                        buffer[bytes_read] = '\0'; 
                        write(STDOUT_FILENO, buffer, bytes_read);
                    }
                    printf("\n");
                    if (bytes_read == -1) {
                        perror("read");
                    }

                    close(fd);
                }
             
        } else{
            pid_t pid =fork();
           if (pid == 0) {
                if (access(argv[0], X_OK) == 0) {
                    execv(argv[0], argv); 
                    perror("execv"); 
                } else {
                    printf("command not found: %s\n", argv[0]);
                }
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
            }
        }
    }
    
    return 0;
}