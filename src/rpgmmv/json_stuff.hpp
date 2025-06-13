#pragma once
#include "map.hpp"
#include <vector>
#include <optional>

#include <QString>

void printParsingError(const std::string &message, const QString &filename, int location);

template<typename T>
bool loadJson(QString filename, std::vector<std::optional<T>> &vector);

template<typename T>
bool loadJson(QString filename, T &object);

template<typename T>
bool saveJson(QString filename, std::vector<std::optional<T>> &vector);

template<typename T>
bool saveJson(QString filename, T &object);
