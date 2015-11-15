mymap = {}
mymap['painter'] = 'i'
mymap['stapler'] = 'j'
mymap['recharger'] = 'k'
mymap['welder'] = 'l'
mymap['cutter'] = 'm'
mymap['sander'] = 'n'
mymap['joiner'] = 'o'
mymap['gluer'] = 'p'

def inputKb(file_name, facts):
    clauses = []
    dict_symbols = {}
    symbols = []
    max = -100
    #cla = [claus.rstrip('\n') for claus in open('example.txt')]
    cla = [claus.rstrip('\n') for claus in open(file_name)]
    for fact in facts:
        cla.append(mymap[fact])
    for clau in cla:
        #clauses.append(Clause(clau))
        symb = clau.split()
        for symbol in symb:
            if "-" in symbol:
                symbol = symbol[1:]
            if ord(symbol) > max:
                max = ord(symbol)
    for i in range(max+1-97):
        symbols.append(chr(i+97))
    symbols.reverse()
    return cla, symbols



