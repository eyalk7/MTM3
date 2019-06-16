1)
template<class Iterator, class Predicate>
int CountPairsByCondition(Iterator first, Iterator last, Predicate& pred){
    // Iterator can use:
        // ++iterator
        // *iterator
        // iterator1 < iterator2
        // iterator1 == iterator2

        pred()

    // two loop inside a loop.
    // the outside loop start each time one ahead (so that we don't count the same pair twice)
    // the inside loop starts each time one ahead of the first loop (so that we don't count one object twice as a pair)


}

bool isSorted(vector<int> v) {
    // use the function above

    // use the iterator of the vector container:
        // v.begin, v.end (we need to check that the iterator has all the needed operator
    // create class of "function object" to pass to the function above
    //
    bool operator()(iterator a, iterator b){
        return (a.index() < b.index() && *a > *b);
    }

    // checks that returns 0;
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