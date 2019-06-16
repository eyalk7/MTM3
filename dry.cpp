1)
template<class Iterator, class Predicate>
int CountPairsByCondition(Iterator first, Iterator last, Predicate pred){
    // Iterator can use:
        // ++iterator
        // *iterator
        // *iterator1 < *iterator2
        // *iterator1 == *iterator2

    // two loop inside a loop.
    // the outside loop start each time one ahead (so that we don't count the same pair twice)
    // the inside loop starts each time one ahead of the first loop (so that we don't count one object twice as a pair)
}

bool isSorted(vector<int> v) {
    // use the function above
}

2)
a.
    Base::baseMethod
    Base::method (because not a virtual function)
    "from Base"
    A::~A (because dtor is virtual)
    A::method
    "from A"
b. make method virtual?
c. call from the ctor of A to beseMethod, and than call method
