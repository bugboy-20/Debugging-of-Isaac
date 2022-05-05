#pragma once


enum event_type {
    ENTITY_MOVE,
    ENTITY_KILLED
};

// Classe per gestire gli eventi. 
// è pensata per tenere gli eventi nella stessa struttura, non per creare oggetti in se
// ogni figlio di RoomEvent deve avere un campo di tipo data
class RoomEvent {
    public:
        RoomEvent(event_type);
        //identifica il tipo di evento
        event_type id;
};
