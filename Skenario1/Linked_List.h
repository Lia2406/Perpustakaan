/*========================================== HEADER LINKED LIST ===================================*/
#ifndef Linked_List_H
#define Linked_List_H

#include "buku.h"

typedef struct Node_List_Buku {
    Buku* buku;
    struct Node_List_Buku* berikutnya;
} Node_List_Buku;

typedef struct {
    Node_List_Buku* kepala;
} Linked_List;

Linked_List* buat_Linked_List();
void Masukkan_Buku_ke_List(Linked_List* daftar, Buku* buku);
Buku* cari_buku(Linked_List* daftar, const char* judul);
void tampilkan_buku(Linked_List* daftar);
void hapus_Linked_List(Linked_List* daftar);

#endif
