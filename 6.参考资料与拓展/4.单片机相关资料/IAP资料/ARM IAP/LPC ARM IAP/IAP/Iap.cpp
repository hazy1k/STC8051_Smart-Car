#include "LPC213XDEF.h"
#include "iap.h"


IAPObj::IAPObj(void){
  iap_intry = (IAP)IAP_LOCATION;
}

unsigned int IAPObj::SelSector(unsigned int sectorstart, unsigned int sectorend)
{
  command[0] = IAP_SELECTOR;
  command[1] = sectorstart;
  command[2] = sectorend;
  iap_intry(command, result);
  return result[0];
}

unsigned int IAPObj::UploadtoFlash(unsigned int addressflash, unsigned int addressram, unsigned int length)
{
  command[0] = IAP_RAMTOFLASH;
  command[1] = addressflash;
  command[2] = addressram;
  command[3] = length;//256/512/1024/4096
  command[4] = IAP_FCCLK;
  iap_intry(command, result);
  return result[0];
}


unsigned int IAPObj::WriteFlash(unsigned int addressflash, unsigned int addressram, unsigned int length)
{
unsigned int sectorstart, sectorend;
  sectorstart = GetSectorNumber(addressflash);
  sectorend = GetSectorNumber(addressflash + length - 1);
  SelSector(sectorstart, sectorend);
  if (result[0] == CMD_SUCCESS) {
    UploadtoFlash(addressflash, addressram, length);
  }
  return result[0];
}

unsigned int IAPObj::BlockWriteFlash(unsigned int addressflash, unsigned int addressblock, unsigned int size)
{
unsigned int sector, addresspos, addressend;
unsigned char str[256];
unsigned int i;
unsigned int err = 1;
unsigned char * ptr;
  addressend = addressflash | 0xff;
  if (addressflash + size > addressend) return err;//失败
  ptr = (unsigned char *)addressflash;
  for (i = 0; i < size; i ++) {
    if (*ptr != 0xff) return err;//失败
  }  
  sector = GetSectorNumber(addressflash);
  addresspos = addressflash & 0xffffff00;
  SelSector(sector, sector);
  if (result[0] == CMD_SUCCESS) {
    ptr = (unsigned char *)addresspos;
    for (i = 0; i < 256; i ++) {
	  str[i] = *ptr++;
    }  
    ptr = (unsigned char *)addressblock;
    for (i = addressflash & 0xff; i < addressflash + size; i ++) {
	  str[i] = *ptr++;//写入
    } 
	UploadtoFlash(sector, (unsigned int)&str, 256); 
  }
  return result[0];
}

unsigned int IAPObj::ReadBootLoaderID(void)
{
  command[0] = IAP_BOOTCODEID;
  iap_intry(command, result);
  return result[0];
}

unsigned int IAPObj::IapExec(void)
{
  command[0] = IAP_EXEC;
  iap_intry(command, result);
  return result[0];
}

unsigned int IAPObj::ReadPartID(void)
{
  command[0] = IAP_READPARTID;
  iap_intry(command, result);
/*---------------------------------------------
  LPC2131  0x0002ff01 196353
  LPC2132  0x0002ff11 196369
  LPC2134  0x0002ff12 196370
  LPC2136  0x0002ff23 196387
  LPC2138  0x0002ff25 196389
----------------------------------------------*/
  return result[0];
}

unsigned int IAPObj::EraseSector(unsigned int sectorstart, unsigned int sectorend)
{
  command[0] = IAP_ERASESECTOR;
  command[1] = sectorstart;
  command[2] = sectorend;
  command[3] = IAP_FCCLK;
  iap_intry(command, result);
  return result[0];
}

unsigned int IAPObj::EraseFlash(unsigned int addressstart, unsigned int addressend)
{
unsigned int sectorstart, sectorend;
  sectorstart = GetSectorNumber(addressstart);
  sectorend = GetSectorNumber(addressend);
  SelSector(sectorstart, sectorend);
  if (result[0] == CMD_SUCCESS) {
    EraseSector(sectorstart, sectorend);
  }
  return result[0];
}

unsigned int IAPObj::BlankCheck(unsigned int sectorstart, unsigned int sectorend)
{
  command[0] = IAP_BLANKCHK;
  command[1] = sectorstart;
  command[2] = sectorend;
  iap_intry(command, result);
  return result[0];
}

unsigned int IAPObj::CheckFlash(unsigned int addressstart, unsigned int addressend)
{
unsigned int sectorstart, sectorend;
  sectorstart = GetSectorNumber(addressstart);
  sectorend = GetSectorNumber(addressend);
  BlankCheck(sectorstart, sectorend);
  return result[0];
}

unsigned int IAPObj::CompareFlash(unsigned int addressstart, unsigned int addressend, unsigned int length)
{
  command[0] = IAP_COMPARE;
  command[1] = addressstart;
  command[2] = addressend;
  command[3] = length;//length % 4 == 0
  iap_intry(command, result);
  return result[0];
}

unsigned int IAPObj::GetSectorNumber(unsigned int address)
{
unsigned int sector;
  sector = address >> 12;//4KB
  if (sector >= 0x78) {//0x16~0x1A
    sector -= 0x62;//4KB
  }
  else if (sector > 8) {//0x08~0x15
    sector >>= 3;//1/8
	sector += 7;//32KB
  }
  else {//0x00~0x07
	sector = sector;//4KB
  }
  return sector;//返回0x08~0x15时Flash为32KB,其他为4KB 
}

unsigned int IAPObj::GetSectorSize(unsigned int address)
{
unsigned int sector, size;
  sector = GetSectorNumber(address);
  if ((sector >= 0x08) && (sector <= 0x15)) {
    size = 32 * 1024;
  }
  else {
    size = 4 * 1024;
  }
  return size;
}


unsigned int IAPObj::GetSectorTop(unsigned int address)
{
unsigned int sector, top;
  sector = GetSectorNumber(address);
  if (sector < 0x08) {
    top = sector * 0x1000;
  }
  else if (sector <= 0x15) {
    top = (sector - 7) * 0x8000;
  }
  else {
    top = (sector - 0x16) * 0x1000 + 0x78000;
  }
  return top;
}

unsigned int IAPObj::GetSectorBottom(unsigned int address)
{
unsigned int sector, bottom;
  sector = GetSectorNumber(address);
  if (sector < 0x08) {
    bottom = sector * 0x1000 + 0xfff;
  }
  else if (sector <= 0x15) {
    bottom = (sector - 7) * 0x8000 + 0x7fff;
  }
  else {
    bottom = (sector - 0x16) * 0x1000 + 0x78fff;
  }
  return bottom;
}

void IAPObj::ReadFlash(unsigned int addressflash, unsigned char val[], unsigned int length)
{
unsigned char *ptr;
unsigned int i;
  ptr = (unsigned char *)addressflash;
  for (i = 0; i < length; i ++) {
    val[i] = *ptr++;
  }
}

