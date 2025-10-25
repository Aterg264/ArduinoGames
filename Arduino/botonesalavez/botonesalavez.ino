// Pines
const int boto_blau = 9;
const int boto_roig = 10;
const int boto_groc = 11;
const int boto_verd = 12;

const int led_verd = 7;  // LOW = encendido
const int led_roig  = 8; // LOW = encendido

// Parámetros
const unsigned long T_SIMULT_MS       = 500;  // ventana "mismo instante"
const unsigned long BLOQUEO_MS        = 3000; // duración del bloqueo
const unsigned long PERIODO_PARPADEO  = 250;  // parpadeo rojo

// Estado
enum Estado { ESPERA, VENTANA, EXITO, BLOQUEO };
Estado estado = ESPERA;

// Ventana
unsigned long t_inicio_ventana = 0;
bool reg_blau = false, reg_roig = false, reg_groc = false, reg_verd = false;

// Bloqueo
unsigned long t_fin_bloqueo = 0;
unsigned long t_ultimo_toggle = 0;
bool rojo_encendido = false;

void setup() {
  Serial.begin(9600);

  pinMode(led_verd, OUTPUT);
  pinMode(led_roig, OUTPUT);
  // Apagar (activos en LOW)
  digitalWrite(led_verd, HIGH);
  digitalWrite(led_roig, HIGH);

  pinMode(boto_blau, INPUT_PULLUP);
  pinMode(boto_roig, INPUT_PULLUP);
  pinMode(boto_groc, INPUT_PULLUP);
  pinMode(boto_verd, INPUT_PULLUP);
}

void loop() {
  // Lecturas (LOW = pulsado)
  bool blau_p = (digitalRead(boto_blau) == LOW);
  bool roig_p = (digitalRead(boto_roig) == LOW);
  bool groc_p = (digitalRead(boto_groc) == LOW);
  bool verd_p = (digitalRead(boto_verd) == LOW);

  switch (estado) {
    case ESPERA: {
      if (blau_p || roig_p || groc_p || verd_p) {
        abrirVentana(blau_p, roig_p, groc_p, verd_p);
        estado = VENTANA;
      }
    } break;

    case VENTANA: {
      // Registrar cualquier botón pulsado dentro de la ventana
      if (blau_p) reg_blau = true;
      if (roig_p) reg_roig = true;
      if (groc_p) reg_groc = true;
      if (verd_p) reg_verd = true;

      unsigned long ahora = millis();
      bool todos = (reg_blau && reg_roig && reg_groc && reg_verd);

      if (todos && (ahora - t_inicio_ventana) <= T_SIMULT_MS) {
        Serial.println("Perfecto");
        digitalWrite(led_roig, HIGH); // rojo off
        digitalWrite(led_verd, LOW);  // verde on (se queda fijo)
        estado = EXITO;               // ¡latcheado!
      } else if ((ahora - t_inicio_ventana) > T_SIMULT_MS) {
        iniciarBloqueo();
        estado = BLOQUEO;
      }
    } break;

    case EXITO: {
      // Estado final: no se modifica nada, se ignoran entradas.
      // LED verde permanece encendido.
      // (Si quisieras un reset manual, añádelo aquí con una condición.)
    } break;

    case BLOQUEO: {
      unsigned long ahora = millis();

      // Parpadeo rojo durante el bloqueo
      if (ahora - t_ultimo_toggle >= PERIODO_PARPADEO) {
        t_ultimo_toggle = ahora;
        rojo_encendido = !rojo_encendido;
        digitalWrite(led_roig, rojo_encendido ? LOW : HIGH);
      }
      digitalWrite(led_verd, HIGH); // verde off en bloqueo

      if (ahora >= t_fin_bloqueo) {
        digitalWrite(led_roig, HIGH); // rojo off
        // Esperar a que suelten todos para rearmar
        if (!blau_p && !roig_p && !groc_p && !verd_p) {
          resetVentana();
          estado = ESPERA;
        }
      }
    } break;
  }
}

// --- Helpers ---
void abrirVentana(bool b, bool r, bool g, bool v) {
  t_inicio_ventana = millis();
  reg_blau = b; reg_roig = r; reg_groc = g; reg_verd = v;
}

void resetVentana() {
  t_inicio_ventana = 0;
  reg_blau = reg_roig = reg_groc = reg_verd = false;
}

void iniciarBloqueo() {
  Serial.println("Intenta-ho de nou!");
  t_fin_bloqueo = millis() + BLOQUEO_MS;
  t_ultimo_toggle = 0;
  rojo_encendido = false;
  digitalWrite(led_verd, HIGH); // verde off
  digitalWrite(led_roig, HIGH); // arranca apagado, luego parpadea
}
