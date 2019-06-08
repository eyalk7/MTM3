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
    ParticipantNode& prev_node = findPrevNode(state);

    // if the state is in the list return true
    if (prev_node->next != NULL && prev_node->next->participant.state() == state) return true;

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

    // add the participant in alphabetic order and return
    ParticipantNode& prev_node = findPrevNode(participant.state());
    if (prev_node->next != NULL) {
        new_node->next = prev_node->next;
        prev_node->next = new_node;
        participant.updateRegistered(true);
        return *this;
    }
    // if reached end of list, insert the new participant in the end, and return
    prev_node->next = new_node;
    return *this;
}
MainControl& MainControl::operator-=(const Participant& participant) {
    // if not Registration phase or if the participant not registered, just return
    if (m_phase != Registration || !participant.isRegistered()) return *this;

    // else, remove the participant
    // find the participant and remove it, and return
    ParticipantNode& prev_node = findPrevNode(participant.state());
    ParticipantNode to_delete = prev_node->next;
    prev_node->next = prev_node->next->next;
    delete to_delete;
    return *this;
}
MainControl& MainControl::operator+=(const Vote& vote) {
    if (m_phase != Voting) return *this; // if the MainControl element's phase isn't "Voting" - return
    if (!participate(voter_state)) return *this; // if the voter's state doesn't participates  - return

    int times_of_votes = vote.m_voter.timesOfVotes();
    if (vote.m_voter.voterType() == Regular) { // regular voter
        if (times_of_votes >= m_max_regular_votes) return *this; // reached voting limit - return
        addPointsIfLegal(vote, vote.m_states[0], 1); // add point to voted state (only if participates & diff from the voting state)
    }

    else { // voterType == Judge
        if (times_of_votes > 0) return *this; // reached voting limit - return
        static const Ranking ranking[NUMBER_OF_RANKINGS] = { // points table according to ranking
                FIRST_PLACE, SECOND_PLACE, THIRD_PLACE, FOURTH_PLACE,
                FIFTH_PLACE, SIXTH_PLACE, SEVENTH_PLACE, EIGHT_PLACE,
                NINTH_PLACE, TENTH_PLACE
        };
        for (int i=0; i < 10; i++) {
            addPointsIfLegal(vote, vote.m_states[i], ranking[i]); // add points accroding to ranking (only if participates & diff from the voting state)
        }
    }

    return *this;
}

ostream& operator<<(ostream& os, const MainControl& eurovision) {

}

// --------------INTERNAL FUNCTIONS---------------------------

ParticipantNode& MainControl::findPrevNode(const string& state) {
    // iterate on the participants list,
    // find the last participant that smaller alphabeticly than the given state
    // and return it
    ParticipantNode* iterator = m_participants;
    while (iterator->next != NULL && iterator->next->participant.state() < state){
        iterator = iterator->next;
    }

    return *iterator;
}

void MainControl::addPointsIfLegal(const Vote& vote, const string& voted_state, int num_of_points) {
    // checks that the voted state participates & that the voted state != voting state
    if (participate(voted_state) && vote.m_voter.state() != voted_state){
        ParticipantNode& prev_node = findPrevNode(vote.m_states[0]);
        prev_node->next->m_regular_votes += num_of_points; // add points to the voted state
        ++vote.m_voter; // increments the number of times the voter has voted
    }

}

// -----------------------------------------------------------

