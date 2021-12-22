#include "candidate.h"
#include "SearchEngine.h"
#include "checkFunction.h"

candidate loginC(char email[])
{
	char* pch = NULL;
	char* temp, buffer[2024];
	int column = 0, row = 0, wantedRow = 1;
	candidate newCand;
	FILE* fp = fopen("Candidate_DATA.csv", "r");//check if opend
	if (!fp)
	{
		printf("Can't open file\n");
		return;
	}
	else
	{

		wantedRow = findRightRow("Candidate_DATA.csv", email);// check if the email exists
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
			if (row == wantedRow)//copy all the information from the database into a struct
			{
				temp = _strdup(buffer);
				strcpy(newCand.ID, getfield(temp, 1));
				temp = _strdup(buffer);
				strcpy(newCand.Fname, getfield(temp, 2));
				temp = _strdup(buffer);
				strcpy(newCand.Lname, getfield(temp, 3));
				temp = _strdup(buffer);
				strcpy(newCand.email, getfield(temp, 4));
				temp = _strdup(buffer);
				strcpy(newCand.password1, getfield(temp, 5));
				temp = _strdup(buffer);
				strcpy(newCand.city, getfield(temp, 6));
				temp = _strdup(buffer);
				newCand.month = atoi(getfield(temp, 7));
				temp = _strdup(buffer);
				newCand.day = atoi(getfield(temp, 8));
				temp = _strdup(buffer);
				newCand.year = atoi(getfield(temp, 9));
				temp = _strdup(buffer);
				strcpy(newCand.phoneNumber, getfield(temp, 10));
				temp = _strdup(buffer);
				newCand.questionChoose = atoi(getfield(temp, 11));
				temp = _strdup(buffer);
				strcpy(newCand.answer, getfield(temp, 12));
				temp = _strdup(buffer);
				strcpy(newCand.wantedjobs, getfield(temp, 13));
				temp = _strdup(buffer);

			}

		}
	}
	fclose(fp);
	return newCand;
}

candidate CVFile(candidate cand)
{
	char temp[10] = "CV.txt", CVName[50];
	strcpy(CVName, cand.Fname);
	strcat(CVName, cand.Lname);
	strcat(CVName, temp);
	FILE* CandidateCV = fopen(CVName, "w+");//the name file will be his name+CV.txt

	char language[MAXNAME], drivingLicence[MAXNAME];//all the candidate base data
	char background[2024], eduction[MAXBUFFER], employmentExperience[MAXBUFFER], MilitaryService[MAXBUFFER];//more info
	if (!CandidateCV) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}
	printf("\nBase information\n");
	// Asking user input for the CVFile
	getchar();
	fprintf(CandidateCV, "%s %s %s", cand.Fname, cand.Lname, "CV\n\n");
	printf("ID : %s \n", cand.ID);
	fprintf(CandidateCV, "%s %s %s", "Base information\nID: ", cand.ID, "\n");
	printf("First name : %s \n", cand.Fname);
	printf("Last name : %s\n", cand.Lname);
	fprintf(CandidateCV, "%s %s %s %s", "Name : ", cand.Fname, cand.Lname, "\n");
	printf("Email address : %s\n", cand.email);
	fprintf(CandidateCV, "%s %s %s", "Email : ", cand.email, "\n");
	printf("Enter the languages you speak :  \b");
	gets(language);
	fprintf(CandidateCV, "%s %s %s", "Language : ", language, "\n");
	printf("Enter your driving license type (if you dont have drining license enter none) :  \b");
	scanf("%s", &drivingLicence);
	fprintf(CandidateCV, "%s %s %s", "DrivingLicence : ", drivingLicence, "\n");
	printf("City address : %s \n", cand.city);
	fprintf(CandidateCV, "%s %s %s", "City : ", cand.city, "\n");
	printf("Phone number: %s \n", cand.phoneNumber);
	fprintf(CandidateCV, "%s %s %s", "Phone number : ", cand.phoneNumber, "\n");

	getchar();
	//more info
	printf("\n\nMore information\nEnter your background :  \b");
	fprintf(CandidateCV, "%s", "Background :\n ");
	while (scanf("%[^\n]%*c", background) == 1)
	{
		fprintf(CandidateCV, "%s %s", background, "\n");
	}
	getchar();
	printf("\nEnter your eduction :  \n");
	fprintf(CandidateCV, "%s", "Eduction :\n ");
	while (scanf("%[^\n]%*c", eduction) == 1)
	{
		fprintf(CandidateCV, "%s %s", eduction, "\n");
	}
	getchar();
	printf("\nEnter your employment experience :  \n");
	fprintf(CandidateCV, "%s", "Employment experience :\n ");
	while (scanf("%[^\n]%*c", employmentExperience) == 1)
	{
		fprintf(CandidateCV, "%s %s", employmentExperience, "\n");
	}
	getchar();
	printf("\nEnter your military service background :  \n");
	fprintf(CandidateCV, "%s", "Military service :\n ");
	while (scanf("%[^\n]%*c", MilitaryService) == 1) {
		fprintf(CandidateCV, "%s %s", MilitaryService, "\n");
	}
	fclose(CandidateCV);
	system("cls");
	printf("your CV file created !\n");
	strcpy(cand.CVname, CVName);

	return cand;

}

candidate editProfile(candidate cand, char* fileName, int ans)
{
	int count = countNumLine("JOB_LIST_DATA.csv");
	char name[MAXNAME] = "submissionsJOB";
	char num[MAXNAME];
	char buffer[MAXBUFFER];
	int exists = 0;
	FILE* temppf = NULL;
	int check = 0, wantedRow;

	wantedRow = findRightRow(fileName, cand.email);//check if exists
	if (wantedRow == 0)
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
			printf("Enter your new email :  \b");
			scanf("%s", &cand.email);
			while (MailCheck(cand.email) == 0)
			{
				printf("\nEnter email address :  \b");
				scanf("%s", &cand.email);
			}
		}
		if (ans == 2)
		{
			printf("\nEnter password (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword :  ");
			scanf("%s", &cand.password1);
			while (PasswordCheck(cand.password1) == 0)
			{
				printf("\nEnter the password again (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword :  ");
				scanf("%s", &cand.password1);
			}
			printf("\nPassword verefication :  \b");
			scanf("%s", &cand.password2);
			while (strcmp(cand.password1, cand.password2))
			{
				printf("\nthe passwords are diffrents, enter your verfication password again :  \b");
				scanf("%s", &cand.password2);
			}
			getchar();
		}
		if (ans == 3)
		{
			printf("Enter your city name (enter just in small letters) : ");
			gets(cand.city);
			while (CheckLower(cand.city) == 0)
			{
				gets(cand.city);
			}
		}
		if (ans == 4)
		{
			printf("\nEnter phone number :  \b");
			scanf("%s", &cand.phoneNumber);
			while (PhoneCheck(cand.phoneNumber) == 0)
			{
				printf("\nEnter phone number :  \b");
				scanf("%s", &cand.phoneNumber);
			}
			getchar();
		}
		if (ans == 5)
		{
			printf("\nChoose your security question (default question is 1) : \n");
			printf("press 1: What is your grandfather name from your father side ? \n");
			printf("press 2: What is your pet name ? \n");
			printf("press 3: What is the name of your high-school ? \nyour choise :  \b");
			scanf("%d", &cand.questionChoose);
			getchar();
			printf("\nEnter your answer :  \b");
			gets(cand.answer);

		}
		if (ans == 6)
		{
			CVFile(cand);
		}
		if (ans == 7)
		{
			printf("\nEnter job preference :  \b");
			gets(cand.wantedjobs);
		}
		for (int i = 0; i < count; i++)
		{
			strcpy(name, "submissionsJOB");
			sprintf(num, "%d", i);
			strcat(name, num);
			strcat(name, ".csv");
			if (ifExists(name, cand.email, 4) == 0)
			{
				deleteline(name, findRightRow(name, cand.email));
				temppf = fopen(name, "a+");
				fprintf(temppf, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n", cand.ID,//enter all the informaitin into the database
					cand.Fname, cand.Lname, cand.email, cand.password1,
					cand.city, cand.month, cand.day,
					cand.year, cand.phoneNumber, cand.questionChoose, cand.answer, cand.wantedjobs);
				fclose(temppf);
			}
		}
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n", cand.ID,//enter all the informaitin into the database
			cand.Fname, cand.Lname, cand.email, cand.password1,
			cand.city, cand.month, cand.day,
			cand.year, cand.phoneNumber, cand.questionChoose, cand.answer, cand.wantedjobs);
		fclose(fp);
		return cand;

	}
	fclose(fp);
	return cand;
}

candidate Candidate_Registration()
{
	FILE* CandidateF = fopen("Candidate_DATA.csv", "a+");
	candidate newCandidate;

	if (!CandidateF) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}

	// Asking user input for the
	// new record to be added
	printf("\nEnter ID :  \b");
	scanf("%s", &newCandidate.ID);

	while ((IDCheck(newCandidate.ID) == 0) || (ifExists("Candidate_DATA.csv", newCandidate.ID, 1) == 0))
	{
		printf("There is already a candidate with the same ID !");
		printf("\nEnter ID again :  \b");
		scanf("%s", &newCandidate.ID);
	}
	printf("\nEnter first name :  \b");
	scanf("%s", &newCandidate.Fname);
	printf("\nEnter last name :  \b");
	scanf("%s", &newCandidate.Lname);

	printf("\nEnter email address (It will be your username) :  \b");
	scanf("%s", &newCandidate.email);
	while (ifExists("Candidate_DATA.csv", newCandidate.email, 4) != 1)
	{
		printf("The email is already exists in the database, please choose another : ");
		scanf("%s", &newCandidate.email);
	}
	while (MailCheck(newCandidate.email) == 0)
	{
		printf("\nEnter email address (It will be your username) :  \b");
		scanf("%s", &newCandidate.email);
	}


	printf("\nEnter password (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword : ");
	scanf("%s", &newCandidate.password1);
	while (ifExists("Candidate_DATA.csv", newCandidate.password1, 5) != 1)
	{
		printf("The password is already exists in the database, please choose anoter\n");
		scanf("%s", &newCandidate.password1);
	}
	while (PasswordCheck(newCandidate.password1) == 0)
	{
		printf("\nEnter password :  \b");
		scanf("%s", &newCandidate.password1);
	}
	printf("\nPassword verefication :  \b");
	scanf("%s", &newCandidate.password2);
	while (strcmp(newCandidate.password1, newCandidate.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again :  \b");
		scanf("%s", &newCandidate.password2);
	}
	getchar();
	printf("\nEnter your city name (enter just in small letters) :  \b");
	gets(newCandidate.city);
	while (CheckLower(newCandidate.city) == 0)
	{
		gets(newCandidate.city);
	}
	printf("\nEnter your birthay (00/00/0000) ");
	printf("\nMonth (00) :  \b");
	scanf("%d", &newCandidate.month);
	printf("\nDay (00) :  \b");
	scanf("%d", &newCandidate.day);
	printf("\nYear (0000) :  \b");
	scanf("%d", &newCandidate.year);
	while (BirthCheck(newCandidate.day, newCandidate.month, newCandidate.year) == 0)
	{
		printf("\nEnter your birthay : \n");
		printf("\nMonth :  \b");
		scanf("%d", &newCandidate.month);
		printf("\nDay :  \b");
		scanf("%d", &newCandidate.day);
		printf("\nYear :  \b");
		scanf("%d", &newCandidate.year);
	}
	printf("\nEnter phone number :  \b");
	scanf("%s", &newCandidate.phoneNumber);
	while (PhoneCheck(newCandidate.phoneNumber) == 0)
	{
		printf("\nEnter phone number :  \b");
		scanf("%s", &newCandidate.phoneNumber);
	}
	printf("\nChoose your security question (default question is 1) : \n");
	printf("press 1: What is your grandfather name from your father side ? \n");
	printf("press 2: What is your pet name ? \n");
	printf("press 3: What is the name of your high-school ? \nyour choice :  \b");
	scanf("%d", &newCandidate.questionChoose);
	getchar();
	printf("\nEnter your answer :  \b");
	gets(newCandidate.answer);
	printf("\nEnter your job preference :  \b");
	gets(newCandidate.wantedjobs);

	// Saving data in file
	fprintf(CandidateF, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n", newCandidate.ID,
		newCandidate.Fname, newCandidate.Lname, newCandidate.email, newCandidate.password1,
		newCandidate.city, newCandidate.month, newCandidate.day,
		newCandidate.year, newCandidate.phoneNumber, newCandidate.questionChoose, newCandidate.answer, newCandidate.wantedjobs);
	fclose(CandidateF);
	system("cls");
	printf("\nNew Account added to record !\n ~press enter to continue~\n");
	return newCandidate;
}

int CandidateMenu(candidate cand)
{
	int run = 0;
	char choice = '0';
	while (run != -1)
	{
		printf("----Welcome dear %s---- \n", cand.Fname);
		printf("Candidate Menu :\n1) Press 1 to search your next job.\n");
		printf("2) Press 2 to go to your list of Favorite jobs.\n");
		printf("3) Press 3 to go to your list of Submissions.\n");
		printf("4) Press 4 to edit your profile.\n");
		printf("5) Press 5 to delete your Profile.\n");
		printf("6) Press 6 to exit.\n\nchoice : ");
		scanf("%c", &choice);
		if (clearBuffer() > 1)
			choice = 'd';
		switch (choice)
		{
		case '1':
		{
			system("cls");
			searchEngine(cand);
			break;
		}
		case '2':
		{
			system("cls");
			favoriteJobs(cand);
			break;
		}
		case '3':
		{
			system("cls");
			wantedJobs(cand);//subbmitions list
			break;
		}
		case '4':
		{
			system("cls");
			editProfileMenu(cand);
			break;
		}
		case '5':
		{
			system("cls");
			char name[MAXNAME], num[MAXNAME], CFileName[MAXNAME];
			int count = countNumLine("JOB_LIST_DATA.csv");
			deleteline("Candidate_DATA.csv", findRightRow("Candidate_DATA.csv", cand.email));
			for (int i = 0; i < count; i++)
			{
				strcpy(name, "submissionsJOB");
				sprintf(num, "%d", i);
				strcat(name, num);
				strcat(name, ".csv");
				if (ifExists(name, cand.email, 4) == 0)
				{
					deleteline(name, findRightRow(name, cand.email));
				}
			}
			char tempname[MAXNAME] = "FAVORITEJOB";
			strcat(tempname, cand.Fname);
			strcat(tempname, cand.ID);
			strcat(tempname, ".csv");
			remove(tempname);

			strcpy(CFileName, cand.Fname);
			strcat(CFileName, cand.ID);
			strcat(CFileName, ".csv");
			remove(CFileName);
			run = -1;
			break;
		}
		case '6':
		{
			system("cls");
			run = -1;
			break;
		}

		default:
		{
			system("cls");
			printf("wrong Input Please Choose between 1-6 \n");
		}
		}
	}
	return 0;
}

void searchEngine(candidate cand) {//Search engine for candidate (menu)

	char choice = '0';
	int	run = 0;

	while (run != -1)
	{
		printf("----Dear %s Please choose a search action :----\n", cand.Fname);
		printf("Press 1 Show all jobs. \n");
		printf("Press 2 for Add filter.\n");
		printf("Press 3 for Sorting old to new.\n");
		printf("Press 4 for Sorting new to old.\n");
		printf("Press 5 for clear your search.\n");
		printf("Press 6 return previous menu.\n");
		printf("------Enter your choice please :------\n");
		scanf("%c", &choice);
		if (clearBuffer() > 1)
			choice = 'd';
		switch (choice)
		{
		case '1': {
			system("cls");
			printall(cand);
			break;
		}
		case '2':
		{
			system("cls");
			Filtermenu(cand);
			break;
		}
		case '3':
		{
			system("cls");
			printoldertonew(cand);
			break;
		}
		case '4':
		{
			system("cls");
			printnewtoolder(cand);
			break;
		}
		case '5':
		{
			system("cls");
			printall(cand);
			break;
		}
		case '6':
		{
			system("cls");
			return 0;
		}
		default:
		{

			system("cls");
			printf("Wrong Input! Please Choose between 1-6 \n\n");
		}
		}
	}

}

int editProfileMenu(candidate cand)
{
	char choice = '0';
	int run = 0;
	int ans = 0;

	while (run != -1)
	{
		printf("Edit Profile Menu :\nPress 1 for Edit email.\n");
		printf("Press 2 to Change your password.\n");
		printf("Press 3 to Edit city adress.\n");
		printf("Press 4 to Edit Phone number.\n");
		printf("Press 5 to Change your security question.\n");
		printf("Press 6 to build your cv file. \n");
		printf("press 7 to Edit your job preference \n");
		printf("Press 8 to go back to the previous menu.\n");
		printf("choice : ");
		scanf("%c", &choice);
		if (clearBuffer() > 1)
			choice = 'd';
		switch (choice)
		{
		case '1':
		{
			getchar();
			system("cls");
			ans = choice - '0';
			cand = editProfile(cand, "Candidate_DATA.csv", ans);//Email editfunction
			getchar();
			printf("edited mail.\n");
			break;
		}
		case '2':
		{
			getchar();
			system("cls");
			ans = choice - '0';
			cand = editProfile(cand, "Candidate_DATA.csv", ans);//Change Password function
			printf("edited password.\n");
			break;
		}
		case '3':
		{
			getchar();
			system("cls");
			ans = choice - '0';
			cand = editProfile(cand, "Candidate_DATA.csv", ans);//address edit function
			printf("edited city.\n");
			break;
		}
		case '4':
		{
			getchar();
			system("cls");
			ans = choice - '0';
			cand = editProfile(cand, "Candidate_DATA.csv", ans);//Phone number edit function 
			printf("edited phone number.\n");
			break;
		}

		case '5':
		{

			getchar();
			system("cls");
			ans = choice - '0';
			cand = editProfile(cand, "Candidate_DATA.csv", ans);//change security question
			printf("edited security question.\n");
			break;
		}

		case '6':
		{
			system("cls");
			cand = CVFile(cand);//free CV builder
			break;
		}
		case '7':
		{
			getchar();
			system("cls");
			ans = choice - '0';
			cand = editProfile(cand, "Candidate_DATA.csv", ans);//change job preference.
			printf("edited job preference.\n");
			break;
		}
		case '8':
		{
			
			system("cls");//exit
			printf("all the data changed!\n");
			run = -1;
			break;
		}

		default:
		{
			system("cls");
			printf("Wrong input please try again...(1-8) \n");
		}
		}
	}

}

candidate resetPassword(candidate c)
{
	char securityAnswer[MAXNAME];
	int run = 0;
	int run2 = 0;
	char temp[MAXNAME];
	strcpy(temp, c.password1);
	while (run == 0)
	{
		printf("\nTo reset your password, enter your security answer \n");
		if (c.questionChoose == 1)
			printf("What is your grandfather name from your father side ?\nAnswer :  \b");
		if (c.questionChoose == 2)
			printf("What is your pet name ? \nAnswer :  \b");
		if (c.questionChoose == 3)
			printf("What is the name of your high school ? \nAnswer :  \b");
			printf("What is the name of your high school ? \nAnswer :  \b");
		gets(securityAnswer);

		if (strcmp(c.answer, securityAnswer) == 0)
		{
			while (run2 == 0)
			{
				while (run2 == 0)
				{
					c = editProfile(c, "Candidate_DATA.csv", 2);//password edit function
					return c;
					if (strcmp(temp, c.password1) == 0)
					{
						printf("the new password can be same as the old one, try again !\n");
					}
					else
						run2 = -1;
				}
				run = -1;

				if (strcmp(temp, c.password1) == 0)
					printf("the new password can be the same as the old one, try again !\n");
			}
		}
		else
		{
			printf("Your security answer does not match, try again !\n");
		}
	}

}

int wantedJobs(candidate cand)// print all the wanted jobs
{
	char CFileName[MAXNAME], buffer[MAXBUFFER];
	strcpy(CFileName, cand.Fname);
	strcat(CFileName, cand.ID);
	strcat(CFileName, ".csv");

	FILE* candF = fopen(CFileName, "r");
	if (!candF) {
		printf("You don't have jobs in submissions list\n");
		return 1;
	}

	while (fgets(buffer, 2024, candF))
	{
		printJob(buffer);
	}
	fclose(candF);
	return 0;
}

int favoriteJobs(candidate cand)// print all the favorite jobs
{
	char name[MAXNAME] = "FAVORITEJOB", buffer[MAXBUFFER];
	strcat(name, cand.Fname);
	strcat(name, cand.ID);
	strcat(name, ".csv");

	FILE* candF = fopen(name, "r");
	if (!candF)
	{
		printf("You don't have jobs in favorite list\n");
		return 0;
	}

	while (fgets(buffer, 2024, candF))
	{
		if (strcmp(buffer, "\n") != 0)
			printJob(buffer);

	}
	fclose(candF);
	return 0;
}