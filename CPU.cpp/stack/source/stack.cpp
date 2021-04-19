
#include "../include/stack.h"
#line 4

#define DEBUG 0                      
#define DBG(expr) if (DEBUG) {expr}

STACK::STACK (int in_size)
{
    this -> capacity    = in_size;
    this -> buf         = (int*) calloc(in_size, sizeof(int));
    this -> size        = 0;
    this -> destruction = non_destructed;

    for (int i = this -> size ; i < this -> capacity; i++)
    {
            this -> buf[i] = poison;
    }

stack_ok();
}

//-----------------------------------------------------------------------------

void STACK::push(int element)
{
stack_ok();

    if (this -> capacity == this -> size) recalloc();
    this -> buf[this -> size] = element;
    this -> size ++;

stack_ok();
}

//-----------------------------------------------------------------------------

int STACK::pop()
{
stack_ok();

    int element = this -> buf[this -> size - 1];
    this -> buf[this -> size - 1] = poison;
    this -> size --;
    return element;

stack_ok();
}
//-----------------------------------------------------------------------------

void STACK::recalloc()
{
stack_ok();

     STACK local_stack(100);

    this -> buf = (int*) realloc(this -> buf,(this -> capacity + upsize)  * sizeof(int));
    assert(this -> buf != NULL);
    this -> capacity += upsize ;

    for (int i = this -> size; i < this -> capacity; i++)
    this -> buf[i] = poison;

stack_ok();
}

//-----------------------------------------------------------------------------

void STACK::stack_printf ()
{
    printf("Stack - (");
    for(int i = 0; i < this -> size - 1; i++) printf("%d, ", this -> buf[i]);

    printf("%d)\n", this -> buf[this -> size - 1]);

}

//-----------------------------------------------------------------------------

STACK::~STACK()
{
stack_ok();

    this -> capacity    = poison;
    this -> size        = poison;
    this -> destruction = destructed;
    free (this -> buf);
}

//-----------------------------------------------------------------------------

int STACK::errortest()
{
    int bag = no_error;
    if ((this -> capacity > this -> size) && (this -> buf[this -> size] != poison )) bag = unpoisoned_element;
    if (this -> capacity < this -> size)                                             bag = bad_capacity;
    if (this -> buf == NULL)                                                         bag = bad_buff_adress;
    if (this == NULL)                                                                bag = bad_stack_adress;
    if (this -> destruction == destructed)                                           bag = destructed_stack;
    return bag;
}

//-----------------------------------------------------------------------------

void STACK::stack_dump ()
{
    int error = errortest ();
    # ifdef MORE
                    printf ("\n[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n");
    if (error == 0) printf("Stack (OK)\n");
    else            
    {
                    printf("Stack (BAD), error - %d\n", error);
                    print_error(error);
    }
                    printf("adress - [%p]\n", this);
                        printf("{\n");
                        printf("\tcapacity    = %d\n", this -> capacity);
                        printf("\tsize        = %d\n", this -> size);
                        printf("\tdestruction = %d\n", this -> destruction);
                        printf("\tbuf [%p]\n",this -> buf);
                            printf("\t{\n");
                            for(int i = 0; i < this -> capacity;i++) printf("\t\t[%d]: %d\n", i, this -> buf[i]);
                            printf("\t}\n");
                        printf("}\n");
                    printf ("[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n\n");
    # else
    if (error == 0) printf("(OK)\t");
    else            
    {
        printf("   (!BAD!), error - %d\n", error);
        print_error(error);
    }
    printf("Buf: ");

    for (int i = 0; i < this -> size; i++)
    {
    printf("[%d]",this -> buf[i]);   
    }


    printf("\n");
    # endif

}

void STACK::stack_dump_file (FILE* file)
{
    int error = errortest ();
    # ifdef MORE
                    fprintf( file, ("\n[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n");
    if (error == 0) fprintf( file,"Stack (OK)\n");
    else            
    {
                    fprintf( file,"Stack (BAD), error - %d\n", error);
                    print_error_file(error, file);
    }
                    fprintf( file,"adress - [%p]\n", this);
                        fprintf( file,"{\n");
                        fprintf( file,"\tcapacity    = %d\n", this -> capacity);
                        fprintf( file,"\tsize        = %d\n", this -> size);
                        fprintf( file,"\tdestruction = %d\n", this -> destruction);
                        fprintf( file,"\tbuf [%p]\n",this -> buf);
                            fprintf( file,"\t{\n");
                            for(int i = 0; i < this -> capacity;i++) fprintf( file,"\t\t[%d]: %d\n", i, this -> buf[i]);
                            fprintf( file,"\t}\n");
                        fprintf( file,"}\n");
                    fprintf( file, ("[][][][][][][][][][][][][][][][][][][][][][][][][][][]\n\n");
    # else
    if (error == 0) fprintf( file,"(OK)\t");
    else            
    {
        fprintf( file,"   (!BAD!), error - %d\n", error);
        print_error(error);
    }
    fprintf( file,"Buf: ");

    for (int i = 0; i < this -> size; i++)
    {
    fprintf( file,"[%d]",this -> buf[i]);   
    }


    fprintf( file,"\n");
    # endif

}

void STACK::stack_ok()
{
if(errortest() != 0)
    {
    stack_dump();
    }
}


void print_error(int error)
{
    switch (error)
    {
        case no_error:           printf("no_error\n");  break;
        case destructed_stack:   printf("destructed_stack\n");  break;
        case bad_stack_adress:   printf("bad_stack_adress\n");  break;
        case bad_buff_adress:    printf("bad_buff_adress\n");  break;
        case bad_capacity:       printf("bad_capacity\n");  break;
        case unpoisoned_element: printf("unpoisoned_element\n");  break;
    }
}

void print_error_file(int error, FILE* file)
{
    switch (error)
    {
        case no_error:           fprintf( file,"no_error\n");  break;
        case destructed_stack:   fprintf( file,"destructed_stack\n");  break;
        case bad_stack_adress:   fprintf( file,"bad_stack_adress\n");  break;
        case bad_buff_adress:    fprintf( file,"bad_buff_adress\n");  break;
        case bad_capacity:       fprintf( file,"bad_capacity\n");  break;
        case unpoisoned_element: fprintf( file,"unpoisoned_element\n");  break;
    }
}

int STACK::get_size()
{
    int value = this -> size;
    assert(value = poison);
    return value;
}

int& STACK::operator[] (int n)
{
    assert (0 <= n && n < this -> size);
    return this -> buf[n];
}

/*
11.04.2021
Урок по динамической памяти

1)  data_ (new int [10] {}),
    size_ (10),
    capacity_(10);
  делаем переменную в си++, он вызывает конструктор(в этом его фишка и он лучше)
    new использует malloc

2) size_t - это дефайн деда или какойто тип в плюсах??

3) delete[] (data_);    
   data_ = nullptr;  - в деструктор вместо фри

4) копирование(нам нужно копировать буффер а не ссылку на него)
-решение проблемы - делаем конструктор копирования;
*/


