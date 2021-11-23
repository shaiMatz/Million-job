#include "SearchEngine.h"
#include "checkFunction.h"
#include"candidate.h"
#include "employer.h"
int Filtermenu(candidate cand)
{
	//int run = 0;
	char i = ' ';
	while (i != '0')
	{
		printf("Press 1 to sort by location \nPress 2 to sort by job hours \nPress 3 to sort by salary \nPress 4 to sort job type \nPress 5 to go to the previous menu\n ");
		scanf("%c", &i);
		switch (i)
		{
		case '1':
			getchar();
			filtertown();
			break;

		case '2':
			getchar();
			filterjobhours();
			break;

		case '3':
			//filter();
			break;

		case '4':
			//filter();
			break;

		case '5':
			i = '0';
			break;

		default:
			printf("wrong entry try again\n");
			break;
		}
	}
	return 0;
}


int filtertown()
{
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
		printf("can't open file\n");
	char buffer[2024], * temp = NULL;
	int row = 0;
	char name[MAXNAME];
	printf("Enter the name of the city\n");
	gets(name);
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
	return 0;
}


void printJob(char* line)
{
	char* temp = _strdup(line);
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
	temp = _strdup(line);
}

int filterjobhours()
{
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
		printf("can't open file\n");
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
	return 0;
}

int printall(candidate cand)
{
	int count = 1,liked=0;
	FILE* fp = fopen("JOB_LIST_DATA.csv", "r");
	if (!fp)
		printf("can't open file\n");
	char buffer[2024];
	char choice = '1';
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
				pickAJob(cand, buildJob(liked));
				break;
			case '2':
				printf("enter the number you want to add to your favorite list: ");
				scanf("%d", &liked);
				pickAFavJob(cand, buildJob(liked));
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
				return 0;
			default:
				printf("wrong entry try again\n");
				break;
			}
		}
	}
	printf("there is no more jobs in the database\n");
}


int pickAJob(candidate cand,job jobN)
{
	char name[MAXNAME] = "submissionsJOB";
	char CFileName[MAXNAME];
	strcat(name,jobN.serialNum + '0');
	strcat(name, ".csv");
	strcpy(CFileName, cand.Fname);
	strcat(CFileName, cand.ID);
	strcat(CFileName, ".csv");

	FILE* pf = fopen(name, "a+");
	if (!pf)
		printf("can't open file: %s\n", name);

	FILE* candF = fopen(CFileName, "a+");
	if (!candF)
		printf("can't open file: %s\n", CFileName);

	fprintf(pf, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n", cand.ID,
		cand.Fname, cand.Lname, cand.email, cand.password1,
		cand.city, cand.month, cand.day,
		cand.year, cand.phoneNumber, cand.questionChoose, cand.wantedjobs, cand.answer);

	fprintf(candF,"%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", jobN.serialNum, jobN.Jname, jobN.Jcity,
		jobN.Jrange, jobN.Jtype, jobN.Jdescription, jobN.Jresponsibilities, jobN.Jqualifications,
		jobN.Jsalary, jobN.Jhours);

	fclose(pf);
	return 0;
}

int pickAFavJob(candidate cand, job jobN)
{
	char name[MAXNAME] = "FAVORITEJOB";
	strcpy(name, cand.Fname);
	strcat(name, cand.ID);
	strcat(name, ".csv");

	FILE* pf = fopen(name, "a+");
	if (!pf)
		printf("can't open file: %s\n", name);


	fprintf(pf, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", jobN.serialNum, jobN.Jname, jobN.Jcity,
		jobN.Jrange, jobN.Jtype, jobN.Jdescription, jobN.Jresponsibilities, jobN.Jqualifications,
		jobN.Jsalary, jobN.Jhours);

	fclose(pf);
	return 0;
}