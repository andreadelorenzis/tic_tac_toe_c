#include <stdio.h>
#include <stdlib.h>

void stampaTris(int matrice[][3])
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

void sceltaSegno(int *segnoGiocatore1,
				 int *segnoGiocatore2)
{
	char segno;
	
	// inserimento del segno del player 1. Il segno del player 2 sarà quello rimanente
	do
	{
		printf("\nPlayer 1 scegli il segno tra O e X: ");
		scanf("%c",
			  &segno);
		printf("\n");
		if(segno != 'O' && segno != 'X')
		{
			   printf("Valore non valido. Riprova.\n");
		}
		else 
		{
			if(segno == 'O')
			{
				*segnoGiocatore1 = 2;
				*segnoGiocatore2 = 1;
			}
			else if(segno == 'X')
			{
				*segnoGiocatore1 = 1;
				*segnoGiocatore2 = 2;
			}
		}
		while(getchar() != '\n');
	}
	while(segno != 'O' && segno != 'X');
}

/* il player inserisce la posizione, e il segno scelto a inizio partita verrà messo in quella posizione. 

Questo è il sistema posizionale, e il player corrente deve mettere una stringa di 2 caratteri contenenti una lettera A-C e un numero 1-3, senza spazi in mezzo. 
  1 2 3
A 0 X 0
B X 0 X
C 0 X 0

*/

void inserisciSegno(int matrice[][3], int player, int segnoGiocatore)
{
	char posizione[10];
	char letteraRiga;
	int riga;
	int colonna;

		printf("Player %d scegli la posizione del prossimo segno: ",
			   player);
		scanf("%s",
			  posizione);
		printf("\n");
		letteraRiga = posizione[0];
		colonna = atoi(&posizione[1]);
		
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
		switch(colonna)
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
				
		matrice[riga][colonna] = segnoGiocatore;
}

// cerca un segno in 3 posizioni consecutive, nelle 3 direzioni possibili

int cercaTripletta(int matrice[][3], int segnoGiocatore)
{
	int ricercaOrizz = 0;
	int ricercaVert = 0;
	int ricercaObliq = 0;
	
	/*cercaOrizzontale: itero riga per riga*/
	
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
	
    /*cercaVerticale: itero colonna per colonna*/
	
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
	
    /*cercaObliquo: itero 3 volte aumentando contemporaneamente riga e colonna
					itero 3 volte partendo da colonna = 3, riga = 0, e diminuisco colonna ed aumento riga ad ogni iterazione*/

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

//O = 2, X = 1
int main(void)
{
	int playerCorrente = 1;
	int segnoGiocatoreCorrente;
	int segnoGiocatore1;
	int segnoGiocatore2;
	int vittoria = 0;
	int segni[3][3];
		
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