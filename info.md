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
