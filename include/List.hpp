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
        node *head;
        void push(void *);
        void *pop();

        void destroy(); //dealloca la lista
};
