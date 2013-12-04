#include "game.h"
#include "graphics_tm4c123.h"
#include "LCD.h"
#include "tm4c123gh6pm.h"

void systick_init(){
    NVIC_ST_CTRL_R = 0;  //disable systick during initialization
    NVIC_ST_RELOAD_R = 0xFFFFFF;    //maximum reload value
    //NVIC_ST_RELOAD_R = 0xFFFFFF;    //maximum reload value
    NVIC_ST_CURRENT_R = 0;   //any write to current clears it
    NVIC_ST_CTRL_R = 7;  //enable systick with core clock
}

void systick_handler(){
    //out_int(num_cubes);
    //LCD_DrawLine();
}

void timer2_init(unsigned long period){ 
    unsigned long volatile delay;
    SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
    delay = SYSCTL_RCGCTIMER_R;
    TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
    TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
    TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
    TIMER2_TAILR_R = period-1;    // 4) reload value, desired delay
    TIMER2_TAPR_R = 0;            // 5) bus clock resolution
    TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
    TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
    NVIC_PRI5_R = (NVIC_PRI5_R & 0x00FFFFFF) | 0x80000000; // 8) priority 4
    // interrupts enabled in the main program after all devices initialized
    // vector number 39, interrupt number 23
    NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
    TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

void timer2a_handler(){ 
    TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
    render_cubes(GREEN, RED);
    draw_player();
    //render_cubes(WHITE, WHITE);
    focal_point.y += dy;
    focal_point.x += dx;
}

void right_button_pressed(){
    if(dx == speed)
        dx = 0;
    else
        dx = speed;
}

void left_button_pressed(){
    if(dx == -1 * speed)
        dx = 0;
    else
        dx = -1 * speed;
}

void change_speed(){
    //stuff
}
