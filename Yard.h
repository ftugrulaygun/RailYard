#ifndef YARD_H
#define YARD_H

#include <string>
#include "WagonStack.h"
#include "WagonQueue.h"

// Track numbers. The sidings S1, S2, ... have the numbers 1, 2, ...
const int TRACK_A = 0;  // arrival track
const int TRACK_D = -1; // departure track
const int TRACK_L = -2; // loop track

// The name of a track ("A", "D", "L", "S3"). GIVEN.
std::string trackName(int track);

// Reads a track name. Returns false if 'name' is not A, D, L or S<number>. GIVEN.
bool parseTrack(const std::string &name, int &track);

// Why a move is possible or not. If several reasons apply, the first one in this
// order is reported (NO_SUCH_TRACK before ILLEGAL_MOVE, and so on).
enum MoveResult
{
    MOVE_OK,
    NO_SUCH_TRACK, // 'from' or 'to' is not a track of this yard
    ILLEGAL_MOVE,  // from D, to A, or from a track to itself
    SOURCE_EMPTY,  // there is no wagon on 'from'
    WRONG_WAGON,   // to D, but the wagon is not the next one of the train
    TARGET_FULL    // the siding or the loop is full
};

/** The marshalling yard.
 *   - numSidings sidings (stacks), each may hold at most sidingCapacity wagons;
 *   - one loop track (a queue) that may hold at most loopCapacity wagons
 *     (loopCapacity 0: the yard has no loop);
 *   - the arrival track A (a queue) and the departure track D.
 *  The wagons of a train are numbered 1 .. trainSize and must enter D in that order.
 */
class Yard
{
private:
    WagonStack *sidings; // dynamic array of numSidings stacks (sidings[0] is S1), nullptr if not built
    int numSidings;
    int sidingCapacity;
    WagonQueue loop;
    int loopCapacity;
    WagonQueue arrival;
    int trainSize; // wagons of the current train, 0 before the first train
    int departed;  // wagons that have entered D
    int moves;     // successful moves since the train arrived

public:
    Yard() : sidings(nullptr), numSidings(0), sidingCapacity(0), loopCapacity(0),
             trainSize(0), departed(0), moves(0) {} // a yard that is not built yet
    Yard(int _numSidings, int _sidingCapacity, int _loopCapacity);
    ~Yard();

    // Rule of Three: a Yard owns its array of sidings, so copies must be deep.
    // Both must also work when 'other' (or *this) is not built.
    Yard(const Yard &other);
    Yard &operator=(const Yard &other);

    bool isBuilt() const { return sidings != nullptr; }
    int getNumSidings() const { return numSidings; }
    int getSidingCapacity() const { return sidingCapacity; }
    int getLoopCapacity() const { return loopCapacity; }
    int getTrainSize() const { return trainSize; }
    int getDeparted() const { return departed; }
    int getMoves() const { return moves; }

    // The wagon that must enter D next.
    int nextWagon() const { return departed + 1; }

    // Read-only access. Precondition for getSiding: 1 <= s <= numSidings.
    const WagonStack &getSiding(int s) const { return sidings[s - 1]; }
    const WagonQueue &getLoop() const { return loop; }
    const WagonQueue &getArrival() const { return arrival; }

    // true for A, D, the sidings 1 .. numSidings, and L if loopCapacity > 0.
    bool hasTrack(int track) const;

    // true if there is no wagon on A, on the sidings and on the loop.
    bool isIdle() const;

    // true if a train has arrived and all of its wagons have entered D.
    bool isAssembled() const;

    // A new train arrives on A: wagons[0] is at the front. trainSize = n, departed = 0,
    // moves = 0. Precondition: the yard is built and isIdle().
    void loadTrain(const int *wagons, int n);

    // The wagon that a move from 'track' would take: the front of A or L, the top of a
    // siding. Returns false (and does not change 'wagon') if the track is empty, is D,
    // or is not a track of this yard.
    bool movable(int track, int &wagon) const;

    // Checks a move without making it (see MoveResult for the order of the checks).
    MoveResult check(int from, int to) const;

    // Makes the move if check(from, to) is MOVE_OK: the wagon leaves 'from' and enters
    // 'to' (the top of a siding, the rear of the loop, or D), and moves grows by one.
    // Otherwise nothing changes. Returns the result of the check.
    MoveResult move(int from, int to);

    // Prints the yard (PRINT format). GIVEN.
    void print() const;
};

#endif
