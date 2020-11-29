/*
	To do:
	+ affrontare il caso in cui l'utente mette il segno in una posizione già occupata.
*/


#include <stdio.h>
#include <stdlib.h>

/*
	Print the matrix of signs.
*/

void print_matrix (int matrix[][3])  /* input: matrix of signs */
{
	printf("    1   2   3\n");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(i == 0 && j == 0)
				printf(" a ");
			if(i == 1 && j == 0)
				printf(" b ");
			if(i == 2 && j == 0)
				printf(" c ");
			
			if(matrix[i][j] == 1) 
				printf(" X");
			else if(matrix[i][j] == 2)
				printf(" O");
			else 
				printf("  ");
			if(j != 2)
				printf(" |");
		}
		if(i != 2)
			printf("\n   -----------\n");
	}
	printf("\n\n");
}

/*
	Choose the sign of player 1. Player 2 will have the other sign.
*/

void choose_signs(int *player1_sign,   /* output: player 1 sign */
				  int *player2_sign)   /* output: player 2 sign */
{
	char sign;          /* input: sign chosen by player 1 */
	int input_result;   /* work:  return value from reading input with scanf */
	
	do
	{
		printf("\nPlayer 1 choose a sign between O and X: ");
		input_result = scanf("%c",
			  &sign);
		printf("\n");
		if((sign != 'O' && sign != 'o' && sign != 'X' && sign != 'x') ||
			input_result != 1)
		{
			   printf("Value not valid. Retry.\n");
		}
		else 
		{
			if(sign == 'O' || sign == 'o')
			{
				*player1_sign = 2;
				*player2_sign = 1;
			}
			else if(sign == 'X' || sign == 'x')
			{
				*player1_sign = 1;
				*player2_sign = 2;
			}
		}
		while(getchar() != '\n');
	}
	while((sign != 'O' && sign != 'o' && sign != 'X' && sign != 'x') ||
		   input_result != 1);
}

/* 
	The current player chooses the position in which his sign will be placed. 
	This is the positional system:
	  1 2 3
	A 0 X 0
	B X 0 X
	C 0 X 0
	The player must write a string of 2 characters (letter a-c and number 1-3) that represent the coordinates. 
*/

void add_sign(int matrix[][3],      /* output: matrix of signs */
			  int player, 		    /* input: current player */	
			  int player_sign)      /* input: current player sign */
{
	char position[10];    /* input: string containing the coordinates (a-c)(1-3) */
	char row_letter;      /* work:  character representing the row */
	int  row = -1;		  /* work:  index of row */	
	int  column_index;    /* work:  number representing the column */
	int  column = -1;     /* work:  index of column */
	int  input_result;    /* work:  return value from reading input with scanf */

		do
		{
			printf("Player %d choose the next position: ",
				   player);
			input_result = scanf("%s",
				  position);
			printf("\n");
			row_letter = position[0];
			column_index = atoi(&position[1]);
			switch(row_letter)
			{
				case 'a':
					row = 0;
					break;
				case 'b':
					row = 1;
					break;
				case 'c':
					row = 2;
					break;
			}
			switch(column_index)
			{
				case 1:
					column = 0;
					break;
				case 2:
					column = 1;
					break;
				case 3:
					column = 2;
					break;
			}		
			if((row == -1 || column == -1) || input_result != 1)
			{
				printf("Position not valid. Retry.\n\n");
			}
			while(getchar() != '\n');
		}
		while((row == -1 || column == -1) || input_result != 1);
		matrix[row][column] = player_sign;
}

// For a given sign, search a sequence of 3 consecutive positions containing the sign. 

int search_sequence(int matrix[][3],    /* input: matrix of signs */
				   int player_sign)  /* input: currenct player sign */
{
	int horizontal_search = 0;   /* output: sequence found horizontaly */
	int vertical_search = 0;     /* output: sequence found vertically */
	int diagonal_search = 0;     /* output: sequence found diagonally */
	
	/* search horizontaly: iterate elements one row at a time. */
	
	for(int i = 0; i < 3; i++)
	{
		int count = 0;
		for(int j = 0; j < 3; j++)
		{
			if(matrix[i][j] == player_sign)
				count++;
		}
		if(count == 3)
		{
			horizontal_search = 1;
		}
		else 
			count = 0;
	}
	
    /* search vertically: iterate elements one column at a time. */
	
	for(int i = 0; i < 3; i++)
	{
		int count = 0;
		for(int j = 0; j < 3; j++)
		{
			if(matrix[j][i] == player_sign)
				count++;
		}
		if(count == 3)
		{
			vertical_search = 1;
		}
		else 
			count = 0;
	}
	
    /* search diagonally: (1) iterate 3 times and for each iteration add one to both row and column.
					      (2) iterate 3 times, starting from row 0, column 2, and for each iteration 
						      subtract one to column and add one to row. */

	int count = 0;
	for(int i = 0, j = 0; i < 3; i++, j++)
	{
		if(matrix[i][j] == player_sign)
			count++;
		if(count == 3)
		{
			diagonal_search = 1;
		}
	}
	count = 0;
	for(int i = 0, j = 2; i < 3; i++, j--)
	{
		if(matrix[i][j] == player_sign)
			count++;
		if(count == 3)
		{
			diagonal_search = 1;
		}
	}
	  
	 return horizontal_search || vertical_search || diagonal_search;
}

int main(void)
{
	int player1_sign;         /* input: sign associated to player 1 */
	int player2_sign;		 /* input: sign associated to playe 2 */
	int current_player = 1;      /* work:  current player. 1 is player one, 2 is player two. Player 1 begins. */
	int current_player_sign;  /* work:  current player sign. */
	int victory = 0;			 /* work:  boolean variable for victory. */
	int signs[3][3];  			 /* output: matrix of signs */
		
	choose_signs(&player1_sign, 
				&player2_sign);
	current_player_sign = player1_sign;
	print_matrix(signs);
		   
	while(!victory)
	{
		add_sign(signs, current_player ,current_player_sign);
		print_matrix(signs);
		victory = search_sequence(signs, current_player_sign);
		if(victory) 
		{
			printf("Player%d ha vinto.", current_player);
		}
		if(current_player == 1)
		{
			current_player = 2;
			current_player_sign = player2_sign;
		}
		else 
		{
			current_player = 1;
			current_player_sign = player1_sign;
		}
	}
	return (0);
}