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
        List(node *head); // inizializza la lista con una sequenza di nodi già esistente
        ~List();
        node *head;
        void push(void *);
        void *pop();

        void append(node *); //concatena in coda un'altra lista
        void append(List);

        bool delete_element(void *); // elimina un membro della stanza (comparando l'indirizzo)
                                     // qual'ora non venga trovato restituisce false
                                     // ATTENZIONE: viene eliminato dalla lista, NON deallocato

        void destroy(); //dealloca la lista, ma non i suoi elementi
};
