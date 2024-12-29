from functools import cache

@cache
def path(start, end):
    keypad = {
        '7': 0, '8': 1, '9': 2, 
        '4': 1j, '5': 1 + 1j, '6': 2 + 1j, 
        '1': 2j, '2': 1 + 2j, '3': 2 + 2j, 
        ' ': 3j, '0': 1 + 3j, 'A': 2 + 3j
    }

    remote = {
        ' ': 0, '^': 1, 'A': 2, 
        '<': 1j, 'v': 1 + 1j, '>': 2 + 1j
    }

    if start in keypad and end in keypad:
        pad = keypad
    else:
        pad = remote
    
    diff = pad[end] - pad[start]
    dx, dy = int(diff.real), int(diff.imag)
    
    vertical = ("^" * -dy) + ("v" * dy)
    horizontal = ("<" * -dx) + (">" * dx)
    
    invalid = pad[" "] - pad[start]
    prefer_vertical_first = (dx > 0 or invalid == dx) and invalid != dy * 1j
    if prefer_vertical_first:
        return vertical + horizontal + "A"
    else:
        return horizontal + vertical + "A"

@cache
def length(code, depth, s=0):
    if depth == 0:
        return len(code)
    
    for i, c in enumerate(code):
        s += length(path(code[i - 1], c), depth - 1)
    
    return s


if __name__ == "__main__":
    lines = open("input.txt").read().split()
    print("+----------------------------+\n| Advent of Code 2024 day 21 |\n+----------------------------+")
    part1 = sum(int(l[:-1]) * length(l, 3) for l in lines)
    print("Part1:",part1)
    part2 = sum(int(l[:-1]) * length(l, 26) for l in lines)
    print("Part2:",part2)
