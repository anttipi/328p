/*
328p
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "n5110.h"

int8_t h = 0;
int8_t m = 0;
int8_t s = 0;

void TIMER1_OVF_vect()
{
    s++;
    if(s>=60)
    {
        s = 0;
        m++;
        if(m>=60)
        {
            m = 0;
            h++;
            if(h>=24)
                h = 0;
        }
    }
    reti();
}

void init_t2 ()
{
    TIMSK2 &= ~(1<<TOIE2);
    TCCR2A = 0;
    TCCR2B = 0;
    TIFR2 |= (1<<TOV2) | (1<<OCF2A);
    TIMSK2 |= (1<<TOIE2);
    TCCR2B = 0b00000111;
}

int main(void)
{
    init_t2();
    Lcd_init();
    sei();

    while(1)
    {
        Lcd_clear();

        Lcd_printf(9+((s<10)?1:0),2,FONT_1X,s,0);
        if(s<10)Lcd_prints(9,2,FONT_1X,(unsigned char*)PSTR("0"));
        Lcd_prints(8,2,FONT_1X,(unsigned char*)PSTR(":"));

        Lcd_printf(6+((m<10)?1:0),2,FONT_1X,m,0);
        if(m<10)Lcd_prints(6,2,FONT_1X,(unsigned char*)PSTR("0"));
        Lcd_prints(5,2,FONT_1X,(unsigned char*)PSTR(":"));

        Lcd_printf(3+((h<10)?1:0),2,FONT_1X,h,0);
        if(h<10)Lcd_prints(3,2,FONT_1X,(unsigned char*)PSTR("0"));

        Lcd_update();
    }
    ;
    return 0;
}
