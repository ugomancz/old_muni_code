/* Implement the Sieve of Eratosthenes for quickly finding the largest prime
 * smaller than or equal to a given bound. */

#include <cassert>
#include <vector>

int sieve(int bound) {
    std::vector<bool> primes(bound +1, true);
    for (int i = 2; i * i <= bound; ++i) {
        if (primes.at(i)) {
            for (int j = i * i; j <= bound; j += i) {
                primes.at(j) = false;
            }
        }
    }
    int result = -1;
    for (int k = primes.size() - 1; k >= 0; k--) {
        if (primes.at(k)) {
            result = k;
            break;
        }
    }
    return result;
}

int main()
{
    assert( sieve(  10 ) == 7   );
    assert( sieve(  13 ) == 13  );
    assert( sieve(  20 ) == 19  );
    assert( sieve( 200 ) == 199 );
}
