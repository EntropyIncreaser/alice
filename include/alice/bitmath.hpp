#ifndef ALICE_BITMATH_HPP
#define ALICE_BITMATH_HPP

namespace alice {

template <class Integer>
Integer low_bit(const Integer d)
{ return d & (~d + 1); }

}

#endif // ALICE_BITMATH_HPP
