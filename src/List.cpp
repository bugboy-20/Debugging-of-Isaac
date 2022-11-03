#include "List.hpp"
#include <cstddef>

List::List(){
    this->head=NULL;
}

List::List(node *head)
{
    if (head == NULL)
        this->head = NULL;
    else
    {
        this->head = new node;
        this->head->element = head->element;
        this->head->next = NULL;
        node *tlcn = this->head;

        for (node *cn = head->next; cn != NULL; cn = cn->next)
        {
            tlcn->next = new node;
            tlcn = tlcn->next;
            tlcn->element = cn->element;
            tlcn->next = NULL;
        }
    }
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

    if(head->element==e) {
        tmp=head;
        this->head=head->next;
        delete tmp;
        return true;
    }
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

    if (n!=NULL) {
        for (last=head; last->next!=NULL; last=last->next);
        node *nuovo = new node;
        nuovo->element = n->element;
        nuovo->next = n->next;

        n = n->next;
        last->next=nuovo;
    }
}
void List::append(List& l) {
    append(l.head);
}

