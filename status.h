#ifndef _STATUS_H_
#define _STATUS_H_

#define MASK_NEGATIVO 0x80
#define MASK_ACARREO 0X100

#define MASK_ACARREO_U8 0x01

#define POSICION_NEGATIVO 7
#define POSICION_ACARREO 0

#define MASK_CARRY 0x01
#define MASK_ZERO 0x02
#define MASK_INTERRUPT_DISABLE 0x04
#define MASK_DECIMAL 0x08
#define MASK_BREAK 0x10
#define MASK_GUION 0x20
#define MASK_OVERFLOW 0x40
#define MASK_NEGATIVE 0x80

typedef enum {
			  CARRY,
			  ZERO,
			  INTERRUPT_DISABLE,
			  DECIMAL,
              BREAK,
              GUION,
              OVERFLOW,
              NEGATIVE,
}flag_t;

bool get_status(uint8_t *reg, flag_t flag);
void set_status(uint8_t *reg, flag_t flag, bool status);
void set_zero(uint8_t *reg, uint8_t res);
void set_negative(uint8_t *reg, uint8_t res);
void set_carry(uint8_t *reg, uint16_t res);
void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res);
void rotate_left(uint8_t *reg, uint8_t *x);
void rotate_right(uint8_t *reg, uint8_t *x);

#endif
