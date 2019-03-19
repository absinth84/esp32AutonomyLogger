 // SD Initializion
  
void sdInit(){  


  spi.begin(PIN_NUM_CLK, PIN_NUM_MISO, PIN_NUM_MOSI, PIN_NUM_CS);
  //auto speed = 1000000;
  if(!SD.begin(PIN_NUM_CS, spi))//, speed))
       {
           Serial.println("SD NOT INIT");
           return;
        }
  
 
  Serial.println("SD CARD Ready");
  uint64_t cardType = SD.cardType();
  Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);

  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
  

  // SD check filename incremental    

   for(int i=0; i<100; i++){
    if(!SD.exists(filename + i + ".csv")){
      filename = filename + i + ".csv";
      Serial.println("File to use: " + filename);
      break;
    }
   }

   writeFile(SD, filename, "ID, time, altitude, altitude F\n");

 
   // Print File list 
   File root = SD.open( "/");

   Serial.println("File list:");

   File filename = root.openNextFile();
   while(filename){
      Serial.println(filename.name());
    
      filename = root.openNextFile();
   }
   

   root.close();

}


void writeFile(fs::FS &fs, String path, const char * message){
    Serial.print("Writing file:" + path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}


void appendFile(fs::FS &fs, String path, String message){
    Serial.println("Appending to file: " + path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

   
