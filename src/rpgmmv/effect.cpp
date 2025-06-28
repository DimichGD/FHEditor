#include "effect.hpp"
#include "database.hpp"
#include <QStringList>

static QStringList attribs {
	"Max HP",
	"Max MP",
	"Attack",
	"Defence",
	"M. Attack",
	"M. Defense",
	"Agility",
	"Luck",
};

QString makeRecoverHPString(int value1, int value2)
{
	QString result;
	if (value1)
		result += QString::number(value1);

	if (value2 != 0)
	{
		QChar sign = (value2 < 0) ? '-' : '+';
		result += QString(" %1 %2").arg(sign).arg(value2);
	}

	return result.trimmed();
}

QString makeStateString(int stateId, int value1)
{
	State *state = Accessor<State>().value(stateId);
	QString stateName = state ? state->name : "?";

	return QString("%1 %2%").arg(stateName).arg(value1);
}

QString makeAddBuffString(int buffId, int value1)
{
	return QString("%1 %2 turns").arg(attribs.at(buffId)).arg(value1);
}

QString makeRemoveBuffString(int buffId)
{
	return attribs.at(buffId);
}

QString makeSpecialEffectString(int buffId)
{
	return QString("SpecialEffectID %1").arg(buffId);
}

QString makeGrowString(int attribId, int value1)
{
	return QString("%1 + %2").arg(attribs.at(attribId)).arg(value1);
}

QString makeSkillString(int skillId)
{
	Skill *skill = Accessor<Skill>().value(skillId);
	return skill ? skill->name : "?";
}

QString makeCommonEventString(int eventId)
{
	Event *event = Accessor<Event>().value(eventId);
	return event ? event->name : "?";
}

QString effectType(const Effect *effect)
{
	switch (effect->code)
	{
		case Effect::RECOVER_HP: return "Recover HP";
		case Effect::RECOVER_MP: return "Recover MP";
		case Effect::GAIN_TP: return "Gain TP";
		case Effect::ADD_STATE: return "Add State";
		case Effect::REMOVE_STATE: return "Remove State";
		case Effect::ADD_BUFF: return "Add Buff";
		case Effect::ADD_DEBUFF: return "Add Debuff";
		case Effect::REMOVE_BUFF: return "Remove Buff";
		case Effect::REMOVE_DEBUFF: return "Remove Debuff";
		case Effect::SPECIAL: return "Special Effect";
		case Effect::GROW: return "Grow";
		case Effect::LEARN_SKILL: return "Learn Skill";
		case Effect::COMMON_EVENT: return "Common Event";
		default: return QString::number(effect->code);
	}
}

QString effectValue(const Effect *effect)
{
	switch (effect->code)
	{
		case Effect::RECOVER_HP: return makeRecoverHPString(int(effect->value1 * 100), effect->value2);
		case Effect::RECOVER_MP: return makeRecoverHPString(int(effect->value1 * 100), effect->value2);
		case Effect::GAIN_TP: return QString::number(int(effect->value1));
		case Effect::ADD_STATE: return makeStateString(effect->dataId, int(effect->value1 * 100));
		case Effect::REMOVE_STATE: return makeStateString(effect->dataId, int(effect->value1 * 100));
		case Effect::ADD_BUFF: return makeAddBuffString(effect->dataId, effect->value1);
		case Effect::ADD_DEBUFF: return makeAddBuffString(effect->dataId, effect->value1);
		case Effect::REMOVE_BUFF: return makeRemoveBuffString(effect->dataId);
		case Effect::REMOVE_DEBUFF: return makeRemoveBuffString(effect->dataId);
		case Effect::SPECIAL: return makeSpecialEffectString(effect->dataId);
		case Effect::GROW: return makeGrowString(effect->dataId, effect->value1);
		case Effect::LEARN_SKILL: return makeSkillString(effect->dataId);
		case Effect::COMMON_EVENT: return makeCommonEventString(effect->dataId);
		default: return QString::number(effect->code);
	}
}
