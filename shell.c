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
    printf("Command: %s\n", command);


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
   
}

void executeCommand(char* command){
    char* argument_list[] = {command,NULL,NULL};
    pid_t pid=fork();
    if (pid == 0) {
        // Newly spawned child Process. This will be taken over by "ls -l"
        execvp(command, argument_list);
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
    for(;;){
        printf("kamasan@NB24-023:");
        char input[100000];
        fgets(input, sizeof(input), stdin);
        char* command = parse(input);
        executeCommand(command);
        if(strcmp(input, "exit\n") == 0)
            exit(EXIT_SUCCESS);

        
        
    }
    return 0;
}