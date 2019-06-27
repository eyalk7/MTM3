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

    /// constructor for NoPrice
    /// \param message - string to print with what()
    explicit NoPrice(const string& message);

    /// \return pointer to the saved message
    virtual const char* what() const noexcept override;
};

// ---------------------------------------------
class Seat
{
    int m_line;
    int m_chair;
    int m_price;

public:

    /// constructor for Seat (called only by derived-class constructors)
    Seat(int line, int chair, int base_price);

    /// destructor for Seat
    virtual ~Seat() = default;

    /// \return basic price ( = 0 because Seat is an abstract class)
    virtual int price() const = 0;

    /// \return string with line num and chair num
    virtual string location() const;
};

// ---------------------------------------------
class GreenRoomSeat : public Seat
{
public:

    /// constructor for GreenRoomSeat (doesn't need price param because GreenRoomSeat don't have prices)
    GreenRoomSeat(int line, int chair);

    /// throws a NoPrice exception
    int price() const override;

    /// \return a string with seat type, chair num and line num
    string location() const override;
};

// ---------------------------------------------
class MainHallSeat : public Seat
{
public:

    /// constructor for MainHallSeat (called only by derived-class constructors)
    MainHallSeat(int line, int chair, int price);

    /// \return basic price + 100
    int price() const override;

    /// not implemented ( =0 ) because MainHallSeat is an abstract class
    string location() const = 0;
};

// ---------------------------------------------
class SpecialSeat : public MainHallSeat
{
public:

    /// constructor for SpecialSeat
    SpecialSeat(int line , int chair, int price);

    /// \return MainHallSeat price + 300
    int price() const override;

    /// not implemented ( =0 ) because SpecialSeat is an abstract class
    string location() const = 0;
};

// ---------------------------------------------
class GoldenCircleSeat : public SpecialSeat
{
public:

    /// constructor for GoldenCircleSeat
    GoldenCircleSeat(int line, int chair, int price);

    /// \return SpecialSeat price + 1000
    int price() const override;

    /// \return a string with seat type, chair num and line num
    string location() const override;
};

// ---------------------------------------------
class DisablePodiumSeat : public SpecialSeat
{
public:

    /// constructor for DisablePodiumSeat
    DisablePodiumSeat(int line, int chair, int price = 0); // can get "basic price" although it's meaningless

    /// \return a string with seat type, chair num and line num
    string location() const override;

    /// \return 200
    int price() const override;
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat
{
    char m_area;
public:

    /// constructor for RegularSeat (called only by derived-class constructors)
    RegularSeat(char area, int line, int chair, int price);

    /// \return a string with area, chair num and line num
    string location() const override;

    /// not implemented ( =0 ) because RegularSeat is an abstract class
    int price() const = 0;
};

// ---------------------------------------------
class FrontRegularSeat : public RegularSeat
{
public:

    /// constructor for FrontRegularSeat
    FrontRegularSeat(char area, int line, int chair, int price);

    /// \return MainHallSeat price + 500
    int price() const override;

    /// \return string with location in hall, area, chair num and seat num
    string location() const override;
};

// ---------------------------------------------
class MiddleRegularSeat : public RegularSeat
{
public:

    /// constructor for MiddleRegularSear
    MiddleRegularSeat(char area, int line, int chair, int price);

    /// \return MainHallSeat price + 250
    int price() const override;

    /// \return string with location in hall, area, chair num and seat num
    string location() const override;
};

// ---------------------------------------------
class RearRegularSeat : public RegularSeat
{
public:

    /// constructor for RearRegularSeat
    RearRegularSeat(char area, int line, int chair, int price);

    /// \return string with location in hall, area, chair num and seat num
    string location() const override;

    /// \return MainHallSeat price
    int price() const override;
};

// ---------------------------------------------

#endif
