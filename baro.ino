
//Barometer ms5611 inizialization

void baroInit(){

    while(!ms5611.begin())
  {
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    delay(500);
  }


  // Get reference pressure for relative altitude
  referencePressure = ms5611.readPressure();
  Serial.print("Oversampling: ");
  Serial.println(ms5611.getOversampling());


}
