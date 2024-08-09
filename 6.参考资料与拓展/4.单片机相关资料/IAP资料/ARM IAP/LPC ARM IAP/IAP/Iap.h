#ifndef __IAPIAP_H
#define __IAPIAP_H

#define Device_LPC2131  0x0002ff01// 196353
#define Device_LPC2132  0x0002ff11// 196369
#define Device_LPC2134  0x0002ff12// 196370
#define Device_LPC2136  0x0002ff23// 196387
#define Device_LPC2138  0x0002ff25// 196389


class IAPObj;

class IAPObj{
public:
  IAPObj(void);
//基本IAP函数
  unsigned int SelSector(unsigned int, unsigned int);
  unsigned int ReadBootLoaderID(void);//读Boot代码及版本号
  unsigned int ReadPartID(void);//读器件标识号
  unsigned int EraseSector(unsigned int, unsigned int);
  unsigned int UploadtoFlash(unsigned int, unsigned int, unsigned int);
  unsigned int CompareFlash(unsigned int, unsigned int, unsigned int);
  unsigned int BlankCheck(unsigned int, unsigned int);
  unsigned int IapExec(void);
//扩展IAP函数
  unsigned int GetSectorNumber(unsigned int);
  unsigned int GetSectorSize(unsigned int);
  unsigned int GetSectorTop(unsigned int);
  unsigned int GetSectorBottom(unsigned int);
  unsigned int EraseFlash(unsigned int, unsigned int);
  unsigned int WriteFlash(unsigned int, unsigned int, unsigned int);
  void ReadFlash(unsigned int, unsigned char [], unsigned int);
  unsigned int BlockWriteFlash(unsigned int, unsigned int, unsigned int);
  unsigned int CheckFlash(unsigned int, unsigned int);
private:
  IAP iap_intry;
public:
  unsigned int result[2];
private:
  unsigned int command[5];
};

//__noinit__ IAPObj Iap; 

#endif  // __IAPIAP_H
