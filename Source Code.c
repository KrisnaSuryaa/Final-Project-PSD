#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define size 7

struct menu{
    char menu_baru[30];
    int harga;
    int isi;
    int kode;
}id[MAX];

struct queue{
    char nama[10];
    int banyak;
    int total;
    int nomor;
    struct pesanan{
        char menu[30];
        int harga;
    }data[MAX];
}antrian[MAX];

int head = -1, tail = -1,no_order=1,cek,key;

int isempty()
{
    if(tail == -1)
        return 1;
    else
        return 0;
}

int isfull()
{
    if(tail == MAX - 1)
        return 1;
    else
        return 0;
}

void enqueue()
{
    int code, uang, sisa;
    if(isempty()){
        head = tail = 0;
        enqueue();
    }
    else if(isfull()){
        printf("\nAntrian Sudah Penuh!");
    }
    else{
        lihat_menu();
        printf("\n===================================\n");
        printf("       NOMOR ANTRIAN ANDA\n\t      0%d\n", no_order);
        printf("    Antrian Yang Menunggu : %d\n", tail);
        printf("===================================\n");
        printf("\nMasukan Nama Pelanggan : ");
        fflush(stdin);
        fgets(antrian[tail].nama,10,stdin);
        printf("\nBanyak menu yang ingin dipesan : ");
        scanf("%d", &antrian[tail].banyak);
        for(int i=0; i<antrian[tail].banyak; i++)
        {
            printf("\nKode Menu %d      : ", i+1);
            scanf("%d",&code);
            int b = code-10;
            strcpy(antrian[tail].data[i].menu,id[b].menu_baru);
            antrian[tail].data[i].harga = id[b].harga;
        }
        antrian[tail].total=0;
        for(int i=0; i<antrian[tail].banyak; i++)
        {
            antrian[tail].total = antrian[tail].total + antrian[tail].data[i].harga;
        }
        printf("\nTotal Bayar = Rp %d", antrian[tail].total);
        printf("\nJumlah Uang = Rp ", uang);
        scanf("%d", &uang);
        printf("             ----------");
        sisa = uang - antrian[tail].total;
        printf("\nKembalian   = Rp %d\n", sisa);
        antrian[tail].nomor = no_order;
        ++no_order;
        ++tail;
    }
}

void lihat_antrian()
{
    if(isempty()){
        printf("\nMaaf, antrian kosong!\n");
    }
    else{
        printf("\nData Antrian Saat Ini :\n");
        printf("\nNo Antrian\tNama Pelanggan\tPesanan\n");
        for(int i=head;i<tail;i++)
        {
            int count = antrian[i].banyak;
            printf("%d\t\t%s",antrian[i].nomor,antrian[i].nama);
            for(int j=0;j<count;j++){
                printf("\t\t\t\t%s\n",antrian[i].data[j].menu);
            }
        }
    }
}

void dequeue()
{
    int count;
    if(isempty()){
        printf("\nMaaf, antrian kosong!\n");
    }
    else{
        for(int i=head;i<tail;i++){
            if(antrian[i].banyak>antrian[i+1].banyak){
                count=antrian[i].banyak;
            }
            if(antrian[i].banyak>antrian[i+1].banyak){
                count=antrian[i].banyak;
            }
            if(antrian[i].banyak<antrian[i+1].banyak){
                count=antrian[i+1].banyak;
            }
            for(int j=0;j<count;j++){
                strcpy(antrian[i].data[j].menu,antrian[i+1].data[j].menu);
                antrian[i].data[j].harga = antrian[i+1].data[j].harga;
            }
            strcpy(antrian[i].nama,antrian[i+1].nama);
            antrian[i].banyak = antrian[i+1].banyak;
            antrian[i].total = antrian[i+1].total;
            antrian[i].nomor = antrian[i+1].nomor;
        }
        tail--;
        printf("\nAntrian Berhasil Dihapus!");
        if(tail==0){
            head=-1;
            tail=-1;
        }
    }
}

void clear()
{
    if(isempty()){
        printf("\nMaaf, antrian kosong!\n");
    }
    else{
        head=tail=-1;
        printf("\nAntrian Berhasil Dikosongkan!");
    }
}

int hash(int panjang){
    cek=0;
    key=panjang%size;
    if(id[key].isi==0){
        cek=1;
        return 1;
    }
    else{
        return hash(panjang+1);
    }
}

void tambah_menu()
{
    char *new_menu = NULL;
    size_t n=1, length;

    new_menu = malloc(n+1);
    printf("===============================\n");
    printf("  MENAMBAH MENU RRUMAH MAKAN\n");
    printf("===============================\n\n");
    printf("Masukkan Nama Menu Baru : ");
    scanf("%s", new_menu);

    length = strlen(new_menu);
    hash(length);
    if(cek==1){
        int b = key;
        id[key].isi=1;
        strcpy(id[key].menu_baru,new_menu);
        printf("\nMasukkan Harga Menu : ");
        scanf("%d",&id[key].harga);
        id[key].kode=b+10;
        printf("Kode Menu : %d",id[key].kode);
    }
    else{
        printf("Maaf Data Menu Sudah Penuh!");
    }
}

void lihat_menu()
{
    printf("\nDaftar Menu :\n");
    printf("\nKode Menu\tNama Menu\t\tHarga\n");
    for(int i=0;i<MAX;i++){
        if(id[i].isi==1){
            printf("%d\t\t%s\t\t%d\n",id[i].kode,id[i].menu_baru,id[i].harga);
        }
    }
}

void title(){
    system ("cls");
    printf("=============== PROGRAM ANTRIAN RUMAH MAKAN ===============\n\n");
}

int main()
{
    for(int i=0; i<MAX; i++){
    id[i].isi=0;
    }

    memcpy(id[0].menu_baru, "Ayam_Goreng", 12);
    id[0].harga=18000;
    id[0].isi=1;
    id[0].kode=10;

    memcpy(id[1].menu_baru, "Bakso_Ayam", 11);
    id[1].harga=10000;
    id[1].isi=1;
    id[1].kode=11;

    memcpy(id[2].menu_baru, "Es_Teh_Hangat", 13);
    id[2].harga=3000;
    id[2].isi=1;
    id[2].kode=12;

    int pil,out;

    do{
            title();
            printf("Pilihan Menu : \n");
            printf("   1. Tambah Antrian\n");
            printf("   2. Lihat Antrian\n");
            printf("   3. Pelayanan\n");
            printf("   4. Kosongkan Antrian\n");
            printf("   5. Tambah Menu\n");
            printf("   6. Lihat Menu\n");
            printf("   7. Exit\n");
            printf("\nKetik Pilihan : ");
            scanf("%d", &pil);
            switch(pil)
            {
                case 1:
                    enqueue();
                    getch();
                    break;
                case 2 :
                    lihat_antrian();
                    getch();
                    break;
                case 3 :
                    dequeue();
                    getch();
                    break;
                case 4 :
                    clear();
                    getch();
                    break;
                case 5 :
                    tambah_menu();
                    getch();
                    break;
                case 6 :
                    lihat_menu();
                    getch();
                    break;
            }
        }while(pil!=7);
        printf("\nAnda Yakin Ingin Keluar? Tekan 1 Jika Ya ");\
        scanf("%d",&out);
        if(out!=1){
            main ();
        }
        return 0;
}
