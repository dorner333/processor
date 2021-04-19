#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//#define MORE 1   

enum
{
    destructed = 1,
    non_destructed = 0,
    start_size = 10,
    upsize = 4,
    poison = -666
};

class STACK
{
private:
    int size;
    int capacity;
    int* buf;
    int destruction;


public:
STACK(int in_size);
~STACK();

void push         (int element);

int  pop          ();

void recalloc     ();

void stack_printf ();

int  errortest    ();

void print_error_file(int error, FILE* file);

void stack_dump   ();

void stack_dump_file (FILE* file);

void stack_ok     ();

int& operator[] (int n);

int get_size();

};

enum error {
    no_error,
    destructed_stack,
    bad_stack_adress,
    bad_buff_adress,
    bad_capacity,
    unpoisoned_element
};

//[*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*][*]

void print_error  (int error);


/*
get_size (размер стека)
elem  (выводит адрес n-ый элемент)
__PRETTY_FUNCTION__

int operator[](int n) заменим элем на это
int value = stk[0]; вызов функции

int& ссылка, она сама пишет * и &

const stack* - защищаем от изменений в си

void print() const; - можно использовать с константными

для константных возвращяем константную ссыылку, для неконствнтных - ссылку
*/
