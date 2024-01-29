#pragma once
#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#define WRITE_CONTEINER const {return writeContainer(container);}
#define READ_CONTEINER {return readContainer(container);}

template <typename data_t>
class StorageManager
{
public:
  StorageManager(data_t &data, const char *path);

  bool deleteFile() const { return LittleFS.remove(path); }
  
  static bool formatFS() { return LittleFS.format(); }

  template <typename T>
  bool write(const T &data) const;

  template <typename T>
  bool read(T &data);

  template <typename T> 
  bool read(std::list<T> &container) READ_CONTEINER

  template <typename T> 
  bool write(const std::list<T> &container) WRITE_CONTEINER

  template <typename T>
  bool read(std::vector<T> &container) READ_CONTEINER

  template <typename T>
  bool write(const std::vector<T> &container) WRITE_CONTEINER

  template <typename T> 
  bool read(std::deque<T> &container) READ_CONTEINER

  template <typename T>
  bool write(const std::deque<T> &container) WRITE_CONTEINER

  template <typename T>
  bool read(std::set<T> &container) READ_CONTEINER
 
  template <typename T>
  bool write(const std::set<T> &container) WRITE_CONTEINER

  template <typename T> 
  bool read(std::multiset<T> &container) READ_CONTEINER

  template <typename T>
  bool write(const std::multiset<T> &container) WRITE_CONTEINER

  template <typename T>
  bool read(std::unordered_set<T> &container){
    T e;
    return readUnorderedSetGroup(container, e);
   }
 
  template <typename T>
  bool write(const std::unordered_set<T> &container) WRITE_CONTEINER
 
  template <typename T>
  bool read(std::unordered_multiset<T> &container) {
    T e;
    return readUnorderedSetGroup(container, e);
  }

  template <typename T>
  bool write(const std::unordered_multiset<T> &container) WRITE_CONTEINER
 
  template <typename T1,typename T2>
  bool read(std::map<T1,T2> &container){
    T1 first; T2 second;
    return (readMapGroup(container, first, second));
  }

  template <typename T1,typename T2>
  bool write(const std::map<T1,T2> &container) WRITE_CONTEINER

  template <typename T1,typename T2>
  bool read(std::multimap<T1,T2> &container){
    T1 first; T2 second;
    return (readMapGroup(container, first, second));
  }

  template <typename T1,typename T2>
  bool write(const std::multimap<T1,T2> &container) WRITE_CONTEINER

  template <typename T1,typename T2>
  bool read(std::unordered_map<T1,T2> &container){
    T1 first; T2 second;
    return (readMapGroup(container, first, second));
  }

  template <typename T1,typename T2>
  bool write(const std::unordered_map<T1,T2> &container) WRITE_CONTEINER

  template <typename T1,typename T2>
  bool read(std::unordered_multimap<T1,T2> &container){
    T1 first; T2 second;
    return (readMapGroup(container, first, second));
  }

  template <typename T1,typename T2>
  bool write(const std::unordered_multimap<T1,T2> &container) WRITE_CONTEINER

  bool write(const String &container) WRITE_CONTEINER

  bool read(String &container);

private:
  const char *path;

  template <typename T>
  bool writeContainer(const T &container) const;

  template <typename T>
  bool readContainer(T &container);

  template <typename T ,typename T2, typename T3>
  bool readMapGroup(T &container, T2 &first, T3 &second);

  template <typename T, typename T1>
  bool readUnorderedSetGroup(T &container, T1 &e);
};

template <typename data_t>
StorageManager<data_t>::StorageManager(data_t &savedData, const char *path){
  LittleFS.begin();
  this->path = path;
  read(savedData);
}

template <typename data_t>
template <typename T>
bool StorageManager<data_t>::write(const T &data) const {
  File file = LittleFS.open(path, "w");
  if (!file)
    return false;
  file.write((byte *)&data, sizeof(data_t) / sizeof(byte));
  file.close();
  return true;
}

template <typename data_t>
template <typename T>
bool StorageManager<data_t>::read(T &savedData)
{
  File file = LittleFS.open(path, "r");
  if (file.size() != sizeof(data_t) or !file)
    return false;
  file.read((byte *)&savedData, file.size());
  file.close();
  return true;
}

template <typename data_t>
template <typename T>
bool StorageManager<data_t>::writeContainer(const T &container) const{
  File file = LittleFS.open(path, "w");
  if (!file) return false;
  for (const auto &e : container)
    file.write((byte *)&e, sizeof(e) / sizeof(byte));
  file.close();
  return true;
}

template <typename data_t>
template <typename T>
bool StorageManager<data_t>::readContainer(T &container)
{
  File file = LittleFS.open(path, "r");
  if (!file) return false;
  container.clear();
  auto e = *container.begin(); // Создаем переменную типа элемента контейнера
  while (file.available()) {
    file.read((byte *)&e, sizeof(e));
    container.insert(container.end(), e);
  }
  file.close();
  return true;
}

template <typename data_t>
template <typename T, typename T2, typename T3>
bool StorageManager<data_t>::readMapGroup(T &container, T2 &first, T3 &second)
{
  File file = LittleFS.open(path, "r");
  if (!file)
    return false;
  container.clear();
  while (file.available())
  {
    file.read((byte *)&first, sizeof(first));
    file.read((byte *)&second, sizeof(second));
    container.insert(std::make_pair(first, second));
  }
  file.close();
  return true;
}

template <typename data_t>
template <typename T, typename T1>
bool StorageManager<data_t>::readUnorderedSetGroup(T &container, T1 &e)
{
  File file = LittleFS.open(path, "r");
  if (!file)
    return false;
  container.clear();
  while (file.available())
  {
    file.read((byte *)&e, sizeof(e));
    container.insert(e);
  }
  file.close();
  return true;
}

template <typename data_t>
  bool StorageManager<data_t>::read(String &container){
    File file = LittleFS.open(path, "r");
    if (!file)
      return false;
    container="";
    char e;
    while (file.available())
    {
      file.read((byte *)&e, sizeof(e));
      container+=e;
    }
    file.close();
    return true;
  }

/*
Последовательные контейнеры:
                              std::vector: Динамический массив.
                              std::list: Двусвязный список.
                              std::deque: Двусторонняя очередь (двусвязный массив).

Ассоциативные контейнеры:
                              std::set: Отсортированное множество уникальных элементов.
                              std::map: Отсортированное отображение ключ-значение.
                              std::multiset: Множество, позволяющее дублирование элементов.
                              std::multimap: Отображение с возможностью дублирования ключей.

Неупорядоченные ассоциативные контейнеры:
                              std::unordered_set: Множество уникальных элементов без порядка.
                              std::unordered_map: Отображение ключ-значение без порядка.
                              std::unordered_multiset: Неупорядоченное множество с возможностью дублирования элементов.
                              std::unordered_multimap: Неупорядоченное отображение с возможностью дублирования ключей.

Адаптеры контейнеров:
std::stack: Стек, базирующийся на другом контейнере.
std::queue: Очередь, базирующаяся на другом контейнере.
std::priority_queue: Очередь с приоритетом, базирующаяся на другом контейнере.
Контейнер битов:

std::bitset: Последовательность фиксированного размера битов.
*/