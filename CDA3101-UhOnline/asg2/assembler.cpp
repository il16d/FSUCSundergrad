/******************************************************
 * *
 * Name: Iho Lopez *
 * Class: CDA 3101 *
 * Assignment: Asg 2 (an assembler of a subset of the *
 * MIPS assembly language) *
 * Compile:  g++ assembler.cpp -c
 g++ assembler.o -o out.exe
 out.exe < sum.asm > asm.obj
 * *
 ******************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <iomanip>



const int INSTRUCTION = 32768;
const int REGISTERS = 8;
const int ASSEMBLY = 32768 * 2 + 2;
const int LINE = 81;
const int LABELS = 11;

const char* const registernames[] =
        {"zero","at","v0","v1","a0","a1","a2","a3",
         "t0","t1","t2","t3","t4","t5","t6","t7",
         "s0","s1","s2","s3","s4","s5","s6","s7",
         "t8","t9","k0","k1","gp","sp","fp","ra"};

const int opcode[] =
    {9, 33, 36, 4, 5, 26, 2, 35,
    16, 18, 24, 37, 42, 35, 43, 12};

const char* const instructionnames[] =
    {"addiu","addu","and","beq","bne","div","j","lw",
     "mfhi","mflo", "mult","or","slt","subu","sw","syscall"};



void ValidRegister(const char*);
int OpCode(const char*);
int ValidInstruction(const char*);
int RegisterIndex(const char*);

int linecount = 0;

int main(int argc, char** argv)
{
   
    
    
    char oper[8], rs[REGISTERS], rt[REGISTERS], rd[REGISTERS];
    
    int wordsPerLine[INSTRUCTION], inword[INSTRUCTION];
    
    bool isData = false, isText = false, Found = false;
    
    char Llocation[ASSEMBLY][LABELS];
    
    char line[LINE], targaddr[LABELS], immed[LABELS];
    
    char in[ASSEMBLY][LINE];
    
    char Lfound[ASSEMBLY][LABELS];
    
    int instructioncount = 0, wordcount = 0, totalcount = 0, Index = 0;
    
    
    
    
    int numberspace, binary, offset;
    int a = 0;
    char comment;
    char* token; 
    

    
    while(fgets(in[a], LINE, stdin))
    {
      
        if (instructioncount == 0 && sscanf(in[a], " %s", line) && strcmp(line, ".text") == 0)
        {
            isText = true;
            continue;
        }
        else if (!isText && !isData)
        {
            
            std::cerr<<"Not text directive "<<in[a]<<std::endl;
            
            exit(1);
        }
        
        if (sscanf(in[a]," %c", &comment) == 1)
        {
            if (comment == '#')
            {
                continue;
            }
        } 
        
        sscanf(in[a], "%[^#\n]", in[a]);
      
        
        if (sscanf(in[a], "%[^:]:%[^\n]", Llocation[linecount], in[a]) != 2)
        {
            strcpy(Llocation[linecount],"");
        }
        
        strcpy(line, in[a]);
        sscanf(line, "%s", oper);
        
        
        if (isText)
        {
            linecount += ValidInstruction(oper);
            instructioncount = linecount;
            
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
                
                std::cerr<<"Word or space should go after data "<<std::endl;
                exit(1);
            }
        }
        ++a;
    }

    
    std::cout << instructioncount << ' ' << wordcount << '\n'<<std::endl;
    
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
                
                 std::cerr<<"Label not found "<<Lfound[i]<<std::endl;
                exit(1);
            }
            Found = false;
        }

    }
    linecount = 0;

    for (int z = 0; z < totalcount; z++) //while (intake[a][b] != 0)
    {
        
        strcpy(line,in[z]);

        
        binary = 0;

        
        strcpy(immed, "!"); 
        
        
        offset = 0;
        if (sscanf(line, "%s $%[^,],%d($%[^)]", oper, rt, &offset, rs) == 4)
        {
            binary = OpCode(oper) << 5;
            binary = (binary + RegisterIndex(rs)) << 5;
            binary = (binary + RegisterIndex(rt)) << 16;
            binary += offset;
        }

        
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

       
        else if (sscanf(line, "%s $%[^,],$%[^,],$%s", oper, rd, rs, rt) == 4) 
        {
            binary = RegisterIndex(rs) << 5;
            binary = (binary + RegisterIndex(rt)) << 5;
            binary = (binary + RegisterIndex(rd)) << 11;
            binary += OpCode(oper);
        }
        
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
                //overflow
                binary = (binary + RegisterIndex(rt)) << 5;
                binary = (binary + RegisterIndex(rs)) << 16;
                binary += atoi(immed) & 65535;
            }
        }
        
        else if (sscanf(line, "%s $%[^,],$%s", oper, rs, rt) == 3) 
        {
            binary = RegisterIndex(rs) << 5;
            binary = (binary + RegisterIndex(rt)) << 16;
            binary += OpCode(oper);
        }
        
        else if (sscanf(line, "%s $%s", oper, rd) == 2) 
        {
            binary = (binary + RegisterIndex(rd)) << 11;
            binary += OpCode(oper);
        }
        else 
        {
            binary = OpCode(oper);
            
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
           
            else if (binary < 0)
            {
                if (strcmp(oper, ".word") == 0)
                {
                    linecount++;
                    sscanf(line, "%s %s", oper, line); 
                    token = strtok(line, ",");
                    while (token != NULL)
                    {
                        
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
                        
                    std::cout << std::hex << std::setfill('0') << std::setw(8) << 0 << std::endl;
                    }
                }
                continue;
            }
        }
        linecount++;
        
        std::cout <<std::hex << std::setfill('0') << std::setw(8) << binary<< std::endl;
        
    }
    return 0;
}

int RegisterIndex(const char* current)
{
    int bits1=32;
    for (int i = 0; i < bits1; i++)
    {
        if (strcmp(current, registernames[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}


int OpCode(const char* code)
{
    int lenghth=16;
    for (int i = 0; i < lenghth; i++)
    {
        if (strcmp(code, instructionnames[i]) == 0)
        {
            return opcode[i];
        }
    } 
    return -1;
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
        if (strcmp(op, instructionnames[i]) == 0)
        {
            return 1;
        }
    }
    
    
    std::cerr<<"Invalid Instruction "<<op<<linecount+2<<std::endl;
    exit(1);
    
    
    return 0;
}


void ValidRegister(const char* current)
{
    int bits=32;
    for (int i = 0; i < bits; i++)
    {
        if (strcmp(current, registernames[i]) == 0)
        {
            return;
        }
    }
    
    std::cerr<<"Invalid Registers "<<current<<linecount+1<<std::endl;
    exit(1);
    
}
