#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------

class Participant
{
// relevant private members can be defined here, if necessary.
    const String state;
    String song;
    String singer;
    int song_length;
    bool is_registered;
    int regular_votes;
    int judge_votes;

public :
    // need to define here possibly c'tr and d'tr and ONLY methods that
    // are mentioned and demonstrated in the test example that has been published.
    // NO OTHER METHODS SHOULD APPEAR HERE.

    Participant(String state, String song, int song_length, String singer);
    Participant(Participant const&) = delete;

    // get functions:
    String state();
    String song();
    String singer();
    int timeLength();
    bool isRegistered();

    // set functions:
    void update(String name, int length, String singer);
    void updateRegistered(bool registered);

// NO friend is allowed here. :(

};

ostream& operator<<(ostream& os, const Participant& participant);
//---------------------------------------------------


class Voter
{
    // relevant private members can be defined here, if necessary.
    const String state;     // voter's state
    const VoterType type;
    int time_of_votes;

public :
    Voter(String state, VoterType type = Regular); // votes = 0

    // get :
    int timeOfVotes();
    String state();
    VoterType voterType();

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
    Voter voter;
    String states[10];

// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.
    Vote(Voter voter, String state1,
         String state2 = "",
         String state3 = "",
         String state4 = "",
         String state5 = "",
         String state6 = "",
         String state7 = "",
         String state8 = "",
         String state9 = "",
         String state10 = "");
    ~Vote();

};

// -----------------------------------------------------------


class MainControl
{
// relevant private members can be defined here, if necessary.
    static Phase phase;

    Participant* participants; // LINKED LISTS??? (need sort :/)
    int num_of_participants;

    int max_song_length;
    int max_participants;
    int max_regular_votes;

public :


    static Phase getPhase();

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

    MainControl(int max_song_length = 180, int max_participants = 26, int max_regular_votes = 5);

    void setPhase(Phase phase); // not static!
    bool participate(String state);
    bool legalParticipant(Participant participant);

    MainControl& operator+=(const Participant& participant);
    MainControl& operator-=(const Participant& participant);
    MainControl& operator+=(const Vote& vote);


// Also it's allowed here to define friend.

};

ostream& operator<<(ostream& os, const MainControl& eurovision);

// -----------------------------------------------------------

#endif
