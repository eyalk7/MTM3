1)
א.)
/// Generic function that iterates over a container and
/// counts the number of pairs that satisfy a given condition
/// (the order of the pair in the condition does not matter).
/// \tparam Iterator - Type of Iterator corresponding to the container
/// \tparam Predicate - The type of condition to check on the pairs
/// \param first - Iterator pointing to the first item in the container
/// \param last - Iterator pointing to the last item in the container
/// \param pred - The condition to check on all the pairs of the container
/// \return The number of pairs in the container that satisfy the given condition
template<class Iterator, class Predicate>
int CountPairsByCondition(const Iterator& first, const Iterator& last, const Predicate& pred){
    int count = 0;

    for (Iterator i=first; i<last; ++i) {
        Iterator j = i;
        ++j;    // j = i + 1 --> the same element will never be a pair on its own
        for (; j < last; ++j) {
            // check the condition is satisfied regardless of the pair's order
            if (pred(i,j) && pred(j,i)) {
                count++;
            }
        }
    }
    return count;
}

ב.)
#include <vector>
using std::vector;

typedef std::vector<int>::iterator Vector_Iterator;
if (v.size() < 2) return true;

// Function Object for the predicate in isSorted
class BiggerThan {
    int m_bar;

public:
    BiggerThan(int bar) : m_bar(bar) {}

    // checks that both integers are bigger than bar and not equal to each other
    bool operator()(const Vector_Iterator& iter1, const Vector_Iterator& iter2) const {
        return (*iter1 > m_bar && *iter2 > m_bar && *iter1 != *iter2);
    }
    void updateBar(int new_bar) {
        m_bar = new_bar;
    }
};

/// Checks if the given integer vector is in ascending order (without equal elements).
/// \param v - An integer vector
/// \return True if the given vector is in ascending order, otherwise False.
bool isSorted(vector<int> v) {
    if (v.empty()) return true; // "empty vector is sorted" is vacuously true

    BiggerThan condition(v.front() - 1);  // initial condition

    // check that both elements in every consecutive pair is
    // bigger than the element before and that they aren't equal to each other
    // <=> check that first element < second element
    for (Vector_Iterator i = v.begin(); i < v.end() - 1; ++i) {
        int pair_count = CountPairsByCondition<Vector_Iterator, BiggerThan>(i, i+2, condition);

        if (pair_count < 1) { // first element >= second element
            return false;     // vector is not ordered in ascending order
        }

        condition.updateBar(*i); // update the condition for next pair
    }

    return true;
}

2)
a.)
    First an object of type A is created and it's being pointed to by a Base pointer.
    Then, the program calls baseMethod() function from that pointer, so it searches it in Base's public functions.
    Base::baseMethod() exists so it is called and in its body it calls Base::method() (which is private and not virtual).
    Base::method() prints:
    "from Base"
    Then the A object is deleted so the d'tor is called. First, A::~A() is executed (because Base d'tor is virtual).
    A::~A() calls A::method() in its body, which in turn prints:
    "from A"
    Finally, the program goes to Base d'tor - Base::~Base() which calls Base::method(), which prints:
    "from Base"
    Overall:
    from Base
    from A
    from Base

b.)  We can make Base's method() function virtual. That will make the program check the object's real type in runtime,
    and call the relevant function to that type. The 'base' variable points to an A object, therefore, it will call
    A::method() instead of Base::method() in the second line in main(). A::method() will then print "from A" in the
    first line, instead of "from Base". Overall the new output will be:
    from A
    from A
    from Base

c.) From A's c'tor call Base::baseMethod(), and then call A::method()
    In code:
        A::A() {
            baseMethod();
            method();
        }
    Now, when A's c'tor is called in the first line in main, Base::baseMethod() will print:
    "from Base" (like we explained in a.)
    and then A::method() will print:
    "from A"
    as required.