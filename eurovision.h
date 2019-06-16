#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;
using std::string;
using std::ostream;
using std::endl;

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
template<class Iterator>
        Iterator get(Iterator first, Iterator last, int i) {
            // if i < 1 return last + 1

            // make Iterator array
            // for loop on the container:
                // iterator_array[i] = container_iterator

            // loop the array to get array size
            // if array size < i -> return last + 1
            // sort the iterator array from biggest to smallest

            // return sorted_iterator_array[i - 1]
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
    string state() const;
    string song() const;
    string singer() const;
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
    string state() const;
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

        explicit ParticipantNode(Participant& source_participant) :
        participant(source_participant), next(NULL), m_regular_votes(0), m_judge_votes(0) {
        }



    };
    // internal functions for the ParticipantNode struct
    ParticipantNode& findPrevNode(const string& state) const;
    void addPointsIfLegal(const Vote& vote, const string& voted_state, int num_of_points) const;

    ParticipantNode *m_participants; //
    int m_num_of_participants;
    int m_max_song_length;
    int m_max_participants;
    int m_max_regular_votes;
    Phase m_phase;

    // internal function for the printing function
    static string getPhaseText(Phase phase);
    // internal function for getting Judge points
    static Ranking getRanking(int place);
    // internal function to check if a Vote element contains one state to vote for
    static bool checkOnlyOneState(const Vote& vote);

public :

    class Iterator {
        ParticipantNode* current;

        Iterator(ParticipantNode* first);
        bool operator<(const Iterator& other) const;
        Iterator operator++();
        bool operator==(const Iterator& other) const;
        const Participant& operator*() const;

    };



    Iterator begin() const;
    Iterator end() const;
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

    explicit MainControl(int max_song_length = 180, int max_participants = 26, int max_regular_votes = 5);
    ~MainControl();
    void setPhase(Phase phase);
    bool participate(const string& state) const;
    bool legalParticipant(const Participant& participant) const;

    MainControl& operator+=(Participant& participant);
    MainControl& operator-=(Participant& participant);
    MainControl& operator+=(const Vote& vote);

    string& operator()(int place, VoterType type) const;


// Also it's allowed here to define friend.
    friend ostream& operator<<(ostream& os, const MainControl& eurovision);

};

ostream& operator<<(ostream& os, const MainControl& eurovision);

// -----------------------------------------------------------

#endif
