#ifndef __TM1637_H__

#define __TM1637_H__



void led_test(void);
void led_update(U8 addr );


void led_init(void);


extern volatile U8 g_led[];



#define SEG_HOUR_TEN 0
#define SEG_HOUR_SINGLE 1
#define SEG_MIN_TEN 2
#define SEG_MIN_SINGLE 3
#define SEG_ICON 4

#define ICON_SPOT 0x01
#define ICON_WIFI 0x02
#define ICON_FULL_GO 0x0c
#define ICON_BAT_3 0x70
#define ICON_BAT_2 0x60
#define ICON_BAT_1 0x40

#define ICON_BAT 0x70



#define _A 0x01
#define _B 0x02
#define _C 0x04
#define _D 0x08
#define _E 0x10
#define _F 0x20
#define _G 0x40


#define DP_1 0x80
#define DP_2 0x80



#define CHAR_0	_A | _B | _C | _D | _E | _F
#define CHAR_1  _E | _F
#define CHAR_2  _A | _B | _G | _E | _D
#define CHAR_3  _A | _B | _G | _C | _D
#define CHAR_4  _F | _G | _B | _C
#define CHAR_5  _A | _F | _G | _C | _D
#define CHAR_6  _A | _F | _G | _C | _D | _E
#define CHAR_7  _A | _B | _C
#define CHAR_8  _A | _B | _C | _D | _E | _F | _G
#define CHAR_9  _A | _B | _C | _D | _F | _G

#define CHAR_S  _A | _F | _G | _C | _D
#define CHAR_E  _A | _D | _E | _F | _G
#define CHAR_R  _E | _G


extern U8 digit_num[];






#endif
