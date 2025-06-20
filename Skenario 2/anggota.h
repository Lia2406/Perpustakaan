/*================================HEADER Untuk Anggota Perpustakan=====================================*/
#ifndef ANGGOTA_H
#define ANGGOTA_H

typedef enum { DOSEN, MAHASISWA, UMUM } JenisAnggota;

typedef struct {
    char* nama;
    JenisAnggota jenis;
    int prioritas; // Angka lebih kecil = prioritas lebih tinggi
} Anggota;

Anggota* buat_anggota(const char* nama, JenisAnggota jenis);
void hapus_anggota(Anggota* anggota);
const char* dapatkan_nama_jenis(JenisAnggota jenis);

#endif
