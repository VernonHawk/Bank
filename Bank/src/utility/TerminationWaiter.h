#ifndef TERMINATION_WAITER_H
#define TERMINATION_WAITER_H

#include <condition_variable>

namespace util
{
	class TerminationWaiter
	{
	public:
		static void wait();

		// no need to be constructed
		TerminationWaiter() = delete;

	private:
		static std::condition_variable _condition;

		static void handleUserInterrupt(int);
	};
}

#endif
