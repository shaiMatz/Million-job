#include "SearchEngine.h"
#include "checkFunction.h"
#include"candidate.h"
#include "employer.h"
int Filtermenu(candidate cand)
{
	char i = ' ';
	while (i != '0')
	{
		printf("Press 1 to sort by location \nPress 2 to sort by job hours \nPress 3 to sort by salary \nPress 4 to sort job type \nPress 5 to go to the previous menu\n ");
		scanf("%c", &i);
		getchar();
		switch (i)
		{
		case '1':
			system("cls");
			
			filtertown(cand);
			break;

		case '2':
			system("cls");

			filterjobhours(cand);
			break;

		case '3':
			system("cls");

			filtersalary(cand);
			break;

		case '4':
			system("cls");

			filterjobtype(cand);
			break;

		case '5':
			system("cls");

			i = '0';
			break;

		default:
			system("cls");

			printf("wrong entry try again\n");
			break;
		}
	}
	return 0;
}

int filtertown(candidate cand)
{
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return 1;
	}
	char buffer[2024], * temp = NULL;
	int row = 0;
	char name[MAXNAME];
	printf("Enter the name of the city\n");
	gets(name);
	if (ifExists("JOB_LIST_DATA.csv", name, 4) == 1)
	{
		printf("there is no work in this city\n");
		return 0;
	}
	while (fgets(buffer, 1024, fp))
	{
		row++;
		if (row == 1)
			continue;
		else
		{
			temp = _strdup(buffer);
			if (strcmp(getfield(temp, 4), name) == 0)
				printJob(buffer);
		}
	}
	fclose(fp);
	free(temp);
	if (strcmp(cand.email, "0") != 0)
		choicemenu(cand);
	return 0;
}

void printJob(char* line)
{
	char* temp = _strdup(line);
	if (strcmp(getfield(temp, 1), "SerialNum") != 0)
	{
		printf("\n  JOB NUMBER %s\n", getfield(temp, 1));
		temp = _strdup(line);
		printf("Job name: %s\n", getfield(temp, 2));
		temp = _strdup(line);
		printf("Job range: %s\n", getfield(temp, 3));
		temp = _strdup(line);
		printf("Job city: %s\n", getfield(temp, 4));
		temp = _strdup(line);
		printf("Job type: %s\n", getfield(temp, 5));
		temp = _strdup(line);
		printf("Job description: %s\n", getfield(temp, 6));
		temp = _strdup(line);
		printf("Job responsibilities: %s\n", getfield(temp, 7));
		temp = _strdup(line);
		printf("Job qualifications: %s\n", getfield(temp, 8));
		temp = _strdup(line);
		printf("Job salary: %s\n", getfield(temp, 9));
		temp = _strdup(line);
		printf("Job hours: %s\n\n", getfield(temp, 10));

	}
}
void printCand(char* line)
{
	char* temp = _strdup(line);
	char* temp1;
	char* temp2;
	if (strcmp(getfield(temp, 1), "ID") != 0)
	{
		printf("\n\n  candidate %s\n\n", getfield(temp, 1));
		temp = _strdup(line);
		printf("First name: %s\n", getfield(temp, 2));
		temp = _strdup(line);
		printf("Last name: %s\n", getfield(temp, 3));
		temp = _strdup(line);
		printf("Email: %s\n", getfield(temp, 4));
		temp = _strdup(line);
		printf("City: %s\n", getfield(temp, 6));
		temp = _strdup(line);
		temp1 = _strdup(line);
		temp2 = _strdup(line);
		printf("Birth date: %s/%s/%s \n", getfield(temp1, 8), getfield(temp2, 7), getfield(temp, 9));
		temp = _strdup(line);
		printf("Phone number: %s\n", getfield(temp, 10));
		temp = _strdup(line);
		printf("Job preferences: %s\n\n", getfield(temp, 13));
	}
}

int filterjobhours(candidate cand)
{
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return 1;
	}
	char buffer[2024], * temp = NULL;
	int row = 0;
	char i = '1';
	char name[MAXNAME];
	while (i != '0')
	{
		printf("Press 1 to show morning jobs \nPress 2 to show afternoon jobs \nPress 3 to show evening jobs \nPress 4 to show night jobs \nPress 5 to go to the previous menu\n ");
		scanf("%c", &i);
		getchar();
		switch (i)
		{
		case '1':
			strcpy(name, "morning");
			i = '0';
			break;

		case '2':
			strcpy(name, "afternoon");
			i = '0';
			break;

		case '3':
			strcpy(name, "evening");
			i = '0';
			break;

		case '4':
			strcpy(name, "night");
			i = '0';
			break;

		case '5':
			return 0;

		default:
			printf("wrong entry try again\n");
			break;
		}
	}
	if (ifExists("JOB_LIST_DATA.csv", name, 10) == 1)
	{
		printf("there is no work in this hours\n");
		return 0;
	}
	while (fgets(buffer, 1024, fp))
	{
		row++;
		if (row == 1)
			continue;

		else
		{
			temp = _strdup(buffer);
			if (strcmp(getfield(temp, 10), name) == 0)
				printJob(buffer);
		}
	}
	fclose(fp);
	free(temp);
	if (strcmp(cand.email, "0") != 0)
		choicemenu(cand);
	return 0;
}

int choicemenu(candidate cand)
{
	char choice = ' ', num[MAXNAME];
	int liked;
	while (choice != '0')
	{
		printf("Press 1 to pick a job \nPress 2 to save a work to your favourites \nPress 3 to go back to previous menu\n");
		scanf("%c", &choice);
		getchar();
		switch (choice)
		{
		case '1':
			printf("enter the number you liked: ");
			scanf("%d", &liked);
			getchar();
			sprintf(num, "%d", liked);
			if (ifExists("JOB_LIST_DATA.csv", num, 1) == 0)
			{
				pickAJob(cand, buildJob(liked));
				choice = '0';
			}
			else
			{
				printf("the job does not exist in the database\n");
				choice = '0';
			}
			
			break;
		case '2':
			printf("enter the number you want to add to your favorite list: ");
			scanf("%d", &liked);
			getchar();
			sprintf(num, "%d", liked);
			if (ifExists("JOB_LIST_DATA.csv", num, 1) == 0)
			{
				pickAFavJob(cand, buildJob(liked));
				choice = '0';
			}
			else
			{
				printf("the job does not exist in the database\n");
				choice = '0';
			}
			
			break;
		case '3':
			choice = '0';
			return 0;
		default:
			printf("wrong entry try again\n");
			break;
		}
	}
	return 0;
}

int printall(candidate cand)
{
	int count = 1, liked = 0;
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return 1;
	}
	char buffer[2024];
	char choice = '1', num[MAXNAME];
	int row = 2;
	int run = 1;
	fgets(buffer, 1024, fp);
	while (run != 0)
	{
		choice = '1';
		while (count <= 10 && fgets(buffer, 1024, fp))
		{

			if (row == 1)
				continue;
			else
			{
				printJob(buffer);
			}
			count++;
			row++;

		}
		if (strcmp(cand.email, "0") != 0)
			while (choice != '0')
			{
				printf("Press 1 to pick a job \nPress 2 to save a work to your favourites \nPress 3 to continue searching for a work \nPress 4 to go back to previous menu\n");
				scanf("%c", &choice);
				getchar();
				switch (choice)
				{
				case '1':
					printf("enter the number you liked: ");
					scanf("%d", &liked);
					getchar();
					sprintf(num, "%d", liked);
					if (ifExists("JOB_LIST_DATA.csv", num, 1) == 0)
					{
						pickAJob(cand, buildJob(liked));
						choice = '0';
					}
					else
					{
						printf("the job does not exist in the database\n");
						choice = '0';
					}
					break;
				case '2':
					printf("enter the number you want to add to your favorite list: ");
					scanf("%d", &liked);
					getchar();
					sprintf(num, "%d", liked);
					if (ifExists("JOB_LIST_DATA.csv", num, 1) == 0)
					{
						pickAFavJob(cand, buildJob(liked));
						choice = '0';
					}
					else
					{
						printf("the job does not exist in the database\n");
						choice = '0';
					}
					break;
				case '3':
					if (count >= 10)
					{
						count = 0;
						choice = '0';
					}
					else
					{
						run = 0;
						choice = '0';
					}
					break;
				case '4':
					choice = '0';
					run = 0;
					fclose(fp);
					return 0;
				default:
					printf("wrong entry try again\n");
					break;
				}
			}
		else
		{
			while (choice != '0')
			{
				printf("Press 1 to continue searching for a work \nPress 2 to go back to previous menu\n");
				scanf("%c", &choice);
				getchar();
				switch (choice)
				{
				case '1':
					if (count >= 10)
					{
						count = 0;
						choice = '0';
					}
					else
					{
						run = 0;
						choice = '0';
					}
					break;
				case '2':
					choice = '0';
					run = 0;
					fclose(fp);
					return 0;
				default:
					printf("wrong entry try again\n");
					break;
				}
			}
		}
	}
	printf("there is no more jobs in the database\n");
	fclose(fp);
	return 0;
}

int pickAJob(candidate cand, job jobN)
{
	char name[MAXNAME] = "submissionsJOB";
	char CFileName[MAXNAME];
	char num[MAXNAME];
	sprintf(num, "%d", jobN.serialNum);
	strcat(name, num);
	strcat(name, ".csv");
	strcpy(CFileName, cand.Fname);
	strcat(CFileName, cand.ID);
	strcat(CFileName, ".csv");

	FILE* pf = fopen(name, "a+");
	if (!pf)
	{
		printf("can't open file: %s\n", name);
		return 1;
	}
	FILE* candF = fopen(CFileName, "a+");
	if (!candF)
	{
		printf("can't open file: %s\n", CFileName);
		return 1;
	}
	if (ifExists(CFileName, num, 1) != 0)
	{
		fprintf(candF, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", jobN.serialNum, jobN.Jname, jobN.Jcity,
			jobN.Jrange, jobN.Jtype, jobN.Jdescription, jobN.Jresponsibilities, jobN.Jqualifications,
			jobN.Jsalary, jobN.Jhours);
		fprintf(pf, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n", cand.ID,
			cand.Fname, cand.Lname, cand.email, cand.password1,
			cand.city, cand.month, cand.day,
			cand.year, cand.phoneNumber, cand.questionChoose, cand.answer, cand.wantedjobs);
	}
	else
		printf("The job already exists in your list!\n");


	fclose(pf);
	fclose(candF);
	return 0;
}

int pickAFavJob(candidate cand, job jobN)
{
	char name[MAXNAME] = "FAVORITEJOB";
	strcat(name, cand.Fname);
	strcat(name, cand.ID);
	strcat(name, ".csv");

	char num[MAXNAME];
	sprintf(num, "%d", jobN.serialNum);

	FILE* pf = fopen(name, "a+");
	if (!pf)
	{
		printf("can't open file: %s\n", name);
		return 1;
	}
	if (ifExists(name, num, 1) != 0)
	{
		fprintf(pf, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", jobN.serialNum, jobN.Jname, jobN.Jcity,
			jobN.Jrange, jobN.Jtype, jobN.Jdescription, jobN.Jresponsibilities, jobN.Jqualifications,
			jobN.Jsalary, jobN.Jhours);
	}
	else
		printf("The job already exists in your list!\n");
	fclose(pf);
	return 0;
}

int filtersalary(candidate cand)
{
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return 1;
	}
	char buffer[2024], * temp = NULL;
	int row = 0;
	char i = '1';
	char name[MAXNAME];
	while (i != '0')
	{
		printf("Press 1 to show salary between 30-40/h \nPress 2 to show salary between 40-50/h  \nPress 3 to show salary between 50-60/h  \nPress 4 to show salary between 60-70/h  \nPress 5 to show salary +70/h \nPress 6 to go to the previous menu\n ");
		scanf("%c", &i);
		getchar();
		switch (i)
		{
		case '1':
			strcpy(name, "30-40/h");
			i = '0';
			break;

		case '2':
			strcpy(name, "40-50/h");
			i = '0';
			break;

		case '3':
			strcpy(name, "50-60/h");
			i = '0';
			break;

		case '4':
			strcpy(name, "60-70/h");
			i = '0';
			break;

		case '5':
			strcpy(name, "70+/h");
			i = '0';
			break;
		case '6':
			return 0;
		default:
			printf("wrong entry try again\n");
			break;
		}
	}
	if (ifExists("JOB_LIST_DATA.csv", name, 9) == 1)
	{
		printf("there is no work for this salary\n");
		return 0;
	}

	while (fgets(buffer, 1024, fp))
	{
		row++;
		if (row == 1)
			continue;

		else
		{
			temp = _strdup(buffer);
			if (strcmp(getfield(temp, 9), name) == 0)
				printJob(buffer);
		}
	}
	fclose(fp);
	free(temp);
	if (strcmp(cand.email, "0") != 0)
		choicemenu(cand);
	return 0;
}

int filterjobtype(candidate cand)
{
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return 1;
	}
	char buffer[2024], * temp = NULL;
	int row = 0;
	char i = '1';
	char name[MAXNAME];
	while (i != '0')
	{
		printf("Press 1 to show part time \nPress 2 to show full time \nPress 3 to go to the previous menu \n");
		scanf("%c", &i);
		getchar();
		switch (i)
		{
		case '1':
			strcpy(name, "part time");
			i = '0';
			break;

		case '2':
			strcpy(name, "full time");
			i = '0';
			break;

		case '3':
			return 0;

		default:
			printf("wrong entry try again\n");
			break;
		}
	}
	if (ifExists("JOB_LIST_DATA.csv", name, 5) == 1)
	{
		printf("there is no work of this type\n");
		return 0;
	}
	while (fgets(buffer, 1024, fp))
	{
		row++;
		if (row == 1)
			continue;

		else
		{
			temp = _strdup(buffer);
			if (strcmp(getfield(temp, 5), name) == 0)
				printJob(buffer);
		}
	}
	fclose(fp);
	free(temp);
	if (strcmp(cand.email, "0") != 0)
		choicemenu(cand);
	return 0;
}

int printoldertonew(candidate cand)
{
	sortFile("JOB_LIST_DATA.csv", 1);
	printall(cand);
	return 0;
}

int printnewtoolder(candidate cand)
{
	sortFilefromendtostart("JOB_LIST_DATA.csv", 1);
	printall(cand);
	return 0;
}

int filtertownEmp()
{
	FILE* fp = fopen("Candidate_DATA.csv", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return 1;
	}
	char buffer[2024], * temp = NULL;
	int row = 0;
	char name[MAXNAME];
	printf("Enter the name of the city\n");
	gets(name);
	if (ifExists("Candidate_DATA.csv", name, 6) == 1)
	{
		printf("there is no candidates in this city\n");
		return 0;
	}
	while (fgets(buffer, 1024, fp))
	{
		row++;
		if (row == 1)
			continue;
		else
		{
			temp = _strdup(buffer);
			if (strcmp(getfield(temp, 6), name) == 0)
				printCand(buffer);
		}
	}
	fclose(fp);
	free(temp);

	return 0;
}

int filterjobGenreEmp()
{
	FILE* fp = fopen("Candidate_DATA.csv", "r");
	if (!fp)
	{
		printf("can't open file\n");
		return 1;
	}
	char buffer[2024], * temp = NULL;
	int row = 0;
	char name[MAXNAME];
	printf("Enter the job type\n");
	gets(name);
	if (ifExists("Candidate_DATA.csv", name, 13) == 1)
	{
		printf("there is no candidates for this genre\n");
		return 0;
	}
	while (fgets(buffer, 1024, fp))
	{
		row++;
		if (row == 1)
			continue;
		else
		{
			temp = _strdup(buffer);
			if (strcmp(getfield(temp, 13), name) == 0)
				printCand(buffer);
		}
	}
	fclose(fp);
	free(temp);
	return 0;
}

int empSearchEngine()
{
	char i = ' ';
	while (i != '0')
	{
		printf("Press 1 to sort by location \nPress 2 to sort by job genre \nPress 3 to go to the previous menu\n ");
		scanf("%c", &i);
		getchar();
		switch (i)
		{
		case '1':
			filtertownEmp();
			break;

		case '2':
			filterjobGenreEmp();
			break;

		case '3':
			i = '0';
			break;

		default:
			printf("wrong entry try again\n");
			break;
		}
	}
	return 0;
}
