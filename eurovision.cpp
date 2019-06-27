#include "eurovision.h"

//-------------------------PARTICIPANT IMPLEMENTATION-------------------------

Participant::Participant(const string& state, const string& song, int song_length, const string& singer) :
    m_state(state), m_song(song),  m_song_length(song_length), m_singer(singer), m_is_registered(false) {
}

// Get functions:

const string& Participant::state() const {
    return m_state;
}
const string& Participant::song() const {
    return m_song;
}
const string& Participant::singer() const {
    return m_singer;
}
int Participant::timeLength() const {
    return m_song_length;
}
bool Participant::isRegistered() const {
    return m_is_registered;
}

// Set functions:

void Participant::update(const string& name, int length, const string& singer) {
    if (m_is_registered) return; // if participant is registered, do nothing

    // for each parameter check if it's value is valid
    // and update the corresponding participant's field

    if (!name.empty()) {
        m_song = name;
    }
    if (length > 0) {
        m_song_length = length;
    }
    if (!singer.empty()) {
        m_singer = singer;
    }
}

void Participant::updateRegistered(bool registered) {
    m_is_registered = registered;
}

//Operators:

ostream& operator<<(ostream& os, const Participant& participant) {
    // Output format: [state/song/song length/singer]

    os << "[" << participant.state() << "/" << participant.song() << "/";
    os << participant.timeLength() << "/" << participant.singer() << "]";
    return os;
}
//-------------------------VOTER IMPLEMENTATION-------------------------
Voter::Voter(const string& state, VoterType type) : m_state(state), m_type(type), m_times_of_votes(0) {

}

// Get functions:
int Voter::timesOfVotes() const {
    return m_times_of_votes;
}
const string& Voter::state() const {
    return m_state;
}
VoterType Voter::voterType() const {
    return m_type;
}

// Operators:
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
//-------------------------VOTE IMPLEMENTATION-------------------------

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

//-------------------------MAINCONTROL IMPLEMENTATION-------------------------

MainControl::MainControl(int max_song_length,
                         int max_participants,
                         int max_regular_votes) :
                         m_num_of_participants(0),
                         m_max_song_length(max_song_length),
                         m_max_participants(max_participants),
                         m_max_regular_votes(max_regular_votes),
                         m_phase(Registration) {
    // insert dummy node in start and at the end of participants list
    Participant* first_dummy = new Participant("","",0,"");
    Participant* last_dummy = new Participant("","",0,"");
    ParticipantNode* last_node = new ParticipantNode(*last_dummy, nullptr);
    ParticipantNode* first_node = new ParticipantNode(*first_dummy, last_node);

    m_participants_first = first_node;
    m_participants_last = last_node;
}

MainControl::~MainControl() {
    // iterate on the participants list & delete all nodes
    ParticipantNode* iterator = m_participants_first->next;
    while (iterator != m_participants_last) {
        ParticipantNode* to_delete = iterator;
        iterator = iterator->next;
        delete to_delete;
    }

    delete &(m_participants_last->participant); // delete the last dummy participant
    delete &(m_participants_first->participant); // delete the first dummy participant
    delete m_participants_last;       // delete the last dummy node
    delete m_participants_first; // delete the first dummy node
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

    // if the state is in the list return true, else return false
    return (candidate_node != m_participants_last && candidate_node->participant.state() == state);
}
bool MainControl::legalParticipant(const Participant& participant) const {
    // check that participant's state, singer and song names are valid
    if (participant.state().empty() || participant.singer().empty() || participant.song().empty()) {
        return false;
    }

    // return true if the song's time length is valid, else false
    int time_length = participant.timeLength();
    return (1 <= time_length && time_length <= m_max_song_length);
}

MainControl& MainControl::operator+=(Participant& participant) {
    // if not Registration phase, or reached max participants,
    //  or state already registered, or participant not legal - can't register
    if (m_phase != Registration) return *this;
    if (m_max_participants <= m_num_of_participants) return *this;
    if (participate(participant.state())) return *this;
    if (!legalParticipant(participant)) return *this;

    // add the participant in alphabetic order and return
    ParticipantNode& prev_node = findPrevNode(participant.state());

    ParticipantNode* new_node = new ParticipantNode(participant, prev_node.next);

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
        addPointsIfLegal(vote, vote.m_states[0], 1); // add point to voted state
    } else if (vote.m_voter.voterType() == Judge) {
        if (vote.m_voter.timesOfVotes() > 0) return *this; // reached voting limit - return
        for (int i=0; i < 10; i++) {
            addPointsIfLegal(vote, vote.m_states[i], getRanking(i));  // add points according to ranking
        }
    }
    return *this;
}

MainControl::VoteCompare::VoteCompare(VoterType v_type) : type(v_type) {}

bool MainControl::VoteCompare::operator()(MainControl::Iterator iter1, MainControl::Iterator iter2) {
    ParticipantNode* node1 = iter1.current;
    int regular_votes_1 = node1->m_regular_votes;
    int judge_votes_1 = node1->m_judge_votes;

    ParticipantNode* node2 = iter2.current;
    int regular_votes_2 = node2->m_regular_votes;
    int judge_votes_2 = node2->m_judge_votes;

    int votes_1 = 0, votes_2 = 0;
    switch (type) {
        case Regular:
            votes_1 = regular_votes_1;
            votes_2 = regular_votes_2;
            break;
        case Judge:
            votes_1 = judge_votes_1;
            votes_2 = judge_votes_2;
            break;
        default: //case All:
            votes_1 = regular_votes_1 + judge_votes_1;
            votes_2 = regular_votes_2 + judge_votes_2;
            break;
    }


    if (votes_1 == votes_2) {
        // if no. of points is equal, the state with the bigger name
        // goes first (true = Participant 1 has bigger state)
        return node1->participant.state() > node2->participant.state();
    }

    // true = Participant 1 has more votes than Participant 2
    return votes_1 > votes_2;
}

string MainControl::operator()(int place, VoterType type) const {
    Iterator winner = get<Iterator,VoteCompare>(begin(), end(), place, VoteCompare(type));
    if (winner == end()) return ""; // place is smaller than 1 or bigger than num of participants
    return (*winner).state();
}

ostream& operator<<(ostream& os, const MainControl& eurovision) {
    MainControl::ParticipantNode* iterator = eurovision.m_participants_first->next; // iterator for the participants list
    MainControl:: ParticipantNode* end = eurovision.m_participants_last;

    os << "{" << endl << MainControl::getPhaseText(eurovision.m_phase) << endl;

    if (eurovision.m_phase == Registration) {
        while (iterator != end) {
            os << iterator->participant << endl;
            iterator = iterator->next;
        }
    } else if (eurovision.m_phase == Voting) {
        while (iterator != end) {
            os << iterator->participant.state() << " : ";
            os << "Regular(" << iterator->m_regular_votes << ") ";
            os << "Judge(" << iterator->m_judge_votes << ")" << endl;
            iterator = iterator->next;
        }
    }

    os << "}" << endl;
    return os;
}

//-------------------------MAINCONTROL ITERATOR FUNCTIONS-------------------------

MainControl::Iterator::Iterator() : current(nullptr) {}

bool MainControl::Iterator::operator<(const Iterator& other) const {
    if (current->next == nullptr) return false; // current == end()
    if (other.current->next == nullptr) return true;    // other.current == end()

    Participant& p1 = current->participant;
    Participant& p2 = other.current->participant;
    return p1.state() < p2.state();
}

MainControl::Iterator& MainControl::Iterator::operator++() {
    // check if reached the last node
    if (current->next != nullptr) { // current != end()
        current = current->next;
    }
    return *this;
}

bool MainControl::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

Participant& MainControl::Iterator::operator*() const {
    assert(current->next != nullptr); // can't dereference the end dummy

    return (this->current->participant);
}

MainControl::Iterator MainControl::begin() const {
    MainControl::Iterator iter;
    iter.current = m_participants_first->next;
    return iter;
}

MainControl::Iterator MainControl::end() const {
    MainControl::Iterator iter;
    iter.current = m_participants_last;
    return iter;
}

//-------------------------MAINCONTROL INTERNAL FUNCTIONS-------------------------

MainControl::ParticipantNode& MainControl::findPrevNode(const string& state) const {
    // iterate on the participants list,
    // return the last participant that smaller alphabetically than the given state
    ParticipantNode* iterator = m_participants_first;
    while (iterator->next != m_participants_last && iterator->next->participant.state() < state) {
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

Ranking MainControl::getRanking(int rank) {
    static const Ranking ranking[NUMBER_OF_RANKINGS] = { // points table for judges points
            FIRST_PLACE, SECOND_PLACE, THIRD_PLACE, FOURTH_PLACE,
            FIFTH_PLACE, SIXTH_PLACE, SEVENTH_PLACE, EIGHT_PLACE,
            NINTH_PLACE, TENTH_PLACE
    };

    return ranking[rank];
}
// -----------------------------------------------------------

