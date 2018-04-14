#include <stdexcept>

class NegativeNumberException : public std::runtime_error {
public:
	NegativeNumberException()
		: std::runtime_error{ "ATTEMPTED TO INPUT NEGATIVE COORDINATE...Try again..." }{}
};