#ifndef Camino_arch_h
#define Camino_arch_h

#include "Arduino.h"
#include "options.h"



// Architecture flags listed in packages/arduino/hardware/avr/1.8.6/boards.txt
// See also: https://docs.arduino.cc/software/ide-v1/tutorials/arduino-ide-v1-basics/#boards
// Supported by Camino:
//  ATmega1280/2560:
//    #define ARDUINO_AVR_MEGA
//          | ARDUINO_AVR_MEGA2560
//          | ARDUINO_AVR_ADK
//    #define CAMINO_SERIAL_PORT 0, 1, 2, 3
//
//  ATmega132/168/328P:
//    #define ARDUINO_AVR_UNO
//          | ARDUINO_AVR_UNO_WIFI_DEV_ED
//          | ARDUINO_AVR_NANO
//          | ARDUINO_AVR_MINI
//          | ARDUINO_AVR_ETHERNET
//          | ARDUINO_AVR_FIO
//          | ARDUINO_AVR_BT
//          | ARDUINO_AVR_PRO
//          | ARDUINO_AVR_LILYPAD
//          | ARDUINO_AVR_DUEMILANOVE
//    #define CAMINO_SERIAL_PORT 0
//
// Not officially supported (file a PR!):
//  ATmega32u4:
//    #define ARDUINO_AVR_LEONARDO
//          | ARDUINO_AVR_LEONARDO_ETH
//          | ARDUINO_AVR_MICRO
//          | ARDUINO_AVR_ESPLORA
//          | ARDUINO_AVR_YUN
//          | ARDUINO_AVR_YUNMINI
//          | ARDUINO_AVR_LILYPAD_USB
//    #define CAMINO_SERIAL_PORT 1
//
//  ATtiny85:
//    #define ARDUINO_AVR_GEMMA
//
//  Others:
//    #define ARDUINO_AVR_CIRCUITPLAY
//    #define ARDUINO_AVR_INDUSTRIAL101
//    #define ARDUINO_AVR_LININO_ONE
//    #define ARDUINO_AVR_ROBOT_CONTROL
//    #define ARDUINO_AVR_ROBOT_MOTOR
//    #define ARDUINO_AVR_NG

#if defined(ARDUINO_AVR_UNO) \
  || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED) \
  || defined(ARDUINO_AVR_NANO) \
  || defined(ARDUINO_AVR_MINI) \
  || defined(ARDUINO_AVR_ETHERNET) \
  || defined(ARDUINO_AVR_FIO) \
  || defined(ARDUINO_AVR_BT) \
  || defined(ARDUINO_AVR_PRO) \
  || defined(ARDUINO_AVR_LILYPAD) \
  || defined(ARDUINO_AVR_DUEMILANOVE)
  #if CAMINO_SERIAL_PORT != 0
    #error "ATmega132/168/328P: PORT must be 0"
  #endif
  #define Camino_InitPort(baudRate) do {\
    /* configure baudrate registers of UART */ \
    uint16_t clockRate = (uint16_t) ((F_CPU / (8L * baudRate)) - 1L); \
    UBRR0H = clockRate >> 8; \
    UBRR0L = clockRate & 0xff; \
    sbi(UCSR0A, U2X0);   /* enable double rate (2X flag) */ \
    sbi(UCSR0B, RXEN0);  /* enable RX interrupt */ \
    sbi(UCSR0B, TXEN0);  /* enable TX interrupt */ \
    sbi(UCSR0B, RXCIE0); /* enable serial receive complete interrupt */ \
    UCSR0C = 0x06;       /* set 8 bit, no parity, 1 stop */ \
  } while(0)
  #define Camino_SendByte(v) do { \
    UDR0 = v; \
  } while(0)
  #define Camino_EnableByteSentISR() sbi(UCSR0B, UDRIE0)
  #define Camino_DisableByteSentISR() cbi(UCSR0B, UDRIE0)
  #define Camino_ReadByte() (UDR0)
  #define Camino_ByteReadable_vect USART_RX_vect
  #define Camino_ByteSent_vect USART_UDRE_vect
#elif defined(ARDUINO_AVR_MEGA) \
  || defined(ARDUINO_AVR_MEGA2560) \
  || defined(ARDUINO_AVR_ADK)
  #if CAMINO_SERIAL_PORT == 0
    #define Camino_InitPort(baudRate) do {\
      /* configure baudrate registers of UART */ \
      uint16_t clockRate = (uint16_t) ((F_CPU / (8L * baudRate)) - 1L); \
      UBRR0H = clockRate >> 8; \
      UBRR0L = clockRate & 0xff; \
      sbi(UCSR0A, U2X0);   /* enable double rate (2X flag) */ \
      sbi(UCSR0B, RXEN0);  /* enable RX interrupt */ \
      sbi(UCSR0B, TXEN0);  /* enable TX interrupt */ \
      sbi(UCSR0B, RXCIE0); /* enable serial receive complete interrupt */ \
      UCSR0C = 0x06;       /* set 8 bit, no parity, 1 stop */ \
    } while(0)
    #define Camino_SendByte(v) do { \
      UDR0 = v; \
    } while(0)
    #define Camino_EnableByteSentISR() sbi(UCSR0B, UDRIE0)
    #define Camino_DisableByteSentISR() cbi(UCSR0B, UDRIE0)
    #define Camino_ReadByte() (UDR0)
    #define Camino_ByteReadable_vect USART0_RX_vect
    #define Camino_ByteSent_vect USART0_UDRE_vect
  #elif CAMINO_SERIAL_PORT == 1
    #define Camino_InitPort(baudRate) do {\
      /* configure baudrate registers of UART */ \
      uint16_t clockRate = (uint16_t) ((F_CPU / (8L * baudRate)) - 1L); \
      UBRR1H = clockRate >> 8; \
      UBRR1L = clockRate & 0xff; \
      sbi(UCSR1A, U2X1);   /* enable double rate (2X flag) */ \
      sbi(UCSR1B, RXEN1);  /* enable RX interrupt */ \
      sbi(UCSR1B, TXEN1);  /* enable TX interrupt */ \
      sbi(UCSR1B, RXCIE1); /* enable serial receive complete interrupt */ \
      UCSR1C = 0x06;       /* set 8 bit, no parity, 1 stop */ \
    } while(0)
    #define Camino_SendByte(v) do { \
      UDR0 = v; \
    } while(0)
    #define Camino_EnableByteSentISR() sbi(UCSR1B, UDRIE1)
    #define Camino_DisableByteSentISR() cbi(UCSR1B, UDRIE1)
    #define Camino_ReadByte() (UDR1)
    #define Camino_ByteReadable_vect USART1_RX_vect
    #define Camino_ByteSent_vect USART1_UDRE_vect
  #elif CAMINO_SERIAL_PORT == 2
    #define Camino_InitPort(baudRate) do {\
      /* configure baudrate registers of UART */ \
      uint16_t clockRate = (uint16_t) ((F_CPU / (8L * baudRate)) - 1L); \
      UBRR2H = clockRate >> 8; \
      UBRR2L = clockRate & 0xff; \
      sbi(UCSR2A, U2X2);   /* enable double rate (2X flag) */ \
      sbi(UCSR2B, RXEN2);  /* enable RX interrupt */ \
      sbi(UCSR2B, TXEN2);  /* enable TX interrupt */ \
      sbi(UCSR2B, RXCIE2); /* enable serial receive complete interrupt */ \
      UCSR2C = 0x06;       /* set 8 bit, no parity, 1 stop */ \
    } while(0)
    #define Camino_SendByte(v) do { \
      UDR0 = v; \
    } while(0)
    #define Camino_EnableByteSentISR() sbi(UCSR2B, UDRIE2)
    #define Camino_DisableByteSentISR() cbi(UCSR2B, UDRIE2)
    #define Camino_ReadByte() (UDR2)
    #define Camino_ByteReadable_vect USART2_RX_vect
    #define Camino_ByteSent_vect USART2_UDRE_vect
  #elif CAMINO_SERIAL_PORT == 3
    #define Camino_InitPort(baudRate) do {\
      /* configure baudrate registers of UART */ \
      uint16_t clockRate = (uint16_t) ((F_CPU / (8L * baudRate)) - 1L); \
      UBRR3H = clockRate >> 8; \
      UBRR3L = clockRate & 0xff; \
      sbi(UCSR3A, U2X3);   /* enable double rate (2X flag) */ \
      sbi(UCSR3B, RXEN3);  /* enable RX interrupt */ \
      sbi(UCSR3B, TXEN3);  /* enable TX interrupt */ \
      sbi(UCSR3B, RXCIE3); /* enable serial receive complete interrupt */ \
      UCSR3C = 0x06;       /* set 8 bit, no parity, 1 stop */ \
    } while(0)
    #define Camino_SendByte(v) do { \
      UDR0 = v; \
    } while(0)
    #define Camino_EnableByteSentISR() sbi(UCSR3B, UDRIE3)
    #define Camino_DisableByteSentISR() cbi(UCSR3B, UDRIE3)
    #define Camino_ReadByte() (UDR3)
    #define Camino_ByteReadable_vect USART3_RX_vect
    #define Camino_ByteSent_vect USART3_UDRE_vect
  #else
    #error "ATmega1280/2560: PORT must be 0, 1, 2, or 3"
  #endif
#elif defined(ARDUINO_AVR_LEONARDO) \
  || defined(ARDUINO_AVR_LEONARDO_ETH) \
  || defined(ARDUINO_AVR_MICRO) \
  || defined(ARDUINO_AVR_ESPLORA) \
  || defined(ARDUINO_AVR_YUN) \
  || defined(ARDUINO_AVR_YUNMINI) \
  || defined(ARDUINO_AVR_LILYPAD_USB)
  #error "ATmega32u4: Not supported. See arch.h to add support and file a PR!"
#elif defined(ARDUINO_AVR_NANO_EVERY)
  #define USB 3
  #ifdef IN_CAMINO_LIBRARY
    extern USART_t& Camino_USART;
    extern const register8_t Camino_USART_Mux;
  #else 
    #if CAMINO_SERIAL_PORT == 1
      ISR_ALIAS(USART1_DRE_vect, Camino_ByteSent_vect);
      ISR_ALIAS(USART1_RXC_vect, Camino_ByteReadable_vect);
      USART_t& Camino_USART = USART1;
      const register8_t Camino_USART_Mux = PORTMUX_USART1_enum::PORTMUX_USART1_ALT1_gc;
    #elif CAMINO_SERIAL_PORT == 3
      ISR_ALIAS(USART3_DRE_vect, Camino_ByteSent_vect);
      ISR_ALIAS(USART3_RXC_vect, Camino_ByteReadable_vect);
      USART_t& Camino_USART = USART3;
      const register8_t Camino_USART_Mux = PORTMUX_USART3_enum::PORTMUX_USART3_ALT1_gc;
    #else
      #error "Nano Every: For USB serial PORT must be USB (3), for Pins PORT must be 1."
    #endif
  #endif
#elif defined(ARDUINO_AVR_GEMMA)
  #error "ATtiny85: Not supported. See arch.h to add support and file a PR!"
#elif defined(ARDUINO_SAM_DUE)
  #ifdef IN_CAMINO_LIBRARY
    extern Stream& SerialStream;
    extern void (*serialBegin)(unsigned long baud);
    extern int (*serialAvailableForWrite)();
  #else
    extern void serialEvent();
    #define USB_P 0
    #define USB_N 4
    #if CAMINO_SERIAL_PORT == 0
      Stream& SerialStream = Serial;
      auto serialBegin = static_cast<void(*)(unsigned long)>([](unsigned long baud)-> void {Serial.begin(baud);});
      auto serialAvailableForWrite = static_cast<int(*)()>([]()->int {return Serial.availableForWrite();});
    #elif CAMINO_SERIAL_PORT == 1
      Stream& SerialStream = Serial1;
      auto serialBegin = static_cast<void(*)(unsigned long)>([](unsigned long baud)-> void {Serial1.begin(baud);});
      auto serialAvailableForWrite = static_cast<int(*)()>([]()->int {return Serial1.availableForWrite();;});
    #elif CAMINO_SERIAL_PORT == 2
      Stream& SerialStream = Serial2;
      auto serialBegin = static_cast<void(*)(unsigned long)>([](unsigned long baud)-> void {Serial2.begin(baud);});
      auto serialAvailableForWrite = static_cast<int(*)()>([]()->int {return Serial2.availableForWrite();});
    #elif CAMINO_SERIAL_PORT == 3
      Stream& SerialStream = Serial3;
      auto serialBegin = static_cast<void(*)(unsigned long)>([](unsigned long baud)-> void {Serial3.begin(baud);});
      auto serialAvailableForWrite = static_cast<int(*)()>([]()->int {return Serial3.availableForWrite();});
    #elif CAMINO_SERIAL_PORT == 4
      Stream& SerialStream = SerialUSB;
      auto serialBegin = static_cast<void(*)(unsigned long)>([](unsigned long baud)-> void {SerialUSB.begin(baud);});
      auto serialAvailableForWrite = static_cast<int(*)()>([]()->int {return SerialUSB.availableForWrite();});
    #else 
      #error "Due: Native USB Serial PORT: USB_N (4), Programmer Serial PORT: USB_P (0)"
    #endif
  #endif
#else
  # error "Unsupported board. See arch.h to add support and file a PR!"
#endif

#endif
