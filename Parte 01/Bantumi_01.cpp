//################################################################################################################################################################//
//############################################################|--------------------------------------|############################################################//
//############################################################| BANTUMI - PROGETTO DI PROGRAMMAZIONE |############################################################//
//############################################################|--------------------------------------|############################################################//
//################################################################################################################################################################//



#include <iostream>
#include <fstream>
using namespace std;

main()
{
	ifstream IN("input");
	ofstream OUT("output");
	
	if (IN && OUT)
	{
		int B[2][7];	//L'array B identifica il tavolo da gioco!
						//Il tavolo è definito come da figura nel PDF con le richieste della PRIMA PARTE della realizzazione del "Progetto - Bantumi"!
						
						/*   B[0][0..5] --> Rappresentano le "buche piccole" (ovvero quelle che all'inizio del gioco (reale) contengono un numero prefissato
						di ceci) del PLAYER 0, mentre B[0][6] rappresenterà la "buca grande" (ovvero quella per il punteggio finale) del PLAYER 0   */
						
						/*   B[1][0..5] --> Rappresentano le "buche piccole" (ovvero quelle che all'inizio del gioco (reale) contengono un numero prefissato
						di ceci) del PLAYER 1, mentre B[1][6] rappresenterà la "buca grande" (ovvero quella per il punteggio finale) del PLAYER 1   */
		
		
		//Fase 1: Preparo le buche con dei valori letti dal file "input"...
		for (int i=0; i<2; i++)
			for (int j=0; j<7; j++)
				IN>>B[i][j];
		
		
		//Fase 2: Stampo a schermo con l'istruzione "cout" una semplice rappresentazione del tavolo da gioco con i rispettivi valori di B nei posti giusti...
		//Scegliere una delle due possibilità di TAVOLO DA GIOCO ("BEN FATTO" o "MINIMALISTA") e mettere fra commenti l'altro!!!
		
		//TAVOLO DA GIOCO BEN FATTO:
		cout<<endl;
		
		cout<<"      ";
		
		for (int play0=5; play0>=0; play0--)	//play0 --> Player_0
		{
			if (B[0][play0] >= 0 && B[0][play0] < 10)
				cout<<"|0"<<B[0][play0]<<"| ";
			else
				cout<<"|"<<B[0][play0]<<"| ";
		}
		
		cout<<endl<<endl;
		
		if (B[0][6] >= 0 && B[0][6] < 10)
			cout<<"*0"<<B[0][6]<<"* ";
		else
			cout<<"*"<<B[0][6]<<"* ";
		
		cout<<"-------------------------------"<<endl;
		cout<<"     -------------------------------";
		
		if (B[1][6] >= 0 && B[1][6] < 10)
			cout<<" *0"<<B[1][6]<<"*"<<endl<<endl;
		else
			cout<<" *"<<B[1][6]<<"*"<<endl<<endl;
		
		cout<<"      ";
		
		for (int play1=0; play1<6; play1++)		//play1 --> Player_1
		{
			if (B[1][play1] >= 0 && B[1][play1] < 10)
				cout<<"|0"<<B[1][play1]<<"| ";
			else
				cout<<"|"<<B[1][play1]<<"| ";
		}
		
		cout<<endl<<endl<<endl;
		
		
		//TAVOLO DA GIOCO MINIMALISTA:
		/*
		for (int play0=6; play0>=0; play0--)	//play0 --> Player_0
			cout<<B[0][play0]<<" ";
		
		cout<<endl;
		
		for (int play1=0; play1<7; play1++)		//play1 --> Player_1
			cout<<B[1][play1]<<" ";
		
		cout<<endl;
		*/
		
		
		/*Fase 3: Stampo nel file "output" il contenuto di B, seguendo lo schema di stampa della fase 2...
					Quindi: Prima il PLAYER 0, partendo dalla sua "buca grande" e terminando con la sua "buca piccola" di indice 0;
					E poi, a capo, il PLAYER 1, partendo dalla sua "buca piccola" di indice 0, e concludendo con la sua "buca grande"!   */
		
		for (int play0=6; play0>=0; play0--)	//play0 --> Player_0
			OUT<<B[0][play0]<<" ";
		
		OUT<<endl;
		
		for (int play1=0; play1<7; play1++)		//play1 --> Player_1
			OUT<<B[1][play1]<<" ";
		
		OUT<<endl;
		
		
		IN.close();
		OUT.close();
	}
	else
	{
		cout<<"Errore causato dai file!";
	}
	
	
}
