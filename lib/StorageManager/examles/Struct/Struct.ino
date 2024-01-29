#include <Arduino.h>
#include "StorageManager.h"

  struct settings {
  int var1 = 0;
  int var2 = 0;
  void print() {
    Serial.printf("\nvar1=%d, var2=%d\n", var1, var2);
  }
};

const char *fileName PROGMEM = "/struct.bin";
settings mySettings;
StorageManager<settings> storageStruct(mySettings, fileName);


void setup() {
  Serial.begin(74880);
  mySettings.print();
  mySettings.var1++;
  mySettings.var2++;
  storageStruct.write(mySettings);
  settings mySettings2;
  storageStruct.read(mySettings2); //Читаем из файла данные в произвольную переменную. Тип должен быть одинаковым!!!
  Serial.print("Прочитано из файла значения:");
  mySettings.print();
 
   //storageStruct.deleteFile(); //удаляет свой файл с настройками
   //StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр
   //storageStruct.formatFS(); //форматирует файловую систему

  delay(5000);
  ESP.restart();
}
void loop() {
  yield();
}
