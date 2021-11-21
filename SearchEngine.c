#include "SearchEngine.h"
#include "checkFunction.h"

int Filtermenu()
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

const char* getfield(char* line, int column)
{
	const char* value;
	for (value = strtok(line, ",");
		value && *value;
		value = strtok(NULL, ",\n"))
	{
		if (!--column)
			return value;
	}
	return NULL;
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

int printall()
{
	int count = 1;
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
				// the function does not exist yet;
				break;
			case '2':
				// the function does not exist yet;
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
				return 0;
			default:
				printf("wrong entry try again\n");
				break;
			}
		}
	}
	printf("there is no more work in the database\n");
}



