
// AVLAgaci.h
#ifndef AVL_AGACI_H
#define AVL_AGACI_H

#include "Yigit.h" // Yigit sınıfını dahil et

class AVL_Dugum {
public:
    int anahtar;
    AVL_Dugum* sol;
    AVL_Dugum* sag;
    int yukseklik;

    AVL_Dugum(int anahtar);
};

class AVL_Agaci {
public:
    AVL_Dugum* kok;

    AVL_Agaci();
    ~AVL_Agaci();

    void ekle(int anahtar);
    AVL_Dugum* ekleRekursif(AVL_Dugum* dugum, int anahtar); // AVL ağacına düğüm eklemek için recursive fonksiyon
    void sil(int anahtar);
    AVL_Dugum* silRekursif(AVL_Dugum* dugum, int anahtar); // AVL ağacından düğüm silmek için recursive fonksiyon
    bool ara(int anahtar);
    bool araRekursif(AVL_Dugum* dugum, int anahtar); // AVL ağacında anahtar aramak için recursive fonksiyon
    void postorderYaprakEkle(Yigit& yigit, AVL_Dugum* dugum); // AVL ağacındaki yaprakları postorder gezerek yığıta ekleyen fonksiyon
    int yukseklikAl(AVL_Dugum* dugum); // AVL ağacındaki bir düğümün yüksekliğini hesaplayan fonksiyon
    int dengeAl(AVL_Dugum* dugum); // AVL ağacındaki bir düğümün denge faktörünü hesaplayan fonksiyon
    AVL_Dugum* sagDonus(AVL_Dugum* y); // Sağa dönüş yapan AVL ağacı rotasyon fonksiyonu
    AVL_Dugum* solDonus(AVL_Dugum* x); // Sola dönüş yapan AVL ağacı rotasyon fonksiyonu
	int toplamDeger();
    int toplamDegerRekursif(AVL_Dugum* dugum);
    void AVLIslemi(AVL_Agaci* agaclar, Yigit* yigitlar, int agacSayisi);
	AVL_Dugum* tumunuSil(AVL_Dugum* dugum);
	AVL_Dugum* minValueNode(AVL_Dugum* dugum); // AVL ağacındaki en küçük değerli düğümü bulan fonksiyon
};

#endif // AVL_AGACI_H
