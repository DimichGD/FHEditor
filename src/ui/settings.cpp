#include "settings.hpp"
#include "json_qstring.hpp" // IWYU pragma: keep

#include <QFile>
#include <QDebug>

Settings *Settings::Get()
{
	static Settings settings;
	return &settings;
}

bool Settings::load()
{
	if (!QFile::exists("settings.json"))
		return false;

	glz::error_ctx err = glz::read_file_json(*this, "settings.json", std::string{});
	if (err)
	{
		qDebug() << QString::fromStdString(glz::format_error(err));
		return false;
	}

	return true;
}

bool Settings::save() // TODO: check behavior if file is read only
{
	glz::error_ctx err = glz::write_file_json<glz::opts{.prettify = true}>(*this, "settings.json", std::string{});
	if (err)
	{
		qDebug() << QString::fromStdString(glz::format_error(err));
		return false;
	}

	return true;
}
