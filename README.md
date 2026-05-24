# Faruri Adaptive cu Tehnologie de Dimming (Arduino) 🚗💡

Acest repository conține codul sursă și documentația vizuală pentru proiectul la materia Proiectare cu Microprocesoare (PM).

## 📌 Scurtă descriere
Proiectul reprezintă un sistem de iluminat auto inteligent capabil să:
- Își adapteze automat direcția în curbe folosind un giroscop (MPU6050).
- Să reducă progresiv luminozitatea (Soft-Fade / Auto-Dimming) la detectarea unui obstacol frontal cu senzorul ultrasonic (HC-SR04).
- Să acționeze un mod de avarii (clipire portocalie intermitentă) independent de starea senzorilor, folosind o abordare de cod non-blocantă (`millis()`).

Toate mișcările mecanice și variațiile de lumină sunt trecute prin filtre software (Exponential Moving Average și Hysteresis) pentru o estetică fluidă, de tip "premium".

## 🛠️ Componente Hardware
* Placă: Arduino Uno (ATMega328P)
* MPU6050 (Giroscop/Accelerometru I2C)
* HC-SR04 (Senzor Ultrasonic)
* 2x Servomotoare SG90
* 2x Benzi LED WS2812B (NeoPixel)
* Modul Power MB-102 (pentru separarea alimentării de forță)
* LDR + Buton push

## 📂 Structura fișierelor
* `/Faruri_Adaptive/Faruri_Adaptive.ino` -> Codul sursă principal care trebuie încărcat pe placa Arduino.
* `diagrama_matrix.png` -> Schema bloc a sistemului, ilustrând fluxul datelor.
* `matrix_tinkercode_image.png` -> Conexiunile hardware vizuale (Breadboard view).
* `Faruri-Adaptive-Matrix-Arduino-schematic.jpeg` -> Schema electrică oficială a proiectului.

## 🚀 Tehnologii și Concepte
- **Fast PWM / One-Wire:** Pentru controlul precis al servomotoarelor și al benzilor NeoPixel.
- **Filtrare EMA:** Pentru stabilizarea citirilor senzorilor low-cost.
- **Interfață I2C:** Comunicația cu modulul inerțial.
