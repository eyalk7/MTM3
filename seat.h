#ifndef SEAT_H_
#define SEAT_H_

#include <iostream>
#include <string>
using std::string;
using std::exception;
using std::to_string;

// ---------------------------------------------
class NoPrice : public exception
{
private:
    string m_message;
public:
    explicit NoPrice(const string& message);
    virtual const char* what() const noexcept override;
};

// ---------------------------------------------
class Seat
{
    int m_line;
    int m_chair;
    int m_price;

public:
    Seat(int line, int chair, int base_price);
    virtual ~Seat() = default;

    virtual int price() const = 0;
    virtual string location() const;
};

// ---------------------------------------------
class GreenRoomSeat : public Seat
{
public:
    GreenRoomSeat(int line, int chair);

    int price() const override;
    string  location() const override;
};

// ---------------------------------------------
class MainHallSeat : public Seat
{
public:
    MainHallSeat(int line, int chair, int price);

    int price() const override;
    string location() const = 0;
};

// ---------------------------------------------
class SpecialSeat : public MainHallSeat
{
public:
    SpecialSeat(int line , int chair, int price);

    int price() const override;
    string location() const = 0;
};

// ---------------------------------------------
class GoldenCircleSeat : public SpecialSeat
{
public:
    GoldenCircleSeat(int line, int chair, int price);

    string location() const override;
    int price() const override;
};

// ---------------------------------------------
class DisablePodiumSeat : public SpecialSeat
{
public:
    DisablePodiumSeat(int line, int chair, int price = 0);

    string location() const override;
    int price() const override;
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat
{
    char m_area;
public:
    RegularSeat(char area, int line, int chair, int price);

    string location() const override;
    int price() const = 0;
};

// ---------------------------------------------
class FrontRegularSeat : public RegularSeat
{
public:
    FrontRegularSeat(char area, int line, int chair, int price);

    int price() const override;
    string location() const override;
};

// ---------------------------------------------
class MiddleRegularSeat : public RegularSeat
{
public:
    MiddleRegularSeat(char area, int line, int chair, int price);

    int price() const override;
    string location() const override;
};

// ---------------------------------------------
class RearRegularSeat : public RegularSeat
{
public:
    RearRegularSeat(char area, int line, int chair, int price);

    string location() const override;
    int price() const override;
};

// ---------------------------------------------

#endif
