all: part1/result.txt part2/result.txt
	@echo ""
	@echo "+----------------------------+"
	@echo "| Advent of Code 2024 day 01 |"
	@echo "+----------------------------+"
	@echo "Part 1: $$(cat part1/result.txt)"
	@echo "Part 2: $$(cat part2/result.txt)"
	@echo ""

part1/result.txt: part1/obj_dir/Vtop
	@cd part1 && ./obj_dir/Vtop > ../$@

part1/obj_dir/Vtop: part1/top.sv part1/main.cpp part1/Makefile
	@cd part1 && make sim > /dev/null

part2/result.txt: part2/obj_dir/Vtop
	@cd part2 && ./obj_dir/Vtop > ../$@

part2/obj_dir/Vtop: part2/top.sv part2/main.cpp part2/Makefile
	@cd part2 && make sim > /dev/null

clean:
	@cd part1 && make clean > /dev/null 2>&1 || true
	@cd part2 && make clean > /dev/null 2>&1 || true
	@rm -f part1/result.txt part2/result.txt

.PHONY: all part1 part2 clean
