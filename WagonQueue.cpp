#include "WagonQueue.h"

const int WagonQueue::DEFAULT_CAPACITY;

WagonQueue::WagonQueue()
    : data(nullptr), capacity(0), front(0), count(0)
{
    // TODO: Allocate an array of DEFAULT_CAPACITY wagons. The queue is empty, front = 0.
    this->data = new int[DEFAULT_CAPACITY];
    this->capacity = DEFAULT_CAPACITY;
}

WagonQueue::~WagonQueue()
{
    delete[] this->data;
    // TODO: Free the array.
}

WagonQueue::WagonQueue(const WagonQueue &other)
    : data(nullptr), capacity(0), front(0), count(0)
{
    // TODO: Deep copy: an array of its own with other.capacity elements,
    //  the same wagons in the same order.

    int* newAr = new int[other.capacity];
    for(int i = 0; i <= other.count-1; i++)
    {
        newAr[i] = other.data[(other.front + i) % other.capacity];
    }
    this->capacity = other.capacity;
    this->count = other.count;
    this->front = 0;
    this->data = newAr;

}

WagonQueue &WagonQueue::operator=(const WagonQueue &other)
{
    // TODO: Deep copy. The old array must not leak, and q = q must change nothing.
    if(&other == this)
    {
        return *this;
    }

    int* newAr = new int[other.capacity];
    for(int i = 0; i <= other.count-1; i++)
    {
        newAr[i] = other.data[(other.front + i) % other.capacity];
    }
    this->capacity = other.capacity;
    this->front = 0;
    this->count = other.count;
    delete[] this->data;
    this->data = newAr;
    
    return *this;
}

bool WagonQueue::isEmpty() const
{
    // TODO
    if(this->count == 0)
    {
        return true;
    }
    return false;
}

int WagonQueue::size() const
{
    // TODO
    return this->count;
}

void WagonQueue::resize(int newCapacity)
{
    // TODO: A new array of newCapacity elements. Copy the wagons IN QUEUE ORDER
    //  to indices 0 .. count-1 and set front = 0. Delete the old array.
    int* newAr = new int[newCapacity];
    for(int i = 0; i <= this->count-1; i++)
    {   
        newAr[i] = this->data[(this->front + i) % this->capacity]; 
    }
    delete[] this->data;
    this->capacity = newCapacity;
    this->front = 0;
    this->data = newAr;
}

void WagonQueue::enqueue(int wagon)
{
    // TODO: If the array is full, resize(2 * capacity) first.
    //  Then write the wagon at (front + count) % capacity.
    if(this->count == this->capacity)
    {
        resize(2*this->capacity);
    }

    int rear = (this->front + this->count) % this->capacity;
    this->data[rear] = wagon;
    this->count++;
}

bool WagonQueue::dequeue(int &out)
{
    // TODO: Return false if empty. Otherwise write the front wagon into out
    //  and move front one step (circularly).
    if(isEmpty())
    {
        return false;
    }
    out = this->data[this->front];
    this->front = (this->front + 1) % this->capacity;
    this->count--;
    return true;
}

bool WagonQueue::peek(int &out) const
{
    // TODO: Return false if empty. Otherwise write the front wagon into out.
    if(isEmpty())
    {
        return false;
    }
    out = this->data[front];
    return true;
}

int WagonQueue::get(int i) const
{
    // TODO: The i-th wagon from the FRONT (0 = front).
    return this->data[(this->front + i) % this->capacity];
}

int WagonQueue::indexOf(int wagon) const
{
    // TODO: The position of the wagon from the FRONT, or -1 if it is not in the queue.
    for(int i = 0; i <= this->count-1; i++)
    {
        if(this->data[(this->front+i)%this->capacity] == wagon)
        {
            return i;
        }
    }
    return -1;
}

void WagonQueue::clear()
{
    // TODO: count = 0 and front = 0. The capacity does not change.
    this->count = 0;
    this->front = 0;
}
