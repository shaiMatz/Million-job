#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <fcntl.h>

#define MAXNAME 50
#define MAXBUFFER 2024



typedef struct candidate////yo????
{
	char Lname[MAXNAME], Fname[MAXNAME], email[MAXNAME], password1[MAXNAME], password2[MAXNAME], city[MAXNAME], answer[MAXNAME], phoneNumber[MAXNAME];//all the candidate data
	int questionChoose;
	long ID;
	int month, day, year;
}candidate;

typedef struct employer
{
	char companyName[MAXNAME], Lname[MAXNAME], Fname[MAXNAME], email[MAXNAME], password1[MAXNAME], password2[MAXNAME], city[MAXNAME], answer[MAXNAME], phoneNumber[MAXNAME], jobDescription[MAXNAME];//all the candidate data
	int questionChoose;


}employer;

////////////// CANDIDATE FUNCTIONS ///////////

int MailCheck(char* mail);
int PhoneCheck(char* phone);
int PasswordCheck(char* password);
int BirthCheck(int day, int month, int year);
int CVFile(char* CandidateName);
candidate Candidate_Registration();
candidate loginC(char email[]);
int findRightRow(char* fileName, char* email);
int deleteline(char* fileName, int row);
int editProfile(candidate cand, char* fileName, int ans);

////////////// EMPLOYER FUNCTIONS ///////////
employer employer_Registration();
employer loginE(char email[]);

int main()
{
	employer newEmployer = employer_Registration();
	//candidate newC = loginC("shyshir@gmail.com");
	//editProfile(newC, "Candidate_DATA.csv", 3);
	//char candidateName[50] = "shai";
	//CVFile(candidateName);

	return 0;

}
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
	FILE* F = fopen("Employer_DATA.csv", "a+");
	employer newEmp;


	if (!F) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}

	// Asking user input for the
	// new record to be added
	printf("\nEnter company name:  \b");
	scanf("%s", &newEmp.companyName);
	getchar();
	printf("\nEnter first name:  \b");
	scanf("%s", &newEmp.Fname);
	printf("\nEnter last name:  \b");
	scanf("%s", &newEmp.Lname);
	printf("\nEnter email address: (It will be your username)  \b");
	scanf("%s", &newEmp.email);
	while (MailCheck(newEmp.email) == 0)
	{
		printf("\nEnter email address: (It will be your username)  \b");
		scanf("%s", &newEmp.email);
	}
	printf("\nEnter password:  \b");
	scanf("%s", &newEmp.password1);
	while (PasswordCheck(newEmp.password1) == 0)
	{
		printf("\nEnter password:  \b");
		scanf("%s", &newEmp.password1);
	}
	printf("\nEnter your password again:  \b");
	scanf("%s", &newEmp.password2);
	while (strcmp(newEmp.password1, newEmp.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
		scanf("%s", &newEmp.password2);
	}
	printf("\nEnter your city name:  \b");
	scanf("%s", &newEmp.city);
	printf("\nEnter phone number:  \b");
	scanf("%s", &newEmp.phoneNumber);
	while (PhoneCheck(newEmp.phoneNumber) == 0)
	{
		printf("\nEnter phone number:  \b");
		scanf("%s", &newEmp.phoneNumber);
	}
	printf("\nEnter some information about the company:  \n");
	getchar(newEmp.jobDescription);

	printf("\nChoose your security question:(default qeustion is 1)\n");
	printf("press 1: What is your grandfather name from your father side? \n");
	printf("press 2: What is your pet name? \n");
	printf("press 3: What is the name of your high-school? \nyour choise:  \b");

	scanf("%d", &newEmp.questionChoose);
	printf("\nEnter your answer:  \b");
	scanf("%s", &newEmp.answer);

	// Saving data in file
	fprintf(F, "%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n", newEmp.companyName,
		newEmp.Fname, newEmp.Lname, newEmp.email, newEmp.password1, newEmp.jobDescription,
		newEmp.city, newEmp.phoneNumber, newEmp.questionChoose, newEmp.answer);
	fclose(F);
	system("cls");
	printf("\nNew Account added to record");

	return newEmp;

}


int deleteline(char* fileName, int row)
{
	char buffer[2024];
	int numRow = 0, rc;
	char name[50] = "temp";
	FILE* fp = fopen(fileName, "r");
	strcat(name, fileName);
	FILE* temp = fopen(name, "w");
	if (!fp)
		printf("Can't open file: %s\n", fileName);

	if (!temp)
		printf("Can't open file: %s\n", name);
	else
	{
		while (fgets(buffer, 1024, fp))
		{
			numRow++;
			if (row != numRow)
				fputs(buffer, temp);
		}
	}


	if (fclose(fp) == 0)
	{
		printf("file closed");
	}



	rc = remove("Candidate_DATA.csv");
	if (rc != 0)
	{
		perror("remove");
		return 1;
	}
	puts("Removed file");
	fclose(temp);
	rc = rename(name, fileName);
	return 0;
}
int findRightRow(char* fileName, char* email)
{//find the row by email, returns the line nunber
	char* value, buffer[2024];
	int column = 0, row = 0, wantedRow = 0;
	FILE* fp = fopen(fileName, "r");
	if (!fp)
		printf("Can't open file\n");

	else
	{
		while (fgets(buffer, 1024, fp))//run until he find the row that matches the email
		{
			if (strcmp("\n", buffer) == 0)
				break;
			column = 0;
			row++;
			wantedRow++;
			if (row == 1)//skip the first row, its titles
				continue;
			else {
				value = strtok(buffer, ", ");
				while (column != 3)//3 is the email column
				{
					value = strtok(NULL, ", ");
					column++;
				}
				if (column == 3)
				{
					if (strcmp(email, value) == 0)
					{//check if the same email
						fclose(fp);
						return wantedRow;		//find the right row can stop now	
					}
				}
				else//continue to the next row
				{
					column = 0;
					continue;
				}

			}

		}
	}
	fclose(fp);
	return 0;
}
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
						newCand.ID = value;
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
	if (check == 0)
	{
		printf("\nenter your new information: \b");
		if (ans == 0)
			scanf("%s", &cand.ID);
		if (ans == 1)
			scanf("%s", &cand.Fname);
		if (ans == 2)
			scanf("%s", &cand.Lname);
		if (ans == 3)
			scanf("%s", &cand.email);
		if (ans == 4)
			scanf("%s", &cand.password1);
		if (ans == 5)
			scanf("%s", &cand.city);
		if (ans == 6)
			scanf("%s", &cand.month);
		if (ans == 7)
			scanf("%d", &cand.day);
		if (ans == 8)
			scanf("%d", &cand.year);
		if (ans == 9)
			scanf("%s", &cand.phoneNumber);
		if (ans == 10)
			scanf("%s", &cand.questionChoose);
		if (ans == 11)
			scanf("%s", &cand.answer);

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
int CVFile(char* CandidateName)
{
	char temp[10] = "CV.txt", CVName[50];
	strcpy(CVName, CandidateName);
	strcat(CVName, temp);
	FILE* CandidateCV = fopen(CVName, "w+");//the name file will be his name+CV.txt

	char Lname[50], Fname[50], email[50], language[50], ID[10], city[50], drivingLicence[10], phoneNumber[20];//all the candidate base data
	char background[2024], eduction[2024], employmentExperience[2024], MilitaryService[2024];//more info
	if (!CandidateCV) {
		// Error in file opening
		printf("Can't open file\n");
		return -1;
	}
	printf("\nBase information\n");
	// Asking user input for the CVFile

	fprintf(CandidateCV, "%s %s", CandidateName, "CV\n\n");
	printf("Enter ID:  \b");
	scanf("%s", &ID);
	fprintf(CandidateCV, "%s %s %s", "Base information\nID: ", ID, "\n");
	printf("Enter first name:  \b");
	scanf("%s", &Fname);
	printf("Enter last name:  \b");
	scanf("%s", &Lname);
	fprintf(CandidateCV, "%s %s %s %s ", "Name: ", Fname, Lname, "\n");
	printf("Enter email address:  \b");
	scanf("%s", &email);
	while (MailCheck(email) == 0)
	{
		printf("Enter email address:  \b");
		scanf("%s", &email);
	}
	fprintf(CandidateCV, "%s %s %s", "Email: ", email, "\n");
	printf("Enter the languages you speak:  \b");
	scanf("%s", &language);
	fprintf(CandidateCV, "%s %s %s", "Language: ", language, "\n");
	printf("Enter your driving licence type:  \b");
	scanf("%s", &drivingLicence);
	fprintf(CandidateCV, "%s %s %s", "DrivingLicence: ", drivingLicence, "\n");
	printf("Enter your city address:  \b");
	scanf("%s", &city);
	fprintf(CandidateCV, "%s %s %s", "City: ", city, "\n");
	printf("Enter phone number:  \b");
	scanf("%s", &phoneNumber);
	while (PhoneCheck(phoneNumber) == 0)
	{
		printf("Enter phone number:  \b");
		scanf("%s", &phoneNumber);
	}
	fprintf(CandidateCV, "%s %s %s", "Phone number: ", phoneNumber, "\n");

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
	printf(CandidateCV, "%s", "Employment experience:\n ");
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
	return 0;
}
candidate Candidate_Registration()
{
	FILE* CandidateF = fopen("Candidate_DATA.csv", "a+");
	candidate newCandidate;
	//char Lname[50],Fname[50],email[50],ID[10],password1[50], password2[50],city[50],answer[50],phoneNumber[20];//all the candidate data
	//int questionChoose = 1,month=0,day=0,year=0;//1 is the default question
	if (!CandidateF) {
		// Error in file opening
		printf("Can't open file\n");
		return;
	}

	// Asking user input for the
	// new record to be added
	printf("\nEnter ID:  \b");
	scanf("%ld", &newCandidate.ID);
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
	printf("\nEnter password:  \b");
	scanf("%s", &newCandidate.password1);
	while (PasswordCheck(newCandidate.password1) == 0)
	{
		printf("\nEnter password:  \b");
		scanf("%s", &newCandidate.password1);
	}
	printf("\nEnter your password again:  \b");
	scanf("%s", &newCandidate.password2);
	while (strcmp(newCandidate.password1, newCandidate.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
		scanf("%s", &newCandidate.password2);
	}
	printf("\nEnter your city name:  \b");
	scanf("%s", &newCandidate.city);
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
	printf("\nChoose your security question:(default qeustion is 1)\n");
	printf("press 1: What is your grandfather name from your father side? \n");
	printf("press 2: What is your pet name? \n");
	printf("press 3: What is the name of your high-school? \nyour choise:  \b");
	scanf("%d", &newCandidate.questionChoose);
	printf("\nEnter your answer:  \b");
	scanf("%s", &newCandidate.answer);
	printf("\nNew Account added to record");
	// Saving data in file
	fprintf(CandidateF, "%ld,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s\n", newCandidate.ID,
		newCandidate.Fname, newCandidate.Lname, newCandidate.email, newCandidate.password1,
		newCandidate.city, newCandidate.month, newCandidate.day,
		newCandidate.year, newCandidate.phoneNumber, newCandidate.questionChoose, newCandidate.answer);
	fclose(CandidateF);
	return newCandidate;
}
int MailCheck(char* mail)
{
	int position = 0;
	int point = 0;
	int point2 = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	int i = 0;
	for (i = 0; i < strlen(mail); i++)
	{
		if (mail[i] == '@')
			counter3++;
		if (mail[i] == '.')
			counter4++;
	}
	if (counter3 != 1 || counter4 < 1)
	{
		printf("Mail not valid !\n");
		return 0;
	}
	i = 0;
	while (mail[i] != '@')
	{
		position++;
		i++;
	}
	i = 0;
	while (mail[i] != '@')
	{
		counter2++;
		i++;
	}
	while (mail[i] != '.')
	{
		counter2++;
		i++;
	}
	for (int i = 0; i < strlen(mail); i++)
	{
		if (mail[i] == '.')
			point++;
		if (mail[i] == '@')
			point2++;
	}
	if (position >= 3 && point >= 1 && point2 == 1 && position < counter2)
		return 1;
	else
	{
		printf("The mail is not valid !\n");
		return 0;
	}
}
int PasswordCheck(char* password)
{
	int i = 0;
	int countLower = 0, countUpper = 0, countSymbol = 0, countDigit = 0;
	for (int i = 0; i < strlen(password); i++)
	{
		if (password[i] >= 'A' && password[i] <= 'Z')
			countUpper++;
		if (password[i] >= 'a' && password[i] <= 'z')
			countLower++;
		if (password[i] >= '0' && password[i] <= '9')
			countDigit++;
		if (password[i] >= 32 && password[i] <= 47 || password[i] >= 58 && password[i] <= 64 || password[i] >= 92 && password[i] <= 96 || password[i] >= 123 && password[i] <= 126)
			countSymbol++;
	}
	if (countUpper > 0 && countLower > 0 && countDigit > 0 && countSymbol > 0 && strlen(password) >= 8)
	{
		printf("Password Valid !\n");
		return 1;
	}
	else
	{
		printf("The password does not match, try again !");
		return 0;
	}
}
int BirthCheck(int day, int month, int year)
{
	if (year < 1900)
	{
		printf("Not valid year !\n");
		return 0;
	}
	if (month < 1 || month >12)
	{
		printf("Not valid month !\n");
		return 0;
	}
	if (day < 1 || day>31)
	{
		printf("Not valid day !\n");
		return 0;
	}
	if (year % 4 == 0 && year & 100 != 0 || year % 400 == 0)
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day >= 1 && day <= 31)
			{
				printf("valid birthdate !\n");
				return 1;
			}
			else
			{
				printf("birthdate not valid !\n");
				return 1;
			}
		}
		if (month == 2)
		{
			if (day >= 1 && day <= 29)
			{
				printf("valid birthdate !\n");
				return 1;
			}
			else
			{
				printf("birthdate not valid !\n");
				return 0;
			}
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day >= 1 && day <= 30)
			{
				printf("valid birthdate !\n");
				return 1;
			}
			else
			{
				printf("birthdate not valid !\n");
				return 0;
			}
		}


	}
	else
	{
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day >= 1 && day <= 31)
			{
				printf("valid birthdate !\n");
				return 1;
			}
			else
			{
				printf("birthdate not valid !\n");
				return 0;
			}
		}
		if (month == 2)
		{
			if (day >= 1 && day <= 28)
			{
				printf("valid birthdate !\n");
				return 1;
			}
			else
			{
				printf("birthdate not valid !\n");
				return 0;
			}
		}
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{
			if (day >= 1 && day <= 30)
			{
				printf("valid birthdate !\n");
				return 1;
			}
			else
			{
				printf("birthdate not valid !\n");
				return 0;
			}
		}
	}
}
int PhoneCheck(char* phone)
{
	if (phone[0] == '0' && phone[1] == '5' && strlen(phone) == 10)
		return 1;
	if (strlen(phone) != 10)
	{
		printf("The phone number must have 10 digits, try again !\n");
		return 0;
	}
	else
	{
		printf("The phone number must start with 05, try again !\n");
		return 0;
	}
}