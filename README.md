🚗 Robot Araba Projesi
Bu proje, ESP32 kullanarak robot araba hareketlerini kontrol etmek ve ESP-NOW üzerinden kablosuz iletişim sağlamak için geliştirilmiştir. Proje, motor hareketlerini kontrol etmenin yanı sıra, pan ve tilt servo motorlarıyla robotun yönünü ayarlamaya da olanak tanır.

🛠️ Proje Özellikleri
Motor Kontrolü: 4 adet DC motor ile robotun hareketi kontrol edilir.

Servo Kontrolü: Pan ve tilt motorları ile yön kontrolü yapılır.

Kablosuz İletişim: ESP-NOW ile cihazlar arası kablosuz veri iletimi yapılır.

Joystick Desteği: İki joystick kullanılarak robot hareketi kontrol edilebilir.

PWM Hız Kontrolü: Motor hızları PWM sinyalleriyle ayarlanabilir.

🔌 Kullanılan Teknolojiler
Microcontroller: ESP32

Motorlar: DC Motorlar

Servo Motorlar: Pan ve Tilt Servo Motorları

Kablosuz İletişim: ESP-NOW

Programlama Dili: C++

PWM: Motor hız kontrolü için PWM kullanılmıştır.

📄 Devre Şeması
Aşağıda, projenin devre şemasını bulabilirsiniz. Bu şema, robot arabanın bağlantılarını ve kullanılan pinleri gösterir.


Not: Resmi yüklemek için, path_to_your_image.jpg kısmını bilgisayarınızdaki resmin yolu ile değiştirin.

🎥 Demo Video
Aşağıdaki butona tıklayarak robot araba projesinin çalışmasını izleyebilirsiniz:



📚 Kod Yapısı
Proje, robot araba ve servo motorları kontrol etmek için gerekli tüm kodu içermektedir. Kodun işleyişi şu şekildedir:

Motor Kontrolü: Her bir motor, belirli bir yön (ileri, geri, sola, sağa) için kontrol edilir.

Servo Kontrolü: Pan ve tilt servo motorlarının açıları ayarlanır.

ESP-NOW İletişimi: Robot, başka bir cihazdan gelen komutları alarak hareket eder.

PWM Hız Kontrolü: Motorların hızları, joystick üzerinden alınan değere göre ayarlanır.

⚙️ Kurulum
Projenin çalışabilmesi için aşağıdaki adımları takip edin:

Bağımlılıkları Yükleyin:

bash
Kopyala
Düzenle
flutter pub get
Projeyi Çalıştırın:

bash
Kopyala
Düzenle
flutter run
📑 Kod Açıklamaları
rotateMotor: Bu fonksiyon, motorları ileri veya geri hareket ettirir.

processCarMovement: Bu fonksiyon, hareket komutlarını alır ve motorlara ileterek robotu hareket ettirir.

OnDataRecv: ESP-NOW üzerinden alınan veriler ile robotun hareketlerini kontrol eder.

🚀 Proje Kullanımı
Joystick Kontrolü: Joystick'inizi kullanarak robotu hareket ettirebilirsiniz.

Servo Kontrolü: PAN ve TILT değerlerini değiştirerek robotun yönünü ayarlayabilirsiniz.

📝 Sonuç
Bu proje, ESP32 tabanlı robot araba hareket kontrolü ile kablosuz veri iletimi sağlar. Ayrıca, PWM ile motor hızlarını ayarlayabilir ve servo motorlar ile yön kontrolü yapabilirsiniz
