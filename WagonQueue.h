#ifndef WAGON_QUEUE_H
#define WAGON_QUEUE_H

/** A FIFO queue of wagon numbers in a dynamically allocated CIRCULAR array:
 *  the arrival track and the loop track of the yard.
 *
 *  The front wagon is at data[front]; the i-th wagon from the front is at
 *  data[(front + i) % capacity]; a new wagon goes to data[(front + count) % capacity].
 *  Nothing is ever shifted.
 *
 *  The queue itself has no size limit: when the array is full it doubles.
 *  The capacity of the loop track is enforced by the Yard, not here.
 */
class WagonQueue
{
private:
    int *data;    // dynamic array of 'capacity' wagon numbers
    int capacity; // length of the array
    int front;    // index of the front wagon
    int count;    // number of wagons in the queue

    // Replaces 'data' by a new array of newCapacity elements. The wagons are copied
    // in queue order to indices 0 .. count-1 and front becomes 0. The old array is deleted.
    void resize(int newCapacity);

public:
    static const int DEFAULT_CAPACITY = 4;

    WagonQueue(); // empty queue with capacity DEFAULT_CAPACITY, front = 0
    ~WagonQueue();

    // Rule of Three: a WagonQueue owns its array, so copies must be deep.
    // A copy has the same capacity and the same wagons in the same order.
    WagonQueue(const WagonQueue &other);
    WagonQueue &operator=(const WagonQueue &other);

    bool isEmpty() const;
    int size() const;
    int getCapacity() const { return capacity; }
    int getFront() const { return front; }

    // Adds a wagon at the rear. If the array is full, first resize(2 * capacity).
    void enqueue(int wagon);

    // Removes the front wagon and writes it into 'out'. Returns false if the queue is empty.
    bool dequeue(int &out);

    // Writes the front wagon into 'out' without removing it. Returns false if empty.
    bool peek(int &out) const;

    // The i-th wagon from the FRONT (0 = front). Precondition: 0 <= i < size().
    int get(int i) const;

    // Position of a wagon counted from the FRONT (0 = front), or -1 if it is not here.
    int indexOf(int wagon) const;

    // Removes all wagons: count = 0 and front = 0. The capacity does not change.
    void clear();
};

#endif
