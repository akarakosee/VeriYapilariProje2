
// VeriOkuyucu.h
#ifndef VERI_OKUYUCU_H
#define VERI_OKUYUCU_H

#include <fstream>
#include <string>
#include <vector>

class VeriOkuyucu {
private:
    std::ifstream dosya;     // Dosya okuma nesnesi
    std::string mevcutSatir; // Okunan mevcut satır

public:
    VeriOkuyucu(const std::string& dosyaAdi); // Yapıcı fonksiyon
    ~VeriOkuyucu();                           // Yıkıcı fonksiyon

    bool dosyaAcildiMi() const;   // Dosyanın başarıyla açılıp açılmadığını kontrol eden fonksiyon
    bool satirOku();              // Dosyadan bir satır okuyan fonksiyon
    std::vector<int> sayilariOku(); // Okunan satırdaki sayıları vektör olarak döndüren fonksiyon
};

#endif // VERI_OKUYUCU_H
