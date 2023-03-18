//#include <common.h>
#include "../../../include/common.h"
#include "data.c"

int hasRandom = 0;
int currL = 0;
char prevGameState = 0;
char currLvl = 0x0a;
char prevHW = 0x0a;
int seed = 0;
int shownMenu = 0;
int showMenu = 0;
int doGems = 0;
int menuPage = 0;

unsigned short boxTop = 0x10;
unsigned short boxRight = 0x01f0;
unsigned short boxLeft = 0x10;
unsigned short boxBottom = 0xdd;

//all text values are based off the text size
int textSpacing = 24;
int textSize = 4000;
int textTop = 32;
int lineSpacing = 20;
int letterWidth = 26;
int screenLetterWidth = 22;

int textSpacingB = 15;
int textSizeB = 5500;
int textTopB = 54;
int lineSpacingB = 16;
int subTextX = 100;
int addTextX = 280;

int *current_gemStack;

void DrawTextToScreen(char*, struct CapitalTextInfo*, struct LowercaseTextInfo*, int, int);
int getTextX(int);
int getIntLen(int);
void drawRandoMenu();
void randomizeGems();
void drawCredits();

int frames = 0;

void assignPortals() {
	
	if(currentLevel == 0x0a){
		currL = 0;
		prevHW = 0x0b; //this gets rounded down to the nearest 10 on game over and end of credits
		toastyMouthVortex = 0x01; //we got the vortex requirement
		toastyMouthDragon = 0; //we don't need no dragon requirement
		aBallReq = 0x0001; //balloonist requirment is only 1
	}else if(currentLevel == 0x14){
		currL = 5;
		prevHW = 0x15;
		pBallReq = 0x0001;
	}else if(currentLevel == 0x1e){
		currL = 10;
		prevHW = 0x1e;
		mBallReq = 0x0001;
	}else if(currentLevel == 0x28){
		currL = 15;
		prevHW = 0x29;
		bBallReq = 0x0001;
	}else if(currentLevel == 0x32){
		currL = 20;
		prevHW = 0x33;
		dBallReq = 0x0001;
	}else if(currentLevel == 0x3c){
		currL = 25;
		prevHW = 0x3d;
		thMouth = 0x01;
		ggMouth = 0x01;

		glMouthGems = 0x0001;
		glMouthDragons = 0x0001;
		glMouthEggs = 0x0001;
	}else{
		currL = 30;
		
		for(int i = 0; i < 29; i++){
			if(newPortalLevels[i] == currentLevel){
				currLvl = currentPortalLevels[i]; //this stores the level id you SHOULD be in
				break;
			}
		}
		
	}
	
	if(currL != 30){
		for(int i = 0; i < 5; i++){
			if(currL == 25 && i == 4){
				break;
			}
			*portalLevelPointers[currL + i] = newPortalLevels[currL + i]; //assign portals
		}
	}
	
}

void Do_GameOver_Hook(){
	currentLevel = prevHW;
	exitPortalP = prevHW;
	goto *(int *)&gopntr;
}

void Do_Tick(){
	
	if(gameState == 1 && prevGameState != gameState){
		
		flyinVar = 0x8006ca3c; //always do a fly-in
	}
	
	if(gameState == 15 && prevGameState != gameState){
		
		if(currentLevel == 0x3f){
			endCreditsGGLevelId = prevHW;
		}
		if(currentLevel == 0x40){
			endCreditsGLLevelId = prevHW;
		}
		
	}
	
	if(gameState == 0 && prevGameState != gameState){
		if(hasRandom == 0){
			randomiseLevels(seed);
			hasRandom = 1;
		}
		
		assignPortals();
		
	}else if(gameState == 7){
		if(currentLevel == 0x0f || 
		currentLevel == 0x19 || 
		currentLevel == 0x23 || 
		currentLevel == 0x2d || 
		currentLevel == 0x37){
			if(flyMenuOption == 3 && currentButton == 64){ //try again? yes
				exitPortalP = currentLevel;
			}else if(flyMenuOption == 2 && currentButton == 64){ //try again? no
				for(int i = 0; i < 29; i++){ 
					if(newPortalLevels[i] == currentLevel){
						exitPortalP = currentPortalLevels[i];
						break;
					}
				}
			}
			
		}
	}else if(gameState == 2){
		if(currentLevel == 0x0a || 
		currentLevel == 0x14 || 
		currentLevel == 0x1e || 
		currentLevel == 0x28 || 
		currentLevel == 0x32 || 
		currentLevel == 0x3c){
			return;
		}
		
		if(pauseMenuOption == 3 && currentButton == 64){
			exitPortalP = currLvl; //exit level
		}else if((pauseMenuOption == 0 && currentButton == 64) || currentButton == 2048){
			exitPortalP = currentLevel; //unpause
		}
	}
	
	if(gameState == 0){
		
		if(shownMenu == 0){
			showMenu = 1;
			shownMenu = 1;
		}
		
		if(showMenu == 1){
			
			if(menuPage == 0){
				if(heldButton == 0xffdf){ //right
					seed += 1;
				}else if(heldButton == 0xff7f){ //left
					seed -= 1;
				}else if(heldButton == 0xf7ff){ //r1
					seed += 100;
				}else if(heldButton == 0xfbff){ //l1
					seed -= 100;
				}else if(heldButton == 0xfdff){ //r2
					seed += 1000;
				}else if(heldButton == 0xfeff){ //l2
					seed -= 1000;
				}else if(heldButton == 0xbfff){ //X
					
					randomiseLevels(seed);
					hasRandom = 1;
					
					assignPortals();
					
					showMenu = 0;
					
				}else if(heldButton == 0xdfff){ //O
					
					seed = sysClock;
					
				}else if(heldButton == 0xf0ff){ //l1+r1+l2+r2
					if(doGems == 1){
						doGems = 0;
					}else{
						doGems = 1;
					}
					
					
				}
			}
			
			if(heldButton == 0xffbf && menuPage == 0){ //down
				menuPage = 1;
			}else if(heldButton == 0xffef && menuPage == 1){ //up
				menuPage = 0;
			}
			
			if(seed < 0){
				seed = 0;
			}
			
			if(menuPage == 1){
				drawCredits();
			}else{
				drawRandoMenu();
			}
			
			buttonVar13 = 0; //stops spyro from moving - still allows animations
		}else{
			if(heldButton == 0xfffe){
				showMenu = 1;
				heldButton = 0xffff;
			}
		}
		
		if(doGems == 1 && frames % 5 == 0 ){
			randomizeGems();
		}
		
	}
	
	if(vortexChange == 0x8000 &&
		gameState == 0 &&
		onGround == 0x00){
		
		for(int i = 0; i < 29; i++){
			if(currentPortalLevels[i] == currentLevel){
				if(vortexId == vortexIds[i]){
					exitPortalP = currLvl;
					break;
					
				}
				break;
			}
		}
		
	}
	
	prevGameState = gameState;
	frames++;
	if(frames >= 100){
		frames = 0;
	}
}

void randomizeGems(){
	
	current_gemStack = &gem_stack;
	for(int g = 0; g < 110; g++){
		char actualValue = *(char *)(*current_gemStack + 0x36);
		if(actualValue == 0x53 || actualValue == 0x54 || actualValue == 0x55 || actualValue == 0x56 || actualValue == 0x57){
			*(char *)(*current_gemStack + 0x4f) = (int)rand(seed) % 254; //pretty colors!
		}
		current_gemStack = current_gemStack + 1;
	}
	
}

void drawRandoMenu(){
	
	DrawBox(boxTop, boxRight, boxLeft, boxBottom);
	
	struct CapitalTextInfo titleC;
	titleC.x = getTextX(5);
	titleC.y = textTop;
	titleC.size = textSize;
	
	struct LowercaseTextInfo titleL;
	titleL.spacing = textSpacing;
	titleL.yOffset = 0;
	titleL.size = textSize;
	
	DrawTextToScreen((char *)"LEVEL", &titleC, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo titleRC;
	titleRC.x = getTextX(10);
	titleRC.y = textTop + (lineSpacing * 1);
	titleRC.size = textSize;
	
	DrawTextToScreen((char *)"RANDOMIZER", &titleRC, &titleL, textSpacing, 2);
	
	int seedLen = getIntLen(seed) + 5;
	
	struct CapitalTextInfo seedC;
	seedC.x = getTextX(seedLen);
	seedC.y = textTop + (lineSpacing * 3);
	seedC.size = textSize;
	
	char * seedStr = SPrintF(seedLen, (char *)"SEED %d", (int *)seed, 0);
	DrawTextToScreen(seedStr, &seedC, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo sC0;
	sC0.x = subTextX;
	sC0.y = textTopB + (lineSpacingB * 4);
	sC0.size = textSizeB;
	
	struct LowercaseTextInfo sL0;
	sL0.spacing = textSpacingB;
	sL0.yOffset = 0;
	sL0.size = textSizeB;
	
	DrawTextToScreen((char *)"SUBTRACT", &sC0, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo sC1;
	sC1.x = subTextX;
	sC1.y = textTopB + (lineSpacingB * 5);
	sC1.size = textSizeB;
	
	DrawTextToScreen((char *)"LEFT 1", &sC1, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo sC2;
	sC2.x = subTextX;
	sC2.y = textTopB + (lineSpacingB * 6);
	sC2.size = textSizeB;
	
	DrawTextToScreen((char *)"L1    100", &sC2, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo sC3;
	sC3.x = subTextX;
	sC3.y = textTopB + (lineSpacingB * 7);
	sC3.size = textSizeB;
	
	DrawTextToScreen((char *)"L2    1000", &sC3, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo cC0;
	cC0.x = addTextX;
	cC0.y = textTopB + (lineSpacingB * 4);
	cC0.size = textSizeB;
	
	DrawTextToScreen((char *)"ADD", &cC0, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo cC1;
	cC1.x = addTextX;
	cC1.y = textTopB + (lineSpacingB * 5);
	cC1.size = textSizeB;
	
	DrawTextToScreen((char *)"RIGHT 1", &cC1, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo cC2;
	cC2.x = addTextX;
	cC2.y = textTopB + (lineSpacingB * 6);
	cC2.size = textSizeB;
	
	DrawTextToScreen((char *)"R1     100", &cC2, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo cC3;
	cC3.x = addTextX;
	cC3.y = textTopB + (lineSpacingB * 7);
	cC3.size = textSizeB;
	
	DrawTextToScreen((char *)"R2     1000", &cC3, &sL0, textSpacingB, 2);
	
	struct CapitalTextInfo randoC;
	randoC.x = getTextX(14);
	randoC.y = textTop + (lineSpacing * 8);
	randoC.size = textSize;
	
	DrawTextToScreen((char *)"O TO RANDOMIZE", &randoC, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo conC;
	conC.x = getTextX(12);
	conC.y = textTop + (lineSpacing * 9);
	conC.size = textSize;
	
	DrawTextToScreen((char *)"X TO CONFIRM", &conC, &titleL, textSpacing, 2);
	
	if(doGems == 1){
		struct CapitalTextInfo conC;
		conC.x = 30;
		conC.y = textTop;
		conC.size = 6000;
		
		struct LowercaseTextInfo conL;
		conL.spacing = 12;
		conL.yOffset = 0;
		conL.size = 6000;
		
		DrawTextToScreen((char *)"COLOR GEMS", &conC, &conL, 12, 2);
	}
	
}

void drawCredits(){
	
	DrawBox(boxTop, boxRight, boxLeft, boxBottom);
	
	struct CapitalTextInfo titleC;
	titleC.x = getTextX(14);
	titleC.y = textTop;
	titleC.size = textSize;
	
	struct LowercaseTextInfo titleL;
	titleL.spacing = textSpacing;
	titleL.yOffset = 0;
	titleL.size = textSize;
	
	DrawTextToScreen((char *)"MOD CREATED BY", &titleC, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo name1C;
	name1C.x = getTextX(7);
	name1C.y = textTop  + (lineSpacing * 1);
	name1C.size = textSize;
	
	DrawTextToScreen((char *)"HELFRIX", &name1C, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo title2C;
	title2C.x = getTextX(16);
	title2C.y = textTop  + (lineSpacing * 3);
	title2C.size = textSize;
	
	DrawTextToScreen((char *)"SPECIAL THANKS TO", &title2C, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo name2C;
	name2C.x = getTextX(7);
	name2C.y = textTop + (lineSpacing * 4);
	name2C.size = textSize;
	
	DrawTextToScreen((char *)"ALDEEZY", &name2C, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo name3C;
	name3C.x = getTextX(7);
	name3C.y = textTop + (lineSpacing * 5);
	name3C.size = textSize;
	
	DrawTextToScreen((char *)"ODDKARA", &name3C, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo name4C;
	name4C.x = getTextX(8);
	name4C.y = textTop + (lineSpacing * 6);
	name4C.size = textSize;
	
	DrawTextToScreen((char *)"COMPOSER", &name4C, &titleL, textSpacing, 2);
	
	struct CapitalTextInfo name5C;
	name5C.x = getTextX(6);
	name5C.y = textTop + (lineSpacing * 7);
	name5C.size = textSize;
	
	DrawTextToScreen((char *)"REDHOT", &name5C, &titleL, textSpacing, 2);
	
}

int getIntLen(int x){
	if (x >= 1000000000) return 10;
	if (x >= 100000000)  return 9;
	if (x >= 10000000)   return 8;
	if (x >= 1000000)    return 7;
	if (x >= 100000)     return 6;
	if (x >= 10000)      return 5;
	if (x >= 1000)       return 4;
	if (x >= 100)        return 3;
	if (x >= 10)         return 2;
	return 1;
}

int getTextX(int len){
	
	int i = 0;
	
	if(len % 2 == 1){
		i = letterWidth / 2;
	}
	
	return ((screenLetterWidth*letterWidth) / 2) - ((len*letterWidth)/2) - i;
}

void DrawTextToScreen(char* p1, struct CapitalTextInfo* p2, struct LowercaseTextInfo* p3, int p4, int p5){
	DrawText(p1, p2, p3, p4, p5);
	
	memset(0x8006fcf4, 0, 0x900);
	ptrTextUnk = 0;
	CopyHudToShaded();
	DrawShadedMobys();
}
