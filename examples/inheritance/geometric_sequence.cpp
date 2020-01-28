#include "geometric_sequence.hpp"

GeometricSequence::GeometricSequence(Number start, Number factor)
: Sequence{start}
, factor_{factor}
{
}

void GeometricSequence::next() { current_ *= factor_; }