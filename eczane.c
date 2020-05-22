/*
eczane ilac sistemi proje odevi
* gurubun ogeleri betol, tasneem, kubra
* betolun yaptigi fonksiyonlari: IlaclariListele, yeniIlacEkle, ilaciBul, ilaciSil
* tasneemin yaptigi fonksiyonlari: strToStruct, openFile, ilacTarihi, ilacFiyati, ilacVakti, ilacAdet
* kubranin yaptigi fonksiyonlari: Guncelle
* ortak yapilan kisim main kismi
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

struct Eczane { //tanimladigimiz struct Eczane 
    char* isim;
    char* stt;
    char* fiyat;
    int ilacinSayisi;
    char* ilacinZamanKullanimi;
} ilac;

struct Eczane strToStruct(char str[]) {  //bu fonksiyon bilgileri okur ve structa atar 
    struct Eczane ilac; //ilac degiskeni struct eczane tipinden

    ilac.isim = strtok(str, "\t");  //stringden tab gelmesine kadar veriyi okur ve struct tipinden olan degiskene(ilac)'a atar
    ilac.stt = strtok(NULL, "\t");  //ayni sey ..
    ilac.fiyat = strtok(NULL, "\t");
    ilac.ilacinSayisi = atoi(strtok(NULL, "\t"));
    ilac.ilacinZamanKullanimi = strtok(NULL, "\n");

    return ilac;
}

FILE* openFile(char* type) {  //bu fonksiyon dosyayi acar ve dosya acilip acilmadigini kontrol eder ve sonunda dosyayi donderir
    FILE* f = fopen("eczane.txt", type);
    if (f == NULL) {
        fprintf(stderr, "Dosya bulunamadi");
        exit(1);
    }

    return f;
}
int ilaciBul(char* ilacAdi) {  //bir ilac var mi yok mu dosyada aramak icin
    FILE* f = openFile("r"); // dosyayi acar

    char l[SIZE];
    fgets(l, SIZE, f);  //dosyadan satir satir okur

    while (fgets(l, SIZE, f) != NULL) { //satirlarin sonuna kadar devam eder
        ilac = strToStruct(l);

        if (strcmp(ilacAdi, ilac.isim) == 0) {  //eger verilen ilacin ismini dosyada var ise ilaci 1 donderir
            return 1;
        }
    }
    fclose(f); //dosyayi kapatir
    return 0;
}

char* ilacTarihi(char* ilacAdi) { //istenen ilacin tarihini verir
    if (ilaciBul(ilacAdi)) { //eger bu ilac dosyada var ise son tuketim tarihini donderir
        return ilac.stt;
    }
    return NULL;//yoksa null donderir
}

char* ilacFiyati(char* ilacAdi) { //istenen ilacin fiyatini verir
    if (ilaciBul(ilacAdi)) {//eger bu ilac dosyada var ise fiyatini donderir
        return ilac.fiyat;
    }
    return NULL; //yoksa null donderir
}

char* ilacinZamanKullanimi(char* ilacAdi) {  //istenen ilacin zaman kullanimi verir
    if (ilaciBul(ilacAdi)) { //eger bu ilac dosyada var ise zaman kullanimi donderir
        return ilac.ilacinZamanKullanimi;
    }
    return NULL; //yoksa null donderir
}

int ilacinSayisi(char* ilacAdi) { //istenen ilacin sayisini verir
    if (ilaciBul(ilacAdi)) { //eger bu ilac dosyada var ise sayisini donderir
        return ilac.ilacinSayisi;
    }

    return -1; //yoksa -1 donderir
}

void IlaclariListele() { //dosyadaki tum ilaclari listeleniyor
    FILE* f = openFile("r"); //dosyayi acar
    char l[SIZE];
    fgets(l, SIZE, f); //dosyadan satir satir okur

    while (fgets(l, SIZE, f) != NULL) {//satirlarin sonuna kadar devam eder
        struct Eczane ilac = strToStruct(l);

        printf("%10s\t", ilac.isim); //ilacin ismini ekrana basar
        printf("%25s\t", ilac.stt); //ilacin son tuketim tarihi ekrana basar
        printf("%10s", ilac.fiyat); //ilacin fiyatini ekrana basar
        printf("%10d", ilac.ilacinSayisi); //ilacin sayisini ekrana basar
        printf("%15s", ilac.ilacinZamanKullanimi); //ilacin zaman kullnimi ekrana basar
        printf("\n");
    }

    fclose(f); //dosyayi kapatir
}

void yeniIlacEkle() { //dosyaya yeni ilac ekler
    FILE* f = openFile("a"); //dosyayi a modu ile acar sonuna eklemek icin

    printf("ilacin ismini giriniz\n"); //kullanciya mesaj basar ilacin ismini girmek icin
    char strIsim[20];
    scanf("%s", strIsim);  //kullancidan ilacin ismini alir ve ilac.isim structa atar
    ilac.isim = strIsim;

    printf("ilacin son tuketim tarihini giriniz\n"); //kullanciya mesaj basar ilacin son tuketim tarihini girmek icin
    char strStt[20];
    scanf("%s", strStt);  //usetteki gibi
    ilac.stt = strStt;

    printf("ilacin fiyatini giriniz\n"); //kullanciya mesaj basar ilacin fiyatini girmek icin
    char strFiyat[20];
    scanf("%s", strFiyat);
    ilac.fiyat = strFiyat;

    printf("ilacin sayisini giriniz\n"); //kullanciya mesaj basar ilacin sayisini girmek icin
    int ilacinSayisi;
    scanf("%d", &ilacinSayisi);
    ilac.ilacinSayisi = ilacinSayisi;

    printf("ilacin kullanilacagi zamani giriniz\n"); //kullanciya mesaj basar ilacin kullanilacagi zamani girmek icin
    char strZaman[20];
    scanf("%s", strZaman);
    ilac.ilacinZamanKullanimi = strZaman;

    fprintf(f, "%10s\t%5s\t%4s\t%10d\t%21s\n", ilac.isim, ilac.stt, ilac.fiyat, ilac.ilacinSayisi, ilac.ilacinZamanKullanimi); //alinan bilgi guzel formatla dosyaya yazar
    fclose(f);
}

void ilaciSil(char* ilacAdi) { //verilen bir ilaci dosyadan siliyor ve newfile diye yeni bir dosya olusturuyor ve icinde kalan ilaclar basiyor 
    FILE* f = openFile("r+");

    FILE* newFile;
    newFile = fopen("newFile.txt", "w");  //yeni file acar
    if (newFile != NULL) {  //eger dosya acildiysa devam eder
        char l[SIZE];

        fgets(l, SIZE, f);//dosyadan satir satir okur
        fprintf(newFile, "ILAC ADI        S.T.T          FIYAT      ILAC SAYISI                   SABAH YADA AKŞAM\n");   //yeni dosyaya yazar bunu

        while (fgets(l, SIZE, f) != NULL) { //satirlarin sonuna kadar devam eder
            ilac = strToStruct(l); //her satrin bildileri alip struct'a atar

            if (strcmp(ilacAdi, ilac.isim) != 0) { //eger bu ilac silmek istenen ilac degilse onu yaz
                fprintf(newFile, "%10s\t%5s\t%4s\t%10d\t%21s\n", ilac.isim, ilac.stt, ilac.fiyat, ilac.ilacinSayisi, ilac.ilacinZamanKullanimi);
            }
        }
    }
    fclose(newFile); //dosyayi kapat
    fclose(f); //dosyayi kapat
    //remove("eczane.txt"); //eski dosyayi sil
   // rename("newFile.txt", "eczane.txt");//yeni dosyanin adini degistir
}

void Guncelle(char* ilacAdi) { //bir ilacin ismini alir siler ve kullanci yenisi ekler 
    ilaciSil(ilacAdi);
    yeniIlacEkle();
}


int main() {
	int devamEt;
	        do{
            int secim;
            printf("%s", "Lutfen yapmak istediginiz islemi seciniz :\n"
                "1 - Istenilen ilacin Son kullanma tarihini goruntuler.\n"
                "2 - Istenilen ilacin Fiyatini goruntuler..\n"
                "3 - Istenilen ilacin ne zaman kullanilacagini goruntuler.\n"
                "4 - Istenilen ilacin adedini goruntuler..\n"
                "5 - Ilaclari listeler.\n"
                "6 - Yeni ilac ekler..\n"
                "7 - Istenilen ilacin var olup olmadigini bilmek.\n"
                "8 - Ilac siler\n"
                "9 - Ilac gunceller\n");
            scanf("%d", &secim);
            char ilacAdi[SIZE];
            

            switch (secim) {
            case 1:
                printf("Lutfen son kullanma tarihini gormek istediginiz ilacin adini giriniz\n");
                scanf("%s", ilacAdi);

                char* tarih = ilacTarihi(ilacAdi);
                if (tarih != NULL)
                    printf("%s\n", tarih);
                else
                    printf("ilac bulunamadi\n");

                break;

            case 2:
                printf("Lutfen fiyatini gormek istediginiz ilacin adini giriniz\n");
                scanf("%s", ilacAdi);

                char* fiyat = ilacFiyati(ilacAdi);
                if (fiyat != NULL)
                    printf("%s\n", fiyat);
                else
                    printf("ilac bulunamadi\n");

                break;

            case 3:
                printf("Lutfen kullanim zamanini gormek istediginiz ilacin adini giriniz\n");
                scanf("%s", ilacAdi);

                char* zaman = ilacinZamanKullanimi(ilacAdi);
                if (zaman != NULL)
                    printf("%s\n", zaman);
                else
                    printf("ilac bulunamadi\n");
                break;

            case 4:
                printf("Lutfen kullanim sayisini gormek istediginiz ilacin adetini giriniz\n");
                scanf("%s", ilacAdi);

                int adet = ilacinSayisi(ilacAdi);
                if (adet >= 0)
                    printf("%d\n", adet);
                else
                    printf("ilac bulunamadi\n");
                break;

            case 5:
                IlaclariListele();

                break;

            case 6:
                yeniIlacEkle();

                break;

            case 7:
                printf("Lutfen olup olmadigini bulmak istediginiz ilacin adini giriniz\n");
                scanf("%s", ilacAdi);
                if (ilaciBul(ilacAdi)) {
					 printf("ilac bulundu\n");
                }
                else
                    printf("ilac bulunamadi\n");
                break;


            case 8:
                printf("Lutfen silmek istediginiz ilacin adini giriniz\n");
                scanf("%s", ilacAdi);
                ilaciSil(ilacAdi);

                break;

            case 9:
                printf("Lutfen guncellemek istediginiz ilacin adini giriniz");
                scanf("%s", ilacAdi);
                Guncelle(ilacAdi);
                break;

            default:
                puts("YANLIS SECİM YAPTİNİZ !!!");
                break;

            }
        
        printf("\nYeni bir islem yapmak istiyorsaniz 10 basin\ncikmak istiyorsaniz 0 basin\n");
         scanf("%d", &devamEt);
    }while(devamEt != 0 && devamEt == 10);
    return 0;
}

