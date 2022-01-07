#include"menu.h"
#include"checkFunction.h"
#include "employer.h"
#include "candidate.h"

void menu()
{
	int run = 0;
	char choice = '0';
	char choice1 = '0';
	char email[MAXNAME];
	employer newEmp;
	candidate newCand;
	int num = 0;
	char temp[MAXNAME];
	while (run != -1)
	{
		printf(" ~~~~~ Hello Dear User !~~~~~ \n");
		printf("Welcome to Million Job Program \n");
		printf(" dont miss your apportunity ! \n\n");
		printf("option : \n1) For login Press 1\n2) For Register press 2\n3) For lost password press 3\n4) For exit press 4\n\nchoice :  \b");
		scanf("%c", &choice);
		if (clearBuffer() > 1)
			choice = 'd';
		switch (choice)
		{
		case '1':
		{
			system("cls");
			strcpy(email, login(&num));
			if (strcmp(email, "\0") == 0)
			{
				system("cls");
				printf("the email don't exists in the database, you need to sign up\n");
				getchar();

				break;
			}
			else if (num == 1)
			{
				system("cls");
				newCand = loginC(email);
				getchar();
				CandidateMenu(newCand);
				break;
			}

			else if (num == 2)
			{
				system("cls");
				newEmp = loginE(email);
				getchar();
				EmployerMenu(newEmp);
				break;
			}
			break;
		}
		case '2':
		{
			system("cls");
			printf("option : \n1) For employer Press 1\n2) For candidate press 2\n3) For returning to previous menu press 3\n\nchoice :  \b");
			scanf("%c", &choice1);
			if (clearBuffer() > 1)
				choice = 'd';
			switch (choice1)			//employer or candidate ?
			{
			case '1':
				system("cls");
				newEmp = employer_Registration();
				system("cls");
				getchar();
				EmployerMenu(newEmp);
				getchar();
				break;

			case '2':
				system("cls");
				newCand = Candidate_Registration();
				system("cls");
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
			system("cls");
			if (forgetMyPass(&num) != NULL)
				strcpy(temp, forgetMyPass);

			if (num == 1)
			{
				system("cls");
				newCand = loginC(temp);
				CandidateMenu(newCand);
				system("cls");
			}

			else if (num == 2)
			{
				system("cls");
				newEmp = loginE(temp);
				EmployerMenu(newEmp);
				system("cls");
			}
			break;
		}
		case '4':
		{
			run = -1;
			system("cls");
			printf("Good-bye !\n\n");

			break;
		}
		default:
		{
			system("cls");
			printf("Error ! You put wrong number please try again (1-4) : \n");

		}
		}
	}

}

char* login(int* num)
{
	char email[MAXNAME], password[MAXNAME];
	candidate cand;
	employer emp;
	int row;
	printf("please enter your email and password\n");
	printf("Email : ");
	scanf("%s", &email);
	printf("Password : ");
	scanf("%s", &password);
	row = findRightRow("Candidate_DATA.csv", email);

	if ((row != 1) && (row == findRightRowPass("Candidate_DATA.csv", password)))
	{
		*num = 1;
		return email;
	}
	else
	{
		row = findRightRow("Employer_DATA.csv", email);
		if ((row != 1) && (row == findRightRowPass("Employer_DATA.csv", password)))
		{
			*num = 2;
			return email;
		}
	}
	if (row == 1)
		printf("the user doesn't exists in the databases\n");
	*num = -1;
	return "\0";

}

char* forgetMyPass(int* num)
{
	char email[MAXNAME];
	candidate cand;
	employer emp;

	printf("Hello, please enter your email address :\nEmail : ");
	scanf("%s", &email);
	getchar();
	if (findRightRow("Candidate_DATA.csv", email) != 1)
	{
		*num = 1;
		cand = loginC(email);
		cand = resetPassword(cand);
		return cand.email;
	}
	if (findRightRow("Employer_DATA.csv", email) != 1)
	{
		*num = 2;
		emp = loginE(email);
		emp = resetPassword2(emp);
		return emp.email;
	}
	else
		printf("the user doesn't exists in the databases !\n");
	return NULL;
}
