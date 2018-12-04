//############################################################################################################################################################//
//##########################################################|--------------------------------------|##########################################################//
//##########################################################| BANTUMI - PROGETTO DI PROGRAMMAZIONE |##########################################################//
//##########################################################|--------------------------------------|##########################################################//
//############################################################################################################################################################//



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
		OUT << *(*(B+0)+play0) << " ";
		//cout << *(*(B+0)+play0) << "     ";
	}
	
	/*if (*(*(B+0)+6) < 10)
		cout<<endl<<"      ";
	else
		cout<<endl<<"       ";*/
	
	for (int play1=0; play1<7; play1++)		//play1 --> Player_1
	{
		OUT << *(*(B+1)+play1) << " ";
		//cout << *(*(B+1)+play1) << "     ";
	}
	
	OUT<<endl;
	//cout<<endl<<"Player 1"<<endl<<endl<<endl;
}
//POST=("output" contiene il contenuto dell'array B nel modo richiesto nel testo di "Bantumi 1" (ovvero ricopiato nel commento qui sopra))


//PRE=('p'=0/1)
int scambia (int p)
{
	//Inverto il giocatore, se prima era 0 ora sarà 1, se prima era 1 ora sarà 0...!
	if (p==0)
		p=1;
	else
		p=0;
	
	return p;
	
	//L'intero corpo della funzione può essere ugualmente scritto in modo equivalente, ma più compatto, così:  -->  'return !p;'
}
//POST=(Inverte il valore di 'player', se era 0 diventa 1, se era 1 diventa 0)


//PRE=(B contiene 14 valori non negativi, 'player'=0/1, 'bucaVuota' in [0..5]. E chiamiamo 'old_B' il valore di B all'invocazione della funzione)
void beansStolen (int (*B)[7], int oldPlayer, int player, int bucaVuota)
{
	player=scambia(player);		//Spostiamoci nel campo del giocatore opposto alla 'bucaVuota' in cui abbiamo terminato la semina!
	
	
	/* Mi serve una funzione che mi calcoli l'indice della buca piccola del lato OPPOSTO al tavolo... Conoscendo solamente l'indice 'bucaVuota'!
	Ovvero: "F(bucaVuota)=bucaOpposta" ==> Nel concreto: F(0)=5, F(1)=4, F(2)=3, F(3)=2, F(4)=1, F(5)=0
	2 sono le funzioni che per prime vengono in mente: "|bucaVuota-5|=bucaOpposta" oppure "5-bucaVuota=bucaOpposta", optiamo per la seconda! */
	
	int fagioliBucaOpposta=*(*(B+player)+(5-bucaVuota));	//Prendiamo i fagioli dalla buca che si trova dal lato opposto in corrispondenza a 'bucaVuota'!
	
	*(*(B+player)+(5-bucaVuota))=0;		//Dopo aver "rubato" i fagioli, resettiamo a 0 tale buca!
	
	
	if (player != oldPlayer)		//In quale campo sono stati "rubati" i fagioli? --> Mi sposto, se necessario, nel lato del player che sta eseguendo la mossa!
		player=scambia(player);
	
	//'oldPlayer' (il giocatore fautore del furto) aggiunge i fagioli "rubati" e il suo ultimo fagiolo (mai depositato nella buca vuota incontrata al termine
	//della sua semina) nella sua buca grande, e così termina il suo turno!
	*(*(B+player)+6)=(*(*(B+player)+6))+fagioliBucaOpposta+1;
}
//POST=(B è ottenuta da 'old_B' eseguendo la mossa descritta nel testo "Bantumi 2" nel caso in cui una semina termini in una buca piccola VUOTA)


//PRE=(B contiene 14 valori non negativi, 'player'=0/1, 'buca' in [0..5], 'fagioli'>0. E chiamiamo 'old_B' il valore di 'B' all'invocazione della funzione)
bool semina (int B[][7], int player, int buca, int fagioli)
{
	//Resetto a 0 (zero) la buca piccola da cui ho appena pescato i fagioli per eseguire la mossa (player, buca)...
	*(*(B+player)+buca)=0;
	
	int i=buca+1;			//Imposto un indice 'i' nella prima buca in cui dovrò iniziare la semina dei 'fagioli' contenuti in 'buca'!
	int oldPlayer=player;		//Mi salvo in una variabile temporanea il giocatore che sta eseguendo la mossa (player, buca)!
	
	//Ora inizio la semina dei 'fagioli' che 'player' ha prelevato da 'buca', fino all'esaurimento di questi ultimi...
	for ( ; fagioli>0; fagioli--)
	{
		//Se incontro la buca grande dell'avversario di 'oldPlayer', devo saltarla senza aggiungere alcun fagiolo; resettare 'i' a 0, e cambiare 'player'!
		if (i==6 && player != oldPlayer)	//B[0][6] (Player 0) && B[1][6] (Player 1) identificano le due BUCHE GRANDI!
		{
			player=scambia(player);
			i=0;
		}
		//Per proseguire la semina DOPO avere superato la buca grande del giocatore 'oldPlayer', devo resettare 'i' a 0, e cambiare 'player'!
		else
		{
			if (i==7)
			{
				player=scambia(player);
				i=0;
			}
		}
		
		//Se termino la semina in una buca vuota (DIVERSA dalla buca grande di 'oldPlayer'), devo agire come richiesto dal testo "Bantumi 2"; in caso
		//contrario proseguo con la semina nella prossima buca...!
		if (fagioli==1 && i != 6 && *(*(B+player)+i) == 0)
			beansStolen(B, oldPlayer, player, i);
		else
			*(*(B+player)+i)=(*(*(B+player)+i))+1;
		
		i++;
	}
	
	bool playAgain=false;		//'playAgain' => FALSE se il prossimo giocatore a giocare sarà DIVERSO dall'attuale 'player', altrimenti TRUE!
	
	if ((i-1)==6)			//Se 'oldPlayer' ha seminato l'ultimo fagiolo nella sua buca grande, la prossima mossa spetta ancora a lui!
		playAgain=true;
	
	return playAgain;
}
//POST=(B è ottenuta da 'old_B' eseguendo la mossa (player, buca) secondo le regole del gioco descritte nel testo. Restituisce true se e solo se alla fine
//della semina si verifica il caso: La semina del giocatore che sta muovendo termina nella sua buca grande; altrimenti false)


//PRE=(B contiene 14 valori non negativi, 'player'=0/1)
int sommaFagioli (int (*B)[7], int player)
{
	int sumBeans=0;		//Totalizzatore per i fagioli inizializzato a 0!
	
	for (int i=0; i<6; i++)					//Mi scorro tutte le buche piccole di 'player'...!
		sumBeans += *(*(B+player)+i);			//Ad ogni buca piccola di 'player' mi aggiorno il valore del mio totalizzatore 'sumBeans'!
	
	return sumBeans;		//Restituisco la somma dei fagioli delle buche piccole di 'player', come richiesto dalla POST!
}
//POST=(Restituisce la somma dei fagioli presenti nelle rispettive buche piccole di 'player')


//PRE=(B contiene 14 valori non negativi, 'player'=0/1)
void resetHoles (int (*B)[7], int player)
{
	for (int i=0; i<6; i++)			//Mi scorro tutte le buche piccole di 'player'...!
		*(*(B+player)+i)=0;				//E resetto a 0 ogni buca piccola del tavolo dal lato di 'player', in modo da non creare "incosistenze" riguardo al
										//numero totale di fagioli tra INIZIO e FINE partita!
}
//POST=(Tutti gli elementi in B[player][0..5] sono == 0)


main()
{
	ifstream IN("input");
	ofstream OUT("output");
	
	if (IN && OUT)
	{
		//PRE=("input" contiene 14 interi non negativi che costituiscono la configurazione iniziale del tavolo da gioco; di seguito "input" contiene un intero
		//(0/1) che rappresenta il player che deve iniziare a giocare; infine contiene una sequenza di interi (in 0..5) che termina con un "-1", tale sequenza
		//sta ad indicare le varie mosse che dovranno essere eseguite durante il gioco seguendo le regole del gioco Bantumi)
		
		
		
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
		
		
		//Fase 2: Ciclo che mi scorre tutti i rispettivi valori di 'b' letti da "input" e stampa su "output" tutti i punti previsti dalla POST del programma.
		//Il ciclo terminerà solamente quando verrà letto b==-1, oppure in caso di terminazione della partita (come richiesto dalla POST); e dopo il ciclo sarà
		//stampata su "output" la consueta stringa "fine"!
		
		//Stampo la configurazione iniziale del tavolo da gioco...
		stampaTavolo(OUT, B);
		
		//Leggo la prima coppia (p, b) per determinare QUALE PLAYER inizerà il gioco iniziando con la mossa (p, b) ==> Se b==-1 NON entro nel ciclo e termino
		//con "fine", altrimenti entro nel ciclo e proseguo...
		int p, b;
		IN>>p>>b;
		
		bool stop=false;
		
		if (b==-1)			//Se b==-1 il gioco deve teminare, senza effettuare alcuna altra lettura e/o scrittura (eccetto la stampa della stringa "fine")!
			stop=true;
		
		
		for ( ; stop==false; )
		{
			OUT<<"il giocatore "<<p<<" fa la mossa "<<b<<endl;		//Stampo, ad ogni coppia (p, b), solamente se b != -1, la stringa che mi esprime tale mossa
																	//su "output"!
			//cout<<"il giocatore "<<p<<" fa la mossa "<<b<<endl;
			
			
			int fagioli=B[p][b];		//Leggo quanti fagioli contiene la buca b del player p che sta eseguendo la mossa (p, b)!
			
			if (fagioli != 0)		//Se la buca selezionata NON è vuota, devo procedere con l'esecuzione di tale mossa e tutto ciò che ne consegue...!
			{
				bool changePlay=semina(B, p, b, fagioli);		//"Change_Player" ==> Mi tiene conto di chi sarà il prossimo giocatore a dover muovere!
				
				stampaTavolo(OUT, B);		//Stampo a video la nuova configurazione del tavolo dopo l'esecuzione della mossa (p, b)!
				
				//Se dopo l'ultima mossa di 'p' (chiunque esso sia), uno dei due players ha tutte le sue buche piccole a 0, il gioco deve terminare e decretare
				//la vincita/sconfitta/parità!
				if (sommaFagioli(B, 0)==0 || sommaFagioli(B, 1)==0)
				{
					//Ora aggiungo la somma di tutti i fagioli delle buche piccole del player 'p' nella sua buca grande...
					B[p][6] += sommaFagioli(B, p);
					
					//...e resetto (pongo a 0) tutte le sue buche piccole, ormai svuotate e sommate alla buca grande!
					resetHoles(B, p);
					
					//Ed ora aggiungo la somma di tutti i fagioli delle buche piccole del player '!p' nella sua buca grande...
					B[scambia(p)][6] += sommaFagioli(B, scambia(p));
					
					//...e resetto (pongo a 0) anche tutte le sue buche piccole, ormai svuotate e sommate alla buca grande!
					resetHoles(B, scambia(p));
					
					
					//stampaTavolo(OUT, B);		//Stampo l'array B, così prima di decretare l'esito della partita, mostro la situzione FINALE DEL GIOCO!!!
												//## ATTENZIONE! ## ==> Tale stampa non è richiesta, è PURAMENTE FACOLTATIVA!!
					
					
					if (B[0][6]==B[1][6])			//PRIMO CHECK: PARITA'??
					{
						OUT<<"entrambi i giocatori hanno "<<B[p][6]<<" fagioli, la partita finisce in parità"<<endl;		//Si è verificato un pareggio, lo
																															//scrivo su "output"!
						//cout<<"entrambi i giocatori hanno "<<B[p][6]<<" fagioli, la partita finisce in parità"<<endl;
					}
					else							//SECONDO CHECK: Niente parità, allora CHI HA VINTO??
					{
						if (B[0][6] > B[1][6])		//TERZO CHECK: HA VINTO IL PLAYER 0??
						{
							OUT<<"vince il giocatore 0 con "<<B[0][6]<<" fagioli, mentre il giocatore 1 ne ha "<<B[1][6]<<endl;		//THE WINNER IS PLAYER 0!!!
																																	//-> Riporto l'adeguata
																																	//stringa su "output"!
							//cout<<"vince il giocatore 0 con "<<B[0][6]<<" fagioli, mentre il giocatore 1 ne ha "<<B[1][6]<<endl;
						}
						else						//ULTIMA CHANCE: Niente parità, il Player 0 non ha vinto, e allora... THE WINNER IS...!
						{
							OUT<<"vince il giocatore 1 con "<<B[1][6]<<" fagioli, mentre il giocatore 0 ne ha "<<B[0][6]<<endl;		//THE WINNER IS PLAYER 1!!!
																																	//-> Riporto l'adeguata
																																	//stringa su "output"!
							//cout<<"vince il giocatore 1 con "<<B[1][6]<<" fagioli, mentre il giocatore 0 ne ha "<<B[0][6]<<endl;
						}
					}
					
					stop=true;		//Ho terminato la partita (a prescindere dal fatto che sia finita in pareggio o con la vincita di uno dei due giocatori),
									//quindi devo uscire dal ciclo, e stampare "fine" su "output"!
				}
				else					//Nessun giocatore ha tutte le sue buche piccole vuote, allora proseguo con il gioco e la lettura del prossimo b,
										//ed eventualmente cambio il giocatore p...!
				{
					if (!changePlay)			//Se la mossa (p, b) fa in modo che il prossimo player a giocare sia DIVERSO da quello che ha appena effettuato
												//tale mossa, allora entro nell'if...; altrimenti NON cambio il player, e non entro nell'if...!
						p=scambia(p);		//Se entro nell'if, il prossimo turno toccherà al player opposto a colui che ha appena eseguito la mossa...!
				}
			}
			else					//Se la buca selezionata è vuota, devo procedere alla scrittura su "output" della stringa relativa alla mossa sbagliata,
									//inverto il player p, e procedo alla lettura della prossima mossa 'b' da "input"!
			{
				p=scambia(p);
				OUT<<"mossa sbagliata, il turno passa al giocatore "<<p<<endl;
				//cout<<"mossa sbagliata, il turno passa al giocatore "<<p<<endl;
			}
			
			
			IN>>b;			//Leggo la prossima mossa 'b' che dovrà essere effettuata dal giocatore 'p' che si aggiorna automaticamente in base all'ultima mossa
							//appena eseguita!
			
			if (b==-1)			//Se il valore di 'b' appena letto risulta essere b==-1, fermo il gioco!
				stop=true;
		}
		
		
		OUT<<"fine"<<endl;		//Stampo alla fine di "output" la consueta stringa "fine" che segna la terminazione del file!
		//cout<<"fine"<<endl;
		
		
		IN.close();
		OUT.close();
		
		
		
		/*
		POST=("output" contiene le seguenti cose:
		1) La configurazione di gioco iniziale;
		
		2) Per ogni coppia (p, b) e tale che b != -1:
			- Se è la prima mossa del gioco il valore di p e di b vengono letti da "input";
			- Se non è la prima mossa del gioco, solamente il valore di b è letto da "input" mentre il valore di p è generato da programma;
			
			--> In entrambi i casi "output" dovrà sempre contenere:
			- La stringa: "il giocatore p fa la mossa b";
			
			Successivamente in base alle seguenti due possibilità, si opererà in modo differente:
			a)	Se la mossa sopra descritta (p, b) e stampata su "output" HA senso (ovvero si prendono i fagioli in una buca NON vuota di p), allora "output"
				deve contenere la nuova configurazione raggiunta eseguendo la mossa (p, b);
			b)	Se la mossa sopra descritta (p, b) e stampata su "output" NON HA senso (perchè p cerca di prelevare i fagioli dalla buca b la quale però è
				VUOTA), allora "output" NON deve contenere la nuova configurazione (perchè tale nuova configurazione resta identica alla precedente), e deve
				invece contenere la stringa: "mossa sbagliata, il turno passa al giocatore !p" (dove !p indica l'AVVERSARIO di p, perchè p tenta di fare la
				mossa sbagliata);
		
		3) Se prima di leggere da "input" b==-1 la partita termina, ovvero uno dei due giocatori ha tutte le sue buche piccole a 0, su "output" deve essere
		   inserita la stringa:
			a)	"vince il giocatore p con n fagioli, mentre il giocatore q ne ha m"
				Il vincitore, seguendo le regole del Bantumi (Bantumi 3), sarà colui che a fine partita, avrà più fagioli (n MAGGIORE STRETTO di m) nella sua
				buca grande, rispetto al suo avversario!
			b)	"entrambi i giocatori hanno n fagioli, la partita finisce in parità"
				Se entrambi i giocatori, seguendo le regole del Bantumi (Bantumi 3), avranno nelle loro rispettive buche grandi un numero == di fagioli; vi è
				un PAREGGIO!
		
		4) Il file "output" termina sempre con la stringa "fine".)
		*/
	}
	else
	{
		cout<<"Errore causato dai file!";
	}
	
	
}
