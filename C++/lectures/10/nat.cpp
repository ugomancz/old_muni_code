#include <iostream>

struct Zero {};

template <typename N>
struct Succ {};

template <typename N, typename M>
struct Add;

template <typename M>
struct Add<Zero, M> { using result = M; };

template <typename N, typename M>
struct Add<Succ<N>, M> {
	using result = Succ<typename Add<N, M>::result>;
};

template <typename N, typename M>
using AddResult = typename Add<N, M>::result;

template <typename N, typename M>
struct Mult;

template <typename N, typename M>
using MultResult = typename Mult<N, M>::result;

template <typename M>
struct Mult<Zero, M> {
	using result = Zero;
};

template <typename N, typename M>
struct Mult<Succ<N>, M> {
	using result = AddResult<M, MultResult<N, M>>;
};

template <typename N, typename M>
struct Pow;

template <typename N, typename M>
using PowResult = typename Pow<N, M>::result;

template <typename N>
struct Pow<N, Zero> {
	using result = Succ<Zero>;
};

template <typename N, typename M>
struct Pow<N, Succ<M>> {
	using result = MultResult<N, PowResult<N, M>>;
};

template <typename N>
struct Fact;

template <typename N>
using FactResult = typename Fact<N>::result;

template <>
struct Fact<Zero> {
	using result = Succ<Zero>;
};

template <typename N>
struct Fact<Succ<N>> {
	using result = MultResult<Succ<N>, FactResult<N>>;
};

using One = Succ<Zero>;
using Two = Succ<One>;
using Three = Succ<Two>;
using Four = Succ<Three>;

template <typename N>
const int to_int = 0;

template <typename N>
const int to_int<Succ<N>> = 1 + to_int<N>;

template <size_t N>
struct ToNat {
	using result = Succ<typename ToNat<N - 1>::result>;
};

template <>
struct ToNat<0> {
	using result = Zero;
};

template <size_t N>
using ToNatResult = typename ToNat<N>::result;

int main() {
	// AddResult<Two, One>::tell();
	// MultResult<Two, Three>::tell();
	// PowResult<Two, Four>::tell();
	// FactResult<Four>::tell();
	std::cout << to_int<FactResult<Four>> << '\n';
	std::cout << to_int<
		PowResult<
			ToNatResult<2>,
			ToNatResult<8>>> << '\n';
}
