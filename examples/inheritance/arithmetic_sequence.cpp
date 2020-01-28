#include "arithmetic_sequence.hpp"

ArithmeticSequence::ArithmeticSequence(Number start, Number step)
: Sequence{start}
, step_{step}
{
}

void ArithmeticSequence::next() { current_ += step_; }