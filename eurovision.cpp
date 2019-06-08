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
                         int max_regular_votes) :
                         m_num_of_participants(0),
                         m_max_song_length(max_song_length),
                         m_max_participants(max_participants),
                         m_max_regular_votes(max_regular_votes),
                         m_phase(Registration){
    Participant& dummy = new Participant("","",0,"");
    ParticipantNode& dummy_node = new ParticipantNode(dummy, NULL);
}

void MainControl::setPhase(Phase phase) {
    m_phase = phase;
}
bool MainControl::participate(string state) const {
    // iterate on the participants list in the MainControl element
    ParticipantNode* iterator = m_participants;
    while (iterator != NULL) {
        // if the state is in the list return true
        if (iterator->participant.state() == state) return true;

        iterator = iterator->next;
    }

    // else return false
    return false;
}
bool MainControl::legalParticipant(const Participant& participant) const {
    if (participant.state() == "" || participant.singer() == "" || participant.song() == "") return false;
    int time_length = participant.timeLength();
    if (time_length < 1 || time_length > m_max_song_length) return false;

    //else
    return true;
}

MainControl& MainControl::operator+=(const Participant& participant) {
    // if not registratino phase, or reached max participants,
    //  or state already registered, or participant not legal - can't register
    if (m_phase != Registration) return *this;
    if (m_max_participants <= m_num_of_participants) return *this;
    if (participate(participant.state())) return *this;
    if (!legalParticipant(participant)) return *this;

    // else, register the participant
    ParticipantNode& new_node = new ParticipantNode(participant, NULL);
    // iterate on the participants list in the MainControl element and add the participant in alphabetic order
    ParticipantNode* iterator = m_participants;
    while (iterator->next != NULL){
        // if the next participant is bigger alphabeticly, insert the new participant before it, and return
        // update the is_registered value on participant
        if (participant.state() < iterator->next->participant.state()) {
            new_node->next = iterator->next;
            iterator->next = new_node;
            participant.updateRegistered(true);
            return *this;
        }

        // else, go to the next participant in the list
        iterator = iterator->next;
    }

    // if reached end of list, insert the new participant in the end, and return
    iterator->next = new_node;
    return *this;
}
MainControl& MainControl::operator-=(const Participant& participant) {
    // if not Registration phase or if the participant not registered, just return
    if (m_phase != Registration || !participant.isRegistered()) return *this;

    // else, remove the participant
    // iterate on the participants list, find the participant and remove it, and return
    ParticipantNode* iterator = m_participants;
    string participant_state = participant.state();
    while (iterator->next->participant.state() != participant_state){
        iterator = iterator->next;
    }
    ParticipantNode to_delete = iterator->next;
    iterator->next = iterator->next->next;
    delete to_delete;
    return *this;
}
MainControl& MainControl::operator+=(const Vote& vote) {
    // if voter state
}

ostream& operator<<(ostream& os, const MainControl& eurovision) {

}

// -----------------------------------------------------------
