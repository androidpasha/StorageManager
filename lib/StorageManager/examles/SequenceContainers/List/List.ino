#include <Arduino.h>
#include "StorageManager.h"
#include <list>

const char *fileName PROGMEM = "/list.bin";

struct settings
{
  int var1, var2;
  void print() { Serial.printf("var1:%02u\t\t var2:%02u\t\t\n", var1, var2); }
};

void printList(std::list<settings> &list)
{
  Serial.println(F("\n______________LIST______________"));
  for (auto &e : list)
    e.print();
}

void setup()
{
  Serial.begin(74880);
  uint8_t capacity = 5;                                            // Объём списка. Важно при первой загрузке. Дальше размер устанавливаеться из файла
  std::list<settings> list(capacity, {0, 0});                      // list.resize(capacity);
  StorageManager<std::list<settings>> storageList(list, fileName); // <std::vector<settings>> можно не указывать
  printList(list);//Выводим данные прочитанные из файла

  for (auto &e : list)
    e.var1 = e.var2++;

  storageList.write(list);
  list.clear(); // Очищаем вектор
  list.resize(0);
  storageList.read(list); // Читаем данные из файла в вектор
  printList(list);
  //storageList.deleteFile(); //удаляет свой файл с настройками
  // storageList.formatFS(); //форматирует файловую систему
  // StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр

  delay(5000);
  ESP.restart();
}
void loop() { yield(); }