
#pragma once

#include"employer.h"
#include"SearchEngine.h"

employer loginE(char email[])
{
	char* temp, buffer[2024];
	int column = 0, row = 0, wantedRow = 1;
	employer newEmp;
	FILE* fp = fopen("Employer_DATA.csv", "r");
	if (!fp)
	{
		printf("Can't open file\n");
		return;
	}

	else
	{

		wantedRow = findRightRow("Employer_DATA.csv", email);
		if (wantedRow == -1)
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
			if (row == wantedRow)
			{
				temp = _strdup(buffer);
				strcpy(newEmp.companyName, getfield(temp,1));
				temp = _strdup(buffer);
				strcpy(newEmp.Fname, getfield(temp, 2));
				temp = _strdup(buffer);
				strcpy(newEmp.Lname, getfield(temp, 3));
				temp = _strdup(buffer);
				strcpy(newEmp.email, getfield(temp, 4));
				temp = _strdup(buffer);
				strcpy(newEmp.password1, getfield(temp, 5));
				temp = _strdup(buffer);
				strcpy(newEmp.city, getfield(temp, 6));
				temp = _strdup(buffer);
				strcpy(newEmp.jobDescription, getfield(temp, 7));
				temp = _strdup(buffer);
				strcpy(newEmp.phoneNumber, getfield(temp, 8));
				temp = _strdup(buffer);
				newEmp.questionChoose=atoi(getfield(temp, 9));
				temp = _strdup(buffer);
				strcpy(newEmp.answer, getfield(temp, 10));

			}
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


	printf("\nEnter password: (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword:  ");
	scanf("%s", &newEmployer.password1);
	while (PasswordCheck(newEmployer.password1) == 0)
	{
		printf("\nEnter the password again: (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword:  ");
		scanf("%s", &newEmployer.password1);
	}
	printf("\nPassword verefication:  \b");
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

employer editProfileEmp(employer emp, char* fileName, int ans)
{
	
	char buffer[MAXBUFFER];
	int exists = 0;
	FILE* temppf = NULL;
	int check = 0, wantedRow;

	wantedRow = findRightRow(fileName, emp.email);
	if (wantedRow == 1)
	{
		printf("The email not found!");
		return;
	}

	check = deleteline(fileName, wantedRow);
	FILE* fp = fopen(fileName, "a+");
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}
	if (check == 0)
	{
		if (ans == 1)
		{
			printf("\nEnter new company name:  \b");
			gets(emp.companyName);
		}
		if (ans == 2)
		{
			printf("Enter your new email: \b");
			scanf("%s", &emp.email);
			while (MailCheck(emp.email) == 0)
			{
				printf("\nEnter email address:  \b");
				scanf("%s", &emp.email);
			}
		}
		if (ans == 3)
		{
			printf("\nEnter password: (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword:  ");
			scanf("%s", &emp.password1);
			while (PasswordCheck(emp.password1) == 0)
			{
				printf("\nEnter the password again: (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword:  ");
				scanf("%s", &emp.password1);
			}
			printf("\nPassword verefication:  \b");
			scanf("%s", &emp.password2);
			while (strcmp(emp.password1, emp.password2))
			{
				printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
				scanf("%s", &emp.password2);
			}
			getchar();
		}
		if (ans == 4)
		{
			printf("Enter new jobDescription : ");
			gets(emp.jobDescription);
		}
		if (ans == 5)
		{
			printf("Enter your city name : (enter just in small letters)");
			gets(emp.city);
			while (CheckLower(emp.city) == 0)
			{
				gets(emp.city);
			}
		}
		if (ans == 6)
		{
			printf("\nEnter phone number:  \b");
			scanf("%s", &emp.phoneNumber);
			while (PhoneCheck(emp.phoneNumber) == 0)
			{
				printf("\nEnter phone number:  \b");
				scanf("%s", &emp.phoneNumber);
			}
		}
		if (ans == 5)
		{
			printf("\nChoose your security question:(default question is 1)\n");
			printf("press 1: What is your grandfather name from your father side? \n");
			printf("press 2: What is your pet name? \n");
			printf("press 3: What is the name of your high-school? \nyour choise:  \b");
			scanf("%s", &emp.questionChoose);
			printf("\nEnter your answer:  \b");
			gets(emp.answer);
		}
		if (ans == 6)
		{
			printf("\nEnter phone number:  \b");
			gets(emp.answer);
		}

		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", emp.companyName,emp.Fname, emp.Lname, 
			emp.email, emp.password1, emp.jobDescription,emp.city, emp.phoneNumber, emp.questionChoose, emp.answer);
		fclose(fp);
		return emp;

	}
	fclose(fp);
	return emp;
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
		printf("\nTo reset your password, enter your security answer \n");
		if (e.questionChoose == 1)
			printf("What is your grandfather name from your father side?\nAnswer:  \b");
		if (e.questionChoose == 2)
			printf("What is your pet name ? \nAnswer:  \b");
		if (e.questionChoose == 3)
			printf("What is the name of your high school? \nAnswer:  \b");
		gets(securityAnswer);
		
		if (strcmp(e.answer, securityAnswer) == 0)
		{
			while (run2 == 0)
			{
				e = editProfileEmp(e, "Employer_DATA.csv", 3);//password edit function
				return e;
				if (strcmp(temp, e.password1) == 0)
				{
					printf("the new password can be same as the old one, try again !\n");
				}
				else
					run2 = -1;
			}
			run = -1;
		}
		else
		{
			printf("You're security answer doesn't match, try again !\n");
		}
	}

}

int EmployerMenu(employer emp)
{
	int run = 0;
	char choice = '0';
	candidate cand;
	strcpy(cand.email,"0");
	strcpy(cand.Fname, emp.Fname);
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
		getchar();
		switch (choice)
		{
		case '1': {
			system("cls");
			searchEngine(cand);
			break;
		}
		case '2':
		{
			system("cls");
			jobEdit(emp.email);// inside function switch cases between 3 cases (edit,add,delete)
			break;
		}
		case '3':
		{
			system("cls");
			jobsOfferList(emp.email);//printing list of jobs and details,viewing optional candidates for specific jobs , and option to delete the job
			break;
		}
		case '4':
		{
			editProfileMenuEmp(emp);// menu for edit profile for employer
			break;
		}
		case '5':
		{
			system("cls");
			deleteline("Employer_DATA.csv", findRightRow("Employer_DATA.csv", emp.email));//delete employer
			run = -1;
			break;
		}
		case '6':
		{
			system("cls");
			run = -1;
			empSearchEngine();// candidate searching by age/type/working area
		}
		case '7':
		{
			system("cls");
			run = -1;
			break;
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

int editProfileMenuEmp(employer emp)
{
	char choice = '0';
	int run = 0;
	int ans = 0;

	while (run != -1)
	{
		printf("Edit Profile Menu:\nPress 1 to company name.\n");
		printf("Press 2 for Edit email.\n");
		printf("Press 3 to Change your password.\n");
		printf("Press 4 to Edit the job description.\n");
		printf("Press 5 to Edit city adress.\n");
		printf("Press 6 to Edit Phone number.\n");
		printf("Press 7 to Change your security question.\n");
		printf("Press 8 to go back to the previous menu.\n");
		printf("choice : ");
		scanf("%c", &choice);
		getchar();
		switch (choice)
		{
		case '1':
		{
			system("cls");
			ans = choice - '0';
			emp = editProfileEmp(emp, "Employer_DATA.csv", ans);//company name
			break;
		}
		case '2':
		{
			system("cls");
			ans = choice - '0';
			emp= editProfileEmp(emp, "Employer_DATA.csv", ans);//email
			break;
		}
		case '3':
		{
			system("cls");
			ans = choice - '0';
			emp= editProfileEmp(emp, "Employer_DATA.csv", ans);//password edit function
			break;
		}
		case '4':
		{
			system("cls");
			ans = choice - '0';
			emp= editProfileEmp(emp, "Employer_DATA.csv", ans);//job description edit function 
			break;
		}

		case '5':
		{
			system("cls");
			ans = choice - '0';
			emp=editProfileEmp(emp, "Employer_DATA.csv", ans);//city edit function 
			break;
		}

		case '6':
		{
			system("cls");
			ans = choice - '0';
			emp=editProfileEmp(emp, "Employer_DATA.csv", ans);//phone number edit function 
			break;
		}
		case '7':
		{
			system("cls");
			ans = choice - '0';
			emp=editProfileEmp(emp, "Employer_DATA.csv", ans);//security question edit function 
			break;
		}
		case '8':
		{
			system("cls");
			run = -1;
			break;
		}

		default:
		{
			system("cls");
			printf("Worng input please try again...(1-8) \n");
		}
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
		getchar();
		switch (choice)
		{
		case '1':
		{
			system("cls");
			jobAdd(email);
			break;
		}
		case '2':
		{
			system("cls");
			editJobFromList(email);
			break;
		}
		case '3':
		{
			system("cls");
			deleteJob(email);
			break;
		}
		case '4':
		{
			system("cls");
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

}

int jobAdd(char* email)
{
	int serialNum;
	serialNum = lastSerial();
	char* Jname[MAXNAME], Jrange[MAXBUFFER], Jcity[MAXNAME], Jtype[MAXNAME], Jdescription[MAXBUFFER], Jresponsibilities[MAXBUFFER], 
		Jqualifications[MAXBUFFER], Jsalary[MAXNAME], Jhours[MAXNAME];

	FILE* Jobdata = fopen("JOB_LIST_DATA.csv", "a+");
	if (!Jobdata) {
		// Error in file opening
		printf("Can't open file\n");
		return 1;
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
		printf("Press 5 for 70+ nis/h\n");//+70/h
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
			strcpy(Jsalary, "70+/h");
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
	serialNum++;
	// Saving data in file

	fprintf(Jobdata, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", serialNum, Jname, Jcity,
		Jrange, Jtype, Jdescription, Jresponsibilities, Jqualifications,
		Jsalary, Jhours, email);
	fclose(Jobdata);
	system("cls");
	printf("\nNew job added to record\n~prees enter to continue~\n");
	return 0;


}

int editJobFromList(char* email)
{
	int jobNumber;
	int check = 0,run = 0,run2 = 0, run3 = 0;
	char choice = '0', choice2 = '0', choice3 = '0';
	
	if (printMyPublishedJobs(email) == 0)
	{
		printf("You dont have any published jobs!");
		return 0;
	}

	printf("\nEnter the job number you want to edit: ");
	scanf("%d", &jobNumber);
	getchar();
	job joBs;
	joBs = buildJob(jobNumber);

	check = deleteJobLine("JOB_LIST_DATA.csv", jobNumber);
	FILE* fp = fopen("JOB_LIST_DATA.csv", "a+");
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return 1;
	}
	

	while (run != -1)
	{
		printf("\nPress 1 to Change the name of the job.\n");
		printf("Press 2 to Change the job description.\n");
		printf("Press 3 to Change job main responsibilities.\n");
		printf("Press 4 to Change job qualifications.\n");
		printf("Press 5 to Change job salary.\n");
		printf("Press 6 to Change job hours.\n");
		printf("Press 7 to exit.\n");
		printf("choice: ");
		scanf("%c", &choice);
		getchar();
		switch (choice)
		{
		case '1':
		{
			system("cls");
			printf("Enter new name of the job: \b");
			gets(joBs.Jname);
			getchar();
			break;
		}
		case '2':
		{
			system("cls");
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
			system("cls");
			printf("Enter new job salary: \b");
			
			while (run2 != -1)
			{
				printf("\nPress 1 for 30-40 nis/h.\n");//30-40/h
				printf("Press 2 for 40-50 nis/h.\n");
				printf("Press 3 for 50-60 nis/h\n");
				printf("Press 4 for 60-70 nis/h\n");
				printf("Press 5 for 70+ nis/h\n");//+70/h
				printf("Choice: ");
				scanf("%c", &choice2);
				getchar();
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
					strcpy(joBs.Jsalary, "70+/h");
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
			break;
		}
		case '6':
		{
			system("cls");
			printf("Enter new job hours: \b");
			while (run3 != -1)
			{
				printf("\nPress 1 for morning.\n");//30-40/h
				printf("Press 2 for afternoon.\n");
				printf("Press 3 for evening.\n");
				printf("Press 4 for night.\n");
				printf("Choice: ");
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
			break;


		}
		case '7':
		{
			system("cls");
			run = -1;
			break;
		}

		default:
			system("cls");
			printf("Worng input please try again...(1-7) \n");

		}
	}
	fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", joBs.serialNum, joBs.Jname, joBs.Jrange, joBs.Jcity,
		joBs.Jtype, joBs.Jdescription, joBs.Jresponsibilities, joBs.Jqualifications,
		joBs.Jsalary, joBs.Jhours, joBs.empEmail);
	fclose(fp);



	return 0;
}

int deleteJob(char* email)
{
	
	int jobNumber, check = 0;
	char jobNum[MAXBUFFER];
	char fileName[MAXNAME] = "submissionsJOB";//submissionsJOB2

	if (printMyPublishedJobs(email) == 0)
	{
		printf("You dont have any published jobs!");
		return 0;
	}
	
	printf("\nEnter the job number you want to delete: ");
	scanf("%d", &jobNumber);
	getchar();
	job joBs;
	joBs = buildJob(jobNumber);
	sprintf(jobNum, "%d", jobNumber);
	strcat(fileName, jobNum);
	strcat(fileName, ".csv");

	if (findJobsubFile(fileName) == 0)// if there a .csv file of submissions.
	{
		deleteFromSubAndFromPersonalcsvFile(fileName,jobNumber);
	}

	check = fevoritsDelete(fileName, jobNumber);//fevorits check and delete.
	


	check = deleteJobLine("JOB_LIST_DATA.csv", jobNumber);
	if (check == 0)
	{
		printf("\nJob No.%d was deleted from the JOB DATA BASE successfully!\n", jobNumber);
		return 0;
	}

	if (check != 0)
	{
		printf("\nThere was a problem to delete your job!\n");
		return 1;
	}
}

int printMyPublishedJobs(char *email)
{
	char* value, buffer[2024];

	int column = 0, row = 0;

	int jobCounter = 0;
	char c2[1000];
	char* pch;

	FILE* JoblistdataF = fopen("JOB_LIST_DATA.csv", "r");
	if (JoblistdataF == NULL)
	{
		printf("Can't open file!");
		return 1;
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
	return jobCounter;
}

int jobsOfferList(char *email)
{
	int jobNumber;
	char jobNum[MAXBUFFER];
	char fileName[MAXNAME] = "submissionsJOB";//submissionsJOB2
	if (printMyPublishedJobs(email) == 0)
	{
		printf("You dont have any published jobs!");
		return 0;
	}
	else
	{
		printf("\nEnter the job number to see all the candidates that submitted for this job: ");
		scanf("%d", &jobNumber);
		getchar();
		sprintf(jobNum, "%d", jobNumber);
		strcat(fileName, jobNum);
		strcat(fileName, ".csv");

		if (findJobsubFile(fileName) != 0)
		{
			printf("\nStill No one submitted for this job!\n");
			return 1;
		}
		else
		{
			FILE* fp = fopen(fileName, "r");
			if (!fp)
			{
				printf("can't open file\n");
				return 1;
			}
			char buffer[2024];
			while (fgets(buffer, 1024, fp))
			{
				printCand(buffer);
			}
			fclose(fp);
			printf("\nIf you want to delete a job, choose the job number that you want");
			int run = 0;
			char choice = '0';
			while (run != -1)
			{
				printf("Press 1 for delete this job.\n");
				printf("Press 2 to go back.\n");
				scanf("%c", &choice);
				switch (choice)
				{
				case '1':
				{
					deleteJob(email);
					run = -1;
					break;
				}
				case '2':
				{
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
		}
	}
	return 0;
}

job buildJob(int number)
{
	int row = 0;
	char* temp = NULL;
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



