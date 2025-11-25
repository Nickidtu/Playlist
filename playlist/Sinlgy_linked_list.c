#include "singly_linked_list.h"               // Inkluder vores header fil
#include <stdlib.h>                           // Inkluder for malloc og free

// Funktion til at indsætte en node på specificeret position
void insert_at(Node **list, size_t index, Node *new_node) {
    if (index == 0) {                         // Hvis vi skal indsætte på position 0 (først i listen)
        new_node->next = *list;               // Ny nodes next peger på den nuværende første node
        *list = new_node;                     // Opdater list pointer til at pege på ny node
        return;                               // Afslut funktionen
    }

    Node *current = *list;                    // Start fra første node
    for (size_t i = 0; i < index - 1; i++) { // Gå til positionen før hvor vi vil indsætte
        if (!current) return;                 // Hvis vi løber tør for nodes, stop
        current = current->next;              // Gå til næste node
    }

    new_node->next = current->next;           // Ny nodes next peger på den node der kommer efter current
    current->next = new_node;                // Current nodes next peger nu på vores nye node
}

// Funktion til at slette en node på specificeret position og returnere dens data
void *delete_at(Node **list, size_t index) {
    if (!*list) return NULL;                 // Hvis listen er tom, returner NULL

    Node *to_del;                            // Pointer til den node vi skal slette
    if (index == 0) {                        // Hvis vi skal slette første node
        to_del = *list;                      // Gem reference til første node
        *list = (*list)->next;               // Opdater list pointer til næste node
        void *data = to_del->data;           // Gem data før vi sletter noden
        free(to_del);                        // Frigør hukommelse for noden
        return data;                         // Returner data
    }

    Node *current = *list;                   // Start fra første node
    for (size_t i = 0; i < index - 1; i++) { // Gå til positionen før den vi vil slette
        if (!current->next) return NULL;     // Hvis der ikke er flere nodes, returner NULL
        current = current->next;             // Gå til næste node
    }

    to_del = current->next;                  // Den node vi skal slette er den næste
    if (!to_del) return NULL;                // Hvis der ikke er en node at slette, returner NULL

    current->next = to_del->next;            // Spring over den node vi sletter

    void *data = to_del->data;               // Gem data før vi sletter
    free(to_del);                            // Frigør hukommelse for noden
    return data;                             // Returner data
}
