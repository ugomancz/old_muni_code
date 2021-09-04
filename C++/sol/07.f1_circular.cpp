/* The solution proceeds along the lines of ‹queue.cpp›: we use a
 * singly-linked list. The solution is simpler because we do not
 * need iteration (which was replaced by ‹rotate›. */

#include <memory>

/* A node of the data structure, bog standard. */

struct circular_node
{
    using pointer = std::unique_ptr< circular_node >;
    pointer next;
    int value;
};

/* Like before, we remember the head of the list (as a ‹unique_ptr›)
 * and a pointer to the last node, which we need to implement
 * ‹rotate›. */

class circular
{
    std::unique_ptr< circular_node > head;
    circular_node *last = nullptr;
public:

    bool empty() const { return !last; }

    /* In this case, the ‹push› method works at the head, since we
     * use the list in a stack-like order. We have already seen
     * «move assignment», using the ‹std::move› helper function. */

    void push( int v )
    {
        auto new_head = std::make_unique< circular_node >();
        new_head->value = v;
        new_head->next = std::move( head );
        head = std::move( new_head );
        if ( !last ) last = head.get();
    }

    /* Popping items at the head is quite simple. */

    void pop()
    {
        head = std::move( head->next );
        if ( !head ) last = nullptr;
    }

    /* Access to the top element. */

    int  top() const { return head->value; }
    int &top()       { return head->value; }

    /* And the rotate operation: we pop a node off the head and
     * chain it to the list at the tail end. Must not forget to
     * update the ‹last› pointer. Does not work on empty list. */

    void rotate()
    {
        auto next_head = std::move( head->next );
        last->next = std::move( head );
        last = last->next.get();
        head = std::move( next_head );
    }
};

#include "f1_circular.cpp"
