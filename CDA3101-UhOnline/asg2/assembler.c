/******************************************************
 * *
 * Name: Iho Lopez *
 * Class: CDA 3101 *
 * Assignment: Asg 2 (an assembler of a subset of the *
 * MIPS assembly language) *
 * Compile: "gcc -std=99 assembler.c" *
 gcc -o out.exe -std=gnu99 assembler.c
 * *
 ******************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

//using namespace std;

const int INSTRUCTION = 32768;
const int ASSEMBLY = 32768 * 2 + 2; // per write up
const int LINE = 81;
const int REGISTERS = 8;
const int LABELS = 11;

const char* const registernames[] =
        {"zero","at","v0","v1","a0","a1","a2","a3",
         "t0","t1","t2","t3","t4","t5","t6","t7",
         "s0","s1","s2","s3","s4","s5","s6","s7",
         "t8","t9","k0","k1","gp","sp","fp","ra"};
const char* const instructionnames[] =
    {"addiu","addu","and","beq","bne","div","j","lw",
     "mfhi","mflo", "mult","or","slt","subu","sw","syscall"};

const int opcode[] = 
    {9, 33, 36, 4, 5, 26, 2, 35,
     16, 18, 24, 37, 42, 35, 43, 12};

int RegisterIndex(const char*);
int OpCode(const char*);
int ValidInstruction(const char*);
void ValidRegister(const char*);

int linecount = 0;

int main(int argc, char** argv)
{
    int instructioncount = 0, wordcount = 0, totalcount = 0, Index = 0;
    
    bool isData = false, isText = false, Found = false;
    
    char oper[8], rs[REGISTERS], rt[REGISTERS], rd[REGISTERS];
    
    char line[LINE], targaddr[LABELS], immed[LABELS];
    
    int wordsPerLine[INSTRUCTION], inword[INSTRUCTION];
    
    char in[ASSEMBLY][LINE]; //intake
    
    char Llocation[ASSEMBLY][LABELS];
    
    char Lfound[ASSEMBLY][LABELS];
    
    int numberspace, binary, offset;
    int a = 0;
    char comment;
    char* token; 
    

    //first pass to get labels for offsets from stdin saving to array
    while(fgets(in[a], LINE, stdin))
    {
        //remove comments
        if (instructioncount == 0 && sscanf(in[a], " %s", line) && strcmp(line, ".text") == 0)
        {
            isText = true;
            continue;
        }
        else if (!isText && !isData)
        {
            //his program does not catch comments pre-.text directive, i copied
            //this functionality
           /* fprintf(stderr,
                    "Not a .text directive:\n   %s\n",
                    in[a]);*/
            std::cerr<<"Not text directive "<<in[a]<<std::endl;
            
            exit(1);
        }
        //remove all comment-only lines
        if (sscanf(in[a]," %c", &comment) == 1)
        {
            if (comment == '#')
            {
                continue;
            }
        } 
        //remove all eol comments
        sscanf(in[a], "%[^#\n]", in[a]);
      
        //extract labels
        if (sscanf(in[a], "%[^:]:%[^\n]", Llocation[linecount], in[a]) != 2)
        {
            strcpy(Llocation[linecount],"");
        }
        //scan by line variable
        strcpy(line, in[a]);
        sscanf(line, "%s", oper);
        
        //start instructions
        if (isText)
        {
            linecount += ValidInstruction(oper);
            instructioncount = linecount;
            //this is to extract all the labels that were found to ensure 
            //the labels and registers are valid
            if (sscanf(line, "%*s $%[^,],%d($%[^)]", rt, &offset, rs) == 3)
            {
                ValidRegister(rt);
                ValidRegister(rs);
            }
            else if (sscanf(line, "%*s $%[^,],%[^(]($%[^)]", rt, immed, rs) == 3)
            {
                strcpy(Lfound[linecount],immed);
                ValidRegister(rt);
                ValidRegister(rs);
            }
            else if (sscanf(line, "%*s $%[^,],($%[^)]", rt, rs) == 2)
            {
                ValidRegister(rt);
                ValidRegister(rs);
            }
            else if (sscanf(line, "%*s $%[^,],$%[^,],$%s", rd, rs, rt) == 3) 
            {
                ValidRegister(rt);
                ValidRegister(rs);
                ValidRegister(rd);
            }
            else if (sscanf(line, "%*s $%[^,],$%[^,],%d", rs, rt, &offset) == 3) 
            {
                ValidRegister(rt);
                ValidRegister(rs);
            }
            else if (sscanf(line, "%*s $%[^,],$%[^,],%s", rs, rt, immed) == 3) 
            {
                ValidRegister(rt);
                ValidRegister(rs);
                strcpy(Lfound[linecount],immed);
            }
            else if (sscanf(line, "%*s $%[^,],$%s", rs, rt) == 2) 
            {
                ValidRegister(rt);
                ValidRegister(rs);
            }
            else if (sscanf(line, "%*s $%s", rd) == 1) 
            {
                ValidRegister(rd);
            }
            else if (strcmp(oper, "j") == 0 && sscanf(line, "%*s %s", targaddr) == 1)
            {
                strcpy(Lfound[linecount],targaddr);
            }
            if (strcmp(oper, ".data") == 0)
            {
                a--;
                isText = false;
                isData = true;
            }
        }
        //runs .data segment
        else if (isData)
        {
            if (sscanf(in[a], "%[^:]:%s", targaddr, line) == 2)
            {
                strcpy(Lfound[linecount],targaddr);
            }
            linecount++;
            if (strcmp(oper, ".word") == 0)
            {
                int temp = wordcount;
                token = strtok(line, ",");
                while (token != NULL)
                {
                    inword[wordcount] = atoi(token);
                    token  = strtok(NULL, ",");
                    wordcount++;
                }
                wordsPerLine[Index]= wordcount - temp;
                Index++;
            }
            else if (strcmp(oper, ".space") == 0)
            {
                sscanf(line, "%*s %d", &numberspace);
                wordcount+= numberspace;
                wordsPerLine[Index] = numberspace;
                Index++;
            }
            else 
            {
                //fprintf(stderr,".word or .space expected after .data\n");
                std::cerr<<"Word or space should go after data "<<std::endl;
                exit(1);
            }
        }
        ++a;
    }

    //print out first line
    //printf("%d %d\n",instructioncount,wordcount);
    cout << instruction count << ' ' << wordcount << '\n';
    //reset iterator
    totalcount = linecount;
    for (int i = 0; i < totalcount + 2; i++)
    {
        if (strlen(Lfound[i]) > 0)
        {
            for (int j = 0; j < totalcount + 2; j++)
            {
                if (strcmp(Llocation[j], Lfound[i]) == 0)
                {
                    Found = true;
                }
            }
            if (!Found)
            {
                //fprintf(stderr,"Unable to find label %s\n", Lfound[i]);
                 std::cerr<<"Label not found "<<Lfound[i]<<std::endl;
                exit(1);
            }
            Found = false;
        }

    }
    linecount = 0;

    for (int z = 0; z < totalcount; z++) //while (intake[a][b] != 0)
    {
        //save to read by line
        strcpy(line,in[z]);

        //reset integer binary builder (will later convert int to hex)
        binary = 0;

        //set to something guaranteed not to be found as a label
        strcpy(immed, "!"); 
        
        //if there is a number in $,$,#($)
        offset = 0;
        if (sscanf(line, "%s $%[^,],%d($%[^)]", oper, rt, &offset, rs) == 4)
        {
            binary = OpCode(oper) << 5;
            binary = (binary + RegisterIndex(rs)) << 5;
            binary = (binary + RegisterIndex(rt)) << 16;
            binary += offset;
        }

        //$,$,n($)) type
        else if (sscanf(line, "%s $%[^,],($%[^)]", oper, rt, rs) == 3 || 
            sscanf(line, "%s $%[^,],%[^(]($%[^)]", oper, rt, immed, rs) == 4)
        {
            binary = OpCode(oper) << 5;
            binary = (binary + RegisterIndex(rs)) << 5;
            binary = (binary + RegisterIndex(rt)) << 16;
                          
            for (int i = 0; i < totalcount; i++)
            {
                if (strcmp(immed,Llocation[i]) == 0)
                {
                    if (i > instructioncount)
                    {
                        int temp = 0;
                        for (int x = 0; x < i - instructioncount; x++)
                        {
                            temp += wordsPerLine[x];
                        }
                        binary += temp;
                        break;
                    }
                    else 
                    {
                        binary += (i - instructioncount) & 65535;
                        break;
                    }
                } 
            }  
        }

        //$,$,$ type
        else if (sscanf(line, "%s $%[^,],$%[^,],$%s", oper, rd, rs, rt) == 4) 
        {
            binary = RegisterIndex(rs) << 5;
            binary = (binary + RegisterIndex(rt)) << 5;
            binary = (binary + RegisterIndex(rd)) << 11;
            binary += OpCode(oper);
        }
        //$,$,imme/label type
        else if (sscanf(line, "%s $%[^,],$%[^,],%s", oper, rs, rt, immed) == 4) 
        {
            binary = OpCode(oper) << 5;
            if(strcmp(oper,"beq") == 0 || strcmp(oper,"bne") == 0)
            {
                binary = (binary + RegisterIndex(rs)) << 5;
                binary = (binary + RegisterIndex(rt)) << 16;
                for (int i = 0; i < totalcount; i++)
                {
                    if (strcmp(immed,Llocation[i]) == 0)
                    {
                        binary += (i - linecount) & 65535;
                        break;
                    } 
                }  
            }
            else
            {
                // mask negative overflow
                binary = (binary + RegisterIndex(rt)) << 5;
                binary = (binary + RegisterIndex(rs)) << 16;
                binary += atoi(immed) & 65535;
            }
        }
        //$,$
        else if (sscanf(line, "%s $%[^,],$%s", oper, rs, rt) == 3) 
        {
            binary = RegisterIndex(rs) << 5;
            binary = (binary + RegisterIndex(rt)) << 16;
            binary += OpCode(oper);
        }
        //$
        else if (sscanf(line, "%s $%s", oper, rd) == 2) 
        {
            binary = (binary + RegisterIndex(rd)) << 11;
            binary += OpCode(oper);
        }
        else 
        {
            binary = OpCode(oper);
            //j instruction
            if (binary == 2)
            {
                sscanf(line, "%s %s", oper, targaddr);
                binary = 2 << 26; 
                for (int i = 0; i < totalcount; i++)
                {
                    if (strcmp(targaddr,Llocation[i]) == 0)
                    {
                        binary += i;
                        break;
                    } 
                } 
            }
            //syscall and others
            else if (binary < 0)
            {
                if (strcmp(oper, ".word") == 0)
                {
                    linecount++;
                    sscanf(line, "%s %s", oper, line); 
                    token = strtok(line, ",");
                    while (token != NULL)
                    {
                        //printf("%08x\n",atoi(token));
                        std::cout << std::hex << std::setfill('0') << std::setw(8) << atoi(token) << std::endl;

                        token = strtok(NULL, ",");
                    }
                } 
                else if (strcmp(oper, ".space") == 0)
                {
                    linecount++;
                    sscanf(line, "%*s %d", &numberspace);
                    for (int i = 0; i < numberspace; i++)
                    {
                        //printf("%08x\n", 0);
                    std::cout << std::hex << std::setfill('0') << std::setw(8) << 0 << std::endl;
                    }
                }
                continue;
            }
        }
        linecount++;
        //printf("%08x\n", binary);
        //printf("0x%04x\n", 0x424);
        std::cout <<std::hex << std::setfill('0') << std::setw(8) << binary<< std::endl;
        
    }
    return 0;
}

int RegisterIndex(const char* current)
{
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(current, reg[i]) == 0)
        {
            return i;
        }
    }
    return -1; //already checked for good
}


int OpCode(const char* code)
{
    int lenghth=16;
    for (int i = 0; i < lenghth; i++)
    {
        if (strcmp(code, instr[i]) == 0)
        {
            return opcode[i];
        }
    } 
    return -1; //already checked for good
}


int ValidInstruction(const char* op)
{
    int lengthf=16;
    if (strcmp(op, ".data") == 0)
    {
        return 0;
    }
    for (int i = 0; i < lengthf; i++)
    {
        if (strcmp(op, instr[i]) == 0)    //find if instructions valid
        {
            return 1;
        }
    }
    
    
    std::cerr<<"Invalid Instruction "<<op<<linecount+2<<std::endl;
    exit(1);
    /*fprintf(stderr,
            "invalid instruction %s at line %d\n",
            op, linecount + 2);//.text and 0 index
    exit(1);*/
    
    return 0;
}


void ValidRegister(const char* current)
{
    int bits=32;
    for (int i = 0; i < bits; i++)
    {
        if (strcmp(current, reg[i]) == 0)
        {
            return;
        }
    }
    
    std::cerr<<"Invalid Registers "<<current<<linecount+1<<std::endl;
    exit(1);
    
    /*fprintf(stderr,
            "invalid register %s at line %d\n",
            current, linecount + 1); //including .text
    exit(1);*/
}
