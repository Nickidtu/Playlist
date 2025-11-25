#ifndef SINGLY_LINKED_LIST_H                  // Tjek om header ikke allerede er inkluderet
#define SINGLY_LINKED_LIST_H                  // Definer header guard navn

#include <stddef.h>                           // Inkluder for size_t type

typedef struct Node {                         // Definer Node struktur
    void *data;                              // Pointer til data (kan være hvilken som helst type)
    struct Node *next;                       // Pointer til næste node i listen
} Node;                                      // Giv strukturen navnet "Node"

// Indsætter en ny node på specificeret index position
void insert_at(Node **list, size_t index, Node *new_node);

// Sletter node på specificeret index og returnerer dens data
void *delete_at(Node **list, size_t index);

#endif                                       // Slut header guard
