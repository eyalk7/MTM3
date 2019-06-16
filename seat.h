#include <iostream>
#include <string>
using std::string;
using std::exception;


// ---------------------------------------------
class NoPrice
{
    string error;

public:
    string what() const; // return error message
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
    GreenRoomSeat(int line, int chair); //  : Seat(line, chair, 0)

    int price() const;  // create NoPrice, set error message="Not for sale!" , throw NoPrice
    string  location() const; // print Green Room-> seat.location()
};

// ---------------------------------------------
class MainHallSeat : public Seat
{
protected:
    MainHallSeat(int line, int chair, int price); // : Seat(line, chair, price)
    virtual ~MainHallSeat();

public:
    virtual int price() const; // seat.price() + 100
};

// ---------------------------------------------
class SpecialSeat : public MainHallSeat
{

protected:
    SpecialSeat(int line , int chair, int price) // : MainHallSeat(line, chair, price)
    virtual ~SpecialSeat();

public:
    virtual int price() const; // mainHall.price() + 300

};

// ---------------------------------------------
class GoldenCircleSeat : public SpecialSeat
{
public:
    GoldenCircleSeat(int line, int chair, int price) // : SpecialSeat(line, chair, price)
    string location() const; // Golden Circle -> seat.location()
    int price() const; // specialSeat.price() + 1000
};

// ---------------------------------------------
class DisablePodiumSeat : public SpecialSeat
{

public:
    DisablePodiumSeat(int line, int chair, int price = 0) // : SpecialSeat(line, chair, price)
    string location() const; // Disabled Podium -> seat.location()
    int price() const; // price ===== 200
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat
{
    char area;

protected:
    RegularSeat(char area, int line, int chair, int price); // : MainHallSeat(line, chair, price)
    virtual ~RegularSeat();

public:
    virtual string location() const; // print area: seat.location()
};

// ---------------------------------------------
class FrontRegularSeat : public RegularSeat
{

public:
    FrontRegularSeat(char area, int line, int chair, int price) // : RegularSeat(area, line, chair, price)

    int price() const; // mainHall.price() + 500
    string location() const; // print Front-> regularSeat.location()
};

// ---------------------------------------------
class MiddleRegularSeat : public RegularSeat
{

public:
    MiddleRegularSeat(char area, int line, int chair, int price) // : RegularSeat(area, line, chair, price)

    int price() const; // mainHall.price() + 250
    string location() const; // print Middle-> regularSeat.location()
};

// ---------------------------------------------
class RearRegularSeat : public RegularSeat
{

public:
    RearRegularSeat(char area, int line, int chair, int price) // : RegularSeat(area, line, chair, price)

    string location() const; // print Rear-> regularSeat.location()
    // no price() needed, mainhall.price is called
};

// ---------------------------------------------
