#ifndef TOWER_H
#define TOWER_H

template <typename T>
class Stack
{
    T *stack;
    int length, cap;
public:
    Stack(int cap);
    ~Stack();
    void push(T object);
    T pop();
    T remove(int index);
    T top();
    T get(int index);
    bool isEmpty();
    bool isFull();
    int getLength();
    int getCapacity();
};

class MainScene
{
public:
    MainScene();
    ~MainScene();
    void Draw();
};

class Tower
{
    Vector2 *position;
public:
    Tower(int cap);
    ~Tower();
    void draw();
};

class Disk
{
    Vector2 *position;
    Rectangle *rect;
    Color col;
public:
    Disk(int x, int y, float width, float height, Color col);
    ~Disk();
    void draw();

    // setters
    void setPosition(int x, int y);

    // getters
    Rectangle getRectangle();
    Color getColor();
    Vector2 getPosition();
};

#endif