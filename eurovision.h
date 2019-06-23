#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;
using std::string;
using std::ostream;
using std::endl;
using std::vector;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

/**  enum for number of points in each rank */
const int NUMBER_OF_RANKINGS = 10;
typedef enum {
    TENTH_PLACE = 1,
    NINTH_PLACE,
    EIGHT_PLACE,
    SEVENTH_PLACE,
    SIXTH_PLACE,
    FIFTH_PLACE,
    FOURTH_PLACE,
    THIRD_PLACE,
    SECOND_PLACE = 10,
    FIRST_PLACE = 12
} Ranking;

//---------------------------------------------------
template<typename Iterator, class Predicate>
Iterator get(const Iterator& first,const Iterator& last, int i, const Predicate& condition) {
    // Assumption: The given condition is a function object that receives two
    // Iterator objects of the given container and returns a bool value
    // which is true if the object the first Iterator points to is bigger
    // than the object the second Iterator is pointing to

    if (i < 1) return last; // i is too small

    // Create a list of the Container's iterators
    vector<Iterator> iter_sequence;
    for (Iterator iter = first; iter < last; ++iter) {
        iter_sequence.insert(iter_sequence.begin(), iter);
    }

    if (iter_sequence.size() < i) return last; // i is too big

    // sort the iterator array from biggest to smallest
    std::sort(iter_sequence.begin(), iter_sequence.end(), condition);
    //iter_sequence.reverse();

    return iter_sequence[i - 1];
}
//---------------------------------------------------

class Participant
{
// relevant private members can be defined here, if necessary.
    const string m_state;
    string m_song;
    string m_singer;
    int m_song_length;
    bool m_is_registered;

public :
    // need to define here possibly c'tr and d'tr and ONLY methods that
    // are mentioned and demonstrated in the test example that has been published.
    // NO OTHER METHODS SHOULD APPEAR HERE.

    Participant(const string& state, const string& song, int song_length, const string& singer);
    Participant(Participant const&) = delete;

    // get functions:
    const string& state() const;
    const string& song() const;
    const string& singer() const;
    int timeLength() const;
    bool isRegistered() const;

    // set functions:
    void update(const string& name, int length, const string& singer);
    void updateRegistered(bool registered); // public, but the assumption is only specific MainControl functions use


    // NO friend is allowed here. :(

};

ostream& operator<<(ostream& os, const Participant& participant);
//---------------------------------------------------
class Voter
{
    // relevant private members can be defined here, if necessary.
    const string m_state;     // voter's state
    const VoterType m_type;
    int m_times_of_votes;

public :
    explicit Voter(const string& state, VoterType type = Regular);

    // get :
    int timesOfVotes() const;
    const string& state() const;
    VoterType voterType() const;

    Voter& operator++();

    // need to define here possibly c'tr and d'tr and ONLY methods that
    // are mentioned and demonstrated in the test example that has been published.
    // NO OTHER METHODS SHOULD APPEAR HERE.

    // NO friend is allowed here. :(

};

ostream& operator<<(ostream& os, const Voter& voter);
// -----------------------------------------------------------

struct Vote
{
    Voter& m_voter;
    string* m_states;

// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.
    Vote(Voter& voter, const string& state1,
         const string& state2 = "",
         const string& state3 = "",
         const string& state4 = "",
         const string& state5 = "",
         const string& state6 = "",
         const string& state7 = "",
         const string& state8 = "",
         const string& state9 = "",
         const string& state10 = "");
    ~Vote();

};

// -----------------------------------------------------------

class MainControl
{
// relevant private members can be defined here, if necessary.
    // struct for participants list in MainControl element
    struct ParticipantNode {
        Participant& participant;
        ParticipantNode *next;
        int m_regular_votes;
        int m_judge_votes;

        explicit ParticipantNode(Participant& participant, ParticipantNode* next_ptr) :
                participant(participant), next(next_ptr), m_regular_votes(0), m_judge_votes(0) {
        }

    };
    // internal functions for the ParticipantNode struct
    ParticipantNode& findPrevNode(const string& state) const;
    void addPointsIfLegal(const Vote& vote, const string& voted_state, int num_of_points) const;

    ParticipantNode *m_participants_first;
    ParticipantNode* m_participants_last;
    int m_num_of_participants;
    int m_max_song_length;
    int m_max_participants;
    int m_max_regular_votes;
    Phase m_phase;

    // internal function for the printing function
    static string getPhaseText(Phase phase);
    // internal function for getting Judge points
    static Ranking getRanking(int place);

public :

    class Iterator {
        ParticipantNode* current;
        friend MainControl;

        public:
        Iterator();
        bool operator<(const Iterator& other) const;
        Iterator operator++();
        bool operator==(const Iterator& other) const;
        Participant& operator*() const;
    };

    Iterator begin() const;
    Iterator end() const;
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

    class VoteCompare {
        VoterType type;

    public:
        explicit VoteCompare(VoterType v_type) : type(v_type) {
        }

        bool operator()(MainControl::Iterator iter1, MainControl::Iterator iter2) {
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
    };

    explicit MainControl(int max_song_length = 180, int max_participants = 26, int max_regular_votes = 5);
    ~MainControl();
    void setPhase(Phase phase);
    bool participate(const string& state) const;
    bool legalParticipant(const Participant& participant) const;

    MainControl& operator+=(Participant& participant);
    MainControl& operator-=(Participant& participant);
    MainControl& operator+=(const Vote& vote);

    string operator()(int place, VoterType type) const;

// Also it's allowed here to define friend.
    friend ostream& operator<<(ostream& os, const MainControl& eurovision);
};

ostream& operator<<(ostream& os, const MainControl& eurovision);

// -----------------------------------------------------------

#endif
