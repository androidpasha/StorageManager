#include <Arduino.h>
#include "StorageManager.h"
#include <set>

const char *fileName PROGMEM = "/multiset.bin";

void print(std::multiset<int> &data){
  Serial.println(F("\n_______________SET_______________"));
  for (auto &e : data)
    Serial.println(e);
}

void setup()
{
  Serial.begin(74880);
  std::multiset<int> multiset;
  StorageManager storage(multiset, fileName); // <std::CONTAINER<settings>> можно не указывать
  print(multiset);
  multiset.insert(random(0, 10));
  storage.write(multiset);
  storage.read(multiset); // Читаем данные из файла
  print(multiset);
  
  //storage.deleteFile(); //удаляет свой файл с настройками
  // storage.formatFS(); //форматирует файловую систему
  //StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр

  delay(5000);
  ESP.restart();
}
void loop() { yield(); }