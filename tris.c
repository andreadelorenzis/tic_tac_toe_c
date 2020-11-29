#include <stdio.h>
#include <stdlib.h>

/*
	Print the matrix of signs.
*/

void stampaTris(int matrice[][3])  /* input: matrix of signs */
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
			
			if(matrice[i][j] == 1) 
				printf(" X");
			else if(matrice[i][j] == 2)
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

void sceltaSegno(int *segnoGiocatore1,   /* output: player 1 sign */
				 int *segnoGiocatore2)   /* output: player 2 sign */
{
	char segno;          /* input: sign chosen by player 1 */
	int esito_lettura;   /* work:  return value from reading input with scanf */
	
	do
	{
		printf("\nPlayer 1 scegli il segno tra O e X: ");
		esito_lettura = scanf("%c",
			  &segno);
		printf("\n");
		if((segno != 'O' && segno != 'o' && segno != 'X' && segno != 'x') ||
			esito_lettura != 1)
		{
			   printf("Valore non valido. Riprova.\n");
		}
		else 
		{
			if(segno == 'O' || segno == 'o')
			{
				*segnoGiocatore1 = 2;
				*segnoGiocatore2 = 1;
			}
			else if(segno == 'X' || segno == 'x')
			{
				*segnoGiocatore1 = 1;
				*segnoGiocatore2 = 2;
			}
		}
		while(getchar() != '\n');
	}
	while(segno != 'O' && segno != 'o' && segno != 'X' && segno != 'x');
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

void inserisciSegno(int matrice[][3],     /* output: matrix of signs */
					int player, 		  /* input: current player */	
					int segnoGiocatore)   /* input: current player sign */
{
	char posizione[10];    /* input: string containing the coordinates (a-c)(1-3) */
	char letteraRiga;      /* work:  character representing the row */
	int  riga = -1;		   /* work:  index of row */	
	int  indiceColonna;    /* work:  number representing the column */
	int  colonna = -1;     /* work:  index of column */
	int  esito_lettura;    /* work:  return value from reading input with scanf */

		do
		{
			printf("Player %d scegli la posizione del prossimo segno: ",
				   player);
			esito_lettura = scanf("%s",
				  posizione);
			printf("\n");
			letteraRiga = posizione[0];
			indiceColonna = atoi(&posizione[1]);
			switch(letteraRiga)
			{
				case 'a':
					riga = 0;
					break;
				case 'b':
					riga = 1;
					break;
				case 'c':
					riga = 2;
					break;
			}
			switch(indiceColonna)
			{
				case 1:
					colonna = 0;
					break;
				case 2:
					colonna = 1;
					break;
				case 3:
					colonna = 2;
					break;
			}		
			if((riga == -1 || colonna == -1) || esito_lettura != 1)
			{
				printf("Posizione non valida. Riprova.\n\n");
			}
			while(getchar() != '\n');
		}
		while((riga == -1 || colonna == -1) || esito_lettura != 1);
		printf("Riga: %d, colonna: %d\n", riga, colonna);
		matrice[riga][colonna] = segnoGiocatore;
}

// For a given sign, search a sequence of 3 consecutive positions containing the sign. 

int cercaTripletta(int matrice[][3],    /* input: matrix of signs */
				   int segnoGiocatore)  /* input: currenct player sign */
{
	int ricercaOrizz = 0;   /* output: sequence found horizontaly */
	int ricercaVert = 0;    /* output: sequence found vertically */
	int ricercaObliq = 0;   /* output: sequence found diagonally */
	
	/* search horizontaly: iterate elements one row at a time. */
	
	for(int i = 0; i < 3; i++)
	{
		int conteggio = 0;
		for(int j = 0; j < 3; j++)
		{
			if(matrice[i][j] == segnoGiocatore)
				conteggio++;
		}
		if(conteggio == 3)
		{
			ricercaOrizz = 1;
		}
		else 
			conteggio = 0;
	}
	
    /* search vertically: iterate elements one column at a time. */
	
	for(int i = 0; i < 3; i++)
	{
		int conteggio = 0;
		for(int j = 0; j < 3; j++)
		{
			if(matrice[j][i] == segnoGiocatore)
				conteggio++;
		}
		if(conteggio == 3)
		{
			ricercaVert = 1;
		}
		else 
			conteggio = 0;
	}
	
    /* search diagonally: (1) iterate 3 times and for each iteration add one to both row and column.
					      (2) iterate 3 times, starting from row 0, column 2, and for each iteration 
						      subtract one to column and add one to row. */

	int conteggio = 0;
	for(int i = 0, j = 0; i < 3; i++, j++)
	{
		if(matrice[i][j] == segnoGiocatore)
			conteggio++;
		if(conteggio == 3)
		{
			ricercaObliq = 1;
		}
	}
	conteggio = 0;
	for(int i = 0, j = 2; i < 3; i++, j--)
	{
		if(matrice[i][j] == segnoGiocatore)
			conteggio++;
		if(conteggio == 3)
		{
			ricercaObliq = 1;
		}
	}
	  
	 return ricercaOrizz || ricercaVert || ricercaObliq;
}

int main(void)
{
	int segnoGiocatore1;         /* input: sign associated to player 1 */
	int segnoGiocatore2;		 /* input: sign associated to playe 2 */
	int playerCorrente = 1;      /* work:  current player. 1 is player one, 2 is player two. Player 1 begins. */
	int segnoGiocatoreCorrente;  /* work:  current player sign. */
	int vittoria = 0;			 /* work:  boolean variable for victory. */
	int segni[3][3];  			 /* output: matrix of signs */
		
	sceltaSegno(&segnoGiocatore1, 
				&segnoGiocatore2);
	segnoGiocatoreCorrente = segnoGiocatore1;
	stampaTris(segni);
		   
	while(!vittoria)
	{
		inserisciSegno(segni, playerCorrente ,segnoGiocatoreCorrente);
		stampaTris(segni);
		vittoria = cercaTripletta(segni, segnoGiocatoreCorrente);
		if(vittoria) 
		{
			printf("Player%d ha vinto.", playerCorrente);
		}
		if(playerCorrente == 1)
		{
			playerCorrente = 2;
			segnoGiocatoreCorrente = segnoGiocatore2;
		}
		else 
		{
			playerCorrente = 1;
			segnoGiocatoreCorrente = segnoGiocatore1;
		}
	}
	return (0);
}