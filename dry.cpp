#include <vector>

1)
template<class Iterator, class Predicate>
int CountPairsByCondition(Iterator first, Iterator last, Predicate& pred){
    int count=0;

    for (Iterator i=first; i<last; ++i){
        for (Iterator j=i; j<last; ++j) {
            ++j;
            if (pred(i,j) && pred(j,i)) {
                count++;
            }
        }
    }
    return count;
}

bool isSorted(vector<int> v) {
    using std::vector<int>::iterator;
    std::vector<int>::iterator;
    class BiggerThan {
        int bar;

    public:
        BiggerThan(const int c_bar) : bar(c_bar) {
        }
        bool operator()(iterator a, iterator b) {
            return (*a > bar && *b > bar && *a != *b);
        }
    };

    int current_bar = v.front() - 1;

    for (iterator i=v.begin(); i<v.end()-1; ++i) {
        if ( CountPairsByCondition<iterator, BiggerThan>(i,i+2,BiggerThan(current_bar)) < 1) {
            return false;
        }

        // else
        current_bar = *i;
    }

    return true;
}

2)
a.
    Base::baseMethod
    Base::method (because not a virtual function)
    "from Base"
    A::~A (because dtor is virtual, so it goes first to the derived dtor)
    A::method
    "from A"
    Base::~Base (and after the derived dtor, goes to the base dtor)
    Base::method
    "from Base"
b. make method virtual (?)
c. call from the ctor of A to beseMethod, and than call method

A() {
    baseMethod();
    method();
}