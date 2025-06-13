#include "state.hpp"
#include "json_stuff.hpp"

#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"

#include <QFile>

#include <iostream>

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

template<>
bool loadJson<State>(QString filename, std::vector<std::optional<State>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	if (err)
	{
		printParsingError(glz::format_error(err, std::string{}), filename, err.location);
		return false;
	}

	return true;
}

template<>
bool saveJson<State>(QString filename, std::vector<std::optional<State>> &vector)
{
	QFile json_file(filename);
	if (!json_file.open(QFile::WriteOnly))
		return false;

	json_file.write("[\n");

	std::string buffer;
	glz::error_ctx err;
	bool first = true;

	for (size_t i = 0; i < vector.size(); i++)
	{
		json_file.write(first ? "\n" : ",\n");

		err = glz::write_json(vector.at(i), buffer);
		if (err)
		{
			std::cout << err << std::endl;
			return false;
		}

		json_file.write(buffer.data(), buffer.size());
		first = false;
	}

	json_file.write("\n]");
	return true;
}
