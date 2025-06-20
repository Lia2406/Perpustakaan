/*============================= IMP Buku ==========================*/
#include "buku.h"
#include <stdlib.h>
#include <string.h>

Buku* buat_buku(const char* judul, int stok) {
    Buku* buku = (Buku*)malloc(sizeof(Buku));
    buku->judul = strdup(judul);
    buku->stok = stok;
    buku->antrian_peminjam = buat_antrian();
    return buku;
}

void hapus_buku(Buku* buku) {
    free(buku->judul);
    hapus_antrian(buku->antrian_peminjam);
    free(buku);
}
