#include "eurovision.h"

//---------------------------------------------------

Participant::Participant(string state, string song, int song_length, string singer) :
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
void Participant::update(string name, int length, string singer) {
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

MainControl::MainControl(int max_song_length,
                         int max_participants,
                         int max_regular_votes) :
                         m_participants = NULL,
                         m_num_of_participants(0),
                         m_max_song_length(max_song_length),
                         m_max_participants(max_participants),
                         m_max_regular_votes(max_regular_votes),
                         m_phase(Registration){
}

void MainControl::setPhase(Phase phase) {
    m_phase = phase;
}
bool MainControl::participate(string state) const {
    ParticipantNode* iterator = m_participants;
    while (iterator != NULL) {
        if (iterator->participant.state() == state) return true;
    }

    return false;
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
