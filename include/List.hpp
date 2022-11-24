#pragma once
//Lista generica con accesso ai suoi elementi
// può contenere elementi di qualsiasi tipo, purché siano passati per indirizzo
struct node {
    void *element;
    node *next;
};

class List {
    public:
        List();
// inizializza la lista con una sequenza di nodi già esistente (fa una copia dell struttura, non dei dati puntati)
        List(node *head);
        node *head;
        void push(void *);
        void *pop();

//concatena in coda un'altra lista
        void append(node *);
        void append(List&);
// elimina un membro della stanza (comparando l'indirizzo)
// qual'ora non venga trovato restituisce false
// ATTENZIONE: viene eliminato dalla lista, NON deallocato
        bool delete_element(void *);

//dealloca la lista, ma non i suoi elementi
        void destroy();
};
