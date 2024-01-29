#include <Arduino.h>
#include "StorageManager.h"
#include <set>

const char *fileName PROGMEM = "/set.bin";

void print(std::set<int> &data){
  Serial.println(F("\n_______________SET_______________"));
  for (auto &e : data)
    Serial.println(e);
}

void setup()
{
  Serial.begin(74880);
  std::set<int> set;
  StorageManager storage(set, fileName); // <std::CONTAINER<settings>> можно не указывать
  print(set);
  set.insert(random(0, 10));
  storage.write(set);// Пишем данные в файла
  storage.read(set); // Читаем данные из файла. Перед чтением set очищается.
  print(set);
  
  //storage.deleteFile(); //удаляет свой файл с настройками
  //storage.formatFS(); //форматирует файловую систему
  //StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр

  delay(5000);
  ESP.restart();
}
void loop() { yield(); }