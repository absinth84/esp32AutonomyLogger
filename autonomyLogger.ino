#include <SD.h>
#include <MS5611.h>
#include <SimpleKalmanFilter.h>


// SD pins configuration
#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  26
#define PIN_NUM_CS   5

//MS5611 pins configuration



#define PIN_LED 2

//Log filename prefix
String filename = "/log-00";

SPIClass spi;

MS5611 ms5611;

double referencePressure;

int counter;

SimpleKalmanFilter pressureKalmanFilter(0.2, 0.2, 0.05);

void setup() {


  Serial.begin(9600);
  while (!Serial) {
  }
  delay(3000);

  sdInit();

  baroInit();

 //Cycle led

 pinMode(PIN_LED, OUTPUT);

 
  
}

void loop() {

  digitalWrite(PIN_LED, HIGH);

  
  long realPressure = ms5611.readPressure();
  float relativeAltitude = ms5611.getAltitude(realPressure, referencePressure);
  float relativeAltitudeFiltered = pressureKalmanFilter.updateEstimate(relativeAltitude);

  String message = String(counter) + ", " + String(millis()) + ", " + String(relativeAltitude) + ", " + String(relativeAltitudeFiltered) + ";\n";

  Serial.println(message);
  
  
  appendFile(SD, filename, message);
  delay(50);
  
  counter++;
  digitalWrite(PIN_LED, LOW);
  delay(50);

  
}
