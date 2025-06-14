#pragma once
#include <vector>
#include <optional>

#include <QString>

void printParsingError(const std::string &message, const QString &filename, int location);

template<typename T>
bool loadJson(const QString &filename, std::vector<std::optional<T>> &vector);

template<typename T>
bool loadJson(const QString &filename, T &object);

template<typename T>
bool saveJson(const QString &filename, std::vector<std::optional<T>> &vector);

template<typename T>
bool saveJson(const QString &filename, T &object);
