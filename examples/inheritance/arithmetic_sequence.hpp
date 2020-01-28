#ifndef ARITHMETIC_SEQUENCE_HPP
#define ARITHMETIC_SEQUENCE_HPP

#include "sequence.hpp"

class ArithmeticSequence : public Sequence
{
public:
    ArithmeticSequence(Number start, Number step);
    void next() override;
private:    
    Number step_;
};

#endif
