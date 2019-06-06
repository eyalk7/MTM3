#include "eurovision.h"

//---------------------------------------------------

Participant::Participant(string state, string song, int song_length, string singer) {

}

// get functions:
string Participant::state() const {

}
string Participant::song() const {

}
string Participant::singer() const {

}
int Participant::timeLength() const {

}
bool Participant::isRegistered() const {

}

// set functions:
void Participant::update(string name, int length, string singer) {

}
void Participant::updateRegistered(bool registered) {

}

ostream& operator<<(ostream& os, const Participant& participant) {

}
//---------------------------------------------------

Voter::Voter(string state, VoterType type) : m_state(state), m_type(type) {
    // votes = 0

}

// get functions:
int Voter::timesOfVotes() const {

}
string Voter::state() const {

}
VoterType Voter::voterType() const {

}

Voter& Voter::operator++() {

}

ostream& operator<<(ostream& os, const Voter& voter) {

}
// -----------------------------------------------------------

Vote::Vote(Voter voter, string state1, string state2,
                        string state3, string state4,
                        string state5, string state6,
                        string state7, string state8,
                        string state9, string state10) : m_voter(voter.state(), voter.voterType()) {
    // voter.state != states ??
    m_states = new string[10] {
            state1, state2, state3, state4, state5, state6, state7, state8, state9, state10
    };
}

Vote::~Vote() {
    delete[] m_states;
}

// -----------------------------------------------------------

Phase MainControl::getPhase() { // static function

}


MainControl::MainControl(int max_song_length,
                         int max_participants,
                         int max_regular_votes) {

}

void MainControl::setPhase(Phase phase) { // not static!

}
bool MainControl::participate(string state) const {

}
bool MainControl::legalParticipant(const Participant& participant) const {

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
