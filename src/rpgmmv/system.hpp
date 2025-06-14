#pragma once
#include "sound.hpp"
#include <optional>
#include <vector>
#include <map>

struct Transport
{
	Sound bgm;
	int characterIndex;
	QString characterName;
	int startMapId;
	int startX;
	int startY;
};

struct AttackMotion
{
	int type;
	int weaponImageId;
};

/*struct Messages
{
	QString actionFailure;
	QString actorDamage;
	QString actorDrain;
	QString actorGain;
	QString actorLoss;
	QString actorNoDamage;
	QString actorNoHit;
	QString actorRecovery;
	QString alwaysDash;
	QString bgmVolume;
	QString bgsVolume;
	QString buffAdd;
	QString buffRemove;
	QString commandRemember;
	QString counterAttack;
	QString criticalToActor;
	QString criticalToEnemy;
	QString debuffAdd;
	QString defeat;
	QString emerge;
	QString enemyDamage;
	QString enemyDrain;
	QString enemyGain;
	QString enemyLoss;
	QString enemyNoDamage;
	QString enemyNoHit;
	QString enemyRecovery;
	QString escapeFailure;
	QString escapeStart;
	QString evasion;
	QString expNext;
	QString expTotal;
	QString file;
	QString levelUp;
	QString loadMessage;
	QString magicEvasion;
	QString magicReflection;
	QString meVolume;
	QString obtainExp;
	QString obtainGold;
	QString obtainItem;
	QString obtainSkill;
	QString partyName;
	QString possession;
	QString preemptive;
	QString saveMessage;
	QString seVolume;
	QString substitute;
	QString surprise;
	QString useItem;
	QString victory;
};*/

struct Terms
{
	std::vector<std::optional<QString>> basic;
	std::vector<std::optional<QString>> commands;
	std::vector<std::optional<QString>> params;
	std::map<std::string, std::string> messages; // FIXME: expected_brace error with QString
};

struct TestBattler
{
	int actorId;
	std::vector<std::optional<int>> equips;
	int level;
};

struct System
{
	Transport airship;
	std::vector<QString> armorTypes;
	std::vector<std::optional<AttackMotion>> attackMotions;
	Sound battleBgm;
	QString battleback1Name;
	QString battleback2Name;
	int battlerHue;
	QString battlerName;
	Transport boat;
	QString currencyUnit;
	Sound defeatMe;
	int editMapId;
	std::vector<QString> elements;
	std::vector<QString> equipTypes;
	QString gameTitle;
	Sound gameoverMe;
	QString locale;
	std::vector<int> magicSkills;
	std::vector<bool> menuCommands; // TODO: change to array?
	bool optDisplayTp;
	bool optDrawTitle;
	bool optExtraExp;
	bool optFloorDeath;
	bool optFollowers;
	bool optSideView;
	bool optSlipDeath;
	bool optTransparent;
	std::vector<int> partyMembers;
	Transport ship;
	std::vector<QString> skillTypes;
	std::vector<Sound> sounds;
	int startMapId;
	int startX;
	int startY;
	std::vector<QString> switches;
	Terms terms;
	std::vector<TestBattler> testBattlers;
	int testTroopId;
	QString title1Name;
	QString title2Name;
	Sound titleBgm;
	std::vector<QString> variables;
	int versionId;
	Sound victoryMe;
	std::vector<QString> weaponTypes;
	std::vector<int> windowTone;
	bool hasEncryptedImages;
	bool hasEncryptedAudio;
	QString encryptionKey;
};

