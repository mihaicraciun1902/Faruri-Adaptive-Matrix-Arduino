# Faruri Adaptive cu Tehnologie de Dimming (Arduino) 🚗💡

Acest proiect reprezintă un sistem de iluminat auto inteligent și adaptiv, realizat pentru materia **Proiectare cu Microprocesoare (PM)**. Sistemul ajustează automat orientarea farurilor în funcție de virajele drumului și scade progresiv intensitatea luminoasă (Auto-Dimming) la detectarea unui vehicul frontal.

## 📌 Funcționalități principale
- **Orientare Adaptivă:** Urmărirea virajelor prin giroscop (MPU6050) cu filtrare software (EMA) pentru o mișcare fluidă.
- **Auto-Dimming Cinematic:** Reducerea automată și progresivă (Soft-Fade) a luminii când un obstacol este detectat de senzorul ultrasonic (HC-SR04).
- **Mod de Avarii:** Semnalizare portocalie intermitentă, prioritara, gestionată prin execuție non-blocantă (`millis()`).
- **LDR Anti-Shadow:** Activare inteligentă a farurilor noaptea, cu filtru de debounce pentru a evita declanșarea accidentală.

## 🛠️ Hardware Hardware
* **Microcontroler:** Arduino Uno (ATmega328P)
* **Senzori:** MPU6050 (I2C), HC-SR04 (Ultrasonic), Fotorezistență (LDR)
* **Actuatoare:** 2x Micro Servomotoare SG90, 2x Benzi LED NeoPixel (WS2812B)
* **Alimentare:** Modul MB-102 (5V stabilizat) + Baterie 9V

## 📂 Structura fișierelor
- `/Faruri_Adaptive/Faruri_Adaptive.ino` -> Codul sursă complet al proiectului.
- `diagrama_matrix.png` -> Schema bloc a arhitecturii sistemului.
- `matrix_tinkercode_image.png` -> Simulare hardware și conexiuni (Tinkercad).
- `Faruri-Adaptive-Matrix-Arduino-schematic.jpeg` -> Schema electrică oficială.

## 🚀 Tehnologii utilizate
- **I2C & PWM:** Pentru comunicarea cu senzorii și controlul motoarelor.
- **Filtre Software:** EMA (Exponential Moving Average) și Hysteresis pentru stabilitatea datelor.
- **Arhitectură Asincronă:** Utilizarea temporizatoarelor software pentru multitasking.

---
*Proiect realizat pentru Facultatea de Automatică și Calculatoare.*
