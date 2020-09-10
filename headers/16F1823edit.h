//////////// Standard Header file for the PIC16F1823 device ////////////////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996, 2013 Custom Computer Services          ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////
#device PIC16F1823

#nolist
//////// Program memory: 2048x14  Data RAM: 112  Stack: 16
//////// I/O: 12   Analog Pins: 8
//////// Data EEPROM: 256
//////// C Scratch area: 20   ID Location: 8000
//////// Fuses: LP,XT,HS,RC,INTRC_IO,ECL,ECM,ECH,NOWDT,WDT_SW,WDT_NOSL,WDT
//////// Fuses: PUT,NOPUT,NOMCLR,MCLR,PROTECT,NOPROTECT,CPD,NOCPD,NOBROWNOUT
//////// Fuses: BROWNOUT_SW,BROWNOUT_NOSL,BROWNOUT,CLKOUT,NOCLKOUT,NOIESO
//////// Fuses: IESO,NOFCMEN,FCMEN,WRT,WRT_400,WRT_200,NOWRT,PLL_SW,PLL
//////// Fuses: NOSTVREN,STVREN,BORV25,BORV19,DEBUG,NODEBUG,NOLVP,LVP
//////// 
#if (!defined(__PCM__)||defined(__ISNT_CCS__))
#define _bif
#define int char
#define int16 long
#define int32 long long
#define float32 float
#define int1 char

#endif
////////////////////////////////////////////////////////////////// I/O
// Discrete I/O Functions: SET_TRIS_x(), OUTPUT_x(), INPUT_x(),
//                         PORT_x_PULLUPS(), INPUT(),
//                         OUTPUT_LOW(), OUTPUT_HIGH(),
//                         OUTPUT_FLOAT(), OUTPUT_BIT()
// Discrete I/O Prototypes:
_bif void set_tris_a(int value);  
_bif void set_tris_c(int value);  
_bif int get_tris_a(void);  
_bif int get_tris_c(void);  
_bif void output_a(int value);  
_bif void output_c(int value);  
_bif int input_a(void);  
_bif int input_c(void);  
_bif int1 input_change_a(void);  
_bif int1 input_change_c(void);  
_bif int1 input(int16 pin);
_bif int1 input_state(int16 pin);
_bif void output_low(int16 pin);
_bif void output_high(int16 pin);
_bif void output_toggle(int16 pin);
_bif void output_bit(int16 pin, int1 level);
_bif void output_float(int16 pin);
_bif void output_drive(int16 pin);

// Constants used to identify pins in the above are:

#define PIN_A0  96
#define PIN_A1  97
#define PIN_A2  98
#define PIN_A3  99
#define PIN_A4  100
#define PIN_A5  101

#define PIN_C0  112
#define PIN_C1  113
#define PIN_C2  114
#define PIN_C3  115
#define PIN_C4  116
#define PIN_C5  117

////////////////////////////////////////////////////////////////// Useful defines
#define FALSE 0
#define TRUE 1

#define BYTE int
#define BOOLEAN int1

#define getc getch
#define fgetc getch
#define getchar getch
#define putc putchar
#define fputc putchar
#define fgets gets
#define fputs puts

////////////////////////////////////////////////////////////////// Control
// Control Functions:  RESET_CPU(), SLEEP(), RESTART_CAUSE()
// Prototypes:
_bif int restart_cause(void);
_bif void reset_cpu(void);
_bif void sleep(void);
// Constants returned from RESTART_CAUSE() are:
#define NORMAL_POWER_UP      0x3C
#define BROWNOUT_RESTART     0x3E
#define MCLR_FROM_SLEEP      0x27
#define WDT_TIMEOUT          0x1F
#define WDT_FROM_SLEEP       0x0F
#define INTERRUPT_FROM_SLEEP 0x2F
#define MCLR_FROM_RUN        0x37
#define RESET_INSTRUCTION    0x3B
#define STACK_OVERFLOW       0xBF
#define STACK_UNDERFLOW      0x7F

////////////////////////////////////////////////////////////////// Timer 0
// Timer 0 (AKA RTCC)Functions: SETUP_COUNTERS() or SETUP_TIMER_0(),
//                              SET_TIMER0() or SET_RTCC(),
//                              GET_TIMER0() or GET_RTCC()
// Timer 0 Prototypes:
_bif void setup_timer_0(int mode);
_bif void set_timer0(int value);      
_bif int get_timer0(void);            
_bif void setup_counters(int mode, int prescaler);
_bif void set_rtcc(int value);        
_bif int get_rtcc(void);              
// Constants used for SETUP_TIMER_0() are:
#define T0_INTERNAL   0   
#define T0_EXT_L_TO_H 32
#define T0_EXT_H_TO_L 48

#define T0_DIV_1      8
#define T0_DIV_2      0
#define T0_DIV_4      1
#define T0_DIV_8      2
#define T0_DIV_16     3
#define T0_DIV_32     4
#define T0_DIV_64     5
#define T0_DIV_128    6
#define T0_DIV_256    7


#define T0_8_BIT      0     

#define RTCC_INTERNAL   0      // The following are provided for compatibility
#define RTCC_EXT_L_TO_H 32     // with older compiler versions
#define RTCC_EXT_H_TO_L 48
#define RTCC_DIV_1      8
#define RTCC_DIV_2      0
#define RTCC_DIV_4      1
#define RTCC_DIV_8      2
#define RTCC_DIV_16     3
#define RTCC_DIV_32     4
#define RTCC_DIV_64     5
#define RTCC_DIV_128    6
#define RTCC_DIV_256    7
#define RTCC_8_BIT      0     

// Constants used for SETUP_COUNTERS() are the above
// constants for the 1st param and the following for
// the 2nd param:

////////////////////////////////////////////////////////////////// WDT
// Watch Dog Timer Functions: SETUP_WDT(), RESTART_WDT()
// WDT base is 1ms
// WDT Prototypes:
_bif void setup_wdt(int16 mode);
_bif void restart_wdt(void);
// Constants used for SETUP_WDT() are:
#define WDT_ON      0x1000
#define WDT_OFF     0x2000

#define WDT_1MS     0x100
#define WDT_2MS     0x101
#define WDT_4MS     0x102
#define WDT_8MS     0x103
#define WDT_16MS    0x104
#define WDT_32MS    0x105
#define WDT_64MS    0x106
#define WDT_128MS   0x107
#define WDT_256MS   0x108
#define WDT_512MS   0x109
#define WDT_1S      0x10A
#define WDT_2S      0x10B
#define WDT_4S      0x10C
#define WDT_8S      0x10D
#define WDT_16S     0x10E
#define WDT_32S     0x10F
#define WDT_64S     0x110
#define WDT_128S    0x111
#define WDT_256S    0x112

////////////////////////////////////////////////////////////////// Timer 1
// Timer 1 Functions: SETUP_TIMER_1, GET_TIMER1, SET_TIMER1
// Timer 1 Prototypes:
_bif void setup_timer_1(int16 mode);
_bif int16 get_timer1(void);
_bif void set_timer1(int16 value);
// Constants used for SETUP_TIMER_1() are:
//      (or (via |) together constants from each group)
#define T1_DISABLED         0
#define T1_CAPSENSE         0xC5
#define T1_EXTERNAL         0x85
#define T1_EXTERNAL_SYNC    0x81
#define T1_FOSC             0x45
#define T1_INTERNAL         0x05

#define T1_ENABLE_T1OSC	    0x08

#define T1_DIV_BY_1         0x00
#define T1_DIV_BY_2         0x10
#define T1_DIV_BY_4         0x20
#define T1_DIV_BY_8         0x30

#define T1_GATE           0x8000
#define T1_GATE_INVERTED  0xC000
#define T1_GATE_TOGGLE    0xA000
#define T1_GATE_SINGLE    0x9000
#define T1_GATE_TIMER0    0x8100
#define T1_GATE_COMP1     0x8200 
#define T1_GATE_COMP2     0x8300  

#define T1_GATE_A4			0
#define T1_GATE_A3			0x10000

////////////////////////////////////////////////////////////////// Timer 2
// Timer 2 Functions: SETUP_TIMER_2, GET_TIMER2, SET_TIMER2
// Timer 2 Prototypes:
_bif void setup_timer_2(int mode, int period, int postscale); 
_bif int get_timer2(void);
_bif void set_timer2(int value);
// Constants used for SETUP_TIMER_2() are:
#define T2_DISABLED         0
#define T2_DIV_BY_1         4
#define T2_DIV_BY_4         5
#define T2_DIV_BY_16        6 
#define T2_DIV_BY_64        7 

////////////////////////////////////////////////////////////////// CCP
// CCP Functions: SETUP_CCPx, SET_PWMx_DUTY
// CCP Variables: CCP_x, CCP_x_LOW, CCP_x_HIGH
// CCP1 Prototypes:
_bif void setup_ccp1(int32 mode);
_bif void setup_ccp1(int32 mode, int pwm);
_bif void set_pwm1_duty(int16 value);
// Constants used for SETUP_CCPx() are:
#define CCP_OFF                         0
#define CCP_CAPTURE_FE                  4
#define CCP_CAPTURE_RE                  5
#define CCP_CAPTURE_DIV_4               6
#define CCP_CAPTURE_DIV_16              7
#define CCP_COMPARE_SET_ON_MATCH        8
#define CCP_COMPARE_CLR_ON_MATCH        9
#define CCP_COMPARE_INT                 0xA
#define CCP_COMPARE_RESET_TIMER         0xB
#define CCP_PWM                         0xC
#define CCP_PWM_PLUS_1                  0x1c  
#define CCP_PWM_PLUS_2                  0x2c
#define CCP_PWM_PLUS_3                  0x3c
#word   CCP_1       =                   getenv("SFR:CCPR1L")
#byte   CCP_1_LOW   =                   getenv("SFR:CCPR1L")
#byte   CCP_1_HIGH  =                   getenv("SFR:CCPR1H")
// The following should be used with the ECCP unit only (or these in)
#define CCP_PWM_H_H                     0x0c
#define CCP_PWM_H_L                     0x0d
#define CCP_PWM_L_H                     0x0e
#define CCP_PWM_L_L                     0x0f

#define CCP_PWM_FULL_BRIDGE             0x40
#define CCP_PWM_FULL_BRIDGE_REV         0xC0
#define CCP_PWM_HALF_BRIDGE             0x80

#define CCP_SHUTDOWN_ON_COMP1           0x100000
#define CCP_SHUTDOWN_ON_COMP2           0x200000
#define CCP_SHUTDOWN_ON_COMP            0x300000
#define CCP_SHUTDOWN_ON_INT0            0x400000
#define CCP_SHUTDOWN_ON_COMP1_INT0      0x500000
#define CCP_SHUTDOWN_ON_COMP2_INT0      0x600000
#define CCP_SHUTDOWN_ON_COMP_INT0       0x700000

#define CCP_SHUTDOWN_AC_L               0x000000
#define CCP_SHUTDOWN_AC_H               0x040000
#define CCP_SHUTDOWN_AC_F               0x080000

#define CCP_SHUTDOWN_BD_L               0x000000
#define CCP_SHUTDOWN_BD_H               0x010000
#define CCP_SHUTDOWN_BD_F               0x020000

#define CCP_SHUTDOWN_RESTART            0x80000000  

#define CCP_PULSE_STEERING_A            0x01000000
#define CCP_PULSE_STEERING_B            0x02000000
#define CCP_PULSE_STEERING_C            0x04000000
#define CCP_PULSE_STEERING_D            0x08000000
#define CCP_PULSE_STEERING_SYNC         0x10000000




////////////////////////////////////////////////////////////////// SPI
// SPI Functions: SETUP_SPI, SPI_WRITE, SPI_READ, SPI_DATA_IN
// SPI Prototypes:
_bif void setup_spi(int32 mode);
_bif void spi_write(int value);
_bif int spi_read(void);
_bif int spi_read(int value);
_bif int1 spi_data_in(void);
// Constants used in SETUP_SPI() are:
#define SPI_DISABLED             0x00
#define SPI_MASTER               0x20
#define SPI_SLAVE                0x24
#define SPI_SCK_IDLE_HIGH        0x10
#define SPI_SCK_IDLE_LOW         0x00
#define SPI_CLK_DIV_4            0x00
#define SPI_CLK_DIV_16           0x01
#define SPI_CLK_DIV_64           0x02
#define SPI_CLK_T2               0x03
#define SPI_SS_DISABLED          0x01

#define SPI_SS_C3             0x00000  
#define SPI_SS_A3             0x10000  
#define SPI_DO_C2             0x00000  
#define SPI_DO_A4             0x20000

#define SPI_XMIT_L_TO_H          0x4000
#define SPI_XMIT_H_TO_L          0x0000

#define SPI_SAMPLE_AT_MIDDLE     0x0000
#define SPI_SAMPLE_AT_END        0x8000

//The following are provided for compatibility
#define SPI_L_TO_H       SPI_SCK_IDLE_LOW
#define SPI_H_TO_L       SPI_SCK_IDLE_HIGH

////////////////////////////////////////////////////////////////// UART
// UART Prototypes:
_bif void setup_uart(int32 baud);
_bif void setup_uart(int32 baud, int stream);
_bif void setup_uart(int32 baud, int stream, int32 clock);
_bif void set_uart_speed(int32 baud);
_bif void set_uart_speed(int32 baud, int stream);
_bif void set_uart_speed(int32 baud, int stream, int32 clock);
// Constants used in setup_uart() are:
// FALSE - Turn UART off
// TRUE  - Turn UART on
#define UART_ADDRESS           2
#define UART_DATA              4
#define UART_AUTODETECT        8
#define UART_AUTODETECT_NOWAIT 9
#define UART_WAKEUP_ON_RDA     10
#define UART_SEND_BREAK        13
////////////////////////////////////////////////////////////////// COMP
// Comparator Variables: C1OUT, C2OUT  
// Comparator Prototypes:
_bif void setup_comparator(int32 mode);
// Constants used in setup_comparator() are:
//
#define NC_NC_NC_NC     0x00 

//Pick one constant for COMP1
#define CP1_A1_A0       0x8000
#define CP1_C1_A0       0x8001 
#define CP1_C2_A0       0x8002 
#define CP1_C3_A0       0x8003 
#define CP1_A1_DAC      0x8010
#define CP1_C1_DAC      0x8011 
#define CP1_C2_DAC      0x8012 
#define CP1_C3_DAC      0x8013 
#define CP1_A1_FVR      0x8020
#define CP1_C1_FVR      0x8021 
#define CP1_C2_FVR      0x8022 
#define CP1_C3_FVR      0x8023 
//Optionally OR with any of the following
#define CP1_INT_L2H     0x0080
#define CP1_INT_H2L     0x0040
#define CP1_OUT_ON_A2   0x2000
#define CP1_INVERT      0x1000
#define CP1_FAST        0x0400
#define CP1_HYST        0x0200
#define CP1_SYNC        0x0100

//Pick one constant for COMP2 
#define CP2_A1_C0       0x80000000 
#define CP2_C1_C0       0x80010000 
#define CP2_C2_C0       0x80020000 
#define CP2_C3_C0       0x80030000 
#define CP2_A1_DAC      0x80100000 
#define CP2_C1_DAC      0x80110000 
#define CP2_C2_DAC      0x80120000 
#define CP2_C3_DAC      0x80130000 
#define CP2_A1_FVR      0x80200000 
#define CP2_C1_FVR      0x80210000 
#define CP2_C2_FVR      0x80220000 
#define CP2_C3_FVR      0x80230000 
//Optionally OR with any of the following 
#define CP2_INT_L2H     0x00800000 
#define CP2_INT_H2L     0x00400000 
#define CP2_OUT_ON_C4   0x20000000 
#define CP2_INVERT      0x10000000 
#define CP2_FAST        0x04000000 
#define CP2_HYST        0x02000000 
#define CP2_SYNC        0x01000000 

#bit C1OUT = getenv("SFR:CM1CON0").6
#bit C2OUT = getenv("SFR:CM2CON0").6 

////////////////////////////////////////////////////////////////// VREF
// VREF Prototypes:
_bif void setup_vref(int mode);
// Constants used in setup_vref() are:
#define VREF_OFF                        0
#define VREF_ON                         0x80
// The following may be OR'ed in with the above using |
#define VREF_ADC_OFF                    0
#define VREF_ADC_1v024                  0x01
#define VREF_ADC_2v048                  0x02
#define VREF_ADC_4v096                  0x03  
// The following may be OR'ed in with the above using | 
#define VREF_COMP_DAC_OFF               0 
#define VREF_COMP_DAC_1v024             0x04 
#define VREF_COMP_DAC_2v048             0x08 
#define VREF_COMP_DAC_4v096             0x0C 
// The following may be OR'ed in with the above using |
#define TEMPERATURE_INDICATOR_DISABLED  0
#define TEMPERATURE_INDICATOR_ENABLED   0x20
#define TEMPERATURE_RANGE_LOW           0
#define TEMPERATURE_RANGE_HIGH          0x10

////////////////////////////////////////////////////////////////// DAC
// Digital to Analog Functions: SETUP_DAC(), DAC_WRITE()
// DAC Prototypes:
_bif void setup_dac(int mode);
_bif void dac_write(int value);
// Constants used in SETUP_DAC() are:
#define DAC_OFF  0
#define DAC_VSS_VDD   0x80
#define DAC_VREF_VDD  0x81
#define DAC_VSS_VREF  0x84
#define DAC_VREF_VREF 0x85
#define DAC_VSS_FVR   0x88
#define DAC_FVR_VREF  0x89
// The following may be OR'ed in with the above using |
#define DAC_OUTPUT    0x20
#define DAC_LVP_POS   0x40  
#define DAC_LVP_NEG   0  


////////////////////////////////////////////////////////////////// INTERNAL RC
// Oscillator Prototypes:
_bif void setup_oscillator(int mode);
// Constants used in setup_oscillator() are:
// First param:
#define OSC_31KHZ   0
#define OSC_31250   (2*8)
#define OSC_62KHZ   (4*8)
#define OSC_125KHZ  (5*8)
#define OSC_250KHZ  (6*8)
#define OSC_500KHZ  (7*8)
#define OSC_1MHZ    (11*8)
#define OSC_2MHZ    (12*8)
#define OSC_4MHZ    (13*8)
#define OSC_8MHZ    (14*8)
#define OSC_16MHZ   (15*8)
// The following may be OR'ed in with the above using |
#define OSC_TIMER1  1 
#define OSC_INTRC   2
#define OSC_NORMAL  0
// The following may be OR'ed in with the above using |
#define OSC_PLL_ON  0x80
#define OSC_PLL_OFF 0


////////////////////////////////////////////////////////////////// ADC
// ADC Functions: SETUP_ADC(), SETUP_ADC_PORTS() (aka SETUP_PORT_A),
//                SET_ADC_CHANNEL(), READ_ADC()
// ADC Prototypes:
_bif void setup_adc(int16 mode);
_bif int read_adc(void);
_bif int read_adc(int mode);
_bif int16 read_adc(void);
_bif int16 read_adc(int mode);
_bif int1 adc_done(void);
// Constants used for SETUP_ADC() are:
#define ADC_OFF                0              // ADC Off
#define ADC_CLOCK_DIV_2    0x100  
#define ADC_CLOCK_DIV_4     0x40  
#define ADC_CLOCK_DIV_8     0x10
#define ADC_CLOCK_DIV_32    0x20
#define ADC_CLOCK_DIV_16    0x50
#define ADC_CLOCK_DIV_64    0x60
#define ADC_CLOCK_INTERNAL  0x30              // Internal 2-6us

//ADC Prototypes:
_bif void setup_adc_ports(int32 pins);
_bif void setup_adc_ports(int32 pins, int32 reference);
_bif void set_adc_channel(int channel);
// Constants used in SETUP_ADC_PORTS() are:
// First argument:
// OR together desired pins
#define sAN0            0x000100    //| A0
#define sAN1            0x000200    //| A1
#define sAN2            0x000400    //| A2
#define sAN3            0x001000    //| A4
#define sAN4            0x000001    //| C0 
#define sAN5            0x000002    //| C1 
#define sAN6            0x000004    //| C2 
#define sAN7            0x000008    //| C3 
#define NO_ANALOGS             0    // None
#define ALL_ANALOG      0x00170F    // A0 A1 A2 A4 C0 C1 C2 C3 

// Optional Second argument:
#define VSS_VDD         0x000000    //| Range 0-Vdd
#define VSS_VREF        0x020000    //| Range 0-Vref
#define VSS_FVR         0x030000    //| Range 0-Fixed Voltage Reference

// Constants used in SET_ADC_CHANNEL() are:
// either use the channel number or one of the following
#define TEMPERATURE_INDICATOR     0x1D
#define DAC_CHANNEL               0x1E
#define FVR_CHANNEL               0x1F

// Constants used in READ_ADC() are:
#define ADC_START_AND_READ     7   // This is the default if nothing is specified
#define ADC_START_ONLY         1
#define ADC_READ_ONLY          6

////////////////////////////////////////////////////////////////// BIF
// Built In Functions Prototypes
//
// Math Prototypes:
_bif signed int abs(signed int x);
_bif signed int16 abs(signed int16 x);
_bif signed int32 abs(signed int32 x);
_bif float32 abs(float32 x);
_bif unsigned int16 _mul(unsigned int, unsigned int);
_bif signed int16 _mul(signed int, signed int);
_bif unsigned int32 _mul(unsigned int16, unsigned int16);
_bif signed int32 _mul(signed int16, signed int16);

// Memory Manipulation Prototypes:
_bif int read_bank(int bank, int offset);
_bif void write_bank(int bank, int offset, int value);
_bif void strcpy(char* dest, char* src);
_bif void strcopy(char* dest, char* src);
_bif void memset(unsigned int* destination, unsigned int value, unsigned int16 num);
_bif void memcpy(unsigned int* destination, unsigned int* source, unsigned int16 num);

// String Prototypes:
_bif char toupper(char cvalue);
_bif char tolower(char cvalue);
_bif void sprintf(char* string, char* cstring, ...);

// Data Manipulators Prototypes:
_bif int1 shift_left(unsigned int* address, unsigned int bytes, int1 value);
_bif int1 shift_right(unsigned int* address, unsigned int bytes, int1 value);
_bif void rotate_left(unsigned int* address, unsigned int bytes);
_bif void rotate_right(unsigned int* address, unsigned int bytes);
_bif void swap(unsigned int value);
_bif unsigned int make8(unsigned int16 var, unsigned int offset);
_bif unsigned int make8(unsigned int32 var, unsigned int offset);
_bif unsigned int16 make16(unsigned int varhigh, unsigned int varlow);
_bif unsigned int32 make32(unsigned int16 var1);
_bif unsigned int32 make32(unsigned int16 var1, unsigned int16 var2);
_bif unsigned int32 make32(unsigned int16 var1, unsigned int var2);
_bif unsigned int32 make32(unsigned int16 var1, unsigned int var2, unsigned int var3);
_bif unsigned int32 make32(unsigned int var1);
_bif unsigned int32 make32(unsigned int var1, unsigned int var2);
_bif unsigned int32 make32(unsigned int var1, unsigned int var2, unsigned int var3);
_bif unsigned int32 make32(unsigned int var1, unsigned int var2, unsigned int var3, unsigned int var4);
_bif unsigned int32 make32(unsigned int var1, unsigned int16 var2);
_bif unsigned int32 make32(unsigned int var1, unsigned int16 var2, unsigned int var3);
_bif unsigned int32 make32(unsigned int var1, unsigned int var2, unsigned int16 var3);
_bif void bit_set(unsigned int var, unsigned int bit);
_bif void bit_set(unsigned int16 var, unsigned int bit);
_bif void bit_set(unsigned int32 var, unsigned int bit);
_bif void bit_clear(unsigned int var, unsigned int bit);
_bif void bit_clear(unsigned int16 var, unsigned int bit);
_bif void bit_clear(unsigned int32 var, unsigned int bit);
_bif int1 bit_test(unsigned int var, unsigned int bit);
_bif int1 bit_test(unsigned int16 var, unsigned int bit);
_bif int1 bit_test(unsigned int32 var, unsigned int bit);

// #use delay() Prototypes:
_bif void delay_cycles(unsigned int count);
_bif void delay_ms(unsigned int16 time);
_bif void delay_us(unsigned int16 time);

// #use rs232() Prototypes:
_bif void putchar(char cdata);
_bif void putchar(char cdata, unsigned int stream);
_bif void puts(char* string);
_bif void puts(char* string, unsigned int stream);
_bif char getch(void);
_bif char getch(unsigned int stream);
_bif void gets(char* string);
_bif void gets(char* string, unsigned int stream);
_bif int1 kbhit(void);
_bif int1 kbhit(unsigned int stream);
_bif void printf(char* string, ...);
_bif void fprintf(unsigned int stream, char* string, ...);
_bif void putc_send(void);
_bif void fputc_send(unsigned int stream);
_bif int1 rcv_buffer_full(void);
_bif int1 rcv_buffer_full(unsigned int stream);
_bif unsigned int16 rcv_buffer_bytes(void);
_bif unsigned int16 rcv_buffer_bytes(unsigned int stream);
_bif int1 tx_buffer_full(void);
_bif int1 tx_buffer_full(unsigned int stream);
_bif unsigned int16 tx_buffer_bytes(void);
_bif unsigned int16 tx_buffer_bytes(unsigned int stream);

// #use i2c() Prototypes:
_bif unsigned int i2c_read(void);
_bif unsigned int i2c_read(unsigned int stream);
_bif unsigned int i2c_read(unsigned int stream, int1 ack);
_bif int1 i2c_write(unsigned int data);
_bif int1 i2c_write(unsigned int stream, unsigned int data);
_bif void i2c_start(void);
_bif void i2c_start(unsigned int stream);
_bif void i2c_start(unsigned int stream, unsigned int restart);
_bif void i2c_stop(void);
_bif void i2c_stop(unsigned int stream);
_bif int i2c_isr_state(void);
_bif void i2c_slaveaddr(unsigned int addr);
_bif void i2c_slaveaddr(unsigned int stream, unsigned int addr);
_bif int1 i2c_poll(void);
_bif int1 i2c_poll(unsigned int stream);
_bif void i2c_init(unsigned int32 baud);
_bif void i2c_init(unsigned int stream, unsigned int32 baud);

// #use spi() Prototypes:
_bif unsigned int spi_xfer(void);
_bif unsigned int16 spi_xfer(void);
_bif unsigned int32 spi_xfer(void);
_bif unsigned int spi_xfer(unsigned int data);
_bif unsigned int16 spi_xfer(unsigned int16 data);
_bif unsigned int32 spi_xfer(unsigned int32 data);
_bif unsigned int spi_xfer(unsigned int stream, unsigned int data);
_bif unsigned int16 spi_xfer(unsigned int stream, unsigned int16 data);
_bif unsigned int32 spi_xfer(unsigned int stream, unsigned int32 data);
_bif unsigned int spi_xfer(unsigned int stream, unsigned int data, unsigned int bits);
_bif unsigned int16 spi_xfer(unsigned int stream, unsigned int16 data, unsigned int bits);
_bif unsigned int32 spi_xfer(unsigned int stream, unsigned int32 data, unsigned int bits);
_bif void spi_init(unsigned int32 baud);
_bif void spi_init(unsigned int stream, unsigned int32 baud);
_bif void spi_speed(unsigned int32 baud);
_bif void spi_speed(unsigned int stream, unsigned int32 baud);
_bif void spi_speed(unsigned int stream, unsigned int32 baud, unsigned int32 clock);
_bif void spi_prewrite(unsigned int data);
_bif void spi_prewrite(unsigned int16 data);
_bif void spi_prewrite(unsigned int32 data);
_bif void spi_prewrite(unsigned int, unsigned int data);
_bif void spi_prewrite(unsigned int, unsigned int16 data);
_bif void spi_prewrite(unsigned int, unsigned int32 data);
_bif unsigned int spi_xfer_in(void);
_bif unsigned int16 spi_xfer_in(void);
_bif unsigned int32 spi_xfer_in(void);
_bif unsigned int spi_xfer_in(unsigned int bits);
_bif unsigned int16 spi_xfer_in(unsigned int bits);
_bif unsigned int32 spi_xfer_in(unsigned int bits);
_bif unsigned int spi_xfer_in(unsigned int stream, unsigned int bits);
_bif unsigned int16 spi_xfer_in(unsigned int stream, unsigned int bits);
_bif unsigned int32 spi_xfer_in(unsigned int stream, unsigned int bits);

// #use rtos() Prototypes:
_bif void rtos_run(void);
_bif void rtos_yield(void);
_bif void rtos_enable(unsigned int task);
_bif void rtos_disable(unsigned int task);
_bif void rtos_terminate(void);
_bif void rtos_await(int1 flag);
_bif void rtos_wait(unsigned int sem);
_bif void rtos_signal(unsigned int sem);
_bif void rtos_msg_send(unsigned int task, unsigned int msg);
_bif unsigned int rtos_msg_read(void);
_bif unsigned int rtos_msg_poll(void);
_bif int1 rtos_overrun(unsigned int task);
_bif void rtos_stats(unsigned int task, unsigned int* stat);

// #use timer() Prototypes:
_bif unsigned int get_ticks(void);
_bif unsigned int16 get_ticks(void);
_bif unsigned int32 get_ticks(void);
_bif unsigned int get_ticks(unsigned int stream);
_bif unsigned int16 get_ticks(unsigned int stream);
_bif unsigned int32 get_ticks(unsigned int stream);
_bif void set_ticks(unsigned int value);
_bif void set_ticks(unsigned int16 value);
_bif void set_ticks(unsigned int32 value);
_bif void set_ticks(unsigned int stream, unsigned int value);
_bif void set_ticks(unsigned int stream, unsigned int16 value);
_bif void set_ticks(unsigned int stream, unsigned int32 value);

// #use pwm() Prototypes:
_bif void pwm_on(void);
_bif void pwm_on(unsigned int stream);
_bif void pwm_off(void);
_bif void pwm_off(unsigned int stream);
_bif void pwm_set_duty(unsigned int16 duty);
_bif void pwm_set_duty(unsigned int stream, unsigned int16 duty);
_bif void pwm_set_duty_percent(unsigned int16 percent);
_bif void pwm_set_duty_percent(unsigned int stream, unsigned int16 percent);
_bif void pwm_set_frequency(unsigned int32 frequency);
_bif void pwm_set_frequency(unsigned int stream, unsigned int32 frequency);

// #use capture() Prototypes:
_bif unsigned int16 get_capture_time(void);
_bif unsigned int16 get_capture_time(unsigned int stream);
_bif int1 get_capture_event(void);
_bif int1 get_capture_event(unsigned int stream);

// Enviroment Prototypes:
//_bif unsigned int getenv(char* cstring);

// Address Prototypes:
#ifndef __ADDRESS__
 #if defined(__PCM__) || define(__PCB__)
  typedef unsigned int16 __ADDRESS__;
 #else
  typedef unsigned int32 __ADDRESS__;
 #endif
#endif
_bif void goto_address(__ADDRESS__ address);
_bif __ADDRESS__ label_address(__ADDRESS__ label);

// Program Memory Prototypes:
_bif void read_program_memory(__ADDRESS__ address, unsigned int* dataptr, unsigned int16 count);
_bif unsigned int16 read_program_eeprom(__ADDRESS__ address);
_bif void erase_program_eeprom(__ADDRESS__ address);
_bif void write_program_memory(__ADDRESS__ address, unsigned int* dataptr, unsigned int16 count);
_bif void write_program_eeprom(__ADDRESS__ address, unsigned int16 data);

// EEPROM Prototypes:
#ifndef __EEADDRESS__
 #if getenv("DATA_EEPROM")>=0x100
  typedef unsigned int16 __EEADDRESS__;
 #else
  typedef unsigned int __EEADDRESS__;
 #endif
#endif
_bif unsigned int read_eeprom(__EEADDRESS__ address);
_bif void write_eeprom(__EEADDRESS__ address, unsigned int value);

// #use touchpad() Prototypes:
_bif void touchpad_state(unsigned int state);
_bif char touchpad_getc(void);
_bif int1 touchpad_hit(void);
////////////////////////////////////////////////////////////////// INT
// Interrupt Functions: ENABLE_INTERRUPTS(), DISABLE_INTERRUPTS(),
//                      CLEAR_INTERRUPT(), INTERRUPT_ACTIVE(),
//                      EXT_INT_EDGE()
// INT Prototypes:
_bif void enable_interrupts(int32 interrupt);
_bif void disable_interrupts(int32 interrupt);
_bif void clear_interrupt(int32 interrupt);
_bif int1 interrupt_active(int32 interrupt);
_bif int1 interrupt_enabled(int32 interrupt);
_bif void ext_int_edge(int source, int edge);
_bif void jump_to_irs(int16 address);
// Constants used in EXT_INT_EDGE() are:
#define L_TO_H              0x40
#define H_TO_L                 0
// Constants used in ENABLE/DISABLE_INTERRUPTS() are:
#define GLOBAL                    0x0BC0
#define PERIPH                    0x0B40
#define INT_EXT_L2H               0x50000B10
#define INT_EXT_H2L               0x60000B10
#define INT_EXT                   0x300B10
#define INT_TIMER0                0x300B20
#define INT_TIMER1                0x309101
#define INT_TIMER2                0x309102
#define INT_CCP1                  0x309104
#define INT_SSP                   0x309108
#define INT_TBE                   0x309110
#define INT_RDA                   0x309120
#define INT_AD                    0x309140
#define INT_TIMER1_GATE            0x309180
#define INT_BUSCOL                0x309208
#define INT_EEPROM                0x309210
#define INT_COMP                  0x309220
#define INT_OSC_FAIL              0x309280
#define INT_RA                    0x30FF0B08
#define INT_RA0                   0x30010B08
#define INT_RA0_L2H               0x10010B08
#define INT_RA0_H2L               0x20010B08
#define INT_RA1                   0x30020B08
#define INT_RA1_L2H               0x10020B08
#define INT_RA1_H2L               0x20020B08
#define INT_RA2                   0x30040B08
#define INT_RA2_L2H               0x10040B08
#define INT_RA2_H2L               0x20040B08
#define INT_RA3                   0x30080B08
#define INT_RA3_L2H               0x10080B08
#define INT_RA3_H2L               0x20080B08
#define INT_RA4                   0x30100B08
#define INT_RA4_L2H               0x10100B08
#define INT_RA4_H2L               0x20100B08
#define INT_RA5                   0x30200B08
#define INT_RA5_L2H               0x10200B08
#define INT_RA5_H2L               0x20200B08

#list
