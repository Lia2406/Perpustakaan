/*========================== HEADER Aktivitas ==========================*/
#ifndef Aktivitas_H
#define Aktivitas_H

#include "Stack.h"
#include "Linked_List.h"

typedef struct {
    Linked_List* daftar_buku;
    Stack* Stack_aktivitas;
} SistemPerpustakaan;

SistemPerpustakaan* buat_sistem_perpustakaan();
void tambah_buku(SistemPerpustakaan* sistem, const char* judul, int stok);
void pinjam_buku(SistemPerpustakaan* sistem, const char* judul, Anggota* anggota);
void proses_peminjaman(SistemPerpustakaan* sistem, const char* judul);
void kembalikan_buku(SistemPerpustakaan* sistem, const char* judul);
void batalkan_peminjaman(SistemPerpustakaan* sistem, const char* nama_anggota, const char* judul_buku);
void batalkan_aksi_terakhir(SistemPerpustakaan* sistem);
void tampilkan_status(SistemPerpustakaan* sistem);
void hapus_sistem_perpustakaan(SistemPerpustakaan* sistem);

#endif
