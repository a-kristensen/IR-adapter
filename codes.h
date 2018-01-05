// codes.h

#ifndef _CODES_h
#define _CODES_h

typedef enum BeoOneAddr
{
  SOURCE_CONTROL = 0x1C,
} BeoOneAddr;

enum eBeoRemoteOne
{
  BR1_BTN_REPEAT = 0x75,
  
  BR1_GUIDE = 0x40,
  BR1_BACK = 0x14,
  BR1_INFO = 0x43,
  
  BR1_UP = 0xCA,
  BR1_DOWN = 0xCB,
  BR1_LEFT = 0xCC,
  BR1_RIGHT = 0xCD,
  BR1_GO = 0x13,

  BR1_FAST_BACK = 0x32,
  BR1_FAST_FOR = 0x34,
  BR1_PLAY = 0x35,
  BR1_PAUSE = 0x36,
  BR1_P_UP = 0x1E,
  BR1_P_DOWN = 0x1F
};

//rf 433mhz outlets
#define CH1_ON  83029
#define CH1_OFF 83028
#define CH2_ON  86101
#define CH2_OFF 86100
#define CH3_ON  70741
#define CH3_OFF 70740
#define CH4_ON  21589
#define CH4_OFF 21588

//LED under bed light strip
//24 bit
#define LED_POWER       1521665
#define LED_MODE_UP     1521669
#define LED_MODE_DOWN   1521675
#define LED_SPEED_UP    1521673
#define LED_SPEED_DOWN  1521671
#define LED_COLOR_UP    1521674
#define LED_COLOR_DOWN  1521677
#define LED_BRIGHT_UP   1521676
#define LED_BRIGHT_DOWN 1521679
#define LED_DEMO        1521672

#define SAMSUNG_POWER       0xE0E040BF
#define SAMSUNG_PLAY        0xE0E0E21D
#define SAMSUNG_STOP        0xE0E0629D
#define SAMSUNG_UP          0xE0E006F9
#define SAMSUNG_DOWN        0xE0E08679
#define SAMSUNG_LEFT        0xE0E0A659
#define SAMSUNG_RIGHT       0xE0E046B9
#define SAMSUNG_ENTER       0xE0E016E9
#define SAMSUNG_VOLUME_UP   0xE0E0E01F
#define SAMSUNG_VOLUME_DOWN 0xE0E0D02F
#define SAMSUNG_MENU        0xE0E058A7
#define SAMSUNG_MUTE        0xE0E0F00F
#define SAMSUNG_EXIT        0xE0E0B44B
#define SAMSUNG_FAST_BACK   0xE0E0A25D
#define SAMSUNG_FAST_FOR    0xE0E012ED
#define SAMSUNG_RETURN      0xE0E01AE5
#define SAMSUNG_P_UP        0xE0E048B7
#define SAMSUNG_P_DOWN      0xE0E008F7
#define SAMSUNG_INFO        0xE0E0F807

#define SAMSUNG_SRC_TV      0xE0E0BE41
#define SAMSUNG_SRC_DVD     0xE0E07E81
#define SAMSUNG_SRC_STB     0xE0E0FE01
#define SAMSUNG_SRC_CABLE   0xE0E0DE21
#define SAMSUNG_SRC_VCR     0xE0E05EA1

#define SAMSUNG_RED         0xE0E036C9
#define SAMSUNG_YELLOW      0xE0E0A857
#define SAMSUNG_GREEN       0xE0E028D7
#define SAMSUNG_BLUE        0xE0E06897

#define SAMSUNG_0           0xE0E08877
#define SAMSUNG_1           0xE0E020DF
#define SAMSUNG_2           0xE0E0A05F
#define SAMSUNG_3           0xE0E0609F
#define SAMSUNG_4           0xE0E010EF
#define SAMSUNG_5           0xE0E0906F
#define SAMSUNG_6           0xE0E050AF
#define SAMSUNG_7           0xE0E030CF
#define SAMSUNG_8           0xE0E0B04F
#define SAMSUNG_9           0xE0E0708F



#endif

