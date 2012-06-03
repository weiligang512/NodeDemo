#ifndef __EEPROM_H__
#define __EEPROM_M__


/**************Define ISP/IAP/EEPROM command*************/
#ifndef CMD_IDLE
	#define CMD_IDLE		0	//Stand-By
#endif

#ifndef CMD_READ
	#define CMD_READ		1	//Byte-Read
#endif

#ifndef CMD_PROGRAM		
	#define CMD_PROGRAM		2	//Byte-Program
#endif

#ifndef CMD_ERASE
	#define CMD_ERASE		3	//Sector-Erase
#endif
/********************************************************/

/***************Enable ISP/IAP/EEPROM********************/
#define ENABLE_IAP			0x83	//System Clock < 12MHz
/********************************************************/

/***************Define Sector Address********************/
#define SECTOR1_STARTADDRESS	0x0000	//Sector1 start address
#define SECTOR1_ENDADDRESS		0x1ff	//Sector1 end address

#define SECTOR2_STARTADDRESS	0x0200	//Sector1 start address
#define SECTOR2_ENDADDRESS		0x3ff	//Sector1 end address

#define SECTORLEN				512		//Sector Length
/********************************************************/



void IAPEraseSector(uint16 addr);

bool IAPRead(uint16 addr, uint8 *buff, uint16 size);

bool IAPProgram(uint16 addr, uint8 *buff, uint16 size);

















#endif