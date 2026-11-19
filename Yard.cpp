#include "Yard.h"
#include <iostream>

// ---------------------------------------------------------------- track names (GIVEN)

std::string trackName(int track)
{
    if (track == TRACK_A)
        return "A";
    if (track == TRACK_D)
        return "D";
    if (track == TRACK_L)
        return "L";
    return "S" + std::to_string(track);
}

bool parseTrack(const std::string &name, int &track)
{
    if (name == "A")
        track = TRACK_A;
    else if (name == "D")
        track = TRACK_D;
    else if (name == "L")
        track = TRACK_L;
    else
    {
        if (name.size() < 2 || name.size() > 5 || name[0] != 'S' || name[1] == '0')
            return false;
        int number = 0;
        for (std::string::size_type i = 1; i < name.size(); ++i)
        {
            if (name[i] < '0' || name[i] > '9')
                return false;
            number = number * 10 + (name[i] - '0');
        }
        track = number;
    }
    return true;
}

// ---------------------------------------------------------------- Yard

Yard::Yard(int _numSidings, int _sidingCapacity, int _loopCapacity)
    : sidings(nullptr), numSidings(_numSidings), sidingCapacity(_sidingCapacity),
      loopCapacity(_loopCapacity), trainSize(0), departed(0), moves(0)
{
    // TODO: Allocate numSidings empty sidings.
}

Yard::~Yard()
{
    // TODO: Free the array of sidings. This must also work for a yard that is not built.
}

Yard::Yard(const Yard &other)
    : sidings(nullptr), numSidings(0), sidingCapacity(0), loopCapacity(0),
      trainSize(0), departed(0), moves(0)
{
    // TODO: Deep copy: every siding, the loop, the arrival track and all counters.
    //  A copy of a yard that is not built is not built.
    (void)other;
}

Yard &Yard::operator=(const Yard &other)
{
    // TODO: Deep copy. The old sidings must not leak, y = y must change nothing, and it
    //  must work when other (or *this) is not built.
    (void)other;
    return *this;
}

bool Yard::hasTrack(int track) const
{
    // TODO: A, D, the sidings 1 .. numSidings, and L only if loopCapacity > 0.
    (void)track;
    return false;
}

bool Yard::isIdle() const
{
    // TODO: true if A, every siding and the loop are empty.
    return true;
}

bool Yard::isAssembled() const
{
    // TODO: true if a train has arrived and all of its wagons are in D.
    return false;
}

void Yard::loadTrain(const int *wagons, int n)
{
    // TODO: The wagons enter A in the given order (wagons[0] is the front).
    //  trainSize = n, departed = 0, moves = 0.
    (void)wagons;
    (void)n;
}

bool Yard::movable(int track, int &wagon) const
{
    // TODO: The front of A or L, or the top of a siding. false if there is none.
    (void)track;
    (void)wagon;
    return false;
}

MoveResult Yard::check(int from, int to) const
{
    // TODO: The checks in the order of MoveResult (Section 1.2):
    //   1. both tracks exist in this yard          -> NO_SUCH_TRACK
    //   2. not from D, not to A, not from == to    -> ILLEGAL_MOVE
    //   3. there is a wagon on 'from'              -> SOURCE_EMPTY
    //   4. to D: the wagon is nextWagon()          -> WRONG_WAGON
    //   5. to a siding or the loop: it has room    -> TARGET_FULL
    (void)from;
    (void)to;
    return NO_SUCH_TRACK;
}

MoveResult Yard::move(int from, int to)
{
    // TODO: If check(from, to) is not MOVE_OK, return it and change nothing.
    //  Otherwise take the wagon from 'from', put it on 'to' (for D: departed grows
    //  by one), count the move and return MOVE_OK.
    (void)from;
    (void)to;
    return NO_SUCH_TRACK;
}

// GIVEN. A is printed from the front, a siding from the bottom, L from the front.
void Yard::print() const
{
    std::cout << "--- Yard: " << departed << " of " << trainSize << " departed, " << moves
              << " move(s) ---" << std::endl;
    std::cout << "A:";
    for (int i = 0; i < arrival.size(); ++i)
        std::cout << " " << arrival.get(i);
    std::cout << std::endl;
    for (int s = 1; s <= numSidings; ++s)
    {
        std::cout << "S" << s << ":";
        for (int i = 0; i < sidings[s - 1].size(); ++i)
            std::cout << " " << sidings[s - 1].get(i);
        std::cout << std::endl;
    }
    if (loopCapacity > 0)
    {
        std::cout << "L:";
        for (int i = 0; i < loop.size(); ++i)
            std::cout << " " << loop.get(i);
        std::cout << std::endl;
    }
}
