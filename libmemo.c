#include "memo.h"

// -h read from .txt file and prints 'help' message to terminal
void help(){
    struct func_vars h;
    if((h.fptr = fopen("help.txt", "r")) == NULL){
        printf("Could not help");
        exit(1);
    }
    
    while((h.c = fgetc(h.fptr)) != EOF){
        printf("%c", h.c);
    }
    fclose(h.fptr);
}

// -a appends to .csv file of choosing and checks previous entry ID before incrementation
void append(char targetFile[], char message[]){
    struct func_vars a;
    a.ID = 0;
    a.bufferID = 0;
    strcat(targetFile, ".csv");

    if((a.fptr = fopen(targetFile, "r")) == NULL){
        printf("Could not add '%s' to %s", message, targetFile);
        exit(3);
    }

    // Reading each line then seperating by comma which cast first token to int i.e ID
    while (fgets(a.buffer, sizeof(a.buffer), a.fptr)){
        a.token = strtok(a.buffer, ",");
        while(a.token!=NULL){
            sscanf(a.token, "%d", &a.bufferID);
            a.ID = a.bufferID + 1;
            break;
        }
    }
    fclose(a.fptr);

    // Importing local time and formatting the apperence
    time(&a.t);
    a.timeinfo = localtime(&a.t);
    strftime(a.timestamp, 80,
             "%d-%m-%Y %H:%M:%S",
             a.timeinfo);
    
    if((a.fptr = fopen(targetFile, "a")) == NULL){
        printf("Could not execute command");
        exit(2);
    }

    fprintf(a.fptr, "%d,%s,%s\n", a.ID, a.timestamp, message);
    fclose(a.fptr);
}

// -i creates a new .csv file. Name is chosen freely
void initiate(char fileName[]){
    struct func_vars i;
    strcat(fileName, ".csv");
    // Checking if file can be open and read, if possible file exists
    // Else it is created with ID,Time,Note row by default
    if((i.fptr = fopen(fileName, "r")) != NULL){
        printf("File already exists\n");
        fclose(i.fptr);
    }else {
        if((i.fptr = fopen(fileName, "w")) == NULL){
            printf("Failure creating file");
            exit(6);
        }
        fprintf(i.fptr, "ID,Time,Note\n");
    }
    fclose(i.fptr);
}

// -s searches for given string in a given .csv file
// Seperates ID,Date,Time,Text with delimiters
void search(char targetFile[], char sWord[]){
    struct func_vars s;
    s.delimiter = ",  \n";
    s.bufferID = 0;
    strcat(targetFile, ".csv");

    if((s.fptr = fopen(targetFile, "r")) == NULL){
        printf("Could not open %s", targetFile);
        exit(3);
    }
    while (fgets(s.buffer, sizeof(s.buffer), s.fptr)){
        strcpy(s.buffercopy, s.buffer);
        s.token = strtok(s.buffer, s.delimiter);
        while(s.token!=NULL){
            sscanf(s.token, "%d", &s.bufferID);
            if(strcmp(s.token, sWord) == 0 && s.bufferID > 0){
                printf("%s", s.buffercopy);
                break;
            }
            s.token = strtok(NULL, s.delimiter);
        }
    }
    fclose(s.fptr);
}

// -d makes a copy of existing file without the given ID
void delete(char targetFile[], int targetID){
    struct func_vars d;
    d.bufferID = 0;
    strcat(targetFile, ".csv");
    strcpy(d.temp_file, "temp");
    strcat(d.temp_file, targetFile);
    
    if((d.fptr = fopen(targetFile, "r")) == NULL || (d.tempfptr = fopen(d.temp_file, "w")) == NULL){
        printf("Could not delete entry '%s' from '%s'", targetID, targetFile);
        exit(2);
    }

    while (fgets(d.buffer, sizeof(d.buffer), d.fptr)){
        strcpy(d.buffercopy, d.buffer);
        d.token = strtok(d.buffer, ",");
        while(d.token!=NULL){
            sscanf(d.token, "%d", &d.bufferID);
            break;
        }
        if(targetID != d.bufferID){
            fputs(d.buffercopy, d.tempfptr);
        }
    }

    fclose(d.fptr);
    fclose(d.tempfptr);
    
    remove(targetFile);
    rename(d.temp_file, targetFile);
}