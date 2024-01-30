#include <Arduino.h>
//#define FS_t SPIFFS
#include "StorageManager.h"
#include <unordered_map>

const char *fileName PROGMEM = "/unordered_map.bin";

template<typename T1, typename T2>
void print(std::unordered_map<T1, T2> &data)
{
  Serial.println(F("____________unordered_map_____________"));
  for (const auto &pair : data)
    Serial.printf("\n %0d : %s", pair.first, pair.second);
}

void setup()
{
  delay(1000UL);
  Serial.begin(74880UL);
  std::unordered_map<int, String> unordered_map;
  StorageManager storage(unordered_map, fileName);
  Serial.printf("\nRead from flash. File size = %d byte.\n", storage.size());
  print(unordered_map);

  String name[] = {"Pavel", "Anastasia", "Anna", "Oleg"};

  for (int i = 0; i < 5; i++)
    unordered_map[i] = name[random(0L,4L)];
  storage.write(unordered_map); // Пишем данные в файла

  delay(10000UL);
  ESP.restart();
}
void loop() { yield(); }