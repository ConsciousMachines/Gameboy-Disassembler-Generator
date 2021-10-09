

file = open(r'C:\Users\pwnag\Desktop\gbops - The Game Boy opcode table.htm',mode='r')
all_of_it = file.read()
file.close()
all_of_it = all_of_it.replace('\n', ' ')
opcodes = all_of_it.split('class="opcode')[1:] 


# THIS SECTION OF CODE IS FOR INSTR 0-255
for i in range(len(opcodes[:256])):
    hex_idx = hex(i)[2:].rjust(2,"0")

    entry = opcodes[i]
    number = entry.split('data-index="')[1].split('"')[0]
    if entry.__contains__('unused'):
        full_instr = f'case 0x{hex_idx}: return dis_line{{ pc, 1, {{b1,b2,b3}}, "UNUSED\\n" }};'
        print(full_instr)
        continue
    text = entry.split('<pre>')[1].split('</pre>')[0]

    assert text.count('t') <= 2, "more than 2 t's found!"
    time = text.split('t')[0]

    parts = time.split(' ')
    size = parts[-2]
    assert int(size) <= 3, 'wrong size?'

    parts2 = parts[:-2]
    instr = ' '.join(parts2)
    
    if int(size) == 1:
        full_instr = f'case 0x{hex_idx}: return dis_line{{ pc, {size}, {{b1,b2,b3}},"{instr}\\n" }};'
    elif int(size) == 2:
        if (instr.__contains__('u8')): # immediate unsigned u8
            instr2 = instr.replace('u8', '$%02x') + '\\n'
            full_instr = f'case 0x{hex_idx}: {{dis_line l = dis_line{{ pc, {size}, {{b1,b2,b3}},"" }}; sprintf(l._text, "{instr2}", b2); return l;}}'
        elif (instr.__contains__('i8')): #immediate signed i8, JR
            instr2 = instr.replace('i8', '$%02x') + '\\n'
            full_instr = f'case 0x{hex_idx}: {{dis_line l = dis_line{{ pc, {size}, {{b1,b2,b3}},"" }}; sprintf(l._text, "{instr2} [%hhi]", b2,b2); return l;}}'
        else: # STOP instruction 
            full_instr = f'case 0x{hex_idx}: return dis_line{{ pc, {size}, {{b1,b2,b3}},"{instr}\\n" }};'

    elif int(size) == 3:
        instr2 = instr.replace('u16', '$%02x%02x') + '\\n'
        full_instr = f'case 0x{hex_idx}: {{dis_line l = dis_line{{ pc, {size}, {{b1,b2,b3}},"" }}; sprintf(l._text, "{instr2}", b3, b2); return l;}}'

    print(full_instr)





# CB INSTRUCTIONS
for i in range(256, len(opcodes)):
    hex_idx = hex(i)[2:].rjust(2,"0")

    entry = opcodes[i]
    number = entry.split('data-index="')[1].split('"')[0]
    text = entry.split('<pre>')[1].split('</pre>')[0]

    assert text.count('t') <= 2, "more than 2 t's found!"
    time = text.split('t')[0]

    parts = time.split(' ')
    size = parts[-2]
    assert int(size) <= 3, 'wrong size?'

    parts2 = parts[:-2]
    instr = ' '.join(parts2)

    hex_idx2 = hex(i-256)[2:].rjust(2,"0")
    full_instr = f'case 0x{hex_idx2}: return dis_line{{ pc, {size}, {{0xCB,b2,0x00}},"{instr}\\n" }};'
    print(full_instr)


