/*================================== Linked_List======================*/
#include "Linked_List.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Linked_List* buat_Linked_List() {
    Linked_List* daftar = (Linked_List*)malloc(sizeof(Linked_List));
    daftar->kepala = NULL;
    return daftar;
}

void Masukkan_Buku_ke_List(Linked_List* daftar, Buku* buku) {
    Node_List_Buku* simpul = (Node_List_Buku*)malloc(sizeof(Node_List_Buku));
    simpul->buku = buku;
    simpul->berikutnya = daftar->kepala;
    daftar->kepala = simpul;
}

Buku* cari_buku(Linked_List* daftar, const char* judul) {
    Node_List_Buku* sekarang = daftar->kepala;
    while (sekarang != NULL) {
        if (strcmp(sekarang->buku->judul, judul) == 0) {
            return sekarang->buku;
        }
        sekarang = sekarang->berikutnya;
    }
    return NULL;
}

void tampilkan_buku(Linked_List* daftar) {
    Node_List_Buku* sekarang = daftar->kepala;
    while (sekarang != NULL) {
        printf("Buku: %s, Stok: %d\n", sekarang->buku->judul, sekarang->buku->stok);
        printf("  Antrian peminjam:\n");
        tampilkan_antrian(sekarang->buku->antrian_peminjam);
        sekarang = sekarang->berikutnya;
    }
}

void hapus_Linked_List(Linked_List* daftar) {
    Node_List_Buku* sekarang = daftar->kepala;
    while (sekarang != NULL) {
        Node_List_Buku* temp = sekarang;
        sekarang = sekarang->berikutnya;
        hapus_buku(temp->buku);
        free(temp);
    }
    free(daftar);
}
