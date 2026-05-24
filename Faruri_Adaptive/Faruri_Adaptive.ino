#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>

// --- PINI CONFIGURARE ---
#define LDR_PIN      A0
#define BUTTON_PIN   2
#define TRIG_PIN     9
#define ECHO_PIN     10
#define SERVO_S_PIN  5
#define SERVO_D_PIN  6
#define LED_S_PIN    7
#define LED_D_PIN    8

Adafruit_NeoPixel farS(2, LED_S_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel farD(2, LED_D_PIN, NEO_GRB + NEO_KHZ800);
Servo sS, sD;

// --- VARIABILE CONTROL ---
float unghiF = 90;
bool avariiActive = false;
unsigned long tUltimulFlash = 0;
bool stareFlash = false;
unsigned long lastDebug = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // Pornire Giroscop (MPU6050)
  Wire.beginTransmission(0x68); Wire.write(0x6B); Wire.write(0x00); Wire.endTransmission(true);

  farS.begin(); farD.begin();
  farS.setBrightness(200); farD.setBrightness(200);
  
  sS.attach(SERVO_S_PIN); sD.attach(SERVO_D_PIN);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);

  welcomeShow();
}

void loop() {
  // 1. CITIRE SENZORI
  int luminaRaw = analogRead(LDR_PIN);
  if (luminaRaw < 10) luminaRaw = 150; // Protectie: daca firul sare, fortam mod NOAPTE

  int dist = citesteDistanta();
  int16_t rawGiro = citesteGiro();
  bool esteNoapte = (luminaRaw < 300);

  // 2. LOGICA BUTON AVARII (Anti-Spam)
  static bool butonLock = false;
  bool bNew = digitalRead(BUTTON_PIN);
  if (bNew == LOW && !butonLock) { 
    avariiActive = !avariiActive; 
    Serial.print(">>> AVARII: "); Serial.println(avariiActive ? "ON" : "OFF");
    butonLock = true;
    delay(50);
  } 
  if (bNew == HIGH) butonLock = false;

  // 3. CALCUL DIRECTIE (Calibrat si Snappy)
  int tinta = map(rawGiro, -17000, 17000, 120, 60); 
  float factorViteza = 0.45;
  unghiF = (unghiF * (1.0 - factorViteza)) + (constrain(tinta, 60, 120) * factorViteza);

  // 4. LOGICA DE ILUMINARE SI MISCARE
  if (avariiActive) {
    executaAvarii(esteNoapte); 
    sS.write(90); sD.write(90);
  } 
  else {
    if (esteNoapte) {
      if (dist > 30 || dist == 0) {
        // --- MOD: NOAPTE LIBER (FULL BRIGHT) ---
        farS.setBrightness(220); farD.setBrightness(220);
        farS.fill(farS.Color(255, 255, 255));
        farD.fill(farD.Color(255, 255, 255));
        
        sS.write((int)unghiF); 
        sD.write((int)unghiF);
      } 
      else {
        // --- MOD: NOAPTE OBSTACOL (DIMMED) ---
        farS.setBrightness(60); farD.setBrightness(60);
        farS.fill(farS.Color(255, 255, 255)); // FIX: era setPixelColor(1,...) -> aprindea doar un LED
        farD.fill(farD.Color(255, 255, 255));
        
        sS.write((int)unghiF); 
        sD.write((int)unghiF);
      }
    } 
    else {
      // --- MOD: ZI (DRL) ---
      farS.setBrightness(150); farD.setBrightness(150);
      farS.clear(); farD.clear();
      farS.setPixelColor(1, 255, 255, 255);
      farD.setPixelColor(1, 255, 255, 255);
      
      sS.write(90); sD.write(90);
    }
  }
  farS.show(); farD.show();

  // 5. DEBUG
  if (millis() - lastDebug > 400) {
    Serial.print("LDR: "); Serial.print(luminaRaw);
    Serial.print(" | DIST: "); Serial.print(dist);
    Serial.print(" | UNGHI: "); Serial.println((int)unghiF);
    lastDebug = millis();
  }
  delay(15);
}

// --- FUNCTII SISTEM ---

void executaAvarii(bool noapte) {
  if (millis() - tUltimulFlash > 450) {
    stareFlash = !stareFlash;
    tUltimulFlash = millis();
  }
  
  if (noapte) {
    farS.setPixelColor(0, 255, 255, 255); 
    farD.setPixelColor(0, 255, 255, 255);
    
    if (stareFlash) {
      farS.setPixelColor(1, 255, 110, 0); 
      farD.setPixelColor(1, 255, 110, 0);
    } else {
      farS.setPixelColor(1, 0, 0, 0); 
      farD.setPixelColor(1, 0, 0, 0); 
    }
  } else {
    if (stareFlash) {
      farS.fill(farS.Color(255, 110, 0)); 
      farD.fill(farD.Color(255, 110, 0));
    } else {
      farS.clear(); 
      farD.clear();
    }
  }
}

void welcomeShow() {
  sS.write(90); sD.write(90);
  farS.setBrightness(0); farD.setBrightness(0);

  // Fade-in Cyan
  for(int b = 0; b <= 120; b++) {
    uint32_t cyan = farS.ColorHSV(35000, 200, b * 2); 
    farS.fill(cyan); farD.fill(cyan);
    farS.setBrightness(b); farD.setBrightness(b);
    farS.show(); farD.show();
    delay(10);
  }
  // Scanare
  for(int unghi = 0; unghi <= 25; unghi++) {
    sS.write(90 + unghi); sD.write(90 - unghi); delay(15);
  }
  for(int unghi = 25; unghi >= 0; unghi--) {
    sS.write(90 + unghi); sD.write(90 - unghi); delay(15);
  }
  // Tranzitie Alb
  for(int s = 200; s >= 0; s -= 10) {
    uint32_t transition = farS.ColorHSV(35000, s, 255); 
    farS.fill(transition); farD.fill(transition);
    farS.show(); farD.show(); delay(10);
  }
  farS.setBrightness(200); farD.setBrightness(200);
}

int citesteDistanta() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long dur = pulseIn(ECHO_PIN, HIGH, 20000);
  return (dur == 0) ? 400 : dur * 0.034 / 2;
}

int16_t citesteGiro() {
  Wire.beginTransmission(0x68); Wire.write(0x3B); Wire.endTransmission(false);
  Wire.requestFrom(0x68, 2, true);
  return (Wire.available() >= 2) ? (Wire.read() << 8 | Wire.read()) : 0;
}
