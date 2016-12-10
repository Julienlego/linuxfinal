/* Chris Bendel, Julien Gilbert */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *scan[128];    // input pre-parse
    char **input;       // input parsed
    
    /* asks user for  */
    while (input[0] != "exit" || input[0] != "EXIT") {
        
        printf("bettershell ---> ");
        scanf("%s",scan);
        input = parseInput(scan);
        
        if( input[0] == "groups") {
            
        }
        else if(input[0] == "ls") {
            
        }
        else if(input[0] == "cp") {
            
        }
        else if(input[0] == "cd") {
            
        }
        else {
            
        }
    }
    
	free(scan);
	for(int i=0;i<128;i++){
	    free(input[i]);
	}
	free(input);
	return 0;
}

/* parses the user input */
char **parseInput(char *input)
{
    /* Initialize Variables */
    int pos = 0;
    char **letters = malloc(128);
    char *letter;
 
    /* Traverse Input */
    letter = strtok(input, " \t\r\n\a");
 
    while(letter != NULL)
    {
        letters[pos] = letter;
        pos ++;
        letter = strtok(NULL, " \t\r\n\a");
    }
 
    /* Add Null Terminator */
    letters[pos] = NULL;
 
    /* Return array of char arrays */
    return letters;
}
