#define BILLION	0x3B9ACA00
#define A BILLION / 442
#define FSHARP BILLION / 372
#define D BILLION / 295

#define FAIRY_FOUNTAIN_LENGTH 129
#define SARIA_SONG_LENGTH 89
// basic functions defined at end of startup.s
extern unsigned long fairyFountain[];
extern unsigned long sariaSong[];
extern unsigned long a[];
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void busyWait(unsigned long);
void playSong(unsigned long *, unsigned long);
void stopSong();

	// songs

/*
void busyWait(){
	unsigned long startTime = NVIC_ST_CURRENT_R;
	while(startTime - NVIC_ST_CURRENT_R < 80)
		;
}*/