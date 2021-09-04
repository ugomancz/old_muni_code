/* Another exercise, another class hierarchy. The «abstract base
 * class» will be called ‹prisoner›, and the implementations will be
 * different strategies in the well-known game of (iterated)
 * prisoner's dilemma. */

#include <cassert>

/* The ‹prisoner› class should provide method ‹betray› which takes a
 * boolean (the decision of the other player in the last round) and
 * returns the decision of the player for this round. In general,
 * the ‹betray› method should «not» be ‹const›, because strategies
 * may want to remember past decisions (though we will not implement
 * a strategy like that in this exercise). */

/** chybí virtuální destruktor – pokud by byl někdy potomek zdestruován přes
 ** ukazatel na předka, tak se zdestruuje špatně – může dojít k leaku, nezavolá
 ** se destruktor potomka **/
class prisoner {
public:
    virtual bool betray(bool) const = 0;
};

/* Implement an always-betray strategy in class ‹traitor›, the
 * tit-for-tat strategy in ‹vengeful› and an always-cooperate in
 * ‹benign›. */

class traitor : public prisoner {
    bool betray(bool) const override {
        return true;
    }
};

class vengeful : public prisoner {
    bool betray(bool enemy_betrayal) const override {
        return enemy_betrayal;
    }
};

class benign : public prisoner {
    bool betray(bool) const override {
        return false;
    }
};

/* Implement a simple strategy evaluator in function ‹play›. It
 * takes two prisoners and the number of rounds and returns a
 * negative number if the first one wins, 0 if the game is a tie and
 * a positive number if the second wins. The scoring matrix:
 *
 *  • neither player betrays     2 / 2
 *  • a betrays, b does not:     3 / 0
 *  • a does not betray, b does: 0 / 3
 *  • both betray                1 / 1 */

int play(prisoner &a, prisoner &b, int rounds) {
    bool a_last = false, b_last = false, a_current, b_current;
    int result_a = 0, result_b = 0;
    for (int i = 0; i < rounds; i++) {
        a_current = a.betray(b_last);
        b_current = b.betray(a_last);
        if (!a_current && !b_current) {
            result_a += 2;
            result_b += 2;
        } else if (a_current && !b_current) {
            result_a += 3;
        } else if (!a_current) { // (!a_current && b_current)
            result_b += 3;
        } else { // (a_current && b_current)
            result_a += 1;
            result_b += 1;
        }
        a_last = a_current;
        b_last = b_current;
    }
    return result_b - result_a;
}

int main()
{
    /* We won't bother with making multiple instances per class,
     * since we know those strategies are stateless. */

    traitor t;
    vengeful v;
    benign b;

    /* Each of the strategies played against itself will result in a
     * tie. */

    assert( play( t, t,  1 ) == 0 );
    assert( play( t, t, 10 ) == 0 );

    assert( play( b, b,  1 ) == 0 );
    assert( play( b, b, 10 ) == 0 );

    assert( play( v, v,  1 ) == 0 );
    assert( play( v, v, 10 ) == 0 );

    /* The benign and vengeful strategies also tie with each other,
     * since vengeful behaves exactly like benign when playing
     * against one. */

    assert( play( v, b, 1 ) == 0 );
    assert( play( b, v, 1 ) == 0 );

    /* The traitor beats both other strategies. */

    assert( play( t, b, 1 ) < 0 );
    assert( play( b, t, 1 ) > 0 );
    assert( play( t, v, 1 ) < 0 );
    assert( play( v, t, 1 ) > 0 );

    assert( play( t, b, 10 ) < 0 );
    assert( play( b, t, 10 ) > 0 );
    assert( play( t, v, 10 ) < 0 );
    assert( play( v, t, 10 ) > 0 );
}
