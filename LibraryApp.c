#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int secim, numara, input, sifre, sifre1 = 1111, syc = 0;
char ad[10], soyAd[20];

struct dugum {
    int numara;
    char kitapAdi[20];
    char kitapTuru[30];
    int sayfaSayisi;
    char soyAd[12];
    char ad[20];
    struct dugum *next;
};

typedef struct dugum kutuphane;
typedef struct dugum ogrenci;
struct dugum *dizi[10];
int konum;
ogrenci *start2 = NULL;
kutuphane *start = NULL;

struct dugum *newnode() { //yeni dugum olusturur hash yapisi icin
    struct dugum *yenidugum = (struct dugum *) malloc(sizeof(struct dugum));
    yenidugum->numara = NULL;
    yenidugum->next = NULL;
    return yenidugum;
}

int hashHesapla(int gelen) { // hash yapisinda ogrencilerin numaralarinin modunu alir
    return gelen % 10;
}

struct dugum *hash() { //hash yapisinin bagli liste alma ve yerlestirme isleminin yapildigi yer (govde)
    int sayac = 1;
    struct dugum *kisiadi = (struct dugum *) malloc(sizeof(struct dugum));
    char hashIsim[20];
    char hashSoyIsim[20];
    char hashKitap[20];
    int eklenecek;
    printf("lutfen adinizi giriniz: ");
    scanf("%s", &hashIsim);
    printf("soyadinizi giriniz: ");
    scanf("%s", &hashSoyIsim);

    printf("lutfen ogrenci numaranizi giriniz : ");
    scanf("%d", &eklenecek);
    printf("Almak istediginiz kitabin adini giriniz: ");
    scanf("%s", &hashKitap);
    kutuphane *temp = start;
    while (temp != NULL) {
        if (strcmp(temp->kitapAdi, hashKitap) == 0) {
            konum = hashHesapla(eklenecek);
            if (dizi[konum] == NULL) { //eğer hash in o indisinde eleman yoksa ilk elemanı ekler
                dizi[konum]->numara = eklenecek;
                strcpy(dizi[konum]->kitapAdi, hashKitap);
                strcpy(dizi[konum]->ad, hashIsim);
                strcpy(dizi[konum]->soyAd, hashSoyIsim);
            } else { //eğer indiste başka bi eleman varsa çakışma olunca yanına bir düğüm daha ekler
                struct dugum *yenidugum = newnode();
                yenidugum->numara = eklenecek;
                strcpy(yenidugum->kitapAdi, hashKitap);
                strcpy(yenidugum->ad, hashIsim);
                strcpy(yenidugum->soyAd, hashSoyIsim);

                struct dugum *temp = dizi[konum];
                while (temp->next != NULL)
                    temp = temp->next;
                temp->next = yenidugum;
            }
            strcpy(kisiadi->ad, hashIsim);
            strcpy(kisiadi->soyAd, hashIsim);
            strcpy(kisiadi->kitapAdi, hashKitap);
            return kisiadi;
            sayac++;
        }
        temp = temp->next;
    }
    printf("Aradiginiz Kitap Kutuphanemizde Mevcut Degildir\n");
};
void startdel(){ //hash silme islemi icin ara fonksiyondur
    struct dugum *second = NULL;
    second = start -> next;
    free(start);
    start = second;
}

void init() { //hash deki indis yapisini olusturan ara fonksiyondur
int i;
    for (i = 0; i < 10; i++) {
        dizi[i] = newnode();
    }
}

struct dugum *search() {//ogrencilerin aldigi kitaplari iade etmesi islemi olarak da soylenebilir
    int searcing;
    printf("lutfen aramak istediginiz ogrenciyi giriniz:");
    scanf("%d", &searcing);
    konum = hashHesapla(searcing);
    if (dizi[konum]->numara == searcing) {
        return dizi[konum];
    } else {
        struct dugum *temp = dizi[konum];
        while (temp != NULL) {
            if (temp->numara == searcing) {
                printf(" => numara: %d ,ogrenci adi: %s ,kitap adi: %s", temp->numara, temp->ad, temp->kitapAdi);
                struct dugum *before = NULL;
                struct dugum *after = NULL;
                struct dugum *q = start;
                if(q ->numara == searcing){
                    startdel();
                    printf("Aranilan %d elemani silindi. \n",searcing);
                }
                else {
                    while (q -> next -> numara != searcing){
                        q = q -> next ;
                    }
                    before = q ;
                    after = q ->next ->next ;
                    free(q->next);
                    before -> next = after;
                    printf("Aranilan %d elemani silindi. \n",searcing);
                }
            }
            temp = temp->next;
        }
    }
    printf("aranan ogrenci bulunamadi");
}

void yazdir() { //hash yapisini yazdiran fonksiyondur
int i;
    for (i = 0; i < 10; i++) {
        printf("\n %d. indis ", i);
        struct dugum *temp = dizi[i]->next;
        while (temp != NULL) {
            printf(" => numara: %d , ad: %s, kitap adi: %s", temp->numara, temp->ad, temp->kitapAdi);
            temp = temp->next;
        }
    }
}

void sonaEkle() //  bagli liste ile kitap ekleme islemidir
{

    kutuphane *kitaplar = (kutuphane *) malloc(sizeof(kutuphane));
    printf("Eklemek Istediginiz Kitabin Adini Giriniz :");
    scanf("%s", &kitaplar->kitapAdi);
    printf("Eklemek Istediginiz Kitabin Turu :");
    scanf("%s", &kitaplar->kitapTuru);
    printf("Eklemek Istediginiz Kitabin Sayfa Sayisi :");
    scanf("%d", &kitaplar->sayfaSayisi);
    printf("kitap kaydedildi!!!");

    if (start == NULL) {
        start = kitaplar;
    } else {
        kutuphane *temp = start;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = kitaplar;
    }
}

void sonaEkle2() // bagli liste ile ogrenci eklem islemidir
{

    ogrenci *ogrenciler = (ogrenci *) malloc(sizeof(ogrenci));
    printf("Adinizi Giriniz :");
    scanf("%s", &ogrenciler->ad);
    printf("soyadinizi giriniz :");
    scanf("%s", &ogrenciler->soyAd);
    printf("numaranizi giriniz:");
    scanf("%d", &ogrenciler->numara);
    printf("ogrenci kaydedildi!!!");

    if (start2 == NULL) {
        start2 = ogrenciler;
    } else {
        ogrenci *temp = start2;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = ogrenciler;
    }
}

void listele() { //kutuphaneye kaydedilen kitaplari listeleyen fonksiyondur

    kutuphane *temp = start;
    // system("cls");
    if (start == NULL) {
        printf("Kutuphanede Listelenecek Eleman Yok !!!\n");
        start = NULL;
    } else {
        kutuphane *temp = start;
        while (temp != NULL) {
            printf("Kitap Adi:%s  Kitap Turu :%s Sayfa Sayisi :%d\n ", temp->kitapAdi, temp->kitapTuru,
                   temp->sayfaSayisi);
            temp = temp->next;
        }
    }
}

void listele2() { //uyelik olusturulan ogrencileri listeleyen fonksiyondur

    ogrenci *temp = start2;
    // system("cls");
    if (start2 == NULL) {
        printf("Kutuphanede Listelenecek ogrenci Yok !!!\n");
        start2 = NULL;
    } else {
        ogrenci *temp = start2;
        while (temp != NULL) {
            printf("ogrenci Adi:%s  ogrenci soyadi :%s numarasi :%d\n ", temp->ad, temp->soyAd, temp->numara);
            temp = temp->next;
        }
    }
}

void kitapArama() { //ozellikle oğrencilerin aradiklari kitaplarin kutuphanede olup olmadigini sorgulayan fonksiyondur
    if (start == NULL) {
        printf("Kutuphanede Listelenecek Eleman Yok !!!\n");
    } else {
        char deger[30];
        kutuphane *temp = start;
        printf("Aramak Istediginiz Kitabin Adini Giriniz :");
        scanf("%s", &deger);
        while (temp != NULL) {
            if (strcmp(temp->kitapAdi, deger) == 0) {
                printf("Aradiginiz Kitap Kutuphanede Mevcuttur");
                return;
            }
            temp = temp->next;
        }
        printf("Aradiginiz Kitap Kutuphanemizde Mevcut Degildir");
    }
}

void bastanSil() { // kitap silme islemi icin kullanilan bir ara fonksiyondur
    if (start != NULL) {
        kutuphane *temp = start;
        temp = start->next;
        free(start);
        start = temp;
    } else {
        free(start);
    }
}

void sondanSil() { // kitap silme islemi icin kullanilan bir ara fonksiyondur
    if (start->next != NULL) {
        kutuphane *temp = start;
        temp = start;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    } else
        bastanSil();
}

void aradanSil() { // kitap silme islemi icin kullanilan asil fonksiyondur
    char silme[30];
    int x=0;
    printf("Silmek Istediginiz Kitabin Adini Giriniz : ");
    scanf("%s", &silme);
    kutuphane *temp = start;
    temp = start;
    kutuphane *temp3=start;
    while(temp3!=NULL){
        if(strcmp(temp3->kitapAdi, silme) == 0){
            x=1;
        }
        temp3=temp3->next;
    }
    if (start != NULL) {

        if (strcmp(temp->kitapAdi, silme) == 0) {
            bastanSil();
        } 
		else if(x==1){
            kutuphane *temp2;
            temp2 = (kutuphane *) malloc(sizeof(kutuphane));
            while (strcmp(temp->next->kitapAdi, silme) != 0) {
                temp = temp->next;
            }
            if (temp->next->next == NULL) {
                sondanSil();
            } else {
                temp2 = temp->next->next;
                free(temp->next);
                temp->next = temp2;
            }
        }
        else if(x==0)
        {
            printf("Silinecek Kitap Yoktur\n");
            
		}
    }   
    else 
    {
        printf("kitap yok");
    }
}

void bastanSil2() { // ogrencilerin uyelik kayitlarini silmek icin kullanilan bir ara fonksiyondur
    if (start2 != NULL) {
        ogrenci *temp = start2;
        temp = start2->next;
        free(start2);
        start2 = temp;
    } else {
        free(start2);
    }
}

void sondanSil2() { // ogrencilerin uyelik kayitlarini silmek icin kullanilan bir ara fonksiyondur
    if (start2->next != NULL) {
        ogrenci *temp = start2;
        temp = start2;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
    } else
        bastanSil2();
}

void aradanSil2() { // ogrencilerin uyelik kayitlarini silmek icin kullanilan asil fonksiyondur
    int silme;
    printf("Silmek Istediginiz ogrencinin numarasini Giriniz : ");
    scanf("%d", &silme);
    ogrenci *temp = start2;
    temp = start2;
    if (start2 != NULL) {

        if (temp->numara == silme) {
            bastanSil2();
        } else {
            ogrenci *temp2;
            temp2 = (ogrenci *) malloc(sizeof(ogrenci));

            while (temp->next->numara != silme) {
                temp = temp->next;
            }
            if (temp->next->next == NULL) {
                sondanSil2();
            } else {
                temp2 = temp->next->next;
                free(temp->next);
                temp->next = temp2;
            }
        }
    } else {
        printf("ogrenci yok");
    }
}

int main() {
    do {
        int x;
        printf("*****************MENU*********************\n");
        printf("*                   *                    *\n");
        printf("*  1-Ogrenci Girisi * 2-Personel Girisi  *\n");
        printf("*                   *                    *\n");
        printf("******************************************\n");
        printf("Giris seceneginizi giriniz: ");
        scanf("%d", &input);
        if (input == 1) // burasi ogrenci girisi.icinde bulunacak fonksiyonlar:
        {
            while (1 == 1) {
                printf("adiniz: ");
                scanf("%s", &ad);
                printf("soyadiniz: ");
                scanf("%s", &soyAd);
                printf(" numaraniz: ");
                scanf("%d",&numara);
                printf("\n******yapmak istediginiz islemi seciniz***********");
                printf("\n0-cikis yap\n1-kitap listele\n2-kitap arama\n");
                printf("secim: ");
                scanf("%d", &secim);
                if (secim == 0) // cikis yap
                {
                    break;
                }

                switch (secim) {
                    case 1: // kitap listeleme
                        listele();
                        break;
                    case 2: // kitap arama
                        kitapArama();
                        break;
                }
            }
        } else if (input == 2) // personel icin kullanilacak fonsiyonlar
        {
            printf("***********BILGILERINIZI GIRINIZ*******\n");
            printf("AD:");
            scanf(" %s", &ad);
            printf("SOYAD:");
            scanf(" %s", &soyAd);
            printf("rakamlardan olusan 4 haneli bir sifre belirleyiniz: ");
            scanf(" %d", &sifre);
            if (sifre == sifre1) { //personel sifre kontrolu

                while (1 == 1) {
                    printf("\n******yapmak istediginiz islemi seciniz***********");
                    printf("\n0-cikis yap\n1-kitap alimi(bu islemi ilk defa yapiyorsaniz once 10'a sonra 1'e basin)\n2-kitap alan ogrencilerin listesi\n3-kitap kayit\n4-kitap listele\n5-kitap arama\n6-kitap silme\n7-ogrenci kayit\n8-ogrenci listele\n9-ogrenci kayit silme\n");
                    printf("secim: ");
                    scanf("%d", &secim);
                    if (secim == 0) // cikis yap
                    {
                        break;
                    }
                    int sayac = 0;
                    int sayi;
                    switch (secim) {
                        case 1: // ogrencinin kitap alma islemi
                            printf("kac tane ogrenci eklemek istediginizi giriniz : ");
                            scanf("%d", &sayi);
                            int i;
                            for (i = 1; i <= sayi; i++) {
                                hash();
                            }
                            break;
                        case 2: // kitap alan ogrencilerin listesi aldiklari kitaplarla birlikte
                        
                            for (i = 0; i <= sayac; i++) {
                                yazdir();
                            }
                            break;

                        case 3: // yeni kitaplarin kayit edilmesi
                            sonaEkle();
                            break;
                        case 4: // kutuphanedeki tüm kitaplarin listesi
                            listele();
                            break;
                        case 5: // kitap aratma islemi
                            kitapArama();
                            break;
                        case 6: // kitap silme islemi
                            aradanSil();
                            break;
                        case 7: // ogrenci uyelik ekleme
                            sonaEkle2();
                            break;
                        case 8: // uye ogrencilerin listesi
                            listele2();
                            break;
                        case 9: // ogrenci uye silme
                            aradanSil2();
                            break;
                        case 10: //hash icin dizi olusturma islemi bir kez yapilmasi yeterlidir
                            init();
                            break;
                        case 11: // ogrencilerin kitap iade islemi
                            search();
                    }
                }
            } else { // personel girisinde sifre 3 defa yanlıs girilirse kod sonlaniyor
                printf("yanlis sifre tekrar deneyiniz!!.\n");
                syc++;
                if (syc >= 3) {
                    printf("cikis.");
                    break;
                }
            }
        }
        printf("basa donmek icin 1 e basin programdan cikmak icin 0 a basin: ");
        scanf("%d", &secim);
        printf("seciminiz: ");
    } while (secim != 0);
}