#include <MTboard.h>
#define TIME_INTERMITENTE 500
#define VECES_INTERMITENTE 5
#define TIEMPO_ONOFF 500
#define TIEMPO_PULSAR 2000
#define LAT "40 19.732"
#define LONG "03 43.295"
#define INTENTOS 6
int secuencia[INTENTOS];
MTboard mtBoard;




void setup() {

  randomSeed(analogRead(A7));// inicia el array con los numeros aleatorios
}

void loop() {

  ledsInicio();
  for (int k = 1; k < INTENTOS; k++)
  {
    //Serial.print(k);
    //Serial.print(",");
    mtBoard.print(k);
    for (int n = 0; n < k; n++) { //muestra secuencia
      mtBoard.enciendeLed(secuencia[n]);
      delay(TIEMPO_ONOFF);
    }
    for (int n = 0; n < k; n++) { //lee la secuencia de  pulsadores
      if (mtBoard.esperaPulsador(KEY_TIMEOUT) != secuencia[n])
      {
        ledsError();
        return; //Vuelve a empezar
      }
    }
    mtBoard.drawBitmap(ALEGRE);
    delay(TIME_INTERMITENTE);
    mtBoard.enciendeTodos();
    delay(TIME_INTERMITENTE);
    mtBoard.apagaTodos();
    delay(TIME_INTERMITENTE);
  }
  while (1) {
    mtBoard.coordenadasShow();
  }
}

void ledsError() {
  mtBoard.drawBitmap(TRISTE);
  for (int k = 0; k < VECES_INTERMITENTE; k++) {
    mtBoard.enciendeTodos();
    delay(TIME_INTERMITENTE);
    mtBoard.apagaTodos();
    delay(TIME_INTERMITENTE);
  }
}
void ledsInicio() {
  for ( int n = 0; n < INTENTOS; n++) {
    secuencia[n] = random(TECLAS);  // para eso utiliza randon
    //Serial.print(secuencia[n]);
  }
  //Serial.println();
  delay(TIME_INTERMITENTE);
   mtBoard.enciendeTodos();
    delay(TIME_INTERMITENTE);
    mtBoard.apagaTodos();
    delay(TIME_INTERMITENTE);
}
