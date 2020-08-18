struct __vic2 {
    unsigned char           spr0_x;         /* Sprite 0, X coordinate */
    unsigned char           spr0_y;         /* Sprite 0, Y coordinate */
    unsigned char           spr1_x;         /* Sprite 1, X coordinate */
    unsigned char           spr1_y;         /* Sprite 1, Y coordinate */
    unsigned char           spr2_x;         /* Sprite 2, X coordinate */
    unsigned char           spr2_y;         /* Sprite 2, Y coordinate */
    unsigned char           spr3_x;         /* Sprite 3, X coordinate */
    unsigned char           spr3_y;         /* Sprite 3, Y coordinate */
    unsigned char           spr4_x;         /* Sprite 4, X coordinate */
    unsigned char           spr4_y;         /* Sprite 4, Y coordinate */
    unsigned char           spr5_x;         /* Sprite 5, X coordinate */
    unsigned char           spr5_y;         /* Sprite 5, Y coordinate */
    unsigned char           spr6_x;         /* Sprite 6, X coordinate */
    unsigned char           spr6_y;         /* Sprite 6, Y coordinate */
    unsigned char           spr7_x;         /* Sprite 7, X coordinate */
    unsigned char           spr7_y;         /* Sprite 7, Y coordinate */
    unsigned char           spr_hi_x;       /* High bits of X coordinate */
    unsigned char           ctrl1;          /* Control register 1 */
    unsigned char           rasterline;     /* Current raster line */
    unsigned char           strobe_x;       /* Light pen, X position */
    unsigned char           strobe_y;       /* Light pen, Y position */
    unsigned char           spr_ena;        /* Enable sprites */
    unsigned char           ctrl2;          /* Control register 2 */
    unsigned char           spr_exp_y;      /* Expand sprites in Y dir */
    unsigned char           addr;           /* Address of chargen and video ram */
    unsigned char           irr;            /* Interrupt request register */
    unsigned char           imr;            /* Interrupt mask register */
    unsigned char           spr_bg_prio;    /* Priority to background */
    unsigned char           spr_mcolor;     /* Sprite multicolor bits */
    unsigned char           spr_exp_x;      /* Expand sprites in X dir */
    unsigned char           spr_coll;       /* Sprite/sprite collision reg */
    unsigned char           spr_bg_coll;    /* Sprite/background collision reg */
    unsigned char           bordercolor;    /* Border color */
    unsigned char           bgcolor0;       /* Background color 0 */
    unsigned char           bgcolor1;       /* Background color 1 */
    unsigned char           bgcolor2;       /* Background color 2 */
    unsigned char           bgcolor3;       /* Background color 3 */
    unsigned char           spr_mcolor0;    /* Color 0 for multicolor sprites */
    unsigned char           spr_mcolor1;    /* Color 1 for multicolor sprites */
    unsigned char           spr0_color;     /* Color sprite 0 */
    unsigned char           spr1_color;     /* Color sprite 1 */
    unsigned char           spr2_color;     /* Color sprite 2 */
    unsigned char           spr3_color;     /* Color sprite 3 */
    unsigned char           spr4_color;     /* Color sprite 4 */
    unsigned char           spr5_color;     /* Color sprite 5 */
    unsigned char           spr6_color;     /* Color sprite 6 */
    unsigned char           spr7_color;     /* Color sprite 7 */

    /* The following ones are only valid in the C128: */
    unsigned char           x_kbd;          /* Additional keyboard lines */
    unsigned char           clock;          /* Clock switch bit */
};
struct __6526 {
    unsigned char       pra;            /* Port register A */
    unsigned char       prb;            /* Port register B */
    unsigned char       ddra;           /* Data direction register A */
    unsigned char       ddrb;           /* Data direction register B */
    unsigned char       ta_lo;          /* Timer A, low byte */
    unsigned char       ta_hi;          /* Timer A, high byte */
    unsigned char       tb_lo;          /* Timer B, low byte */
    unsigned char       tb_hi;          /* Timer B, high byte */
    unsigned char       tod_10;         /* TOD, 1/10 sec. */
    unsigned char       tod_sec;        /* TOD, seconds */
    unsigned char       tod_min;        /* TOD, minutes */
    unsigned char       tod_hour;       /* TOD, hours */
    unsigned char       sdr;            /* Serial data register */
    unsigned char       icr;            /* Interrupt control register */
    unsigned char       cra;            /* Control register A */
    unsigned char       crb;            /* Control register B */
};

#define VIC     (*(struct __vic2*)0xD000)
#define CIA1    (*(struct __6526*)0xDC00)
#define CIA2    (*(struct __6526*)0xDD00)
    