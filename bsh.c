/* Chris Bendel, Julien Gilbert */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *line = NULL;    // input pre-parse
    char **input;       // input parsed
    pid_t pid;
    
    /* asks user for input till they exit*/
    while (input[0] != "exit" || input[0] != "EXIT") {
        line = readInput();
        input = parseInput(scan);
        
        if( input[0] == "groups") {
            execpv("./groups", input);
        }
        else if(input[0] == "ls") {
            execpv("./ls", input);
        }
        else if(input[0] == "cp") {
            execpv("./cp", input);
        }
        else if(input[0] == "cd") {
            execpv("./cd", input);
        }
        else {
            system(scan);
        }
        pid = fork();
    }
    
    /* free allocated memory */
	free(line);
	free(input);
	
	return EXIT_SUCCESS;
}

/* parses the user input */
char **parseInput(char *input)
{
    /* Initialize Variables */
    int pos = 0;
    char **letters = malloc(64 * sizeof(char));
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

/* reads and returns line from user */
char *readInput()
{
    char *line = NULL;
    size_t bufsize = 0; // allocates a buffer
    printf("bettershell ---> ");
    getline(&line, &bufsize, stdin);
    return line;
}
