#include "effect.hpp"
#include "database.hpp"

QString makeRecoverHPString(int value1, int value2)
{
	QString result;
	if (value1)
		result += QString("%1%").arg(value1);

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
	return QString("BuffID %1 %2 turns").arg(buffId).arg(value1);
}

QString makeRemoveBuffString(int buffId)
{
	return QString("BuffID %1").arg(buffId);
}

QString makeSpecialEffectString(int buffId)
{
	return QString("SpecialEffectID %1").arg(buffId);
}

QString makeGrowString(int attribId, int value1)
{
	return QString("AttribID %1 + %2").arg(attribId).arg(value1);
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

QStringList effectToStringList(Effect *effect)
{
	QStringList result;

	switch (effect->code)
	{
		case Effect::RECOVER_HP:
			result.append("Recover HP");
			result.append(makeRecoverHPString(int(effect->value1 * 100), effect->value2));
			break;

		case Effect::RECOVER_MP:
			result.append("Recover MP");
			result.append(makeRecoverHPString(int(effect->value1 * 100), effect->value2));
			break;

		case Effect::GAIN_TP:
			result.append("Gain TP");
			result.append(QString::number(int(effect->value1)));
			break;

		case Effect::ADD_STATE:
			result.append("Add State");
			result.append(makeStateString(effect->dataId, int(effect->value1 * 100)));
			break;

		case Effect::REMOVE_STATE:
			result.append("Remove State");
			result.append(makeStateString(effect->dataId, int(effect->value1 * 100)));
			break;

		case Effect::ADD_BUFF:
			result.append("Add Buff");
			result.append(makeAddBuffString(effect->dataId, effect->value1));
			break;

		case Effect::ADD_DEBUFF:
			result.append("Add Debuff");
			result.append(makeAddBuffString(effect->dataId, effect->value1));
			break;

		case Effect::REMOVE_BUFF:
			result.append("Remove Buff");
			result.append(makeRemoveBuffString(effect->dataId));
			break;

		case Effect::REMOVE_DEBUFF:
			result.append("Remove Debuff");
			result.append(makeRemoveBuffString(effect->dataId));
			break;

		case Effect::SPECIAL:
			result.append("Special Effect");
			result.append(makeSpecialEffectString(effect->dataId));
			break;

		case Effect::GROW:
			result.append("Grow");
			result.append(makeGrowString(effect->dataId, effect->value1));
			break;

		case Effect::LEARN_SKILL:
			result.append("Learn Skill");
			result.append(makeSkillString(effect->dataId));
			break;

		case Effect::COMMON_EVENT:
			result.append("Common Event");
			result.append(makeCommonEventString(effect->dataId));
			break;

		default:
			result.append(QString::number(effect->code));
			result.append(QString::number(effect->dataId));
			break;
	}

	return result;
}
