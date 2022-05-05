#include "Queue.hpp"
#include "List.hpp"
#include <cstddef>


Queue::Queue() {
    this->first=NULL;
    this->last=NULL;
}

/*
Queue::Queue(node *head) : Queue() {
    if(head!=NULL) {

    }
}
*/

Queue::~Queue() {
    destroy();
}

void Queue::destroy() {
    while (dequeue()!=NULL);
}

void Queue::enqueue(void *e) {
    if(e==NULL) return;

    node *n = new node;
    n->element=e;
    n->next=NULL;

    this->last->next=n;
    this->last=n;

    if(this->first==NULL) this->first=n;
}

void* Queue::dequeue() {
    void *ret_e;
    node *f_n;

    f_n=this->first;
    ret_e=f_n->element;

    this->first=this->first->next;

    delete f_n;
    return ret_e;
}

void* Queue::seek() { 
    return this->first->element;
}
