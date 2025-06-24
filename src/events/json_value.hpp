#pragma once
#include <vector>
#include <string>
#include <map>
#include <variant>
#include <QString>
#include <QStringList>
#include "glaze/core/meta.hpp"

struct JsonValue
{
	using array_t = std::vector<JsonValue>;
	using object_t = std::map<std::string, JsonValue, std::less<>>;
	using null_t = std::nullptr_t;
	using val_t = std::variant<null_t, double, std::string, bool, array_t, object_t>;
	val_t data {};

	JsonValue& operator[](int index)
	{
		return std::get<array_t>(data)[index];
	}

	JsonValue& operator[](const std::string &key)
	{
		return std::get<object_t>(data)[key];
	}

	QString toQString() const
	{
		return QString::fromStdString(std::get<std::string>(data));
	}

	int toInt() const
	{
		return int(std::get<double>(data));
	}

	QStringList toStringList() const
	{
		QStringList result;
		for (auto &s: std::get<array_t>(data))
			result << s.toQString();

		return result;
	}
};

template <>
struct glz::meta<JsonValue>
{
	static constexpr std::string_view name = "JsonValue";
	using T = JsonValue;
	static constexpr auto value = &T::data;
};
