/******************************************************************************
// Function name: getAddress
//
// DESCRIPTION:   A function that takes a string array and int as parameters
//		              and is used to query for an address and stores them in
//                  a temp array which is then copied into the pushed array.
//
// Parameters:    param1: a char string array, that holds the entire empty
//			          address container.
//		            size: an integer value for the size of the address array
//
//
// Return values: n/a because it's void
//
*****************************************************************************/

#include "header.h"
extern int debugmode;

void getAddress(char param1[], int size)
{
	char temp[size];
	char temp2[size];
	char container[100];
	int hasAddress = 0;

	if (debugmode == 1)
	{
		printf("\n");
		printf("***getAddress function called***\n");
		printf("\n");
	}


	printf("What is the address you want to add?\n");
	printf("Press ENTER twice when finished.\n");
        memset(temp, 0, size);
        memset(temp2, 0, size);

	while(hasAddress == 0) {
		fgets(temp, size, stdin);
		if(strlen(temp) == 1)
		{
			hasAddress = 1;
		} else
		{
			strcat(temp2, temp);
		}
	}
	fgets(container, 100, stdin);
	strcpy(param1, temp2);
}
