#ifndef _REMINDER_HPP
#define _REMINDER_HPP

#include <utility>
#include <thread>


namespace intent 
{
    template <typename FunctionPrev, typename FunctionAfter>
    class Reminder
    {
        private:
            FunctionPrev prev;
            FunctionAfter after;
        public:
            Reminder(FunctionPrev p, FunctionAfter a) : 
                prev{std::move(p)}, after{std::move(a)}
            {
                prev();
            }

            Reminder(void) = default;
            Reminder(Reminder const&) = delete;
            Reminder &operator=(Reminder const&) = delete;


            Reminder(Reminder &&r) :
                prev(std::move(r.prev)),
                after(std::move(r.after))
            { }
            Reminder &operator=(Reminder &&r) 
            {
                prev = std::move(r.prev);
                after = std::move(r.after);
                return *this;
            }


            ~Reminder(void)
            {
                after();
            }

    };




}

#endif // _REMINDER_HPP