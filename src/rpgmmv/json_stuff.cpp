#include "json_stuff.hpp"
#include "actor.hpp"
#include "armor.hpp"
#include "class.hpp"
#include "enemy.hpp"
#include "item.hpp"
#include "map.hpp"
#include "animation.hpp"
#include "map_info.hpp"
//#include "rpgmmz/system_mz.hpp"
#include "skill.hpp"
#include "state.hpp"
#include "system.hpp"
#include "tileset.hpp"
#include "troop.hpp"
#include "weapon.hpp"
#include "event.hpp"
#include "command_factory.hpp"
#include "json_qstring.hpp"

#include <QFile>
#include <QDebug>


/*template <>
struct glz::to<glz::JSON, QSharedPointer<ICommandParams>>
{
	template <auto Opts>
	static void op(QSharedPointer<ICommandParams>& value, is_context auto&& ctx, auto&& it, auto&& end) noexcept
	{
		serialize<JSON>::op<glz::opts{.raw = true}>(value->write(), ctx, it, end);
	}
};*/

template<>
struct glz::to<glz::JSON, std::shared_ptr<ICommandParams>>
{
	template <auto Opts>
	static void op(std::shared_ptr<ICommandParams> &value, is_context auto&& ctx, auto&& it, auto&& end) noexcept
	{
		serialize<JSON>::op<glz::opts{.raw = true}>(value->write(), ctx, it, end);
	}
};

template <>
struct glz::meta<Command>
{
	using T = Command;
	static constexpr auto readParams = [](Command &command, JsonValue &&jsonValues)
	{
		command.parameters = CommandFactory::createCommand2(command.code);
		command.parameters->read(jsonValues);
	};
	static constexpr auto value = object("code", &T::code,
										 "indent", &T::indent,
										 "parameters", custom<readParams, &T::parameters>);
};


/*template <>
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
};*/

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
bool loadJson<Actor>(const QString &filename, std::vector<std::optional<Actor>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Class>(const QString &filename, std::vector<std::optional<Class>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Animation>(const QString &filename, std::vector<std::optional<Animation>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Enemy>(const QString &filename, std::vector<std::optional<Enemy>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

template<>
bool loadJson<Troop>(const QString &filename, std::vector<std::optional<Troop>> &vector)
{
	glz::error_ctx err = glz::read_file_json(vector, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}

/*template<>
bool loadJson<MZ::System>(const QString &filename, MZ::System &object)
{
	glz::error_ctx err = glz::read_file_json(object, filename.toUtf8().data(), std::string{});
	return showParsingError(err, filename);
}*/


bool saveArray(const QString &filename, size_t count, std::function<glz::error_ctx(size_t, std::string &)> func)
{
	QFile json_file(filename);
	if (!json_file.open(QFile::WriteOnly))
		return false;

	json_file.write("[");

	std::string buffer;
	glz::error_ctx err;
	bool first = true;

	for (size_t i = 0; i < count; i++)
	{
		json_file.write(first ? "\n" : ",\n");

		err = func(i, buffer);
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
bool saveJson<Item>(const QString &filename, std::vector<std::optional<Item>> &vector)
{
	return saveArray(filename, vector.size(),
		[&vector](size_t i, std::string &buffer) -> glz::error_ctx
			{ return glz::write_json(vector.at(i), buffer); });
}

template<>
bool saveJson<Weapon>(const QString &filename, std::vector<std::optional<Weapon>> &vector)
{
	return saveArray(filename, vector.size(),
		[&vector](size_t i, std::string &buffer) -> glz::error_ctx
			{ return glz::write_json(vector.at(i), buffer); });
}

template<>
bool saveJson<Event>(const QString &filename, std::vector<std::optional<Event>> &vector)
{
	return saveArray(filename, vector.size(),
		[&vector](size_t i, std::string &buffer) -> glz::error_ctx
			{ return glz::write_json(vector.at(i), buffer); });
}

template<>
bool saveJson<Skill>(const QString &filename, std::vector<std::optional<Skill>> &vector)
{
	return saveArray(filename, vector.size(),
		[&vector](size_t i, std::string &buffer) -> glz::error_ctx
			{ return glz::write_json(vector.at(i), buffer); });
}

template<>
bool saveJson<State>(const QString &filename, std::vector<std::optional<State>> &vector)
{
	return saveArray(filename, vector.size(),
		[&vector](size_t i, std::string &buffer) -> glz::error_ctx
			{ return glz::write_json(vector.at(i), buffer); });
}

template<>
bool saveJson<MapInfo>(const QString &filename, std::vector<std::optional<MapInfo>> &vector)
{
	return saveArray(filename, vector.size(),
		[&vector](size_t i, std::string &buffer) -> glz::error_ctx
			{ return glz::write_json(vector.at(i), buffer); });
}

void printParsingError(const std::string &message, const QString &filename, int location)
{
	// TODO: combine this and showParsingError
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

