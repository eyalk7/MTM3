1)
#include <vector>
using std::vector;

template<class Iterator, class Predicate>
int CountPairsByCondition(cosnt Iterator& first, const Iterator& last, const Predicate& pred){
    int count=0;

    for (Iterator i=first; i<last; ++i){
        Iterator j=i;
        ++j;
        for ( ; j<last; ++j) {
            if (pred(i,j) && pred(j,i)) { // validate that the order between the elements does not matter
                count++;
            }
        }
    }
    return count;
}

bool isSorted(vector<int> v) {
    typedef std::vector<int>::iterator v_iterator;

    // predicate object function class
    class BiggerThan {
        int bar;

    public:
        BiggerThan(const int c_bar) : bar(c_bar) {
        }
        bool operator()(const v_iterator& a, const v_iterator& b) const {
            return (*a > bar && *b > bar && *a != *b);
        }
    };

    int current_bar = v.front() - 1;

    // check that every consecutive pair is bigger than the element before both of them
    // and that they aren't equal to each other.
    for (v_iterator i=v.begin(); i<v.end()-1; ++i) {
        if ( CountPairsByCondition<v_iterator, BiggerThan>(i,i+2,BiggerThan(current_bar)) < 1) {
            return false;
        }

        // else
        current_bar = *i;
    }

    return true;
}

2)
a.
    the program calls baseMethod function from a Base pointer, so it search it in Base's public.
    Base::baseMethod calls method function, which exist in Base (and not virtual), so it calls it.
    Base::method prints:
    "from Base"
    the we delete base so the d'tor is called. first A::~A (because Base dtor is virtual).
    A::~A calls method from the class so it goes to A::method, and prints:
    "from A"
    finally, it goes to Base d'tor - Base::~Base which calls method function from inside the class.
    so it goes to Base::method, which prints:
    "from Base"
b.  make Base's method function virtual. that will make the program to check the object real type in run time,
    and call the relevant function to that type. because base points to an A object, than it will call
    A::method instead of Base::method. A::method will print "from A" in the first line, instead of "from Base".
c.  call from the c'tor of A to beseMethod, and than call method
        A() {
            baseMethod();
            method();
        }
        the c'tor of A will be called when we call new A(). than baseMethod will print:
        "from Base" (like we explained in a.)
        and than, method() will call A::method because it calls it from inside A class.
        than, it will print:
        "from A"