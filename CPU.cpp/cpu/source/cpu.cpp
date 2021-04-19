﻿#include "../../stack/source/stack.cpp"
//#include <iostream>
//#include <ctime>
//using namespace std;

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

registers rgs[R_SIZE] = {{"R_1", 0},{"R_2", 0}};

int main() 
{
	/*
	   // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   cout << "The local date and time is: " << dt << endl;

   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   cout << "The UTC date and time is:"<< dt << endl;
   */
	int SIZE = 0;
	int* cmd = file(SIZE);

	proc(cmd, SIZE);

	return 0;
}

int* file(int& SIZE) 
{
	FILE* comands = fopen("../binary/TEST.out", "rb");

	fseek(comands, 0, SEEK_END);                          
	SIZE = ftell(comands)/sizeof(int);                     
	rewind(comands);                                     

	int* cmd = (int*)calloc(SIZE, sizeof(int));

	fread(cmd, sizeof(int), SIZE, comands);
	fclose(comands);
	
	for(int i = 0; i < SIZE; i++)
	{
		printf("%3d command is %d\n",i ,(cmd)[i]);
	}

	return cmd;
}

int proc(int* cmd, int SIZE)
{

	FILE* dump = fopen( "dump/dump.txt" , "w");
	int mode = poison;

	STACK stack   (start_size);
	STACK returns (start_size);

	int tmp1 = 0, tmp2 = 0, top = 0;
	int registers[R_SIZE] = {0};

		for(int i = 0;(i < SIZE) && (cmd[i] != EXIT) ; i++)
		{
		//printf("\ncommand %2d is %d\n",i ,cmd[i]);
		fprintf(dump, "\ncommand %2d is %d\n",i ,cmd[i]);
			switch(cmd[i])
			{
				case(NOP):
					break;
				case(PUSH):
					i++;
					stack.push(cmd[i]);	
					break;
				case(ADD):				
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					stack.push( tmp2 + tmp1);
					break;
				case(SUB):			
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					stack.push( tmp2 - tmp1);
					break;
				case(DIV):
					tmp1 = stack.pop();;
					tmp2 = stack.pop();
					stack.push( (tmp2)/(tmp1));
					break;
				case(MUL):
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					stack.push( (tmp2) * (tmp1));
					break;
				case(IN):
					printf("enter a number: ");
					scanf("%d", &tmp1);
					stack.push( tmp1);
					break;
				case(PRINT):
					top = stack.pop();
					stack.push(top);
					printf("print: %d\n", top);
					break;
				case(JUMP):
					i++;
					i = cmd[i] - 2;
					break;
				case(CALL):
				returns.push(i+3);
					i++;
					i = cmd[i] - 2;
					break;
				case(RET):
				tmp1 = returns.pop();
					i = tmp1 - 2;
					break;					
				case(RPOP):
					i++;
					stack.push( rgs[cmd[i]].data);		
					break;
				case(RPUSH):
					i++;
					top = stack.pop();
					rgs[cmd[i]].data = top; 
					break;
				case(JA):
					i++;
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					if (tmp1 > tmp2) i = cmd[i] - 2;
					break; 
				case(JAE):
					i++;
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					if (tmp1 >= tmp2) i = cmd[i] - 2;
					break; 
				case(JB):
					i++;
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					if (tmp1 < tmp2)	i = cmd[i] - 2;
					break; 
				case(JBE):
					i++;
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					if (tmp1 <= tmp2)	i = cmd[i] - 2;
					break; 
				case(JO):
					i++;
					tmp1 = stack.pop();
					if (tmp1 == 0)	i = cmd[i] - 2;
					break; 
				case(JC):
					i++;
					tmp1 = stack.pop();
					if (tmp1 == 1)	i = cmd[i] - 2;
					break; 
				case(JE):
					i++;
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					if (tmp1 == tmp2) i = cmd[i] - 2;
					break; 
				case(JNE):
					i++;
					tmp1 = stack.pop();
					tmp2 = stack.pop();
					if (tmp1 != tmp2)	i = cmd[i] - 2;
					break;     	
				}
		 		/*
				stack.stack_dump ();
				returns.stack_dump ();				
				for(int i = 0; i < 4; i++)
				{
					printf("r_%d = %d; ", i+1, rgs[i].data);
				}
				printf("\n");
				*/
				
				fprintf(dump, "stack:  "); 
				stack.stack_dump_file (dump);
				fprintf(dump, "return: "); 
				returns.stack_dump_file (dump);
				

		}
	fclose(dump);
	free(cmd);
	return 0;

}