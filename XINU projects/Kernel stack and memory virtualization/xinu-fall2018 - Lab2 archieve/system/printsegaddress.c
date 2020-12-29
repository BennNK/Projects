//void printsegaddress()

#include <xinu.h>

void printsegaddress()

{


unsigned char *textend=(unsigned char*)&etext;
unsigned char *dataend=(unsigned char*)&edata;
unsigned char *bssend=(unsigned char*)&ebss;

kprintf("end of text seg 0x%08x\n\n",textend);
kprintf("end of data seg 0x%08x\n\n",dataend);
kprintf("end of bss seg 0x%08x\n\n",bssend);

kprintf("6 bytes before end of text seg \n0x");
for(int i=-6;i<0;i++){
      kprintf("%02x\n",textend+i);

}
kprintf("6 bytes after end of text seg \n0x");
for(int i=0;i<6;i++){
      kprintf("%02x\n",textend+i);

}

kprintf("6 bytes before end of data seg \n0x");
for(int i=-6;i<0;i++){
      kprintf("%02x\n",dataend+i);

}
kprintf("6 bytes after end of data seg \n0x");
for(int i=0;i<6;i++){
      kprintf("%02x\n",dataend+i);

}

kprintf("6 bytes before end of bss seg \n0x");
for(int i=-6;i<0;i++){
      kprintf("%02x\n",bssend+i);

}
kprintf("6 bytes after end of bss seg \n0x");
for(int i=0;i<6;i++){
      kprintf("%02x\n",bssend+i);

}





}

