//################################################################################################################################################################//
//############################################################|--------------------------------------|############################################################//
//############################################################| BANTUMI - PROGETTO DI PROGRAMMAZIONE |############################################################//
//############################################################|--------------------------------------|############################################################//
//################################################################################################################################################################//



#include <iostream>
#include <fstream>
using namespace std;


//PRE=(B contiene 14 valori non negativi, OUT è lo stream di output per il file "output")
void stampaTavolo (ofstream & OUT, int (*B)[7])
{
	/* Stampo nel file "output" il contenuto di B (ovvero l'attuale configurazione del tavolo da gioco).
	Quindi: Prima il PLAYER 0, partendo dalla sua "buca grande" e terminando con la sua "buca piccola" di indice 0;
	E poi, a capo, il PLAYER 1, partendo dalla sua "buca piccola" di indice 0, e concludendo con la sua "buca grande"! */
	
	//cout<<"Player 0"<<endl;
	
	for (int play0=6; play0>=0; play0--)	//play0 --> Player_0
	{
		OUT << *(*(B+0)+play0) <<" ";
		//cout << *(*(B+0)+play0) <<"     ";
	}
	
	/*if (*(*(B+0)+6) < 10)
		cout<<endl<<"      ";
	else
		cout<<endl<<"       ";*/
	
	for (int play1=0; play1<7; play1++)		//play1 --> Player_1
	{
		OUT << *(*(B+1)+play1) <<" ";
		//cout << *(*(B+1)+play1) <<"     ";
	}
	
	OUT<<endl;
	//cout<<endl<<"Player 1"<<endl<<endl;
}
//POST=("output" contiene il contenuto dell'array B nel modo richiesto nel testo di "Bantumi 1" (ovvero ricopiato nel commento qui sopra))


//PRE=('p'=0/1)
void scambia (int & p)
{
	//Inverto il giocatore, se prima era 0 ora sarà 1, se prima era 1 ora sarà 0...!
	if (p==0)
		p=1;
	else
		p=0;
}
//POST=(Inverte il valore di 'player', se era 0 diventa 1, se era 1 diventa 0)


//PRE=(B contiene 14 valori non negativi, 'player'=0/1, 'bucaVuota' in [0..5]. E chiamiamo 'old_B' il valore di B all'invocazione della funzione)
void beansStolen (int (*B)[7], int oldPlayer, int player, int bucaVuota)
{
	scambia(player);	//Spostiamoci nel campo del giocatore opposto alla 'bucaVuota' in cui abbiamo terminato la semina!
	
	
	/* Mi serve una funzione che mi calcoli l'indice della buca piccola del lato OPPOSTO al tavolo... Conoscendo solamente l'indice 'bucaVuota'!
	Ovvero: "F(bucaVuota)=bucaOpposta" ==> Nel concreto: F(0)=5, F(1)=4, F(2)=3, F(3)=2, F(4)=1, F(5)=0
	2 sono le funzioni che per prime vengono in mente: "|bucaVuota-5|=bucaOpposta" oppure "5-bucaVuota=bucaOpposta", optiamo per la seconda! */
	
	int fagioliBucaOpposta=*(*(B+player)+(5-bucaVuota));	//Prendiamo i fagioli dalla buca che si trova dal lato opposto in corrispondenza a 'bucaVuota'!
	
	*(*(B+player)+(5-bucaVuota))=0;		//Dopo aver "rubato" i fagioli, resettiamo a 0 tale buca!
	
	
	if (player != oldPlayer)	//In quale campo sono stati "rubati" i fagioli? --> Mi sposto, se necessario, nel lato del player che sta eseguendo la mossa!
		scambia(player);
	
	//'oldPlayer' (il giocatore fautore del furto) aggiunge i fagioli "rubati" e il suo ultimo fagiolo (mai depositato nella buca vuota incontrata al termine
	//della sua semina) nella sua buca grande, e così termina il suo turno!
	*(*(B+player)+6)=(*(*(B+player)+6))+fagioliBucaOpposta+1;
}
//POST=(B è ottenuta da 'old_B' eseguendo la mossa descritta nel testo "Bantumi 2" nel caso in cui una semina termini in una buca piccola VUOTA)


//PRE=(B contiene 14 valori non negativi, 'player'=0/1, 'buca' in [0..5], 'fagioli'>0. E chiamiamo 'old_B' il valore di B all'invocazione della funzione)
bool semina (int B[][7], int player, int buca, int fagioli)
{
	//Resetto a 0 (zero) la buca piccola da cui ho appena pescato i fagioli per eseguire la mossa (player, buca)...
	*(*(B+player)+buca)=0;
	
	int i=buca+1;			//Imposto un indice 'i' nella prima buca in cui dovrò iniziare la semina dei 'fagioli' contenuti in 'buca'!
	int oldPlayer=player;	//Mi salvo in una variabile temporanea il giocatore che sta eseguendo la mossa (player, buca)!
	
	//Ora inizio la semina dei 'fagioli' che 'player' ha prelevato da 'buca', fino all'esaurimento di questi ultimi...
	for ( ; fagioli>0; fagioli--)
	{
		//Se incontro la buca grande dell'avversario di 'oldPlayer', devo saltarla senza aggiungere alcun fagiolo; resettare 'i' a 0, e cambiare 'player'!
		if (i==6 && player != oldPlayer)	//B[0][6] (Player 0) && B[1][6] (Player 1) identificano le due BUCHE GRANDI!
		{
			scambia(player);
			i=0;
		}
		//Per proseguire la semina DOPO avere superato la buca grande del giocatore 'oldPlayer', devo resettare 'i' a 0, e cambiare 'player'!
		else
		{
			if (i==7)
			{
				scambia(player);
				i=0;
			}
		}
		
		//Se termino la semina in una buca vuota (DIVERSA dalla buca grande di 'oldPlayer'), devo agire come richiesto dal testo "Bantumi 2";
		//in caso contrario proseguo con la semina nella prossima buca...!
		if (fagioli==1 && i != 6 && *(*(B+player)+i) == 0)
			beansStolen(B, oldPlayer, player, i);
		else
			*(*(B+player)+i)=(*(*(B+player)+i))+1;
		
		i++;
	}
	
	bool playAgain=false;		//'playAgain' => FALSE se il prossimo giocatore a giocare sarà DIVERSO dall'attuale 'player', altrimenti TRUE!
	
	if ((i-1)==6)			//Se 'player' ha seminato l'ultimo fagiolo nella sua buca grande, la prossima mossa spetta ancora a lui!
		playAgain=true;
	
	return playAgain;
}
//POST=(B è ottenuta da 'old_B' eseguendo la mossa (player, buca) secondo le regole del gioco descritte nel testo. Restituisce true se e solo se alla fine
//della semina si verifica il caso: La semina del giocatore che sta muovendo termina nella sua buca grande; altrimenti false)


main()
{
	ifstream IN("input");
	ofstream OUT("output");
	
	if (IN && OUT)
	{
		//PRE=("input" contiene 14 interi non negativi seguiti da coppie di interi non negativi, e contiene anche una coppia con seconda componente uguale a -1;
		//inoltre: (p=0/1) identifica il giocatore, e b identifica la buca nella quale p effettuerà la sua mossa)
		
		int B[2][7];	//L'array B identifica il tavolo da gioco!
						//Il tavolo è definito come da figura nel PDF con le richieste della PRIMA PARTE della realizzazione del "Progetto - Bantumi"!
						
						/*   B[0][0..5] --> Rappresentano le "buche piccole" del PLAYER 0, mentre B[0][6] rappresenterà la "buca grande" (ovvero quella per
						il punteggio finale) del PLAYER 0   */
						
						/*   B[1][0..5] --> Rappresentano le "buche piccole" del PLAYER 1, mentre B[1][6] rappresenterà la "buca grande" (ovvero quella per
						il punteggio finale) del PLAYER 1   */
		
		
		
		//Fase 1: Preparo le buche con i valori letti dal file "input"...
		for (int i=0; i<2; i++)
			for (int j=0; j<7; j++)
				IN>>B[i][j];
		
		
		//Fase 2: Ciclo che mi scorre tutte le rispettive coppie (p, b) lette da "input" e stampa su "output" tutti i punti previsti dalla POST del programma.
		//Il ciclo terminerà solamente quando verrà letto b=-1, e dopo il ciclo sarà stampato su "output" la consueta stringa "fine"!
		
		//Stampo la configurazione iniziale del tavolo da gioco...
		stampaTavolo(OUT, B);
		
		//Leggo la prima coppia (p, b) => Se b==-1 NON entro nel ciclo e termino con "fine", altrimenti entro nel ciclo e proseguo...
		int p, b;
		IN>>p>>b;
		
		bool stop=false;
		
		if (b==-1)		//Se b==-1 il gioco deve teminare, senza effettuare alcuna altra lettura e/o scrittura (eccetto la stampa della stringa "fine")!
			stop=true;
		
		for ( ; stop==false; )
		{
			OUT<<p<<" "<<b<<endl;		//Stampo, ad coppia (p, b), solamente se b != -1, tale coppia su "output"!
			//cout<<p<<" "<<b<<endl;
			
			int fagioli=B[p][b];		//Leggo quanti fagioli contiene la buca b del player p che sta eseguendo la mossa (p, b)!
			
			if (fagioli != 0)		//Se la buca selezionata è vuota, devo procedere alla lettura della prossima mossa (p, b) da "input"!
			{
				bool changePlay=semina(B, p, b, fagioli);		//"Change_Player" ==> Mi tiene conto di chi sarà il prossimo giocatore a dover muovere!
				
				stampaTavolo(OUT, B);		//Stampo a video la nuova configurazione del tavolo dopo l'esecuzione della mossa (p, b)!
				
				if (changePlay)
				{
					OUT<<"il giocatore non cambia"<<endl;	//Stampo tale stringa se la prossima mossa DOVREBBE essere a carico dello stesso giocatore (p)!
					//cout<<"il giocatore non cambia"<<endl;
				}
				else
				{
					OUT<<"il giocatore cambia"<<endl;		//Stampo tale stringa se la prossima mossa DOVREBBE essere a carico del giocatore avversario a (p)!
					//cout<<"il giocatore cambia"<<endl;
				}
			}
			
			IN>>p>>b;			//Leggo la prossima mossa (p, b) che dovrà essere effettuata!
			
			if (b==-1)			//Se la coppia appena letta contiene b==-1, fermo il gioco!
				stop=true;
		}
		
		OUT<<"fine"<<endl;		//Stampo alla fine di "output" la consueta stringa "fine" che segna la terminazione del file!
		//cout<<"fine"<<endl;
		
		
		IN.close();
		OUT.close();
		
		/*
		POST=("output" contiene le seguenti cose:
		1) La configurazione di gioco iniziale;
		2) Per ogni coppia (p,b) letta da "input" e tale che b !=-1, i 2 interi p e b vanno scritti su "output" e, nel caso la buca b del giocatore p non sia
		   vuota, "output" deve contenere la nuova configurazione raggiunta eseguendo la mossa (p,b).
		Se invece la buca b del giocatore p è vuota, la configurazione non cambia e quindi non va riscritta su "output";
		3) Dopo ciascuna nuova configurazione va scritta anche la frase "il giocatore cambia" oppure "il giocatore non cambia" a seconda che la semina
		   corrispondente alla mossa effettuata finisca o no nel caso: La semina del giocatore che sta muovendo termina nella sua buca grande.
		   [Va ricordato che in entrambi i casi il prossimo giocatore che deve muovere è deciso sempre dalla prossima coppia che viene letta da "input"];
		4) Il file "output" termina sempre con la stringa "fine".)
		*/
	}
	else
	{
		cout<<"Errore causato dai file!";
	}
	
	
}
