/******************************************************************************
//
// NAME:          Blake Larson
//
// HOMEWORK:      Project1
//
// CLASS:         ICS 212
//
// INSTRUCTOR:    Ravi Narayan
//
// DATE:          October 18, 2016
//
// FILE:          main.c
//
// DESCRIPTION:   This is the main function that uses a user-interface
//            	  for a bank database application. All functions are
//		  in seperate files, but this is strictly menu based.
//
*****************************************************************************/

#include "header.h"

int debugmode = 0;

int main(int argc, char* argv[])
{
	struct record * start = NULL;
	char container[100]; 
	int option = 0;
	int accnum = 0;
	int numCheck = 0;
	char accname[100] = "\0";
	char address[100] = "\0";
	int birthyear = 0;	

	// Check if more than 2 arguments.
        if (argc > 2)
        {
                printf("project1 Insufficient arguments (>2)\n");
                printf("Usage: project1      \n");
                printf("       project1 debug\n");
                exit(1);

        }
	
	// Check if argument two is debug, if not then error.
	if((argc == 2) && ((strcmp(argv[1], "debug") == 0)))
	{
		debugmode = 1;

	} else if (argc == 2)
	{
                printf("project1 Insufficient arguments(argv[1] != debug)\n");
		printf("Usage: project1      \n");
		printf("       project1 debug\n");
                exit(1);	
	}
	
	printf("------------------------------------------\n");
        printf("-Welcome to the Bank Database Application-\n");
        printf("------------------------------------------\n");

	readfile(&start, "output.txt");

	if(debugmode == 1)
	{
		printf("******************************************\n");
		printf("***************DEBUG MODE*****************\n");
		printf("******************************************\n");	
        	printf("\n");	
	}

	while (option == 0) {
                printf("------------------------------------------\n");
		printf("------------------MENU--------------------\n");
                printf("------------------------------------------\n");
		printf("1)\tAdd a new record\n");
		printf("2)\tModify a record\n");
		printf("3)\tPrint a record\n");
		printf("4)\tPrint all the records\n");
		printf("5)\tDelete a record\n");
		printf("6)\tQuit Program\n");
		printf("------------------------------------------\n");
		printf("\n");
		
		printf("Please enter an option\n");
		scanf("%i", &option);

		switch (option)
		{

			case 1 :
	               		printf("------------Option 1 selected-------------\n");
				while(numCheck == 0)
				{
					printf("What is the account number you want to add?\n");
					if(scanf("%d", &accnum) != 1)
					{
                                                fgets(container, 100, stdin);						
                                                printf("***Please enter an integer***\n");						
					} else
					{
						if(accnum <= 0)
						{
							printf("***Only positive values can be used***\n");
						} else
						{
							numCheck=1;
						}
					}
				}
				
				numCheck = 0;
				fgets(container, 100, stdin);

				printf("What is the full name you want to add?\n");
				fgets(accname, 100, stdin);
				if(accname[strlen(accname)-1] == '\n')
				{
					accname[strlen(accname)-1] = '\0';
				}

				getAddress(address, 100);
				if(address[strlen(address)-1] == '\n')
				{
					address[strlen(address)-1] = '\0';
				}				
				
                                while(numCheck == 0)
                                {
                                        printf("What is the birth year you want to add?\n");
					printf("Please format: YYYY\n");
                                        if(scanf("%i", &birthyear) != 1)
                                        {
                                                fgets(container, 100, stdin);
                                                printf("***Please enter an integer***\n");                                
                                        } else
                                        {
                                                if(birthyear <= 999 || birthyear > 9999)
                                                {
                                                        printf("***Birth years can only be 4 digits***\n");
                                                } else 
						{	
                                                        numCheck = 1;
                                                }
                                        }
                                }
				
				numCheck = 0;	
				fgets(container, 100, stdin);

				addRecord(&start, accnum, accname, address, birthyear);
				printf("Press ENTER to continue\n");
				break;
			
			case 2 :
                                printf("------------Option 2 selected-------------\n");
                                while(numCheck == 0)
                                {
                                        printf("What is the account number you want to modify?\n");
                                        if(scanf("%d", &accnum) != 1)
                                        {
                                                fgets(container, 100, stdin);
                                                printf("***Please enter an integer***\n");                                
                                        } else
                                        {
                                                if(accnum <= 0)
                                                {
                                                        printf("***Only positive values can be used***\n");
                                                } else
                                                {
                                                        numCheck=1;
                                                }
                                        }
                                }
				numCheck = 0;
				fgets(container, 100, stdin);				

				getAddress(address, 100);
                                if(address[strlen(address)-1] == '\n')
                                {
                                        address[strlen(address)-1] = '\0';
                                }
				
				modifyRecord(start, accnum, address);
                                printf("Press ENTER to continue\n");
                                break;
			case 3 :
                                printf("------------Option 3 selected-------------\n");
                                while(numCheck == 0)
                                {
                                        printf("What is the account number you want to print?\n");
                                        if(scanf("%d", &accnum) != 1)
                                        {
                                                fgets(container, 100, stdin);
                                                printf("***Please enter an integer***\n");                                
                                        } else
                                        {
                                                if(accnum <= 0)
                                                {
                                                        printf("***Only positive values can be used***\n");
                                                } else
                                                {
                                                        numCheck=1;
                                                }
                                        }
                                }
                                numCheck = 0;
				printRecord(start, accnum);
				break;
			case 4 :
                                printf("------------Option 4 selected-------------\n");
				printAllRecords(start);
                                break;
			case 5 :
                                printf("------------Option 5 selected-------------\n");
                                while(numCheck == 0)
                                {
                                        printf("What is the account number you want to delete?\n");
                                        if(scanf("%d", &accnum) != 1)
                                        {
                                                fgets(container, 100, stdin);
                                                printf("***Please enter an integer***\n");                                
                                        } else
                                        {
                                                if(accnum <= 0)
                                                {
                                                        printf("***Only positive values can be used***\n");
                                                } else
                                                {
                                                        numCheck=1;
                                                }
                                        }
                                }
				numCheck = 0;
				deleteRecord(&start, accnum);
                                break;
			case 6 :
                                printf("------------Option 6 selected-------------\n");
                                printf("----Exitting Bank Database Application----\n");
				writefile(start, "output.txt"); 
				exit(1);
			default :
				printf("*******Please enter a valid option!*******\n");
				option = 0;
		}
		option = 0;
                fgets(container, 100, stdin);
	}
	return 0;
}

