
// Yigit.cpp
#include "Yigit.h"
#include <stdexcept> // std::out_of_range için

void Yigit::ekle(int eleman) {
    elemanlar.push_back(eleman); // Elemanı yığıtın en üstüne ekle
}

int Yigit::cikar() {
    if (!bosMu()) {
        int enUstEleman = elemanlar.back(); // En üstteki elemanı al
        elemanlar.pop_back(); // En üstteki elemanı sil
        return enUstEleman;
    } else {
        throw std::out_of_range("Yığıt boş!"); // Yığıt boşsa hata fırlat
    }
}

bool Yigit::bosMu() const {
    return elemanlar.empty(); // Yığıtın boş olup olmadığını kontrol et
}
