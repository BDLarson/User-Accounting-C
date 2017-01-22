/******************************************************************************
//
// FILE:          iofunctions.c
//
// DESCRIPTION:   This is file contains the functions readfile and
//		  writefile. Readfile is used to read in the textfile
//		  "output.txt". The program will not read any other file
//		  in if the name is different, unless changed in the main.
//		  writefile will write a text file "output.txt" containing
//		  the contents of the database.
//
*****************************************************************************/

#include "header.h"

extern int debugmode;

/******************************************************************************
// Function name: readfile
//
// DESCRIPTION:   A function that takes a struct account array, int pointer, and
//			 a char array as input. This function is able to read
//			 from a textfile and properly store each line into their
//			 proper variable, which is then all passed to addrecord.
//
// Parameters:    theBeginning: a pointer pointer argument that will be passed
//			 to the addrecord function.
//		  filename: The text file that will be read line by line, in
//			 the form of account number, name, address, and year
//			 of birth, then passed to addrecord.
//
// Return values: n/a because it's void
//
*****************************************************************************/

void readfile(struct record **theBeginning, char filename[])
{
	FILE * file;
	int tempAcc;
	int tempYOB;
	char tempName[100];
	char tempAdr[100];
	int currState;
        int nameLength;
	int addressLine;
	int addressLength;
	int numReadIn;
	char inputRecord [300];
        char can[100];
        char * garbage;


        file = fopen(filename,"r"); /*Creates the buffer*/
	tempAcc = 0;
	tempYOB = 0;
        currState = 1;
        garbage = can;
        nameLength = 0;
	addressLine = 1;
	numReadIn = 0;

	if(debugmode == 1)
	{
                printf("\n");
                printf("***readfile function called***\n");
                printf("\n");
                printf("***Name of file to be read***\n");
		printf("%s\n", filename);
                printf("\n");

		if(file == NULL)
		{
			printf("***There was an error opening the file***\n");
		}
	}

	if (file != NULL)
	{
		while(fgets(inputRecord, 300, file) != NULL)
		{

			if (currState == 1)
			{
				tempAcc = strtol(inputRecord, &garbage, 10);
				currState++;
			}
			else if(currState == 2)
			{
				nameLength = (strlen(inputRecord) - 1);
				if(inputRecord[nameLength] == '\n')
				{
					inputRecord[nameLength] = '\0';
				}
				strcpy(tempName, inputRecord);
				currState++;
			}
			else if(currState == 3)
			{
				addressLength = (strlen(inputRecord) - 2);

				if (addressLine == 1)
				{
					strcpy(tempAdr, inputRecord);
					addressLine++;
				}
				else
				{
					strcat(tempAdr, inputRecord);
				}

                        	if(inputRecord[addressLength] == '!')
                        	{
					tempAdr[strlen(tempAdr) - 2] = '\0';
                                	currState++;
                                	addressLine = 1;
                        	}
			}
			else if(currState == 4)
			{
                        	tempYOB  = strtol(inputRecord, &garbage, 10);
				currState = 1;
				numReadIn++;
				addRecord(theBeginning, tempAcc, tempName, tempAdr, tempYOB);
			}
			else
			{
				printf("***There was an error!***\n");
			}
		}
	        fclose(file); /*Closes the buffer*/
	}

	if(debugmode == 1)
	{
		printf("Number of records read from file: %d\n", numReadIn);
	}
}

/******************************************************************************
// Function name: writefile
//
// DESCRIPTION:   A function that takes a struct array, int, and a char array
//		  as input. This function is able to write the contents of
//		  the database into a textfile called "output.txt".
//
// Parameters:    theBeginning: a pointer pointer argument used to determine
//			 the start of the database list.
//		  filename: the char array that is used to hold the contents
//			 of the database that is being written to it. The
//			 address of each record will end in "!" to delimit
//			 the end of the address, in order to re-read the
//			 same file. The end product is a textfile called
//			 "output.txt".
//
// Return values: n/a because it's void
//
*****************************************************************************/

void writefile(struct record *theBeginning, char filename[])
{
	struct record *currRecord;
	int numWriteRec;

	currRecord = theBeginning;
	numWriteRec = 0;
	FILE * file = fopen(filename,"w"); /*Creates the buffer*/

        if(debugmode == 1)
        {
                printf("\n");
                printf("***writefile function called***\n");
                printf("\n");
                printf("***Name of file to be written***\n");
                printf("%s\n", filename);
                printf("\n");
        }

	/*Check for file*/

	while(currRecord != NULL)
	{
		fprintf(file, "%i\n", currRecord -> accountno);
    fprintf(file, "%s\n", currRecord -> name);
    fprintf(file, "%s!\n", currRecord -> address);
    fprintf(file, "%i\n", currRecord -> yearofbirth);
		currRecord = currRecord -> next;
		numWriteRec++;
	}

	fclose(file); /*Closes the buffer*/

	if(debugmode == 1)
	{
		printf("Number of records written to file: %d\n", numWriteRec);
	}
}
