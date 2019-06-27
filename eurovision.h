#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <assert.h>
#include <algorithm> // used in get function for sorting
#include <vector>    // used in get function

using std::string;
using std::ostream; // for printing
using std::endl;    // for printing
using std::vector;  // used in get function

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

/**  enum for number of points the judge gives based on the ranking */
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
    const string m_state; // The state the participant is from
    string m_song;        // The name of the participant's song
    int m_song_length;    // The length of the song
    string m_singer;      // The name of the participant's singer

    bool m_is_registered; // Boolean stating whether the participant is registered or not

public:
    /// Constructor for participants.
    /// \param state - The state the participant is from
    /// \param song - The name of the participant's song
    /// \param song_length - The length of the song
    /// \param singer - The name of the participant's singer
    Participant(const string& state, const string& song, int song_length, const string& singer);

    Participant(const Participant&) = delete; // never send a participant by value

    // get functions:

    /// \return The name of the participant's state
    const string& state() const;

    /// \return The name of the participant's song
    const string& song() const;

    /// \return The name of the participant's singer
    const string& singer() const;

    /// \return The length of the participant's song
    int timeLength() const;

    /// \return True if the participant is registered, otherwise False.
    bool isRegistered() const;

    // set functions:

    /// If the participant is not registered, the function updates
    /// it's name, length and singer according to the given parameters.
    /// If the participant is registered, nothing happens.
    /// Moreover, if a parameter is not valid the corresponding field won't be updated.
    /// \param name - The new name to set
    /// \param length - The new song length to set
    /// \param singer - The new singer name to set
    void update(const string& name, int length, const string& singer);

    /// Updates the participant's status - registered/not registered.
    /// Assumption: Only specific MainControl functions will use this function
    /// \param registered - The new status to set for this participant's "is registered" state
    void updateRegistered(bool registered);

    // NO friend is allowed here. :(
};

/// Printing/Output function for a participant
/// \param os - The output stream
/// \param participant - The participant to print
/// \return The output stream that was given after
///  having sent the participant's info through it
ostream& operator<<(ostream& os, const Participant& participant);
//---------------------------------------------------

class Voter
{
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

    // NO friend is allowed here. :(

};

ostream& operator<<(ostream& os, const Voter& voter);
// -----------------------------------------------------------

struct Vote
{
    Voter& m_voter;
    string* m_states;

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

    class VoteCompare {
        VoterType type;
    public:
        explicit VoteCompare(VoterType v_type);
        bool operator()(MainControl::Iterator iter1, MainControl::Iterator iter2);
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

    // Also it's allowed here to define friend. :)
    friend ostream& operator<<(ostream& os, const MainControl& eurovision);
};

ostream& operator<<(ostream& os, const MainControl& eurovision);

// -----------------------------------------------------------

#endif
