// Lab6.c
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2013 
// Last Modified: 10/9/2013 
// Section 1-2pm     TA: Saugata Bhattacharyya
// Lab number: 6
// Brief description of the program
//   A digital piano with 4 keys and a 4-bit DAC
// Hardware connections


#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "Sound.h"
#include "Piano.h"

#include "Lab6.h"
// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
unsigned long fairyFountain[FAIRY_FOUNTAIN_LENGTH] = {0x01300370, 0x0130024B, 0x013001D2, 0x01300188,
								0x01300310, 0x0130024B, 0x013001D2, 0x01300188,
								0x013002E4, 0x0130024B, 0x013001D2, 0x01300188,
								0x01300310, 0x0130024B, 0x013001D2, 0x01300188,
								0x01300310, 0x0130020B, 0x013001B8, 0x0130015D,
								0x013002BA, 0x0130020B, 0x013001B8, 0x0130015D,
								0x01300293, 0x0130020B, 0x013001B8, 0x0130015D,
								0x013002BA, 0x0130020B, 0x013001B8, 0x0130015D,
								0x013002BA, 0x013001D2, 0x01300188, 0x0130014A,
								0x01300293, 0x013001D2, 0x01300188, 0x0130014A,
								0x0130026E, 0x013001D2, 0x01300188, 0x0130014A,
								0x01300293, 0x013001D2, 0x01300188, 0x0130014A,
								0x01300293, 0x013001B8, 0x0130015D, 0x01300126,
								0x0130024B, 0x013001B8, 0x0130015D, 0x01300126,
								0x0130022A, 0x013001B8, 0x0130015D, 0x01300126,
								0x0130024B, 0x013001B8, 0x0130015D, 0x01300126,
								0x01300370, 0x0130024B, 0x013001D2, 0x01300188,
								0x01300310, 0x0130024B, 0x013001D2, 0x01300188,
								0x013002E4, 0x0130024B, 0x013001D2, 0x01300188,
								0x01300310, 0x0130024B, 0x013001D2, 0x01300188,
								0x013003A4, 0x0130026E, 0x0130020B, 0x01300172,
								0x01300370, 0x0130026E, 0x0130020B, 0x01300172,
								0x0130033F, 0x0130026E, 0x0130020B, 0x01300172,
								0x01300370, 0x0130026E, 0x0130020B, 0x01300172,
								0x01300417, 0x0130024B, 0x013001D2, 0x01300188,
								0x013003A4, 0x0130024B, 0x013001D2, 0x01300188,
								0x01300370, 0x0130024B, 0x013001D2, 0x01300188,
								0x013003A4, 0x0130024B, 0x013001D2, 0x01300188, 
								0x01300370, 0x013001D2, 0x01300188, 0x0130014A,
								0x01300310, 0x013001D2, 0x01300188, 0x0130014A,
								0x013002BA, 0x013001D2, 0x01300188, 0x0130014A,
								0x01300293, 0x013001D2, 0x01300188, 0x0130014A,
								0x00000000};
unsigned long sariaSong[SARIA_SONG_LENGTH] = {0x0130015D, 0x013001B8, 0x026001EE, 0x0130015D, 
								0x013001B8, 0x026001EE, 0x0130015D, 0x013001B8, 
								0x013001EE, 0x01300293, 0x0260024B, 0x013001EE, 
								0x0130020B, 0x013001EE, 0x01300188, 0x05F0014A, 
								0x01300126, 0x0130014A, 0x01300188, 0x0720014A,
								0x0130015D, 0x013001B8, 0x026001EE, 0x0130015D, 
								0x013001B8, 0x026001EE, 0x0130015D, 0x013001B8, 
								0x013001EE, 0x01300293, 0x0260024B, 0x013001EE, 
								0x0130020B, 0x01300293, 0x0130020B, 0x05F00188, 
								0x013001EE, 0x01300188, 0x01300126, 0x0720014A,
								0x01300093, 0x013000A5, 0x026000AF, 0x013000C4, 
								0x013000DC, 0x026000F7, 0x01300106, 0x013000F7, 
								0x072000A5, 0x013000AF, 0x013000C4, 0x026000DC, 
								0x013000F7, 0x01300106, 0x02600126, 0x0130014A, 
								0x0130015D, 0x07200188, 0x01300093, 0x013000A5, 
								0x026000AF, 0x013000C4, 0x013000DC, 0x026000F7,
								0x01300106, 0x013000F7, 0x072000A5, 0x013000AF, 
								0x013000A5, 0x013000C4, 0x013000AF, 0x013000DC, 
								0x013000C4, 0x013000F7, 0x013000DC, 0x01300106, 
								0x013000F7, 0x01300126, 0x01300106, 0x0130014A, 
								0x01300126, 0x0098014A, 0x0130015D, 0x00980126,
								0x0980014A, 0x07200000, 0x013001EE, 0x01300000,
								0x00000000};
	
unsigned long a[1] = {0x01300370};
void busyWait(unsigned long time);
void playSong(unsigned long *song, unsigned long length);
void Timer0A_Init();
void stopSong();

	// songs

/*
void busyWait(){
	unsigned long startTime = NVIC_ST_CURRENT_R;
	while(startTime - NVIC_ST_CURRENT_R < 80)
		;
}*/
void busyWait(unsigned long time){
	unsigned i;
	for(i = 0; i < time * 7; i++)
		__nop();
}

void playSong(unsigned long *song, unsigned long length){
	int i;
	for(i = 0; i < length; i++){
		if(!(song[i] & 0x0000FFFF)){
			Sound_Play(0);
		}else{	
			Sound_Play(BILLION / (song[i] & 0x0000FFFF) / 2);
		}
		busyWait(1000 * (song[i] >> 16));
	}
}
/*
void Timer0A_Init(){
	SYSCTL_RCGC1_R |= 0x00010000;
	TIMER0_CTL_R &= ~0x00000001;
	TIMER0_CFG_R = 0x00000004;
	TIMER0_TAMR_R = 0x00000002;
	TIMER0_TAILR_R = 0x00007FFF;
	TIMER0_TAPR_R = 0xFF;
	TIMER0_ICR_R = 0x00000001;
	TIMER0_IMR_R |= 0x00000001;
	NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF) | 0xE0000000;
	NVIC_EN0_R = 0x00080000;
	TIMER0_CTL_R |= 0x00000001;
	//EnableInterrupts();
}
void Timer0A_Handler(){
	TIMER0_ICR_R = 0x00000001;
	Sound_Play(song[note]);
	if(++sixteenths == song[note] >> 16){
		note = (++note) % song_length;
		sixteenths = 0;
	}
}
*/
void stopSong(){
	SYSCTL_RCGC1_R &= ~0x00010000;
}
