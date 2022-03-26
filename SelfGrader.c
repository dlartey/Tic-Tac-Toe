// University of Leeds, School of Computing
// Autograder for Coursework 2
// Copyright Dr Ammar Alsalka, 30 October 2020


// STUDENTS: DO NOT ALTER ANYTHING IN THIS FILE
//++++++++++++++++++++++++++++++++++++++++++++++++

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tic.h"

#define JsonStrSize 5000
#define Presubmission 1


int IsAutoGradinng = 0;
int mustShow=0;
int stage= 1;
char* JsonStr;

void tell (char* s)
{
	if (Presubmission && stage == 1)
		printf ("%s", s);
}

void show ()
{
	if (Presubmission && mustShow && stage == 1)
		showGrid ();

}

int InitGraderString ()
{
	JsonStr = (char *) malloc (sizeof (char) * JsonStrSize);
	strcpy (JsonStr, "{\n");   // let's start, bismillah
	strcat (JsonStr, "\t\"output\": \"Graded by Ammar's CAutoGrader\",\n");
	strcat (JsonStr, "\t\"tests\":\n");  // let's start the tests
	strcat (JsonStr, "\t[\n");
	return 1;
}

int AddTestString (int score, int max_score, char* output, int is_final)
{
	char temp[320];

	strcat (JsonStr , "\t\t{\n");
	sprintf (temp, "%i", score);
	strcat (JsonStr , "\t\t\t\"score\": ");
	strcat (JsonStr , temp);
	strcat (JsonStr , ",\n");

	sprintf (temp, "%i", max_score);
	strcat (JsonStr , "\t\t\t\"max_score\": ");
	strcat (JsonStr , temp);
	strcat (JsonStr , ",\n");


	strcat (JsonStr , "\t\t\t\"output\": ");
	strcat (JsonStr , "\"");
	strcat (JsonStr , output);
	strcat (JsonStr , "\"");
	strcat (JsonStr , "\n");

	strcat (JsonStr , "\t\t}");
	if (!is_final)
		strcat (JsonStr, ",");
	strcat (JsonStr, "\n");

	return 1;
}

int CloseGraderString ()
{
	strcat (JsonStr, "	]\n"); // end of tests
	strcat (JsonStr, "}\n");
	return 1;
}

// test newGame()
int t_newGame () // 8 marks
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;

	tell ("\n*** Checking function newGame ***\n");
	tell ("#Checking it can handle invalid parameters, gridsize<3:");
	r = newGame (2,3);
	if (r == 0)
	{
		m++; // 1
		tell ("Passed\n");
	}
	tell ("#Checking it can handle invalid parameters, gridsize>10:");
	r = newGame (11,3);
	if (r == 0)
	{
		m++; // 1
		tell ("Passed\n");
	}
	tell ("#Checking it can handle invalid parameters, winlength<3:");
	r = newGame (3,2);
	if (r == 0)
	{
		m++; // 1
		tell ("Passed\n");
	}
	tell ("#Checking it can handle invalid parameters, winlength>gridsize:");
	r = newGame (3,4);
	if (r == 0)
	{
		m++; // 1
		tell ("Passed\n");
	}
	tell ("#Checking it does accept valid parameters:");
	r = newGame (6,4);
	if (r == 1)
	{
		m++; // 1
		tell ("Passed\n");
	}
	tell ("#Checking grid is initialised correctly:");
	for (int i = 0 ; i < 6 ; i ++)
	{
		for (int j = 0 ; j < 6; j++)
			if (peek(i,j) != '.')
			{
				fail = 1;
				break;
			}
		if (fail) break;
	}
	if (!fail)
	{
		m+=3;
		tell ("Passed\n");
	}

	sprintf (s,"%i/8 for function newGame", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 8, s, 0);
	return m;
}

// test makeMove
int t_makeMove ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;
	tell ("\n*** Checking function makeMove ***\n");
	tell ("#Checking it can handle invalid parameters\n");
	newGame (4,4);
	r = makeMove (-1,1,'X');
	if (r == 0) m++;
	r = makeMove (5,1,'X');
	if (r == 0) m++;
	r = makeMove (1,-1,'X');
	if (r == 0) m++;
	r = makeMove (1,5,'X');
	if (r == 0) m++;
	makeMove (1,1,'X');
	r = makeMove (1,1,'X'); // return 0 if position is taken
	if (r == 0) m++;
	tell ("#Checking it stores valid moves correctly\n");
	r = makeMove (2,1,'X'); // return 1 on good move
	if (r == 1) m++;
	r = makeMove (0,1,'O');  // O move properly stored
	r = peek (0,1);
	if ((char)r == 'O') m++;
	r = makeMove (2,1,'X');  // X move properly stored
	r = peek (2,1);
	if ((char)r == 'X') m++;

	sprintf (s,"%i/8 for function makeMove", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 8, s, 0);
	return m;
}

// test boardIsFull
int t_boardIsFull ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;
	tell ("\n*** Checking function boardIsFull ***\n");
	// should return 0 when called just after a new game is started, 1m
	newGame(10,4);
	r = boardIsFull ();
	if (r == 0) m++;
	// should return 0 when a board is not full, 1m
	newGame(8,3);
	grid[0][0] = 'X';
	grid[0][1] = 'O';
	grid[2][2] = 'X';
	grid[3][0] = 'X';
	grid[4][4] = 'O';
	grid[7][7] = 'X';
	grid[0][7] = 'O';
	grid[7][0] = 'X';
	r = boardIsFull ();
	if (r == 0) m++;
	// should return 1 when a board is full, 2m
	int c = 0;
	newGame(7,3);
	for (int i = 0; i < 7 ; i++)
		for (int j = 0; j < 7; j++)
		{
			if (c%2 == 0)
				grid[i][j] = 'X';
			else
				grid[i][j] = 'O';
			c++;
		}
	//showGrid();
	r = boardIsFull ();
	if (r == 1) m+=2;

	sprintf (s,"%i/4 for function boardIsFull", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 4, s, 0);
	return m;
}


// test checkHorizontal
int t_checkHorizontal ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;
	tell ("\n*** Checking function checkHorizontal ***\n");
	newGame (8,5);
	r = checkHorizontal ('X', 2); // handle invalid length <3, 1m
	if (r == -1) m++;
	r = checkHorizontal ('O', 9); // handle invalid length > gridsize, 1m
	if (r == -1) m++;
	r = checkHorizontal ('R', 3); // handle invalid symbol, 1m
	if (r == -1) m++;

	// can detect NO win of same symbol?, 2m
	grid[2][1] = 'X';
	grid[2][3] = 'X';
	grid[2][4] = 'X';
	grid[2][5] = 'X';
	grid[2][6] = 'X';
	show();
	r = checkHorizontal ('X', 5);
	if (r==0) m=m+2;

	// can detect a win?, 2m
	grid[4][0] = 'O';
	grid[4][3] = 'O';
	grid[4][4] = 'O';
	grid[4][5] = 'O';
	grid[4][6] = 'O';
	grid[4][7] = 'O';
	show();
	r = checkHorizontal ('O', 5);
	if (r==1) m=m+2;

	// can detect a NO win of mixed symbols?, 1m
	newGame (10,5);
	grid[7][0] = 'O';
	grid[7][1] = 'O';
	grid[7][2] = 'O';
	grid[7][3] = 'O';
	grid[7][4] = 'X';
	grid[7][5] = 'O';
	r = checkHorizontal ('O', 5);
	show();
	if (r==0) m=m+1;

	sprintf (s,"%i/8 for function checkHorizontal", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 8, s, 0);
	return m;

}

// test checkVertical, 4m
int t_checkVertical ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;
	double fm=0;

	tell ("\n*** Checking function checkVertical ***\n");
	newGame (8,5);
	r = checkVertical ('X', 2); // handle invalid length <3, 0.3m
	if (r == -1) fm+=.3;
	r = checkVertical ('O', 9); // handle invalid length > gridsize,  0.3m
	if (r == -1) fm+=.3;
	r = checkHorizontal ('R', 3); // handle invalid symbol,  0.3m
	if (r == -1) fm+=.3;
	if (fm > .5) m++; // round to one mark if  of the tests are ok

	// can detect NO win of same symbol?, 1m
	grid[1][0] = 'X';
	grid[3][0] = 'X';
	grid[4][0] = 'X';
	grid[5][0] = 'X';
	grid[6][0] = 'X';
	r = checkVertical ('X', 5);
	if (r==0) m=m+1;

	// can detect a win?, 1m
	grid[0][7] = 'O';
	grid[3][7] = 'O';
	grid[4][7] = 'O';
	grid[5][7] = 'O';
	grid[6][7] = 'O';
	grid[7][7] = 'O';
	//showGrid();
	r = checkVertical ('O', 5);
	if (r==1) m=m+1;

	// can detect a NO win of mixed symbols?, 1m
	newGame (10,5);
	grid[0][3] = 'O';
	grid[1][3] = 'O';
	grid[2][3] = 'O';
	grid[3][3] = 'O';
	grid[4][3] = 'X';
	grid[5][3] = 'O';
	r = checkVertical ('O', 5);
	//showGrid();
	if (r==0) m=m+1;

	sprintf (s,"%i/4 for function checkVertical", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 4, s, 0);
	return m;
}


// test checkDiagonals
int t_checkDiagonals ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;
	double fm=0;

	tell ("\n*** Checking function checkDiagonals ***\n");
	newGame (8,4);
	r = checkDiagonals ('X', 2); // handle invalid length <3, 0.3m
	if (r == -1) fm+=.3;
	r = checkDiagonals ('O', 9); // handle invalid length > gridsize,  0.3m
	if (r == -1) fm+=.3;
	r = checkDiagonals ('R', 3); // handle invalid symbol,  0.3m
	if (r == -1) fm+=.3;
	if (fm > .5) m++; // round to one mark if  of the tests are ok

	// can detect a win in main diagonal?, 2m
	grid[1][1] = 'X';
	grid[3][3] = 'X';
	grid[4][4] = 'X';
	grid[5][5] = 'X';
	grid[6][6] = 'X';
	//showGrid();
	r = checkDiagonals ('X', 4);
	if (r==1) m=m+2;


	// can detect a win in upper half diagonal?, 2m
	newGame (8,4);
	grid[0][2] = 'O';
	grid[2][4] = 'O';
	grid[3][5] = 'O';
	grid[4][6] = 'O';
	grid[5][7] = 'O';
	//showGrid();
	r = checkDiagonals ('O', 4);
	if (r==1) m=m+2;

	// can detect a win in lower half diagonal?, 1m
	newGame (8,4);
	grid[4][0] = 'O';
	grid[5][1] = 'O';
	grid[6][2] = 'O';
	grid[7][3] = 'O';
	//showGrid();
	r = checkDiagonals ('O', 4);
	if (r==1) m=m+2;

	// should not falsely detect a NO win in main diagonal?, 1m
	newGame (8,4);
	grid[1][1] = 'X';
	grid[3][3] = 'X';
	grid[4][4] = 'O';
	grid[5][5] = 'X';
	grid[6][6] = 'X';
	r = checkDiagonals ('X', 4);
	//showGrid();
	if (r==0) m=m+1;

	sprintf (s,"%i/8 for function checkDiagonals", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 8, s, 0);
	return m;

}

// test checkAntiDiagonals
int t_checkAntiDiagonals ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;

	tell ("\n*** Checking function checkAntiDiagonals ***\n");
	newGame (8,4);

	// can detect a win in antidiagonal?, 1m
	grid[1][6] = 'X';
	grid[3][4] = 'X';
	grid[4][3] = 'X';
	grid[5][2] = 'X';
	grid[6][1] = 'X';
	//showGrid();
	r = checkAntiDiagonals ('X', 4);
	if (r==1) m=m+1;

	// can detect a win in upper anti diagonal?, 1m
	newGame (8,3);
	grid[3][1] = 'O';
	grid[2][2] = 'O';
	grid[1][3] = 'O';
	//showGrid();
	r = checkAntiDiagonals ('O', 3);
	if (r==1) m=m+1;

	// can detect a win in lower anti diagonal?, 1m
	newGame (8,4);
	grid[4][6] = 'O';
	grid[5][5] = 'O';
	grid[6][4] = 'O';
	grid[7][3] = 'O';
	//showGrid();
	r = checkAntiDiagonals ('O', 4);
	if (r==1) m=m+1;

	// should not falsely detect a NO win in anti diagonal?, 1m
	newGame (8,4);
	grid[1][6] = 'X';
	grid[3][4] = 'X';
	grid[4][3] = 'O';
	grid[5][2] = 'X';
	grid[6][1] = 'X';
	r = checkAntiDiagonals ('X', 4);
	//showGrid();
	if (r==0) m=m+1;

	sprintf (s,"%i/4 for function checkAntiDiagonals", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 4, s,0);
	return m;
}

// test playerHasWon
int t_playerHasWon ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;
	double fm=0;

	tell ("\n*** Checking function playerHasWon ***\n");
	tell ("#Checking it can handle invalid parameters\n");
	newGame (8,5);
	r = playerHasWon ('X', 2); // handle invalid length <3, 0.3m
	if (r == -1) fm+=.3;
	r = playerHasWon ('O', 9); // handle invalid length > gridsize,  0.3m
	if (r == -1) fm+=.3;
	r = playerHasWon ('R', 3); // handle invalid symbol,  0.3m
	if (r == -1) fm+=.3;
	if (fm > .5) m++; // round to one mark if  of the tests are ok

	tell ("#Checking it can detect a horizontal win, case 1:");
	newGame (7,4);
	__Check_Count=0;
	grid[4][4] = 'X';
	grid[4][3] = 'X';
	grid[4][2] = 'X';
	grid[4][1] = 'X';
	show ();
	r = playerHasWon ('X',4);
	if (r != 1)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a horizontal win, case 2:");
	newGame (7,4);
	grid[3][3] = 'X';
	grid[3][4] = 'X';
	grid[3][5] = 'X';
	grid[3][6] = 'X';
	show();
	r = playerHasWon ('X',4);
	if (r != 1)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a vertical win, case 1:");
	newGame (10,5);
	grid[3][3] = 'O';
	grid[4][3] = 'O';
	grid[5][3] = 'O';
	grid[6][3] = 'O';
	grid[7][3] = 'O';
	show();
	r = playerHasWon ('O',5);
	if (r != 1)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a vertical no win, case 1:");
	newGame (10,5);
	grid[3][9] = 'O';
	grid[4][9] = 'O';
	grid[5][9] = 'O';
	grid[6][9] = 'O';
	grid[7][9] = 'x';
	grid[8][9] = 'O';
	show();
	r = playerHasWon ('O',5);
	if (r != 0)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a diagonal win, case 1:");
	newGame (10,5);
	grid[2][2] = 'O';
	grid[3][3] = 'O';
	grid[4][4] = 'O';
	grid[5][5] = 'O';
	grid[6][6] = 'O';
	show();
	r = playerHasWon ('O',5);
	if (r != 1)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a diagonal win, case 2:");
	newGame (10,5);
	grid[4][1] = 'O';
	grid[5][2] = 'O';
	grid[6][3] = 'O';
	grid[7][4] = 'O';
	grid[8][5] = 'O';
	show();
	r = playerHasWon ('O',5);
	if (r != 1)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a diagonal no win, case 1:");
	newGame (10,5);
	grid[4][1] = 'O';
	grid[5][2] = 'O';
	grid[6][3] = 'O';
	grid[7][4] = '.';
	grid[8][5] = 'O';
	show();
	r = playerHasWon ('O',5);
	if (r != 0)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect an anti-diagonal win, case 1:");
	newGame (10,5);
	grid[3][6] = 'O';
	grid[2][7] = 'O';
	grid[1][8] = 'O';
	grid[0][9] = 'O';
	grid[4][5] = 'O';
	show();
	r = playerHasWon ('O',5);
	if (r != 1)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect an anti-diagonal NO win, case 1:");
	newGame (10,5);
	grid[3][6] = 'O';
	grid[2][7] = 'O';
	grid[1][8] = 'O';
	grid[0][9] = 'O';
	grid[4][5] = 'X';
	show();
	r = playerHasWon ('O',5);
	if (r != 0)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	if (fail)
		m = 0;
	else
		m = 6;

	sprintf (s,"%i/6 for function playerHasWon", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 6, s,0);
	return m;
}

int t_effPlayerHasWon ()
{
	int r;
	int m=0;
	char s[100];
	int fail = 0;

	tell ("\n*** Checking function effPlayerHasWon ***\n");
	tell ("#Checking it can detect a horizontal win, case 1:");
	newGame (7,4);
	__Check_Count=0;
	grid[4][4] = 'X';
	grid[4][3] = 'X';
	grid[4][2] = 'X';
	grid[4][1] = 'X';
	show ();
	r = effPlayerHasWon (4,3,'X',4);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 1 || __Check_Count == 0 || __Check_Count > 5)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a horizontal win, case 2:");
	__Check_Count=0;
	newGame (7,4);
	grid[3][3] = 'X';
	grid[3][4] = 'X';
	grid[3][5] = 'X';
	grid[3][6] = 'X';
	show();
	r = effPlayerHasWon (3,5,'X',4);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 1 || __Check_Count == 0 || __Check_Count > 5)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a vertical win, case 1:");
	__Check_Count=0;
	newGame (10,5);
	grid[3][3] = 'O';
	grid[4][3] = 'O';
	grid[5][3] = 'O';
	grid[6][3] = 'O';
	grid[7][3] = 'O';
	show();
	r = effPlayerHasWon (3,3,'O',5);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 1 || __Check_Count == 0 || __Check_Count > 9)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a vertical no win, case 1:");
	__Check_Count=0;
	newGame (10,5);
	grid[3][9] = 'O';
	grid[4][9] = 'O';
	grid[5][9] = 'O';
	grid[6][9] = 'O';
	grid[7][9] = 'x';
	grid[8][9] = 'O';
	show();
	r = effPlayerHasWon (4,9,'O',5);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 0 || __Check_Count == 0 || __Check_Count > 12)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a diagonal win, case 1:");
	__Check_Count=0;
	newGame (10,5);
	grid[2][2] = 'O';
	grid[3][3] = 'O';
	grid[4][4] = 'O';
	grid[5][5] = 'O';
	grid[6][6] = 'O';
	show();
	r = effPlayerHasWon (3,3,'O',5);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 1 || __Check_Count == 0 || __Check_Count > 12)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a diagonal win, case 2:");
	__Check_Count=0;
	newGame (10,5);
	grid[4][1] = 'O';
	grid[5][2] = 'O';
	grid[6][3] = 'O';
	grid[7][4] = 'O';
	grid[8][5] = 'O';
	show();
	r = effPlayerHasWon (8,5,'O',5);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 1 || __Check_Count == 0 || __Check_Count > 12)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect a diagonal no win, case 1:");
	__Check_Count=0;
	newGame (10,5);
	grid[4][1] = 'O';
	grid[5][2] = 'O';
	grid[6][3] = 'O';
	grid[7][4] = '.';
	grid[8][5] = 'O';
	show();
	r = effPlayerHasWon (8,5,'O',5);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 0 || __Check_Count == 0 || __Check_Count > 12)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect an anti-diagonal win, case 1:");
	__Check_Count=0;
	newGame (10,5);
	grid[3][6] = 'O';
	grid[2][7] = 'O';
	grid[1][8] = 'O';
	grid[0][9] = 'O';
	grid[4][5] = 'O';
	show();
	r = effPlayerHasWon (4,5,'O',5);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 1 || __Check_Count == 0 || __Check_Count > 15)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");

	tell ("#Checking it can detect an anti-diagonal NO win, case 1:");
	__Check_Count=0;
	newGame (10,5);
	grid[3][6] = 'O';
	grid[2][7] = 'O';
	grid[1][8] = 'O';
	grid[0][9] = 'O';
	grid[4][5] = 'X';
	show();
	r = effPlayerHasWon (3,6,'O',5);
	if (Presubmission)
			printf (" Made %i checks, ", __Check_Count);
	if (r != 0 || __Check_Count == 0 || __Check_Count > 14)
	{
		fail = 1;
		tell ("Failed\n");
	}
	else
		tell ("Passed\n");


	if (fail)
		m = 0;
	else
		m = 6;

	sprintf (s,"%i/6 for function effPlayerHasWon", m);

	if (Presubmission)
		printf ("%s\n", s);
	else
		AddTestString (m, 6, s, 0);
	return m;
}

void test_showGrid ()
{
	if (!Presubmission || stage == 2)  // do not show the grid when it is a pre-submission or not 2nd stage
	{
		newGame (7,4);
		grid[4][1] = 'O';
		grid[5][2] = 'O';
		grid[6][3] = 'O';
		grid[6][4] = 'X';
		grid[4][5] = 'O';
		grid[6][0] = 'X';
		grid[1][6] = 'X';
		showGrid ();
	}
}


#ifdef TEST
int main (int argc, char* argv[])
{
	FILE* jsonFile;
	int tot = 0;

	if (argc > 1 && !strcmp(argv[1], "s"))
		mustShow= 1;

	if (argc > 1 && !strcmp(argv[1], "2"))
		stage = 2;

	if (argc > 1 && !strcmp(argv[1], "3"))
		stage = 3;


	if (!Presubmission && stage == 1)
		InitGraderString ();

	tell ("\n\n\t$$$ Checking your functions, behold $$$\n");
	tell ("\t=========================================\n");
	tell ("Started ...\n");

	if (stage == 1)
	{
		tot += t_newGame ();
		tot += t_makeMove ();
		tot += t_boardIsFull ();
		tot += t_checkHorizontal();
		tot += t_checkVertical ();
		tot += t_checkDiagonals ();
		tot += t_checkAntiDiagonals ();
		tot += t_playerHasWon ();
		tot += t_effPlayerHasWon ();
	}

	if (stage == 2)
		test_showGrid ();

	if (Presubmission && stage == 1)
	{
		printf ("\n---------------------------------------------------\n");
		printf ("\t\tTotal mark = %i/56\n", tot);
		printf ("---------------------------------------------------\n\n");
	}
	tell ("Finished\n");


	if (!Presubmission && stage ==1)  // create the results.json file
	{
		CloseGraderString ();
		jsonFile = fopen ("results.json", "w");
		fprintf (jsonFile, "%s", JsonStr);
		fclose (jsonFile);
	}
	return 0;
}
#endif
