/*====================================QUEUE==========================================
*/
#include "antrian.h"
#include <stdlib.h>

Antrian* buat_antrian() {
    Antrian* antrian = (Antrian*)malloc(sizeof(Antrian));
    antrian->depan = antrian->belakang = NULL;
    return antrian;
}

void tambah_antrian(Antrian* antrian, Anggota* anggota) {
    SimpulAntrian* simpul = (SimpulAntrian*)malloc(sizeof(SimpulAntrian));
    simpul->anggota = anggota;
    simpul->berikutnya = NULL;
    
    if (antrian_kosong(antrian)) {
        antrian->depan = antrian->belakang = simpul;
    } else {
        // Antrian prioritas - prioritas lebih tinggi didahulukan
        if (anggota->prioritas < antrian->depan->anggota->prioritas) {
            simpul->berikutnya = antrian->depan;
            antrian->depan = simpul;
        } else {
            SimpulAntrian* sekarang = antrian->depan;
            while (sekarang->berikutnya != NULL && 
                   anggota->prioritas >= sekarang->berikutnya->anggota->prioritas) {
                sekarang = sekarang->berikutnya;
            }
            simpul->berikutnya = sekarang->berikutnya;
            sekarang->berikutnya = simpul;
            if (simpul->berikutnya == NULL) {
                antrian->belakang = simpul;
            }
        }
    }
}

Anggota* layani_antrian(Antrian* antrian) {
    if (antrian_kosong(antrian)) return NULL;
    
    SimpulAntrian* temp = antrian->depan;
    Anggota* anggota = temp->anggota;
    antrian->depan = temp->berikutnya;
    
    if (antrian->depan == NULL) {
        antrian->belakang = NULL;
    }
    
    free(temp);
    return anggota;
}

int antrian_kosong(Antrian* antrian) {
    return antrian->depan == NULL;
}

void hapus_antrian(Antrian* antrian) {
    while (!antrian_kosong(antrian)) {
        layani_antrian(antrian);
    }
    free(antrian);
}
