#ifndef WAGON_STACK_H
#define WAGON_STACK_H

/** A stack of wagon numbers in a dynamically allocated array: one siding of the yard.
 *  data[0] is the bottom (the wagon at the dead end), data[top] is the top (the wagon
 *  at the entrance, the only one that can leave).
 *
 *  The stack itself has no size limit: when the array is full it doubles.
 *  The capacity of a siding is enforced by the Yard, not here.
 */
class WagonStack
{
private:
    int *data;    // dynamic array of 'capacity' wagon numbers
    int capacity; // length of the array
    int top;      // index of the top wagon, -1 if the stack is empty

    // Replaces 'data' by a new array of newCapacity elements that holds the same
    // wagons at the same indices. The old array is deleted.
    void resize(int newCapacity);

public:
    static const int DEFAULT_CAPACITY = 4;

    WagonStack(); // empty stack with capacity DEFAULT_CAPACITY
    ~WagonStack();

    // Rule of Three: a WagonStack owns its array, so copies must be deep.
    WagonStack(const WagonStack &other);
    WagonStack &operator=(const WagonStack &other);

    bool isEmpty() const;
    int size() const;
    int getCapacity() const { return capacity; }

    // Puts a wagon on top. If the array is full, first resize(2 * capacity).
    void push(int wagon);

    // Removes the top wagon and writes it into 'out'. Returns false if the stack is empty.
    bool pop(int &out);

    // Writes the top wagon into 'out' without removing it. Returns false if empty.
    bool peek(int &out) const;

    // The i-th wagon from the BOTTOM (0 = bottom). Precondition: 0 <= i < size().
    int get(int i) const;

    // Position of a wagon counted from the BOTTOM (0 = bottom), or -1 if it is not here.
    int indexOf(int wagon) const;

    // Removes all wagons. The capacity does not change.
    void clear();
};

#endif
