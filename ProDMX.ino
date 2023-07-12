#include "LPD8806.h"
#include "SPI.h"
#include "Wire.h"
#include "string.h"
#include "Arduino.h"
// Example to control LPD8806-based RGB LED Modules 
//string data=Serial.readStringUntil('\n');

/***/
 String data = "123";
// Number of RGB LEDs in strand:
int nLEDs = 2;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);


void setColor(int index);
void colorChase(uint32_t c, uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void fadeAnimation(uint32_t colorStart, uint32_t colorEnd, uint32_t duration);
uint32_t Wheel(uint16_t WheelPos);
void sparkleAnimation(uint32_t color, int numSparkles, uint32_t duration);
void cascadePattern(uint32_t color, uint32_t interval, uint32_t duration);
void sequentialOutputActivation(uint32_t interval);
void activateOutput(int index);
void deactivateOutput(int index);
void turnOnAllRed();
void turnOnAllGreen();
void turnOnAllBlue();
void pulseAnimation(uint32_t color, uint32_t duration);
void setColor(int index,int r, int g, int b);
void setup() {
  Serial.begin(9600);
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
  
}


void loop() {
  
   if (Serial.available()) {
    data = Serial.readStringUntil('\n');
    int c=data.toInt();
      
   switch (c){
       case 1: // Send a simple pixel chase in...
        Serial.println("case 1");
        colorChase(strip.Color(127, 127, 127), 250); // White
        colorChase(strip.Color(127,   0,   0), 250); // Red
        colorChase(strip.Color(127, 127,   0), 250); // Yellow
        colorChase(strip.Color(  0, 127,   0), 250); // Green
        colorChase(strip.Color(  0, 127, 127), 250); // Cyan
        colorChase(strip.Color(  0,   0, 127), 250); // Blue
        colorChase(strip.Color(127,   0, 127), 250); // Violet
        break;
      case 2:
        // Send a theater pixel chase in...
        Serial.println("case 2");
        theaterChase(strip.Color(127, 127, 127), 250); // White
        theaterChase(strip.Color(127,   0,   0), 250); // Red
        theaterChase(strip.Color(127, 127,   0), 250); // Yellow
        theaterChase(strip.Color(  0, 127,   0), 250); // Green
        theaterChase(strip.Color(  0, 127, 127), 250); // Cyan
        theaterChase(strip.Color(  0,   0, 127), 250); // Blue
        theaterChase(strip.Color(127,   0, 127), 250); // Violet
        break;
      case 3: 
        Serial.println("case 3");// Rutina con mpw
        // rojo
           for (int i = 0; i < 127; i++) {
           setColor(0, i, 0, 0);
           setColor(1, i, 0, 0);
           Serial.println(i);
            delay(10);
    }
          for (int i = 127; i > 0; i--) {
          setColor(0, i, 0, 0);
          setColor(1, i, 0, 0);
          Serial.println(i);
            delay(10);
    }
    // verde
          for (int i = 0; i < 127; i++) {
          setColor(0, 0, i, 0);
          setColor(1, 0, i, 0);
          Serial.println(i);
          delay(10);
    }
          for (int i = 127; i > 0; i--) {
          setColor(0, 0, i, 0);
          setColor(1, 0, i, 0);
          Serial.println(i);
           delay(10);
    }
   // azul 
          for (int i = 0; i < 127; i++) {
          setColor(0, 0, 0, i);
          setColor(1, 0, 0, i);
          Serial.println(i);
            delay(10);
    }
         for (int i = 127; i > 0; i--) {
         setColor(0, 0, 0, i);
         setColor(1, 0, 0, i);
         Serial.println(i);
          delay(10);
    }
        break;
      case 4:
        Serial.println("case 4");
        fadeAnimation(strip.Color(255, 0, 0), strip.Color(0, 255, 0), 1000); // Fade de rojo a verde
        fadeAnimation(strip.Color(0, 255, 0), strip.Color(0, 0, 255), 1000); // Fade de verde a azul
        fadeAnimation(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 1000); // Fade de azul a rojo
        break;
      case 5:
        Serial.println("case 5");
        sparkleAnimation(strip.Color(255, 255, 255), 20, 2000); // Sparkle en color blanco con 20 destellos y una duración de 2 segundos
        delay(1000); // Esperar 1 segundo antes de repetir el efecto
        break;
      case 6:
        Serial.println("case 6");
        pulseAnimation(strip.Color(255, 0, 0), 2000); // Pulso en color rojo con una duración de 2 segundos
        break;
      case 7:
        Serial.println("case 7");// Encender salida por salida
        for (int i = 0; i < 6; i++) {
          setColor(i);
          delay(800);
        }
         break;
      case 8:
        Serial.println("case 8");
        cascadePattern(strip.Color(0, 255, 0), 100, 100); // Patrón de cascada en color verde con un intervalo de 100 ms y duración de 1000 ms
        break;
      case 9:
        Serial.println("case 9");//rgb
        turnOnAllRed(); // Encender todos los LEDs en rojo
          delay(2000); // Esperar 2 segundos
        turnOnAllGreen(); // Encender todos los LEDs en verde
          delay(2000); // Esperar 2 segundos
         turnOnAllBlue(); // Encender todos los LEDs en azul
           delay(2000); // Esperar 2 segundos
        break;
      default: 
      break;
    }
  }
}



// RUTINA
void setColor(int index) {
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.setPixelColor(1, strip.Color(0, 0, 0));
  strip.show(); // Mostrar el cambio en los LEDs
  switch(index) {
    case 0:
        strip.setPixelColor(0, strip.Color(255, 0, 0));
        strip.show();
        break;
    case 1:
        strip.setPixelColor(0, strip.Color(0, 255, 0));
        strip.show();
        break;
    case 2:
        strip.setPixelColor(0, strip.Color(0, 0, 255));
        strip.show();
        break;
    case 3:
        strip.setPixelColor(1, strip.Color(255, 0, 0));
        strip.show();
        break;
    case 4:
        strip.setPixelColor(1, strip.Color(0, 255, 0));
        strip.show();
        break;
    case 5:
        strip.setPixelColor(1, strip.Color(0, 0, 255));
        strip.show();
        break;
  }
}

 // mpw
 void setColor(int index,int r, int g, int b) {
  
  strip.setPixelColor(index, strip.Color(g, r, b));
  strip.show(); // Mostrar el cambio en los LEDs
  
}
  // Rgb
  void turnOnAllRed() {
  for (int i = 0; i < nLEDs; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // Establecer el color rojo para cada LED
  }
  strip.show(); // Mostrar los cambios en los LEDs
}

void turnOnAllGreen() {
  for (int i = 0; i < nLEDs; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // Establecer el color verde para cada LED
  }
  strip.show(); // Mostrar los cambios en los LEDs
}

void turnOnAllBlue() {
  for (int i = 0; i < nLEDs; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255)); // Establecer el color azul para cada LED
  }
  strip.show(); // Mostrar los cambios en los LEDs
}
// Activar cada salida en secuencia
  void sequentialOutputActivation(uint32_t interval) {
  for (int i = 0; i < nLEDs; i++) {
    activateOutput(i); // Activar la salida actual
    delay(interval);
    deactivateOutput(i); // Apagar la salida actual
  }
}

void activateOutput(int index) {
  strip.setPixelColor(index, strip.Color(255, 255, 255)); // Establecer el color blanco para la salida especificada
  strip.show(); // Mostrar el color en los LEDs
}

void deactivateOutput(int index) {
  strip.setPixelColor(index, strip.Color(0, 0, 0)); // Establecer el color negro para apagar la salida especificada
  strip.show(); // Mostrar el color en los LEDs
}
  
 // Efecto cascada ROJA
void cascadePattern(uint32_t color, uint32_t interval, uint32_t duration) {
  uint32_t startTime = millis();
  uint32_t endTime = startTime + duration;

  for (int i = 0; i < nLEDs; i++) {
    strip.setPixelColor(i, color); // Encender el LED actual
    strip.show();
    delay(interval);
    strip.setPixelColor(i, 0); // Apagar el LED actual
  }

  strip.show(); // Asegurarse de que todos los LEDs estén apagados al final del patrón

  uint32_t elapsedTime = millis() - startTime;
  if (elapsedTime < duration) {
    delay(duration - elapsedTime); // Esperar el tiempo restante si la duración del patrón no se ha cumplido completamente
  }
}
//Pulse
  void pulseAnimation(uint32_t color, uint32_t duration) {
  uint32_t startTime = millis();
  uint32_t endTime = startTime + duration;
  int brightness = 0;
  bool increasing = true;

  while (millis() < endTime) {
    if (increasing) {
      brightness++;
      if (brightness >= 255) {
        increasing = false;
      }
    } else {
      brightness--;
      if (brightness <= 0) {
        increasing = true;
      }
    }

    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r = (r * brightness) / 255;
    g = (g * brightness) / 255;
    b = (b * brightness) / 255;

    for (int i = 0; i < nLEDs; i++) {
      strip.setPixelColor(i, r, g, b);
    }

    strip.show();
    delay(10); // Pequeña pausa entre cada iteración para ajustar la velocidad del pulso
  }
}
  // SparkleAnimation
 void sparkleAnimation(uint32_t color, int numSparkles, uint32_t duration) {
  uint32_t startTime = millis();
  uint32_t endTime = startTime + duration;

  while (millis() < endTime) {
    for (int i = 0; i < numSparkles; i++) {
      int randomLed = random(0, nLEDs); // Elegir un LED aleatorio
      strip.setPixelColor(randomLed, color); // Encender el LED aleatorio con el color especificado
    }

    strip.show();
    delay(100); // Pequeña pausa entre cada iteración para ajustar la velocidad de los destellos

   
  }

  strip.show(); // Asegurarse de que todos los LEDs estén apagados al final del efecto
}
// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for (j=0; j < 384 * 2; j++) {     //2cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show(); // write all the pixels out
    
    delay(wait);
  }
}

 

  //FadeAnimation
  void fadeAnimation(uint32_t colorStart, uint32_t colorEnd, uint32_t duration) {
  uint32_t startTime = millis();
  uint32_t endTime = startTime + duration;

  while (millis() < endTime) {
    float progress = (float)(millis() - startTime) / duration;

    uint8_t r = (uint8_t)((1.0 - progress) * ((colorStart >> 16) & 0xFF) + progress * ((colorEnd >> 16) & 0xFF));
    uint8_t g = (uint8_t)((1.0 - progress) * ((colorStart >> 8) & 0xFF) + progress * ((colorEnd >> 8) & 0xFF));
    uint8_t b = (uint8_t)((1.0 - progress) * (colorStart & 0xFF) + progress * (colorEnd & 0xFF));

    for (int i = 0; i < nLEDs; i++) {
      strip.setPixelColor(i, r, g, b);
    }

    strip.show();
  }
}
// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<3; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
