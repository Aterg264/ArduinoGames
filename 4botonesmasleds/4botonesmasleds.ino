
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

// Secuencias
int seq1[] = {red, verd};
int lenseq1 = sizeof(seq1) / sizeof(seq1[0]);

int seq2[] = {blue, groc};
int lenseq2 = sizeof(seq2) / sizeof(seq2[0]);

int seq3[] = {red, blue, groc};
int lenseq3 = sizeof(seq3) / sizeof(seq3[0]);

int seq4[] = {blue, blue};
int lenseq4 = sizeof(seq4) / sizeof(seq4[0]);

// Secuencia inicial
int seq[] = {};
int posicion = 0;

// Marca si hay algun error al poner la secuencia
bool errorseq = false;

//Marca el inicio
int start = 0;

void setup() {
  // Configurar botones
  pinMode(red, INPUT);
  pinMode(groc, INPUT);
  pinMode(blue, INPUT);
  pinMode(verd, INPUT);

  // Configurar LED - Tener en cuenta que va al revés - De momento este led no hace nada



  // Configurar buzzer
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  start = encender();
  // Fer una funció amb els ifs i un while per cada cas
  while(start == red){
      if (digitalRead(red) == LOW)  check(red, seq1);
      if (digitalRead(blue) == LOW) check(blue, seq1);
      if (digitalRead(verd) == LOW) check(verd, seq1);
      if (digitalRead(groc) == LOW) check(groc, seq1);
  }

  while(start == groc){
      if (digitalRead(red) == LOW)  check(red, seq2);
      if (digitalRead(blue) == LOW) check(blue, seq2);
      if (digitalRead(verd) == LOW) check(verd, seq2);
      if (digitalRead(groc) == LOW) check(groc, seq2);
  }

  while(start == blue){
      if (digitalRead(red) == LOW)  check(red, seq3);
      if (digitalRead(blue) == LOW) check(blue, seq3);
      if (digitalRead(verd) == LOW) check(verd, seq3);
      if (digitalRead(groc) == LOW) check(groc, seq3);
  }

  while(start == verd){
      if (digitalRead(red) == LOW)  check(red, seq4);
      if (digitalRead(blue) == LOW) check(blue, seq4);
      if (digitalRead(verd) == LOW) check(verd, seq4);
      if (digitalRead(groc) == LOW) check(groc, seq4);
  }

  // si és el botño negre, ho farà sequencialment

}

// Iniciar el programa pulsando el boton rojo durante dos segundos - (PROGRAMA 4 BOTONES A LA VEZ!)
int encender(){
  // Saber que botón se ha pulsado
  if (digitalRead(red) == LOW){
    pulsar = HIGH;
    botpuls = rojo;
  } else if (digitalRead(blue) == LOW)
  int pulsar = digitalRead(boton);
  bool inicio = false;
  unsigned long tiempoInicio = 0;

  if (pulsar == LOW && !inicio) {
    // millis es el tiempo actual
    Serial.println("Manten");
    tiempoInicio = millis();
    inicio = true;
    delay(2010);

    if(digitalRead(red) == HIGH){
      Serial.println("2s");
      inicio = false;
      tiempoInicio = 0;
      pulsar = LOW;
    }  
  }

  if (pulsar == LOW && inicio) {
    if (millis() - tiempoInicio >= 2000) { 
      Serial.println("Botón mantenido 2 segundos!");
      inicio = false;
      tiempoInicio = 0;
      
      //Tonadilla inicial
      tone(buzzer, 220, 150);  
      delay(200);
      tone(buzzer, 294, 120);  
      delay(170);
      tone(buzzer, 349, 200);  
      delay(300);
      noTone(buzzer);

      return pulsar;
    }
  }
  return 0; 
}

void check(int boton){
  // Evitar rebotes comprobando que el LOW se ha leído correctamente
  delay(50); 
  if (digitalRead(boton) == HIGH) return; 

  // Confirmación
  tone(buzzer, 1000, 100);
  delay(120);

  Serial.println(posicion);

  if (boton == seq1[posicion]) {
    Serial.println(":)");
    Serial.println(lenseq1);

    if (posicion >= lenseq1-1){
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
      
        tone(buzzer, 330, 150);  
        delay(200);
        tone(buzzer, 247, 150);  
        delay(200);
        tone(buzzer, 196, 300); 
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



















