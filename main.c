#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRANSAKSI 100
#define JUMLAH_ALAT 5

// Data peralatan camping
char namaAlat[JUMLAH_ALAT][50] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

int hargaAlat[JUMLAH_ALAT] = {
    50000, 15000, 20000, 10000, 12000
};

// Array untuk menyimpan riwayat transaksi
char namaPenyewa[MAX_TRANSAKSI][100];
int jenisAlat[MAX_TRANSAKSI];
int jumlahUnit[MAX_TRANSAKSI];
int lamaSewa[MAX_TRANSAKSI];
double totalBayar[MAX_TRANSAKSI];

int jumlahTransaksi = 0;

// Fungsi membersihkan input
void bersihkanInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi membaca bilangan bulat
int inputAngka(char pesan[], int min, int max) {
    int angka;
    int hasil;

    while (1) {
        printf("%s", pesan);
        hasil = scanf("%d", &angka);

        if (hasil != 1) {
            printf("Input harus berupa angka!\n");
            bersihkanInput();
            continue;
        }

        bersihkanInput();

        if (angka < min || angka > max) {
            printf("Input tidak valid! Masukkan angka %d sampai %d.\n",
                   min, max);
        } else {
            return angka;
        }
    }
}

// Fungsi menampilkan menu utama
void tampilMenu() {
    printf("\n========================================\n");
    printf("             ADVENTURE CAMP\n");
    printf("       SISTEM PENYEWAAN PERALATAN\n");
    printf("========================================\n");
    printf("1. Lihat Daftar Peralatan\n");
    printf("2. Sewa Peralatan\n");
    printf("3. Lihat Riwayat Transaksi\n");
    printf("4. Keluar\n");
    printf("========================================\n");
}

// Fungsi menampilkan daftar peralatan
void daftarPeralatan() {
    int i;

    printf("\n========================================\n");
    printf("          DAFTAR PERALATAN CAMPING\n");
    printf("========================================\n");

    for (i = 0; i < JUMLAH_ALAT; i++) {
        printf("%d. %-27s Rp%d/hari\n",
               i + 1, namaAlat[i], hargaAlat[i]);
    }

    printf("========================================\n");
}

// Fungsi menghitung persentase diskon
int hitungDiskon(int hari) {
    if (hari >= 5) {
        return 15;
    } else if (hari >= 3) {
        return 10;
    } else {
        return 0;
    }
}

// Fungsi menampilkan struk
void tampilStruk(char nama[], int alat, int unit,
                 int hari, double subtotal,
                 int persenDiskon, double diskon,
                 double total) {

    printf("\n========================================\n");
    printf("             ADVENTURE CAMP\n");
    printf("              STRUK PENYEWAAN\n");
    printf("========================================\n");

    printf("Nama Penyewa   : %s\n", nama);
    printf("Peralatan      : %s\n", namaAlat[alat]);
    printf("Harga per Hari : Rp%d\n", hargaAlat[alat]);
    printf("Jumlah Unit    : %d\n", unit);
    printf("Lama Sewa      : %d hari\n", hari);

    printf("----------------------------------------\n");
    printf("Subtotal       : Rp%.0f\n", subtotal);
    printf("Diskon (%d%%)    : Rp%.0f\n",
           persenDiskon, diskon);
    printf("----------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%.0f\n", total);
    printf("========================================\n");
    printf("Terima kasih telah menggunakan\n");
    printf("layanan Adventure Camp!\n");
}

// Fungsi melakukan penyewaan
int sewaPeralatan() {
    char nama[100];
    char pilihan;
    int alat, unit, hari;
    int persenDiskon;
    double subtotal, diskon, total;

    // Memeriksa kapasitas transaksi
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\nMaaf, kapasitas transaksi sudah penuh!\n");
        return 1;
    }

    printf("\n========================================\n");
    printf("             FORM PENYEWAAN\n");
    printf("========================================\n");

    // Input nama penyewa
    do {
        printf("Masukkan nama penyewa : ");
        fgets(nama, sizeof(nama), stdin);

        nama[strcspn(nama, "\n")] = '\0';

        if (strlen(nama) == 0) {
            printf("Nama tidak boleh kosong!\n");
        }

    } while (strlen(nama) == 0);

    // Menampilkan peralatan
    daftarPeralatan();

    // Input jenis peralatan
    alat = inputAngka(
        "\nPilih nomor peralatan [1-5] : ", 1, 5
    );

    // Input jumlah unit
    unit = inputAngka(
        "Masukkan jumlah unit       : ", 1, 1000
    );

    // Input lama penyewaan
    hari = inputAngka(
        "Masukkan lama sewa (hari)  : ", 1, 365
    );

    // Menghitung subtotal
    subtotal = (double)hargaAlat[alat - 1] * unit * hari;

    // Menghitung diskon
    persenDiskon = hitungDiskon(hari);

    diskon = subtotal * persenDiskon / 100.0;

    // Menghitung total pembayaran
    total = subtotal - diskon;

    // Menyimpan transaksi ke array
    strcpy(namaPenyewa[jumlahTransaksi], nama);

    jenisAlat[jumlahTransaksi] = alat - 1;
    jumlahUnit[jumlahTransaksi] = unit;
    lamaSewa[jumlahTransaksi] = hari;
    totalBayar[jumlahTransaksi] = total;

    jumlahTransaksi++;

    // Menampilkan struk pembayaran
    tampilStruk(
        nama,
        alat - 1,
        unit,
        hari,
        subtotal,
        persenDiskon,
        diskon,
        total
    );

    // Konfirmasi kembali ke menu utama
    do {
        printf("\nKembali ke menu utama? (Y/T): ");
        scanf(" %c", &pilihan);
        bersihkanInput();

        if (pilihan == 'Y' || pilihan == 'y') {
            return 1;
        } else if (pilihan == 'T' || pilihan == 't') {
            return 0;
        } else {
            printf("Pilihan tidak valid! Masukkan Y atau T.\n");
        }

    } while (1);
}

// Fungsi menampilkan riwayat transaksi
void riwayatTransaksi() {
    int i;
    double totalPendapatan = 0;

    printf("\n========================================\n");
    printf("           RIWAYAT TRANSAKSI\n");
    printf("========================================\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        printf("========================================\n");
        return;
    }

    for (i = 0; i < jumlahTransaksi; i++) {
        printf("\nTransaksi ke-%d\n", i + 1);
        printf("----------------------------------------\n");
        printf("Nama Penyewa : %s\n", namaPenyewa[i]);
        printf("Peralatan    : %s\n", namaAlat[jenisAlat[i]]);
        printf("Jumlah Unit  : %d\n", jumlahUnit[i]);
        printf("Lama Sewa    : %d hari\n", lamaSewa[i]);
        printf("Total Bayar  : Rp%.0f\n", totalBayar[i]);

        totalPendapatan += totalBayar[i];
    }

    printf("\n========================================\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%.0f\n", totalPendapatan);
    printf("========================================\n");
}

// Fungsi utama
int main() {
    int menu;
    int lanjut = 1;

    while (lanjut) {
        tampilMenu();

        menu = inputAngka(
            "Pilih menu [1-4]: ", 1, 4
        );

        switch (menu) {
            case 1:
                daftarPeralatan();
                printf("\nTekan ENTER untuk kembali...");
                getchar();
                break;

            case 2:
                lanjut = sewaPeralatan();
                break;

            case 3:
                riwayatTransaksi();
                printf("\nTekan ENTER untuk kembali...");
                getchar();
                break;

            case 4:
                lanjut = 0;
                break;

            default:
                printf("Menu tidak tersedia!\n");
        }
    }

    printf("\n========================================\n");
    printf("       TERIMA KASIH TELAH MENGGUNAKAN\n");
    printf("              ADVENTURE CAMP\n");
    printf("========================================\n");

    return 0;
}
