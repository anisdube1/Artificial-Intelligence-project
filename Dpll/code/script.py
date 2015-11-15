from itertools import combinations

max = ord("h")
symbols = []
for i in range(max+1-97):
    symbols.append(chr(i+97))
print(symbols)

combs = [''.join(p) for p in combinations(symbols, 3)]
print(combs)
for comb in combs:
    rest=""
    for symbol in symbols:
        if symbol not in comb:
            rest = rest + symbol

    print(comb, rest)
    str = "-"+comb[0]+" -"+comb[1]+" -"+comb[2]
    for i in range(len(rest)):
        print(str+" -"+rest[i])

