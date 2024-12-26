def part1(lines):
    # create filesystem
    fs = []
    is_file = True
    id = 0
    for x in lines:
        x = int(x)
        if is_file:
            fs += [id] * x
            id += 1
            is_file = False
        else:
            fs += [None] * x
            is_file = True
    
    # compress filesystem
    first_free = 0
    while fs[first_free] != None:
        first_free += 1
    
    i = len(fs) - 1
    while fs[i] == None:
        i -= 1

    while i > first_free:
        fs[first_free] = fs[i]
        fs[i] = None
        while fs[i] == None:
            i -= 1
        while fs[first_free] != None:
            first_free += 1
    

    res = 0
    for i, x in enumerate(fs):
        if x != None:
            res += i * x
    return res


def part2(lines):
    # files: (start position, size, file ID), spaces: (start position, size)
    files = []
    spaces = []
    is_file = True
    pos = 0
    file_id = 0

    for x in lines:
        x = int(x)
        if is_file:
            files.append((pos, x, file_id))
            pos += x
            file_id += 1
            is_file = False
        else:
            spaces.append((pos, x))
            pos += x
            is_file = True

    # create filesystem
    fs = [None] * pos
    for start, size, fid in files:
        for i in range(size):
            fs[start + i] = fid

    # move files into spaces
    for pos, size, fid in reversed(files):
        for space_idx, (space_start, space_size) in enumerate(spaces):
            if space_start < pos and size <= space_size:
                for i in range(size):
                    fs[pos + i] = None
                    fs[space_start + i] = fid
                spaces[space_idx] = (space_start + size, space_size - size)
                break
    res = 0
    for i, fid in enumerate(fs):
        if fid != None:
            res += i * fid
    return res


print("+----------------------------+\n| Advent of Code 2024 day 09 |\n+----------------------------+")
lines = open("./input.txt").read().strip()
print("Part 1:", part1(lines)) 
print("Part 2:", part2(lines))
