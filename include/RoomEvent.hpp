#pragma once


enum event_type {
    ENTITY_MOVE,
    ENTITY_KILLED,
    ENTITY_DAMAGED,
    ROOM_CHANGED,
    PLAYER_HEALTH_CHANGED,
    INVENTORY_CHANGED,
    ITEM_PICKED
};

// Classe per gestire gli eventi. 
// è pensata per tenere gli eventi nella stessa struttura, non per creare oggetti in se
// ogni figlio di RoomEvent (che contiene dati aggiuntivi) deve avere un campo di tipo data
class RoomEvent {
    public:
        RoomEvent(event_type);
        //identifica il tipo di evento
        event_type id;
};
