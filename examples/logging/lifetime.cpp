#include <iostream>
#include <string>

class Log 
{
	std::string msg_;

	auto log(std::string text) const 
	{
		std::cerr << this << " : \'" << msg_ << "\' " << text << ".\n"; 
	}
public:
	// TODO:
	~Log() { log("destroyed"); }
	
	Log() : Log("default") {}
	Log(std::string msg) : msg_(msg) { log("constructed"); }
	Log(Log const& orig) : msg_{orig.msg_} { log("copy constructed"); }	
	Log(Log && orig) : msg_{std::move(orig.msg_)} { log("move constructed"); }	
	
	Log& operator=(Log const& rhs)
	{
		msg_ = rhs.msg_;
		log("copy assigned");
		return *this;
	}
	
	Log& operator=(Log&& rhs)
	{
		swap(msg_, rhs.msg_);
		log("move assigned");
		return *this;
	}
};

Log global{"global"};

auto f(Log param)
{
	static Log slocal{"static local"};

	Log local{"local in f()"};
	return Log{"result"};
}

int main()
{
	Log start{"in main"};
	Log copy{start};
	Log log;

	for (int i = 0; i < 2; ++i)
	{
		Log log{"loop body"};
		Log result = f({"param"});
	}

	{	
		Log log{"a moving story"};
		Log movedfrom = std::move(log);
		log = std::move(movedfrom);
	}
	Log end{"leaving main"};
	copy = end;
}
