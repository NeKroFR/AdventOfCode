import itertools

def part1(lines):
    res = 0
    for l in lines:
        res += solve(l, ['+', '*'])
    print("part1:",res)

def part2(lines):
    res = 0
    for l in lines:
        res += solve(l, ['+', '*', '||'])
    print("part2:",res)

def solve(l, os):
    d = [int(x) for x in l.split()]
    ans = d[0] 
    vals = d[1:]
    for o in list(itertools.product(os, repeat=len(vals) - 1)):
        exp = str(vals[0])
        for i, op in enumerate(o):
            exp += f" {op} {vals[i + 1]}"
        r = eval(exp.split())
        if r == ans:
            return r
    return 0

def eval(exp):
    res = int(exp[0])
    for i in range(1, len(exp), 2):
        o = exp[i]
        n = int(exp[i + 1])
        if o == '+':
            res += n
        elif o == '*':
            res *= n
        elif o == '||':
            res = int(f"{res}{n}")
    return res

print("+----------------------------+\n| Advent of Code 2024 day 07 |\n+----------------------------+")
lines = open("input.txt").read().replace(":","").splitlines()
part1(lines)
part2(lines)
