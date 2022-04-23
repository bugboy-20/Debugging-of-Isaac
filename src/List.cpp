#include "List.hpp"
#include <cstddef>

List::List(){
    this->head=NULL;
}

List::List(node *head) {
    node *tlcn= new node;
    this->head=tlcn;

    for(node *cn=head; cn!=NULL; cn=cn->next) {
        tlcn->element=cn->element;
        tlcn->next=new node;
        tlcn=tlcn->next;
    }
    tlcn->next=NULL;
}

List::~List() {
    destroy();
}

void List::push(void *e) {
    node *nw_head = new node;
    nw_head->element=e;
    nw_head->next=this->head;
    this->head=nw_head;
}

void *List::pop() {
    if (this->head==NULL)
        return NULL;
    node *npopped=this->head;
    void *epopped=npopped->element;

    this->head=npopped->next;
    delete npopped;

    return epopped;
}

void List::destroy() {
    while (pop()!=NULL);
}

bool List::delete_element(void *e) {
    node *cn; //current node
    node *tmp;

    for(cn=head; cn->next!=NULL; cn=cn->next) {
        if(cn->next->element == e) {
            tmp=cn->next;
            cn->next=tmp->next;
            delete tmp;
            return true;
        }
    }
    return false;
}

void List::append(node *n) {
    node *last;

    for (last=head; last->next!=NULL; last=last->next);

    last->next=n;
}
void List::append(List l) {
    append(l.head);
}

