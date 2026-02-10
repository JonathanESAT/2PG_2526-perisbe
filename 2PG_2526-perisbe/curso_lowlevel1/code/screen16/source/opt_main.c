#include <gba_base.h>
#include <gba_video.h>
#include <gba_systemcalls.h>
#include <gba_interrupt.h>

#define RGB16(r,g,b)  ((r)+((g)<<5)+((b)<<10)) 

int main()
{
  int x,y = 0;  

  // Set up the interrupt handlers
  irqInit();
  // Enable Vblank Interrupt to allow VblankIntrWait
  irqEnable(IRQ_VBLANK);

  // Allow Interrupts
  REG_IME = 1;

  // GBA's VRAM is located at address 0x6000000. 
  // Screen memory in MODE 3 is located at the same place
  volatile unsigned short* screen = (unsigned short*)0x6000000;
  // GBA's graphics chip is controled by registers located at 0x4000000 
  volatile unsigned int* video_regs = (unsigned int*) 0x4000000; // mode3, bg2 on (16 bits RGB)
  // Configure the screen at mode 3 using the display mode register

  unsigned short* s_coords = screen;
  s_coords += 30 + 20 * 240;  
 
  video_regs[0] = 0x403; // mode3, bg2 on (16 bits RGB)

  for(int i = 0; i < 240 * 160; i++){
  screen[i] = 0x7fff;
}

  for(int i = 0; i <= 180; i++){
  s_coords[i] = 0x0000;
}
  
  s_coords += 31200;

  for(int i = 0; i <= 180; i++){
  s_coords[i] = 0x0000;
}

}
/*
  int tmp = 20 * 240;
  int tmp2 = 150 * 240;
  for(x = 30; x <= 210; x++){
  screen[x + tmp] = 0x0000;
  screen[x + tmp2] = 0x0000;
}
  for(y = 20; y <= 150; y++){
  screen[30 + y * 240] = 0x0000;
  screen[210 + y * 240] = 0x0000;
}
}
*/

/*
  for(y = 0; y<160; y++){
    int tmp_y = y * 240;                              
    for(x = 0; x<240;x++)
      if(x >= 30 && x <= 210 && y >= 20 && y <= 130)
{
         screen[x + tmp_y] = 0x0000;
}                    
     screen[x + tmp_y] = 0x7fff;                    
}

//268.800 instrucciones



  while(1) {
    VBlankIntrWait();

 
    g++;
  }
}
*/

