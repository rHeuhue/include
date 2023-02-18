

new const WAR3FT_BLOCK_ITEMS_FILE[] = "war3ft/disable/block_items.ini"

// Секции файла настроек block_items.ini
enum
{
	SECTION_NONE = 0,
	SECTION_BLOCK_ITEMS
}

#define BLOCK_ITEM_NONE	-1
#define	BLOCK_ITEM_ANKH ITEM_ANKH										//Ankh of Reincarnation
#define	BLOCK_ITEM_BOOTS ITEM_BOOTS										//Boots of Speed
#define	BLOCK_ITEM_CLAWS ITEM_CLAWS										//Claws of Attack
#define	BLOCK_ITEM_CLOAK ITEM_CLOAK										//Cloak of Shadows
#define	BLOCK_ITEM_MASK ITEM_MASK										//Mask of Death
#define	BLOCK_ITEM_NECKLACE ITEM_NECKLACE								//Necklace of Immunity
#define	BLOCK_ITEM_FROST ITEM_FROST										//Orb of Frost
#define	BLOCK_ITEM_HEALTH ITEM_HEALTH									//Periapt of Health
#define	BLOCK_ITEM_TOME ITEM_TOME										//Tome of Experience
#define	BLOCK_ITEM_SCROLL ITEM_SCROLL									//Scroll of Respawning
#define	BLOCK_ITEM_PROTECTANT ITEM_PROTECTANT							//Mole Protectant
#define	BLOCK_ITEM_HELM ITEM_HELM										//Helm of Excellence
#define	BLOCK_ITEM_AMULET ITEM_AMULET									//Amulet of the Cat
#define	BLOCK_ITEM_SOCK ITEM_SOCK										//Sock of the Feather
#define	BLOCK_ITEM_GLOVES ITEM_GLOVES									//Flaming Gloves of Warmth
#define	BLOCK_ITEM_RING ITEM_RING										//Ring of Regeneration + 1
#define	BLOCK_ITEM_CHAMELEON ITEM_CHAMELEON								//Chameleon
#define	BLOCK_ITEM_MOLE ITEM_MOLE										//Mole
#define	BLOCK_ITEM_INTELLECT ITEM_INTELLECT								//Intellect
#define	BLOCK_ITEM_GRENADE_PROTECTION ITEM_GRENADE_PROTECTION			// Grenade Protection
#define	BLOCK_ITEM_MIRROR_SHIELD ITEM_MIRROR_SHIELD						//Mirror Shield
#define	BLOCK_ITEM_ESP ITEM_ESP											//ESP
#define	BLOCK_ITEM_FROST_ARMOR ITEM_FROST_ARMOR							//Frost Armor
#define	BLOCK_ITEM_DEATH_TOUCH ITEM_DEATH_TOUCH							//Death's Touch
#define	BLOCK_ITEM_HEALTH_POTION ITEM_HEALTH_POTION						//Health Potion
#define	BLOCK_ITEM_ULTIMATE_TIMER_DIVIDER ITEM_ULTIMATE_TIMER_DIVIDER	//Ultimate Timer Divider
#define	BLOCK_ITEM_STEEL_SKIN ITEM_STEEL_SKIN							//Steel Skin
#define	BLOCK_ITEM_DEVOURER_LIGHT ITEM_DEVOURER_LIGHT
#define	BLOCK_ITEM_ICE_BLOCK ITEM_ICE_BLOCK
#define	BLOCK_ITEM_THIEF ITEM_THIEF
#define	BLOCK_ITEM_MIRROR_ULTIMATE ITEM_MIRROR_ULTIMATE
#define	BLOCK_ITEM_DEATHCOIL ITEM_DEATHCOIL
#define	BLOCK_ITEM_IMPALE ITEM_IMPALE
#define	BLOCK_ITEM_SLEEP ITEM_SLEEP
#define	BLOCK_ITEM_BOOK_DEAD ITEM_BOOK_DEAD
#define	BLOCK_ITEM_TRANQUILITY ITEM_TRANQUILITY

new TravTrie:arrTrieBlockItemsMap;