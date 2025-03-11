#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

// Concetti chiave:
// - Loop di input: leggere comandi dall’utente.
// - Parsing: separare il comando dagli argomenti.
// - Esecuzione dei comandi: usare fork(), execvp() e waitpid().
// Obiettivo iniziale: eseguire comandi semplici (ls, pwd, ecc.).


// So, whenever you use execvp(), if you want to maintain your C program, 
// you generally use fork() to first spawn a new process, and then use execvp() on that new process.
// This is called the “fork-exec” model, and is the standard practice for running multiple processes using C.

/*
char* parse(char* str){
    //White space
    static const char* ws = " \t";
    char *command = str;
    char* argument_list[] = {};

    //Skipping leading whitespaces
    str += strspn(str,ws);
    char* newLinePos;
    if (*str) {
        newLinePos = strchr(str,'\n');
        *newLinePos = 0; // Terminate command
    }

    if(strcmp(command, "\n") != 0){
        printf("%s",command);
        return command;
    }
    /*while(*str){
        str += strspn(str,ws);
        if(!*str){
            break;
        }

        char* option = str;
        argument_list
    }
    */
   
//}
//*/

void parse(char *input, char **argv){
    while(*input != '\0'){
        while(*input == ' ' || *input == '\t' || *input == '\n'){
            *input++ = '\0';
        }
        *argv++ = input;
        while(*input != '\0' && *input != '\t' && *input != '\n' && *input != ' '){
            input++;
        }
    }
    *(argv - 1) = NULL;
    *argv = NULL;
}


void executeCommand(char** argv){
    pid_t pid=fork();
    if (pid == 0) {
        // Newly spawned child Process. This will be taken over by "ls -l"
        if(execvp(*argv, argv)<0){
            printf("*** ERROR: exec failed\n");
            exit(EXIT_FAILURE);
        }
        fflush(stdout);
        sleep(10);
        exit(EXIT_SUCCESS);
        perror("execvp failed");
    }
    else if (pid > 0) {
        // Old Parent process. The C program will come here
        waitpid(pid,0,0);
    }
    else {
        perror("fork failed");
    }
}

int main(){
    char input[1024];
    char *argv[64];
    for(;;){
        printf("kamasan@NB24-023:");
        fgets(input, sizeof(input), stdin);
        parse(input, argv);
        if(strcmp(argv[0], "exit") == 0)
           exit(EXIT_SUCCESS);
        /*for(int i = 1; i < 64; i++){
            if(**(argv + i) == '\0')
                *(argv + i) = NULL;
        }
        */
        executeCommand(argv); 
    }
    return 0;
}