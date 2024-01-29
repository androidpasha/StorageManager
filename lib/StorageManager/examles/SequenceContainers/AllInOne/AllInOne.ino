#include <Arduino.h>
#include "StorageManager.h"
#include <deque>
#include <vector>
#include <list>

#define CONTAINER vector
//#define CONTAINER list
//#define CONTAINER deque

const char *fileName PROGMEM = "/CONTAINER.bin";

struct settings
{
  int var1, var2;
  void print() { Serial.printf("var1:%02u\t\t var2:%02u\t\t\n", var1, var2); }
};

void print(std::CONTAINER<settings> &data){
  Serial.println(F("\n_____________CONTAINER_____________"));
  for (auto &e : data)
    e.print();
}

void setup()
{
  Serial.begin(74880);
  uint8_t capacity = 5;                           // Объём вектора. Важно при первой загрузке. Дальше размер устанавливаеться из файла
  std::CONTAINER<settings> CONTAINER(capacity, {0, 0}); // CONTAINER.resize(capacity);

  StorageManager<std::CONTAINER<settings>> storage(CONTAINER, fileName); // <std::deque<settings>> можно не указывать
  print(CONTAINER);
  for (auto &e : CONTAINER)
    e.var1 = e.var2++;


  storage.write(CONTAINER);

  CONTAINER.clear();//Очищаем вектор
  storage.read(CONTAINER); // Читаем данные из файла в вектор
  print(CONTAINER);
  
  // storage.deleteFile(); //удаляет свой файл с настройками
  // storage.formatFS(); //форматирует файловую систему
  // StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр

  delay(5000);
  ESP.restart();
}
void loop() { yield(); }