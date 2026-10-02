#ifndef STC15_BITSH
#define STC15_BITSH
/***************************************************************************************************
                                Macros for Bit Manipulation
 ****************************************************************************************************/

#define bit_shift_right(val, shift_size)                    (val >> shift_size)
#define bit_shift_left(val, shift_size)                     (val << shift_size)
#define bit_mask(bit_pos)                                   bit_shift_left(1, bit_pos)

#define bit_set(val, bit_mask_val)                          (val |= bit_mask_val)
#define bit_clr(val, bit_mask_val)                          (val &= ~bit_mask_val)
#define bit_tgl(val, bit_mask_val)                          (val ^= bit_mask_val)

#define get_reg(val, bit_mask_val)                          (val & bit_mask_val)

#define test_if_bit_set(val, bit_mask_val)                  (((val) & (bit_mask_val)) == bit_mask_val)
#define test_if_bit_cleared(val, bit_mask_val)              (((val) & (bit_mask_val)) == 0)

/**************************************************************************************************/


/***************************************************************************************************
                           Definition of common Bit-Masks
 ***************************************************************************************************/

#define SBIT0            0x01
#define SBIT1            0x02
#define SBIT2            0x04
#define SBIT3            0x08
#define SBIT4            0x10
#define SBIT5            0x20
#define SBIT6            0x40
#define SBIT7            0x80

/**************************************************************************************************/
#endif