#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable : 4996).


void MenuPrint(void);
void MenuProcess(void);
void NewGame(void);
void ContinueGame(void);
void ClearScreen(void);
void GamePrint(void);
void GameProcess(void);
int GameControls(char, char[4], char[2]);
void GameSave(char, char[4], char[2]);

int main(void)
{
	MenuPrint();
	MenuProcess();



	getchar();
	return 0;
}


void MenuPrint(void)
{
	ClearScreen();
	printf("Please enter a number. Press the Enter button.\n");
	printf("1. New game\n");
	printf("2. Continue game\n");
	printf("3. End game\n");
}

void MenuProcess(void)
{
	int menuSelected;
	scanf("%d", &menuSelected);

	switch (menuSelected)
	{
	case 1:
		printf("1. New game\n");
		NewGame();
		break;
	case 2:
		printf("2. Continue game\n");
		ContinueGame();
		break;
	case 3:
		printf("3. End game\n");
		system("Exit");
		break;
	default:
		printf("Wrong choice\n");
		MenuProcess();
		break;
	}
}

void NewGame(void)
{
	FILE* fpGameFile;
	fpGameFile = fopen("checkersGame.dat", "w+");
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (i == 2 || i == 3)
			{
				fprintf(fpGameFile, "W ");
			}
			else if (i == 6 || i == 7)
			{
				fprintf(fpGameFile, "B ");
			}
			else
			{
				fprintf(fpGameFile, "  ");
			}

		}
		fprintf(fpGameFile, "\n");
	}
	fprintf(fpGameFile, "W");

	fclose(fpGameFile);
	GamePrint();
}

void ContinueGame(void)
{
	GamePrint();
}

void ClearScreen(void)
{
	fprintf(stdout, "\033[2J"); // clean screen
	fprintf(stdout, "\033[1;1H"); // move cursor to the first line
}

void GamePrint(void)
{
	ClearScreen();


	FILE* fpGameFile;

	fpGameFile = fopen("checkersGame.dat", "r");
	fseek(fpGameFile, 0, SEEK_SET);
	char readGameRow[17];

	for (int i = 8; i > 0; i--)
	{
		printf("%d", i);
		fgets(readGameRow, 17, fpGameFile);
		puts(readGameRow);
		fseek(fpGameFile, sizeof(char), SEEK_CUR);
		fseek(fpGameFile, sizeof(char), SEEK_CUR);
	}

	printf(" ");
	for (char j = 'A'; j < 'I'; j++)
	{
		printf("%c ", j);
	}
	printf("\n");

	fclose(fpGameFile);

	GameProcess();

}

void GameProcess(void)
{
	FILE* fpGameFile;

	fpGameFile = fopen("checkersGame.dat", "r");
	fseek(fpGameFile, -1, SEEK_END);
	char readWhichPlayer;
	readWhichPlayer = fgetc(fpGameFile);
	if (readWhichPlayer == 'W')
	{
		printf("Team White please enter your command. \n");
	}
	else if (readWhichPlayer == 'B')
	{
		printf("Team Black please enter your command.\n");
	}
	fclose(fpGameFile);



	char enteredValue[4];
	scanf("%s", enteredValue);

	//char newStampValue[2];
	char newStampValue[2] = { 'X','X' };
	char oldStampValue[2] = { 'X','X' };


	size_t lenteredValueLength = strlen(enteredValue);
	if (lenteredValueLength == 4)
	{
		enteredValue[0] = toupper(enteredValue[0]);
		enteredValue[2] = toupper(enteredValue[2]);

		fpGameFile = fopen("checkersGame.dat", "r+");
		char readGameRow[17];

		fseek(fpGameFile, 0, SEEK_SET);

		for (int i = 8; i > 0; i--)
		{
			if (enteredValue[1] == (char)(i + '0'))
			{

				for (char j = 'A'; j < 'I'; j++)
				{
					if (enteredValue[0] == j)
					{
						oldStampValue[0] = (char)fgetc(fpGameFile);
						oldStampValue[1] = (char)fgetc(fpGameFile);
					}
					fseek(fpGameFile, sizeof(char), SEEK_CUR);
					fseek(fpGameFile, sizeof(char), SEEK_CUR);
				}

			}
			fgets(readGameRow, 17, fpGameFile);
			fseek(fpGameFile, sizeof(char), SEEK_CUR);
			fseek(fpGameFile, sizeof(char), SEEK_CUR);
		}

		fclose(fpGameFile);

		newStampValue[0] = oldStampValue[0];
		newStampValue[1] = oldStampValue[1];

	}



	int isSuccessGameControls = GameControls(readWhichPlayer, enteredValue, oldStampValue);

	if (isSuccessGameControls == 0)
	{
		printf("Continue press enter\n");
		system("pause");
		GamePrint();

	}
	else
	{


		if (readWhichPlayer == 'W' && enteredValue[3] == '1')
		{
			newStampValue[0] = 'W';
			newStampValue[1] = 'W';
		}

		if (readWhichPlayer == 'B' && enteredValue[3] == '8')
		{
			newStampValue[0] = 'B';
			newStampValue[1] = 'B';
		}


		GameSave(readWhichPlayer, enteredValue, newStampValue);
	}

}

int  GameControls(char readWhichPlayer, char enteredValue[4], char oldStampValue[2])
{
	char newStampValue[1];
	int isSuccess = 1;
	size_t lenteredValueLength = strlen(enteredValue);
	if (lenteredValueLength != 4)
	{
		printf("Wrong: Only 4 character\n");
		isSuccess = 0;
	}

	if (enteredValue[0] == enteredValue[2] && enteredValue[1] == enteredValue[3])
	{
		printf("Wrong : Same character\n");
		isSuccess = 0;
	}


	if (enteredValue[0] != 'A' && enteredValue[0] != 'B' && enteredValue[0] != 'C' && enteredValue[0] != 'D' && enteredValue[0] != 'E' && enteredValue[0] != 'F' && enteredValue[0] != 'G' && enteredValue[0] != 'H')
	{
		printf("Wrong : First character\n");
		isSuccess = 0;
	}

	if (enteredValue[1] != '1' && enteredValue[1] != '2' && enteredValue[1] != '3' && enteredValue[1] != '4' && enteredValue[1] != '5' && enteredValue[1] != '6' && enteredValue[1] != '7' && enteredValue[1] != '8')
	{
		printf("Wrong : Second character\n");
		isSuccess = 0;
	}

	if (enteredValue[2] != 'A' && enteredValue[2] != 'B' && enteredValue[2] != 'C' && enteredValue[2] != 'D' && enteredValue[2] != 'E' && enteredValue[2] != 'F' && enteredValue[2] != 'G' && enteredValue[2] != 'H')
	{
		printf("Wrong : Third character\n");
		isSuccess = 0;
	}

	if (enteredValue[3] != '1' && enteredValue[3] != '2' && enteredValue[3] != '3' && enteredValue[3] != '4' && enteredValue[3] != '5' && enteredValue[3] != '6' && enteredValue[3] != '7' && enteredValue[3] != '8')
	{
		printf("Wrong : Fourth character\n");
		isSuccess = 0;
	}

	if (enteredValue[0] != enteredValue[2] && enteredValue[1] != enteredValue[3])
	{
		printf("Wrong : CROSS cannot be done\n");
		isSuccess = 0;
	}


	if (oldStampValue[0] == 'W' && oldStampValue[1] == ' ' && (enteredValue[3] - enteredValue[1]) > 0)
	{
		printf("Wrong : No return \n");
		isSuccess = 0;
	}

	if (oldStampValue[0] == 'B' && oldStampValue[1] == ' ' && (enteredValue[3] - enteredValue[1]) < 0)
	{
		printf("Wrong : No return \n");
		isSuccess = 0;
	}


	return isSuccess;

}

void GameSave(char readWhichPlayer, char enteredValue[4], char newStampValue[2])
{
	FILE* fpGameFile;

	fpGameFile = fopen("checkersGame.dat", "r+");
	char readGameRow[17];

	fseek(fpGameFile, 0, SEEK_SET);

	for (int i = 8; i > 0; i--)
	{
		if (enteredValue[1] == (char)(i + '0'))
		{

			for (char j = 'A'; j < 'I'; j++)
			{
				if (enteredValue[0] == j)
				{
					fprintf(fpGameFile, "  ");
				}
				fseek(fpGameFile, sizeof(char), SEEK_CUR);
				fseek(fpGameFile, sizeof(char), SEEK_CUR);
			}

		}
		fgets(readGameRow, 17, fpGameFile);
		fseek(fpGameFile, sizeof(char), SEEK_CUR);
		fseek(fpGameFile, sizeof(char), SEEK_CUR);
	}

	fclose(fpGameFile);

	fpGameFile = fopen("checkersGame.dat", "r+");

	fseek(fpGameFile, 0, SEEK_SET);
	for (int i = 8; i > 0; i--)
	{
		if (enteredValue[3] == (char)(i + '0'))
		{
			for (char j = 'A'; j < 'I'; j++)
			{
				if (enteredValue[2] == j)
				{
					fprintf(fpGameFile, "%c%c", newStampValue[0], newStampValue[1]);
				}
				fseek(fpGameFile, sizeof(char), SEEK_CUR);
				fseek(fpGameFile, sizeof(char), SEEK_CUR);
			}
		}
		fgets(readGameRow, 17, fpGameFile);
		fseek(fpGameFile, sizeof(char), SEEK_CUR);
		fseek(fpGameFile, sizeof(char), SEEK_CUR);
	}

	fclose(fpGameFile);



	fpGameFile = fopen("checkersGame.dat", "r+");

	fseek(fpGameFile, -1, SEEK_END);
	if (readWhichPlayer == 'W')
	{
		fprintf(fpGameFile, "B");
	}
	else if (readWhichPlayer == 'B')
	{
		fprintf(fpGameFile, "W");
	}

	fclose(fpGameFile);

	GamePrint();
}