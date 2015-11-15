from inputKb import *
from heuristics import *
import sys
import copy
ite = 0

unit_clause_flag = 0
pure_symbol_flag = 0

def expression_solver(claus, model, flag):
    symbols = claus.split()
    sum = 0
    neg_literal = 0
    for symbol in symbols:
        negation = 1
        r_symbol = symbol
        if "-" in symbol:
            r_symbol = symbol[1:]
            negation = -1
        if negation == -1 and model[r_symbol] == 1:
            sum = sum + 0
        elif negation == -1 and model[r_symbol] == 0:
            sum = sum + 1
        elif model[r_symbol] == -1:
            sum = sum + 0
            neg_literal = neg_literal + 1
        else:
            sum = sum + model[r_symbol]
    if sum == 0:
        if flag == 0:
            return 0
        elif flag == 1 and neg_literal == 0:
            return 0
        else:
            return 1
    else:
        return 1

def dpll_satis(clauses, symbols, model):
    #Implementing if all clauses are true
    sum = 0
    global ite
    ite = ite + 1
    print("Iteration", ite)
    for i, clau in enumerate(clauses):
        #print(clau.clause)
        sum = sum + expression_solver(clau, model, 0)
    if sum == len(clauses) and len(symbols) == 0:
        return True

    #Implementing if any clause is false
    sum = 0
    for i, clau in enumerate(clauses):
        sum = sum + expression_solver(clau, model, 1)
    if sum != len(clauses):
        return False

    # Applying Pure Symbol Heuristic
    if pure_symbol_flag:
        pu_symbol, pu_value = pure_symbol(clauses, symbols, model)
        if len(pu_symbol) > 0:
            print("Pure_symbol on ",pu_symbol," =",(True if pu_value == 1 else False))
            model[pu_symbol] = 1 if pu_value == 1 else 0
            print_app_model(model)
            ind = symbols.index(pu_symbol)
            symbols.remove(pu_symbol)
            if dpll_satis(clauses, symbols, model):
                return True
            else:
                symbols.insert(ind, pu_symbol)
                model[pu_symbol] = -1
                return False

    #Applying Unit Clause Heuristic
    if unit_clause_flag:
        unit_symbol, un_clause = unit_clause(clauses, symbols, model)
        if len(unit_symbol) > 0:
            r_symbol = unit_symbol
            if "-" in unit_symbol:
                r_symbol = unit_symbol[1:]
                model[r_symbol] = 0
            else:
                model[unit_symbol] = 1
            print("Unit Clause on ", un_clause , "implies ",r_symbol," =",(True if model[r_symbol] == 1 else False))
            print_app_model(model)
            ind = symbols.index(r_symbol)
            symbols.remove(r_symbol)
            if dpll_satis(clauses, symbols, model):
                return True
            else:
                symbols.insert(ind, r_symbol)
                model[r_symbol] = -1
                return False

    if len(symbols) > 0:
        symbol = symbols.pop()

        print("trying", symbol, "= T")
        model[symbol] = 1
        print_app_model(model)
        if (dpll_satis(clauses, symbols, model)):
            return True
        else:
            print("trying", symbol, "= F")
            model[symbol] = 0
            print_app_model(model)
            if (dpll_satis(clauses, symbols, model)):
                return True

        print("backtracking")
        model[symbol] = -1
        symbols.append(symbol)
    else:
        return True

def print_model(model):
    true_prop =[]
    for key in sorted(model.keys()):
        if model[key] == 0:
            print(key, " = False")
        elif model[key] == 1:
            print(key, " = True")
            true_prop.append(key)

    print("True Prop ", true_prop)
    print("Mapping", mymap)

def print_app_model(model):
    new_model = copy.deepcopy(model)
    for key in model:
        if model[key] == 0:
            new_model[key] = "False"
        elif model[key] == 1:
            new_model[key] = "True"
        else:
            new_model.pop(key)
    print("Model ", new_model)

if __name__ == "__main__":
    # a = input()
    # a = a.split()
    a = sys.argv
    if len(a) == 0:
        sys.exit("Insufficient Argument")
    else:
        file_name = a[1]
        pure_symbol_flag = int(a[2])
        unit_clause_flag = int(a[3])
        facts = a[4:]
    expression, symbols = inputKb(file_name, facts)
    model = {}
    for symbol in symbols:
        model[symbol] = -1
    is_satisfiable = dpll_satis(expression, symbols, model)
    if is_satisfiable:
        print("Iteration", ite)
        print_model(model)
        print("Solution Reached")
    else:
        print("Solution Not Reached")

    # model['f'] = 0
    # symbols.remove('f')
    #
    # model['e'] = 0
    # symbols.remove('e')
    #
    # # model['j'] = 0
    # # model['l'] = 0
    # symbol, value = pure_symbol(expression, symbols, model)
    # print(symbol, value)

#workers.txt 1 1 painter sander gluer joiner
#workers.txt 1 1 cutter welder painter joiner recharger
