#include "singly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRACK_TITLE_SIZE 60                    // Maksimal længde på sang titel

#define PLAYLIST_IN_PATH "playlist.txt"        // Input fil navn
#define PLAYLIST_OUT_PATH "playlist-out.txt"   // Output fil navn

typedef char Data[TRACK_TITLE_SIZE];          // Data type for sang titel
Node *playlist = NULL;                        // Global variabel til vores playlist

// Fjerner linjeskift fra slutningen af en string
char *remove_newline_if_exists(char *line) {
    size_t len = strlen(line);                // Find længden af string
    if (len > 0 && line[len - 1] == '\n')     // Hvis sidste karakter er linjeskift
        line[len - 1] = '\0';                 // Erstat med null terminator
    return line;                              // Returner den modificerede string
}

// Indlæser sange fra fil og bygger linked list
Node **load_file(const char *filename, Node **list) {
    FILE *f = fopen(filename, "r");           // Åben fil til læsning
    if (!f) {                                 // Hvis fil ikke kan åbnes
        perror(filename);                     // Print fejlbesked
        exit(EXIT_FAILURE);                   // Stop programmet
    }

    char line[TRACK_TITLE_SIZE];              // Buffer til at læse hver linje

    while (fgets(line, TRACK_TITLE_SIZE, f)) { // Læs hver linje fra filen
        remove_newline_if_exists(line);        // Fjern linjeskift

        Node *new_node = malloc(sizeof(Node)); // Allokér ny node
        new_node->next = NULL;                 // Sæt next pointer til NULL

        Data *data = malloc(sizeof(Data));    // Allokér plads til sang data
        strcpy(*data, line);                  // Kopiér sang navn til data

        new_node->data = data;                // Tilknyt data til node

        if (*list == NULL) {                  // Hvis listen er tom
            *list = new_node;                 // Sæt ny node som første element
        } else {                              // Ellers
            Node *cur = *list;                // Start fra første node
            while (cur->next)                 // Find sidste node
                cur = cur->next;
            cur->next = new_node;             // Tilføj ny node til slutningen
        }
    }

    fclose(f);                               // Luk filen
    return list;                             // Returner listen
}

// Gemmer playlist til fil
void save_file(const char *filename, Node *list) {
    FILE *f = fopen(filename, "w");          // Åben fil til skrivning
    if (!f) {                                // Hvis fil ikke kan oprettes
        perror(filename);                    // Print fejlbesked
        exit(EXIT_FAILURE);                  // Stop programmet
    }

    Node *current = list;                    // Start fra første node
    while (current) {                        // For hver node i listen
        fprintf(f, "%s\n", *(Data *)current->data); // Skriv sang navn til fil
        current = current->next;             // Gå til næste node
    }

    fclose(f);                              // Luk filen
}

// Printer alle sange med nummerering
void print_tracks(const Node *playlist) {
    const Node *current = playlist;          // Start fra første node
    size_t i = 1;                           // Tæller til nummerering
    while (current) {                       // For hver node
        printf("%2zu: %s\n", i++, (char *)current->data); // Print nummer og sang
        current = current->next;            // Gå til næste node
    }
}

int main() {
    load_file(PLAYLIST_IN_PATH, &playlist); // Indlæs sange fra fil

    puts("Loaded tracks:");                 // Print overskrift
    print_tracks(playlist);                 // Vis alle sange

    size_t node_index_to_del = 4;          // Index for sang der skal slettes (0-baseret)
    free(delete_at(&playlist, node_index_to_del)); // Slet sang og frigør hukommelse

    Node *new_node = malloc(sizeof(Node)); // Opret ny node
    new_node->next = NULL;                  // Sæt next pointer til NULL
    new_node->data = malloc(sizeof(Data)); // Allokér plads til data
    strcpy((char *)new_node->data, "Tarkan – Şımarık 💋"); // Kopiér ny sang navn

    insert_at(&playlist, 3, new_node);     // Indsæt ny sang på position 3

    save_file(PLAYLIST_OUT_PATH, playlist); // Gem opdateret playlist til fil

    return 0;                               // Afslut programmet
}
