//#include "../../../include/common.h"
#include "cd.h"

CdlCB callback;
CdlLOC loc;
int mode = 0xC8; //this translates to Double Transfer Speed (0x80) + ADPCM On (0x40) + and Subheader Filter On (0x08).
char initialised = 0;
char loading = 0;
int SectorsToRead = 3;
int SectorsRead = 0;

void read_cb(unsigned char status, unsigned char *result){
    CdReadCallback(callback); //for some reason this keeps the read_cb function from happening a second time
    //CdIntToPos(*(&musicSectors + 3), &loc); //takes the abslute sector numbers of the music from ram and converts them into the CdlLOC format
    //CdControlB(CdlReadS, (void *)&loc, 0); //Starts reading from the disk at the specified location
    //CdControlB(CdlSetmode, (char *)&mode, 0); //puts the Cd subsystem in the right mode to play music
    // CdControlB(CdlSetmode, (void*)&(const int){0xC8}, 0); //Potential alternative to creating the variable mode and pointing to it
	
	//SectorsRead++;
	if(SectorsRead == SectorsToRead){
		initialised = 1;
	}
}

//this is my solution to gettng it working in pcsx-redux - not needed on other emulators but does work regardless
void ReadCD(){
	int sec_add = SectorsRead * 1;
	int * addr_write = (int *)(((int)0x8000C000) + (SectorsRead * 0x800));
	callback = CdReadCallback(read_cb); //Defines read_cb as the function to run after CdRead is completed
	CdIntToPos(265759 + sec_add, &loc); //Converts the absolute sector number into the CdlLOC format
	CdControlB(CdlSeekL, (void *)&loc, 0);
	CdControlB(CdlSetloc, (void *)&loc, 0); //Uses CdSetloc (0x02) to prepare for CdRead
	CdRead(1, addr_write, 0x80); //Read n Sectors to the address 0x8000C000
	SectorsRead++;
}

void init(){
	if (loading == 0 && mainMenuState == 1){
		
        if(SectorsRead < SectorsToRead){
			ReadCD();
		}
		
    }
}

void Do_Tick_Hook(){
	if(!initialised){
        init(); //Begin the code loading process
	}
	else{
		
		//hook_loc = 0x0800330f;
		
        Do_Tick(); //Run the main Loop of the loaded code
	}
}