# 🚗 Akıllı Araç Kontrol Sistemi - ESP32 ile Motor Kontrol ve Servo Hareketi

Bu proje, **ESP32** kullanarak bir aracın **motorlarını** kontrol etmek ve **servo motorları** ile yönlendirmek için geliştirilmiştir. Projede **ESP-NOW** protokolü ile iki cihaz arasında kablosuz veri iletişimi sağlanmış ve **PWM sinyalleri** ile motor hızları ayarlanabilir hale getirilmiştir. 

Araç, yönlendirme komutlarına göre **ileri**, **geri**, **sola**, **sağa** ve daha karmaşık hareketler yapabilmektedir. Ayrıca, **pan-tilt servoları** kullanılarak araç üzerinde **kamera** veya diğer cihazların yönlendirilmesi mümkündür.

## 📦 Proje İçeriği

- **ESP32** mikrodenetleyici
- **Motor Kontrolü:** Hız ve yön ayarları, PWM ile motor kontrolü
- **Servo Motor Kontrolü:** Pan ve tilt hareketi
- **ESP-NOW İletişimi:** Kablosuz veri alımı
- **Joystik Yönlendirmesi:** İki joystick ile hareket yönü belirleme

## ⚙️ Kullanılan Teknolojiler

- **ESP32** Mikrodenetleyici
- **ESP-NOW** İletişim Protokolü
- **PWM (Pulse Width Modulation)**
- **Servo Motorları**
- **WiFi**
- **Arduino IDE**

---

## 🏗️ Devre Şeması

Aşağıda bu proje için kullanılan **devre şemasını** bulabilirsiniz. Motorlar ve servo motorlar, ESP32'ye bağlanarak aracın hareket etmesini sağlar.

![Devre Şeması](path-to-your-circuit-diagram.png)

---

## ⚡ Proje Kurulumu

### Gerekli Malzemeler

- **ESP32** (Herhangi bir ESP32 kartı kullanılabilir)
- **Motor sürücü kartı** (L298N gibi)
- **2 adet DC motor**
- **2 adet servo motor** (Pan ve Tilt için)
- **Joystik modülü**
- **Bağlantı kabloları ve breadboard**

### Adımlar

1. **Depoyu Klonlayın**
    git clone https://github.com/kullaniciadi/proje-adi.git
    cd proje-adi
2. **Gerekli Kütüphaneleri Yükleyin**
    ESP32Servo: Servo motorları kontrol etmek için kullanılır.
    ESP-NOW: ESP32 arasında veri iletişimi sağlamak için kullanılır.
    Arduino IDE'yi açın ve Kütüphaneler > Kütüphane Yöneticisi kısmından gerekli kütüphaneleri yükleyin.
3. **Pinleri Yapılandırın Arduino kodunda motor pinleri ve servo pinleri tanımlıdır. Bu pinlerin doğru bağlandığından emin olun.**
4. **Yazılımı Yükleyin Arduino IDE ile ESP32'yi seçin ve projeyi yükleyin.**
5. **Bağlantıyı Test Edin**
    Projeyi ESP32'ye yükledikten sonra, Serial Monitor üzerinden gelen komutları gözlemleyebilir ve sistemin düzgün çalıştığını kontrol edebilirsiniz.

## 📹 Tanıtım Videosu
Aşağıdaki videoyu izleyerek projenin nasıl çalıştığını daha yakından görebilirsiniz:
[![Videoyu İzle](https://upload.wikimedia.org/wikipedia/commons/thumb/3/34/Leo-Rover.jpg/640px-Leo-Rover.jpg)](https://www.youtube.com/watch?v=7wg4JfJojSU&t=29s)
