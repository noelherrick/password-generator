#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

void printHelp();
int randBounded (int min, int max);
bool isAlphanumeric (int c);

int main (int argc, char** argv)
{
	// Program options
	int length = 12;
	int number = 1;
	bool includePunctuation = false;

	int opt = -1;

	while ((opt = getopt(argc, argv, "l:n:ph")) != -1)
	{
		int intval;

		switch (opt)
		{
			case 'l':
				if (sscanf(optarg, "%i", &intval) == 1)
				{
					length = intval;
				}
				else
				{
					printf("Argument passed to length is not a digit");
					return 1;
				}

				break;

			case 'n':
				if (sscanf(optarg, "%i", &intval) == 1)
				{
					number = intval;
				}
				else
				{
					printf("Argument passed to number is not a digit");
					return 1;
				}

				break;

			case 'p':
				includePunctuation = true;
				break;

			case 'h':
				printHelp();
				break;

			default:
				printHelp();
		}
	}

	srand(time(NULL));
	
	char *password = malloc(length + 1);

	password[length] = '\0';

	for (int i = 0; i < number; i++)
	{
		for (int j = 0; j < length; j++)
		{
			int randomNum;

			do
			{
				randomNum = randBounded(33, 126);
			}
			while (!isAlphanumeric(randomNum) && !includePunctuation);

			password[j] = (char)randomNum;
		}

		printf("%s\n", password);
	}

	free(password);

	return 0;
}

int randBounded (int min, int max)
{
	return rand() % (max - min + 1) + min;
}

bool isAlphanumeric (int c)
{
	return (c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123);
}

void printHelp ()
{
	printf("Usage: pass-gen\n");
	printf("-l number - length of the password\n");
	printf("-n number - number of passwords to generate\n");
	printf("-p - include punctuation\n");
	printf("-h - print help\n");
}
