#ifndef STC15_BITSH
#define STC15_BITSH
/***************************************************************************************************
                                Macros for Bit Manipulation
 ****************************************************************************************************/

#define bit_shift_right(val, shift_size)                    (val >> shift_size)
#define bit_shift_left(val, shift_size)                     (val << shift_size)
#define bit_mask(bit_pos)                                   bit_shift_left(1, bit_pos)

#define bit_set(val, bit_val)                               (val |= bit_mask(bit_val))
#define bit_clr(val, bit_val)                               (val &= (~bit_mask(bit_val)))
#define bit_tgl(val, bit_val)                               (val ^= bit_mask(bit_val))
#define get_bit(val, bit_val)                               (val & bit_mask(bit_val))
#define get_reg(val, msk)                                   (val & msk)

#define set_bits(reg, val, pos)                             (reg |= bit_shift_left(val, pos))    
#define clr_bits(reg, val, pos)                             (reg &= ~bit_shift_left(val, pos)) 

#define or_mask(val, msk)                                   (val |= msk)
#define and_mask(val, msk)                                  (val &= msk)   

#define test_if_bit_set(val, bit_val)                       (get_bit(val, bit_val) != 0)
#define test_if_bit_cleared(val, bit_val)                   (get_bit(val, bit_val) == 0)

#define test_if_all_bits_set(val, msk)                      (get_reg(val, msk) == msk)
#define test_if_any_bit_set(val, msk)                       (get_reg(val, msk) != 0)

/**************************************************************************************************/


/***************************************************************************************************
                           Definition of common Bit-Masks
 ***************************************************************************************************/

#define BIT0            bit_mask(0)
#define BIT1            bit_mask(1)
#define BIT2            bit_mask(2)
#define BIT3            bit_mask(3)
#define BIT4            bit_mask(4)
#define BIT5            bit_mask(5)
#define BIT6            bit_mask(6)
#define BIT7            bit_mask(7)
#define BIT8            bit_mask(8)
#define BIT9            bit_mask(9)
#define BIT10           bit_mask(10)
#define BIT11           bit_mask(11)
#define BIT12           bit_mask(12)
#define BIT13           bit_mask(13)
#define BIT14           bit_mask(14)
#define BIT15           bit_mask(15)
#define BIT16           bit_mask(16)
#define BIT17           bit_mask(17)
#define BIT18           bit_mask(18)
#define BIT19           bit_mask(19)
#define BIT20           bit_mask(20)
#define BIT21           bit_mask(21)
#define BIT22           bit_mask(22)
#define BIT23           bit_mask(23)
#define BIT24           bit_mask(24)
#define BIT25           bit_mask(25)
#define BIT26           bit_mask(26)
#define BIT27           bit_mask(27)
#define BIT28           bit_mask(28)
#define BIT29           bit_mask(29)
#define BIT30           bit_mask(30)
#define BIT31           bit_mask(31)

/**************************************************************************************************/
#endif