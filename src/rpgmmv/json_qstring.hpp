#pragma once
#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"
#include <QString>
#include <string>

namespace glz
{
	template<>
	struct from<JSON, QString>
	{
		template <auto Opts>
		static void op(QString& value, auto&&... args)
		{
			std::string buffer {};
			parse<JSON>::op<Opts>(buffer, args...);
			value = QString::fromStdString(buffer);
		}
	};

	template<>
	struct to<JSON, QString>
	{
		template <auto Opts>
		static void op(QString& value, auto&&... args)
		{
			std::string buffer = value.toStdString();
			serialize<JSON>::op<Opts>(buffer, args...);
		}
	};
}
