from dpll import *

def pure_symbol(clauses, symbols, model):
    un_clauses = unassigned_clauses(clauses, model)
    mymap = {}
    for clause in un_clauses:
        clau_symbols = clause.split()
        for clau_symbol in clau_symbols:
            negation = 1
            r_symbol = clau_symbol
            if "-" in clau_symbol:
                r_symbol = clau_symbol[1:]
                negation = -1
            if r_symbol not in mymap:
                mymap[r_symbol] = negation
            else:
                if mymap[r_symbol] != negation:
                    mymap[r_symbol] = 0
    symbols.reverse()
    for symbol in symbols:
        if symbol in mymap and mymap[symbol] != 0:
            return symbol, mymap[symbol]
    return "", ""

def unit_clause(clauses, symbols, model):
    un_clauses = unassigned_clauses(clauses, model)
    unit_cl_symbol = []
    unit_cl = []
    for clau in un_clauses:
        unassigned = 0
        symbols = clau.split()
        for symbol in symbols:
            r_symbol = symbol
            if "-" in symbol:
                r_symbol = symbol[1:]
            if model[r_symbol] == -1:
                unassigned = unassigned+1
                unit_symbol = symbol
        if unassigned == 1:
            unit_cl_symbol.append(unit_symbol)
            unit_cl.append(clau)
    if len(unit_cl_symbol) > 0:
        return unit_cl_symbol[0], unit_cl[0]
    else:
        return unit_cl_symbol, unit_cl

def unassigned_clauses(clauses, model):
    unassigned_clause =[]
    for clause in clauses:
        if expression_solver(clause, model, 0) == 0:
            unassigned_clause.append(clause)
    return unassigned_clause