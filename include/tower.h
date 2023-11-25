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

class Tower
{
    Vector2 *position;
    Rectangle *rect;
    Stack<Disk*> *tower;
public:
    Tower(int x, int y, int cap);
    ~Tower();
    void draw();
    void push(Disk *disk);
    bool isEmpty();
    int getLength();
    Rectangle getRectangle();
    Disk* pop();
    Disk* top();
    Disk* popTopDiskOnHover(Vector2 mouseV);
};

class MainScene
{
    int n, count, moves;
    Tower *src, *aux, *dest, *prev, *hovered;
    Disk *selected;
    Stack<Tower*> *towers;
public:
    MainScene(int n);
    ~MainScene();
    int Update();
    void Draw();
    Color getColor(int index);
};

#endif