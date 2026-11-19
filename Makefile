# Builds ./RailYard (make works on Linux, macOS and Windows with MinGW).
# Without make:  g++ -std=c++11 *.cpp -o RailYard
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra
SRCS = $(wildcard *.cpp)

all: RailYard

RailYard: $(SRCS) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o RailYard $(SRCS)

# Memory check (Linux, needs valgrind):  make mem INPUT=Sample_IO_PA2/inputs/t1_basic.txt
mem: all
	valgrind --leak-check=full --track-origins=yes ./RailYard $(INPUT)

# Compares your output with every sample output (Linux / macOS):  make test IO=Sample_IO_PA2
IO ?= Sample_IO_PA2
test: all
	@for f in $(IO)/inputs/*.txt; do \
		name=$$(basename $$f); \
		if ./RailYard $$f | diff -q - $(IO)/outputs/$$name > /dev/null; \
		then echo "PASS $$name"; else echo "FAIL $$name  (diff <(./RailYard $$f) $(IO)/outputs/$$name)"; fi; \
	done

# Main line, part 1: compares the plan of your planGreedy with the expected plan on every
# public instance that has one (league/greedy_plans). The plans must be equal (Level 6).
greedy: all
	@for f in league/greedy_plans/*.txt; do name=$$(basename $$f); \
		if ./RailYard --greedy league/$$name | diff -q - $$f > /dev/null; \
		then echo "PASS $$name"; else echo "FAIL $$name  (diff <(./RailYard --greedy league/$$name) $$f)"; fi; \
	done

# Rail Yard League: plans every public instance with your planTrain, replays the plan
# with your own simulator and prints the number of moves (Level 6).
# Compare the result with league/reference_planners.txt.
league: all
	@for l in main long; do total=0; for f in league/$$l*.txt; do \
		./RailYard --plan $$f > plan.tmp; cat $$f plan.tmp > full.tmp; \
		last=$$(./RailYard full.tmp | tail -n 1); errors=$$(./RailYard full.tmp | grep -c '^Error'); \
		case "$$last" in \
			"Train assembled in "*) if [ $$errors -eq 0 ]; then m=$$(echo $$last | awk '{print $$4}'); \
				total=$$((total + m)); echo "$$(basename $$f): $$m moves"; \
				else echo "$$(basename $$f): NOT VALID ($$errors illegal moves)"; fi;; \
			*) echo "$$(basename $$f): NOT SOLVED";; \
		esac; done; echo "TOTAL $$l: $$total"; done; rm -f plan.tmp full.tmp

.PHONY: all mem test greedy league
