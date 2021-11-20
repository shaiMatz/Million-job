#include "checkFunction.h"


int IDCheck(char* ID)
{
	long longID;
	if (strlen(ID) != 9 && strlen(ID) != 8)
	{
		printf("Your ID isn't right!\n");
		return 0;
	}
	longID = atol(ID);
	if (IDCheckIFREAL(longID) == 0)
	{
		printf("Your ID isn't right!\n");
		return 0;
	}
	return 1;

}
int IDCheckIFREAL(long numid) //function "ID"
{
	long int num1, num2, num3, num4, num5, num6, num7, num8, num9, sum; // in this function i unpucked the id number that the user entered. and multiplide by the algoritem 1,2.
	num1 = (numid / 100000000) * 1;
	num2 = ((numid / 10000000) % 10) * 2;
	num3 = ((numid / 1000000) % 10) * 1;
	num4 = ((numid / 100000) % 10) * 2;
	num5 = ((numid / 10000) % 10) * 1;
	num6 = ((numid / 1000) % 10) * 2;
	num7 = ((numid / 100) % 10) * 1;
	num8 = ((numid / 10) % 10) * 2;
	num9 = (numid % 10) * 1;
	if (num1 >= 10 || num2 >= 10 || num3 >= 10 || num4 >= 10 || num5 >= 10 || num6 >= 10 || num7 >= 10 || num8 >= 10 || num9 >= 10) // in this case i checked if after i multiplied i get number bigger than 10 so i broke the number and and sum it.
	{
		num1 = (num1 / 10) + (num1 % 10);
		num2 = (num2 / 10) + (num2 % 10);
		num3 = (num3 / 10) + (num3 % 10);
		num4 = (num4 / 10) + (num4 % 10);
		num5 = (num5 / 10) + (num5 % 10);
		num6 = (num6 / 10) + (num6 % 10);
		num7 = (num7 / 10) + (num7 % 10);
		num8 = (num8 / 10) + (num8 % 10);
		num9 = (num9 / 10) + (num9 % 10);
	}
	sum = num1 + num2 + num3 + num4 + num5 + num6 + num7 + num8 + num9; // here i check the sum of the numbers after the algoritem.
	if (sum % 10 == 0)// if the sum devied by 10 without remain so its proper id.
		return 1;
	else// else mean that the id is not proper.
		return 0;
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
int CheckLower(char* city)
{
	int count = 0, i = 0, countSpace = 0, countSymbol = 0;

	for (i; i < strlen(city); i++)
	{
		if (city[i] >= 'a' && city[i] <= 'z')
		{
			count++;
		}
		if (city[i] == ' ')
		{
			countSpace++;
		}
		if (city[i] > 32 && city[i] <= 47 || city[i] >= 58 && city[i] <= 64 || city[i] >= 92 && city[i] <= 96 || city[i] >= 123 && city[i] <= 126)
		{
			countSymbol++;
		}


	}
	if (count == strlen(city) - countSpace - countSymbol)
		return 1;
	else
	{
		printf("Enter the city only in lowercase : ");
		return 0;
	}

}

