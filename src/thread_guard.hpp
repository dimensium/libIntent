#ifndef _THREAD_GUARD_HPP
#define _THREAD_GUARD_HPP


#include <functional>
#include <thread>
#include "reminder.hpp"

namespace intent 
{
    class ThreadGuard
    {
        private:
            Reminder<std::function<void(void)>, std::function<void(void)>> r;
            std::thread &t;
            bool hold;
        public:
            ThreadGuard(std::thread &t_) : r(
                []{},
                [this]
                {
                    if (t.joinable())
                        t.join();
                }), 
                t(t_),
                hold(true)
            { }

            ThreadGuard(void) = delete;
            ThreadGuard(ThreadGuard const&) = delete;
            ThreadGuard &operator=(ThreadGuard const&) = delete;


            ThreadGuard(ThreadGuard &&tg) :
                t(tg.t), r(std::move(tg.r))
            {
                tg.hold = false;
                hold = true;
            }
            ThreadGuard &operator=(ThreadGuard &&tg)
            {
                r = std::move(tg.r);
                t = std::move(tg.t);
                tg.hold = false;
                hold = true;
                return *this;
            }
    };
}



#endif // _THREAD_GUARD_HPP