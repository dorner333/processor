#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMIT(arg1, arg2)    else if(!strcmp(symbols + cmd_str, #arg1))\
							{										  \
							emit (&cod_pos, code, buffer, arg2);	  \
							}

#define INJUMP(arg1, arg2)	else if(!strcmp(symbols + cmd_str, #arg1))\
							{										  \
							emit (&cod_pos, code, buffer, arg2);	  \
							injump (&cod_pos, &i, &cmd_str, code, symbols, buffer, labels, nof_lable, str_size);\
							}											
												
const int OPEN_ERR = 1;

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

typedef struct LABEL
{
char name[50];
int adress;	
}label;

int open(char** symbols, int* code_size, char* file_name, int directory_mode);
void asembler(char* symbols, int SIZE, int code_size, char* file_name, int directory_mode);
int lable_count(char* symbols, int SIZE);
int make_label(label** labels, char* symbols, int SIZE, int nof_labels);
int emit (int* corrector, int* code, char* buffer, int number);
int injump(int* cod_pos, int* i, int* cmd_str, int* code, char* symbols, char* buffer,label* labels, int n_labels, int str_size);
char* full_file_name = (char*) calloc(30, sizeof(char));
void unit_test(int* code,char* symbols, int code_size, char* file_name);
