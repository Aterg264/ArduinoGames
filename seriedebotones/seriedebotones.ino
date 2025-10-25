
// Botones
const int red = 12;
const int groc = 11;
const int blue = 10;
const int verd = 9;

// LED bicolor (cátodo común)
const int ledR = 7;
const int ledG = 8;

// Buzzer
const int buzzer = 6;

// Secuencia correcta
int correctseq[] = {red, blue, groc, verd};
int posicion = 0;
int lenseq = sizeof(correctseq) / sizeof(correctseq[0]);
bool errorseq = false;

bool start = false;

void setup() {
  // Configurar botones
  pinMode(red, INPUT);
  pinMode(groc, INPUT);
  pinMode(blue, INPUT);
  pinMode(verd, INPUT);

  // Configurar LED
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);

  // Configurar buzzer
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  start = encender();
  while(start == true){
      if (digitalRead(red) == LOW)  check(red);
      if (digitalRead(blue) == LOW) check(blue);
      if (digitalRead(verd) == LOW) check(verd);
      if (digitalRead(groc) == LOW) check(groc);
  }
}

// Iniciar el programa pulsando el boton rojo durante dos segundos -- PROGRAMA 4 BOTONES A LA VEZ!
bool encender(){

  int pulsar_rojo = digitalRead(red);
  bool inicio = false;
  unsigned long tiempoInicio = 0;

  if (pulsar_rojo == LOW && !inicio) {
    // millis es el tiempo actual
    Serial.println("Manten");
    tiempoInicio = millis();
    inicio = true;
    delay(2010);

    if(digitalRead(red) == HIGH){
      Serial.println("2s");
      inicio = false;
      tiempoInicio = 0;
      pulsar_rojo = LOW;
    }  
  }

  if (pulsar_rojo == LOW && inicio) {
    if (millis() - tiempoInicio >= 2000) { 
      Serial.println("Botón mantenido 2 segundos!");
      inicio = false;
      tiempoInicio = 0;
      
      //Tonadilla inicial
      tone(buzzer, 220, 150);  // La3 (grave)
      delay(200);
      tone(buzzer, 294, 120);  // Re4
      delay(170);
      tone(buzzer, 349, 200);  // Fa4 (apagado, cierre)
      delay(300);
      noTone(buzzer);

      return true;
    }
  }
  return false; 
}

void check(int boton){
  // Evitar rebotes comprobando que el LOW se ha leído correctamente
  delay(50); 
  if (digitalRead(boton) == HIGH) return; 

  // Confirmación
  tone(buzzer, 1000, 100);
  delay(120);

  Serial.println(posicion);

  if (boton == correctseq[posicion]) {
    Serial.println(":)");
    Serial.println(lenseq);

    if (posicion >= lenseq-1){
      if (errorseq == false) {
        Serial.println("Has ganado!"); 

        // 🎉 Secuencia completa
        posicion = 0; // reiniciar
        start = false;

        tone(buzzer, 330, 150);  
        delay(200);
        tone(buzzer, 392, 120); 
        delay(170);
        tone(buzzer, 523, 200);  
        delay(300);
        noTone(buzzer);
      
      } else {
        Serial.println("Intentalo de nuevo"); 

        posicion = 0;
        errorseq = false;
        start = false;
      
        tone(buzzer, 330, 150);  // Mi4
        delay(200);
        tone(buzzer, 247, 150);  // Si3
        delay(200);
        tone(buzzer, 196, 300);  // Sol3
        delay(350);
        noTone(buzzer);
      }
    }

  } else {
    // ❌ Error
    Serial.println(":("); 
    errorseq = true;
  }

  // Siempre suma una posición
  posicion ++;

  while (digitalRead(boton) == LOW); // esperar a soltar
}



















