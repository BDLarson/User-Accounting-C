/******************************************************************************
//
// FILE:          dbfunctions.c
//
// DESCRIPTION:   These functions are used for database purposes only.
//		  When a menu option is selected one of these will be called.
//		  If these functions are called via debugmode, then messages
//		  will display with information regarding function called and
//		  parameters passed.
//
*****************************************************************************/

#include "header.h"
extern int debugmode;

/******************************************************************************
// Function name: addRecord
//
// DESCRIPTION:   A function that takes a pointer argument, two ints, and two
//                char arrays. Allows the user to add a record with specifics
//                like: name, address, birth year, and account number. All
//		  records added with similar year of birth, will be added
//		  after already existing ones, no matter how many exist.
//
// Parameters:    start: start pointer pointer argument
//                uaccountno: an integer value for the account number.
//                uname: a char array to hold the full name.
//                uaddress: a char array to hold the address.
//                uyob: an integer to hold the birth year.
//
// Return values: int (for now 0)
//
*****************************************************************************/

int addRecord(struct record **start, int uaccountno, char uname[], char uaddress[], int uyob)
{

        int exitCount;
	int numRecAdded;
        struct record *currRecord;
        struct record *prevRecord;
	struct record *tempRecord;

        exitCount = 0;
	numRecAdded = 0;
        currRecord = *start;
        prevRecord = NULL;
	
	/*Allocate space on the heap for tempRecord*/
        tempRecord = (struct record*)malloc(sizeof(struct record));
	
	/*Store parameters passed into individual members of tempRecord*/
        tempRecord -> accountno = uaccountno;
        strcpy(tempRecord -> name, uname);
        strcpy(tempRecord -> address, uaddress);
        tempRecord -> yearofbirth = uyob;
	tempRecord -> next = NULL;

        if(debugmode == 1)
        {
                printf("-------------------------------\n");
                printf("***addRecord function called***\n");
                printf("\n");
                printf("***Account number passed***\n");
                printf("%d\n", uaccountno);
		printf("\n");
                printf("***Name passed***\n");
                printf("%s\n", uname);                
		printf("\n");
                printf("***Address passed***\n");
                printf("%s\n", uaddress);
		printf("\n");
		printf("***Birth year passed***\n");
                printf("%d\n", uyob);
		printf("--------------------------------\n"); 
	}

        while(exitCount == 0)
        {
		/*Check whether list is empty or not*/
                if(currRecord == NULL)
                {
			*start = tempRecord;
			tempRecord -> next = NULL;
			exitCount = 1;
                        numRecAdded++;
	        }
		/*Add new record to the next available spot*/
                else if(currRecord -> yearofbirth >= tempRecord -> yearofbirth && currRecord -> next == NULL)
                {
			currRecord -> next = tempRecord;
			tempRecord -> next = NULL;
			exitCount = 1;
                        numRecAdded++;
                }
		/*Add new record to the current start link and shift down the existing list*/
                else if(currRecord -> yearofbirth < tempRecord -> yearofbirth && prevRecord == NULL)
                {
			tempRecord -> next = currRecord;
			*start = tempRecord;
			exitCount = 1;
                        numRecAdded++;
                }
		/*Add new record in between the currRecord and prevRecord*/
                else if(currRecord -> yearofbirth < tempRecord -> yearofbirth && prevRecord != NULL)
		{
			prevRecord -> next = tempRecord;
			tempRecord -> next = currRecord;
			exitCount = 1;
			numRecAdded++;
		}
		else
		{
			/*Move down the list*/
			prevRecord = currRecord;
			currRecord = currRecord -> next;
		}
        }
	if(debugmode == 1)
	{
		printf("Number of records successfully added: %d\n", numRecAdded);
	}

	return 0;
}


/******************************************************************************
// Function name: printRecord
//
// DESCRIPTION:   A function that takes a pointer argument and int.
//		  Allows the user to specify an account record to print.
//		  If the program cannot find the account number then the
//		  number of records printed will be 0. All records with the
//		  same account number, will be printed in the order that
//		  they are sorted by in the list. 
//
// Parameters:    theBeginning: start pointer argument
//		  uaccountno: an integer value for the account number. 
//
// Return values: int (for now 0)
//
*****************************************************************************/

int printRecord(struct record *theBeginning, int uaccountno)
{
	struct record *currRecord;
	int numPrintRec;

	currRecord = theBeginning;
	numPrintRec = 0;

        if(debugmode == 1)
        {
		printf("---------------------------------\n");
		printf("***printRecord function called***\n");
		printf("\n");
		printf("***Account number to be printed***\n");
                printf("%d\n", uaccountno);
		printf("----------------------------------\n");
	}

        if(theBeginning != NULL)
        {
                while(currRecord != NULL)
                {
                        if(currRecord -> accountno == uaccountno)
                        {
				printf("\n");
				printf("%d\n", currRecord -> accountno);
                		printf("%s\n", currRecord -> name);
                		printf("%s\n", currRecord -> address);
                		printf("%d\n", currRecord -> yearofbirth);
                		printf("\n");
				numPrintRec++;
			}
                        currRecord = currRecord -> next;
                }
        }

	if(debugmode == 1 && numPrintRec != 0)
	{
		printf("Number of records printed: %d\n", numPrintRec);
	}
	else if(debugmode == 1 && numPrintRec == 0)
	{
		printf("No matching records found!\n");
	}	

	return 0;
}


/******************************************************************************
// Function name: modifyRecord
//
// DESCRIPTION:   A function that takes a pointer argument, int, and 
//		  char array. Allows the user to specify an account
//		  to update the address. All records with similar account
//		  numbers will be updated with the new one. If no records
//		  with specified account number are found, then 0 records
//		  will be modified.
//
// Parameters:    theBeginning: start pointer argument.
//		  uaccountno: an integer value for the account number.
//		  uaddress: a char array for the address specified. 
//
// Return values: int (for now 0)
//
*****************************************************************************/

int modifyRecord(struct record * theBeginning, int uaccountno, char uaddress[])
{

        struct record *currRecord;
	int numModRec;

        currRecord = theBeginning;
	numModRec = 0;	

        if(debugmode == 1)
        {
		printf("-----------------------------------\n");
		printf("***modifyRecord function called***\n");
		printf("\n");
                printf("***Account number to be modified***\n");	
                printf("%d\n", uaccountno);
		printf("\n");
                printf("***New address to be added***\n");
                printf("%s\n", uaddress);
		printf("-----------------------------------\n");
	}

        if(theBeginning != NULL)
        {
                while(currRecord != NULL)
                {
                        if(currRecord -> accountno == uaccountno)
                        {
        			strcpy(currRecord -> address, uaddress);
				numModRec++;
                        }
                        currRecord = currRecord -> next;
                }
        }
	
        if(debugmode == 1 && numModRec != 0)
        {
                printf("Number of records printed: %d\n", numModRec);
        }
        else if(debugmode == 1 && numModRec == 0)
        {
                printf("No matching records found!\n");
        }
	
	return 0;
}


/******************************************************************************
// Function name: printAllRecords
//
// DESCRIPTION:   A function that takes a pointer argument. Allows the user
//		  to print all records on file. 
//
// Parameters:    theBeginning: start pointer argument
//
// Return values: n/a because it's void
//
*****************************************************************************/

void printAllRecords(struct record *theBeginning)
{	
	struct record *currRecord;
	int numAllRec;

	currRecord = theBeginning;
	numAllRec = 0;

        if(debugmode == 1)
        {
		printf("-------------------------------------\n");
		printf("***printAllRecords function called***\n");
		printf("-------------------------------------\n");
	}
	
	while(currRecord != NULL)
	{
		printf("%d\n", currRecord -> accountno);
                printf("%s\n", currRecord -> name);
                printf("%s\n", currRecord -> address);
                printf("%d\n", currRecord -> yearofbirth);
		printf("\n");	
		currRecord = currRecord -> next;
		numAllRec++;
	}	
	
	if(debugmode == 1)
	{
		printf("Number of records printed: %d\n", numAllRec);
	}

}


/******************************************************************************
// Function name: deleteRecord
//
// DESCRIPTION:   A function that takes a pointer argument as well as an 
//		  int. Allows for the user to specify what record to delete
//		  from the account number given. If any record has the same
//		  account as the specified one, then they will all get
//		  deleted. If no record is found matching the specified
//		  account number, then no record will be deleted.
//
// Parameters:    start: start pointer pointer argument
//		  uaccountno: an integer value for the account number. 
//
// Return values: int (for now 0)
//
*****************************************************************************/

int deleteRecord(struct record **start, int uaccountno)
{
	int numDelRec;
	struct record *currRecord;
	struct record *prevRecord;
	struct record *tempRecord;

	numDelRec = 0;
	currRecord = *start;	
	prevRecord = NULL;
	
	if(debugmode == 1)
        {
		printf("----------------------------------\n");
		printf("***deleteRecord function called***\n");
		printf("\n");
                printf("***Account number to be deleted***\n");
                printf("%d\n", uaccountno);
		printf("----------------------------------\n");
	}
	
	if(*start != NULL)
	{
		while(currRecord != NULL)
		{
			if(currRecord -> accountno == uaccountno)
			{
				if(currRecord -> next == NULL)
				{
					/*Delete a record from the list with only one*/
					if(prevRecord == NULL)
					{
						*start = NULL;
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						free(tempRecord);
						numDelRec++;
					}
					/*Delete a record thats at the end of the list*/
					else
					{
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						prevRecord -> next = currRecord;
						free(tempRecord);
                                                numDelRec++;
					}
				}
				else
				{
					/*Delete a record surrounded by other records*/
					if(prevRecord != NULL)
					{
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						prevRecord -> next = currRecord;
						free(tempRecord);
                                                numDelRec++;
					}
					/*Delete a record at start from a list with a next record*/
					else
					{
						*start = currRecord -> next;
						tempRecord = currRecord;
						currRecord = currRecord -> next;
						free(tempRecord);
                                                numDelRec++;
					}
				}
			}
			else
			{
				prevRecord = currRecord;
				currRecord = currRecord -> next;
			}
		}
	}
	else
	{
		printf("There are no records left to delete!");
	}

	if(debugmode == 1 && numDelRec != 0)
	{
		printf("Number of records deleted: %d\n", numDelRec);
	}
	else if(debugmode == 1 && numDelRec == 0)
	{
		printf("No matching records found!\n");
	}
		
	return 0;
}

