#ifndef PLANNER_H
#define PLANNER_H

#include "Yard.h"
#include "MoveList.h"

/** Level 6, the planners (Planner.cpp).
 *  Every planner gets 'start', a yard on which a train has just arrived (no move has been
 *  made yet), and fills 'plan' with moves that assemble the train: after the last move
 *  every wagon must be in D, and every move must be legal when it is made.
 *
 *  'start' is read-only: copy it (Yard yard = start;) and make the moves on your copy
 *  while you plan.
 */

/// GIVEN. A simple planner that always works: park the whole train, then dig it out.
void planRookie(const Yard &start, MoveList &plan);

/// YOU (Main line). The greedy yard master of Section 6.2, exactly as described there.
/// Every move of your plan is compared with the move of the greedy rule (Section 6.2).
void planGreedy(const Yard &start, MoveList &plan);

/// YOU (Main line and Long haul). Your own planner: any legal plan, shorter is better.
/// The starter version simply returns the greedy plan.
void planTrain(const Yard &start, MoveList &plan);

#endif
