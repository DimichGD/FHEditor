#pragma once
#include <QString>

struct Effect
{
	enum Type
	{
		RECOVER_HP = 11, RECOVER_MP, GAIN_TP,
		ADD_STATE = 21, REMOVE_STATE,
		ADD_BUFF = 31, ADD_DEBUFF, REMOVE_BUFF, REMOVE_DEBUFF,
		SPECIAL = 41, GROW, LEARN_SKILL, COMMON_EVENT,
	};

	int code = Type::RECOVER_HP;
	int dataId = 0;
	float value1 = 1.0f;
	float value2 = 0.0f;
};

QString effectType(const Effect *effect);
QString effectValue(const Effect *effect);
