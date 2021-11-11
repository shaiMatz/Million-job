#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include<conio.h>


typedef struct candidate////yo
{
	char Lname[50], Fname[50], email[50], ID[10], password1[50], password2[50], city[50], answer[50], phoneNumber[20];//all the candidate data
	int questionChoose;
	int month, day, year;
}candidate;

int CVFile(char* CandidateName);
candidate Candidate_Registration();

int main()
{
    printf("\033[1; 31m");
    printf("Hello world\n"); 
    printf("\033[0m");
	//candidate newC = Candidate_Registration();
	char candidateName[50] = "shai";
	CVFile(candidateName);

	return 0;

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
        return 0;
    }
    printf("\nBase information\n");
    // Asking user input for the CVFile
    
    fprintf(CandidateCV, "%s %s",  CandidateName, "CV\n\n");
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
	scanf("%s", &newCandidate.ID);
	printf("\nEnter first name:  \b");
	scanf("%s", &newCandidate.Fname);
	printf("\nEnter last name:  \b");
	scanf("%s", &newCandidate.Lname);
	printf("\nEnter email address: (It will be your username)  \b");
	scanf("%s", &newCandidate.email);
	printf("\nEnter password:  \b");
	scanf("%s", &newCandidate.password1);
	printf("\nEnter your password again:  \b");
	scanf("%s", &newCandidate.password2);
	while (strcmp(newCandidate.password1, newCandidate.password2))
	{
		printf("\nthe passwords are diffrents,enter your verfication password again:  \b");
		scanf("%s", &newCandidate.password2);
	}
	printf("\nEnter your city name:  \b");
	scanf("%s", &newCandidate.city);
	printf("\nEnter your birthay: \n");
	printf("\nMonth:  \b");
	scanf("%d", &newCandidate.month);
	printf("\nDay:  \b");
	scanf("%d", &newCandidate.day);
	printf("\nYear:  \b");
	scanf("%d", &newCandidate.year);
	printf("\nEnter phone number:  \b");
	scanf("%s", &newCandidate.phoneNumber);
	printf("\nChoose your security question:(default qeustion is 1)\n");
	printf("press 1: What is your grandfather name from your father side? \n");
	printf("press 2: What is your pet name? \n");
	printf("press 3: What is the name of your high-school? \nyour choise:  \b");
	scanf("%d", &newCandidate.questionChoose);
	printf("\nEnter your answer:  \b");
	scanf("%s", &newCandidate.answer);
	printf("\nNEw account added to record");
	printf("\nNew Account added to record");
	// Saving data in file
	fprintf(CandidateF, "%s,%s,%s,%s,%s,%s,%d,%d,%d,%s,%d,%s\n", newCandidate.ID,
		newCandidate.Fname, newCandidate.Lname, newCandidate.email, newCandidate.password1,
		newCandidate.city, newCandidate.month, newCandidate.day,
		newCandidate.year, newCandidate.phoneNumber, newCandidate.questionChoose, newCandidate.answer);
	fclose(CandidateF);
	return newCandidate;
}






