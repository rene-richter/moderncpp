#ifndef GEOMETRIC_SEQUENCE_HPP
#define GEOMETRIC_SEQUENCE_HPP

class GeometricSequence
{
public:
	using Number = double;

    GeometricSequence(Number start, Number factor);
    Number value() const;
    void next();
private:    
    Number current_;
    Number factor_;
};

#endif
