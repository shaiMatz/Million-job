#include "candidate.h"

candidate loginC(char email[])
{
	char* value, buffer[2024];
	int column = 0, row = 0, wantedRow = 1;
	candidate newCand;
	FILE* fp = fopen("Candidate_DATA.csv", "r");
	if (!fp)
		printf("Can't open file\n");

	else
	{

		wantedRow = findRightRow("Candidate_DATA.csv", email);
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
			column = 0;
			if (row == wantedRow)
			{
				value = strtok(buffer, ", ");
				while (value)
				{
					if (column == 0)
						strcpy( newCand.ID ,value);
					if (column == 1)
						strcpy(newCand.Fname, value);
					if (column == 2)
						strcpy(newCand.Lname, value);
					if (column == 3)
						strcpy(newCand.email, value);
					if (column == 4)
						strcpy(newCand.password1, value);
					if (column == 5)
						strcpy(newCand.city, value);
					if (column == 6)
						newCand.month = atoi(value);
					if (column == 7)
						newCand.day = atoi(value);
					if (column == 8)
						newCand.year = atoi(value);
					if (column == 9)
						strcpy(newCand.phoneNumber, value);
					if (column == 10)
						newCand.questionChoose = atoi(value);
					if (column == 11)
						strcpy(newCand.answer, value);
					if (column == 12)
						strcpy(newCand.CVname, value);

					value = strtok(NULL, ", ");
					column++;
				}
			}
			else
				continue;
		}
	}
	fclose(fp);
	return newCand;
}

int CVFile(candidate cand)
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
		return -1;
	}
	printf("\nBase information\n");
	// Asking user input for the CVFile

	fprintf(CandidateCV, "%s %s %s", cand.Fname,cand.Lname, "CV\n\n");
	printf("ID: %s \n",cand.ID);
	fprintf(CandidateCV, "%s %s %s", "Base information\nID: ", cand.ID, "\n");
	printf("First name: %s \n",cand.Fname);
	printf("Last name:  %s\n",cand.Lname);
	fprintf(CandidateCV, "%s %s %s %s ", "Name: ", cand.Fname, cand.Lname, "\n");
	printf("Email address: %s\n",cand.email);
	fprintf(CandidateCV, "%s %s %s", "Email: ", cand.email, "\n");
	printf("Enter the languages you speak:  \b");
	gets(language);
	fprintf(CandidateCV, "%s %s %s", "Language: ", language, "\n");
	printf("Enter your driving license type: (if you dont have drining license enter none)  \b");
	scanf("%s", &drivingLicence);
	fprintf(CandidateCV, "%s %s %s", "DrivingLicence: ", drivingLicence, "\n");
	printf("City address: %s \n",cand.city);
	fprintf(CandidateCV, "%s %s %s", "City: ", cand.city, "\n");
	printf("Phone number: %s \n",cand.phoneNumber);
	fprintf(CandidateCV, "%s %s %s", "Phone number: ", cand.phoneNumber, "\n");

	getchar();
	//more info
	printf("\n\nMore information\nEnter your background:  \b");
	fprintf(CandidateCV, "%s", "Background:\n ");
	while (scanf("%[^\n]%*c", background) == 1)
	{
		fprintf(CandidateCV, "%s %s", background, "\n");
	}
	getchar();
	printf("\nEnter your eduction:  \n");
	fprintf(CandidateCV, "%s", "Eduction:\n ");
	while (scanf("%[^\n]%*c", eduction) == 1)
	{
		fprintf(CandidateCV, "%s %s", eduction, "\n");
	}
	getchar();
	printf("\nEnter your employment experience:  \n");
	fprintf(CandidateCV, "%s", "Employment experience:\n ");
	while (scanf("%[^\n]%*c", employmentExperience) == 1)
	{
		fprintf(CandidateCV, "%s %s", employmentExperience, "\n");
	}
	getchar();
	printf("\nEnter your military service background:  \n");
	fprintf(CandidateCV, "%s", "Military service:\n ");
	while (scanf("%[^\n]%*c", MilitaryService) == 1) {
		fprintf(CandidateCV, "%s %s", MilitaryService, "\n");
	}
	fclose(CandidateCV);
	system("cls");
	printf("your CV file created!\n");
	strcpy(cand.CVname, CVName);
	int row=findRightRow("Candidate_DATA.csv", cand.email);
	deleteline("Candidate_DATA.csv", row);
	FILE* fp = fopen("Candidate_DATA.csv", "a+");
	if (!fp) {
		// Error in file opening
		printf("Can't open file\n");
		return -1;
	}
	fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n", cand.ID,
		cand.Fname, cand.Lname, cand.email, cand.password1,
		cand.city, cand.month, cand.day,
		cand.year, cand.phoneNumber, cand.questionChoose, cand.answer,cand.CVname);
	fclose(fp);
	return 0;
	
}

int editProfile(candidate cand, char* fileName, int ans)
{

	int check = 0, wantedRow;
	wantedRow = findRightRow(fileName, cand.email);
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
		return -1;
	}
	if (check == 0)
	{
		if (ans == 1)
		{
			printf("Enter your new email: \b");
			scanf("%s", &cand.email);
			while (MailCheck(cand.email) == 0)
			{
				printf("\nEnter email address:  \b");
				scanf("%s", &cand.email);
			}
		}
		if (ans == 2)
		{
			printf("\nEnter password: (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword:  ");
			scanf("%s", &cand.password1);
			while (PasswordCheck(cand.password1) == 0)
			{
				printf("\nEnter the password again: (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword:  ");
				scanf("%s", &cand.password1);
			}
			printf("\nPassword verefication:  \b");
			scanf("%s", &cand.password2);
			while (strcmp(cand.password1, cand.password2))
			{
				printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
				scanf("%s", &cand.password2);
			}
			getchar();
		}
		if (ans == 3)
		{
			printf("Enter your city name : (enter just in small letters)");
			gets(cand.city);
			while (CheckLower(cand.city) == 0)
			{
				gets(cand.city);
			}
		}
		if (ans == 4)
		{
			printf("\nEnter phone number:  \b");
			scanf("%s", &cand.phoneNumber);
			while (PhoneCheck(cand.phoneNumber) == 0)
			{
				printf("\nEnter phone number:  \b");
				scanf("%s", &cand.phoneNumber);
			}
		}
		if (ans == 5)
		{
			printf("\nChoose your security question:(default question is 1)\n");
			printf("press 1: What is your grandfather name from your father side? \n");
			printf("press 2: What is your pet name? \n");
			printf("press 3: What is the name of your high-school? \nyour choise:  \b");
			scanf("%s", &cand.questionChoose);
		}
		if (ans == 6)
		{
			printf("\nEnter phone number:  \b");
			gets(cand.answer);
		}
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s\n", cand.ID,
			cand.Fname, cand.Lname, cand.email, cand.password1,
			cand.city, cand.month, cand.day,
			cand.year, cand.phoneNumber, cand.questionChoose, cand.answer);
		fclose(fp);
		return 0;

	}
	fclose(fp);
	return 1;
}

//int addAtTheEndRow(candidate cand, char* fileName, int row, char* addString);
//{
//	FILE* pf = fopen(fileName, "r");
//	char buffer[2024], * value, s[3] = "\n";
//	int column = 0;
//	int numRow = 0;
//	int rc;
//	if (!pf)
//		printf("Can't open file\n");
//
//	else
//	{
//		while (fgets(buffer, 1024, pf))
//		{
//			puts(buffer);
//			numRow++;
//			if (row == numRow)
//			{
//				value = strtok(buffer, s);
//				puts(value);
//				strcat(buffer, ",");
//				strcat(buffer, addString);
//				strcat(buffer, "\n");
//			}
//		}
//		deleteline(fileName, row);
//	}
//	fclose(pf);
//	return 0;
//}


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
	printf("\nEnter ID:  \b");
	scanf("%s", &newCandidate.ID);
	while (IDCheck(newCandidate.ID) == 0)
	{
		printf("\nEnter ID:  \b");
		scanf("%s", &newCandidate.ID);
	}
	printf("\nEnter first name:  \b");
	scanf("%s", &newCandidate.Fname);
	printf("\nEnter last name:  \b");
	scanf("%s", &newCandidate.Lname);
	printf("\nEnter email address: (It will be your username)  \b");
	scanf("%s", &newCandidate.email);
	while (MailCheck(newCandidate.email) == 0)
	{
		printf("\nEnter email address: (It will be your username)  \b");
		scanf("%s", &newCandidate.email);
	}
	printf("\nEnter password: (needs to be at least 8 char with at least one capital letter,\none small letter,a number and symbol The password needs to be in english)\npassword:  ");
	scanf("%s", &newCandidate.password1);
	while (PasswordCheck(newCandidate.password1) == 0)
	{
		printf("\nEnter password:  \b");
		scanf("%s", &newCandidate.password1);
	}
	printf("\nPassword verefication:  \b");
	scanf("%s", &newCandidate.password2);
	while (strcmp(newCandidate.password1, newCandidate.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
		scanf("%s", &newCandidate.password2);
	}
	getchar();
	printf("\nEnter your city name: (enter just in small letters) \b");
	gets(newCandidate.city);
	while (CheckLower(newCandidate.city) == 0)
	{
		gets(newCandidate.city);
	}
	printf("\nEnter your birthay ");
	printf("\nMonth:  \b");
	scanf("%d", &newCandidate.month);
	printf("\nDay:  \b");
	scanf("%d", &newCandidate.day);
	printf("\nYear:  \b");
	scanf("%d", &newCandidate.year);
	while (BirthCheck(newCandidate.day, newCandidate.month, newCandidate.year) == 0)
	{
		printf("\nEnter your birthay: \n");
		printf("\nMonth:  \b");
		scanf("%d", &newCandidate.month);
		printf("\nDay:  \b");
		scanf("%d", &newCandidate.day);
		printf("\nYear:  \b");
		scanf("%d", &newCandidate.year);
	}
	printf("\nEnter phone number:  \b");
	scanf("%s", &newCandidate.phoneNumber);
	while (PhoneCheck(newCandidate.phoneNumber) == 0)
	{
		printf("\nEnter phone number:  \b");
		scanf("%s", &newCandidate.phoneNumber);
	}
	printf("\nChoose your security question:(default question is 1)\n");
	printf("press 1: What is your grandfather name from your father side? \n");
	printf("press 2: What is your pet name? \n");
	printf("press 3: What is the name of your high-school? \nyour choise:  \b");
	scanf("%d", &newCandidate.questionChoose);
	getchar();
	printf("\nEnter your answer:  \b");
	gets(newCandidate.answer);

	// Saving data in file
	fprintf(CandidateF, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s\n", newCandidate.ID,
		newCandidate.Fname, newCandidate.Lname, newCandidate.email, newCandidate.password1,
		newCandidate.city, newCandidate.month, newCandidate.day,
		newCandidate.year, newCandidate.phoneNumber, newCandidate.questionChoose, newCandidate.answer);
	fclose(CandidateF);
	system("cls");
	printf("\nNew Account added to record!\n");
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
		printf("4) Press 4 to edit your profile \n");
		printf("5) Press 5 to delete your Profile\n");
		printf("6) Press 6 to exit.\n\nchoice : ");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
		{
			getchar();
			system("cls");
			//searchEngine(cand);
			getchar();
			break;
		}
		case '2':
		{
			getchar();
			system("cls");
			//favoriteJobs(cand);
			getchar(); 
			break;
		}
		case '3':
		{
			getchar();
			system("cls");
			//subList(cand);//subbmitions list
			getchar();
			break;
		}
		case '4':
		{
			system("cls");
			getchar();
			editProfileMenu(cand);
			getchar();
			break;
		}
		case '5':
		{
			getchar();
			system("cls");
			deleteline(cand.email,findRightRow("Candidate_DATA.csv",cand.email));
			getchar();
			break;
		}
		case '6':
		{
			system("cls");
			run = -1;
			getchar();
			break;
		}

		default: 
		{
			system("cls");
			printf("wrong Input Please Choose between 1-6 \n");
		}
		}
	}
	return main();
}

void searchEngine(candidate cand) {//Search engine for candidate (menu)

	char choice = '0';
	int	run = 0;
	printf("----Dear %s Please choose a search action:----\n", cand.Fname);
	printf("Press 1 Show all jobs. \n");
	printf("Press 2 for Search by keywords.\n");
	printf("Press 3 for Add filter.\n");
	printf("Press 4 for Sorting new to old.\n");
	printf("Press 5 for Sorting old to new.\n");
	printf("Press 6 for clear your search.\n");
	printf("Press 7 return previous menu.\n");
	printf("------Enter your choice please:------\n");
	scanf("%d", &choice);
	while (run != -1)
	{
		switch (choice)
		{
		case 1: {
			//allJobsPrint();
			int i = 0;
			char choice = '0';
			printf("Would you like to add job to favorite?\n");
			printf("For Yes, press 1 , for No, press 0\n");
			scanf("%s", &choice);
			while (i != 0)
			{
				switch (choice)
				{
				case 1:
					//addFavorite();//add favorite job function
					i = 0;

				case 0:
					i = 0;

				default:
					printf("Worng number please try again");
				}
			}
			break;
		}
		case 2:
		{
			//keywordSearch();
			break;
		}
		case 3:
		{
			//addFilter();
			break;
		}
		case 4:
		{
			//newToOld();//sorting  function new to old
			break;
		}
		case 5:
		{
			//oldToNew();//old to new...
		}
		case 6:
		{
			//searchReset();
			break;
		}
		case 7:
		{
			run = -1;
			break;
		}
		default:
		{
			printf("Wrong Input! Please Choose between 1-7 \n");
		}
		}
	}

}

int editProfileMenu(candidate cand)
{
	char choice = '0';
	int run = 0;

	while (run != -1) 
	{
		printf("Edit Profile Menu:\nPress 1 for Edit email.\n");
		printf("Press 2 for Change your password\n");
		printf("Press 3 for Edit city adress.\n");
		printf("Press 4 for Edit Phone number.\n");
		printf("Press 5 for to add or change your wanted job.\n");
		printf("Press 6 for Change your security question\n");
		printf("Press 7 for to enter your cv file: (enter cv name)\n");
		printf("Press 8 for to build your cv file: \n");
		printf("Press 9 to back to the previous menu\n");
		printf("choice : ");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
		{
			system("cls");
			getchar();
			editProfile(cand, "Candidate_DATA.csv",atoi(choice));//Email editfunction
			getchar();
			break;
		}
		case '2':
		{
			system("cls");
			getchar();
			editProfile(cand, "Candidate_DATA.csv", atoi(choice));//Change Password function.passwordChange();//Change Password function.
			getchar();
			break;
		}
		case '3':
		{
			system("cls");
			getchar();
			editProfile(cand, "Candidate_DATA.csv", atoi(choice));//address edit function
			getchar();
			break;
		}
		case '4':
		{
			system("cls");
			getchar();
			editProfile(cand, "Candidate_DATA.csv", atoi(choice));//Phone number edit function 
			getchar();
			break;
		}
		case '5':
		{
			system("cls");
			getchar();
			//addORchangeJob();// add or change your wanted job(from list of types)
			getchar();
			break;
		}
		case '6':
		{
			system("cls");
			//change security number
			getchar();
			break;
		}
		case '7':
		{
			system("cls");
			getchar();
			//upLoadCV();
			getchar();
			break;
		}
		 case '8':
		{
			 system("cls");
			 getchar();
			 CVFile(cand);//free CV builder (not urgent)
			 getchar();
			 break;
		}
		case '9':
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

candidate resetPassword(candidate c)
{
	char securityAnswer[MAXNAME];
	int run = 0;
	int run2 = 0;
	char temp[MAXNAME];
	strcpy(temp, c.password1);
	while (run == 0)
	{
		printf("\nTo reset you're password, enter you're security answer \n");
		if (c.questionChoose == 1)
			printf("What is your grandfather name from your father side?\nAnswer:  \b");
		if (c.questionChoose == 2)
			printf("What is your pet name ? \nAnswer:  \b");
		if (c.questionChoose == 3)
			printf("What is the name of your high-school? \nAnswer:  \b");
		getchar();
		gets(securityAnswer);
		if (strcmp(c.answer, securityAnswer) == 0)
		{
			while (run2 == 0)
			{
				printf("Enter you're new password twice :\nFirst time : ");
				scanf("%s", &c.password1);
				while (PasswordCheck(c.password1) == 0)
				{
					printf("Enter valid password : ");
					scanf("%s", &c.password1);
				}
				if (strcmp(temp, c.password1) != 0)
				{
					printf("Second Time : ");
					scanf("%s", &c.password2);
					if (strcmp(c.password1, c.password2) != 0)
					{
						printf("Passwords are different, try again : ");
					}
					else
					{
						system("cls");
						printf("Done !\n");
						run2 = 1;
						
						int row = findRightRow("Candidate_DATA.csv", c.email);
						deleteline("Candidate_DATA.csv", row);
						FILE* fp = fopen("Candidate_DATA.csv", "a+");
						if (!fp) {
							// Error in file opening
							printf("Can't open file\n");
						}
						fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s,%s\n", c.ID,
							c.Fname, c.Lname, c.email, c.password1,
							c.city, c.month, c.day,
							c.year, c.phoneNumber, c.questionChoose, c.answer, c.CVname);
						fclose(fp);
						return c;
					}
				}
				if (strcmp(temp, c.password1) == 0)
					printf("the new password can be same as the old one, try again !\n");
			}
		}
		else
		{
			printf("You're security answer doesn't match, try again !\n");
		}
	}

}