#include "json_stuff.hpp"
#include "armor.hpp"
#include "item.hpp"
#include "map.hpp"
#include "animation.hpp"
#include "map_info.hpp"
//#include "rpgmmz/system_mz.hpp"
#include "skill.hpp"
#include "state.hpp"
#include "system.hpp"
#include "tileset.hpp"
#include "weapon.hpp"
#include "event.hpp"
#include "command_factory.hpp"
#include "json_qstring.hpp"


#include <QFile>
#include <QDebug>

template <>
struct glz::from<glz::JSON, Command>
{
	template <auto Opts>
	static bool read_k(std::string_view sv, is_context auto&& ctx, auto&& it, auto&& end)
	{
		static std::string_view buffer = "XXXXXXXXXXXXXXXXXXXX";
		skip_ws<Opts>(ctx, it, end);
		parse<JSON>::op<Opts>(buffer, ctx, it, end);
		if (buffer != sv)
		{
			ctx.error = error_code::unknown_key;
			return true;
		}

		skip_ws<Opts>(ctx, it, end);
		if (match<':'>(ctx, it))
			return true;

		return false;
	}

	template <auto Opts>
	static bool read_kv(std::string_view sv, int &value, is_context auto&& ctx, auto&& it, auto&& end)
	{
		if (read_k<Opts>(sv, ctx, it, end))
			return true;

		skip_ws<Opts>(ctx, it, end);
		parse<JSON>::op<Opts>(value, ctx, it, end);

		skip_ws<Opts>(ctx, it, end);
		if (match<','>(ctx, it))
			return true;

		return false;
	}

	template <auto Opts>
	static void op(Command& value, is_context auto&& ctx, auto&& it, auto&& end)
	{
		skip_ws<Opts>(ctx, it, end);
		if (match<'{'>(ctx, it))
			return;

		if (read_kv<Opts>("code", value.code, ctx, it, end))
			return;

		if (read_kv<Opts>("indent", value.indent, ctx, it, end))
			return;

		if (read_k<Opts>("parameters", ctx, it, end))
			return;

		skip_ws<Opts>(ctx, it, end);
		const auto start = it++;
		skip_until_closed<Opts, '[', ']'>(ctx, it, end);
		value.parameters = CommandFactory::createCommand2(value.code);
		value.parameters->read({ start, size_t(it - start) });

		skip_ws<Opts>(ctx, it, end);
		if (match<'}'>(ctx, it))
			return;
	}
};


template <>
struct glz::to<glz::JSON, QSharedPointer<ICommand>>
{
	template <auto Opts>
	static void op(QSharedPointer<ICommand>& value, is_context auto&& ctx, auto&& it, auto&& end) noexcept
	{
		serialize<JSON>::op<glz::opts{.raw = true}>(value->write(), ctx, it, end);
	}
};



/*template <>
struct glz::to<glz::JSON, Command>
{
	template <auto Opts>
	static void op(Command& value, is_context auto&& ctx, auto&& it, auto&& end) noexcept
	{
		serialize<JSON>::op<Opts>("{code:", ctx, it, end);
		serialize<JSON>::op<Opts>(value.code, ctx, it, end);
		serialize<JSON>::op<Opts>(",indent:", ctx, it, end);
		serialize<JSON>::op<Opts>(value.indent, ctx, it, end);
		serialize<JSON>::op<Opts>(",parameters:", ctx, it, end);
		serialize<JSON>::op<Opts>(value.parameters, ctx, it, end);
		serialize<JSON>::op<Opts>("}", ctx, it, end);
	}
};*/

template <>
struct glz::from<glz::JSON, Route>
{
	template <auto Opts>
	static void op(Route& value, is_context auto&& ctx, auto&& it, auto&& end)
	{
		const auto start = it++;
		skip_until_closed<Opts, '{', '}'>(ctx, it, end);
		value.parseLater = { start, size_t(it - start) };
	}
};

template <>
struct glz::to<glz::JSON, Route>
{
	template <auto Opts>
	static void op(Route& value, is_context auto&& ctx, auto&& it, auto&& end)
	{
		serialize<JSON>::op<glz::opts{.raw = true}>(value.parseLater, ctx, it, end);
	}
};

template <>
struct glz::from<glz::JSON>
{
	template <auto Opts>
	static void op(Timing& value, is_context auto&& ctx, auto&& it, auto&& end)
	{
		(void)value;
		const auto start = it++;
		skip_until_closed<Opts, '{', '}'>(ctx, it, end);
		//value.parseLater = { start, size_t(it - start) };
	}
};

bool showParsingError(glz::error_ctx err, const QString &filename)
{
	if (err)
	{
		qDebug() << QString::fromStdString(glz::format_error(err));
		QFile file(filename);
		file.open(QIODevice::ReadOnly);
		if (err.location > 10)
		{
			file.skip(err.location - 10);
			qDebug().noquote() << file.read(30);
			qDebug().noquote() << "          ^";
		}
		return false;
	}

	return true;
}

template<>
bool loadJson<Item>(const QString &filename, std::vector<std::optional<Item>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Armor>(const QString &filename, std::vector<std::optional<Armor>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Weapon>(const QString &filename, std::vector<std::optional<Weapon>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Event>(const QString &filename, std::vector<std::optional<Event>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<MapInfo>(const QString &filename, std::vector<std::optional<MapInfo>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<TileSet>(const QString &filename, std::vector<std::optional<TileSet>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Map>(const QString &filename, Map &object)
{
	glz::error_ctx err = glz::read_file_json(object, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<System>(const QString &filename, System &object)
{
	glz::error_ctx err = glz::read_file_json(object, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Skill>(const QString &filename, std::vector<std::optional<Skill>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<State>(const QString &filename, std::vector<std::optional<State>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Animation>(const QString &filename, std::vector<std::optional<Animation>> &vector)
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

/*template<>
bool loadJson<MZ::System>(const QString &filename, MZ::System &object)
{
	glz::error_ctx err = glz::read_file_json(object, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}*/

template<>
bool saveJson<Item>(const QString &filename, std::vector<std::optional<Item>> &vector)
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
			qDebug() << err;
			return false;
		}

		json_file.write(buffer.data(), buffer.size());
		first = false;
	}

	json_file.write("\n]");
	return true;
}

template<>
bool saveJson<Weapon>(const QString &filename, std::vector<std::optional<Weapon>> &vector)
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
			qDebug() << err;
			return false;
		}

		json_file.write(buffer.data(), buffer.size());
		first = false;
	}

	json_file.write("\n]");
	return true;
}

template<>
bool saveJson<Event>(const QString &filename, std::vector<std::optional<Event>> &vector)
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
			qDebug() << err;
			return false;
		}

		json_file.write(buffer.data(), buffer.size());
		first = false;
	}

	json_file.write("\n]");
	return true;
}

template<>
bool saveJson<Skill>(const QString &filename, std::vector<std::optional<Skill>> &vector)
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
			qDebug() << err;
			return false;
		}

		json_file.write(buffer.data(), buffer.size());
		first = false;
	}

	json_file.write("\n]");
	return true;
}

template<>
bool saveJson<State>(const QString &filename, std::vector<std::optional<State>> &vector)
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
			qDebug() << err;
			return false;
		}

		json_file.write(buffer.data(), buffer.size());
		first = false;
	}

	json_file.write("\n]");
	return true;
}

void printParsingError(const std::string &message, const QString &filename, int location)
{
	if (!message.empty())
	{
		//qDebug() << glz::format_error(err, std::string{});
		qDebug() << QString::fromStdString(message);
		QFile file(filename);
		file.open(QIODevice::ReadOnly);
		if (location > 10)
		{
			file.skip(location - 10);
			qDebug().noquote() << file.read(30);
			qDebug().noquote() << "          ^";
		}
	}
}

template<>
bool saveJson<Map>(const QString &filename, Map &object)
{
	glz::error_ctx err = glz::write_file_json(object, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

