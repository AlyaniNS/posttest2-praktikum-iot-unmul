# Sistem Monitoring Polusi Suara Menggunakan Platform ThingSpeak
Menampilkan tingkat intensitas suara dalam desibel disertai dengan kategori kebisingan, terdapat 3 tingkat kebisingan yang diatur dalam program: sunyi (<60db), sedang (>60db sampai dengan <85db), dan tinggi (>85db). Masing-masing tingkat kebisingan yang diterima sensor ditandai dengan 3 buah LED yang berwarna merah, kuning, dan hijau. 
Projek ini merupakan post test 2 praktikum mata kuliah Internet of Things di Univeritas Mulawarman.

## Metode IoT
Monitoring dilakukan melalui web server yang sudah didesain menggunakan bahasa pemrograman HTML, CSS, dan JS. Data yang ditampilkan di web server berupa grafik yang diambil dari platform ThingSpeak yang terhubung dengan device IoT menggunakan API. 

## Komponen yang digunakan
1. ESP8266
2. Breadboard
3. Resistor
4. LED (warna merah, kuning, dan hijau)
5. LCD I2C 16x2
6. Microphone sound sensor
7. Kabel jumper
8. Kabel micro-USB

## Board Schematic
![Board-Schematic-PostTest2](https://user-images.githubusercontent.com/74224380/230539067-9805dcf9-9255-4c87-97f9-139ecf358a1e.png)

## Pembagian Tugas

No|Nim       |Nama                            |Tugas
--|----------|--------------------------------|-----------------------
1 |1915026021|Muhammad Dicky Rizqia Nur Achmar| Konfigurasi ThingSpeak
2 |2009106100|Alyani Noor Septalia            | Konfigurasi Program & Web Server
3 |2009106112|Adrian Tasmin                   | Membuat Rangkaian    
