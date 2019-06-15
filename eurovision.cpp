#include "eurovision.h"

//---------------------------------------------------

Participant::Participant(const string& state, const string& song, int song_length, const string& singer) :
    m_state(state), m_song(song),  m_singer(singer), m_song_length(song_length), m_is_registered(false) {
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
    os << "[" << participant.state() << "/" << participant.song() << "/";
    os << participant.timeLength() << "/" << participant.singer() << "]";
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
    os << "<" << voter.state() << "/";

    VoterType type = voter.voterType();
    if (type == Regular) {
        os << "Regular";
    } else if (type == Judge) {
        os << "Judge";
    }

    return os << ">";
}
// -----------------------------------------------------------

Vote::Vote(Voter& voter, const string& state1,
           const string& state2, const string& state3, const string& state4,
           const string& state5, const string& state6, const string& state7,
           const string& state8, const string& state9, const string& state10) :
        m_voter(voter) {
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
                         m_phase(Registration) {
    // insert dummy node in start of participants list
    Participant* dummy = new Participant("","",0,"");
    ParticipantNode* dummy_node = new ParticipantNode(*dummy);
    m_participants = dummy_node;
}

MainControl::~MainControl() {
    // iterate on the participants list & delete all nodes
    ParticipantNode* iterator = m_participants->next;
    while (iterator != NULL) {
        ParticipantNode* to_delete = iterator;
        iterator = iterator->next;
        delete to_delete;
    }
    delete &(m_participants->participant); // delete the dummy participant
    delete m_participants; // delete the dummy node
}

void MainControl::setPhase(Phase phase) {
    if ((m_phase == Registration && phase == Contest) || (m_phase == Contest && phase == Voting)) {
        m_phase = phase;
    }
}
bool MainControl::participate(const string& state) const {
    // iterate on the participants list in the MainControl element
    ParticipantNode& prev_node = findPrevNode(state);
    ParticipantNode* candidate_node = prev_node.next;

    // if the state is in the list return true
    if (candidate_node != NULL && (candidate_node->participant).state() == state) {
        return true;
    }
    // else return false
    return false;
}
bool MainControl::legalParticipant(const Participant& participant) const {
    if (participant.state() == "" || participant.singer() == "" || participant.song() == "") {
        return false;
    }

    int time_length = participant.timeLength();
    if (time_length < 1 || time_length > m_max_song_length) {
        return false;
    }
    //else
    return true;
}

MainControl& MainControl::operator+=(Participant& participant) {
    // if not Registration phase, or reached max participants,
    //  or state already registered, or participant not legal - can't register
    if (m_phase != Registration) return *this;
    if (m_max_participants <= m_num_of_participants) return *this;
    if (participate(participant.state())) return *this;
    if (!legalParticipant(participant)) return *this;

    // else, register the participant
    ParticipantNode* new_node = new ParticipantNode(participant);

    // add the participant in alphabetic order and return
    ParticipantNode& prev_node = findPrevNode(participant.state());
    if (prev_node.next != NULL) { // not end of list
        new_node->next = prev_node.next;
    }
    // else, reached end of list
    prev_node.next = new_node;

    participant.updateRegistered(true); // change is_registered to true
    m_num_of_participants++; // increment num of participants in MainControl
    return *this;
}
MainControl& MainControl::operator-=(Participant& participant) {
    // if not Registration phase or if the participant not registered, just return
    if (m_phase != Registration || !participant.isRegistered()) return *this;

    // else, remove the participant
    ParticipantNode& prev_node = findPrevNode(participant.state());
    ParticipantNode* to_delete = prev_node.next;
    prev_node.next = prev_node.next->next;
    delete to_delete;

    participant.updateRegistered(false); // update is_registered in participant to false
    m_num_of_participants--; // reduce count of participants in MainControl
    return *this;
}
MainControl& MainControl::operator+=(const Vote& vote) {
    if (m_phase != Voting) return *this; // if the MainControl element's phase isn't "Voting" - return
    if (!participate(vote.m_voter.state())) return *this; // if the voter's state doesn't participates  - return

    // else, add the points, according to voterType
    if (vote.m_voter.voterType() == Regular) { // regular voter
        if (vote.m_voter.timesOfVotes() >= m_max_regular_votes) return *this; // reached voting limit - return
        if (!checkOnlyOneState(vote)) return *this; // the Vote struct contain more than one state to vote for
        addPointsIfLegal(vote, vote.m_states[0], 1); // add point to voted state
    } else if (vote.m_voter.voterType() == Judge) {
        if (vote.m_voter.timesOfVotes() > 0) return *this; // reached voting limit - return
        ++(vote.m_voter); // increment the number of times the judge voter
        for (int i=0; i < 10; i++) {
            addPointsIfLegal(vote, vote.m_states[i], getRanking(i));  // add points accroding to ranking
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const MainControl& eurovision) {
    MainControl::ParticipantNode* iterator = eurovision.m_participants->next; // iterator for the participants list

    os << "{" << endl << MainControl::getPhaseText(eurovision.m_phase) << endl;

    if (eurovision.m_phase == Registration) {
        while (iterator != NULL) {
            os << iterator->participant << endl;
            iterator = iterator->next;
        }
    } else if (eurovision.m_phase == Voting) {
        while (iterator != NULL) {
            os << iterator->participant.state() << " : ";
            os << "Regular(" << iterator->m_regular_votes << ") ";
            os << "Judge(" << iterator->m_judge_votes << ")" << endl;
            iterator = iterator->next;
        }
    }

    os << "}" << endl;
    return os;
}

// --------------INTERNAL FUNCTIONS---------------------------

MainControl::ParticipantNode& MainControl::findPrevNode(const string& state) const {
    // iterate on the participants list,
    // return the last participant that smaller alphabeticly than the given state
    ParticipantNode* iterator = m_participants;
    while (iterator->next != NULL && iterator->next->participant.state() < state){
        iterator = iterator->next;
    }
    return *iterator;
}

void MainControl::addPointsIfLegal(const Vote& vote, const string& voted_state, int num_of_points) const {
    // if the voted state doesn't participates or voted state == voting state, return
    if (!participate(voted_state) || vote.m_voter.state() == voted_state) return;

    ParticipantNode& prev_node = findPrevNode(voted_state);

    // add points to the voted state
    if (vote.m_voter.voterType() == Regular) { // regular voter
        prev_node.next->m_regular_votes += num_of_points;
    } else if (vote.m_voter.voterType() == Judge) { // judge voter
        prev_node.next->m_judge_votes += num_of_points;
    }

    ++(vote.m_voter); // increments the number of times the voter has voted
}

string MainControl::getPhaseText (Phase phase) {
    if (phase == Registration) return "Registration";
    if (phase == Voting) return "Voting";
    //else
    return "Contest";
}

Ranking MainControl::getRanking(int place) {
    static const Ranking ranking[NUMBER_OF_RANKINGS] = { // points table for judges points
            FIRST_PLACE, SECOND_PLACE, THIRD_PLACE, FOURTH_PLACE,
            FIFTH_PLACE, SIXTH_PLACE, SEVENTH_PLACE, EIGHT_PLACE,
            NINTH_PLACE, TENTH_PLACE
    };

    return ranking[place];
}

bool MainControl::checkOnlyOneState(const Vote& vote) {
    for (int i=1; i<10; i++) {
        if (vote.m_states[i] != "") return false; // contains more than one state to vote for
    }
    // else
    return true;
}
// -----------------------------------------------------------

