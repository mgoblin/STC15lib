#ifndef STC15_UART1SHAREDH
#define STC15_UART1SHAREDH

#define uart1_send_byte(byte)                   \
do                                              \
{                                               \
    SBUF = byte;                                \
    while (!TI);                                \
    TI = 0;                                     \
} while (0)

#define uart1_receive_byte(byte_ptr)            \
do {                                            \
	while(!RI);                                 \
    *byte_ptr = SBUF;                           \
	RI=0;                                       \
} while (0)


#endif
