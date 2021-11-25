
#pragma once

#include"employer.h"
#include"SearchEngine.h"

employer loginE(char email[])
{
	char* value, buffer[2024];
	int column = 0, row = 0, wantedRow = 1;
	employer newEmp;
	FILE* fp = fopen("Employer_DATA.csv", "r");
	if (!fp)
		printf("Can't open file\n");

	else
	{

		wantedRow = findRightRow("Employer_DATA.csv", email);
		if (wantedRow == 0)
		{
			printf("The email not found!");
			fclose(fp);
			return;
		}
		row = 0;
		rewind(fp);

		while (fgets(buffer, 1024, fp))
		{
			row++;
			column = 0;
			if (row == wantedRow)
			{
				value = strtok(buffer, ", ");
				while (value)
				{
					if (column == 0)
						strcpy(newEmp.companyName, value);
					if (column == 1)
						strcpy(newEmp.Fname, value);
					if (column == 2)
						strcpy(newEmp.Lname, value);
					if (column == 3)
						strcpy(newEmp.email, value);
					if (column == 4)
						strcpy(newEmp.password1, value);
					if (column == 5)
						strcpy(newEmp.city, value);
					if (column == 6)
						strcpy(newEmp.jobDescription, value);
					if (column == 7)
						strcpy(newEmp.phoneNumber, value);
					if (column == 8)
						newEmp.questionChoose = atoi(value);
					if (column == 9)
						strcpy(newEmp.answer, value);
					value = strtok(NULL, ", ");
					column++;
				}
			}
			else
				continue;
		}
	}
	fclose(fp);
	return newEmp;
}

employer employer_Registration()
{
	FILE* EmployerF = fopen("Employer_DATA.csv", "a+");
	employer newEmployer;


	if (!EmployerF)
	{
		// Error in file opening
		printf("Can't open file\n");
		return;
	}

	// Asking user input for the
	// new record to be added
	printf("\nEnter company name:  \b");
	gets(newEmployer.companyName);

	printf("\nEnter first name:  \b");
	scanf("%s", &newEmployer.Fname);
	printf("\nEnter last name:  \b");
	scanf("%s", &newEmployer.Lname);
	printf("\nEnter email address: (It will be your username)  \b");
	scanf("%s", &newEmployer.email);
	while (MailCheck(newEmployer.email) == 0)
	{
		printf("\nEnter email address: (It will be your username)  \b");
		scanf("%s", &newEmployer.email);
	}
	printf("\nEnter password:  \b");
	scanf("%s", &newEmployer.password1);
	while (PasswordCheck(newEmployer.password1) == 0)
	{
		printf("\nEnter password:  \b");
		scanf("%s", &newEmployer.password1);
	}
	printf("\nEnter your password again:  \b");
	scanf("%s", &newEmployer.password2);
	while (strcmp(newEmployer.password1, newEmployer.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
		scanf("%s", &newEmployer.password2);
	}
	getchar();
	printf("\nEnter your city name: (enter just in small letters) \b");
	gets(newEmployer.city);
	while (CheckLower(newEmployer.city) == 0)
	{
		gets(newEmployer.city);
	}
	printf("\nEnter phone number:  \b");
	scanf("%s", &newEmployer.phoneNumber);
	while (PhoneCheck(newEmployer.phoneNumber) == 0)
	{
		printf("\nEnter phone number:  \b");
		scanf("%s", &newEmployer.phoneNumber);
	}
	getchar();
	printf("\nEnter some information about the company:  \n");
	gets(newEmployer.jobDescription);

	printf("\nChoose your security question:(default qeustion is 1)\n");
	printf("press 1: What is your grandfather name from your father side? \n");
	printf("press 2: What is your pet name? \n");
	printf("press 3: What is the name of your high-school? \nyour choise:  \b");

	scanf("%d", &newEmployer.questionChoose);
	getchar();
	printf("\nEnter your answer:  \b");
	gets(newEmployer.answer);

	// Saving data in file
	fprintf(EmployerF, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", newEmployer.companyName,
		newEmployer.Fname, newEmployer.Lname, newEmployer.email, newEmployer.password1, newEmployer.jobDescription,
		newEmployer.city, newEmployer.phoneNumber, newEmployer.questionChoose, newEmployer.answer);
	fclose(EmployerF);
	system("cls");
	printf("\nNew Account added to record!\n");
	return newEmployer;

}

int EmployerMenu(employer emp)
{
	int run = 0;
	char choice = '0';
	while (run != -1)
	{
		printf("----Wellcome dear %s---- \n", emp.Fname);
		printf("Employer Menu :\n");
		printf("Press 1 to Search engine.\n");// signed as a same candidate search engine in the requirments...
		printf("Press 2 to Add,Edit,Delete jobs.\n");
		printf("Press 3 to List of my jobs offers.\n");
		printf("Press 4 to Edit profile.\n");
		printf("Press 5 to delete profile.\n");
		printf("Press 6 to Candidate Search.\n");
		printf("Press 7 to exit.\n\nchoice : ");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1': {
			//empSearchEngine();
			break;
		}
		case '2':
		{
			getchar();
			jobEdit(emp.email);// inside function switch cases between 3 cases (edit,add,delete)
			getchar();
			break;
		}
		case '3':
		{
			//jobsOfferList();//printing list of jobs and details,viewing optional candidates for specific jobs , and option to delete the job
			break;
		}
		case '4':
		{
			//empProfilEdit();// not the same  profile for the employer...
		}
		case '5': {
			//deleteProfile();
		}
		case '6':
		{
			run = -1;
			//candidateSearch();// candidate searching by age/type/working area
		}
		case '7':
		{
			//logoutFunc();// Logout Function
		}

		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-7 \n");
		}
		}
	}
	return main();
}
employer resetPassword2(employer e)
{
	char securityAnswer[MAXNAME];
	int run = 0;
	int run2 = 0;
	char temp[MAXNAME];
	strcpy(temp, e.password1);
	while (run == 0)
	{
		printf("\nTo reset you're password, enter you're security answer : ");
		scanf("%s", &securityAnswer);
		if (strcmp(e.answer, securityAnswer) == 0)
		{
			while (run2 == 0)
			{
				printf("Enter you're new password twice :\nFirst time : ");
				scanf("%s", &e.password1);
				while (PasswordCheck(e.password1) == 0)
				{
					printf("Enter valid password : ");
					scanf("%s", &e.password1);
				}
				if (strcmp(temp, e.password1) != 0)
				{
					printf("Second Time : ");
					scanf("%s", &e.password2);
					if (strcmp(e.password1, e.password2) != 0)
					{
						printf("Passwords are different, try again : ");
					}
					else
					{
						printf("Done !\n");
						run2 = 1;
						return e;
					}
				}
				if (strcmp(temp, e.password1) == 0)
					printf("the new password can be same as the old one, try again !\n");
			}
		}
		else
		{
			printf("You're security answer doesn't match, try again !\n");
		}
	}

}

int jobEdit(char* email)// inside function switch cases between 3 cases (edit,add,delete)
{
	int run = 0;
	char choice = '0';

	while (run != -1)
	{
		printf("1) Press 1 to add a job.\n");
		printf("2) Press 2 to Edit a job.\n");
		printf("3) Press 3 to delete a job.\n");
		printf("4) Press 4 to exit.\n\nchoice : ");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
		{
			getchar();
			jobAdd(email);
			getchar();
			break;
		}
		case '2':
		{
			getchar();
			editJobFromList(email);
			getchar();
			break;
		}
		case '3':
		{
			break;
		}
		case '4':
		{
			system("cls");
			run = -1;
			getchar();
			break;
		}
		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-4 \n");
		}
		}

	}

}

int jobAdd(char* email)
{
	int serialNum;
	char* value, buffer[2024];
	int column = 0, row = 0, wantedRow = 0;
	FILE* JoblistdataF = fopen("JOB_LIST_DATA.csv", "r");
	if (JoblistdataF == NULL)
	{
		printf("Can't open file!");
		return;
	}


	while (fgets(buffer, 1024, JoblistdataF))//run to the end.
	{
		if (strcmp("\n", buffer) == 0)
			break;
		column = 1;
		row++;
		wantedRow++;
		if (row == 1)//skip the first row, its titles
			continue;
		else {
			value = strtok(buffer, ", ");
			while (column != 1)//1 is the serial column
			{
				value = strtok(NULL, ", ");
				column++;
			}
			if (column == 1)
			{
				serialNum = atoi(value);// save the last serial number.

			}
			else//continue to the next row
			{
				column = 0;
				continue;
			}

		}

	}
	serialNum++;
	fclose(JoblistdataF);



	char* Jname[MAXNAME], Jrange[MAXNAME], Jcity[MAXNAME], Jtype[MAXNAME], Jdescription[MAXNAME], Jresponsibilities[MAXNAME], Jqualifications[MAXNAME], Jsalary[MAXNAME], Jhours[MAXNAME];

	FILE* Jobdata = fopen("JOB_LIST_DATA.csv", "a+");


	if (!Jobdata) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}

	printf("\nEnter the job name: \b");
	gets(Jname);
	printf("\nEnter the job range: \b");
	gets(Jrange);
	printf("\nEnter the city: \b");
	gets(Jcity);
	while (CheckLower(Jcity) == 0)
	{
		gets(Jcity);
	}
	printf("\nJob type:\n");
	int run = 0;
	char choice = '0';
	while (run != -1)
	{
		printf("Press 1 for full time.\n");
		printf("Press 2 for part time.\n");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
		{
			strcpy(Jtype, "full time");
			run = -1;
			break;
		}
		case '2':
		{
			strcpy(Jtype, "part time");
			run = -1;
			break;
		}
		
		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-2 \n");
		}
		}
	}
	

	getchar();
	printf("\nEnter the job description: \n");
	gets(Jdescription);

	printf("\nEnter the job responsibilities: \n");
	gets(Jresponsibilities);

	printf("\nEnter the job qualifications: \n");
	gets(Jqualifications);

	printf("\nJob salary: \n");
	run = 0;
	choice = '0';
	while (run != -1)
	{
		printf("Press 1 for 30-40 nis/h.\n");//30-40/h
		printf("Press 2 for 40-50 nis/h.\n");
		printf("Press 3 for 50-60 nis/h\n");
		printf("Press 4 for 60-70 nis/h\n");
		printf("Press 5 for +70 nis/h\n");//+70/h
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
		{
			strcpy(Jsalary, "30-40/h");
			run = -1;
			break;
		}
		case '2':
		{
			strcpy(Jsalary, "40-50/h");
			run = -1;
			break;
		}
		case '3':
		{
			strcpy(Jsalary, "50-60/h");
			run = -1;
			break;

		}
		case '4':
		{
			strcpy(Jsalary, "60-70/h");
			run = -1;
			break;
		}
		case '5':
		{
			strcpy(Jsalary, "+70/h");
			run = -1;
			break;
		}


		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-5 \n");
		}
		}
	}

	getchar();
	printf("\nJob hours: \n");
	run = 0;
	choice = '0';
	while (run != -1)
	{
		printf("Press 1 for morning.\n");//30-40/h
		printf("Press 2 for afternoon.\n");
		printf("Press 3 for evening\n");
		printf("Press 4 for night\n");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
		{
			strcpy(Jhours, "morning");
			run = -1;
			break;
		}
		case '2':
		{
			strcpy(Jhours, "afternoon");
			run = -1;
			break;
		}
		case '3':
		{
			strcpy(Jhours, "evening");
			run = -1;
			break;


		}
		case '4':
		{
			strcpy(Jhours, "night");
			run = -1;
			break;
		}
		
		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-4 \n");
		}
		}
	}

	// Saving data in file

	fprintf(Jobdata, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", serialNum, Jname, Jcity,
		Jrange, Jtype, Jdescription, Jresponsibilities, Jqualifications,
		Jsalary, Jhours, email);
	fclose(Jobdata);
	system("cls");
	printf("\nNew job added to record\n");
	return 0;


}

int editJobFromList(char* email)
{
	char* value, buffer[2024];

	int column = 0, row = 0, wantedRow = 0;

	int jobCounter = 0;
	int jobNumber;
	char c2[1000];
	char* pch;

	FILE* JoblistdataF = fopen("JOB_LIST_DATA.csv", "r");
	if (JoblistdataF == NULL)
	{
		printf("Can't open file!");
		return;
	}

	else
	{
		while (fgets(buffer, 1024, JoblistdataF))//run to the end.
		{
			if (strcmp("\n", buffer) == 0)
				break;
			column = 0;
			row++;
			if (row == 1)//skip the first row, its titles
				continue;
			else {
				strcpy(c2, _strrev(buffer));
				pch = strtok(c2, " ,");
				strcpy(c2, _strrev(pch));
				pch = strtok(c2, "\n");// pch holds the email.
				if (strcmp(pch, email) == 0)
				{
					jobCounter++;

					_strrev(buffer);
					printJob(buffer);

					continue;
				}
				else
				{
					continue;
				}
			}
		}
	}
	fclose(JoblistdataF);

	if (jobCounter == 0)
	{
		printf("You don't have any published jobs!\n");
		return 0;
	}

	printf("\nEnter the job number you want to edit: ");
	scanf("%d", &jobNumber);
	getchar();
	job joBs;
	joBs=buildJob(jobNumber);

	
	
	
	int check = 0;
	check = deleteJobLine("JOB_LIST_DATA.csv", jobNumber);
	FILE* fp = fopen("JOB_LIST_DATA.csv", "a+");
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}
	char choice = '0';
	int run = 0;
	
	while (run != -1)
	{
		printf("\nPress 1 to Change the name of the job.\n");
		printf("Press 2 to Change the job description.\n");
		printf("Press 3 to Change job main responsibilities.\n");
		printf("Press 4 to Change job qualifications.\n");
		printf("Press 5 to Change job salary.\n");
		printf("Press 6 to Change job hours.\n");
		printf("Press 7 to exit.");
		printf("choice: ");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
		{
			getchar();
			printf("Enter new name of the job: \b");
			gets(joBs.Jname);
			getchar();


			break;
		}
		case '2':
		{
			getchar();
			printf("Enter new job description: \b");
			gets(joBs.Jdescription);
			getchar();
			break;
		}
		case '3':
		{
			getchar();
			printf("Enter new job main responsibilities: \b");
			gets(joBs.Jresponsibilities);
			getchar();
			break;
		}
		case '4':
		{
			getchar();
			printf("Enter new job qualifications: \b");
			gets(joBs.Jqualifications);
			getchar();
			break;
		}
		case '5':
		{
			getchar();
			printf("Enter new job salary: \b");
			int run2 = 0;
			char choice2 = '0';
			while (run2 != -1)
			{//gets(joBs.Jsalary);
				printf("\nPress 1 for 30-40 nis/h.\n");//30-40/h
				printf("Press 2 for 40-50 nis/h.\n");
				printf("Press 3 for 50-60 nis/h\n");
				printf("Press 4 for 60-70 nis/h\n");
				printf("Press 5 for +70 nis/h\n");//+70/h
				scanf("%c", &choice2);
				switch (choice2)
				{
				case '1':
				{
					strcpy(joBs.Jsalary, "30-40/h");
					run2 = -1;
					break;
				}
				case '2':
				{
					strcpy(joBs.Jsalary, "40-50/h");
					run2 = -1;
					break;
				}
				case '3':
				{
					strcpy(joBs.Jsalary, "50-60/h");
					run2 = -1;
					break;

				}
				case '4':
				{
					strcpy(joBs.Jsalary, "60-70/h");
					run2 = -1;
					break;
				}
				case '5':
				{
					strcpy(joBs.Jsalary, "+70/h");
					run2 = -1;
					break;
				}


				default:
				{
					system("cls");
					printf("wrong Input Please Choose between 1-5 \n");
				}
				}
			}
			getchar();
			break;
		}
		case '6':
		{
			getchar();
			printf("Enter new job hours: \b");
			//gets(joBs.Jhours);
			int run3 = 0;
			char choice3 = '0';
			while (run3 != -1)
			{
				printf("\nPress 1 for morning.\n");//30-40/h
				printf("Press 2 for afternoon.\n");
				printf("Press 3 for evening\n");
				printf("Press 4 for night\n");
				scanf("%c", &choice3);
				switch (choice3)
				{
				case '1':
				{
					strcpy(joBs.Jhours, "morning");
					run3 = -1;
					break;
				}
				case '2':
				{
					strcpy(joBs.Jhours, "afternoon");
					run3 = -1;
					break;
				}
				case '3':
				{
					strcpy(joBs.Jhours, "evening");
					run3 = -1;
					break;


				}
				case '4':
				{
					strcpy(joBs.Jhours, "night");
					run3 = -1;
					break;
				}

				default:
				{
					system("cls");
					printf("wrong Input Please Choose between 1-4 \n");
				}
				}
			}
			getchar();
			break;


		}
		case '7':
		{
			run = -1;
			getchar();
			break;
		}

		default:
			system("cls");
			printf("Worng input please try again...(1-7) \n");

		}
	}
	fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", joBs.serialNum, joBs.Jname, joBs.Jrange, joBs.Jcity, joBs.Jtype, joBs.Jdescription, joBs.Jresponsibilities, joBs.Jqualifications, joBs.Jsalary, joBs.Jhours, joBs.empEmail);
	fclose(fp);
	return 0;
}

job buildJob(int number)
{
	int row = 0;
	char* temp=NULL;
	FILE* jobF = fopen("JOB_LIST_DATA.csv", "r");
	job JobN;
	char buffer[MAXBUFFER];
	if (!jobF) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}
	JobN.serialNum = number;
	fgets(buffer, 2024, jobF);
	while (fgets(buffer, 2024, jobF))
	{
		temp = _strdup(buffer);
		if (atoi(getfield(temp, 1)) == number)
		{
			
			temp = _strdup(buffer);
			strcpy(JobN.Jname, getfield(temp, 2));
			temp = _strdup(buffer);
			strcpy(JobN.Jrange, getfield(temp, 3));
			temp = _strdup(buffer);
			strcpy(JobN.Jcity, getfield(temp, 4));
			temp = _strdup(buffer);
			strcpy(JobN.Jtype, getfield(temp, 5));
			temp = _strdup(buffer);
			strcpy(JobN.Jdescription, getfield(temp, 6));
			temp = _strdup(buffer);
			strcpy(JobN.Jresponsibilities, getfield(temp, 7));
			temp = _strdup(buffer);
			strcpy(JobN.Jqualifications, getfield(temp, 8));
			temp = _strdup(buffer);
			strcpy(JobN.Jsalary, getfield(temp, 9));
			temp = _strdup(buffer);
			strcpy(JobN.Jhours, getfield(temp, 10));
			temp = _strdup(buffer);
			strcpy(JobN.empEmail, getfield(temp, 11));

		}
	}
	fclose(jobF);
	return JobN;
}



