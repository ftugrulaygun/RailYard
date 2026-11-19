#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <string>
#include "Yard.h"

/** The controller: owns the yard and executes the commands of the input file.
 *  It needs no destructor, copy constructor or assignment of its own: the yard
 *  cleans up after itself.
 */
class Dispatcher
{
private:
    Yard yard;

    // Command handlers
    void cmdYard(const std::string &args);
    void cmdTrain(const std::string &args);
    void cmdMove(const std::string &args);

public:
    // Reads the command word of one input line and calls the right handler. GIVEN.
    void processCommand(const std::string &line);
};

#endif
