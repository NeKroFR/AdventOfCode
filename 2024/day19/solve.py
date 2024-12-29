from functools import cache 

@cache
def count(design, op):
	if design == '':
		return True
		
	res = []
	for match in filter(lambda towel: design.startswith(towel), towels):
		remaining = design[len(match):]
		res.append(count(remaining, op))
	
	return op(res)


if __name__ == '__main__':
	lines = open("input.txt").read().splitlines()
	towels = lines[0].split(', ')
	designs = lines[2:]
	print("+----------------------------+\n| Advent of Code 2024 day 19 |\n+----------------------------+")
	part1 = sum(count(design, any) for design in designs)
	print('Part 1:', part1)
	part2 = sum(count(design, sum) for design in designs)
	print('Part 2:', part2)
