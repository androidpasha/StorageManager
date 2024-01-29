// сохранение map со стоками не работает (строки)!!! Только с типами на стеке

#include <Arduino.h>
#include "StorageManager.h"
#include <map>

const char *fileName PROGMEM = "/map.bin";

void print(std::map<int, int> &data)
{
  Serial.println(F("\n____________map_____________"));
  for (const auto &pair : data)
    Serial.printf("\n %d:%d", pair.first, pair.second);
}

void setup()
{
  delay(1000);
  Serial.begin(74880);
  std::map<int, int> map;
  StorageManager storage(map, fileName); // <std::CONTAINER<settings>> можно не указывать
 print(map);
  for (int i = 0; i < 5; i++)
    map[i] = random(0,100);
  storage.write(map); // Пишем данные в файла
  storage.read(map); // Читаем данные из файла. Перед чтением map очищается.
  print(map);

  //storage.deleteFile(); //удаляет свой файл с настройками
  //storage.formatFS(); //форматирует файловую систему
  //StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр

  delay(5000);
  ESP.restart();
}
void loop() { yield(); }