#include <stdio.h>
#include <string.h>
#include "aktivitas.h"
#include "anggota.h"

void mode_simulasi(SistemPerpustakaan* perpustakaan) {
    printf("==================== Simulasi Sistem Perpustakaan ======================\n\n");
    // a) Tambah 2 buku
    printf("a) Menambah buku...\n");
    tambah_buku(perpustakaan, "Buku1", 1);
    tambah_buku(perpustakaan, "Buku2", 1);
    // b) Anggota1 (mahasiswa) memesan Buku1
    printf("\nb) Mahasiswa memesan Buku1...\n");
    Anggota* anggota1 = buat_anggota("Anggota1", MAHASISWA);
    pinjam_buku(perpustakaan, "Buku1", anggota1);
    // c) Dosen1 memesan Buku1
    printf("\nc) Dosen memesan Buku1...\n");
    Anggota* dosen1 = buat_anggota("Dosen1", DOSEN);
    pinjam_buku(perpustakaan, "Buku1", dosen1);
    // d) Umum1 memesan Buku1
    printf("\nd) Umum memesan Buku1...\n");
    Anggota* umum1 = buat_anggota("Umum1", UMUM);
    pinjam_buku(perpustakaan, "Buku1", umum1);
    // e) Umum1 memesan Buku2
    printf("\ne) Umum memesan Buku2...\n");
    pinjam_buku(perpustakaan, "Buku2", umum1);
    // Tampilkan status
    printf("\nStatus saat ini:\n");
    tampilkan_status(perpustakaan);
    // f) Proses peminjaman Buku1
    printf("\nf) Memproses peminjaman Buku1...\n");
    proses_peminjaman(perpustakaan, "Buku1");
    tampilkan_status(perpustakaan);
    // g) Kembalikan Buku1
    printf("\ng) Mengembalikan Buku1...\n");
    kembalikan_buku(perpustakaan, "Buku1");
    tampilkan_status(perpustakaan);
    // h) Batalkan pemesanan Umum1
    printf("\nh) Membatalkan pemesanan Umum1...\n");
    batalkan_peminjaman(perpustakaan, "Umum1");
    tampilkan_status(perpustakaan);
    // Bersihkan memori
    hapus_anggota(anggota1);
    hapus_anggota(dosen1);
    hapus_anggota(umum1);
}

void mode_manual(SistemPerpustakaan* perpustakaan) {
    int running = 1;
    while (running) {
        printf("\n===== MENU PERPUSTAKAAN =====\n");
        printf("1. Tambah Buku\n");
        printf("2. Pinjam Buku\n");
        printf("3. Kembalikan Buku\n");
        printf("4. Tampilkan Status\n");
        printf("5. Lihat Daftar Buku & Antrian\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        int pilih;
        scanf("%d", &pilih);
        getchar(); // buang newline
        if (pilih == 1) {
            char judul[100];
            int stok;
            printf("Judul buku: ");
            fgets(judul, sizeof(judul), stdin);
            judul[strcspn(judul, "\n")] = 0;
            printf("Stok: ");
            scanf("%d", &stok);
            getchar();
            tambah_buku(perpustakaan, judul, stok);
            printf("Buku berhasil ditambah!\n");
        } else if (pilih == 2) {
            char judul[100], nama[100];
            int jenis;
            printf("Judul buku: ");
            fgets(judul, sizeof(judul), stdin);
            judul[strcspn(judul, "\n")] = 0;
            printf("Nama peminjam: ");
            fgets(nama, sizeof(nama), stdin);
            nama[strcspn(nama, "\n")] = 0;
            printf("Jenis anggota ( 0: DOSEN, 1: MAHASISWA, 2: UMUM): ");
            scanf("%d", &jenis);
            getchar();
            Anggota* anggota = buat_anggota(nama, jenis);
            pinjam_buku(perpustakaan, judul, anggota);
            printf("Permintaan peminjaman dicatat!\n");
        } else if (pilih == 3) {
            char judul[100];
            printf("Judul buku yang dikembalikan: ");
            fgets(judul, sizeof(judul), stdin);
            judul[strcspn(judul, "\n")] = 0;
            kembalikan_buku(perpustakaan, judul);
        } else if (pilih == 4) {
            tampilkan_status(perpustakaan);
        } else if (pilih == 5) {
        	tampilkan_buku(perpustakaan->daftar_buku);
            
        } else if (pilih == 6) {
            running = 0;
        } else {
            printf("Pilihan tidak valid!\n");
        }
    }
}

int main() {
    SistemPerpustakaan* perpustakaan = buat_sistem_perpustakaan();
    printf("==================== SISTEM PERPUSTAKAAN =====================\n");
    printf("Pilih mode:\n");
    printf("1. Simulasi Otomatis\n");
    printf("2. Mode Manual (Input Pengguna)\n");
    printf("Pilihan Anda: ");
    int mode;
    scanf("%d", &mode);
    getchar(); // buang newline
    if (mode == 1) {
        mode_simulasi(perpustakaan);
    } else if (mode == 2) {
        mode_manual(perpustakaan);
    } else {
        printf("Pilihan tidak valid!\n");
    }
    hapus_sistem_perpustakaan(perpustakaan);
    return 0;
}
