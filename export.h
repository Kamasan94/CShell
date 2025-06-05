#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

extern char** __environ;

void listEnvVariables() {
    for(int i=0; __environ[i] != NULL; i++){
        printf("%s\n", __environ[i]);
    }
}

int runExport(char** argv){
    if(argv[1] == NULL){
        listEnvVariables();
    }
    else {
        if(strcmp(argv[1], "-p") == 0){
            listEnvVariables();                    
        }
    }
}