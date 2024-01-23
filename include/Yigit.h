
// Yigit.h
#ifndef YIGIT_H
#define YIGIT_H

#include <vector>

class Yigit {
private:
    std::vector<int> elemanlar; // Yığıt elemanlarını tutan vektör

public:
    void ekle(int eleman);    // Yığıta eleman ekleyen fonksiyon
    int cikar();              // Yığıttan eleman çıkaran fonksiyon
    bool bosMu() const;        // Yığının boş olup olmadığını kontrol eden fonksiyon
};

#endif // YIGIT_H
