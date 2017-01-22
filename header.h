#include <stdio.h>
#include "record.h"
#include <string.h>
#include <stdlib.h>


void getAddress(char[], int);
int addRecord (struct record **, int, char[], char[], int);
int printRecord(struct record *, int);
int modifyRecord(struct record *, int, char[]);
void printAllRecords(struct record *);
int deleteRecord(struct record **, int);
void readfile(struct record **, char []);
void writefile(struct record *, char []);
