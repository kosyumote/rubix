#include <vector>
#include "sticker.hpp"

class Cube
{
    std::vector<Sticker> m_stickers;
public:
    // some constants for cleaner syntax
    static const int U = 0;
    static const int R = 1;
    static const int L = 2;
    static const int F = 3;
    static const int B = 4;
    static const int D = 5;

    static const int X = 0;
    static const int Y = 1;
    static const int Z = 2;
    
    static const long CW = 0;
    static const long CCW = 1;

    // ctor
    Cube();
    
    //methods    
    void turn(int, long); // was a bit clever here, and made it so that you don't accidentally call turn "backwards"
    void rotate(int, long); // same - if I wanted to really make sure, I would make an enum class - maybe I will later on
    void scramble();
    void reset();

    // getters
    std::vector<Sticker>* getStickers() const; // means that getStickers doesn't change the Cube
    bool isSolved() const;
    
};
