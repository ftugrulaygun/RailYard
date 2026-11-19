#include "Dispatcher.h"
#include <iostream>
#include <sstream>

void Dispatcher::cmdYard(const std::string &args)
{
    // TODO: YARD <numSidings> <sidingCapacity> <loopCapacity>   (Section 4.1)
    //  A new yard replaces the old one (yard = Yard(k, c, q);).
    //   "Yard built: <k> siding(s) of capacity <c>, loop capacity <q>."
    (void)args;
}

void Dispatcher::cmdTrain(const std::string &args)
{
    // TODO: TRAIN <n> <w1> ... <wn>   (Section 4.2)
    //   - the yard is not idle -> "Error: The yard is not empty."
    //   - otherwise read the n wagon numbers into a dynamic array, load the train
    //     and free the array -> "Train of <n> wagon(s) arrived."
    (void)args;
}

void Dispatcher::cmdMove(const std::string &args)
{
    std::istringstream ss(args);
    std::string fromName, toName;
    ss >> fromName >> toName;
    int from = 0, to = 0;
    parseTrack(fromName, from); // the input is well-formed, so both names are valid
    parseTrack(toName, to);

    // TODO: MOVE <from> <to>   (Section 4.3). The two track numbers are in 'from' and 'to'.
    //  Make the move with yard.move and print one of:
    //    "Moved <w> from <from> to <to>."
    //       and then, if the train is complete, "Train assembled in <m> move(s)."
    //    "Error: No track <name>."              (check 'from' first, then 'to')
    //    "Error: Cannot move from <from> to <to>."
    //    "Error: <from> is empty."
    //    "Error: Wagon <w> cannot depart before wagon <next>."
    //    "Error: <to> is full."
}

// GIVEN
void Dispatcher::processCommand(const std::string &line)
{
    std::istringstream ss(line);
    std::string cmd;
    if (!(ss >> cmd))
        return;
    std::string args;
    std::getline(ss, args);

    if (cmd == "YARD")
    {
        cmdYard(args);
        return;
    }
    if (cmd != "TRAIN" && cmd != "MOVE" && cmd != "PRINT")
    {
        std::cout << "Error: Unknown command '" << cmd << "'." << std::endl;
        return;
    }
    if (!yard.isBuilt())
    {
        std::cout << "Error: No yard." << std::endl;
        return;
    }
    if (cmd == "TRAIN")
        cmdTrain(args);
    else if (cmd == "MOVE")
        cmdMove(args);
    else
        yard.print();
}
