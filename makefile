# Derleyici ve bayrakları belirle
CXX = g++
CXXFLAGS = -Wall -std=c++11 -I include

# Hedef dosyanın adını ve konumunu belirle
TARGET = bin/main.exe

# Kaynak ve başlık dosyalarını belirle
SOURCES = src/main.cpp src/AVLAgaci.cpp src/Yigit.cpp src/VeriOkuyucu.cpp
HEADERS = include/AVLAgaci.h include/Yigit.h include/VeriOkuyucu.h

# Hedef dosyayı oluştur
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# 'make clean' komutu ile hedef dosyayı sil
clean:
	rm $(TARGET)
