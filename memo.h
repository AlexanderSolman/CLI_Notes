#ifndef _MEMO_H_
#define _MEMO_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

// Function deklarations
void help();
void append(char [], char []);
void search(char [], char[]);
void delete(char [], int);
void initiate(char []);

// Variable deklarations<memo.c>
struct options{
    char *hopt;
    char *aopt;
    char *iopt;
    char *sopt;
    char *dopt;
    int num;
};

// Variables for functions<libmemo.c>
struct func_vars{
    FILE *fptr, *tempfptr;
    time_t t;

    struct tm* timeinfo;
    int ID, bufferID;

    char c;
    char timestamp[100];
    char buffer[BUFFER_SIZE];
    char buffercopy[BUFFER_SIZE];
    char temp_file[100];
    char *token, *delimiter;
};

#endif