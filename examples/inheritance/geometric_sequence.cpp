#include "geometric_sequence.hpp"

GeometricSequence::GeometricSequence(Number start, Number factor)
: current_{start}
, factor_{factor}
{
}

GeometricSequence::Number GeometricSequence::value() const { return current_; }
void GeometricSequence::next() { current_ *= factor_; }