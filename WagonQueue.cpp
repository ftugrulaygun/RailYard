#include "WagonQueue.h"

const int WagonQueue::DEFAULT_CAPACITY;

WagonQueue::WagonQueue()
    : data(nullptr), capacity(0), front(0), count(0)
{
    // TODO: Allocate an array of DEFAULT_CAPACITY wagons. The queue is empty, front = 0.
}

WagonQueue::~WagonQueue()
{
    // TODO: Free the array.
}

WagonQueue::WagonQueue(const WagonQueue &other)
    : data(nullptr), capacity(0), front(0), count(0)
{
    // TODO: Deep copy: an array of its own with other.capacity elements,
    //  the same wagons in the same order.
    (void)other;
}

WagonQueue &WagonQueue::operator=(const WagonQueue &other)
{
    // TODO: Deep copy. The old array must not leak, and q = q must change nothing.
    (void)other;
    return *this;
}

bool WagonQueue::isEmpty() const
{
    // TODO
    return true;
}

int WagonQueue::size() const
{
    // TODO
    return 0;
}

void WagonQueue::resize(int newCapacity)
{
    // TODO: A new array of newCapacity elements. Copy the wagons IN QUEUE ORDER
    //  to indices 0 .. count-1 and set front = 0. Delete the old array.
    (void)newCapacity;
}

void WagonQueue::enqueue(int wagon)
{
    // TODO: If the array is full, resize(2 * capacity) first.
    //  Then write the wagon at (front + count) % capacity.
    (void)wagon;
}

bool WagonQueue::dequeue(int &out)
{
    // TODO: Return false if empty. Otherwise write the front wagon into out
    //  and move front one step (circularly).
    (void)out;
    return false;
}

bool WagonQueue::peek(int &out) const
{
    // TODO: Return false if empty. Otherwise write the front wagon into out.
    (void)out;
    return false;
}

int WagonQueue::get(int i) const
{
    // TODO: The i-th wagon from the FRONT (0 = front).
    (void)i;
    return 0;
}

int WagonQueue::indexOf(int wagon) const
{
    // TODO: The position of the wagon from the FRONT, or -1 if it is not in the queue.
    (void)wagon;
    return -1;
}

void WagonQueue::clear()
{
    // TODO: count = 0 and front = 0. The capacity does not change.
}
