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
- Ale: Creazione delle classi per le entità del gioco
- Saad: Gestione della fisica del gioco
- Piske: Stampa a video

https://virtuale.unibo.it/pluginfile.php/1059665/mod_resource/content/1/presentazioneProgetto.pdf

[Albero genealogico delle classi](https://viewer.diagrams.net/?tags=%7B%7D&highlight=0000ff&edit=_blank&layers=1&nav=1&title=ger_classi.drawio#R7Ztdb5swFIZ%2FTS47gQ2EXG5pu0nbpEmV9nUzucEFb4bDjNOE%2FfqZYEKC0zRbK9xCrxq%2F2GDOc3yOP%2BgEz9P1W0Hy5CNElE%2BQE60n%2BHyCkIscpP5USlkrPvJrIRYs0pVa4Yr9oVp0tLpkES32KkoALlm%2BLy4gy%2BhC7mlECFjtV7sBvv%2FUnMTUEK4WhJvqFxbJpFZDNG31d5TFSfNkN5jVV1LSVNZvUiQkgtWOhC8meC4AZP0rXc8pr4zX2KVud3nH1W3HBM3kKQ0Yia%2Bn7z18Fn8G97IU6%2B%2F%2B27NQ902WzQvTSL2%2FLoKQCcSQEX7Rqm8ELLOIVnd1VKmt8wEgV6KrxJ9UylLDJEsJSkpkyvVV1WFRftXtN4VvVeHV1G%2FK5%2Bvdq%2BelLtWdrXp4pw20VMBSLOiRF298iYiYyiP10JaUcnEKKVX9Ue0E5USy2%2F1%2BEO1r8bZei0P90ET%2BgY7rvuA5jiewisd%2FSnieIJ2pVTr1fW8JX%2BonzUFQg5ika7lv4EIK%2BEXnwEEoJYOswnbDOO9IhLM4U8WFsh9V%2BptbKiRTqeO1vpCyKNowXyVM0qucbIy6UonS8APdV3UDuj6OxzSnbhDoPKMTrYt1edWmLU9LyU7GatLTo9t%2FNtLBgU4cHNjq4HBe6Byl49ukg4zQpd6TyXK4wcv1O9HLsRy9sIEg56RUlhosgq0tNYKpZQK%2BQSCBQjI%2B4BTeRWA9hwcGA2WFVCmQbVbslQGGi8MISjPLOKYGjhsOIH5EdAHjwXAoMk37xIDwSCdPbnDi7MkNrU6fntW6nK6Z%2FNrWVKVvO1faRlXBKtOHruY3TV8LQcqdCjmwTBY7d%2F5UCTuDv5MSPdfp%2BEd9x9Zbtl17gAMFz8mBrDjD7Ek4w6wHZ3APTIKyW2VaECW5HvJ0NOxY2zfzbthn3nXN%2Bc8CsmKZDhuD2%2BVwYG3c6%2FwHjzY8hieGR2QlVyLH33cUr4fwiMe6z3u6Mzx0Mvx%2FzuB1okbQOR6%2Br37YR24NjYi%2BoiSvdhdGE80PZFW%2F16w6MxgQkcKAdzoNBKHlfR0P2YihjxgLm89h7j%2F0uoNMPxsD3lg3bk7n4zyQz3%2FlKux0BqR3PFcZ9Z0%2BNgXM1UdKOR3wwgN1Nl4928cRzcMsjd8z55XjzzqD2HPvGcab0icqmLJBBfXRx%2Fap81CMrMbeJ%2FUtW5%2Bx92Q%2BnpXY6x6d999b38d9xF5znSBIFivPGE%2FwPXDq1es6oQn%2BOwyKnJMiUVpE0uo76sHCwJ2NZ3zgJDjoFYb5dWPBsrjaBg14ZfNrtX4L4uqXjjujYXNoltIvG2QGK%2Fp7yQQtqsel6YDP6vEdu0j2vuPyjsHIYPhEcCdfI5PII50eqGL77yx16m%2F%2FKQhf%2FAU%3D)

## Gioco

### Armi

```
Weapon
 └─ Melee
    ├─ Area
    └─ Singol target
 └─ Ranged
    ├─ Ammo
    └─ Magic (no mana)
```

### Armatura

L'armatura aumenta i cuori e quindi gli hp del personaggio, il limite è una solo armatura equipaggiata in ogni momento.

### Oggetti

Gli oggetti possono essere di due tipi:

- pickup (es. munizioni, chiavi)
- consumabili (es. pozioni di cura, di danno)

_Dagli appunti che avevo preso non è chiara la differenza tra le due categorie_

### Nemici

I nemici si dividono in due tipi:

- minion
- boss

Tutti i nemici possono essere o **melee** o **ranged**, l'unica cosa che cambia è il loro range di aggro

Per scalare la difficoltà dei nemici in base a quanto si è progredito nel gioco, utilizziamo un moltiplicatore che aumento con il procedere della partita

### Informazioni generiche

1. avevamo previsto uno starter kit, che varia in base al tipo di personaggio che si sceglie all'inizio
2. implementare un gioco con movimento fluido, non a turni
3. per raccogliere un oggetto bisogna andarci sopra
4. quando un oggetto viene droppato, verrà posizionato di fianco
5. implementare un set di stanze fisso che definisce come sono strutturate e cosa c'è dentro
6. implementare un set di nemici fisso che verrà associato randomicamente alla stanza.
7. la quantità di nemici presente nella stanza dipende sempre dal moltiplicatore di difficoltà che aumenta col procedere della partita (mi ero scritto che questo era da rivedere)

_i punti 5, 6, 7 non sono molto chiari quindi se in corso d'opera ci rendiamo conto che c'è una soluzione migliore, cambiamo rotta_

### Cose a caso

classe inventoryable

- char display
- char name[]
- int type {1,..,3}
  - 1 -> spada
  - 2 -> armatura
  - 3 -> consumabile

struttura data di tipo inventoryable
