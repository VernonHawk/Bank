#include "TerminationWaiter.h"

#include <csignal>
#include <mutex>

std::condition_variable util::TerminationWaiter::_condition;

void util::TerminationWaiter::wait()
{
	signal(SIGINT, handleUserInterrupt);

	auto mutex = std::mutex {};
	auto lock  = std::unique_lock<std::mutex> {mutex};

	_condition.wait(lock);

	lock.unlock();
}

void util::TerminationWaiter::handleUserInterrupt(const int signal)
{
	if (signal == SIGINT)
		_condition.notify_one();
}