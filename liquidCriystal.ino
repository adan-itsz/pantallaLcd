#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);
const int pinLcdALed=6;
const int PIN_ERR_LED = 7;  // digital
const int pinBoton1 = 8;  // digital
const int pinBoton2 = 9;  // digital
const int lcdColumnas = 16;
const int lcdBrillo= 128;
int estadoLcd=LOW;
int lcdInicio=0;
int estadoLed = LOW;
unsigned long tiempoLed;
const int tiempoEsperaLed = 500;

// texto a imprimir 
const char texto[] = "Adan De Santiago Avalos";
const int tamanoTexto = (sizeof(texto) / sizeof(char)) - 1;
const int limitesLcd = tamanoTexto - lcdColumnas;



void setup() {
  //primera implementacion 
 /* lcd.begin(6,2);
  lcd.setCursor(0,1);
  lcd.write("Aprendere HTML");
  */
  //

  //texto en movimiento

    //  Configuración pines digitales 
  pinMode(pinBoton1, INPUT);
  pinMode(pinBoton2, INPUT);

  pinMode(PIN_ERR_LED, OUTPUT);

  // Configuración LCD 
  lcd.begin(16,2);
  lcd.noDisplay();
  digitalWrite(pinLcdALed, estadoLcd);

  // LED de error está apagado cuando se empieza
  digitalWrite(PIN_ERR_LED, estadoLed);

  
  }



void loop() {

  //  asignación botones 
  int estadoBoton1 = digitalRead(pinBoton1);
  int estadoBoton2 = digitalRead(pinBoton2);

  //  LCD aún apagada 
  if(LOW == estadoLcd)
  {
    // apretando los dos botones a la vez -> encendido pantalla LCD
    if(HIGH == estadoBoton1 && HIGH == estadoBoton2)
    {
      analogWrite(pinLcdALed, lcdBrillo);

      lcd.display();

      estadoLcd = HIGH;

      delay(250);
    }
  }
  else  // LCD ON 
  {
    // presionar pulsador 1 ->intentar deslizar hacia la izquierda o encender el LED si no se puede
    if(HIGH == estadoBoton1)
    {
      if(lcdInicio > 0)
      {
        lcdInicio--;

        estadoLed = LOW;
        digitalWrite(PIN_ERR_LED, estadoLed);

        delay(200);
      }
      else
      {
        estadoLed = HIGH;
        digitalWrite(PIN_ERR_LED, estadoLed);

        tiempoLed = millis();
      }
    }

    //  presionar pulsador 2 ->intentar deslizar hacia la derecha o encender el LED si no se puede
    if(HIGH == estadoBoton2)
    {
      if(lcdInicio < limitesLcd)
      {
        lcdInicio++;

        estadoLed= LOW;
        digitalWrite(PIN_ERR_LED, estadoLed);

        delay(200);
      }
      else
      {
        estadoLed = HIGH;
        digitalWrite(PIN_ERR_LED, estadoLed);

        tiempoLed = millis();
      }
    }

    //  Imprimir texto por pantalla 
    for(int i = 0; i < lcdColumnas; i++)
    {
      lcd.setCursor(i, 0);
      lcd.print(texto[lcdInicio + i]);
    }

    // LED de error está ON
    if(HIGH == estadoLed)
    {
      unsigned long td = millis() - tiempoLed;

      // LED ha estado encendido más tiempo que LED_TIMEOUT ms . -> apagarlo
      if(td > tiempoEsperaLed)
      {
        estadoLed = LOW;
        digitalWrite(PIN_ERR_LED, estadoLed);
      }
    }
  }

  // normalmente 20FPS
  delay(50);
}


