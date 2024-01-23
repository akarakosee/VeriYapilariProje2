
// AVLAgaci.cpp
#include "AVLAgaci.h"
#include <algorithm>

// AVL_Dugum sınıfının yapıcı fonksiyonu
AVL_Dugum::AVL_Dugum(int anahtar) : anahtar(anahtar), sol(nullptr), sag(nullptr), yukseklik(1) {}

// AVL_Agaci sınıfının yapıcı ve yıkıcı fonksiyonları
AVL_Agaci::AVL_Agaci() : kok(nullptr) {}

// AVL_Agaci sınıfının yıkıcı fonksiyonu
AVL_Agaci::~AVL_Agaci() {
    kok = tumunuSil(kok);
}

// AVL ağacına bir düğüm eklemek için fonksiyon
void AVL_Agaci::ekle(int anahtar) {
    kok = ekleRekursif(kok, anahtar);
}

// AVL ağacına bir düğüm eklemek için yardımcı rekürsif fonksiyon
AVL_Dugum* AVL_Agaci::ekleRekursif(AVL_Dugum* dugum, int anahtar) {
    // Normal BST ekleme işlemi
    if (dugum == nullptr)
        return new AVL_Dugum(anahtar);
    if (anahtar < dugum->anahtar)
        dugum->sol = ekleRekursif(dugum->sol, anahtar);
    else if (anahtar > dugum->anahtar)
        dugum->sag = ekleRekursif(dugum->sag, anahtar);
    else // Eşit anahtarlar izin verilmez
        return dugum;

    // Yukseklik güncelleme
    dugum->yukseklik = 1 + std::max(yukseklikAl(dugum->sol), yukseklikAl(dugum->sag));

    // AVL dengesizlik kontrolü
    int denge = dengeAl(dugum);

    // Denge durumlarına göre düğüm döndürme
    // Sol Sol Durumu
    if (denge > 1 && anahtar < dugum->sol->anahtar)
        return sagDonus(dugum);

    // Sağ Sağ Durumu
    if (denge < -1 && anahtar > dugum->sag->anahtar)
        return solDonus(dugum);

    // Sol Sağ Durumu
    if (denge > 1 && anahtar > dugum->sol->anahtar) {
        dugum->sol = solDonus(dugum->sol);
        return sagDonus(dugum);
    }

    // Sağ Sol Durumu
    if (denge < -1 && anahtar < dugum->sag->anahtar) {
        dugum->sag = sagDonus(dugum->sag);
        return solDonus(dugum);
    }

    return dugum;
}

// Ağaçtaki tüm düğümlerin (yapraklar hariç) anahtar değerlerini toplayan fonksiyon
int AVL_Agaci::toplamDeger() {
    return toplamDegerRekursif(kok);
}

// Ağaçtaki tüm düğümlerin (yapraklar hariç) anahtar değerlerini toplayan yardımcı rekürsif fonksiyon
int AVL_Agaci::toplamDegerRekursif(AVL_Dugum* dugum) {
    if (dugum == nullptr)
        return 0;
    else if (dugum->sol == nullptr && dugum->sag == nullptr) // Yaprak düğüm kontrolü
        return 0; // Yaprak düğümse, değerini toplama ekleme
    else
        return dugum->anahtar + toplamDegerRekursif(dugum->sol) + toplamDegerRekursif(dugum->sag);
}

// AVL ağacından bir düğüm silmek için fonksiyon
void AVL_Agaci::sil(int anahtar) {
    kok = silRekursif(kok, anahtar);
}

// AVL ağacından bir düğüm silmek için yardımcı rekürsif fonksiyon
AVL_Dugum* AVL_Agaci::silRekursif(AVL_Dugum* dugum, int anahtar) {
    // Normal BST silme işlemi
    if (dugum == nullptr)
        return dugum;
    if (anahtar < dugum->anahtar)
        dugum->sol = silRekursif(dugum->sol, anahtar);
    else if(anahtar > dugum->anahtar)
        dugum->sag = silRekursif(dugum->sag, anahtar);
    else {
        // Düğümün bir veya hiç çocuğu yoksa
        if((dugum->sol == nullptr) || (dugum->sag == nullptr)) {
            AVL_Dugum *temp = dugum->sol ? dugum->sol : dugum->sag;
            // Hiç çocuğu yoksa
            if(temp == nullptr) {
                temp = dugum;
                dugum = nullptr;
            }
            else // Bir çocuğu varsa
                *dugum = *temp; // Çocuğu kopyala
            delete temp;
        }
        else {
            // İki çocuğu varsa
            AVL_Dugum* temp = minValueNode(dugum->sag);
            // İnorder sıralamadaki halefin anahtarını kopyala
            dugum->anahtar = temp->anahtar;
            // İnorder sıralamadaki halefi sil
            dugum->sag = silRekursif(dugum->sag, temp->anahtar);
        }
    }

    // Sadece bir düğüm vardı ve silindi
    if (dugum == nullptr)
        return dugum;

    // Yukseklik güncelleme
    dugum->yukseklik = 1 + std::max(yukseklikAl(dugum->sol), yukseklikAl(dugum->sag));

    // AVL dengesizlik kontrolü
    int denge = dengeAl(dugum);

    // Denge durumlarına göre düğüm döndürme
    // Sol Sol Durumu
    if (denge > 1 && anahtar < dugum->sol->anahtar)
        return sagDonus(dugum);

    // Sağ Sağ Durumu
    if (denge < -1 && anahtar > dugum->sag->anahtar)
        return solDonus(dugum);

    // Sol Sağ Durumu
    if (denge > 1 && anahtar > dugum->sol->anahtar) {
        dugum->sol = solDonus(dugum->sol);
        return sagDonus(dugum);
    }

    // Sağ Sol Durumu
    if (denge < -1 && anahtar < dugum->sag->anahtar) {
        dugum->sag = sagDonus(dugum->sag);
        return solDonus(dugum);
    }

    return dugum;
}

// AVL ağacında belirli bir anahtar değerini aramak için fonksiyon
bool AVL_Agaci::ara(int anahtar) {
    return araRekursif(kok, anahtar);
}

// AVL ağacında belirli bir anahtar değerini aramak için yardımcı rekürsif fonksiyon
bool AVL_Agaci::araRekursif(AVL_Dugum* dugum, int anahtar) {
    // Normal BST arama işlemi
    if (dugum == nullptr)
        return false;
    else if (anahtar < dugum->anahtar)
        return araRekursif(dugum->sol, anahtar);
    else if (anahtar > dugum->anahtar)
        return araRekursif(dugum->sag, anahtar);
    else
        return true; // Anahtar bulundu
}

// Bir düğümün denge faktörünü hesaplamak için fonksiyon
int AVL_Agaci::dengeAl(AVL_Dugum* N) {
    if (N == nullptr)
        return 0;
    return yukseklikAl(N->sol) - yukseklikAl(N->sag);
}

// Bir düğümün yüksekliğini almak için fonksiyon
int AVL_Agaci::yukseklikAl(AVL_Dugum* dugum) {
    if (dugum == nullptr)
        return 0;
    else
        return dugum->yukseklik;
}

// Sağa dönüş (Right Rotation) işlemi için fonksiyon
AVL_Dugum* AVL_Agaci::sagDonus(AVL_Dugum* y) {
    AVL_Dugum* x = y->sol;
    AVL_Dugum* T2 = x->sag;

    // Dönüşü gerçekleştir
    x->sag = y;
    y->sol = T2;

    // Yükseklikleri güncelle
    y->yukseklik = std::max(yukseklikAl(y->sol), yukseklikAl(y->sag)) + 1;
    x->yukseklik = std::max(yukseklikAl(x->sol), yukseklikAl(x->sag)) + 1;

    // Yeni kökü döndür
    return x;
}

// Sola dönüş (Left Rotation) işlemi için fonksiyon
AVL_Dugum* AVL_Agaci::solDonus(AVL_Dugum* x) {
    AVL_Dugum* y = x->sag;
    AVL_Dugum* T2 = y->sol;

    // Dönüşü gerçekleştir
    y->sol = x;
    x->sag = T2;

    // Yükseklikleri güncelle
    x->yukseklik = std::max(yukseklikAl(x->sol), yukseklikAl(x->sag)) + 1;
    y->yukseklik = std::max(yukseklikAl(y->sol), yukseklikAl(y->sag)) + 1;

    // Yeni kökü döndür
    return y;
}

// Verilen bir ağaç düğümünün en küçük değerli düğümünü bulan fonksiyon
AVL_Dugum* AVL_Agaci::minValueNode(AVL_Dugum* dugum) {
    AVL_Dugum* current = dugum;

    /* En sol yaprağı bul */
    while (current->sol != nullptr)
        current = current->sol;

    return current;
}

// Tüm düğümleri silmek için yardımcı fonksiyon
AVL_Dugum* AVL_Agaci::tumunuSil(AVL_Dugum* dugum) {
    if (dugum == nullptr)
        return dugum;
    dugum->sol = tumunuSil(dugum->sol);
    dugum->sag = tumunuSil(dugum->sag);
    delete dugum;
    return nullptr;
}

// Ağaçta postorder gezinme yaparak yaprak düğümleri bir yığına ekleyen fonksiyon
void AVL_Agaci::postorderYaprakEkle(Yigit& yigit, AVL_Dugum* dugum) {
    if (dugum != nullptr) {
        // Önce sol alt ağaca git
        postorderYaprakEkle(yigit, dugum->sol);
        // Sonra sağ alt ağaca git
        postorderYaprakEkle(yigit, dugum->sag);
        // Eğer düğüm yapraksa, yığıta ekle
        if (dugum->sol == nullptr && dugum->sag == nullptr) {
            yigit.ekle(dugum->anahtar);
        }
    }
}

