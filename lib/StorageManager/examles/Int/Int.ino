#include <Arduino.h>
#include "StorageManager.h"

const char *fileName PROGMEM = "/int.bin";
int a=0;
StorageManager<int> storageInt(a, fileName);// Тут значение a читается из фс если было ранее сохранено

void setup()
{
  Serial.begin(74880);
  Serial.printf("\n\nЗагрузка№ %03d\n", a);
  a++;
  storageInt.write(a);
  int b;
  storageInt.read(b); //Читаем из файла данные в произвольную переменную. Тип должен быть одинаковым!!!
  Serial.printf("Прочитано из файла значение %03d\n\n", b);
 
   //storageInt.deleteFile(); //удаляет свой файл с настройками
   //StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр
   //storageInt.formatFS(); //форматирует файловую систему
  
  delay(5000);
  ESP.restart();
}
void loop() { yield(); }