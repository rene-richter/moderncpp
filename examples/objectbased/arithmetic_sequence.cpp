#include "arithmetic_sequence.hpp"

ArithmeticSequence::ArithmeticSequence(Number start, Number step)
: current_{start}
, step_{step}
{
}

ArithmeticSequence::Number ArithmeticSequence::value() const { return current_; }
void ArithmeticSequence::next() { current_ += step_; }