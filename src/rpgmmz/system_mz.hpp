#pragma once
#include "system.hpp"

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

namespace MZ {

struct Advanced
{
	int gameId = 0;
	int screenWidth = 0;
	int screenHeight = 0;
	int uiAreaWidth = 0;
	int uiAreaHeight = 0;
	std::string numberFontFilename {};
	std::string fallbackFonts {};
	int fontSize = 0;
	std::string mainFontFilename {};
	int screenScale = 0;
	int windowOpacity = 0;
	int picturesUpperLimit = 0;
};

struct TitleCommandWindow
{
	int background;
	int offsetX;
	int offsetY;
};

struct Editor
{
	int messageWidth1;
	int messageWidth2;
	int jsonFormatLevel;
};

struct System
{
	Advanced advanced;
	Transport airship;
	std::vector<std::string> armorTypes;
	std::vector<std::optional<AttackMotion>> attackMotions;
	Sound battleBgm;
	std::string battleback1Name;
	std::string battleback2Name;
	int battlerHue;
	std::string battlerName;
	int battleSystem;
	Transport boat;
	std::string currencyUnit;
	Sound defeatMe;
	int editMapId;
	std::vector<std::string> elements;
	std::vector<std::string> equipTypes;
	std::string gameTitle;
	Sound gameoverMe;
	std::vector<bool> itemCategories; // TODO: change to array?
	std::string locale;
	std::vector<int> magicSkills;
	std::vector<bool> menuCommands; // TODO: change to array?
	bool optAutosave;
	bool optDisplayTp;
	bool optDrawTitle;
	bool optExtraExp;
	bool optFloorDeath;
	bool optFollowers;
	bool optKeyItemsNumber;
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
	TitleCommandWindow titleCommandWindow;
	std::vector<std::string> variables;
	int versionId;
	Sound victoryMe;
	std::vector<std::string> weaponTypes;
	std::vector<int> windowTone;
	bool optSplashScreen;
	bool optMessageSkip;
	int tileSize;
	Editor editor;
	int faceSize;
	int iconSize;
	/*bool hasEncryptedImages;
	bool hasEncryptedAudio;
	std::string encryptionKey;*/
};

}
