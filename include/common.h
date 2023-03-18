#ifndef COMMON_H
#define COMMON_H

void Do_Tick();

struct CapitalTextInfo{
    int x;
    int y;
    int size;
};

struct LowercaseTextInfo{
    int spacing;
    int yOffset;
    int size;
};

enum LEVEL_IDS {
  ARTISANS=0x0a,
  STONE_HILL=0x0b,
  DARK_HOLLOW=0x0c,
  TOWN_SQUARE=0x0d,
  TOASTY=0x0e,
  SUNNY_FLIGHT=0x0f,
  PEACE_KEEPERS=0x14,
  DRY_CANYON=0x15,
  CLIFF_TOWN=0x16,
  ICE_CAVERN=0x17,
  SHEMP=0x18,
  NIGHT_FLIGHT=0x19,
  MAGIC_CRAFTERS=0x1e,
  ALPINE_RIDGE=0x1f,
  HIGH_CAVES=0x20,
  WIZARD_PEAK=0x21,
  BLOWHARD=0x22,
  CRYSTAL_FLIGHT=0x23,
  BEAST_MAKERS=0x28,
  TERRACE_VILLAGE=0x29,
  MISTY_BOG=0x2a,
  TREE_TOPS=0x2b,
  METALHEAD=0x2c,
  WILD_FLIGHT=0x2d,
  DREAM_WEAVERS=0x32,
  DARK_PASSAGE=0x33,
  LOFTY_CASTLE=0x34,
  HAUNTED_TOWERS=0x35,
  JACQUES=0x36,
  ICY_FLIGHT=0x37,
  GNORC_GNEXUS=0x3c,
  GNORC_COVE=0x3d,
  TWILIGHT_HARBOR=0x3e,
  GNASTY_GNORC=0x3f,
  GNASTYS_LOOT=0x40
};

extern int gameState;
extern int isLoadingLevel;
extern int loadingLevelState;
extern int colectedGemValue;
extern int totalLives;
extern int sparxLevel;
extern int collectedDragons;
extern int collectedEggs;
extern int collectedOrbs;
extern int hasKey;
extern int currentSpyroxCord;
extern int currentSpyroyCord;
extern int currentSpyrozCord;
extern int currentSpyroRot;

extern int gem_stack;
extern int gemCount;
extern unsigned char collGemStack;

extern char exitPortalP;
extern char currentLevel;

extern int flyMenuOption;
extern int pauseMenuOption;

extern int currentButton;
extern unsigned short heldButton;
extern int buttonVar13;

extern unsigned int sysClock;

extern char toastyMouthVortex;
extern char toastyMouthDragon;
extern char thMouth;
extern char ggMouth;
extern short glMouthGems;
extern short glMouthDragons;
extern short glMouthEggs;

extern short endCreditsGGLevelId;
extern short endCreditsGLLevelId;

extern unsigned short vortexChange;
extern unsigned short vortexId;
extern char onGround;
extern int gopntr;
extern int flyinVar;

extern int gemPickup;

extern int aBallReqPnt;
extern unsigned short aBallReq;

extern int pBallReqPnt;
extern unsigned short pBallReq;

extern int mBallReqPnt;
extern unsigned short mBallReq;

extern int bBallReqPnt;
extern unsigned short bBallReq;

extern int dBallReqPnt;
extern unsigned short dBallReq;


extern void srand(int);
extern unsigned int rand();
extern void DrawBox(int, int, int, int);
extern void DrawText(char *, struct CapitalTextInfo *, struct LowercaseTextInfo *, int, int);
extern char * SPrintF(int, char *, int *, int);
extern void memset(int, int, short);
extern void CopyHudToShaded();
extern void DrawShadedMobys();
extern int ptrTextUnk;

extern int mainMenuState;

extern int hook_loc;


// artisans world
extern char shPortal;
extern char dhPortal;
extern char tsPortal;
extern char toaPortal;
extern char sfPortal;

// peace keepers
extern char dcPortal;
extern char ctPortal;
extern char icPortal;
extern char shePortal;
extern char nfPortal;

// magic crafters
extern char arPortal;
extern char hcPortal;
extern char wpPortal;
extern char bloPortal;
extern char cfPortal;

// beast makers
extern char tvPortal;
extern char mbPortal;
extern char ttPortal;
extern char metPortal;
extern char wfPortal;

// dream weavers
extern char dpPortal;
extern char lcPortal;
extern char htPortal;
extern char jacPortal;
extern char ifPortal;

// gnorc gnexus
extern char gcPortal;
extern char thPortal;
extern char ggPortal;
extern char glPortal;

#endif