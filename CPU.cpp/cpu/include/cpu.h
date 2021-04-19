#pragma once

#define FILE_ERROR 1
#define CMD_ERROR 2

struct registers
{
public:
	const char* name;
	int data;
};

//	   0        1     2    3    4    5    6   7      8    9    10
enum { NOP = 0, PUSH, ADD, SUB, DIV, MUL, IN, PRINT, OUT, RET, EXIT, 
//11    12   13  14   15  16   17  18  19  20
  CALL, JUMP, JA, JAE, JB, JBE, JO, JC, JE, JNE} CMDS; // standart comands
//     0          1  2    3    
enum { R_1 = 0, R_2, R_3, RAX, R_SIZE } RG;  // registers
//     32		   33        
enum { RPUSH =	32, RPOP }RCMDS; // registers commands
//     64 
enum { CMD = 64 }UCMD; // user commands

int* file (int& SIZE);
int proc(int* cmd, int SIZE);
