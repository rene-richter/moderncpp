#ifndef ARITHMETIC_SEQUENCE_HPP
#define ARITHMETIC_SEQUENCE_HPP

class ArithmeticSequence
{
public:
	using Number = double;

    ArithmeticSequence(Number start, Number step);
    Number value() const;
    void next();
private:    
    Number current_;
    Number step_;
};

#endif
