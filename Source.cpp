// STOP is the only instruction that is >1 byte and has no immediate (aside form CB set)
// CB set has no immediates, and are all 2 bytes each

#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdio.h>
#include <malloc.h>

typedef uint8_t u8;
typedef uint16_t u16;

struct dis_line
{
	u16 _address;
	int _size;
	u8 _bytes[3];
	char _text[20];
	int _category; // {'control misc' : 0, 'control br' : 1, 'x16 lsm' : 2, 'x8 alu' : 3, 'x8 rsb' : 4, 'x8 lsm' : 5, 'unused' : 6, 'x16 alu' : 7}
};


dis_line disassemble(u8* bytes, u16 pc)
{
	u8 b1 = bytes[pc + 0];
	u8 b2 = bytes[pc + 1];
	u8 b3 = bytes[pc + 2];

	switch (b1)
	{
	case 0x00: return dis_line{ pc, 1, {b1,b2,b3},"NOP\n", 0 };
	case 0x01: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 2 }; sprintf(l._text, "LD BC,$%02x%02x\n", b3, b2); return l; }
	case 0x02: return dis_line{ pc, 1, {b1,b2,b3},"LD (BC),A\n", 5 };
	case 0x03: return dis_line{ pc, 1, {b1,b2,b3},"INC BC\n", 7 };
	case 0x04: return dis_line{ pc, 1, {b1,b2,b3},"INC B\n", 3 };
	case 0x05: return dis_line{ pc, 1, {b1,b2,b3},"DEC B\n", 3 };
	case 0x06: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD B,$%02x\n", b2); return l; }
	case 0x07: return dis_line{ pc, 1, {b1,b2,b3},"RLCA\n", 4 };
	case 0x08: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 2 }; sprintf(l._text, "LD ($%02x%02x),SP\n", b3, b2); return l; }
	case 0x09: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,BC\n", 7 };
	case 0x0A: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(BC)\n", 5 };
	case 0x0B: return dis_line{ pc, 1, {b1,b2,b3},"DEC BC\n", 7 };
	case 0x0C: return dis_line{ pc, 1, {b1,b2,b3},"INC C\n", 3 };
	case 0x0D: return dis_line{ pc, 1, {b1,b2,b3},"DEC C\n", 3 };
	case 0x0E: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD C,$%02x\n", b2); return l; }
	case 0x0F: return dis_line{ pc, 1, {b1,b2,b3},"RRCA\n", 4 };
	case 0x10: return dis_line{ pc, 2, {b1,b2,b3},"STOP\n" , 0 };
	case 0x11: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 2 }; sprintf(l._text, "LD DE,$%02x%02x\n", b3, b2); return l; }
	case 0x12: return dis_line{ pc, 1, {b1,b2,b3},"LD (DE),A\n", 5 };
	case 0x13: return dis_line{ pc, 1, {b1,b2,b3},"INC DE\n", 7 };
	case 0x14: return dis_line{ pc, 1, {b1,b2,b3},"INC D\n", 3 };
	case 0x15: return dis_line{ pc, 1, {b1,b2,b3},"DEC D\n", 3 };
	case 0x16: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD D,$%02x\n", b2); return l; }
	case 0x17: return dis_line{ pc, 1, {b1,b2,b3},"RLA\n", 4 };
	case 0x18: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JR $%02x [%hhi]\n", b2, b2); return l; }
	case 0x19: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,DE\n", 7 };
	case 0x1A: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(DE)\n", 5 };
	case 0x1B: return dis_line{ pc, 1, {b1,b2,b3},"DEC DE\n", 7 };
	case 0x1C: return dis_line{ pc, 1, {b1,b2,b3},"INC E\n", 3 };
	case 0x1D: return dis_line{ pc, 1, {b1,b2,b3},"DEC E\n", 3 };
	case 0x1E: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD E,$%02x\n", b2); return l; }
	case 0x1F: return dis_line{ pc, 1, {b1,b2,b3},"RRA\n", 4 };
	case 0x20: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JR NZ,$%02x [%hhi]\n", b2, b2); return l; }
	case 0x21: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 2 }; sprintf(l._text, "LD HL,$%02x%02x\n", b3, b2); return l; }
	case 0x22: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL+),A\n", 5 };
	case 0x23: return dis_line{ pc, 1, {b1,b2,b3},"INC HL\n", 7 };
	case 0x24: return dis_line{ pc, 1, {b1,b2,b3},"INC H\n", 3 };
	case 0x25: return dis_line{ pc, 1, {b1,b2,b3},"DEC H\n", 3 };
	case 0x26: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD H,$%02x\n", b2); return l; }
	case 0x27: return dis_line{ pc, 1, {b1,b2,b3},"DAA\n", 3 };
	case 0x28: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JR Z,$%02x [%hhi]\n", b2, b2); return l; }
	case 0x29: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,HL\n", 7 };
	case 0x2A: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(HL+)\n", 5 };
	case 0x2B: return dis_line{ pc, 1, {b1,b2,b3},"DEC HL\n", 7 };
	case 0x2C: return dis_line{ pc, 1, {b1,b2,b3},"INC L\n", 3 };
	case 0x2D: return dis_line{ pc, 1, {b1,b2,b3},"DEC L\n", 3 };
	case 0x2E: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD L,$%02x\n", b2); return l; }
	case 0x2F: return dis_line{ pc, 1, {b1,b2,b3},"CPL\n", 3 };
	case 0x30: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JR NC,$%02x [%hhi]\n", b2, b2); return l; }
	case 0x31: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 2 }; sprintf(l._text, "LD SP,$%02x%02x\n", b3, b2); return l; }
	case 0x32: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL-),A\n", 5 };
	case 0x33: return dis_line{ pc, 1, {b1,b2,b3},"INC SP\n", 7 };
	case 0x34: return dis_line{ pc, 1, {b1,b2,b3},"INC (HL)\n", 3 };
	case 0x35: return dis_line{ pc, 1, {b1,b2,b3},"DEC (HL)\n", 3 };
	case 0x36: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD (HL),$%02x\n", b2); return l; }
	case 0x37: return dis_line{ pc, 1, {b1,b2,b3},"SCF\n", 3 };
	case 0x38: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JR C,$%02x [%hhi]\n", b2, b2); return l; }
	case 0x39: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,SP\n", 7 };
	case 0x3A: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(HL-)\n", 5 };
	case 0x3B: return dis_line{ pc, 1, {b1,b2,b3},"DEC SP\n", 7 };
	case 0x3C: return dis_line{ pc, 1, {b1,b2,b3},"INC A\n", 3 };
	case 0x3D: return dis_line{ pc, 1, {b1,b2,b3},"DEC A\n", 3 };
	case 0x3E: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD A,$%02x\n", b2); return l; }
	case 0x3F: return dis_line{ pc, 1, {b1,b2,b3},"CCF\n", 3 };
	case 0x40: return dis_line{ pc, 1, {b1,b2,b3},"LD B,B\n", 5 };
	case 0x41: return dis_line{ pc, 1, {b1,b2,b3},"LD B,C\n", 5 };
	case 0x42: return dis_line{ pc, 1, {b1,b2,b3},"LD B,D\n", 5 };
	case 0x43: return dis_line{ pc, 1, {b1,b2,b3},"LD B,E\n", 5 };
	case 0x44: return dis_line{ pc, 1, {b1,b2,b3},"LD B,H\n", 5 };
	case 0x45: return dis_line{ pc, 1, {b1,b2,b3},"LD B,L\n", 5 };
	case 0x46: return dis_line{ pc, 1, {b1,b2,b3},"LD B,(HL)\n", 5 };
	case 0x47: return dis_line{ pc, 1, {b1,b2,b3},"LD B,A\n", 5 };
	case 0x48: return dis_line{ pc, 1, {b1,b2,b3},"LD C,B\n", 5 };
	case 0x49: return dis_line{ pc, 1, {b1,b2,b3},"LD C,C\n", 5 };
	case 0x4A: return dis_line{ pc, 1, {b1,b2,b3},"LD C,D\n", 5 };
	case 0x4B: return dis_line{ pc, 1, {b1,b2,b3},"LD C,E\n", 5 };
	case 0x4C: return dis_line{ pc, 1, {b1,b2,b3},"LD C,H\n", 5 };
	case 0x4D: return dis_line{ pc, 1, {b1,b2,b3},"LD C,L\n", 5 };
	case 0x4E: return dis_line{ pc, 1, {b1,b2,b3},"LD C,(HL)\n", 5 };
	case 0x4F: return dis_line{ pc, 1, {b1,b2,b3},"LD C,A\n", 5 };
	case 0x50: return dis_line{ pc, 1, {b1,b2,b3},"LD D,B\n", 5 };
	case 0x51: return dis_line{ pc, 1, {b1,b2,b3},"LD D,C\n", 5 };
	case 0x52: return dis_line{ pc, 1, {b1,b2,b3},"LD D,D\n", 5 };
	case 0x53: return dis_line{ pc, 1, {b1,b2,b3},"LD D,E\n", 5 };
	case 0x54: return dis_line{ pc, 1, {b1,b2,b3},"LD D,H\n", 5 };
	case 0x55: return dis_line{ pc, 1, {b1,b2,b3},"LD D,L\n", 5 };
	case 0x56: return dis_line{ pc, 1, {b1,b2,b3},"LD D,(HL)\n", 5 };
	case 0x57: return dis_line{ pc, 1, {b1,b2,b3},"LD D,A\n", 5 };
	case 0x58: return dis_line{ pc, 1, {b1,b2,b3},"LD E,B\n", 5 };
	case 0x59: return dis_line{ pc, 1, {b1,b2,b3},"LD E,C\n", 5 };
	case 0x5A: return dis_line{ pc, 1, {b1,b2,b3},"LD E,D\n", 5 };
	case 0x5B: return dis_line{ pc, 1, {b1,b2,b3},"LD E,E\n", 5 };
	case 0x5C: return dis_line{ pc, 1, {b1,b2,b3},"LD E,H\n", 5 };
	case 0x5D: return dis_line{ pc, 1, {b1,b2,b3},"LD E,L\n", 5 };
	case 0x5E: return dis_line{ pc, 1, {b1,b2,b3},"LD E,(HL)\n", 5 };
	case 0x5F: return dis_line{ pc, 1, {b1,b2,b3},"LD E,A\n", 5 };
	case 0x60: return dis_line{ pc, 1, {b1,b2,b3},"LD H,B\n", 5 };
	case 0x61: return dis_line{ pc, 1, {b1,b2,b3},"LD H,C\n", 5 };
	case 0x62: return dis_line{ pc, 1, {b1,b2,b3},"LD H,D\n", 5 };
	case 0x63: return dis_line{ pc, 1, {b1,b2,b3},"LD H,E\n", 5 };
	case 0x64: return dis_line{ pc, 1, {b1,b2,b3},"LD H,H\n", 5 };
	case 0x65: return dis_line{ pc, 1, {b1,b2,b3},"LD H,L\n", 5 };
	case 0x66: return dis_line{ pc, 1, {b1,b2,b3},"LD H,(HL)\n", 5 };
	case 0x67: return dis_line{ pc, 1, {b1,b2,b3},"LD H,A\n", 5 };
	case 0x68: return dis_line{ pc, 1, {b1,b2,b3},"LD L,B\n", 5 };
	case 0x69: return dis_line{ pc, 1, {b1,b2,b3},"LD L,C\n", 5 };
	case 0x6A: return dis_line{ pc, 1, {b1,b2,b3},"LD L,D\n", 5 };
	case 0x6B: return dis_line{ pc, 1, {b1,b2,b3},"LD L,E\n", 5 };
	case 0x6C: return dis_line{ pc, 1, {b1,b2,b3},"LD L,H\n", 5 };
	case 0x6D: return dis_line{ pc, 1, {b1,b2,b3},"LD L,L\n", 5 };
	case 0x6E: return dis_line{ pc, 1, {b1,b2,b3},"LD L,(HL)\n", 5 };
	case 0x6F: return dis_line{ pc, 1, {b1,b2,b3},"LD L,A\n", 5 };
	case 0x70: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),B\n", 5 };
	case 0x71: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),C\n", 5 };
	case 0x72: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),D\n", 5 };
	case 0x73: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),E\n", 5 };
	case 0x74: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),H\n", 5 };
	case 0x75: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),L\n", 5 };
	case 0x76: return dis_line{ pc, 1, {b1,b2,b3},"HALT\n", 0 };
	case 0x77: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),A\n", 5 };
	case 0x78: return dis_line{ pc, 1, {b1,b2,b3},"LD A,B\n", 5 };
	case 0x79: return dis_line{ pc, 1, {b1,b2,b3},"LD A,C\n", 5 };
	case 0x7A: return dis_line{ pc, 1, {b1,b2,b3},"LD A,D\n", 5 };
	case 0x7B: return dis_line{ pc, 1, {b1,b2,b3},"LD A,E\n", 5 };
	case 0x7C: return dis_line{ pc, 1, {b1,b2,b3},"LD A,H\n", 5 };
	case 0x7D: return dis_line{ pc, 1, {b1,b2,b3},"LD A,L\n", 5 };
	case 0x7E: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(HL)\n", 5 };
	case 0x7F: return dis_line{ pc, 1, {b1,b2,b3},"LD A,A\n", 5 };
	case 0x80: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,B\n", 3 };
	case 0x81: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,C\n", 3 };
	case 0x82: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,D\n", 3 };
	case 0x83: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,E\n", 3 };
	case 0x84: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,H\n", 3 };
	case 0x85: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,L\n", 3 };
	case 0x86: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,(HL)\n", 3 };
	case 0x87: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,A\n", 3 };
	case 0x88: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,B\n", 3 };
	case 0x89: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,C\n", 3 };
	case 0x8A: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,D\n", 3 };
	case 0x8B: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,E\n", 3 };
	case 0x8C: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,H\n", 3 };
	case 0x8D: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,L\n", 3 };
	case 0x8E: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,(HL)\n", 3 };
	case 0x8F: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,A\n", 3 };
	case 0x90: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,B\n", 3 };
	case 0x91: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,C\n", 3 };
	case 0x92: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,D\n", 3 };
	case 0x93: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,E\n", 3 };
	case 0x94: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,H\n", 3 };
	case 0x95: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,L\n", 3 };
	case 0x96: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,(HL)\n", 3 };
	case 0x97: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,A\n", 3 };
	case 0x98: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,B\n", 3 };
	case 0x99: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,C\n", 3 };
	case 0x9A: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,D\n", 3 };
	case 0x9B: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,E\n", 3 };
	case 0x9C: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,H\n", 3 };
	case 0x9D: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,L\n", 3 };
	case 0x9E: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,(HL)\n", 3 };
	case 0x9F: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,A\n", 3 };
	case 0xA0: return dis_line{ pc, 1, {b1,b2,b3},"AND A,B\n", 3 };
	case 0xA1: return dis_line{ pc, 1, {b1,b2,b3},"AND A,C\n", 3 };
	case 0xA2: return dis_line{ pc, 1, {b1,b2,b3},"AND A,D\n", 3 };
	case 0xA3: return dis_line{ pc, 1, {b1,b2,b3},"AND A,E\n", 3 };
	case 0xA4: return dis_line{ pc, 1, {b1,b2,b3},"AND A,H\n", 3 };
	case 0xA5: return dis_line{ pc, 1, {b1,b2,b3},"AND A,L\n", 3 };
	case 0xA6: return dis_line{ pc, 1, {b1,b2,b3},"AND A,(HL)\n", 3 };
	case 0xA7: return dis_line{ pc, 1, {b1,b2,b3},"AND A,A\n", 3 };
	case 0xA8: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,B\n", 3 };
	case 0xA9: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,C\n", 3 };
	case 0xAA: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,D\n", 3 };
	case 0xAB: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,E\n", 3 };
	case 0xAC: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,H\n", 3 };
	case 0xAD: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,L\n", 3 };
	case 0xAE: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,(HL)\n", 3 };
	case 0xAF: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,A\n", 3 };
	case 0xB0: return dis_line{ pc, 1, {b1,b2,b3},"OR A,B\n", 3 };
	case 0xB1: return dis_line{ pc, 1, {b1,b2,b3},"OR A,C\n", 3 };
	case 0xB2: return dis_line{ pc, 1, {b1,b2,b3},"OR A,D\n", 3 };
	case 0xB3: return dis_line{ pc, 1, {b1,b2,b3},"OR A,E\n", 3 };
	case 0xB4: return dis_line{ pc, 1, {b1,b2,b3},"OR A,H\n", 3 };
	case 0xB5: return dis_line{ pc, 1, {b1,b2,b3},"OR A,L\n", 3 };
	case 0xB6: return dis_line{ pc, 1, {b1,b2,b3},"OR A,(HL)\n", 3 };
	case 0xB7: return dis_line{ pc, 1, {b1,b2,b3},"OR A,A\n", 3 };
	case 0xB8: return dis_line{ pc, 1, {b1,b2,b3},"CP A,B\n", 3 };
	case 0xB9: return dis_line{ pc, 1, {b1,b2,b3},"CP A,C\n", 3 };
	case 0xBA: return dis_line{ pc, 1, {b1,b2,b3},"CP A,D\n", 3 };
	case 0xBB: return dis_line{ pc, 1, {b1,b2,b3},"CP A,E\n", 3 };
	case 0xBC: return dis_line{ pc, 1, {b1,b2,b3},"CP A,H\n", 3 };
	case 0xBD: return dis_line{ pc, 1, {b1,b2,b3},"CP A,L\n", 3 };
	case 0xBE: return dis_line{ pc, 1, {b1,b2,b3},"CP A,(HL)\n", 3 };
	case 0xBF: return dis_line{ pc, 1, {b1,b2,b3},"CP A,A\n", 3 };
	case 0xC0: return dis_line{ pc, 1, {b1,b2,b3},"RET NZ\n", 1 };
	case 0xC1: return dis_line{ pc, 1, {b1,b2,b3},"POP BC\n", 2 };
	case 0xC2: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JP NZ,$%02x%02x\n", b3, b2); return l; }
	case 0xC3: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JP $%02x%02x\n", b3, b2); return l; }
	case 0xC4: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "CALL NZ,$%02x%02x\n", b3, b2); return l; }
	case 0xC5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH BC\n", 2 };
	case 0xC6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "ADD A,$%02x\n", b2); return l; }
	case 0xC7: return dis_line{ pc, 1, {b1,b2,b3},"RST 00h\n", 1 };
	case 0xC8: return dis_line{ pc, 1, {b1,b2,b3},"RET Z\n", 1 };
	case 0xC9: return dis_line{ pc, 1, {b1,b2,b3},"RET\n", 1 };
	case 0xCA: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JP Z,$%02x%02x\n", b3, b2); return l; }
	case 0xCB: 
		switch (b2)
		{
		case 0x00: return dis_line{ pc, 2, {0xCB,0x00,0x00},"RLC B\n" , 4 };
		case 0x01: return dis_line{ pc, 2, {0xCB,0x01,0x00},"RLC C\n" , 4 };
		case 0x02: return dis_line{ pc, 2, {0xCB,0x02,0x00},"RLC D\n" , 4 };
		case 0x03: return dis_line{ pc, 2, {0xCB,0x03,0x00},"RLC E\n" , 4 };
		case 0x04: return dis_line{ pc, 2, {0xCB,0x04,0x00},"RLC H\n" , 4 };
		case 0x05: return dis_line{ pc, 2, {0xCB,0x05,0x00},"RLC L\n" , 4 };
		case 0x06: return dis_line{ pc, 2, {0xCB,0x06,0x00},"RLC (HL)\n" , 4 };
		case 0x07: return dis_line{ pc, 2, {0xCB,0x07,0x00},"RLC A\n" , 4 };
		case 0x08: return dis_line{ pc, 2, {0xCB,0x08,0x00},"RRC B\n" , 4 };
		case 0x09: return dis_line{ pc, 2, {0xCB,0x09,0x00},"RRC C\n" , 4 };
		case 0x0A: return dis_line{ pc, 2, {0xCB,0x0A,0x00},"RRC D\n" , 4 };
		case 0x0B: return dis_line{ pc, 2, {0xCB,0x0B,0x00},"RRC E\n" , 4 };
		case 0x0C: return dis_line{ pc, 2, {0xCB,0x0C,0x00},"RRC H\n" , 4 };
		case 0x0D: return dis_line{ pc, 2, {0xCB,0x0D,0x00},"RRC L\n" , 4 };
		case 0x0E: return dis_line{ pc, 2, {0xCB,0x0E,0x00},"RRC (HL)\n" , 4 };
		case 0x0F: return dis_line{ pc, 2, {0xCB,0x0F,0x00},"RRC A\n" , 4 };
		case 0x10: return dis_line{ pc, 2, {0xCB,0x10,0x00},"RL B\n" , 4 };
		case 0x11: return dis_line{ pc, 2, {0xCB,0x11,0x00},"RL C\n" , 4 };
		case 0x12: return dis_line{ pc, 2, {0xCB,0x12,0x00},"RL D\n" , 4 };
		case 0x13: return dis_line{ pc, 2, {0xCB,0x13,0x00},"RL E\n" , 4 };
		case 0x14: return dis_line{ pc, 2, {0xCB,0x14,0x00},"RL H\n" , 4 };
		case 0x15: return dis_line{ pc, 2, {0xCB,0x15,0x00},"RL L\n" , 4 };
		case 0x16: return dis_line{ pc, 2, {0xCB,0x16,0x00},"RL (HL)\n" , 4 };
		case 0x17: return dis_line{ pc, 2, {0xCB,0x17,0x00},"RL A\n" , 4 };
		case 0x18: return dis_line{ pc, 2, {0xCB,0x18,0x00},"RR B\n" , 4 };
		case 0x19: return dis_line{ pc, 2, {0xCB,0x19,0x00},"RR C\n" , 4 };
		case 0x1A: return dis_line{ pc, 2, {0xCB,0x1A,0x00},"RR D\n" , 4 };
		case 0x1B: return dis_line{ pc, 2, {0xCB,0x1B,0x00},"RR E\n" , 4 };
		case 0x1C: return dis_line{ pc, 2, {0xCB,0x1C,0x00},"RR H\n" , 4 };
		case 0x1D: return dis_line{ pc, 2, {0xCB,0x1D,0x00},"RR L\n" , 4 };
		case 0x1E: return dis_line{ pc, 2, {0xCB,0x1E,0x00},"RR (HL)\n" , 4 };
		case 0x1F: return dis_line{ pc, 2, {0xCB,0x1F,0x00},"RR A\n" , 4 };
		case 0x20: return dis_line{ pc, 2, {0xCB,0x20,0x00},"SLA B\n" , 4 };
		case 0x21: return dis_line{ pc, 2, {0xCB,0x21,0x00},"SLA C\n" , 4 };
		case 0x22: return dis_line{ pc, 2, {0xCB,0x22,0x00},"SLA D\n" , 4 };
		case 0x23: return dis_line{ pc, 2, {0xCB,0x23,0x00},"SLA E\n" , 4 };
		case 0x24: return dis_line{ pc, 2, {0xCB,0x24,0x00},"SLA H\n" , 4 };
		case 0x25: return dis_line{ pc, 2, {0xCB,0x25,0x00},"SLA L\n" , 4 };
		case 0x26: return dis_line{ pc, 2, {0xCB,0x26,0x00},"SLA (HL)\n" , 4 };
		case 0x27: return dis_line{ pc, 2, {0xCB,0x27,0x00},"SLA A\n" , 4 };
		case 0x28: return dis_line{ pc, 2, {0xCB,0x28,0x00},"SRA B\n" , 4 };
		case 0x29: return dis_line{ pc, 2, {0xCB,0x29,0x00},"SRA C\n" , 4 };
		case 0x2A: return dis_line{ pc, 2, {0xCB,0x2A,0x00},"SRA D\n" , 4 };
		case 0x2B: return dis_line{ pc, 2, {0xCB,0x2B,0x00},"SRA E\n" , 4 };
		case 0x2C: return dis_line{ pc, 2, {0xCB,0x2C,0x00},"SRA H\n" , 4 };
		case 0x2D: return dis_line{ pc, 2, {0xCB,0x2D,0x00},"SRA L\n" , 4 };
		case 0x2E: return dis_line{ pc, 2, {0xCB,0x2E,0x00},"SRA (HL)\n" , 4 };
		case 0x2F: return dis_line{ pc, 2, {0xCB,0x2F,0x00},"SRA A\n" , 4 };
		case 0x30: return dis_line{ pc, 2, {0xCB,0x30,0x00},"SWAP B\n" , 4 };
		case 0x31: return dis_line{ pc, 2, {0xCB,0x31,0x00},"SWAP C\n" , 4 };
		case 0x32: return dis_line{ pc, 2, {0xCB,0x32,0x00},"SWAP D\n" , 4 };
		case 0x33: return dis_line{ pc, 2, {0xCB,0x33,0x00},"SWAP E\n" , 4 };
		case 0x34: return dis_line{ pc, 2, {0xCB,0x34,0x00},"SWAP H\n" , 4 };
		case 0x35: return dis_line{ pc, 2, {0xCB,0x35,0x00},"SWAP L\n" , 4 };
		case 0x36: return dis_line{ pc, 2, {0xCB,0x36,0x00},"SWAP (HL)\n" , 4 };
		case 0x37: return dis_line{ pc, 2, {0xCB,0x37,0x00},"SWAP A\n" , 4 };
		case 0x38: return dis_line{ pc, 2, {0xCB,0x38,0x00},"SRL B\n" , 4 };
		case 0x39: return dis_line{ pc, 2, {0xCB,0x39,0x00},"SRL C\n" , 4 };
		case 0x3A: return dis_line{ pc, 2, {0xCB,0x3A,0x00},"SRL D\n" , 4 };
		case 0x3B: return dis_line{ pc, 2, {0xCB,0x3B,0x00},"SRL E\n" , 4 };
		case 0x3C: return dis_line{ pc, 2, {0xCB,0x3C,0x00},"SRL H\n" , 4 };
		case 0x3D: return dis_line{ pc, 2, {0xCB,0x3D,0x00},"SRL L\n" , 4 };
		case 0x3E: return dis_line{ pc, 2, {0xCB,0x3E,0x00},"SRL (HL)\n" , 4 };
		case 0x3F: return dis_line{ pc, 2, {0xCB,0x3F,0x00},"SRL A\n" , 4 };
		case 0x40: return dis_line{ pc, 2, {0xCB,0x40,0x00},"BIT 0,B\n" , 4 };
		case 0x41: return dis_line{ pc, 2, {0xCB,0x41,0x00},"BIT 0,C\n" , 4 };
		case 0x42: return dis_line{ pc, 2, {0xCB,0x42,0x00},"BIT 0,D\n" , 4 };
		case 0x43: return dis_line{ pc, 2, {0xCB,0x43,0x00},"BIT 0,E\n" , 4 };
		case 0x44: return dis_line{ pc, 2, {0xCB,0x44,0x00},"BIT 0,H\n" , 4 };
		case 0x45: return dis_line{ pc, 2, {0xCB,0x45,0x00},"BIT 0,L\n" , 4 };
		case 0x46: return dis_line{ pc, 2, {0xCB,0x46,0x00},"BIT 0,(HL)\n" , 4 };
		case 0x47: return dis_line{ pc, 2, {0xCB,0x47,0x00},"BIT 0,A\n" , 4 };
		case 0x48: return dis_line{ pc, 2, {0xCB,0x48,0x00},"BIT 1,B\n" , 4 };
		case 0x49: return dis_line{ pc, 2, {0xCB,0x49,0x00},"BIT 1,C\n" , 4 };
		case 0x4A: return dis_line{ pc, 2, {0xCB,0x4A,0x00},"BIT 1,D\n" , 4 };
		case 0x4B: return dis_line{ pc, 2, {0xCB,0x4B,0x00},"BIT 1,E\n" , 4 };
		case 0x4C: return dis_line{ pc, 2, {0xCB,0x4C,0x00},"BIT 1,H\n" , 4 };
		case 0x4D: return dis_line{ pc, 2, {0xCB,0x4D,0x00},"BIT 1,L\n" , 4 };
		case 0x4E: return dis_line{ pc, 2, {0xCB,0x4E,0x00},"BIT 1,(HL)\n" , 4 };
		case 0x4F: return dis_line{ pc, 2, {0xCB,0x4F,0x00},"BIT 1,A\n" , 4 };
		case 0x50: return dis_line{ pc, 2, {0xCB,0x50,0x00},"BIT 2,B\n" , 4 };
		case 0x51: return dis_line{ pc, 2, {0xCB,0x51,0x00},"BIT 2,C\n" , 4 };
		case 0x52: return dis_line{ pc, 2, {0xCB,0x52,0x00},"BIT 2,D\n" , 4 };
		case 0x53: return dis_line{ pc, 2, {0xCB,0x53,0x00},"BIT 2,E\n" , 4 };
		case 0x54: return dis_line{ pc, 2, {0xCB,0x54,0x00},"BIT 2,H\n" , 4 };
		case 0x55: return dis_line{ pc, 2, {0xCB,0x55,0x00},"BIT 2,L\n" , 4 };
		case 0x56: return dis_line{ pc, 2, {0xCB,0x56,0x00},"BIT 2,(HL)\n" , 4 };
		case 0x57: return dis_line{ pc, 2, {0xCB,0x57,0x00},"BIT 2,A\n" , 4 };
		case 0x58: return dis_line{ pc, 2, {0xCB,0x58,0x00},"BIT 3,B\n" , 4 };
		case 0x59: return dis_line{ pc, 2, {0xCB,0x59,0x00},"BIT 3,C\n" , 4 };
		case 0x5A: return dis_line{ pc, 2, {0xCB,0x5A,0x00},"BIT 3,D\n" , 4 };
		case 0x5B: return dis_line{ pc, 2, {0xCB,0x5B,0x00},"BIT 3,E\n" , 4 };
		case 0x5C: return dis_line{ pc, 2, {0xCB,0x5C,0x00},"BIT 3,H\n" , 4 };
		case 0x5D: return dis_line{ pc, 2, {0xCB,0x5D,0x00},"BIT 3,L\n" , 4 };
		case 0x5E: return dis_line{ pc, 2, {0xCB,0x5E,0x00},"BIT 3,(HL)\n" , 4 };
		case 0x5F: return dis_line{ pc, 2, {0xCB,0x5F,0x00},"BIT 3,A\n" , 4 };
		case 0x60: return dis_line{ pc, 2, {0xCB,0x60,0x00},"BIT 4,B\n" , 4 };
		case 0x61: return dis_line{ pc, 2, {0xCB,0x61,0x00},"BIT 4,C\n" , 4 };
		case 0x62: return dis_line{ pc, 2, {0xCB,0x62,0x00},"BIT 4,D\n" , 4 };
		case 0x63: return dis_line{ pc, 2, {0xCB,0x63,0x00},"BIT 4,E\n" , 4 };
		case 0x64: return dis_line{ pc, 2, {0xCB,0x64,0x00},"BIT 4,H\n" , 4 };
		case 0x65: return dis_line{ pc, 2, {0xCB,0x65,0x00},"BIT 4,L\n" , 4 };
		case 0x66: return dis_line{ pc, 2, {0xCB,0x66,0x00},"BIT 4,(HL)\n" , 4 };
		case 0x67: return dis_line{ pc, 2, {0xCB,0x67,0x00},"BIT 4,A\n" , 4 };
		case 0x68: return dis_line{ pc, 2, {0xCB,0x68,0x00},"BIT 5,B\n" , 4 };
		case 0x69: return dis_line{ pc, 2, {0xCB,0x69,0x00},"BIT 5,C\n" , 4 };
		case 0x6A: return dis_line{ pc, 2, {0xCB,0x6A,0x00},"BIT 5,D\n" , 4 };
		case 0x6B: return dis_line{ pc, 2, {0xCB,0x6B,0x00},"BIT 5,E\n" , 4 };
		case 0x6C: return dis_line{ pc, 2, {0xCB,0x6C,0x00},"BIT 5,H\n" , 4 };
		case 0x6D: return dis_line{ pc, 2, {0xCB,0x6D,0x00},"BIT 5,L\n" , 4 };
		case 0x6E: return dis_line{ pc, 2, {0xCB,0x6E,0x00},"BIT 5,(HL)\n" , 4 };
		case 0x6F: return dis_line{ pc, 2, {0xCB,0x6F,0x00},"BIT 5,A\n" , 4 };
		case 0x70: return dis_line{ pc, 2, {0xCB,0x70,0x00},"BIT 6,B\n" , 4 };
		case 0x71: return dis_line{ pc, 2, {0xCB,0x71,0x00},"BIT 6,C\n" , 4 };
		case 0x72: return dis_line{ pc, 2, {0xCB,0x72,0x00},"BIT 6,D\n" , 4 };
		case 0x73: return dis_line{ pc, 2, {0xCB,0x73,0x00},"BIT 6,E\n" , 4 };
		case 0x74: return dis_line{ pc, 2, {0xCB,0x74,0x00},"BIT 6,H\n" , 4 };
		case 0x75: return dis_line{ pc, 2, {0xCB,0x75,0x00},"BIT 6,L\n" , 4 };
		case 0x76: return dis_line{ pc, 2, {0xCB,0x76,0x00},"BIT 6,(HL)\n" , 4 };
		case 0x77: return dis_line{ pc, 2, {0xCB,0x77,0x00},"BIT 6,A\n" , 4 };
		case 0x78: return dis_line{ pc, 2, {0xCB,0x78,0x00},"BIT 7,B\n" , 4 };
		case 0x79: return dis_line{ pc, 2, {0xCB,0x79,0x00},"BIT 7,C\n" , 4 };
		case 0x7A: return dis_line{ pc, 2, {0xCB,0x7A,0x00},"BIT 7,D\n" , 4 };
		case 0x7B: return dis_line{ pc, 2, {0xCB,0x7B,0x00},"BIT 7,E\n" , 4 };
		case 0x7C: return dis_line{ pc, 2, {0xCB,0x7C,0x00},"BIT 7,H\n" , 4 };
		case 0x7D: return dis_line{ pc, 2, {0xCB,0x7D,0x00},"BIT 7,L\n" , 4 };
		case 0x7E: return dis_line{ pc, 2, {0xCB,0x7E,0x00},"BIT 7,(HL)\n" , 4 };
		case 0x7F: return dis_line{ pc, 2, {0xCB,0x7F,0x00},"BIT 7,A\n" , 4 };
		case 0x80: return dis_line{ pc, 2, {0xCB,0x80,0x00},"RES 0,B\n" , 4 };
		case 0x81: return dis_line{ pc, 2, {0xCB,0x81,0x00},"RES 0,C\n" , 4 };
		case 0x82: return dis_line{ pc, 2, {0xCB,0x82,0x00},"RES 0,D\n" , 4 };
		case 0x83: return dis_line{ pc, 2, {0xCB,0x83,0x00},"RES 0,E\n" , 4 };
		case 0x84: return dis_line{ pc, 2, {0xCB,0x84,0x00},"RES 0,H\n" , 4 };
		case 0x85: return dis_line{ pc, 2, {0xCB,0x85,0x00},"RES 0,L\n" , 4 };
		case 0x86: return dis_line{ pc, 2, {0xCB,0x86,0x00},"RES 0,(HL)\n" , 4 };
		case 0x87: return dis_line{ pc, 2, {0xCB,0x87,0x00},"RES 0,A\n" , 4 };
		case 0x88: return dis_line{ pc, 2, {0xCB,0x88,0x00},"RES 1,B\n" , 4 };
		case 0x89: return dis_line{ pc, 2, {0xCB,0x89,0x00},"RES 1,C\n" , 4 };
		case 0x8A: return dis_line{ pc, 2, {0xCB,0x8A,0x00},"RES 1,D\n" , 4 };
		case 0x8B: return dis_line{ pc, 2, {0xCB,0x8B,0x00},"RES 1,E\n" , 4 };
		case 0x8C: return dis_line{ pc, 2, {0xCB,0x8C,0x00},"RES 1,H\n" , 4 };
		case 0x8D: return dis_line{ pc, 2, {0xCB,0x8D,0x00},"RES 1,L\n" , 4 };
		case 0x8E: return dis_line{ pc, 2, {0xCB,0x8E,0x00},"RES 1,(HL)\n" , 4 };
		case 0x8F: return dis_line{ pc, 2, {0xCB,0x8F,0x00},"RES 1,A\n" , 4 };
		case 0x90: return dis_line{ pc, 2, {0xCB,0x90,0x00},"RES 2,B\n" , 4 };
		case 0x91: return dis_line{ pc, 2, {0xCB,0x91,0x00},"RES 2,C\n" , 4 };
		case 0x92: return dis_line{ pc, 2, {0xCB,0x92,0x00},"RES 2,D\n" , 4 };
		case 0x93: return dis_line{ pc, 2, {0xCB,0x93,0x00},"RES 2,E\n" , 4 };
		case 0x94: return dis_line{ pc, 2, {0xCB,0x94,0x00},"RES 2,H\n" , 4 };
		case 0x95: return dis_line{ pc, 2, {0xCB,0x95,0x00},"RES 2,L\n" , 4 };
		case 0x96: return dis_line{ pc, 2, {0xCB,0x96,0x00},"RES 2,(HL)\n" , 4 };
		case 0x97: return dis_line{ pc, 2, {0xCB,0x97,0x00},"RES 2,A\n" , 4 };
		case 0x98: return dis_line{ pc, 2, {0xCB,0x98,0x00},"RES 3,B\n" , 4 };
		case 0x99: return dis_line{ pc, 2, {0xCB,0x99,0x00},"RES 3,C\n" , 4 };
		case 0x9A: return dis_line{ pc, 2, {0xCB,0x9A,0x00},"RES 3,D\n" , 4 };
		case 0x9B: return dis_line{ pc, 2, {0xCB,0x9B,0x00},"RES 3,E\n" , 4 };
		case 0x9C: return dis_line{ pc, 2, {0xCB,0x9C,0x00},"RES 3,H\n" , 4 };
		case 0x9D: return dis_line{ pc, 2, {0xCB,0x9D,0x00},"RES 3,L\n" , 4 };
		case 0x9E: return dis_line{ pc, 2, {0xCB,0x9E,0x00},"RES 3,(HL)\n" , 4 };
		case 0x9F: return dis_line{ pc, 2, {0xCB,0x9F,0x00},"RES 3,A\n" , 4 };
		case 0xA0: return dis_line{ pc, 2, {0xCB,0xA0,0x00},"RES 4,B\n" , 4 };
		case 0xA1: return dis_line{ pc, 2, {0xCB,0xA1,0x00},"RES 4,C\n" , 4 };
		case 0xA2: return dis_line{ pc, 2, {0xCB,0xA2,0x00},"RES 4,D\n" , 4 };
		case 0xA3: return dis_line{ pc, 2, {0xCB,0xA3,0x00},"RES 4,E\n" , 4 };
		case 0xA4: return dis_line{ pc, 2, {0xCB,0xA4,0x00},"RES 4,H\n" , 4 };
		case 0xA5: return dis_line{ pc, 2, {0xCB,0xA5,0x00},"RES 4,L\n" , 4 };
		case 0xA6: return dis_line{ pc, 2, {0xCB,0xA6,0x00},"RES 4,(HL)\n" , 4 };
		case 0xA7: return dis_line{ pc, 2, {0xCB,0xA7,0x00},"RES 4,A\n" , 4 };
		case 0xA8: return dis_line{ pc, 2, {0xCB,0xA8,0x00},"RES 5,B\n" , 4 };
		case 0xA9: return dis_line{ pc, 2, {0xCB,0xA9,0x00},"RES 5,C\n" , 4 };
		case 0xAA: return dis_line{ pc, 2, {0xCB,0xAA,0x00},"RES 5,D\n" , 4 };
		case 0xAB: return dis_line{ pc, 2, {0xCB,0xAB,0x00},"RES 5,E\n" , 4 };
		case 0xAC: return dis_line{ pc, 2, {0xCB,0xAC,0x00},"RES 5,H\n" , 4 };
		case 0xAD: return dis_line{ pc, 2, {0xCB,0xAD,0x00},"RES 5,L\n" , 4 };
		case 0xAE: return dis_line{ pc, 2, {0xCB,0xAE,0x00},"RES 5,(HL)\n" , 4 };
		case 0xAF: return dis_line{ pc, 2, {0xCB,0xAF,0x00},"RES 5,A\n" , 4 };
		case 0xB0: return dis_line{ pc, 2, {0xCB,0xB0,0x00},"RES 6,B\n" , 4 };
		case 0xB1: return dis_line{ pc, 2, {0xCB,0xB1,0x00},"RES 6,C\n" , 4 };
		case 0xB2: return dis_line{ pc, 2, {0xCB,0xB2,0x00},"RES 6,D\n" , 4 };
		case 0xB3: return dis_line{ pc, 2, {0xCB,0xB3,0x00},"RES 6,E\n" , 4 };
		case 0xB4: return dis_line{ pc, 2, {0xCB,0xB4,0x00},"RES 6,H\n" , 4 };
		case 0xB5: return dis_line{ pc, 2, {0xCB,0xB5,0x00},"RES 6,L\n" , 4 };
		case 0xB6: return dis_line{ pc, 2, {0xCB,0xB6,0x00},"RES 6,(HL)\n" , 4 };
		case 0xB7: return dis_line{ pc, 2, {0xCB,0xB7,0x00},"RES 6,A\n" , 4 };
		case 0xB8: return dis_line{ pc, 2, {0xCB,0xB8,0x00},"RES 7,B\n" , 4 };
		case 0xB9: return dis_line{ pc, 2, {0xCB,0xB9,0x00},"RES 7,C\n" , 4 };
		case 0xBA: return dis_line{ pc, 2, {0xCB,0xBA,0x00},"RES 7,D\n" , 4 };
		case 0xBB: return dis_line{ pc, 2, {0xCB,0xBB,0x00},"RES 7,E\n" , 4 };
		case 0xBC: return dis_line{ pc, 2, {0xCB,0xBC,0x00},"RES 7,H\n" , 4 };
		case 0xBD: return dis_line{ pc, 2, {0xCB,0xBD,0x00},"RES 7,L\n" , 4 };
		case 0xBE: return dis_line{ pc, 2, {0xCB,0xBE,0x00},"RES 7,(HL)\n" , 4 };
		case 0xBF: return dis_line{ pc, 2, {0xCB,0xBF,0x00},"RES 7,A\n" , 4 };
		case 0xC0: return dis_line{ pc, 2, {0xCB,0xC0,0x00},"SET 0,B\n" , 4 };
		case 0xC1: return dis_line{ pc, 2, {0xCB,0xC1,0x00},"SET 0,C\n" , 4 };
		case 0xC2: return dis_line{ pc, 2, {0xCB,0xC2,0x00},"SET 0,D\n" , 4 };
		case 0xC3: return dis_line{ pc, 2, {0xCB,0xC3,0x00},"SET 0,E\n" , 4 };
		case 0xC4: return dis_line{ pc, 2, {0xCB,0xC4,0x00},"SET 0,H\n" , 4 };
		case 0xC5: return dis_line{ pc, 2, {0xCB,0xC5,0x00},"SET 0,L\n" , 4 };
		case 0xC6: return dis_line{ pc, 2, {0xCB,0xC6,0x00},"SET 0,(HL)\n" , 4 };
		case 0xC7: return dis_line{ pc, 2, {0xCB,0xC7,0x00},"SET 0,A\n" , 4 };
		case 0xC8: return dis_line{ pc, 2, {0xCB,0xC8,0x00},"SET 1,B\n" , 4 };
		case 0xC9: return dis_line{ pc, 2, {0xCB,0xC9,0x00},"SET 1,C\n" , 4 };
		case 0xCA: return dis_line{ pc, 2, {0xCB,0xCA,0x00},"SET 1,D\n" , 4 };
		case 0xCB: return dis_line{ pc, 2, {0xCB,0xCB,0x00},"SET 1,E\n" , 4 };
		case 0xCC: return dis_line{ pc, 2, {0xCB,0xCC,0x00},"SET 1,H\n" , 4 };
		case 0xCD: return dis_line{ pc, 2, {0xCB,0xCD,0x00},"SET 1,L\n" , 4 };
		case 0xCE: return dis_line{ pc, 2, {0xCB,0xCE,0x00},"SET 1,(HL)\n" , 4 };
		case 0xCF: return dis_line{ pc, 2, {0xCB,0xCF,0x00},"SET 1,A\n" , 4 };
		case 0xD0: return dis_line{ pc, 2, {0xCB,0xD0,0x00},"SET 2,B\n" , 4 };
		case 0xD1: return dis_line{ pc, 2, {0xCB,0xD1,0x00},"SET 2,C\n" , 4 };
		case 0xD2: return dis_line{ pc, 2, {0xCB,0xD2,0x00},"SET 2,D\n" , 4 };
		case 0xD3: return dis_line{ pc, 2, {0xCB,0xD3,0x00},"SET 2,E\n" , 4 };
		case 0xD4: return dis_line{ pc, 2, {0xCB,0xD4,0x00},"SET 2,H\n" , 4 };
		case 0xD5: return dis_line{ pc, 2, {0xCB,0xD5,0x00},"SET 2,L\n" , 4 };
		case 0xD6: return dis_line{ pc, 2, {0xCB,0xD6,0x00},"SET 2,(HL)\n" , 4 };
		case 0xD7: return dis_line{ pc, 2, {0xCB,0xD7,0x00},"SET 2,A\n" , 4 };
		case 0xD8: return dis_line{ pc, 2, {0xCB,0xD8,0x00},"SET 3,B\n" , 4 };
		case 0xD9: return dis_line{ pc, 2, {0xCB,0xD9,0x00},"SET 3,C\n" , 4 };
		case 0xDA: return dis_line{ pc, 2, {0xCB,0xDA,0x00},"SET 3,D\n" , 4 };
		case 0xDB: return dis_line{ pc, 2, {0xCB,0xDB,0x00},"SET 3,E\n" , 4 };
		case 0xDC: return dis_line{ pc, 2, {0xCB,0xDC,0x00},"SET 3,H\n" , 4 };
		case 0xDD: return dis_line{ pc, 2, {0xCB,0xDD,0x00},"SET 3,L\n" , 4 };
		case 0xDE: return dis_line{ pc, 2, {0xCB,0xDE,0x00},"SET 3,(HL)\n" , 4 };
		case 0xDF: return dis_line{ pc, 2, {0xCB,0xDF,0x00},"SET 3,A\n" , 4 };
		case 0xE0: return dis_line{ pc, 2, {0xCB,0xE0,0x00},"SET 4,B\n" , 4 };
		case 0xE1: return dis_line{ pc, 2, {0xCB,0xE1,0x00},"SET 4,C\n" , 4 };
		case 0xE2: return dis_line{ pc, 2, {0xCB,0xE2,0x00},"SET 4,D\n" , 4 };
		case 0xE3: return dis_line{ pc, 2, {0xCB,0xE3,0x00},"SET 4,E\n" , 4 };
		case 0xE4: return dis_line{ pc, 2, {0xCB,0xE4,0x00},"SET 4,H\n" , 4 };
		case 0xE5: return dis_line{ pc, 2, {0xCB,0xE5,0x00},"SET 4,L\n" , 4 };
		case 0xE6: return dis_line{ pc, 2, {0xCB,0xE6,0x00},"SET 4,(HL)\n" , 4 };
		case 0xE7: return dis_line{ pc, 2, {0xCB,0xE7,0x00},"SET 4,A\n" , 4 };
		case 0xE8: return dis_line{ pc, 2, {0xCB,0xE8,0x00},"SET 5,B\n" , 4 };
		case 0xE9: return dis_line{ pc, 2, {0xCB,0xE9,0x00},"SET 5,C\n" , 4 };
		case 0xEA: return dis_line{ pc, 2, {0xCB,0xEA,0x00},"SET 5,D\n" , 4 };
		case 0xEB: return dis_line{ pc, 2, {0xCB,0xEB,0x00},"SET 5,E\n" , 4 };
		case 0xEC: return dis_line{ pc, 2, {0xCB,0xEC,0x00},"SET 5,H\n" , 4 };
		case 0xED: return dis_line{ pc, 2, {0xCB,0xED,0x00},"SET 5,L\n" , 4 };
		case 0xEE: return dis_line{ pc, 2, {0xCB,0xEE,0x00},"SET 5,(HL)\n" , 4 };
		case 0xEF: return dis_line{ pc, 2, {0xCB,0xEF,0x00},"SET 5,A\n" , 4 };
		case 0xF0: return dis_line{ pc, 2, {0xCB,0xF0,0x00},"SET 6,B\n" , 4 };
		case 0xF1: return dis_line{ pc, 2, {0xCB,0xF1,0x00},"SET 6,C\n" , 4 };
		case 0xF2: return dis_line{ pc, 2, {0xCB,0xF2,0x00},"SET 6,D\n" , 4 };
		case 0xF3: return dis_line{ pc, 2, {0xCB,0xF3,0x00},"SET 6,E\n" , 4 };
		case 0xF4: return dis_line{ pc, 2, {0xCB,0xF4,0x00},"SET 6,H\n" , 4 };
		case 0xF5: return dis_line{ pc, 2, {0xCB,0xF5,0x00},"SET 6,L\n" , 4 };
		case 0xF6: return dis_line{ pc, 2, {0xCB,0xF6,0x00},"SET 6,(HL)\n" , 4 };
		case 0xF7: return dis_line{ pc, 2, {0xCB,0xF7,0x00},"SET 6,A\n" , 4 };
		case 0xF8: return dis_line{ pc, 2, {0xCB,0xF8,0x00},"SET 7,B\n" , 4 };
		case 0xF9: return dis_line{ pc, 2, {0xCB,0xF9,0x00},"SET 7,C\n" , 4 };
		case 0xFA: return dis_line{ pc, 2, {0xCB,0xFA,0x00},"SET 7,D\n" , 4 };
		case 0xFB: return dis_line{ pc, 2, {0xCB,0xFB,0x00},"SET 7,E\n" , 4 };
		case 0xFC: return dis_line{ pc, 2, {0xCB,0xFC,0x00},"SET 7,H\n" , 4 };
		case 0xFD: return dis_line{ pc, 2, {0xCB,0xFD,0x00},"SET 7,L\n" , 4 };
		case 0xFE: return dis_line{ pc, 2, {0xCB,0xFE,0x00},"SET 7,(HL)\n" , 4 };
		case 0xFF: return dis_line{ pc, 2, {0xCB,0xFF,0x00},"SET 7,A\n" , 4 };
		}
	case 0xCC: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "CALL Z,$%02x%02x\n", b3, b2); return l; }
	case 0xCD: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "CALL $%02x%02x\n", b3, b2); return l; }
	case 0xCE: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "ADC A,$%02x\n", b2); return l; }
	case 0xCF: return dis_line{ pc, 1, {b1,b2,b3},"RST 08h\n", 1 };
	case 0xD0: return dis_line{ pc, 1, {b1,b2,b3},"RET NC\n", 1 };
	case 0xD1: return dis_line{ pc, 1, {b1,b2,b3},"POP DE\n", 2 };
	case 0xD2: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JP NC,$%02x%02x\n", b3, b2); return l; }
	case 0xD3: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xD4: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "CALL NC,$%02x%02x\n", b3, b2); return l; }
	case 0xD5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH DE\n", 2 };
	case 0xD6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "SUB A,$%02x\n", b2); return l; }
	case 0xD7: return dis_line{ pc, 1, {b1,b2,b3},"RST 10h\n", 1 };
	case 0xD8: return dis_line{ pc, 1, {b1,b2,b3},"RET C\n", 1 };
	case 0xD9: return dis_line{ pc, 1, {b1,b2,b3},"RETI\n", 1 };
	case 0xDA: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "JP C,$%02x%02x\n", b3, b2); return l; }
	case 0xDB: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xDC: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 1 }; sprintf(l._text, "CALL C,$%02x%02x\n", b3, b2); return l; }
	case 0xDD: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xDE: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "SBC A,$%02x\n", b2); return l; }
	case 0xDF: return dis_line{ pc, 1, {b1,b2,b3},"RST 18h\n", 1 };
	case 0xE0: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD (FF00+$%02x),A\n", b2); return l; }
	case 0xE1: return dis_line{ pc, 1, {b1,b2,b3},"POP HL\n", 2 };
	case 0xE2: return dis_line{ pc, 1, {b1,b2,b3},"LD (FF00+C),A\n", 5 };
	case 0xE3: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xE4: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xE5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH HL\n", 2 };
	case 0xE6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "AND A,$%02x\n", b2); return l; }
	case 0xE7: return dis_line{ pc, 1, {b1,b2,b3},"RST 20h\n", 1 };
	case 0xE8: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 7 }; sprintf(l._text, "ADD SP,$%02x [%hhi]\n", b2, b2); return l; }
	case 0xE9: return dis_line{ pc, 1, {b1,b2,b3},"JP HL\n", 1 };
	case 0xEA: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD ($%02x%02x),A\n", b3, b2); return l; }
	case 0xEB: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xEC: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xED: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xEE: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "XOR A,$%02x\n", b2); return l; }
	case 0xEF: return dis_line{ pc, 1, {b1,b2,b3},"RST 28h\n", 1 };
	case 0xF0: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD A,(FF00+$%02x)\n", b2); return l; }
	case 0xF1: return dis_line{ pc, 1, {b1,b2,b3},"POP AF\n", 2 };
	case 0xF2: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(FF00+C)\n", 5 };
	case 0xF3: return dis_line{ pc, 1, {b1,b2,b3},"DI\n", 0 };
	case 0xF4: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xF5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH AF\n", 2 };
	case 0xF6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "OR A,$%02x\n", b2); return l; }
	case 0xF7: return dis_line{ pc, 1, {b1,b2,b3},"RST 30h\n", 1 };
	case 0xF8: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 7 }; sprintf(l._text, "LD HL,SP+$%02x [%hhi]\n", b2, b2); return l; }
	case 0xF9: return dis_line{ pc, 1, {b1,b2,b3},"LD SP,HL\n", 2 };
	case 0xFA: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" , 5 }; sprintf(l._text, "LD A,($%02x%02x)\n", b3, b2); return l; }
	case 0xFB: return dis_line{ pc, 1, {b1,b2,b3},"EI\n", 0 };
	case 0xFC: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xFD: return dis_line{ pc, 1, {b1,b2,b3}, "UNUSED\n", 6 };
	case 0xFE: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" , 3 }; sprintf(l._text, "CP A,$%02x\n", b2); return l; }
	case 0xFF: return dis_line{ pc, 1, {b1,b2,b3},"RST 38h\n", 1 };
	}
}









int main()
{
	// https://bytefreaks.net/programming-2/c/cc-full-example-of-reading-a-whole-binary-file-to-buffer
	FILE* fIn = fopen("C:\\Users\\pwnag\\Desktop\\retro\\my_GBC\\10-bit ops.gb", "rb");
	const int fseek_end_value = fseek(fIn, 0, SEEK_END); 
	long file_size = ftell(fIn); 
	const int fseek_set_value = fseek(fIn, 0, SEEK_SET); 
	u8* bytes = (u8*)malloc(file_size); 
	if (!bytes) return 420;
	fread(bytes, 1, file_size, fIn);
	fclose(fIn);


	
	u16 pc = 0;
	while (pc < 0x8000)
	{
		dis_line r = disassemble(bytes, pc);
		switch (r._size)
		{
		case 1: printf("%04x : %02x\t\t%s\n", r._address, r._bytes[0], r._text); break;
		case 2: printf("%04x : %02x %02x\t\t%s\n", r._address, r._bytes[0], r._bytes[1], r._text); break;
		case 3: printf("%04x : %02x %02x %02x\t\t%s\n", r._address, r._bytes[0], r._bytes[1], r._bytes[2], r._text); break;
		}
		pc += r._size;
	}

	free(bytes);
	return 0;
}
