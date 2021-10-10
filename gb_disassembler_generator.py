file = open(r'C:\Users\pwnag\Desktop\gbops - The Game Boy opcode table.htm',mode='r')
all_of_it = file.read()
file.close()
all_of_it = all_of_it.replace('\n', ' ')
opcodes = all_of_it.split('class="opcode')[1:] 


cat2int = {'control misc' : 0, 'control br' : 1, 'x16 lsm' : 2, 'x8 alu' : 3, 'x8 rsb' : 4, 'x8 lsm' : 5, 'unused' : 6, 'x16 alu' : 7}

# THIS SECTION OF CODE IS FOR INSTR 0-255
for i in range(len(opcodes[:256])):
    hex_idx = hex(i)[2:].upper().rjust(2,"0")
    entry = opcodes[i]
    category = entry.split('"')[0].strip()
    cat_int = cat2int[category]

    if entry.__contains__('unused'): # for the unused opcodes 
        full_instr = f'case 0x{hex_idx}: return dis_line{{ pc, 1, {{b1,b2,b3}}, "UNUSED\\0", {cat_int} }};'
        print(full_instr)
        continue

    text = entry.split('<pre>')[1].split('</pre>')[0]
    assert text.count('t') <= 2, "more than 2 t's found!"
    parts = text.split('t')[0].split(' ')
    size = parts[-2]
    assert int(size) <= 3, 'wrong size?'
    instr = ' '.join(parts[:-2])
    
    if int(size) == 1:
        full_instr = f'case 0x{hex_idx}: return dis_line{{ pc, {size}, {{b1,b2,b3}},"{instr}\\0", {cat_int} }};'

    elif int(size) == 2:
        if (instr.__contains__('u8')): # immediate unsigned u8
            instr2 = instr.replace('u8', '$%02x') 
            full_instr = f'case 0x{hex_idx}: {{dis_line l = dis_line{{ pc, {size}, {{b1,b2,b3}},"" , {cat_int} }}; sprintf(l._text, "{instr2}\\0", b2); return l;}}'
        elif (instr.__contains__('i8')): #immediate signed i8, JR
            instr2 = instr.replace('i8', '$%02x') 
            full_instr = f'case 0x{hex_idx}: {{dis_line l = dis_line{{ pc, {size}, {{b1,b2,b3}},"" , {cat_int} }}; sprintf(l._text, "{instr2} [%hhi]\\0", b2,b2); return l;}}'
        else: # STOP instruction 
            full_instr = f'case 0x{hex_idx}: return dis_line{{ pc, {size}, {{b1,b2,b3}},"{instr}\\0" , {cat_int} }};'

    elif int(size) == 3:
        instr2 = instr.replace('u16', '$%02x%02x')
        full_instr = f'case 0x{hex_idx}: {{dis_line l = dis_line{{ pc, {size}, {{b1,b2,b3}},"" , {cat_int} }}; sprintf(l._text, "{instr2}\\0", b3, b2); return l;}}'

    print(full_instr)





# CB INSTRUCTIONS
for i in range(256, len(opcodes)):
    entry = opcodes[i]
    category = entry.split('"')[0].strip()
    cat_int = cat2int[category]
    text = entry.split('<pre>')[1].split('</pre>')[0]
    assert text.count('t') <= 2, "more than 2 t's found!"
    parts = text.split('t')[0].split(' ')
    size = parts[-2]
    assert int(size) <= 3, 'wrong size?'
    instr = ' '.join(parts[:-2])

    hex_idx2 = hex(i - 256)[2:].upper().rjust(2,"0")
    full_instr = f'case 0x{hex_idx2}: return dis_line{{ pc, {size}, {{0xCB,0x{hex_idx2},0x00}},"{instr}\\0" , {cat_int} }};'
    print(full_instr)

