/*================================ IMP Aktivitas ===============*/
#include "Aktivitas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SistemPerpustakaan* buat_sistem_perpustakaan() {
    SistemPerpustakaan* sistem = (SistemPerpustakaan*)malloc(sizeof(SistemPerpustakaan));
    sistem->daftar_buku = buat_Linked_List();
    sistem->Stack_aktivitas = buat_Stack();
    return sistem;
}

void tambah_buku(SistemPerpustakaan* sistem, const char* judul, int stok) {
    Buku* buku = buat_buku(judul, stok);
    Masukkan_Buku_ke_List(sistem->daftar_buku, buku);
    
    char aktivitas[100];
    snprintf(aktivitas, sizeof(aktivitas), "Menambah buku: %s (Stok: %d)", judul, stok);
    tumpuk(sistem->Stack_aktivitas, aktivitas);
}

void pinjam_buku(SistemPerpustakaan* sistem, const char* judul, Anggota* anggota) {
    Buku* buku = cari_buku(sistem->daftar_buku, judul);
    if (!buku) {
        printf("Buku tidak ditemukan: %s\n", judul);
        return;
    }
    
    tambah_antrian(buku->antrian_peminjam, anggota);
    
    char aktivitas[100];
    snprintf(aktivitas, sizeof(aktivitas), "%s (%s) memesan %s", 
             anggota->nama, dapatkan_nama_jenis(anggota->jenis), judul);
    tumpuk(sistem->Stack_aktivitas, aktivitas);
}

void proses_peminjaman(SistemPerpustakaan* sistem, const char* judul) {
    Buku* buku = cari_buku(sistem->daftar_buku, judul);
    if (!buku) {
        printf("Buku tidak ditemukan: %s\n", judul);
        return;
    }
    
    if (buku->stok <= 0) {
        printf("Stok buku %s habis\n", judul);
        return;
    }
    
    if (antrian_kosong(buku->antrian_peminjam)) {
        printf("Tidak ada antrian untuk buku %s\n", judul);
        return;
    }
    
    Anggota* anggota = layani_antrian(buku->antrian_peminjam);
    buku->stok--;
    
    char aktivitas[100];
    snprintf(aktivitas, sizeof(aktivitas), "%s telah meminjam %s", anggota->nama, judul);
    tumpuk(sistem->Stack_aktivitas, aktivitas);
    
    printf("%s (%s) berhasil meminjam %s\n", 
           anggota->nama, dapatkan_nama_jenis(anggota->jenis), judul);
}

void kembalikan_buku(SistemPerpustakaan* sistem, const char* judul) {
    Buku* buku = cari_buku(sistem->daftar_buku, judul);
    if (!buku) {
        printf("Buku tidak ditemukan: %s\n", judul);
        return;
    }
    
    buku->stok++;
    
    char aktivitas[100];
    snprintf(aktivitas, sizeof(aktivitas), "Buku dikembalikan: %s", judul);
    tumpuk(sistem->Stack_aktivitas, aktivitas);
    
    printf("Buku dikembalikan: %s\n", judul);
    
    // Proses antrian berikutnya jika ada
    if (!antrian_kosong(buku->antrian_peminjam)) {
        proses_peminjaman(sistem, judul);
    }
}

void batalkan_peminjaman(SistemPerpustakaan* sistem, const char* nama_anggota, const char* judul_buku) {
    Buku* buku = cari_buku(sistem->daftar_buku, judul_buku);
    if (!buku) {
        printf("Buku '%s' tidak ditemukan.\n", judul_buku);
        return;
    }

    Antrian* antrian_asli = buku->antrian_peminjam;
    int ditemukan = 0;

    if (antrian_kosong(antrian_asli)) {
        printf("Tidak ada antrian untuk buku '%s'.\n", judul_buku);
        return;
    }

    Antrian* antrian_baru = buat_antrian();
    while (!antrian_kosong(antrian_asli)) {
        Anggota* anggota_sekarang = layani_antrian(antrian_asli);
        if (strcmp(anggota_sekarang->nama, nama_anggota) == 0) {
            printf("Membatalkan pemesanan '%s' untuk buku '%s'.\n", nama_anggota, judul_buku);
            hapus_anggota(anggota_sekarang);
            ditemukan = 1;
        } else {
            tambah_antrian(antrian_baru, anggota_sekarang);
        }
    }

    free(antrian_asli);
    buku->antrian_peminjam = antrian_baru;

    if (ditemukan) {
        char aktivitas[200];
        snprintf(aktivitas, sizeof(aktivitas), "Membatalkan pemesanan %s untuk buku %s", nama_anggota, judul_buku);
        tumpuk(sistem->Stack_aktivitas, aktivitas);
    } else {
        printf("Anggota dengan nama '%s' tidak ditemukan dalam antrian buku '%s'.\n", nama_anggota, judul_buku);
    }
}

void batalkan_aksi_terakhir(SistemPerpustakaan* sistem) {
    char* aksi = ambil_dari_Stack(sistem->Stack_aktivitas);
    if (aksi) {
        printf("Membatalkan: %s\n", aksi);
        free(aksi);
    } else {
        printf("Tidak ada aksi untuk dibatalkan\n");
    }
}

void tampilkan_status(SistemPerpustakaan* sistem) {
    printf("\n=== STATUS PERPUSTAKAAN ===\n");
    
    Node_List_Buku* sekarang = sistem->daftar_buku->kepala;
    while (sekarang != NULL) {
        Buku* buku = sekarang->buku;
        printf("\nBuku: %s (Stok: %d)\n", buku->judul, buku->stok);
        
        if (antrian_kosong(buku->antrian_peminjam)) {
            printf("  Tidak ada antrian\n");
        } else {
            printf("peminjam saat ini:\n");
            // Disederhanakan - hanya tampilkan yang terdepan
            if (buku->antrian_peminjam->depan) {
                printf("    - %s (%s)\n", 
                       buku->antrian_peminjam->depan->anggota->nama,
                       dapatkan_nama_jenis(buku->antrian_peminjam->depan->anggota->jenis));
            }
        }
        
        sekarang = sekarang->berikutnya;
    }
    
    printf("\nAktivitas Terakhir:\n");
    if (!Stack_kosong(sistem->Stack_aktivitas)) {
        printf("  - %s\n", sistem->Stack_aktivitas->puncak->data);
    }
    
    printf("=====================\n");
}

void hapus_sistem_perpustakaan(SistemPerpustakaan* sistem) {
    hapus_Linked_List(sistem->daftar_buku);
    hapus_Stack(sistem->Stack_aktivitas);
    free(sistem);
}
