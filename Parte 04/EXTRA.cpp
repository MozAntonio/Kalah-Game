/*
######################################################################################################################################################################################
############################################################################=============================#############################################################################
############################################################################|| BANTUMI 4 - SMART KALAH ||#############################################################################
############################################################################=============================#############################################################################
######################################################################################################################################################################################*/

#include <climits>
using namespace std;


namespace EXTRA
{
	//PRE=(B contiene 14 valori non negativi, 'p'=0/1, 'bucaVuota' in [0..5]. E chiamiamo 'old_B' il valore di B all'invocazione della funzione)
	void beansStolen(int (*B)[7], int oldP, int p, int bucaVuota)
	{
		p=!p;		//Spostiamoci nel campo del giocatore opposto alla 'bucaVuota' in cui abbiamo terminato la semina!
		
		
		//Mi serve una funzione che mi calcoli l'indice della buca piccola del lato OPPOSTO al tavolo... Conoscendo solamente l'indice 'bucaVuota'!
		//Ovvero: "F(bucaVuota)=bucaOpposta" ==> Nel concreto: F(0)=5, F(1)=4, F(2)=3, F(3)=2, F(4)=1, F(5)=0
		
		int fagioliBucaOpposta=*(*(B+p)+(5-bucaVuota));		//Prendiamo i fagioli dalla buca che si trova dal lato opposto in corrispondenza a 'bucaVuota'!
		
		*(*(B+p)+(5-bucaVuota))=0;		//Dopo aver "rubato" i fagioli, resettiamo a 0 tale buca!
		
		
		if (p != oldP)		//In quale campo sono stati "rubati" i fagioli? --> Mi sposto, se necessario, nel lato del player che sta eseguendo la mossa!
			p=!p;
		
		//'oldP' (il giocatore fautore del furto) aggiunge i fagioli "rubati" e il suo ultimo fagiolo (mai depositato nella buca vuota incontrata al termine della sua semina)
		//nella sua buca grande, e così termina il suo turno!
		*(*(B+p)+6)=(*(*(B+p)+6))+fagioliBucaOpposta+1;
	}
	//POST=(B è ottenuta da 'old_B' eseguendo la mossa descritta nel testo "Bantumi 2" nel caso in cui una semina termini in una buca piccola VUOTA)
	
	
	//PRE=(B contiene 14 valori non negativi, 'p'=0/1, 'buca' in [0..5], 'fagioli' > 0. E chiamiamo 'old_B' il valore di 'B' all'invocazione della funzione)
	bool semina(int (*B)[7], int p, int buca)
	{
		//Prendo i fagioli della buca di 'p', con i quali eseguirò la mossa indicata dal loro numero...!
		int fagioli=*(*(B+p)+buca);
		
		//Resetto a 0 (zero) la buca piccola da cui ho appena pescato i fagioli per eseguire la mossa (p, buca)...
		*(*(B+p)+buca)=0;
		
		int i=buca+1;			//Imposto un indice 'i' nella prima buca in cui dovrò iniziare la semina dei 'fagioli' contenuti in 'buca'!
		int oldP=p;		//Mi salvo in una variabile temporanea il giocatore che sta eseguendo la mossa (p, buca)!
		
		//Ora inizio la semina dei 'fagioli' che 'p' ha prelevato da 'buca', fino all'esaurimento di questi ultimi...
		for ( ; fagioli>0; fagioli--)
		{
			//Se incontro la buca grande dell'avversario di 'oldP', devo saltarla senza aggiungere alcun fagiolo; resettare 'i' a 0, e cambiare 'p'!
			if (i==6 && p != oldP)		//B[0][6] (Player 0) && B[1][6] (Player 1) identificano le due BUCHE GRANDI!
			{
				p=!p;
				i=0;
			}
			//Per proseguire la semina DOPO avere superato la buca grande del giocatore 'oldP', devo resettare 'i' a 0, e cambiare 'p'!
			else
			{
				if (i==7)
				{
					p=!p;
					i=0;
				}
			}
			
			//Se termino la semina in una buca vuota (DIVERSA dalla buca grande di 'oldP'), devo agire come richiesto dal testo "Bantumi 2"; in caso contrario proseguo con la semina
			//nella prossima buca...!
			if (fagioli==1 && i != 6 && *(*(B+p)+i) == 0)
				EXTRA::beansStolen(B, oldP, p, i);
			else
				*(*(B+p)+i)=(*(*(B+p)+i))+1;
			
			i++;
		}
		
		bool playAgain=false;		//'playAgain' => FALSE se il prossimo giocatore a giocare sarà DIVERSO dall'attuale 'oldP', altrimenti TRUE!
		
		if ((i-1)==6)			//Se 'oldP' ha seminato l'ultimo fagiolo nella sua buca grande, la prossima mossa spetta ancora a lui!
			playAgain=true;
		
		return playAgain;
	}
	//POST=(B è ottenuta da 'old_B' eseguendo la mossa (p, buca) secondo le regole del gioco descritte nel testo. Restituisce "true" se e solo se alla fine della semina si verifica
	//il caso: La semina del giocatore che sta muovendo termina nella sua buca grande; altrimenti "false")
	
	
	//PRE=(B contiene 14 valori non negativi, 'player'=0/1)
	int sommaFagioli (int (*B)[7], int player)
	{
		int sumBeans=0;		//Totalizzatore per i fagioli inizializzato a 0!
		
		for (int i=0; i<6; i++)					//Mi scorro tutte le buche piccole di 'player'...!
			sumBeans += *(*(B+player)+i);			//Ad ogni buca piccola di 'player' mi aggiorno il valore del mio totalizzatore 'sumBeans'!
		
		return sumBeans;		//Restituisco la somma dei fagioli delle buche piccole di 'player', come richiesto dalla POST!
	}
	//POST=(Restituisce la somma dei fagioli presenti nelle rispettive buche piccole di 'player')
	
	
	//PRE=('a' è un array vuoto, 'b' contiene 14 valori non negativi)
	void copyArray(int a[][7], int b[][7])
	{
		for(int i=0; i<2; i++)			//Scorro la prima dimensione degli array...
			for(int j=0; j<7; j++)		//Scorro la seconda dimensione degli array...
				a[i][j]=b[i][j];			//Assegno ogni elemento dell'array 'b' all'array 'a' nella posizione corretta! ==> Di fatto: Creo una copia!
	}
	//POST=(L'array 'a' è una copia, elemento per elemento, dell'array 'b')
	
	
	//PRE=(B rappresenta la situazione del gioco, player=0/1, allBeans == Numero totale dei fagioli nel campo di gioco)
	int heuristic(int B[][7], int player, int allBeans)
	{
		if(B[1][6] > allBeans/2)	//Se ora mi trovo in una situazione di VITTORIA CERTA (ho più della metà dei fagioli complessivi nella mia buca grande)...
			return 500;				//Torno un valore "significativamente" MAGGIORE di qualsiasi altro possibile valore euristico che possa essere restiutito dalla funzione!
										//N.B.: Non ritorno 'INT_MAX' per evitare conflitti con l'inzializzazione di 'best' (variabile della funzione chiamante)!
		if(B[0][6] > allBeans/2)	//Se ora mi trovo in una situazione di PERDITA CERTA (più della metà dei fagioli complessivi sono nella buca grande dell'avversario)...
			return -500;			//Torno un valore "significativamente" MINORE di qualsiasi altro possibile valore euristico che possa essere restiutito dalla funzione!
										//N.B.: Non ritorno 'INT_MIN' per evitare conflitti con l'inzializzazione di 'best' (variabile della funzione chiamante)!
		
		//NOTA: Il valore "500" è puramente arbitrario, l'importante è che superi 'allBeans'*2 (nel nostro caso: 48*2), e che sia inferiore a 'INT-MAX'!
		
		//Mi calcolo quanti fagioli ci sono in totale nelle mie sole buche piccole...!
		int tot=EXTRA::sommaFagioli(B, 1);
		
		
		//FUNZIONE EURISTICA: Moltiplico i fagioli della mia buca grande x2, ed a questi vi aggiungo 'tot' (totale fagioli buche piccole) x1!
		//P.S.: Sarebbe stato equivalente contare 1 punto per B[1][6] e 1/2 di punto per 'tot', ma così facendo avrei avuto perdite di informazioni a causa del cast: double->int!
		return (B[1][6]*2 + tot);
	}
	//POST=(Restituisce un intero che assume un determinato valore in base alla situazione descritta dalla board 'B' e al valore di 'player')
	
	
	//PRE=(B rappresenta la situazione del gioco, player=0/1, livello >= 0, 'mossa' è un intero alias di una variabile del chiamante)
	int calcolaMossa(int B[][7], int player, int livello, int & mossa, int allBeans)
	{
		//Se sono a livello 0, vuol dire che devo fermarmi e valutare l'attuale situazione della board B!
		//Ma devo fermarmi anche se uno dei due campi (buche piccole) del tavolo sono tutti vuoti (questo può accadere durante la ricorsione, anche se non sono a livello==0)!
		if(!livello || EXTRA::sommaFagioli(B, 1)==0 || EXTRA::sommaFagioli(B, 0)==0)
			return EXTRA::heuristic(B, player, allBeans);		//Invoco la funzione che mi valuterà la mia attuale situazione di B, e in base ad essa tornerà un valore significativo!
		else							//Non sono ancora al livello 0, quindi proseguo con la genereazione delle mosse successive, imitando un "albero virtuale" per la generazione!
		{
			int tempValue;		//Intero d'appoggio che mi servirà per assegnargli le rispettive chiamate ricorsive che poi utilizzerò per controllare, e sceglierne, la MIGLIORE!
			int best;			//Intero che di volta in volta (a seconda del giocatore che sta eseguendo le varie mosse) avrà il VALORE MIGLIORE per codesto giocatore!
			int tempMossa=-1;	//Intero che di volta in volta (a seconda del giocatore che sta eseguendo le varie mosse) sarà la MOSSA MIGLIORE per codesto giocatore!
			
			if(player)			//Player==1, le mosse che sto per generare appartengono A ME... ==> SCELGO IL MASSIMO TRA QUELLE CHE HO A DISPOSIZIONE!
				best=INT_MIN;		//Inizializzo ad INT_MIN, in modo che sarà subito scartato tale valore di inizializzazione...
			else				//Player==0, le mosse che sto per generare appartengono ALL'AVVERSARIO... ==> SCELGO IL MINIMO TRA QUELLE CHE CI SONO A DISPOSIZIONE!
				best=INT_MAX;		//Inizializzo ad INT_MAX, in modo che sarà subito scartato tale valore di inizializzazione...
			
			//Ogni "nodo dell'albero virtuale" avrà al massimo 6 figli (le 6 mosse possibili), le scorro tramite un ciclo for...
			for(int i=0; i<6; i++)
			{
				if(B[player][i] != 0)		//Se la buca (ovvero la mossa) che voglio eseguire HA SENSO (buca non vuota) la eseguo, altrimento non faccio nulla...
				{
					int temp[2][7];				//Mi dichiaro un array temporaneo da utilizzare senza "sporcare" la board originale 'B'...
					EXTRA::copyArray(temp, B);			//Copio 'B' nel temporaneo appena dichiarato!
					
					bool extraMove=false;		//Booleano che mi serve per sapere se la mossa che sto per eseguire è una mossa che mi procura una 'MOSSA EXTRA'!
					
					extraMove=EXTRA::semina(temp, player, i);		//Invoco la semina, che mi dirà se dopo toccherà ancora al giocatore che ha appena eseguito la mossa, oppure no,
																	//e mi avrà modificato la board con la semina appena eseguita...
					
					if(extraMove)																//Tocca nuovamente il giocatore che ha appena giocato!
						tempValue=EXTRA::calcolaMossa(temp, player, livello, mossa, allBeans);		//Invoco con stesso player, e stesso livello, e metto il risultato in 'tempValue'!
					else																		//Tocca al giocatore avversario di colui che ha appena giocato!
						tempValue=EXTRA::calcolaMossa(temp, !player, livello-1, mossa, allBeans);	//Invoco con il player opposto, e livello -1, e metto il risultato in 'tempValue'!
					
					
					if(player)					//Se player==1, allora sto cercando il MAX!
					{
						if(best <= tempValue)	//Se 'tempValue' è meglio di 'best' aggiorno, altrimenti niente!
						{
							best=tempValue;		//Aggiorno 'best'!
							tempMossa=i;		//Aggiorno 'tempMossa' che sta ad indicare la buca (tra le 6 buche/mosse possibili) che attualmente ha generato un 'best' migliore!
						}
					}
					else					//Se player==0, allora sto cercando il MIN!
					{
						if(best >= tempValue)	//Se 'tempValue' è meglio di 'best' aggiorno, altrimenti niente!
						{
							best=tempValue;		//Aggiorno 'best'!
							tempMossa=i;		//Aggiorno 'tempMossa' che sta ad indicare la buca (tra le 6 buche/mosse possibili) che attualmente ha generato un 'best' migliore!
						}
					}
				}
			}
			
			if((player && best==INT_MIN) || (!player && best==INT_MAX))		//Se non è MAI stato modificato il valore di 'best', e quindi nemmeno 'B', torno la valutazione di 'B'...!
				return heuristic(B, player, allBeans);
			else
			{
				mossa=tempMossa;	//Setto la variabile 'mossa', passata per aliasing, con la migliore fin'ora incontrata!
				return best;		//Se è stata effettuata almeno una mossa, allora torno il meglio ('best') tra le rispettive 6 mosse possibili di 'player'!
			}
		}
	}
	//POST=(Restituisce un valore z, tale che z sia il MIGLIOR valore (in base ad una funzione di euristica sulle mosse) per la successiva mossa che dovrà eserguire 'player'; tale
	//mossa, grazie all'aliasing, viene aggiornata al variare di 'best' (valore MIGLIORE incontrato fin'ora); inoltre 0<=mossa<=5, e B[player][mossa] != 0)
	
	
	//PRE=(B rappresenta la situazione del gioco, player=0/1, livello >= 0)
	int meglio_mossa(int B[][7], int player, int livello)
	{
		//Il ciclo for all'interno del costrutto if che segue questo commento ha il seguente scopo:
		//Se la funzione viene invocata con player==1, nessun problema, proseguo; se invece viene invocata con player==0, devo INVERTIRE i due campi della board B, e 'player' da "0"
		//deve assumere "1", così facendo "ignoro" il fatto che io sia stato invocato con player==0/1, e mi comporterò, dopo le eventuali modifiche, come se fossi SEMPRE il "player 1"!
		
		int temp[2][7];
		EXTRA::copyArray(temp, B);		//Mi creo una copia di 'B' in 'temp' per non modificare la board 'B' originale!
		
		if(!player)				//Se player==0, inverto i campi di gioco, e il giocatore!
		{
			for(int i=0; i<7; i++)
			{
				int salva=temp[player][i];
				temp[player][i]=temp[!player][i];
				temp[!player][i]=salva;
			}
			
			player=!player;
		}
		
		
		//Mi calcolo il numero totale di fagioli presenti nel campo da gioco (di norma è 48 [(4*6)*2], ma utilizzare un totalizzatore può migliorare il riutilizzo di tale variabile
		//anche su partite che iniziano con un numero differente di fagioli, ad esempio [(3*6)*2 == 36])!
		int allBeans=0;
		for(int i=0; i<2; i++)					//Scorro la prima dimensione dell'array...
			for(int j=0; j<7; j++)				//Scorro la seconda dimensione dell'array...
				allBeans=allBeans+B[i][j];			//Incremento di volta in volta il totalizzatore del numero di fagioli 'allBeans'!
		
		int mossa=-1;	//Mi creo una variabile 'mossa', da passare per aliasing alla funzione che mi esegue i vari calcoli, e mi "genera l'albero virtuale"!
		
		
		//Grazie all'algoritmo MIN-MAX la funzione 'calcolaMossa' massimizza per il player 1 (io), e minimizza per il player 0 (avversario)!
		
		EXTRA::calcolaMossa(temp, player, livello, mossa, allBeans);
		
		return mossa;		//Torno 'mossa', cambiata tramite aliasing, che ora indicherà la miglior mossa da eseguire con l'attuale 'B' per il giocatore 'player'!
	}
	//POST=(Restituisce una mossa 'm' per 'player', 0<=m<=5, e B[player][m] != 0)
	
	
	
	/*
	FUNZIONE EURISTICA (O DI ANALISI STATICA):
	
	Da qui in poi si parla di "player 1" come colui che deve eseguire la mossa, e ottimizzare tale mossa; mentre "player 0" sarà l'avversario!
	(Infatti player 1 MASSIMIZZA, e player 0 MINIMIZZA; questo è per quanto riguarda l'algoritmo MIN-MAX utilizzato!)
	
	La mia funzione euristica (o di analisi statica) è quella di:
	1) Prendere i fagioli della buca grande del player 1, che li chiameremo: beansGH (beans_great_hole);
	2) Prendere la somma dei fagioli delle buche piccole del player 1, che li chiameremo: beansSH (beans_small_holes)!
	
	Poi moltiplichiamo x2 "beansGH", e a questo risultato ci sommiamo "beansSH"!
	
	Questa scelta è nata dal fatto che:
	- Più fagioli ci sono nella buca grande di player 1, più tale giocatore si sta avvicinando al superamento della metà dei fagioli totali, e appena succede, si ha una
	vittoria MATEMATICA!
	- Però anche i fagioli che ci sono nelle buche piccole del player 1 devono essere contati in qualche modo, perchè sono possibili (e forse probabili) punti futuri che condurranno
	alla vittoria per player 1!
	
	==> PERO': I fagioli già nella buca grande sono punti sicuri, mentre quelli nelle buche piccole sono POSSIBILI (e non si sa quanto probabili) punti futuri, quindi bisogna
	valutarli di meno, rispetto a quelli già presenti nella buca grande!
	PER LE ATTUALI REGOLE DEL GIOCO, ho fornito il valore un 1/2 ai possibili futuri fagioli, mentre il valore 1 ai fagioli CERTI (quelli già presenti nella buca grande)!
	
	OVVERO: { beansGH + (beansSH/2) } == { (beansGH*2) + beansSH }
	
	
	In aggiunta a tutto questo, ho aggiunto, per completezza, due controlli: Che controllano se ho GIA' VINTO, o se ho GIA' PERSO...
	Questi due controlli sembrano logicamente e concettualmente corretti e coerenti con il resto della funzione euristica (per i dettagli leggere i commenti che affiancano tali
	istruzioni nella parte soprastante del programma, o meglio nella funzione "heuristic")!
	*/
}
