/* =============================== anggota ===================*/
#include "anggota.h"
#include <stdlib.h>
#include <string.h>

Anggota* buat_anggota(const char* nama, JenisAnggota jenis) {
    Anggota* anggota = (Anggota*)malloc(sizeof(Anggota));
    anggota->nama = strdup(nama);
    anggota->jenis = jenis;
    
    switch(jenis) {
        case DOSEN: anggota->prioritas = 1; break;
        case MAHASISWA: anggota->prioritas = 2; break;
        case UMUM: anggota->prioritas = 3; break;
    }
    
    return anggota;
}

void hapus_anggota(Anggota* anggota) {
    free(anggota->nama);
    free(anggota);
}

const char* dapatkan_nama_jenis(JenisAnggota jenis) {
    switch(jenis) {
        case DOSEN: return "Dosen";
        case MAHASISWA: return "Mahasiswa";
        case UMUM: return "Umum";
        default: return "Tidak Dikenal";
    }
}
