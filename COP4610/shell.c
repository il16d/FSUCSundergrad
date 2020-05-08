//COP4610
//Project 1 
//Coded by Iho Lopez, Felipe Bergano, and Kyle Suarez


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

const int MAX_ALIAS = 10;

typedef struct
{
    char** tokens;
    int numTokens;
} instruction;

typedef struct
{
    char* alias[10];
    char* OGcommand[10];
    int numAliases;
} aStruct;

//given to us already***********************************************
void addToken(instruction* instr_ptr, char* tok);
void printTokens(instruction* instr_ptr);
void clearInstruction(instruction* instr_ptr);
void addNull(instruction* instr_ptr);
// *****************************************************************


//Checkers
int checkBuilt(char *); //checks if the command is one of the built ins
void alreadyIn(instruction * instr_ptr, aStruct * alias_ptr, int x);
//checks that the command is already in or one of the built ins to allow the user to add or un add

//char * getEnv(char*env);
char* getEnvVariable(char* envVariable);
void echo(instruction * instr_ptr);

//Execute commands
void execute(instruction* instr_ptr);
int pathResolution(char* targetFile);

void exitFunc(int);
int execPath(instruction* instr_ptr);
void changeDirectory(instruction * instr_ptr); //right now it only goes to home directory when cd is entered


//SEGMENTATION FAULT THEY ARE NOT COMMENTED OUT BECAUSE MAIN NEEDS THEM TO WORK
//************************************************************************************************
//ALIAS STUFF
//is alias already existing
int isAliasThere(char* string, aStruct * apointer);
void addAlias(instruction* instr_ptr, aStruct* alias_ptr);
int removeAlias(char* string,aStruct * alias_ptr);
//*************************************************************************************************


int pipeErrorCheck(instruction * instr_ptr);
int Pipe(instruction * instr_ptr);
void implementPipe(char ** cmd1, char ** cmd2);

void outputRedirect(char* fileName);
void inputRedirect(char* fileName);
int fileIO(instruction * instr_ptr);



int main() {
    
    int instructNum=0;
    char* token = NULL;
    char* temp = NULL;
    
    instruction instr;
    instr.tokens = NULL;
    instr.numTokens = 0;
    
    
    aStruct alias_;
    int orflag=0;
    int andfalg=0;
    int i;
    
    for(i = 0; i < 10; i++)
    {
        alias_.alias[i] = NULL;
        alias_.OGcommand[i] = NULL;
    }
    alias_.numAliases = 0;
    
    
    
    
    while (1) {
        //printf("Please enter an instruction: ");
        printf("%s@%s:%s>", getenv("USER"), getenv("MACHINE"),getenv("PWD"));
        
        
        // loop reads character sequences separated by whitespace
        do {
            //scans for next token and allocates token var to size of scanned token
            scanf("%ms", &token);
            temp = (char*)malloc((strlen(token) + 1) * sizeof(char));
            
            int i;
            int start;
            start = 0;
            
            for (i = 0; i < strlen(token); i++) {
                //pull out special characters and make them into a separate token in the instruction
                if (token[i] == '|' || token[i] == '>' || token[i] == '<' || token[i] == '&') {
                    
                    if(token[i]=='|')
                    {
                        orflag=1;
                    }
                    if(token[i]=='&')
                    {
                        andfalg=1;
                    }
                    if (i-start > 0)
                    {
                        memcpy(temp, token + start, i - start);
                        temp[i-start] = '\0';
                        addToken(&instr, temp);
                    }
                    
                    char specialChar[2];
                    specialChar[0] = token[i];
                    specialChar[1] = '\0';
                    addToken(&instr,specialChar);
                    start = i + 1;
                }
            }
            
            if (start < strlen(token))
            {
                memcpy(temp, token + start, strlen(token) - start);
                temp[i-start] = '\0';
                
                addToken(&instr, temp);
            }
            
            //free and reset variables
            free(token);
            free(temp);
            
            token = NULL;
            temp = NULL;
            
        } while ('\n' != getchar());    //until end of line is reached
        if (strcmp(instr.tokens[0], "unalias") != 0)
        {
            int aliasIndex;
            for (i = 0; i < instr.numTokens; i++)
            {
                aliasIndex = isAliasThere(instr.tokens[i], &alias_);
                if (aliasIndex != -1)
                {
                    free(instr.tokens[i]);
                    instr.tokens[i] = (char*) malloc((strlen(alias_.OGcommand[aliasIndex]) + 1 ) * sizeof(char));
                    strcpy(instr.tokens[i], alias_.OGcommand[aliasIndex]);
                }
            }
        }
        if(orflag == 1)
        {//piping instruction
            Pipe(&instr);
            orflag=0;   //reset the flag
        }
        //something
        
        if(checkBuilt(instr.tokens[0]) == 0)
        {//not a built in instruction
            fflush(0);
            execute(&instr);
            
        }else
        {//built in instruction
            alreadyIn(&instr, &alias_, instructNum);
        }

      //  addNull(&instr);
        //printTokens(&instr);
        clearInstruction(&instr);
        instructNum++;
    }
    
    
    
    return 0;
}


//**************************************************************************************************
//reallocates instruction array to hold another token
//allocates for new token within instruction array
void addToken(instruction* instr_ptr, char* tok)
{
    //extend token array to accomodate an additional token
    if (instr_ptr->numTokens == 0)
        instr_ptr->tokens = (char**) malloc(sizeof(char*));
    else
        instr_ptr->tokens = (char**) realloc(instr_ptr->tokens, (instr_ptr->numTokens+1) * sizeof(char*));
    
    //allocate char array for new token in new slot
    instr_ptr->tokens[instr_ptr->numTokens] = (char *)malloc((strlen(tok)+1) * sizeof(char));
    strcpy(instr_ptr->tokens[instr_ptr->numTokens], tok);
    
    instr_ptr->numTokens++;
}

void addNull(instruction* instr_ptr)
{
    //extend token array to accomodate an additional token
    if (instr_ptr->numTokens == 0)
        instr_ptr->tokens = (char**)malloc(sizeof(char*));
    else
        instr_ptr->tokens = (char**)realloc(instr_ptr->tokens, (instr_ptr->numTokens+1) * sizeof(char*));
    
    instr_ptr->tokens[instr_ptr->numTokens] = (char*) NULL;
    instr_ptr->numTokens++;
}

void printTokens(instruction* instr_ptr)
{
    int i;
    printf("Tokens:\n");
    for (i = 0; i < instr_ptr->numTokens; i++)
    {
        printf("#%s#\n", (instr_ptr->tokens)[i]);
    }
}

void clearInstruction(instruction* instr_ptr)
{
    int i;
    for (i = 0; i < instr_ptr->numTokens; i++)
        free(instr_ptr->tokens[i]);
    
    free(instr_ptr->tokens);
    
    instr_ptr->tokens = NULL;
    instr_ptr->numTokens = 0;
}
//******************************************************************************************





char* getEnvVariable(char* envVariable)
{
    char* envVarSubstr;
    char* storedEnvVariable;
    
    envVarSubstr = strtok(envVariable, "$");
    storedEnvVariable = getenv(envVarSubstr);
    
    if(storedEnvVariable != NULL)
        return storedEnvVariable;
    else
        return "Error: Undefined variable.";
}


void echo(instruction * instr_ptr) // FOR REFERENCE   https://www.youtube.com/watch?v=F9vTLC8w7Ms
{
    int i;
    char * envVar;
    for(i = 1; i < instr_ptr->numTokens; i++)
    {
        if(instr_ptr->tokens[i][0] == '$')
        {
            envVar = getEnvVariable(instr_ptr->tokens[i]);
            printf("%s ", envVar);
        }
        else
        {
            printf("%s ",instr_ptr->tokens[i]);
        }
    }
    printf("\n");
    
}


void exitFunc(int instructNum)
{
    
    printf("Exiting...\n");
   printf("\tCommands executed: %d\n", instructNum);
    exit(0);
    
}


int checkBuilt(char* cmd)
{
    if(strcmp(cmd,"exit") == 0 || strcmp(cmd,"cd") == 0 || strcmp(cmd,"echo") == 0 ||
       strcmp(cmd, "alias") == 0 || strcmp(cmd,"unalias") == 0)
    {
        return 1; //true
    }
    else
    {
        return 0;     //false
    }
}


void alreadyIn(instruction * instr_ptr, aStruct * alias_ptr, int instructNum)
{
    if(strcmp(instr_ptr->tokens[0], "exit") == 0)
    {
        exitFunc(instructNum);
    }
    if(strcmp(instr_ptr->tokens[0], "cd") == 0)
    {
        changeDirectory(instr_ptr);
        
    }
    if(strcmp(instr_ptr->tokens[0],"echo") == 0)
    {
        echo(instr_ptr); //works prints user if called $USER
    }
    if(strcmp(instr_ptr->tokens[0], "alias") == 0)
    {
        if(alias_ptr->numAliases >= MAX_ALIAS)
        {
            printf("Reached Max Amount alias allowed (10).\n");
        }
        else
        {
            addAlias(instr_ptr,alias_ptr);
           
        }
    }
    if(strcmp(instr_ptr->tokens[0], "unalias") == 0)
    {
        if (instr_ptr->numTokens == 1)
        {
            printf("Too few arguments provided for unalias command\n");
        }
        else if (instr_ptr->numTokens > 2)
        {
            printf("Too many arguments provided for unalias command\n");
        }
        else
        {
            if(!removeAlias(instr_ptr->tokens[1],alias_ptr))
            {
                printf("No alias found\n");
            }
        }
    }
}



void execute(instruction* instr_ptr)
{
    pid_t pid = fork();
    int status;
    int i;
    int cmdTokens = 0;
    
    if(pid == -1){
        exit(1);
    }
    else if(pid == 0){
        
        execPath(instr_ptr);
        
        //extend token array to accomodate an additional token
        instr_ptr->tokens = (char**)realloc(instr_ptr->tokens, (instr_ptr->numTokens+1) * sizeof(char*));
        
        //allocate char array for new token in new slot
        instr_ptr->tokens[instr_ptr->numTokens] = 0;
        
       
        
         if(fileIO(instr_ptr) == 1)
         {
         for(i = 0; i < instr_ptr->numTokens; i++)
         {
         cmdTokens++;
         if(instr_ptr->tokens[i+1][0] == '>' || instr_ptr->tokens[i+1][0] == '<')
         {
         break;
         }
         }
         char * newCommand[cmdTokens + 1];
         
         for(i = 0; i < cmdTokens; i++)
         {
         newCommand[i] = instr_ptr->tokens[i];
         }
         newCommand[i] = (char) 0;
         execv(newCommand[0], newCommand);
         }
        
        else{
       
        execv(instr_ptr->tokens[0], instr_ptr->tokens);
        }
        
        //free the null terminated slot
        free(instr_ptr->tokens[instr_ptr->numTokens]);
        
        //reallocate to the original size
        instr_ptr->tokens = (char**) realloc(instr_ptr->tokens, (instr_ptr->numTokens) * sizeof(char*));
        
        exit(0);
    }
    else{
        waitpid(pid, &status, 0);
    }
}

void changeDirectory(instruction * instr_ptr)
{
    char* newdir = (char*) calloc(100, 100);


    //So far this function works for everything except cd ~
    if(instr_ptr->numTokens == 1)    //entered only cd
    {    //treat as if $HOME is argument
        char* home = getenv("HOME");
        chdir(home);       
       setenv("PWD", home, 1);
    }
    else if(instr_ptr->numTokens > 2)    //entered too many arguments
    {
        printf("Error: more than one argument entered.\n");
    }
    else    //entered the correct cd command w correct amount of args
    {
      char* newdir = (char*) calloc(100, 100);

      if(instr_ptr->tokens[1][0] == '.' && instr_ptr->tokens[1][1] == '.')
      {     
          char* modifiedPath = getenv("PWD");
          int i;
          int count = 0;
          for(i = strlen(modifiedPath) - 1; modifiedPath[i] != '/'; i--){
             count++;
          }
          count++;

          for(i = 0; i<strlen(modifiedPath) - count; i++){
             newdir[i] = modifiedPath[i];
          }
          chdir(newdir);
          setenv("PWD", newdir, 1);
      }
      else if(pathResolution(instr_ptr->tokens[1]) == 1)    //valid path
      {
        strcat(newdir, getenv("PWD"));
        strcat(newdir, "/");
        strcat(newdir, instr_ptr->tokens[1]);
        chdir(newdir);
        setenv("PWD", newdir, 1);
      }
      else
      {
            printf("Error: %s: No such file or directory\n", instr_ptr->tokens[1]);
      }
    }

    free(newdir);          
}



//THE CODE BELOW IS NOT WORKING CORRETLY BUT AGAIN IS A 
//SEGMENTATION NOT MY FAULT


void addAlias(instruction* instr_ptr, aStruct* alias_ptr)
{
    //    printf("help");
    char* slicePointer = instr_ptr->tokens[1];
    char* quotePointer = 0;
    int aliasIndex;
    
    //check if alias already exists
    int i;
    for (i = 0; i < 10; i++)
    {//if alias[i] == null ? then break
        if(alias_ptr->alias[i] == '\0')
            break;
        
        if (strcmp(instr_ptr->tokens[1], alias_ptr->alias[i]))
        {
            printf("alias already exists\n");
            return;
        }
    }
    //check if alias list has room
    for (i = 0; i < 10; i++)
    {
        if (alias_ptr->alias[i] == (char*) 0)
            break;
    }
    if (i == 10)
    {
        printf("alias list is full\n");
        return;
    }
    
    aliasIndex = i;
    
    // (i) is now the index of the first available slot
    
    for (i = 2; i < instr_ptr->numTokens; i++)
    {
        //reallocate tokens[1] to a space that can accomodate the next token
        instr_ptr->tokens[1] = (char*) realloc(instr_ptr->tokens[1], (strlen(instr_ptr->tokens[1]) + 2 + strlen(instr_ptr->tokens[i])) * sizeof(char));
        //add a space
        strcat(instr_ptr->tokens[1], " ");
        //add the next token
        strcat(instr_ptr->tokens[1], instr_ptr->tokens[i]);
    }
    
    //add a null termination where the '=' is
    slicePointer = strchr(instr_ptr->tokens[1], (int) '=');
    *slicePointer = (char) 0;
    slicePointer++; slicePointer++;
    
    
    //malloc space, save the alias name into the list
    alias_ptr->alias[aliasIndex] = (char*) malloc((strlen(instr_ptr->tokens[1]) + 1) * sizeof(char));
    strcpy(alias_ptr->alias[aliasIndex], instr_ptr->tokens[1]);
    
    //null terminate the ending quotation
    quotePointer = strrchr(slicePointer, (int) '\'');
    *quotePointer = (char) 0;
    
    //copy from just after the first quote, to the end of the quoted text
    alias_ptr->OGcommand[aliasIndex] = (char*) malloc((strlen(slicePointer) + 1) * sizeof(char));
    strcpy(alias_ptr->OGcommand[aliasIndex], slicePointer);
    
    
    alias_ptr->numAliases++;
    return;
}


int isAliasThere(char* string, aStruct * apointer){ //Check for alias

int i;
for(i = 0; i < apointer->numAliases; i++)
{
    if (apointer->alias[i] != 0)
        if(strcmp(string, apointer->alias[i]) == 0)
        {
            return i;
        }
}

return -1;
}


int removeAlias(char* string, aStruct* alias_ptr) //remove the alias from the list
{
    
    int index= isAliasThere(string,alias_ptr);
    if(index != -1)
    {
        alias_ptr->alias[index] = (char) 0;
        free(alias_ptr->alias[index]);
        alias_ptr->OGcommand[index] = (char) 0;
        free(alias_ptr->OGcommand[index]);
        alias_ptr->numAliases--;
        return 1;
    }
    
    return 0;
}
    
    
    

int execPath(instruction* instr_ptr)
{
    //printf("ME HELLO");
    char systemPathArray[200];
    strcpy(systemPathArray, getenv("PATH"));
    
    char* workingPathPointer = systemPathArray;
    char* testPathPointer = 0;
    
    char* colonPointer = systemPathArray;
    
    while(1)
    {
        
        if (*colonPointer == '.')
        {
            testPathPointer = (char*) malloc((strlen(getenv("PWD")) + 2
                                              + strlen(instr_ptr->tokens[0])) * sizeof(char));
            strcpy(testPathPointer, getenv("PWD"));
            strcat(testPathPointer, "/");
            strcat(testPathPointer, instr_ptr->tokens[0]);
            
            if (pathResolution(testPathPointer) == 1)
            {
                free(instr_ptr->tokens[0]);
                instr_ptr->tokens[0] = testPathPointer;
                return 1;
            }
            else
            {
                return 0;
            }
        }
        
        //find the next :, set it to null, increment pointer
        colonPointer = strchr(workingPathPointer, (int) ':');
        *colonPointer = (char) 0;
        colonPointer++;
        
        //malloc space for the next possible path
        testPathPointer = (char*) malloc((strlen(workingPathPointer) + 2
                                          + strlen(instr_ptr->tokens[0])) * sizeof(char));
        
       
        strcpy(testPathPointer, workingPathPointer);
        strcat(testPathPointer, "/");
        strcat(testPathPointer, instr_ptr->tokens[0]);
        
        
        
        if (pathResolution(testPathPointer) == 1)
        {
            free(instr_ptr->tokens[0]);
            instr_ptr->tokens[0] = testPathPointer;
            return 1;
        }
       
        
        free(testPathPointer);
        workingPathPointer = colonPointer;
        
    }
}


void outputRedirect(char* fileName) //https://pubs.opengroup.org/onlinepubs/009695399/functions/open.html & https://linux.die.net/man/3/open
{//CMD > FILE (output redirection)
    int fd = open(fileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    close(STDOUT_FILENO);
    dup(fd);
    close(fd);
}

void inputRedirect(char* fileName) //https://pubs.opengroup.org/onlinepubs/009695399/functions/open.html & https://linux.die.net/man/3/open
{//CMD < FILE (input redirection)
    int fd = open(fileName, O_RDWR | S_IRUSR);
    if(pathResolution(fileName) == 0)
    {
        printf("Error: input file doesn't exist\n");
    }
    close(STDIN_FILENO);
    dup(fd);
    close(fd);
    
}


int Pipe(instruction * instr_ptr)
{
    int i;
    int amount = 0;
    
    if(pipeErrorCheck(instr_ptr) == 0)
    {
        printf("Invalid null command\n");
        return 0;
    }
    for(i = 0; i < instr_ptr->numTokens; i++)
    {
        if(instr_ptr->tokens[i][0] == '|')
        {
            amount++;   //keep track of how many pipes there are
        }
    }
    if(amount == 1) //one pipe
    {
        int cmd1Tokens = 0;
        int cmd2Tokens = 0;
        for(i = 0; i < instr_ptr->numTokens; i++)
        {
            cmd1Tokens++;   //tracks amount of first command tokens
            if(instr_ptr->tokens[i+1][0] == '|')
            {
                break;
            }
        }
        for(i = cmd1Tokens + 1; i < instr_ptr->numTokens; i++)
        {
            cmd2Tokens++;
        }
        
        char * cmd1[cmd1Tokens + 1];
        char * cmd2[cmd2Tokens + 1];
        int j;
        int k = 0;
        //parse through all the tokens and separate commands
        for(i = 0; i < instr_ptr->numTokens; i++)
        {
            cmd1[i] = instr_ptr->tokens[i];
            if(instr_ptr->tokens[i + 1][0] == '|')
            {
                i++; i++;
                for(j = i; j < instr_ptr->numTokens; j++)
                {
                    cmd2[k] = instr_ptr->tokens[j];
                    k++;
                }
                break;
            }
        }
        cmd1[cmd1Tokens] = (char) 0;
        cmd2[cmd2Tokens] = (char) 0;
        implementPipe(cmd1, cmd2);
        return 1;
    }
}


int pipeErrorCheck(instruction * instr_ptr)
{
    //ERROR CHECKING:
    if(instr_ptr->tokens[0][0] == '|')
    {//entered only | or | at begining of command
        return 0;
    }
    else if(instr_ptr->tokens[instr_ptr->numTokens - 1][0] == '|')
    {//ended with a | at the end of a command
        return 0;
    }
    
    return 1;
    
}


int pathResolution(char* targetFile){ // for reference    https://linux.die.net/man/2/path_resolution
    FILE* file;
    file = fopen(targetFile, "r");
    
    if(file != NULL){
        fclose(file);
        return 1;
    }
    
    return 0;
    
}


void implementPipe(char ** cmd1, char ** cmd2)
{
    int pipefd[2];
    int pid = fork();
    
    
    if(pid == 0)
    {//child (cmd1 | cmd2)
        pipe(pipefd);   //puts the fds for each command into a pipe to read/write from
        if(pid == 0)
        {
            //cmd1 writer
            close(STDOUT_FILENO);
            dup(pipefd[1]);
            close(pipefd[0]);
            close(pipefd[1]);
            //execute command
            //            execPath(cmd1);
            execv(cmd1[0], cmd1);
        }
        else
        {
            //cmd2 reader
            close(STDIN_FILENO);
            dup(pipefd[0]);
            close(pipefd[0]);
            close(pipefd[1]);
            //execute command
            //          execPath(cmd2);
            execv(cmd2[0], cmd2);
        }
    }
    else
    {
        //parent shell
        //close(pipefd[0]);
        //close(pipefd[1]);
        
    }
}

int fileIO(instruction * instr_ptr)
{
    int returnValue = 0;
    int i;
    int cmdTokens = 0;
    
    for(i = 0; i < instr_ptr->numTokens; i++)
    {
        cmdTokens++;
        if(instr_ptr->tokens[i][0] == '>' || instr_ptr->tokens[i][0] == '<')
        {
            break;
        }
    }
    cmdTokens--;
    
    //THIS SECTION IS FOR ERROR CHECKING FOR INVALID SYNTAX
    if(instr_ptr->tokens[instr_ptr->numTokens -1][0] == '>' ||
       instr_ptr->tokens[instr_ptr->numTokens -1][0] == '<'){
        //entered > or <, or CMD < or CMD >
        printf("Error: Invalid syntax for redirct\n");
    }
    else if(instr_ptr->numTokens == 2 && pathResolution(instr_ptr->tokens[0]) == 1){
        //entered FILE > or FILE <
        printf("Error: Invalid syntax for redirct\n");
    }
    else if(instr_ptr->numTokens == 2 && pathResolution(instr_ptr->tokens[1]) == 1
            && instr_ptr->tokens[0][0] == '<'){
        //entered < FILE
        printf("Error: Invalid syntax for redirct\n");
    }
    
    //EXECUTING REDIRECTION
    int in = 0;
    int out = 0;
    
    for(i = 0; i < instr_ptr->numTokens; i++)
    {
        if(instr_ptr->tokens[i][0] == '<' && in == 0)
        {
            returnValue = 1;
            in = 1;
            inputRedirect(instr_ptr->tokens[i + 1]);
        }
        else if(instr_ptr->tokens[i][0] == '>' && out == 0)
        {
            returnValue = 1;
            out = 1;
            outputRedirect(instr_ptr->tokens[i + 1]);
        }
    }
    
    return returnValue;
}
