#include "Dispatcher.h"
#include <iostream>
#include <sstream>

void Dispatcher::cmdYard(const std::string &args)
{
    // TODO: YARD <numSidings> <sidingCapacity> <loopCapacity>   (Section 4.1)
    //  A new yard replaces the old one (yard = Yard(k, c, q);).
    //   "Yard built: <k> siding(s) of capacity <c>, loop capacity <q>."
    int k;
    int c;
    int q;
    std::istringstream ss(args);
    ss >> k >> c >> q;
    yard = Yard(k, c, q);
    
    std::cout << "Yard built: " << k << " siding(s) of capacity " << c << ", loop capacity " << q << "." << std::endl;
}

void Dispatcher::cmdTrain(const std::string &args)
{
    // TODO: TRAIN <n> <w1> ... <wn>   (Section 4.2)
    //   - the yard is not idle -> "Error: The yard is not empty."
    //   - otherwise read the n wagon numbers into a dynamic array, load the train
    //     and free the array -> "Train of <n> wagon(s) arrived."
    if(!yard.isIdle())
    {
        std::cout << "Error: The yard is not empty." << std::endl;
        return;
    }

    int count;
    int train;
    std::istringstream ss(args);
    ss >> count;

    int* newAr = new int[count];
    for(int i = 0; i <= count-1; i++)
    {   
        ss >> train;
        newAr[i] = train;
    }

    yard.loadTrain(newAr, count);
    delete[] newAr;

    std::cout << "Train of " << count << " wagon(s) arrived." << std::endl;
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
    int wagon;
    yard.movable(from, wagon);
    MoveResult result = yard.move(from, to);
    if(result == MOVE_OK)
    {
        std::cout << "Moved " << wagon << " from " << fromName << " to " << toName << "." << std::endl;
        if(yard.isAssembled())
        {
           std::cout << "Train assembled in " << yard.getMoves() << " move(s)." << std::endl; 
        }
    }else if(result == NO_SUCH_TRACK)
    {
        if(!yard.hasTrack(from))
        {
            std::cout << "Error: No track " << fromName << "." << std::endl;   
        }else{
            std::cout << "Error: No track " << toName << "." << std::endl;     
        }
    }else if(result == ILLEGAL_MOVE)
    {
        std::cout << "Error: Cannot move from " << fromName << " to " << toName << "." << std::endl;
    }else if(result == SOURCE_EMPTY)
    {
        std::cout << "Error: " << fromName << " is empty." << std::endl;
    }else if(result == WRONG_WAGON)
    {
        std::cout << "Error: Wagon " << wagon << " cannot depart before wagon " << yard.nextWagon() << "." << std::endl;
    }else if(result == TARGET_FULL)
    {
       std::cout << "Error: " << toName << " is full." << std::endl; 
    }
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
