#include <iostream>
#include <string>
using std::string;
using std::exception;

// ---------------------------------------------
class NoPrice : public exception
{
public:
    const char* what() const;
};

// ---------------------------------------------
class Seat
{
    int row;
    int seat;
    int price;

protected:
    Seat(int line, int chair, int base_price);
    virtual ~Seat();

public:
    virtual int price() const;
    virtual string location() const;
};

// ---------------------------------------------
class GreenRoomSeat : public Seat
{

public:
    GreenRoomSeat(int line, int chair);

    int price() const;
    string  location() const;
};

// ---------------------------------------------
class MainHallSeat : public Seat
{
protected:
    MainHallSeat(int line, int chair, int price);
    ~MainHallSeat();

public:
    int price() const;
};

// ---------------------------------------------
class SpecialSeat : public MainHallSeat
{

protected:
    SpecialSeat(int line , int chair, int price)
    ~SpecialSeat();

public:
    int price() const;

};

// ---------------------------------------------
class GoldenCircleSeat : public SpecialSeat
{
public:
    GoldenCircleSeat(int line, int chair, int price)
    string location() const;
    int price() const;
};

// ---------------------------------------------
class DisablePodiumSeat : public SpecialSeat
{

public:
    DisablePodiumSeat(int line, int chair, int price = 0)
    string location() const;
    int price() const;
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat
{
    char area;

protected:
    RegularSeat(char area, int line, int chair, int price);
    ~RegularSeat();

public:
    string location() const;
};

// ---------------------------------------------
class FrontRegularSeat : public RegularSeat
{

public:
    FrontRegularSeat(char area, int line, int chair, int price)

    int price() const;
    string location() const;
};

// ---------------------------------------------
class MiddleRegularSeat : public RegularSeat
{

public:
    MiddleRegularSeat(char area, int line, int chair, int price)

    int price() const;
    string location() const;
};

// ---------------------------------------------
class RearRegularSeat : public RegularSeat
{

public:
    RearRegularSeat(char area, int line, int chair, int price)

    string location() const;
    // no price() needed, mainhall.price is called
};

// ---------------------------------------------
