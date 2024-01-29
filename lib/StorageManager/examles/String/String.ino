#include <Arduino.h>
#include "StorageManager.h"

const char *fileName PROGMEM = "/string.bin";

void setup()
{
  Serial.begin(74880);
  String str;

  StorageManager<String> storage(str, fileName); // <std::vector<settings>> можно не указывать
  Serial.println(str);//Выведет сохраненную строку в файле после включения

  const char *names[] = {
      "Pavel",
      "Anastasia",
      "Anna",
      "Oleg"};

  str = names[random(0, 4)];
  storage.write(str); //Записываем обновленную строку в файл
  storage.read(str); // Читаем данные из файла в строку
  Serial.println(str);// Выведет строку прочитанную из файла

  // storageVector.deleteFile(); //удаляет свой файл с настройками
  //  storageVector.formatFS(); //форматирует файловую систему
  //  StorageManager<int>::formatFS();//форматирует файловую систему без обращений через экземпляр

  delay(5000);
  ESP.restart();
}
void loop() { yield(); }