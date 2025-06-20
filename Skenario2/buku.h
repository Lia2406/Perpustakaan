/*======================HEADER untuk DAftar Stok Buku=====================*/
#ifndef BUKU_H
#define BUKU_H

#include "antrian.h"

typedef struct {
    char* judul;
    int stok;
    Antrian* antrian_peminjam;
} Buku;

Buku* buat_buku(const char* judul, int stok);
void hapus_buku(Buku* buku);

#endif
