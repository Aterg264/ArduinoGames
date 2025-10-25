// Botones (pull-up: reposo HIGH, pulsado LOW)
const int red  = 4;
const int groc = 5;
const int blue = 6;
const int verd = 7;

// LED (no usados aquí, pero definidos)
const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int led4 = 10;

// Buzzer
const int buzzer = 8;

// Secuencias
int seq1[] = {groc, groc};
int lenseq1 = sizeof(seq1) / sizeof(seq1[0]);

int seq2[] = {verd, verd};
int lenseq2 = sizeof(seq2) / sizeof(seq2[0]);

int seq3[] = {red, red, red};
int lenseq3 = sizeof(seq3) / sizeof(seq3[0]);

int seq4[] = {blue, blue};
int lenseq4 = sizeof(seq4) / sizeof(seq4[0]);

int posicion = 0;
bool errorseq = false;
int start = 0;

void setup() {
  // Pull-ups internos
  pinMode(red,  INPUT_PULLUP);
  pinMode(groc, INPUT_PULLUP);
  pinMode(blue, INPUT_PULLUP);
  pinMode(verd, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  start = encender();     // Espera un botón mantenido 2s y devuelve cuál
  if (start == 0) return; // Nada aún

  // Serie según botón de inicio
  while (start == red) {
    
     // --- PARPADEO LED1 DURANTE LA SECUENCIA ---
    static unsigned long previo = 0;
    static bool estadoLed = false;
    unsigned long ahora = millis();

    if (ahora - previo >= 300) {   // cada 300 ms
      previo = ahora;
      estadoLed = !estadoLed;
      digitalWrite(led1, estadoLed);
    }

    // lectura con pull-up: pulsado == LOW
    if (digitalRead(red)  == LOW) check(red,  seq1, lenseq1, led1);
    if (digitalRead(blue) == LOW) check(blue, seq1, lenseq1, led1);
    if (digitalRead(verd) == LOW) check(verd, seq1, lenseq1, led1);
    if (digitalRead(groc) == LOW) check(groc, seq1, lenseq1, led1);
  }

  while (start == groc) {

     // --- PARPADEO LED1 DURANTE LA SECUENCIA ---
    static unsigned long previo = 0;
    static bool estadoLed = false;
    unsigned long ahora = millis();

    if (ahora - previo >= 300) {   // cada 300 ms
      previo = ahora;
      estadoLed = !estadoLed;
      digitalWrite(led2, estadoLed);
    }

    if (digitalRead(red)  == LOW) check(red,  seq2, lenseq2, led2);
    if (digitalRead(blue) == LOW) check(blue, seq2, lenseq2, led2);
    if (digitalRead(verd) == LOW) check(verd, seq2, lenseq2, led2);
    if (digitalRead(groc) == LOW) check(groc, seq2, lenseq2, led2);
  }

  while (start == blue) {
     // --- PARPADEO LED1 DURANTE LA SECUENCIA ---
    static unsigned long previo = 0;
    static bool estadoLed = false;
    unsigned long ahora = millis();

    if (ahora - previo >= 300) {   // cada 300 ms
      previo = ahora;
      estadoLed = !estadoLed;
      digitalWrite(led3, estadoLed);
    }

    if (digitalRead(red)  == LOW) check(red,  seq3, lenseq3, led3);
    if (digitalRead(blue) == LOW) check(blue, seq3, lenseq3, led3);
    if (digitalRead(verd) == LOW) check(verd, seq3, lenseq3, led3);
    if (digitalRead(groc) == LOW) check(groc, seq3, lenseq3, led3);
  }

  while (start == verd) {

     // --- PARPADEO LED1 DURANTE LA SECUENCIA ---
    static unsigned long previo = 0;
    static bool estadoLed = false;
    unsigned long ahora = millis();

    if (ahora - previo >= 300) {   // cada 300 ms
      previo = ahora;
      estadoLed = !estadoLed;
      digitalWrite(led4, estadoLed);
    }

    if (digitalRead(red)  == LOW) check(red,  seq4, lenseq4, led4);
    if (digitalRead(blue) == LOW) check(blue, seq4, lenseq4, led4);
    if (digitalRead(verd) == LOW) check(verd, seq4, lenseq4, led4);
    if (digitalRead(groc) == LOW) check(groc, seq4, lenseq4, led4);
  }
}

// Mantener un botón 2s para iniciar
int encender() {
  int botpuls = 0;

  if (digitalRead(red)  == LOW) { 
    botpuls = red;  
    Serial.println("Rojo pulsado"); 
  }
  else if (digitalRead(blue) == LOW) { 
    botpuls = blue; 
    Serial.println("Azul pulsado"); 
  }
  else if (digitalRead(verd) == LOW) { 
    botpuls = verd; 
    Serial.println("Verde pulsado"); 
  }
  else if (digitalRead(groc) == LOW) { 
    botpuls = groc; 
    Serial.println("Amarillo pulsado"); 
  }
  else { return 0; }

  // Espera hasta 2s manteniendo pulsado
  unsigned long t0 = millis();
  while (digitalRead(botpuls) == LOW && (millis() - t0) < 2000) {
    delay(1); // pequeña espera
  }

  if ((millis() - t0) >= 2000 && digitalRead(botpuls) == LOW) {
    Serial.println("Botón mantenido 2 segundos!");

    // Tonadilla
    tone(buzzer, 220, 150);  delay(200);
    tone(buzzer, 294, 120);  delay(170);
    tone(buzzer, 349, 200);  delay(300);
    noTone(buzzer);

    return botpuls;
  } else {
    Serial.println("Lo has soltado antes de tiempo");
    return 0;
  }
}

void check(int boton, int seq[], int len, int led) {
  // Debounce y verificación: pulsado sigue siendo LOW
  delay(50);
  if (digitalRead(boton) == HIGH) return; // si ya no está pulsado, ignorar

  // Confirmación
  Serial.println("Boton " + String(boton) + " confirmado");
  tone(buzzer, 1000, 100);
  delay(120);

  if (boton == seq[posicion]) {
    Serial.println(":)");
  } else {
    Serial.println(":(");
    errorseq = true;
  }

  posicion++;

  // === FIN DE SECUENCIA ===
  if (posicion >= len) {
    Serial.println("Final");
    if (!errorseq) {
      Serial.println("Has ganado!");

      posicion = 0;
      start = 0;

      tone(buzzer, 330, 150); delay(200);
      tone(buzzer, 392, 120); delay(170);
      tone(buzzer, 523, 200); delay(300);
      noTone(buzzer);

      digitalWrite(led, HIGH); // ✅ se queda encendido si está bien

    } else {
      Serial.println("Intentalo de nuevo");

      digitalWrite(led, LOW);

      posicion = 0;
      errorseq = false;
      start = 0;

      tone(buzzer, 330, 150); delay(200);
      tone(buzzer, 247, 150); delay(200);
      tone(buzzer, 196, 300); delay(350);
      noTone(buzzer);

      digitalWrite(led, LOW); // ❌ se queda apagado si está mal
    }
  }

  // Esperar a soltar (pull-up: suelto == HIGH)
  while (digitalRead(boton) == LOW) { /* espera */ }
}


