/* Chris Bendel, Julien Gilbert */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char ** parseInput(char *input);
char * readInput(void);
int cmdLaunch(char *cmd, char **args);
int cmdExecute(char *line, char **input);


int main(int argc, char **argv) {
    char *line;    // input pre-parse
    char **input;       // input parsed
    int status;
    
    do
    {
        printf("bettershell --> ");
        line = readInput();
        input = parseInput(line);
        status = cmdExecute(line,input);
        /* free allocated memory */
        free(line);
	    free(input);
    } while(status == 0);
    
	return EXIT_SUCCESS;
}

/* parses the user input */
char ** parseInput(char *input)
{
    /* Initialize Variables */
    int pos = 0;
    char **letters = malloc(128 * sizeof(char));
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
char * readInput(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // allocates a buffer
	getline(&line, &bufsize, stdin);
    return line;
}

/* creates process for command */
int cmdLaunch(char *cmd, char **args)
{
    pid_t pid, wpid;
    int status;
    
    pid = fork();       // child made
    /* error checking */
    if (pid == 0) {
        if (execvp(cmd, args) == -1)
        {
             perror("Error_Forking");
        }
    }
    else if (pid < 0) {
        perror("Error_Forking");
    }
    else {

    /* parent waits till child is done*/
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/* determines command and executes it */
int cmdExecute(char *line, char **input)
{
    int i;
    //printf("%s\n", line);
    if(input[0] == NULL)
	{
		return 0;
	}
	else if( strcmp(input[0], "groups") == 0)
	{
        cmdLaunch("groups", input);
        return 0;
    }
    else if(strcmp(input[0], "ls") == 0) 
    {
        cmdLaunch("ls", input);
        return 0;
    }
    else if(strcmp(input[0], "cp") == 0)
    {
        cmdLaunch("cp", input);
        return 0;
    }
    else if(input[0] == "cd") 
    {
        cmdLaunch("cd", input);
        return 0;
    }
    else if(strcmp(input[0], "exit") == 0)
    {
        return -1;
    }
    else if(system(line) == 0)
    {
        return 0;
    }
    else
    {
        printf("That is not a valid command\n");
    }
    return 0;
}
