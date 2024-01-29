#include <Arduino.h>
#include "StorageManager.h"
#include <map>

const char *fileName PROGMEM = "/multimap.bin";

void print(std::multimap<const char*, int> &data)
{
  Serial.println(F("\n____________MULTIMAP_____________"));
  for (const auto &pair : data)
    Serial.printf("\n %s:%d", pair.first, pair.second);
}

void setup()
{
  delay(1000);
  Serial.begin(74880);
  std::multimap<const char*, int> multimap;
  StorageManager storage(multimap, fileName); // <std::CONTAINER<settings>> можно не указывать
  print(multimap);
    const char *names[] = {
    "Pavel",
    "Anastasia",
    "Anna",
    "Oleg"
  };
  auto pair = std::make_pair(names[random(0,4)], (int)random(0, 10));
  multimap.insert(pair);

  storage.write(multimap); // Пишем данные в файла
  storage.read(multimap);  // Читаем данные из файла. Перед чтением multimap очищается.
  print(multimap);

  //storage.deleteFile(); //удаляет свой файл с настройками
  //storage.formatFS(); //форматирует файловую систему
  //StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр

  delay(5000);
  ESP.restart();
}
void loop() { yield(); }