
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
int secuenciaCorrecta[] = {9, 10, 11, 12};
int longitud = 4;

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
  // put your main code here, to run repeatedly:
  if(encender() == true){
    Serial.println("Programa iniciado!");
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
    }  
  }

  if (pulsar_rojo == LOW && inicio) {
    Serial.println(millis() - tiempoInicio);
    // Botón sigue pulsado
    if (millis() - tiempoInicio >= 2000) { 
      Serial.println("Botón mantenido 2 segundos!");
      inicio = false;
      tiempoInicio = 0;
      return true;
    }
  }
  
  return false;
  
}





















