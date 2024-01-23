
#include "VeriOkuyucu.h"
#include "AVLAgaci.h"
#include "Yigit.h"
#include <iostream>

using namespace std;

void YigittanSilVeKarsilastir(char*& karakterler, int*& satirNumaralari, int& karakterSayisi, int& satirNumarasi);

int main() {
    VeriOkuyucu okuyucu("Veri.txt"); // VeriOkuyucu sınıfını kullanarak Veri.txt dosyasını aç

    if (!okuyucu.dosyaAcildiMi()) {
        cerr << "Dosya açılamadı!\n";
        return 1;
    }

    int karakterSayisi = 0; // AVL ağaçlarını temsil eden karakterlerin sayısını tutacak bir değişken oluştur
    char* karakterler = new char[karakterSayisi]; // AVL ağaçlarını temsil eden karakterleri tutacak bir dinamik dizi oluştur
    int* satirNumaralari = new int[karakterSayisi]; // Hangi satırdan geldiğini belirlemek için bir dizi oluşturun

    int satirNumarasi = 1; // Satır numarasını takip etmek için bir değişken oluşturun

    while (okuyucu.satirOku()) {
        AVL_Agaci agac; // Yeni bir AVL ağacı oluştur

        std::vector<int> sayilar = okuyucu.sayilariOku(); // Satırdaki sayıları oku

        // Satırdaki her sayıyı AVL ağacına ekleyerek işlem yap
        for (int sayi : sayilar) {
            agac.ekle(sayi); // Sayıyı AVL ağacına ekle
        }

        // AVL ağacının düğüm değerlerinin toplamını hesapla (yapraklar hariç)
        int AVLToplamDugumDeger = agac.toplamDeger();

        // AVL ağacının düğüm değerlerinin toplamını bir ASCII değerine dönüştür
        int ascii = AVLToplamDugumDeger % (90 - 65 + 1) + 65;

        // ASCII değerini bir karaktere dönüştür ve dinamik diziye ekle
        char* yeniKarakterler = new char[karakterSayisi + 1];
        int* yeniSatirNumaralari = new int[karakterSayisi + 1]; // Yeni bir satır numarası dizisi oluşturun

        for (int i = 0; i < karakterSayisi; i++) {
            yeniKarakterler[i] = karakterler[i];
            yeniSatirNumaralari[i] = satirNumaralari[i]; // Eski satır numaralarını yeni diziye kopyalayın
        }

        yeniKarakterler[karakterSayisi] = static_cast<char>(ascii);
        yeniSatirNumaralari[karakterSayisi] = satirNumarasi; // Satır numarasını yeni diziye ekleyin

        delete[] karakterler;
        delete[] satirNumaralari; // Eski satır numarası dizisini silin

        karakterler = yeniKarakterler;
        satirNumaralari = yeniSatirNumaralari; // Yeni satır numarası dizisini saklayın

        karakterSayisi++;
        satirNumarasi++; // Satır numarasını artırın
    }

    YigittanSilVeKarsilastir(karakterler, satirNumaralari, karakterSayisi, satirNumarasi);

    return 0;
}

void YigittanSilVeKarsilastir(char*& karakterler, int*& satirNumaralari, int& karakterSayisi, int& satirNumarasi) {
    while (karakterSayisi > 1) {
        // Dinamik dizinin sonundaki karakteri sil
        char* yeniKarakterler = new char[karakterSayisi - 1];
        int* yeniSatirNumaralari = new int[karakterSayisi - 1]; // Yeni bir satır numarası dizisi oluşturun

        for (int i = 0; i < karakterSayisi - 1; i++) {
            yeniKarakterler[i] = karakterler[i];
            yeniSatirNumaralari[i] = satirNumaralari[i]; // Eski satır numaralarını yeni diziye kopyalayın
        }

        delete[] karakterler;
        delete[] satirNumaralari; // Eski satır numarası dizisini silin

        karakterler = yeniKarakterler;
        satirNumaralari = yeniSatirNumaralari; // Yeni satır numarası dizisini saklayın

        karakterSayisi--;

        // Ekranı temizle
        cout << "\033[2J\033[1;1H";

        // Dinamik dizideki karakterleri tekrar ekrana yazdır
        for (int i = 0; i < karakterSayisi; i++) {
            cout << karakterler[i];
        }
        cout << endl;
    }

    // Son kalan ağacın temsil ettiği ASCII değerini yazdır
    for (int i = 0; i < karakterSayisi; i++) {
        if (karakterler[i] != 0) {
            cout << "Son Karakter: " << karakterler[i] << ", AVL No: " << satirNumaralari[i] << endl;
            break;
        }
    }
}
