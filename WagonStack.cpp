#include "WagonStack.h"

const int WagonStack::DEFAULT_CAPACITY;

WagonStack::WagonStack()
    : data(nullptr), capacity(0), top(-1)
{
    // TODO: Allocate an array of DEFAULT_CAPACITY wagons. The stack is empty.
}

WagonStack::~WagonStack()
{
    // TODO: Free the array.
}

WagonStack::WagonStack(const WagonStack &other)
    : data(nullptr), capacity(0), top(-1)
{
    // TODO: Deep copy: an array of its own with other.capacity elements and the same wagons.
    (void)other;
}

WagonStack &WagonStack::operator=(const WagonStack &other)
{
    // TODO: Deep copy. The old array must not leak, and s = s must change nothing.
    (void)other;
    return *this;
}

bool WagonStack::isEmpty() const
{
    // TODO
    return true;
}

int WagonStack::size() const
{
    // TODO
    return 0;
}

void WagonStack::resize(int newCapacity)
{
    // TODO: A new array of newCapacity elements with the same wagons at the same indices.
    //  Delete the old array.
    (void)newCapacity;
}

void WagonStack::push(int wagon)
{
    // TODO: If the array is full, resize(2 * capacity) first. Then put the wagon on top.
    (void)wagon;
}

bool WagonStack::pop(int &out)
{
    // TODO: Return false if empty. Otherwise write the top wagon into out and remove it.
    (void)out;
    return false;
}

bool WagonStack::peek(int &out) const
{
    // TODO: Return false if empty. Otherwise write the top wagon into out.
    (void)out;
    return false;
}

int WagonStack::get(int i) const
{
    // TODO: The i-th wagon from the BOTTOM (0 = bottom).
    (void)i;
    return 0;
}

int WagonStack::indexOf(int wagon) const
{
    // TODO: The position of the wagon from the BOTTOM, or -1 if it is not in the stack.
    (void)wagon;
    return -1;
}

void WagonStack::clear()
{
    // TODO: Remove all wagons. The capacity does not change.
}
