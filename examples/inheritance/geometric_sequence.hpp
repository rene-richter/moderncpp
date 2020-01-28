#ifndef GEOMETRIC_SEQUENCE_HPP
#define GEOMETRIC_SEQUENCE_HPP

#include "sequence.hpp"

class GeometricSequence : public Sequence
{
public:
    GeometricSequence(Number start, Number factor);
    void next() override;
private:    
    Number factor_;
};

#endif
