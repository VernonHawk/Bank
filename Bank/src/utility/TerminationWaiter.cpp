#include "TerminationWaiter.h"

#include <csignal>
#include <mutex>

namespace util
{
	std::condition_variable TerminationWaiter::_condition;

	void TerminationWaiter::wait()
	{
		signal(SIGINT, handleUserInterrupt);

		auto mutex = std::mutex {};
		auto lock  = std::unique_lock<std::mutex> {mutex};

		_condition.wait(lock);

		lock.unlock();
	}

	void TerminationWaiter::handleUserInterrupt(const int signal) noexcept
	{
		if (signal == SIGINT)
			_condition.notify_one();
	}
}