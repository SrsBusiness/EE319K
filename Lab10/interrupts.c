#include "game.h"
#include "graphics_tm4c123.h"
#include "LCD.h"
#include "tm4c123gh6pm.h"
#include "ADC.h"
#include "Lab6.h"
unsigned int pe_prev = 0;
unsigned char current_count = 0; // 
unsigned char note_total = 0; //
unsigned int current_note = -1; // index
unsigned int note = 0; // note value


void Timer0A_Init(unsigned long period){
        SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;
        __nop();
        __nop();
        TIMER0_CTL_R &= ~0x01;
        TIMER0_CFG_R = 0x04;
        TIMER0_TAMR_R = 0x02;
        TIMER0_TAILR_R = period;
        TIMER0_TAPR_R = 79;
        TIMER0_ICR_R = 0x01;
        TIMER0_IMR_R |= 0x01;
        NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF)|0x40000000;            //priority 4
        NVIC_EN0_R |= 1<<19;
        TIMER0_CTL_R |= 0x01;
}

void Timer0A_Handler(void) {
	TIMER0_ICR_R = 0x00000001;   // acknowledge timer2A timeout
	if (tick % (CUBE_SIZE/2) == 0) {
			random_wave();
	}
	render_cubes(BLACK, BLACK);
	speed = MAX_SPEED * ADC_In() / 4095;
	focal_point.y += 2 * speed;
	focal_point.x += dx;
	clean_cubes();
	render_cubes(GREEN, BLACK);
	draw_player();
	if(collision()){
		game_over = 1;
		TIMER0_CTL_R &= ~0x01;
	}
	tick++;
}

void timer2_init(){ 
    unsigned long volatile delay;
    SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
    delay = SYSCTL_RCGCTIMER_R;
    TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
    TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
    TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
    TIMER2_TAILR_R = 0xFFFF - 1;    // 4) reload value, desired delay
    TIMER2_TAPR_R = 0xFF - 1;            // 5) bus clock resolution
    TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
    TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
    NVIC_PRI5_R = (NVIC_PRI5_R & 0x00FFFFFF) | 0x00000000; // 8) priority 4
    // interrupts enabled in the main program after all devices initialized
    // vector number 39, interrupt number 23
    NVIC_EN0_R |= 1<<23;           // 9) enable IRQ 23 in NVIC
    TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

void timer2a_handler(){ 
    TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
	if(current_count == note_total){
		current_note = (++current_note) % FAIRY_FOUNTAIN_LENGTH;
		unsigned int temp = fairyFountain[current_note];
		note_total = (temp & 0xFFF00000) / 0x01300000;
		current_count = 0;
		note = temp & 0xFFFF;
		
		//Sound_Play(BILLION / (song[i] & 0x0000FFFF) / 2);
	}
	Sound_Play(BILLION / note / 2);
	current_count++;
}
void button_init(){
	SYSCTL_RCGC2_R |= 0x10;
	__nop();
	__nop();
	__nop();
	GPIO_PORTE_DIR_R &= ~0x03;
	GPIO_PORTE_AFSEL_R &= ~0x03;
	GPIO_PORTE_DEN_R |= 0x03;
	GPIO_PORTE_AMSEL_R &= ~0x03;
	GPIO_PORTE_IS_R &= ~0x03;
	GPIO_PORTE_IBE_R |= 0x03;
	GPIO_PORTE_ICR_R = 0x03;
	GPIO_PORTE_IM_R |= 0x03;
	NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFFFF00) | 0x00000000;
	NVIC_EN0_R = 0x10;
}

void button_pressed(){
	GPIO_PORTE_ICR_R = 0x03;
	unsigned int edges = pe_prev ^ GPIO_PORTE_DATA_R;
	if(edges == 1){
		if(dx == speed)
			dx = 0;
		else
			dx = speed;
	}else if(edges == 2){
		if(dx == -1 * speed)
			dx = 0;
		else
			dx = -1 * speed;
	}else if(edges == 3){
		dx = 0;
	}
	pe_prev = GPIO_PORTE_DATA_R;
}


