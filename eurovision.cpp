#include "eurovision.h"

//---------------------------------------------------

class Participant
{

    public :

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


};

ostream& operator<<(ostream& os, const Participant& participant);
//---------------------------------------------------

class Voter
{
    public :
    Voter(String state, VoterType type = Regular); // votes = 0

    // get :
    int timeOfVotes();
    String state();
    VoterType voterType();

    Voter& operator++();

};

ostream& operator<<(ostream& os, const Voter& voter);
// -----------------------------------------------------------

struct Vote
{
    // ALL is public here.
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
    public :


    static Phase getPhase();

    MainControl(int max_song_length = 180, int max_participants = 26, int max_regular_votes = 5);

    void setPhase(Phase phase); // not static!
    bool participate(String state);
    legalParticipant(Participant participant);

    MainControl& operator+=(const Participant& participant);
    MainControl& operator-=(const Participant& participant);
    MainControl& operator+=(const Vote& vote);

};

ostream& operator<<(ostream& os, const MainControl& eurovision);

// -----------------------------------------------------------
