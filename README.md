# Progetto-Programmazione


## Modus operandi
- usare .gitignore per nascondere eventuali cartelle create dai propri tool
- usare `make`
- non pushare finché non si è certi che ciò che si è fatto funziona
- realizzare le interfacce (file .h e .hpp) e poi implementarle
- eventuali modifiche ad intefacce vanno comunicate a tutti
- ogni funzione deve avere un commento alla riga precedente nel file .h o .hpp che ne decrive il funzionamento (input, output, criticità)
- usare il formato `caca_pupu` e non `cacaPupu`
- se una funzione precedente in input un dato ma non lo modifica segnare quel dato con `const` (es. `void stampa_stringa(char stringa[]); -> void stampa_stringa( const char stringa[]);`
- per il resto uno può fare quello che vuole

## Divisione del lavoro
- Diego: Main, gestione degli input e delle chiamate
- Ale:	 Creazione delle classi per le entità del gioco
- Saad:	 Gestione della fisica del gioco
- Piske: Stampa a video

https://virtuale.unibo.it/pluginfile.php/1059665/mod_resource/content/1/presentazioneProgetto.pdf
