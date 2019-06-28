#include "seat.h"

// ---------------------------------------------

NoPrice::NoPrice(const string &message) : m_message(message) {}

const char* NoPrice::what() const noexcept {
    return m_message.c_str();
}

// ---------------------------------------------
Seat::Seat(int line, int chair, int base_price) :
        m_line(line), m_chair(chair), m_price(base_price) {}

int Seat::price() const {
    return m_price;
}

string Seat::location() const {
    string line("line: ");
    string row_number = to_string(m_line);
    string chair(", chair: ");
    string seat_number = to_string(m_chair);

    return line + row_number + chair + seat_number;

}

// ---------------------------------------------

GreenRoomSeat::GreenRoomSeat(int line, int chair) :
                            Seat(line, chair, 0) {}

int GreenRoomSeat::price() const {
    // GreenRoomSeat doesn't have a price
    throw NoPrice("Not For Sale !");
}

string GreenRoomSeat::location() const {
    return "Green Room-> " + Seat::location();
}

// ---------------------------------------------

MainHallSeat::MainHallSeat(int line, int chair, int price) :
                            Seat(line, chair, price) {}

int MainHallSeat::price() const {
    return Seat::price() + 100;
}

// ---------------------------------------------
SpecialSeat::SpecialSeat(int line , int chair, int price) :
                        MainHallSeat(line, chair, price) {}

int SpecialSeat::price() const {
    return MainHallSeat::price() + 300;
}

// ---------------------------------------------
GoldenCircleSeat::GoldenCircleSeat(int line, int chair, int price) :
                                SpecialSeat(line, chair, price) {}

string GoldenCircleSeat::location() const {
    return "Golden Circle-> " + Seat::location();
}
int GoldenCircleSeat::price() const {
    return SpecialSeat::price() + 1000;
}

// ---------------------------------------------
DisablePodiumSeat::DisablePodiumSeat(int line, int chair, int price) :
                                SpecialSeat(line, chair, price) {}

string DisablePodiumSeat::location() const {
    return "Disable Podium-> " + Seat::location();
}
int DisablePodiumSeat::price() const {
    return 200;
}

// ---------------------------------------------
RegularSeat::RegularSeat(char area, int line, int chair, int price) :
                        MainHallSeat(line, chair, price), m_area(area) {}

string RegularSeat::location() const {
    string area = "area: ";
    area += m_area;
    return area + ", " + Seat::location();
}

// ---------------------------------------------

FrontRegularSeat::FrontRegularSeat(char area, int line, int chair, int price) :
                                RegularSeat(area, line, chair, price) {}


int FrontRegularSeat::price() const {
    return MainHallSeat::price() + 500;
}
string FrontRegularSeat::location() const {
    return "Front-> " + RegularSeat::location();
}


// ---------------------------------------------
MiddleRegularSeat::MiddleRegularSeat(char area, int line, int chair, int price) :
                                RegularSeat(area, line, chair, price) {}

int MiddleRegularSeat::price() const {
    return MainHallSeat::price() + 250;
}
string MiddleRegularSeat::location() const {
    return "Middle-> " + RegularSeat::location();
}

// ---------------------------------------------
RearRegularSeat::RearRegularSeat(char area, int line, int chair, int price) :
                                RegularSeat(area, line, chair, price) {}

string RearRegularSeat::location() const {
    return "Rear-> " + RegularSeat::location();
}

int RearRegularSeat::price() const {
    return MainHallSeat::price();
}
// ---------------------------------------------