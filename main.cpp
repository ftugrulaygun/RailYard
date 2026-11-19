#include "Dispatcher.h"
#include "Planner.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/* GIVEN. You do not submit main.cpp (the grader uses its own copy).
 *
 *   ./RailYard <input file>               runs the commands of the file (Levels 1-4)
 *   ./RailYard --greedy <instance file>   prints the plan of planGreedy (Level 6)
 *   ./RailYard --plan <instance file>     prints the plan of planTrain (Level 6)
 *   ./RailYard --rookie <instance file>   prints the plan of planRookie (Level 6)
 *
 * An instance file has two lines, YARD and TRAIN. The plan is printed as MOVE lines,
 * so "instance + plan" is an input file for the first mode.
 */

static int runCommands(const char *path)
{
    std::ifstream infile(path);
    if (!infile)
    {
        std::cerr << "Error: Cannot open input file " << path << std::endl;
        return 1;
    }
    Dispatcher dispatcher;
    std::string line;
    while (std::getline(infile, line))
    {
        if (!line.empty() && line[line.size() - 1] == '\r') // Windows line endings
            line.erase(line.size() - 1);
        if (line.empty() || line[0] == '#') // empty lines and comment lines are skipped
            continue;
        dispatcher.processCommand(line);
    }
    return 0;
}

static int runPlanner(const char *path, void (*planner)(const Yard &, MoveList &))
{
    std::ifstream infile(path);
    if (!infile)
    {
        std::cerr << "Error: Cannot open instance file " << path << std::endl;
        return 1;
    }
    std::string word;
    int k = 0, c = 0, q = 0, n = 0;
    infile >> word >> k >> c >> q; // YARD k c q
    infile >> word >> n;           // TRAIN n w1 ... wn
    if (!infile || n < 1)
    {
        std::cerr << "Error: Not an instance file: " << path << std::endl;
        return 1;
    }
    int *wagons = new int[n];
    for (int i = 0; i < n; ++i)
        infile >> wagons[i];

    Yard yard(k, c, q);
    yard.loadTrain(wagons, n);
    delete[] wagons;

    MoveList plan;
    planner(yard, plan);

    std::ostringstream out; // one write at the end is much faster than one per move
    for (int i = 0; i < plan.size(); ++i)
        out << "MOVE " << trackName(plan.get(i).from) << " " << trackName(plan.get(i).to) << "\n";
    std::cout << out.str();
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 3 && std::string(argv[1]) == "--plan")
        return runPlanner(argv[2], planTrain);
    if (argc == 3 && std::string(argv[1]) == "--greedy")
        return runPlanner(argv[2], planGreedy);
    if (argc == 3 && std::string(argv[1]) == "--rookie")
        return runPlanner(argv[2], planRookie);
    if (argc == 2)
        return runCommands(argv[1]);
    std::cerr << "Usage: ./RailYard <input file>   or   ./RailYard --greedy|--plan|--rookie <instance file>" << std::endl;
    return 1;
}
