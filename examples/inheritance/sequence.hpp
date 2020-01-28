#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

class Sequence
{
public:
	using Number = double;

    explicit Sequence(Number start) 
	: current_{start} 
	{
	}
	
    Number value() const { return current_; }
    virtual void next() = 0;
protected:    
    Number current_;
};

#endif
