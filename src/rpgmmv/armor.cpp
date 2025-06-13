#include "armor.hpp"
#include "json_stuff.hpp"

#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"

#include <QFile>

#include <iostream>

template<>
bool loadJson<Armor>(QString filename, std::vector<std::optional<Armor>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	if (err)
	{
		printParsingError(glz::format_error(err, std::string{}), filename, err.location);
		return false;
	}

	return true;
}
