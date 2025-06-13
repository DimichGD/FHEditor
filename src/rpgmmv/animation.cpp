#include "animation.hpp"
#include "json_stuff.hpp"

#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"

#include <QFile>

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
bool loadJson<Animation>(QString filename, std::vector<std::optional<Animation>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	if (err)
	{
		printParsingError(glz::format_error(err, std::string{}), filename, err.location);
		return false;
	}

	Animation normalAttack { .id = -1, .name = "Normal Attack" };
	vector.insert(vector.begin(), normalAttack);
	vector[1] = { .id = 0, .name = "None" };

	return true;
}
