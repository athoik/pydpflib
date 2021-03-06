// Dirty trick to use a # for the assembly:
#define HASH #
#define _escape(x) x
#define _concat(x, y) x##y

/* System functions */

/** Shut down DPF
 * \param mode     one of [#PWR_IDLE, #PWR_SLEEP, #PWR_DEEPSLEEP, #PWR_DOWN]
 */
void shutdown(unsigned char mode) __banked;
/** Turn off DPF. After wakeup, initializes screen and sets global refresh
 * bit for main loop
 */
void turn_off(void) __banked;

/** Sleeps in units of 1 / 1024 seconds */
void sleep(unsigned short ticks) __banked;

/** Initialize LCD screen */
void lcd_init(void) __banked;

/** Initialize all peripherals */
void init_all(unsigned char mode) __banked;

/** Initialize PWM backlight */
void timer1_config(unsigned char brightness) __banked;

enum {
	PWR_IDLE,        ///< Go idle for one second
	PWR_SLEEP,       ///< Turn off LCD LED only
	PWR_DEEPSLEEP,   ///< Turn off all ports and LCD power
	PWR_DOWN,        ///< Powerdown, only reset can restart
};

/* Menu functions */

typedef 
enum { S_RUN, S_LOWPOWER, S_MENU, S_EDIT } MainState;

typedef 
enum { S_GOOD, S_LOW, S_DOWN } PwrState;

#define STATE_ENTER(a, b, c) (a != b && b == c)
#define STATE_LEAVE(a, b, c) (a != b && a == c)

MainState handle_event(MainState state, unsigned char evt) __banked;

/* Generic utils for DPF hack */

void disp_home(void) __banked;
void set_orientation(unsigned char which) __banked;
void clrscreen(unsigned short col) __banked;
void lcd_demo(unsigned char n) __banked;

#define GOTOXY(_x, _y) g_term.x = _x; g_term.y = _y;
void print_splash(void) __banked;
void notice_powerdown(void) __banked;
void print_status(void) __banked;
void print_dump(void) __banked;
void print_usbstat(void) __banked;

#define CODE_ESCAPE 0x7f
// For padded printing:
#define CODE_CENTER '\176'
#define STR_CODE_CENTER  "\176"

// Drawing:
void fill_rect(__idata const unsigned char *b) __banked;
void copy_rect(__idata const unsigned char *b) __banked;

void draw_buf(unsigned char n) __banked;
void fake_led(unsigned char which, unsigned char col) __banked;

// FLIX mode
void flix_mode(unsigned char evt) __banked;

// RAM applet loading:
void *app_load(unsigned char __idata *b) __banked;
char mem_read(unsigned char __idata *b) __banked;

void *execute(unsigned short jmpaddr);

void usb_init(void) __banked;

// Common function to load data from bank into XRAM (without exec)
void bank_load(unsigned char bankno);
#define BANK_LOAD(func) \
	_asm mov dpl, _escape(HASH)(_concat(_,func) >> 16) \
		lcall _bank_load \
	_endasm

// Library stuff:

unsigned long get_int3i(unsigned char __idata *b);
void spi_sendaddr3i(unsigned char __idata *b);

char flash_detect(__idata unsigned char *codes) __banked;
void flash_print_size(__idata unsigned char *codes) __banked;
void flash_erasesector(unsigned long addr) __banked;
unsigned char flash_write(__pdata unsigned char *buf, unsigned char n) __banked;


// Simple property handling:
char handle_setprop(__idata unsigned char *b) __banked;
char handle_getprop(__idata unsigned char *b) __banked;

// Button events:

#ifdef BUTTON_SWAP    // Some have the button pins swapped
#define KEY_UP   0x02
#define KEY_DOWN 0x04
#else
#define KEY_UP   0x04
#define KEY_DOWN 0x02
#endif

#define KEY_MENU 0x40
// User defined events:
#define EVT_EDIT    0x20
#define EVT_REFRESH 0x21

#define F_UPDATE   0x80  // Update flag for display_menu()

#define PWM_PERIOD 7

// Normalization of ADC value:
#define NORMALIZE_ADCVAL(x) ((x >> 7) - 0x100)
// Battery level threshold, after normalization
#define VBAT_THRESH_PWDN 8
#define VBAT_THRESH_WARN 16

#define LCD_WRITECONST(x) \
_asm mov a, _escape(HASH)x _endasm; \
_asm lcall otp_lcdwrite _endasm;

#define RUB_WATCHDOG() wdtcon |= WDTPND

#define get_short(x) *((unsigned short __idata *) (x))

