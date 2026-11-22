#include "Planner.h"

/* Level 6. The three planners of Planner.h:
 *   planRookie  GIVEN, an example of a planner. Read it before you start.
 *   planGreedy  YOU, the greedy yard master of Section 6.2.
 *   planTrain   YOU, your own planner (Section 6.3).
 * You may add helper functions to this file (make them static).
 */

// Makes a move on the working copy of the yard and writes it into the plan.
static void go(Yard &yard, MoveList &plan, int from, int to)
{
    yard.move(from, to);
    plan.add(from, to);
}

// ---------------------------------------------------------------- Rookie (GIVEN)

// The first siding with room that is not 'except' (0 if there is none).
static int sidingWithRoom(const Yard &yard, int except)
{
    for (int s = 1; s <= yard.getNumSidings(); ++s)
        if (s != except && yard.getSiding(s).size() < yard.getSidingCapacity())
            return s;
    return 0;
}

//  1. Park the whole train: every wagon goes from A to the first siding that has room.
//  2. Dig the wagons out in order: move the wagons above the next wagon to other
//     sidings, then send the next wagon to D.
// Step 2 cannot get stuck in a League yard (Section 6.1 explains why).
void planRookie(const Yard &start, MoveList &plan)
{
    Yard yard = start; // work on a copy

    while (!yard.getArrival().isEmpty())
        go(yard, plan, TRACK_A, sidingWithRoom(yard, 0));

    while (!yard.isAssembled())
    {
        int next = yard.nextWagon();
        int home = 0; // the siding that holds the next wagon
        for (int s = 1; s <= yard.getNumSidings() && home == 0; ++s)
            if (yard.getSiding(s).indexOf(next) != -1)
                home = s;

        int above = yard.getSiding(home).size() - 1 - yard.getSiding(home).indexOf(next);
        for (int i = 0; i < above; ++i)
            go(yard, plan, home, sidingWithRoom(yard, home));
        go(yard, plan, home, TRACK_D);
    }
}

// ---------------------------------------------------------------- Greedy (YOU)
static int chooseSiding(const Yard &yard, int w, int except)
{
    int bestGood = 0;
    int bestGoodKey = 0;

    int bestOther = 0;
    int bestOtherTop = 0;

    int BIG = yard.getTrainSize() + 1;

    for(int i = 1; i <= yard.getNumSidings(); i++)
    {
        if((i == except) || (yard.getSiding(i).size() >= yard.getSidingCapacity()))
        {
            continue;
        }

        int key;
        if(yard.getSiding(i).isEmpty())
        {
            key = BIG;
        }else
        {
            yard.getSiding(i).peek(key);
        }

        if(key > w)
        {
            if(bestGood == 0 || key < bestGoodKey)
            {
                bestGood = i;
                bestGoodKey = key;
            }else
            {
                if(bestOther == 0 || key > bestOtherTop)
                {
                    bestOther = i;
                    bestOtherTop = key;
                }
            }
        }
    }
}

void planGreedy(const Yard &start, MoveList &plan)
{
    // TODO: Section 6.2. Work on a copy of 'start'. Until the train is assembled:
    //    1. If the next wagon is at the front of A or on top of a siding, send it to D.
    //    2. Otherwise move the wagon in front of it (the front wagon of A, or the top
    //       wagon of its siding) to the siding that the greedy rule chooses.
    //  Follow the rule exactly: every move of your plan is compared with the move of the rule.
    Yard yard = start;

    while(!yard.isAssembled())
    {
        int x = yard.nextWagon();
        int w = 0;

        if(yard.movable(TRACK_A, w) && (w == x))
        {
            go(yard, plan, TRACK_A, TRACK_D);
            continue;
        }

        int top = 0;
        for(int i = 1; i <= yard.getNumSidings(); i++)
        {
            if(yard.movable(i, w) && w == x)
            {
                top = i;
            }
        }

        if(top != 0)
        {
            go(yard, plan, top, TRACK_D);
            continue;
        }

        int source = 0;
        if(yard.getArrival().indexOf(x) == -1)
        {
            for(int j = 1; j <= yard.getNumSidings(); j++)
            {
                if(yard.getSiding(j).indexOf(x) != -1)
                {
                    source = j;
                }
            }
        }
        yard.movable(source, w);

        int target;

        target = chooseSiding(yard, w, source);
        go(yard, plan, source, target);
    }
    
    
}

// ---------------------------------------------------------------- your planner (YOU)

void planTrain(const Yard &start, MoveList &plan)
{
    // TODO: Section 6.3: your own planner. Any legal plan counts and shorter is better.
    //  You may start from the greedy plan and improve it, or write something new.
    planGreedy(start, plan); // the greedy plan until you have something better
}
