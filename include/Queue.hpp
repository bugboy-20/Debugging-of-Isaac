#pragma once

#include "List.hpp"
class Queue {
    public:
        Queue();
        //Queue(node *head);
        ~Queue();
        void destroy();

        void enqueue(void *);
        void *dequeue();
//mostra la testa ma non rimuove l'elemento
        void *seek();
    private:
        node *first;
        node *last;

};
