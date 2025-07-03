#include "map_event_pages_model.hpp"

void MapEventPagesModel::setPages(std::vector<Page> *pages)
{
	beginResetModel();
	this->pages = pages;
	endResetModel();
}

int MapEventPagesModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return pages->size();
}

int MapEventPagesModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return Page::Type::COUNT;
}

QVariant MapEventPagesModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::EditRole)
		return QVariant();

	Page *page = &pages->at(index.row());
	Page::Type type = Page::Type(index.column());

	switch (type)
	{
		case Page::COND_ACTOR_ID: return page->conditions.actorId;
		case Page::COND_ACTOR_VALID: return page->conditions.actorValid;
		case Page::COND_ITEM_ID: return page->conditions.itemId;
		case Page::COND_ITEM_VALID: return page->conditions.itemValid;
		case Page::COND_SELF_SWITCH_CHAR: return page->conditions.selfSwitchCh[0].toLatin1() - 65;
		case Page::COND_SELF_SWITCH_VALID: return page->conditions.selfSwitchValid;
		case Page::COND_SWITCH_1_ID: return page->conditions.switch1Id;
		case Page::COND_SWITCH_1_VALID: return page->conditions.switch1Valid;
		case Page::COND_SWITCH_2_ID: return page->conditions.switch2Id;
		case Page::COND_SWITCH_2_VALID: return page->conditions.switch2Valid;
		case Page::COND_VARIABLE_ID: return page->conditions.variableId;
		case Page::COND_VARIABLE_VALID: return page->conditions.variableValid;
		case Page::COND_VARIABLE_VALUE: return page->conditions.variableValue;
		case Page::DIRECTION_FIX: return page->directionFix;
		case Page::MOVE_FREQ: return page->moveFrequency - 1;
		case Page::MOVE_SPEED: return page->moveSpeed - 1;
		case Page::MOVE_TYPE: return page->moveType;
		case Page::PRIORITY_TYPE: return page->priorityType;
		case Page::STEP_ANIME: return page->stepAnime;
		case Page::THROUGH:return page->through;
		case Page::TRIGGER: return page->trigger;
		case Page::WALK_ANIME: return page->walkAnime;
		default: return QVariant();
	}
}

bool MapEventPagesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;

	if (role != Qt::EditRole)
		return false;

	Page *page = &pages->at(index.row());
	Page::Type type = Page::Type(index.column());

	switch (type)
	{
		case Page::COND_ACTOR_ID: page->conditions.actorId = value.toInt(); break;
		case Page::COND_ACTOR_VALID: page->conditions.actorValid = value.toBool(); break;
		case Page::COND_ITEM_ID: page->conditions.itemId = value.toInt(); break;
		case Page::COND_ITEM_VALID: page->conditions.itemValid = value.toBool(); break;
		case Page::COND_SELF_SWITCH_CHAR: page->conditions.selfSwitchCh = QChar(value.toInt() + 65); break;
		case Page::COND_SELF_SWITCH_VALID: page->conditions.selfSwitchValid = value.toBool(); break;
		case Page::COND_SWITCH_1_ID: page->conditions.switch1Id = value.toInt(); break;
		case Page::COND_SWITCH_1_VALID: page->conditions.switch1Valid = value.toBool(); break;
		case Page::COND_SWITCH_2_ID: page->conditions.switch2Id = value.toInt(); break;
		case Page::COND_SWITCH_2_VALID: page->conditions.switch2Valid = value.toBool(); break;
		case Page::COND_VARIABLE_ID: page->conditions.variableId = value.toInt(); break;
		case Page::COND_VARIABLE_VALID: page->conditions.variableValid = value.toBool(); break;
		case Page::COND_VARIABLE_VALUE: page->conditions.variableValue = value.toInt(); break;
		case Page::DIRECTION_FIX: page->directionFix = value.toBool(); break;
		case Page::MOVE_FREQ: page->moveFrequency = value.toInt() + 1; break;
		case Page::MOVE_SPEED: page->moveSpeed = value.toInt() + 1; break;
		case Page::MOVE_TYPE: page->moveType = value.toInt(); break;
		case Page::PRIORITY_TYPE: page->priorityType = value.toInt(); break;
		case Page::STEP_ANIME: page->stepAnime = value.toBool(); break;
		case Page::THROUGH: page->through = value.toBool(); break;
		case Page::TRIGGER: page->trigger = value.toInt(); break;
		case Page::WALK_ANIME: page->walkAnime = value.toBool(); break;
		default: return false;
	}

	return true;
}
