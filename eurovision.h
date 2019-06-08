#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;
using std::string;
using std::ostream;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------

class Participant
{
// relevant private members can be defined here, if necessary.
    const string m_state;
    string m_song;
    string m_singer;
    int m_song_length;
    bool m_is_registered;
    int m_regular_votes;
    int m_judge_votes;

public :
    // need to define here possibly c'tr and d'tr and ONLY methods that
    // are mentioned and demonstrated in the test example that has been published.
    // NO OTHER METHODS SHOULD APPEAR HERE.

    Participant(string state, string song, int song_length, string singer);
    Participant(Participant const&) = delete;

    // get functions:
    string state() const;
    string song() const;
    string singer() const;
    int timeLength() const;
    bool isRegistered() const;

    // set functions:
    void update(string name, int length, string singer);
    void updateRegistered(bool registered);

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
    Voter(string state, VoterType type = Regular); // votes = 0

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
    Voter m_voter;
    string* m_states;

// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.
    Vote(Voter voter, string state1,
         string state2 = "",
         string state3 = "",
         string state4 = "",
         string state5 = "",
         string state6 = "",
         string state7 = "",
         string state8 = "",
         string state9 = "",
         string state10 = "");
    ~Vote();

};

// -----------------------------------------------------------


class MainControl
{
// relevant private members can be defined here, if necessary.
    Participant* m_participants; // LINKED LISTS??? (need sort :/)
    int m_num_of_participants;
    int m_max_song_length;
    int m_max_participants;
    int m_max_regular_votes;
    Phase phase;

public :

    Phase getPhase();

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

    MainControl(int max_song_length = 180, int max_participants = 26, int max_regular_votes = 5);

    void setPhase(Phase phase);
    bool participate(string state) const;
    bool legalParticipant(const Participant& participant) const;

    MainControl& operator+=(const Participant& participant);
    MainControl& operator-=(const Participant& participant);
    MainControl& operator+=(const Vote& vote);


// Also it's allowed here to define friend.

};

ostream& operator<<(ostream& os, const MainControl& eurovision);

// -----------------------------------------------------------

#endif
