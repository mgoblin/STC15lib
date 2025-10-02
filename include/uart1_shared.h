#ifndef STC15_UART1SHAREDH
#define STC15_UART1SHAREDH

/**
 * @brief Sends a single byte over UART1.
 * 
 * @details 
 * Transmits the specified byte through UART1.
 * The function blocks until the byte is fully transmitted.
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for transmission.
 *
 * 
 * @param byte uint8_t byte to be sent
 * 
 * @ingroup uart
 */
#define uart1_send_byte(byte)                   \
do                                              \
{                                               \
    SBUF = byte;                                \
    while (!TI);                                \
    TI = 0;                                     \
} while (0)

/**
 * @brief Receives a single byte over UART1.
 * 
 * @details 
 * Receives byte through UART1 configured.
 * The function blocks until the byte is fully received.
 * 
 * @param byte_ptr byte* uintT8_t the 8-bit data value to be received (0-255).
 * 
 * @note Requires UART1 to be previously initialized and started.
 * @note Uses polling (blocking) method for receveive.
 *
 * 
 * @ingroup uart
 */
#define uart1_receive_byte(byte_ptr)            \
do {                                            \
	while(!RI);                                 \
    *byte_ptr = SBUF;                           \
	RI=0;                                       \
} while (0)


#endif
