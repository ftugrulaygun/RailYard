#ifndef MOVE_LIST_H
#define MOVE_LIST_H

/** A growing list of moves: what a planner produces. GIVEN completely (header only). */
struct Move
{
    int from;
    int to;
};

class MoveList
{
private:
    Move *data;
    int capacity;
    int count;

    MoveList(const MoveList &);            // not copyable
    MoveList &operator=(const MoveList &); // not copyable

public:
    MoveList() : data(new Move[64]), capacity(64), count(0) {}
    ~MoveList() { delete[] data; }

    int size() const { return count; }
    const Move &get(int i) const { return data[i]; }

    void add(int from, int to)
    {
        if (count == capacity)
        {
            Move *fresh = new Move[2 * capacity];
            for (int i = 0; i < count; ++i)
                fresh[i] = data[i];
            delete[] data;
            data = fresh;
            capacity *= 2;
        }
        data[count].from = from;
        data[count].to = to;
        ++count;
    }

    void clear() { count = 0; }
};

#endif
