#include "../include/assembler.h"

int main(int argc, char* argv[])
{
	char* file_name = (char*) calloc (30, sizeof(char));
	
	int  directory_mode = 0;

	if(argc > 3)
		{
			printf("invalid file name\n");
			exit(1);
		}
	else if(argc == 3)
		{
		file_name = argv[1];
		directory_mode = atoi(argv[2]);
		}
	else if(argc == 2)
		{
		file_name = argv[1];
		}
	else
	{
		file_name = (char*)"unTest.txt";			
	}

	char* symbols = NULL;
	int code_size = 2;
	int SIZE = open(&symbols, &code_size, file_name, directory_mode);

	printf("\ncodesize is %d\n", code_size);
	if(SIZE == OPEN_ERR)
    {
		printf("OPEN_ERR\n");
		return OPEN_ERR;
	}

	 asembler(symbols, SIZE, code_size, file_name, directory_mode);

	return 0;
	free(file_name);
}

int open(char** symbols, int* code_size, char* file_name, int directory_mode)
{


	char* full_file_name = (char*) calloc(50, sizeof(char));
	if (directory_mode)
	{
		strcat(full_file_name, "../../test/test_code/" );
	}
	else 
	{
		strcat(full_file_name, "../../user_code/");
	}
	full_file_name = strcat(full_file_name, file_name);
	printf("full file name is - %s\n", full_file_name);
	printf("mode - %d \n", directory_mode);

	FILE* file1 = fopen(full_file_name, "r+");

	if(file1 == NULL)
    {
		return OPEN_ERR;
	}

	fseek(file1, 0, SEEK_END);
	int SIZE = ftell(file1);
	rewind(file1);
	
	char* symbols_win = (char*)calloc(SIZE, sizeof(char));
    *symbols          = (char*)calloc(SIZE, sizeof(char));
	fread(symbols_win, sizeof(char), SIZE, file1);
      
    //printf("%s\n", symbols_win);

	for(int i = 0; i < SIZE; i++)
    {
		if((symbols_win)[i] == ' ' || (symbols_win)[i] == '\n' || (symbols_win)[i] == '\r' )
        {
			(*code_size)++;
			(symbols_win)[i] = '\0';
		}
	}

	int cnt = 0;
    for(int i = 0; i < SIZE; i++)
    {
        if (!((symbols_win)[i] == '\0' && (symbols_win)[i+1] == '\0'))
        {
            (*symbols)[cnt] = (symbols_win)[i];
            cnt++;
        }
		else (*code_size)--;
    }

	fclose(file1);

	return SIZE;
}

void asembler(char* symbols, int SIZE, int code_size, char* file_name, int directory_mode)
{

    FILE* file2 = fopen("../../cpu/binary/TEST.out", "w");

	int nof_lable = lable_count(symbols, SIZE);
    int*  code   = (int*)  calloc(SIZE, sizeof(int));
	label* labels = (label*) calloc(nof_lable, sizeof(label));

	make_label(	&labels, symbols, SIZE, nof_lable);

    int cod_pos = 0, cmd_str = 0,str_size = 0;
	char buffer[100];

	for(int i = 0; i < SIZE; i++)
    {
		if(symbols[i] == '\0')
        {
			if(!strcmp(symbols + cmd_str, "nop"))
			{
				emit (&cod_pos, code, buffer, NOP);
			}
			EMIT(nop, NOP)
			EMIT(push, PUSH)
			EMIT(add, ADD)
			EMIT(sub, SUB)
			EMIT(div, DIV)
			EMIT(mul, MUL)			
			EMIT(in, IN)
			EMIT(print, PRINT)
			EMIT(out, OUT)
			EMIT(return, RET)
			EMIT(exit, EXIT)
			EMIT(rpush, RPUSH)
			EMIT(rpop, RPOP)
			EMIT(r_1, R_1)
			EMIT(r_2, R_2)
			EMIT(r_3, R_3)			
			EMIT(rax, RAX)			
			EMIT(:, NOP)			
			INJUMP(jump,JUMP)
			INJUMP(call,CALL)
			INJUMP(ja,JA)
			INJUMP(jae,JAE)
			INJUMP(jb, JB)
			INJUMP(jbe, JBE)
			INJUMP(jc, JC)
			INJUMP(jo, JO)
			INJUMP(je, JE)
			INJUMP(jne, JNE)
			else 
			{	
				code[cod_pos++] = atoi(symbols + cmd_str);
			}
			cmd_str = i + 1;
		}
	}

	/*
	for ( int i = 0; i < code_size; i++)
	{
		printf("code [%-3d] is (%d)\n",i ,code[i]);
	}
	*/

	fwrite(code, sizeof(int), code_size, file2);

	if(directory_mode)
	{
		unit_test(code, symbols, code_size, file_name);
	}

	fclose(file2);
	free(symbols);
	free(code);   
}

int lable_count(char* symbols, int SIZE)
{
	int count = 0;
	
	for(int i = 0; i < SIZE; i++)
	{
	if((symbols)[i] == ':') count++;	
	}

	return count;
}

int make_label(label** labels, char* symbols, int SIZE, int nof_labels)
{
	int label = 0;
	int cnt = 1;
	for(int i = 0; i < SIZE; i++)
	{	
		if (symbols[i] == '\0') cnt++;

		if (symbols[i] == ':')
		{
			strcpy( ((*labels)[label].name), (symbols + i + 1));
			(*labels)[label].adress = cnt;
			label++;
		}
	}

	/* label print 
	for (int i = 0; i < nof_labels; i++)
	{
	 printf("\nlabel  %d is %s\n",i ,(*labels)[i].name);
	 printf("adress %d is %d\n\n",i ,(*labels)[i].adress);
	}
	*/ 
	return label;
}

int emit (int* corrector, int* code, char* buffer, int number)
{

	code[(*corrector)++] = number;
					
}

int injump(int* cod_pos, int* i, int* cmd_str, int* code, char* symbols, char* buffer,label* labels, int n_labels, int str_size)
{
				*cmd_str = *i+1;
				for(int label = 0; label < n_labels; label++)
				{
					if (!strcmp(symbols + *cmd_str,  labels[label].name))
					{	
							(code)[(*cod_pos)++] = labels[label].adress;

						int len = strlen(labels[label].name);
						*i = *i + len + 1;
						*cmd_str = *i;
						break;
					}
				} 
}

void unit_test(int* code,char* symbols, int code_size, char* file_name)
{
	 FILE* test = fopen( file_name , "w");
	 char string[30];
	 int marker = 0;
	 int null_marker = 0;
	 int space_marker = 6;


	 for(int i = 0; i < code_size; i++)
	 {
		 fprintf(test, "%3d) ", i);
		 while (symbols[marker] != '\0')
		 {
			
			 fprintf(test, "%c", symbols[marker++]);
			 space_marker--;
		 }
		 for(int i = 0; i < space_marker; i++)  fprintf(test, " "); 
		null_marker = ++marker;
		space_marker = 6;

		 fprintf(test, " - (%d)\n", code[i]);
	 }
	 fclose(test);

}

//01.04.2021
//g++ -I
//propusk strok
//g++ asm.cpp -o asm.out //vo
//out нужно сделать в бин
// чек валгринд на проёб памяти
// gnumake
// StasSD - git
