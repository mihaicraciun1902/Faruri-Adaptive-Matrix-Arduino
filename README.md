# Faruri Adaptive cu Tehnologie de Dimming (Arduino) 🚗💡
Acest proiect reprezintă un sistem de iluminat auto inteligent și adaptiv, realizat pentru materia **Proiectare cu Microprocesoare (PM)**. Sistemul ajustează automat orientarea farurilor în funcție de virajele drumului și reduce intensitatea luminoasă (Auto-Dimming) la detectarea unui vehicul frontal.

## 📌 Funcționalități principale
- **Orientare Adaptivă:** Urmărirea virajelor prin giroscop (MPU6050) cu filtrare software (EMA) pentru o mișcare fluidă, fără jitter.
- **Auto-Dimming:** Reducerea automată a luminii (220 → 60) când un obstacol este detectat de senzorul ultrasonic (HC-SR04) la mai puțin de 30 cm.
- **Mod de Avarii:** Semnalizare portocalie intermitentă, prioritară, gestionată prin execuție non-blocantă (`millis()`).
- **Detectare Zi/Noapte:** Activare automată a farurilor pe baza pragului ADC al LDR-ului, cu fail-safe software pentru contact imperfect al senzorului.

## 🛠️ Hardware
* **Microcontroler:** Arduino Uno (ATmega328P)
* **Senzori:** MPU6050 (I2C), HC-SR04 (Ultrasonic), Fotorezistență (LDR)
* **Actuatoare:** 2x Micro Servomotoare SG90, 2x Module LED NeoPixel (WS2812B)
* **Alimentare:** Modul MB-102 (5V stabilizat) + Baterie 9V

## 📂 Structura fișierelor
- `/Faruri_Adaptive/Faruri_Adaptive.ino` — Codul sursă complet al proiectului.
- `diagrama_matrix.png` — Schema bloc a arhitecturii sistemului.
- `matrix_tinkercode_image.png` — Simulare hardware și conexiuni (Tinkercad).
- `Faruri-Adaptive-Matrix-Arduino-schematic.jpeg` — Schema electrică oficială.

## 🚀 Tehnologii utilizate
- **I2C & PWM:** Pentru comunicarea cu senzorii și controlul motoarelor.
- **Filtru EMA:** Exponential Moving Average pentru stabilizarea datelor de giroscop și mișcare fluidă a servomotoarelor.
- **Arhitectură Asincronă:** Utilizarea `millis()` pentru multitasking non-blocant (avarii + citire senzori simultane).

---
*Proiect realizat pentru Facultatea de Automatică și Calculatoare.*
