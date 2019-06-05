#include "eurovision.h"

//---------------------------------------------------

Participant::Participant(String state, String song, int song_length, String singer) {

}

// get functions:
String Participant::state() {

}
String Participant::song() {

}
String Participant::singer() {

}
int Participant::timeLength() {

}
bool Participant::isRegistered() {

}

// set functions:
void Participant::update(String name, int length, String singer) {

}
void Participant::updateRegistered(bool registered) {

}

ostream& operator<<(ostream& os, const Participant& participant) {

}
//---------------------------------------------------

Voter::Voter(String state, VoterType type = Regular) : state(state), type(ype) {
    // votes = 0

}

// get functions:
int Voter::timeOfVotes() {

}
String Voter::state() {

}
VoterType Voter::voterType() {

}

Voter& Voter::operator++() {

}

ostream& operator<<(ostream& os, const Voter& voter) {

}
// -----------------------------------------------------------

Vote::Vote(Voter voter, String state1,
           String state2 = "",
           String state3 = "",
           String state4 = "",
           String state5 = "",
           String state6 = "",
           String state7 = "",
           String state8 = "",
           String state9 = "",
           String state10 = "") {
    // voter.state != states ??
    this.voter = Voter(voter.state(), voter.voterType());
    this->states = new String[10] {
            state1, state2, state3, state4, state5, state6, state7, state8, state9, state10
    };
}

Vote::~Vote() {
    delete[] states;
}

// -----------------------------------------------------------

static Phase MainControl::getPhase() {

}


MainControl::MainControl(int max_song_length = 180,
                         int max_participants = 26,
                         int max_regular_votes = 5) {

}

void MainControl::setPhase(Phase phase) { // not static!

}
bool MainControl::participate(String state) {

}
bool MainControl::legalParticipant(Participant participant) {

}

MainControl& MainControl::operator+=(const Participant& participant) {

}
MainControl& MainControl::operator-=(const Participant& participant) {

}
MainControl& MainControl::operator+=(const Vote& vote) {

}

ostream& operator<<(ostream& os, const MainControl& eurovision) {

}

// -----------------------------------------------------------
