#pragma once
#include "event.hpp"
#include <optional>
#include <vector>
#include <string>
#include <map>

struct Transport
{
	Sound bgm;
	int characterIndex;
	std::string characterName;
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
	std::string actionFailure;
	std::string actorDamage;
	std::string actorDrain;
	std::string actorGain;
	std::string actorLoss;
	std::string actorNoDamage;
	std::string actorNoHit;
	std::string actorRecovery;
	std::string alwaysDash;
	std::string bgmVolume;
	std::string bgsVolume;
	std::string buffAdd;
	std::string buffRemove;
	std::string commandRemember;
	std::string counterAttack;
	std::string criticalToActor;
	std::string criticalToEnemy;
	std::string debuffAdd;
	std::string defeat;
	std::string emerge;
	std::string enemyDamage;
	std::string enemyDrain;
	std::string enemyGain;
	std::string enemyLoss;
	std::string enemyNoDamage;
	std::string enemyNoHit;
	std::string enemyRecovery;
	std::string escapeFailure;
	std::string escapeStart;
	std::string evasion;
	std::string expNext;
	std::string expTotal;
	std::string file;
	std::string levelUp;
	std::string loadMessage;
	std::string magicEvasion;
	std::string magicReflection;
	std::string meVolume;
	std::string obtainExp;
	std::string obtainGold;
	std::string obtainItem;
	std::string obtainSkill;
	std::string partyName;
	std::string possession;
	std::string preemptive;
	std::string saveMessage;
	std::string seVolume;
	std::string substitute;
	std::string surprise;
	std::string useItem;
	std::string victory;
};*/

struct Terms
{
	std::vector<std::optional<std::string>> basic;
	std::vector<std::optional<std::string>> commands;
	std::vector<std::optional<std::string>> params;
	std::map<std::string, std::string> messages;
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
	std::vector<std::string> armorTypes;
	std::vector<std::optional<AttackMotion>> attackMotions;
	Sound battleBgm;
	std::string battleback1Name;
	std::string battleback2Name;
	int battlerHue;
	std::string battlerName;
	Transport boat;
	std::string currencyUnit;
	Sound defeatMe;
	int editMapId;
	std::vector<std::string> elements;
	std::vector<std::string> equipTypes;
	std::string gameTitle;
	Sound gameoverMe;
	std::string locale;
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
	std::vector<std::string> skillTypes;
	std::vector<Sound> sounds;
	int startMapId;
	int startX;
	int startY;
	std::vector<std::string> switches;
	Terms terms;
	std::vector<TestBattler> testBattlers;
	int testTroopId;
	std::string title1Name;
	std::string title2Name;
	Sound titleBgm;
	std::vector<std::string> variables;
	int versionId;
	Sound victoryMe;
	std::vector<std::string> weaponTypes;
	std::vector<int> windowTone;
	bool hasEncryptedImages;
	bool hasEncryptedAudio;
	std::string encryptionKey;
};

