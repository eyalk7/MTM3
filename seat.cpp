#include "seat.h"

// ---------------------------------------------

const char* NoPrice::what() {
    // return char*("Not for sale !");
}

// ---------------------------------------------
Seat::Seat(int line, int chair, int base_price) {

}
Seat::~Seat() {

}

int Seat::price() {

}

string Seat::location() {

}

// ---------------------------------------------



GreenRoomSeat::GreenRoomSeat(int line, int chair) : Seat(line, chair, 0) {

}

int GreenRoomSeat::price() override {
    // throw NoPrice()
}
string GreenRoomSeat::location() override {
    // print Green Room-> seat.location()
}


// ---------------------------------------------

MainHallSeat::MainHallSeat(int line, int chair, int price) : Seat(line, chair, price) {

}
MainHallSeat::~MainHallSeat() {

}

int MainHallSeat::price() override {
    // seat.price() + 100
}

// ---------------------------------------------
SpecialSeat::SpecialSeat(int line , int chair, int price) : MainHallSeat(line, chair, price) {

}
SpecialSeat::~SpecialSeat() {

}

int SpecialSeat::price() override {
    // mainHall.price() + 300
}

// ---------------------------------------------
GoldenCircleSeat::GoldenCircleSeat(int line, int chair, int price) : SpecialSeat(line, chair, price) {

}
string GoldenCircleSeat::location() override {
    // Golden Circle -> seat.location()
}
int GoldenCircleSeat::price() override {
    // specialSeat.price() + 1000
}


// ---------------------------------------------
DisablePodiumSeat::DisablePodiumSeat(int line, int chair, int price = 0) : SpecialSeat(line, chair, price) {

}
string DisablePodiumSeat::location() override {
    // Disabled Podium -> seat.location()
}
int DisablePodiumSeat::price() override {
    // price ===== 200
}

// ---------------------------------------------
RegularSeat::RegularSeat(char area, int line, int chair, int price) : MainHallSeat(line, chair, price) {

}
RegularSeat::~RegularSeat() {

}

string RegularSeat::location() override {
    // print area: seat.location()
}

// ---------------------------------------------

FrontRegularSeat::FrontRegularSeat(char area, int line, int chair, int price) : RegularSeat(area, line, chair, price) {}


int FrontRegularSeat::price() override {
    // mainHall.price() + 500
}
string FrontRegularSeat::location() override {
    // print Front-> regularSeat.location()
}


// ---------------------------------------------
MiddleRegularSeat::MiddleRegularSeat(char area, int line, int chair, int price) : RegularSeat(area, line, chair, price) {

}

int MiddleRegularSeat::price() override {
    // mainHall.price() + 250
}
string MiddleRegularSeat::location() override {
    // print Middle-> regularSeat.location()
}

// ---------------------------------------------
RearRegularSeat::RearRegularSeat(char area, int line, int chair, int price) : RegularSeat(area, line, chair, price) {

}

string RearRegularSeat::location() override {
    // print Rear-> regularSeat.location()
}
// ---------------------------------------------