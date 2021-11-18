#include"menu.h"
#include"checkFunction.h"
#include "employer.h"
#include "candidate.h"
void menu()
{
	int run = 0;
	char choice = '0'; 
	char choice1 = '0';
	employer newEmp;
	candidate newCand;
	printf(" ~~~~~ Hello Dear User!~~~~~ \n");
	printf("Welcome to Million Job Program \n");
	printf(" dont miss your apportunity! \n\n");

	while (run != -1)
	{
		
		printf("option :\n1) For login Press 1\n2) For Register press 2\n3) For lost password press 3\n4) For exit press 4\n\nchoice : \b");
		scanf("%c", &choice);

		switch (choice)
		{
		case '1':
		{
			//login();
			break;
		}
		case '2':
		{
			system("cls");
			getchar();
			printf("option :\n1) For employer Press 1\n2) For candidate press 2\n3) For returning to previous menu press 3\n\nchoice : \b");
			scanf("%c", &choice1);
			switch (choice1)			//employer or candidate ?
			{
			case'1':
				getchar();
				newEmp = employer_Registration();
				getchar();

				break;
			case '2':
				getchar();
				newCand = Candidate_Registration();
				getchar();
				CandidateMenu(newCand);
				getchar();
				break;
			default:
				break;
			}

			break;
		}
		case '3':
		{
			//lostPassword();
			getchar();
			break;
		}
		case '4':
		{
			run = -1;
			system("cls");
			printf("Good-bye!\n\n");
			getchar();
			break;
		}
		default:
		{
			
			printf("Error! you put wrong number please try again (1-4)\n");

		}
		}
	}

}

