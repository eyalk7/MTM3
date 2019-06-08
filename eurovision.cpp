#include "eurovision.h"

using std::endl;

//---------------------------------------------------

Participant::Participant(const string& state, const string& song, int song_length, const string& singer) :
    m_state(state), m_song(song), m_song_length(song_length), m_singer(singer) {
}

// get functions:
string Participant::state() const {
    return m_state;
}
string Participant::song() const {
    return m_song;
}
string Participant::singer() const {
    return m_singer;
}
int Participant::timeLength() const {
    return m_song_length;
}
bool Participant::isRegistered() const {
    return m_is_registered;
}

// set functions:
void Participant::update(const string& name, int length, const string& singer) {
    // if participant is registered can't do update
    if (m_is_registered) return;

    // check values and if they are valid, update the participant
    if (name != "") {
        m_song = name;
    }
    if (length > 0) {
        m_song_length = length;
    }
    if (singer != "") {
        m_singer = singer;
    }
}
void Participant::updateRegistered(bool registered) {
    m_is_registered = registered;
}

ostream& operator<<(ostream& os, const Participant& participant) {
    // [Israel/Song_Israel/175/Singer_Israel]
    os << "[" << participant.state() << "/" << participant.song() << "/" << participant.timeLength() << "/" << participant.singer() << "]";
    return os;
}
//---------------------------------------------------
Voter::Voter(const string& state, VoterType type) : m_state(state), m_type(type), m_times_of_votes(0) {

}

// get functions:
int Voter::timesOfVotes() const {
    return m_times_of_votes;
}
string Voter::state() const {
    return m_state;
}
VoterType Voter::voterType() const {
    return m_type;
}

Voter& Voter::operator++() {
    m_times_of_votes++;
    return *this;
}

ostream& operator<<(ostream& os, const Voter& voter) {
    return os << "<" << voter.state() << "/" << voter.voterType() << ">" << endl;
}
// -----------------------------------------------------------

Vote::Vote(const Voter& voter, const string& state1,
           const string& state2, const string& state3, const string& state4,
           const string& state5, const string& state6, const string& state7,
           const string& state8, const string& state9, const string& state10) :
        m_voter(voter.state(), voter.voterType()) {
    // voter.state != states ??
    m_states = new string[10] {
            state1, state2, state3, state4, state5, state6, state7, state8, state9, state10
    };
}

Vote::~Vote() {
    delete[] m_states;
}

// -----------------------------------------------------------

MainControl::MainControl(int max_song_length,
                         int max_participants,
                         int max_regular_votes) {

}

void MainControl::setPhase(Phase phase) { // not static!

}
bool MainControl::participate(const string& state) const {

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
