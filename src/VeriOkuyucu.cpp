
// VeriOkuyucu.cpp
#include "VeriOkuyucu.h"
#include <sstream>

// VeriOkuyucu sınıfının kurucu fonksiyonu
VeriOkuyucu::VeriOkuyucu(const std::string& dosyaAdi) : dosya(dosyaAdi) {}

// VeriOkuyucu sınıfının yıkıcı fonksiyonu
VeriOkuyucu::~VeriOkuyucu() {
    // Dosya açıksa, kapat
    if (dosya.is_open()) {
        dosya.close();
    }
}

// Dosyanın başarılı bir şekilde açılıp açılmadığını kontrol eden fonksiyon
bool VeriOkuyucu::dosyaAcildiMi() const {
    return dosya.is_open();
}

// Dosyadan bir satır okuyan fonksiyon
bool VeriOkuyucu::satirOku() {
    // Dosya iyi durumda (good) ve bir satır okunabiliyorsa true döndür
    return dosya.good() && std::getline(dosya, mevcutSatir);
}

// Mevcut satırdaki sayıları okuyan ve bir vektörde saklayan fonksiyon
std::vector<int> VeriOkuyucu::sayilariOku() {
    // Mevcut satırı bir istringstream nesnesine yerleştir
    std::istringstream iss(mevcutSatir);
    
    // Sayıları saklamak için bir vektör oluştur
    std::vector<int> sayilar;
    
    // İss nesnesinden sayıları oku ve vektöre ekle
    int sayi;
    while (iss >> sayi) {
        sayilar.push_back(sayi);
    }
    
    // Sayıları içeren vektorü döndür
    return sayilar;
}
