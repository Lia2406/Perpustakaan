/*==========================HEADER QUEUE ==================================*/
#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "anggota.h"

typedef struct SimpulAntrian {
    Anggota* anggota;
    struct SimpulAntrian* berikutnya;
} SimpulAntrian;

typedef struct {
    SimpulAntrian* depan;
    SimpulAntrian* belakang;
} Antrian;

Antrian* buat_antrian();
void tambah_antrian(Antrian* antrian, Anggota* anggota);
Anggota* layani_antrian(Antrian* antrian);
int antrian_kosong(Antrian* antrian);
void hapus_antrian(Antrian* antrian);

#endif
