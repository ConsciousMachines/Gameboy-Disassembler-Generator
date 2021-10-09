// TODO: check i dont get stack corruption when doing spritnf %hhi for immediate signed i8 

// STOP is the only instruction that is >1 byte and has no immediate (aside form CB set)
// CB set has no immediates, and are all 2 bytes each

#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <stdio.h>
#include <memory>

typedef uint8_t u8;
typedef uint16_t u16;

struct dis_line
{
	u16 _address;
	int _size;
	u8 _bytes[3];
	char _text[20];
};

dis_line disassemble_cb(u8* bytes, u16 pc)
{
	u8 b2 = bytes[pc + 1];

	switch (b2)
	{
	case 0x00: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC B\n" };
	case 0x01: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC C\n" };
	case 0x02: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC D\n" };
	case 0x03: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC E\n" };
	case 0x04: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC H\n" };
	case 0x05: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC L\n" };
	case 0x06: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC (HL)\n" };
	case 0x07: return dis_line{ pc, 2, {0xCB,b2,0x00},"RLC A\n" };
	case 0x08: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC B\n" };
	case 0x09: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC C\n" };
	case 0x0a: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC D\n" };
	case 0x0b: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC E\n" };
	case 0x0c: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC H\n" };
	case 0x0d: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC L\n" };
	case 0x0e: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC (HL)\n" };
	case 0x0f: return dis_line{ pc, 2, {0xCB,b2,0x00},"RRC A\n" };
	case 0x10: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL B\n" };
	case 0x11: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL C\n" };
	case 0x12: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL D\n" };
	case 0x13: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL E\n" };
	case 0x14: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL H\n" };
	case 0x15: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL L\n" };
	case 0x16: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL (HL)\n" };
	case 0x17: return dis_line{ pc, 2, {0xCB,b2,0x00},"RL A\n" };
	case 0x18: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR B\n" };
	case 0x19: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR C\n" };
	case 0x1a: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR D\n" };
	case 0x1b: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR E\n" };
	case 0x1c: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR H\n" };
	case 0x1d: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR L\n" };
	case 0x1e: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR (HL)\n" };
	case 0x1f: return dis_line{ pc, 2, {0xCB,b2,0x00},"RR A\n" };
	case 0x20: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA B\n" };
	case 0x21: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA C\n" };
	case 0x22: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA D\n" };
	case 0x23: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA E\n" };
	case 0x24: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA H\n" };
	case 0x25: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA L\n" };
	case 0x26: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA (HL)\n" };
	case 0x27: return dis_line{ pc, 2, {0xCB,b2,0x00},"SLA A\n" };
	case 0x28: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA B\n" };
	case 0x29: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA C\n" };
	case 0x2a: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA D\n" };
	case 0x2b: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA E\n" };
	case 0x2c: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA H\n" };
	case 0x2d: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA L\n" };
	case 0x2e: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA (HL)\n" };
	case 0x2f: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRA A\n" };
	case 0x30: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP B\n" };
	case 0x31: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP C\n" };
	case 0x32: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP D\n" };
	case 0x33: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP E\n" };
	case 0x34: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP H\n" };
	case 0x35: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP L\n" };
	case 0x36: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP (HL)\n" };
	case 0x37: return dis_line{ pc, 2, {0xCB,b2,0x00},"SWAP A\n" };
	case 0x38: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL B\n" };
	case 0x39: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL C\n" };
	case 0x3a: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL D\n" };
	case 0x3b: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL E\n" };
	case 0x3c: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL H\n" };
	case 0x3d: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL L\n" };
	case 0x3e: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL (HL)\n" };
	case 0x3f: return dis_line{ pc, 2, {0xCB,b2,0x00},"SRL A\n" };
	case 0x40: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,B\n" };
	case 0x41: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,C\n" };
	case 0x42: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,D\n" };
	case 0x43: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,E\n" };
	case 0x44: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,H\n" };
	case 0x45: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,L\n" };
	case 0x46: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,(HL)\n" };
	case 0x47: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 0,A\n" };
	case 0x48: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,B\n" };
	case 0x49: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,C\n" };
	case 0x4a: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,D\n" };
	case 0x4b: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,E\n" };
	case 0x4c: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,H\n" };
	case 0x4d: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,L\n" };
	case 0x4e: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,(HL)\n" };
	case 0x4f: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 1,A\n" };
	case 0x50: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,B\n" };
	case 0x51: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,C\n" };
	case 0x52: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,D\n" };
	case 0x53: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,E\n" };
	case 0x54: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,H\n" };
	case 0x55: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,L\n" };
	case 0x56: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,(HL)\n" };
	case 0x57: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 2,A\n" };
	case 0x58: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,B\n" };
	case 0x59: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,C\n" };
	case 0x5a: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,D\n" };
	case 0x5b: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,E\n" };
	case 0x5c: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,H\n" };
	case 0x5d: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,L\n" };
	case 0x5e: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,(HL)\n" };
	case 0x5f: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 3,A\n" };
	case 0x60: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,B\n" };
	case 0x61: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,C\n" };
	case 0x62: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,D\n" };
	case 0x63: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,E\n" };
	case 0x64: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,H\n" };
	case 0x65: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,L\n" };
	case 0x66: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,(HL)\n" };
	case 0x67: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 4,A\n" };
	case 0x68: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,B\n" };
	case 0x69: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,C\n" };
	case 0x6a: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,D\n" };
	case 0x6b: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,E\n" };
	case 0x6c: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,H\n" };
	case 0x6d: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,L\n" };
	case 0x6e: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,(HL)\n" };
	case 0x6f: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 5,A\n" };
	case 0x70: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,B\n" };
	case 0x71: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,C\n" };
	case 0x72: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,D\n" };
	case 0x73: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,E\n" };
	case 0x74: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,H\n" };
	case 0x75: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,L\n" };
	case 0x76: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,(HL)\n" };
	case 0x77: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 6,A\n" };
	case 0x78: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,B\n" };
	case 0x79: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,C\n" };
	case 0x7a: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,D\n" };
	case 0x7b: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,E\n" };
	case 0x7c: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,H\n" };
	case 0x7d: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,L\n" };
	case 0x7e: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,(HL)\n" };
	case 0x7f: return dis_line{ pc, 2, {0xCB,b2,0x00},"BIT 7,A\n" };
	case 0x80: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,B\n" };
	case 0x81: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,C\n" };
	case 0x82: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,D\n" };
	case 0x83: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,E\n" };
	case 0x84: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,H\n" };
	case 0x85: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,L\n" };
	case 0x86: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,(HL)\n" };
	case 0x87: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 0,A\n" };
	case 0x88: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,B\n" };
	case 0x89: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,C\n" };
	case 0x8a: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,D\n" };
	case 0x8b: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,E\n" };
	case 0x8c: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,H\n" };
	case 0x8d: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,L\n" };
	case 0x8e: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,(HL)\n" };
	case 0x8f: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 1,A\n" };
	case 0x90: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,B\n" };
	case 0x91: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,C\n" };
	case 0x92: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,D\n" };
	case 0x93: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,E\n" };
	case 0x94: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,H\n" };
	case 0x95: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,L\n" };
	case 0x96: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,(HL)\n" };
	case 0x97: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 2,A\n" };
	case 0x98: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,B\n" };
	case 0x99: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,C\n" };
	case 0x9a: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,D\n" };
	case 0x9b: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,E\n" };
	case 0x9c: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,H\n" };
	case 0x9d: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,L\n" };
	case 0x9e: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,(HL)\n" };
	case 0x9f: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 3,A\n" };
	case 0xa0: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,B\n" };
	case 0xa1: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,C\n" };
	case 0xa2: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,D\n" };
	case 0xa3: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,E\n" };
	case 0xa4: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,H\n" };
	case 0xa5: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,L\n" };
	case 0xa6: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,(HL)\n" };
	case 0xa7: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 4,A\n" };
	case 0xa8: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,B\n" };
	case 0xa9: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,C\n" };
	case 0xaa: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,D\n" };
	case 0xab: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,E\n" };
	case 0xac: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,H\n" };
	case 0xad: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,L\n" };
	case 0xae: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,(HL)\n" };
	case 0xaf: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 5,A\n" };
	case 0xb0: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,B\n" };
	case 0xb1: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,C\n" };
	case 0xb2: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,D\n" };
	case 0xb3: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,E\n" };
	case 0xb4: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,H\n" };
	case 0xb5: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,L\n" };
	case 0xb6: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,(HL)\n" };
	case 0xb7: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 6,A\n" };
	case 0xb8: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,B\n" };
	case 0xb9: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,C\n" };
	case 0xba: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,D\n" };
	case 0xbb: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,E\n" };
	case 0xbc: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,H\n" };
	case 0xbd: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,L\n" };
	case 0xbe: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,(HL)\n" };
	case 0xbf: return dis_line{ pc, 2, {0xCB,b2,0x00},"RES 7,A\n" };
	case 0xc0: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,B\n" };
	case 0xc1: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,C\n" };
	case 0xc2: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,D\n" };
	case 0xc3: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,E\n" };
	case 0xc4: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,H\n" };
	case 0xc5: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,L\n" };
	case 0xc6: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,(HL)\n" };
	case 0xc7: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 0,A\n" };
	case 0xc8: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,B\n" };
	case 0xc9: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,C\n" };
	case 0xca: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,D\n" };
	case 0xcb: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,E\n" };
	case 0xcc: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,H\n" };
	case 0xcd: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,L\n" };
	case 0xce: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,(HL)\n" };
	case 0xcf: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 1,A\n" };
	case 0xd0: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,B\n" };
	case 0xd1: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,C\n" };
	case 0xd2: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,D\n" };
	case 0xd3: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,E\n" };
	case 0xd4: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,H\n" };
	case 0xd5: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,L\n" };
	case 0xd6: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,(HL)\n" };
	case 0xd7: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 2,A\n" };
	case 0xd8: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,B\n" };
	case 0xd9: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,C\n" };
	case 0xda: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,D\n" };
	case 0xdb: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,E\n" };
	case 0xdc: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,H\n" };
	case 0xdd: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,L\n" };
	case 0xde: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,(HL)\n" };
	case 0xdf: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 3,A\n" };
	case 0xe0: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,B\n" };
	case 0xe1: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,C\n" };
	case 0xe2: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,D\n" };
	case 0xe3: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,E\n" };
	case 0xe4: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,H\n" };
	case 0xe5: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,L\n" };
	case 0xe6: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,(HL)\n" };
	case 0xe7: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 4,A\n" };
	case 0xe8: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,B\n" };
	case 0xe9: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,C\n" };
	case 0xea: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,D\n" };
	case 0xeb: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,E\n" };
	case 0xec: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,H\n" };
	case 0xed: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,L\n" };
	case 0xee: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,(HL)\n" };
	case 0xef: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 5,A\n" };
	case 0xf0: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,B\n" };
	case 0xf1: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,C\n" };
	case 0xf2: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,D\n" };
	case 0xf3: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,E\n" };
	case 0xf4: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,H\n" };
	case 0xf5: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,L\n" };
	case 0xf6: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,(HL)\n" };
	case 0xf7: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 6,A\n" };
	case 0xf8: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,B\n" };
	case 0xf9: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,C\n" };
	case 0xfa: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,D\n" };
	case 0xfb: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,E\n" };
	case 0xfc: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,H\n" };
	case 0xfd: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,L\n" };
	case 0xfe: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,(HL)\n" };
	case 0xff: return dis_line{ pc, 2, {0xCB,b2,0x00},"SET 7,A\n" };
	}
}


dis_line disassemble(u8* bytes, u16 pc, long size)
{
	if (size - pc < 4) // we read 3 bytes ahead so dont want to overflow
	{
		printf("disassembler has reached the end of the instructions!\n"); getchar();
	}

	u8 b1 = bytes[pc + 0];
	u8 b2 = bytes[pc + 1];
	u8 b3 = bytes[pc + 2];
	u8 b4 = bytes[pc + 3];


	switch (b1)
	{
	case 0x00: return dis_line{ pc, 1, {b1,b2,b3},"NOP\n" };
	case 0x01: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "LD BC,$%02x%02x\n", b3, b2); return l; }
	case 0x02: return dis_line{ pc, 1, {b1,b2,b3},"LD (BC),A\n" };
	case 0x03: return dis_line{ pc, 1, {b1,b2,b3},"INC BC\n" };
	case 0x04: return dis_line{ pc, 1, {b1,b2,b3},"INC B\n" };
	case 0x05: return dis_line{ pc, 1, {b1,b2,b3},"DEC B\n" };
	case 0x06: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD B,$%02x\n", b2); return l; }
	case 0x07: return dis_line{ pc, 1, {b1,b2,b3},"RLCA\n" };
	case 0x08: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "LD ($%02x%02x),SP\n", b3, b2); return l; }
	case 0x09: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,BC\n" };
	case 0x0a: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(BC)\n" };
	case 0x0b: return dis_line{ pc, 1, {b1,b2,b3},"DEC BC\n" };
	case 0x0c: return dis_line{ pc, 1, {b1,b2,b3},"INC C\n" };
	case 0x0d: return dis_line{ pc, 1, {b1,b2,b3},"DEC C\n" };
	case 0x0e: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD C,$%02x\n", b2); return l; }
	case 0x0f: return dis_line{ pc, 1, {b1,b2,b3},"RRCA\n" };
	case 0x10: return dis_line{ pc, 2, {b1,b2,b3},"STOP\n" };
	case 0x11: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "LD DE,$%02x%02x\n", b3, b2); return l; }
	case 0x12: return dis_line{ pc, 1, {b1,b2,b3},"LD (DE),A\n" };
	case 0x13: return dis_line{ pc, 1, {b1,b2,b3},"INC DE\n" };
	case 0x14: return dis_line{ pc, 1, {b1,b2,b3},"INC D\n" };
	case 0x15: return dis_line{ pc, 1, {b1,b2,b3},"DEC D\n" };
	case 0x16: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD D,$%02x\n", b2); return l; }
	case 0x17: return dis_line{ pc, 1, {b1,b2,b3},"RLA\n" };
	case 0x18: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "JR $%02x\n [%hhi]", b2, b2); return l; }
	case 0x19: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,DE\n" };
	case 0x1a: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(DE)\n" };
	case 0x1b: return dis_line{ pc, 1, {b1,b2,b3},"DEC DE\n" };
	case 0x1c: return dis_line{ pc, 1, {b1,b2,b3},"INC E\n" };
	case 0x1d: return dis_line{ pc, 1, {b1,b2,b3},"DEC E\n" };
	case 0x1e: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD E,$%02x\n", b2); return l; }
	case 0x1f: return dis_line{ pc, 1, {b1,b2,b3},"RRA\n" };
	case 0x20: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "JR NZ,$%02x\n [%hhi]", b2, b2); return l; }
	case 0x21: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "LD HL,$%02x%02x\n", b3, b2); return l; }
	case 0x22: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL+),A\n" };
	case 0x23: return dis_line{ pc, 1, {b1,b2,b3},"INC HL\n" };
	case 0x24: return dis_line{ pc, 1, {b1,b2,b3},"INC H\n" };
	case 0x25: return dis_line{ pc, 1, {b1,b2,b3},"DEC H\n" };
	case 0x26: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD H,$%02x\n", b2); return l; }
	case 0x27: return dis_line{ pc, 1, {b1,b2,b3},"DAA\n" };
	case 0x28: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "JR Z,$%02x\n [%hhi]", b2, b2); return l; }
	case 0x29: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,HL\n" };
	case 0x2a: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(HL+)\n" };
	case 0x2b: return dis_line{ pc, 1, {b1,b2,b3},"DEC HL\n" };
	case 0x2c: return dis_line{ pc, 1, {b1,b2,b3},"INC L\n" };
	case 0x2d: return dis_line{ pc, 1, {b1,b2,b3},"DEC L\n" };
	case 0x2e: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD L,$%02x\n", b2); return l; }
	case 0x2f: return dis_line{ pc, 1, {b1,b2,b3},"CPL\n" };
	case 0x30: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "JR NC,$%02x\n [%hhi]", b2, b2); return l; }
	case 0x31: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "LD SP,$%02x%02x\n", b3, b2); return l; }
	case 0x32: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL-),A\n" };
	case 0x33: return dis_line{ pc, 1, {b1,b2,b3},"INC SP\n" };
	case 0x34: return dis_line{ pc, 1, {b1,b2,b3},"INC (HL)\n" };
	case 0x35: return dis_line{ pc, 1, {b1,b2,b3},"DEC (HL)\n" };
	case 0x36: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD (HL),$%02x\n", b2); return l; }
	case 0x37: return dis_line{ pc, 1, {b1,b2,b3},"SCF\n" };
	case 0x38: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "JR C,$%02x\n [%hhi]", b2, b2); return l; }
	case 0x39: return dis_line{ pc, 1, {b1,b2,b3},"ADD HL,SP\n" };
	case 0x3a: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(HL-)\n" };
	case 0x3b: return dis_line{ pc, 1, {b1,b2,b3},"DEC SP\n" };
	case 0x3c: return dis_line{ pc, 1, {b1,b2,b3},"INC A\n" };
	case 0x3d: return dis_line{ pc, 1, {b1,b2,b3},"DEC A\n" };
	case 0x3e: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD A,$%02x\n", b2); return l; }
	case 0x3f: return dis_line{ pc, 1, {b1,b2,b3},"CCF\n" };
	case 0x40: return dis_line{ pc, 1, {b1,b2,b3},"LD B,B\n" };
	case 0x41: return dis_line{ pc, 1, {b1,b2,b3},"LD B,C\n" };
	case 0x42: return dis_line{ pc, 1, {b1,b2,b3},"LD B,D\n" };
	case 0x43: return dis_line{ pc, 1, {b1,b2,b3},"LD B,E\n" };
	case 0x44: return dis_line{ pc, 1, {b1,b2,b3},"LD B,H\n" };
	case 0x45: return dis_line{ pc, 1, {b1,b2,b3},"LD B,L\n" };
	case 0x46: return dis_line{ pc, 1, {b1,b2,b3},"LD B,(HL)\n" };
	case 0x47: return dis_line{ pc, 1, {b1,b2,b3},"LD B,A\n" };
	case 0x48: return dis_line{ pc, 1, {b1,b2,b3},"LD C,B\n" };
	case 0x49: return dis_line{ pc, 1, {b1,b2,b3},"LD C,C\n" };
	case 0x4a: return dis_line{ pc, 1, {b1,b2,b3},"LD C,D\n" };
	case 0x4b: return dis_line{ pc, 1, {b1,b2,b3},"LD C,E\n" };
	case 0x4c: return dis_line{ pc, 1, {b1,b2,b3},"LD C,H\n" };
	case 0x4d: return dis_line{ pc, 1, {b1,b2,b3},"LD C,L\n" };
	case 0x4e: return dis_line{ pc, 1, {b1,b2,b3},"LD C,(HL)\n" };
	case 0x4f: return dis_line{ pc, 1, {b1,b2,b3},"LD C,A\n" };
	case 0x50: return dis_line{ pc, 1, {b1,b2,b3},"LD D,B\n" };
	case 0x51: return dis_line{ pc, 1, {b1,b2,b3},"LD D,C\n" };
	case 0x52: return dis_line{ pc, 1, {b1,b2,b3},"LD D,D\n" };
	case 0x53: return dis_line{ pc, 1, {b1,b2,b3},"LD D,E\n" };
	case 0x54: return dis_line{ pc, 1, {b1,b2,b3},"LD D,H\n" };
	case 0x55: return dis_line{ pc, 1, {b1,b2,b3},"LD D,L\n" };
	case 0x56: return dis_line{ pc, 1, {b1,b2,b3},"LD D,(HL)\n" };
	case 0x57: return dis_line{ pc, 1, {b1,b2,b3},"LD D,A\n" };
	case 0x58: return dis_line{ pc, 1, {b1,b2,b3},"LD E,B\n" };
	case 0x59: return dis_line{ pc, 1, {b1,b2,b3},"LD E,C\n" };
	case 0x5a: return dis_line{ pc, 1, {b1,b2,b3},"LD E,D\n" };
	case 0x5b: return dis_line{ pc, 1, {b1,b2,b3},"LD E,E\n" };
	case 0x5c: return dis_line{ pc, 1, {b1,b2,b3},"LD E,H\n" };
	case 0x5d: return dis_line{ pc, 1, {b1,b2,b3},"LD E,L\n" };
	case 0x5e: return dis_line{ pc, 1, {b1,b2,b3},"LD E,(HL)\n" };
	case 0x5f: return dis_line{ pc, 1, {b1,b2,b3},"LD E,A\n" };
	case 0x60: return dis_line{ pc, 1, {b1,b2,b3},"LD H,B\n" };
	case 0x61: return dis_line{ pc, 1, {b1,b2,b3},"LD H,C\n" };
	case 0x62: return dis_line{ pc, 1, {b1,b2,b3},"LD H,D\n" };
	case 0x63: return dis_line{ pc, 1, {b1,b2,b3},"LD H,E\n" };
	case 0x64: return dis_line{ pc, 1, {b1,b2,b3},"LD H,H\n" };
	case 0x65: return dis_line{ pc, 1, {b1,b2,b3},"LD H,L\n" };
	case 0x66: return dis_line{ pc, 1, {b1,b2,b3},"LD H,(HL)\n" };
	case 0x67: return dis_line{ pc, 1, {b1,b2,b3},"LD H,A\n" };
	case 0x68: return dis_line{ pc, 1, {b1,b2,b3},"LD L,B\n" };
	case 0x69: return dis_line{ pc, 1, {b1,b2,b3},"LD L,C\n" };
	case 0x6a: return dis_line{ pc, 1, {b1,b2,b3},"LD L,D\n" };
	case 0x6b: return dis_line{ pc, 1, {b1,b2,b3},"LD L,E\n" };
	case 0x6c: return dis_line{ pc, 1, {b1,b2,b3},"LD L,H\n" };
	case 0x6d: return dis_line{ pc, 1, {b1,b2,b3},"LD L,L\n" };
	case 0x6e: return dis_line{ pc, 1, {b1,b2,b3},"LD L,(HL)\n" };
	case 0x6f: return dis_line{ pc, 1, {b1,b2,b3},"LD L,A\n" };
	case 0x70: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),B\n" };
	case 0x71: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),C\n" };
	case 0x72: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),D\n" };
	case 0x73: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),E\n" };
	case 0x74: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),H\n" };
	case 0x75: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),L\n" };
	case 0x76: return dis_line{ pc, 1, {b1,b2,b3},"HALT\n" };
	case 0x77: return dis_line{ pc, 1, {b1,b2,b3},"LD (HL),A\n" };
	case 0x78: return dis_line{ pc, 1, {b1,b2,b3},"LD A,B\n" };
	case 0x79: return dis_line{ pc, 1, {b1,b2,b3},"LD A,C\n" };
	case 0x7a: return dis_line{ pc, 1, {b1,b2,b3},"LD A,D\n" };
	case 0x7b: return dis_line{ pc, 1, {b1,b2,b3},"LD A,E\n" };
	case 0x7c: return dis_line{ pc, 1, {b1,b2,b3},"LD A,H\n" };
	case 0x7d: return dis_line{ pc, 1, {b1,b2,b3},"LD A,L\n" };
	case 0x7e: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(HL)\n" };
	case 0x7f: return dis_line{ pc, 1, {b1,b2,b3},"LD A,A\n" };
	case 0x80: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,B\n" };
	case 0x81: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,C\n" };
	case 0x82: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,D\n" };
	case 0x83: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,E\n" };
	case 0x84: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,H\n" };
	case 0x85: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,L\n" };
	case 0x86: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,(HL)\n" };
	case 0x87: return dis_line{ pc, 1, {b1,b2,b3},"ADD A,A\n" };
	case 0x88: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,B\n" };
	case 0x89: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,C\n" };
	case 0x8a: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,D\n" };
	case 0x8b: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,E\n" };
	case 0x8c: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,H\n" };
	case 0x8d: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,L\n" };
	case 0x8e: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,(HL)\n" };
	case 0x8f: return dis_line{ pc, 1, {b1,b2,b3},"ADC A,A\n" };
	case 0x90: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,B\n" };
	case 0x91: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,C\n" };
	case 0x92: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,D\n" };
	case 0x93: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,E\n" };
	case 0x94: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,H\n" };
	case 0x95: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,L\n" };
	case 0x96: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,(HL)\n" };
	case 0x97: return dis_line{ pc, 1, {b1,b2,b3},"SUB A,A\n" };
	case 0x98: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,B\n" };
	case 0x99: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,C\n" };
	case 0x9a: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,D\n" };
	case 0x9b: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,E\n" };
	case 0x9c: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,H\n" };
	case 0x9d: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,L\n" };
	case 0x9e: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,(HL)\n" };
	case 0x9f: return dis_line{ pc, 1, {b1,b2,b3},"SBC A,A\n" };
	case 0xa0: return dis_line{ pc, 1, {b1,b2,b3},"AND A,B\n" };
	case 0xa1: return dis_line{ pc, 1, {b1,b2,b3},"AND A,C\n" };
	case 0xa2: return dis_line{ pc, 1, {b1,b2,b3},"AND A,D\n" };
	case 0xa3: return dis_line{ pc, 1, {b1,b2,b3},"AND A,E\n" };
	case 0xa4: return dis_line{ pc, 1, {b1,b2,b3},"AND A,H\n" };
	case 0xa5: return dis_line{ pc, 1, {b1,b2,b3},"AND A,L\n" };
	case 0xa6: return dis_line{ pc, 1, {b1,b2,b3},"AND A,(HL)\n" };
	case 0xa7: return dis_line{ pc, 1, {b1,b2,b3},"AND A,A\n" };
	case 0xa8: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,B\n" };
	case 0xa9: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,C\n" };
	case 0xaa: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,D\n" };
	case 0xab: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,E\n" };
	case 0xac: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,H\n" };
	case 0xad: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,L\n" };
	case 0xae: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,(HL)\n" };
	case 0xaf: return dis_line{ pc, 1, {b1,b2,b3},"XOR A,A\n" };
	case 0xb0: return dis_line{ pc, 1, {b1,b2,b3},"OR A,B\n" };
	case 0xb1: return dis_line{ pc, 1, {b1,b2,b3},"OR A,C\n" };
	case 0xb2: return dis_line{ pc, 1, {b1,b2,b3},"OR A,D\n" };
	case 0xb3: return dis_line{ pc, 1, {b1,b2,b3},"OR A,E\n" };
	case 0xb4: return dis_line{ pc, 1, {b1,b2,b3},"OR A,H\n" };
	case 0xb5: return dis_line{ pc, 1, {b1,b2,b3},"OR A,L\n" };
	case 0xb6: return dis_line{ pc, 1, {b1,b2,b3},"OR A,(HL)\n" };
	case 0xb7: return dis_line{ pc, 1, {b1,b2,b3},"OR A,A\n" };
	case 0xb8: return dis_line{ pc, 1, {b1,b2,b3},"CP A,B\n" };
	case 0xb9: return dis_line{ pc, 1, {b1,b2,b3},"CP A,C\n" };
	case 0xba: return dis_line{ pc, 1, {b1,b2,b3},"CP A,D\n" };
	case 0xbb: return dis_line{ pc, 1, {b1,b2,b3},"CP A,E\n" };
	case 0xbc: return dis_line{ pc, 1, {b1,b2,b3},"CP A,H\n" };
	case 0xbd: return dis_line{ pc, 1, {b1,b2,b3},"CP A,L\n" };
	case 0xbe: return dis_line{ pc, 1, {b1,b2,b3},"CP A,(HL)\n" };
	case 0xbf: return dis_line{ pc, 1, {b1,b2,b3},"CP A,A\n" };
	case 0xc0: return dis_line{ pc, 1, {b1,b2,b3},"RET NZ\n" };
	case 0xc1: return dis_line{ pc, 1, {b1,b2,b3},"POP BC\n" };
	case 0xc2: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "JP NZ,$%02x%02x\n", b3, b2); return l; }
	case 0xc3: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "JP $%02x%02x\n", b3, b2); return l; }
	case 0xc4: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "CALL NZ,$%02x%02x\n", b3, b2); return l; }
	case 0xc5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH BC\n" };
	case 0xc6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "ADD A,$%02x\n", b2); return l; }
	case 0xc7: return dis_line{ pc, 1, {b1,b2,b3},"RST 00h\n" };
	case 0xc8: return dis_line{ pc, 1, {b1,b2,b3},"RET Z\n" };
	case 0xc9: return dis_line{ pc, 1, {b1,b2,b3},"RET\n" };
	case 0xca: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "JP Z,$%02x%02x\n", b3, b2); return l; }
	case 0xcb: return disassemble_cb(bytes, pc);
	case 0xcc: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "CALL Z,$%02x%02x\n", b3, b2); return l; }
	case 0xcd: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "CALL $%02x%02x\n", b3, b2); return l; }
	case 0xce: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "ADC A,$%02x\n", b2); return l; }
	case 0xcf: return dis_line{ pc, 1, {b1,b2,b3},"RST 08h\n" };
	case 0xd0: return dis_line{ pc, 1, {b1,b2,b3},"RET NC\n" };
	case 0xd1: return dis_line{ pc, 1, {b1,b2,b3},"POP DE\n" };
	case 0xd2: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "JP NC,$%02x%02x\n", b3, b2); return l; }
	case 0xd3: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xd4: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "CALL NC,$%02x%02x\n", b3, b2); return l; }
	case 0xd5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH DE\n" };
	case 0xd6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "SUB A,$%02x\n", b2); return l; }
	case 0xd7: return dis_line{ pc, 1, {b1,b2,b3},"RST 10h\n" };
	case 0xd8: return dis_line{ pc, 1, {b1,b2,b3},"RET C\n" };
	case 0xd9: return dis_line{ pc, 1, {b1,b2,b3},"RETI\n" };
	case 0xda: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "JP C,$%02x%02x\n", b3, b2); return l; }
	case 0xdb: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xdc: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "CALL C,$%02x%02x\n", b3, b2); return l; }
	case 0xdd: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xde: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "SBC A,$%02x\n", b2); return l; }
	case 0xdf: return dis_line{ pc, 1, {b1,b2,b3},"RST 18h\n" };
	case 0xe0: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD (FF00+$%02x),A\n", b2); return l; }
	case 0xe1: return dis_line{ pc, 1, {b1,b2,b3},"POP HL\n" };
	case 0xe2: return dis_line{ pc, 1, {b1,b2,b3},"LD (FF00+C),A\n" };
	case 0xe3: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xe4: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xe5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH HL\n" };
	case 0xe6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "AND A,$%02x\n", b2); return l; }
	case 0xe7: return dis_line{ pc, 1, {b1,b2,b3},"RST 20h\n" };
	case 0xe8: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "ADD SP,$%02x\n [%hhi]", b2, b2); return l; }
	case 0xe9: return dis_line{ pc, 1, {b1,b2,b3},"JP HL\n" };
	case 0xea: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "LD ($%02x%02x),A\n", b3, b2); return l; }
	case 0xeb: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xec: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xed: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xee: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "XOR A,$%02x\n", b2); return l; }
	case 0xef: return dis_line{ pc, 1, {b1,b2,b3},"RST 28h\n" };
	case 0xf0: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD A,(FF00+$%02x)\n", b2); return l; }
	case 0xf1: return dis_line{ pc, 1, {b1,b2,b3},"POP AF\n" };
	case 0xf2: return dis_line{ pc, 1, {b1,b2,b3},"LD A,(FF00+C)\n" };
	case 0xf3: return dis_line{ pc, 1, {b1,b2,b3},"DI\n" };
	case 0xf4: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xf5: return dis_line{ pc, 1, {b1,b2,b3},"PUSH AF\n" };
	case 0xf6: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "OR A,$%02x\n", b2); return l; }
	case 0xf7: return dis_line{ pc, 1, {b1,b2,b3},"RST 30h\n" };
	case 0xf8: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "LD HL,SP+$%02x\n [%hhi]", b2, b2); return l; }
	case 0xf9: return dis_line{ pc, 1, {b1,b2,b3},"LD SP,HL\n" };
	case 0xfa: {dis_line l = dis_line{ pc, 3, {b1,b2,b3},"" }; sprintf(l._text, "LD A,($%02x%02x)\n", b3, b2); return l; }
	case 0xfb: return dis_line{ pc, 1, {b1,b2,b3},"EI\n" };
	case 0xfc: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xfd: return dis_line{ pc, 1,  {b1,b2,b3}, "UNUSED\n" };
	case 0xfe: {dis_line l = dis_line{ pc, 2, {b1,b2,b3},"" }; sprintf(l._text, "CP A,$%02x\n", b2); return l; }
	case 0xff: return dis_line{ pc, 1, {b1,b2,b3},"RST 38h\n" };
	}

}









int main()
{

	// https://bytefreaks.net/programming-2/c/cc-full-example-of-reading-a-whole-binary-file-to-buffer
	FILE* fIn = fopen("C:\\Users\\pwnag\\Desktop\\retro\\my_GBC\\10-bit ops.gb", "rb");
	const int fseek_end_value = fseek(fIn, 0, SEEK_END); //Go to the end of the file
	long file_size = ftell(fIn); //Get the current position in the file (in bytes)
	const int fseek_set_value = fseek(fIn, 0, SEEK_SET); //Go back to the beginning of the file
	u8* bytes = (u8*)malloc(file_size); //Allocate enough space to read the whole file
	if (!bytes) exit(420);
	fread(bytes, 1, file_size, fIn); //Read the whole file to buffer
	fclose(fIn);
	//for (int i = 0; i < 0x102; i++) printf("%02x\n", buffer[i]);

	

	u16 pc = 0;
	while (pc < 0x8000 - 4)
	{
		dis_line r = disassemble(bytes, pc, file_size);
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