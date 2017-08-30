#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 1024

int main(int argc, char *argv[]) {
    //char *cmd;
    //char *cmd2;
    //char *cmd3;
    char line[MAX_LENGTH];
    char lineBackup[MAX_LENGTH];
    char prompt[MAX_LENGTH] = "VisheraShell:";
    
    printf("Don't worry, loves, VisheraShell is here!\n");
    printf("-----~-------~------*-------~-----~------\n\n");
    
    while (1) {
        
        /* ==== PRINT PROMPT ==== */
        
        printf("%s ", prompt);
        
        /* ==== TAKE USER INPUT ==== */
        
        fgets(line, MAX_LENGTH-1, stdin);
        strcpy(lineBackup,line);
        
        /* === PARSE USER INPUT === */
        
        char *cmd = strtok(lineBackup," \n");
        char *cmd2 = strtok(NULL," \n");
        char *cmd3 = strtok(NULL," \n");
        
        if(strcasecmp(cmd,"SET")==0 && strcasecmp(cmd2,"PROMPT")==0){   /* === SET PROMPT COMMAND === */
            
            strcpy(prompt,cmd3); /* Assign new prompt */
            
        } else if(strcasecmp(cmd,"QUIT")==0){   /* ==== QUIT COMMAND ===== */
            printf("Bye now, loves!\n");
            break;
        } else {
            system(line);                       /* ===== SYSTEM CALL ===== */
        }
        
    }
    
    return 0;
}