// -*- C++ -*-
// timer.hpp --
//

#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>


namespace chro = std::chrono;

// timer
namespace timer
{
    // time format
    enum class TimeFormat
    {
    	H = 1, 			// hours
    	M = 2,			// minutes
    	S = 4,			// seconds
    	MS = 8			// milliseconds
    };

    constexpr TimeFormat
    operator|(const TimeFormat & lhs, const TimeFormat & rhs)
    {
    	return static_cast<TimeFormat>
    	    (static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    constexpr TimeFormat
    operator&(const TimeFormat & lhs, const TimeFormat & rhs)
    {
    	return static_cast<TimeFormat>
    	    (static_cast<int>(lhs) & static_cast<int>(rhs));
    }

    class Manip
    {
	TimeFormat _flag = TimeFormat::M | TimeFormat::S | TimeFormat::MS;

    public:
	explicit
	Manip(TimeFormat flag) : _flag(flag) {};

	static int
	getIndex()
	{
	    static int index = std::ios_base::xalloc();
	    return index;
	}

	friend
	std::ostream &
	operator<<(std::ostream & os, Manip m)
	{
	    os.iword(getIndex()) = static_cast<long>(m._flag);
	    return os;
	}

	virtual
	~Manip() {};
    };

    Manip set_time_format(TimeFormat flag)
    { return Manip(flag); }


    template <typename F>
    auto
    measure(const F & functor)
    {
	auto at_start = chro::steady_clock::now();
	functor();
	auto at_end = chro::steady_clock::now();

	return at_end - at_start;
    }
}

template <
    typename Rep,
    typename Period = std::ratio<1>
    >
std::ostream &
operator<<(std::ostream & os,
	   chro::duration<Rep, Period> dur)
{
    timer::TimeFormat flag = timer::TimeFormat::M | timer::TimeFormat::S | timer::TimeFormat::MS;

    auto word = os.iword(timer::Manip::getIndex());

    if (word > 0)
	{
	    flag = static_cast<timer::TimeFormat>(word);
	    os.iword(timer::Manip::getIndex()) = 0;
	}

    os << std::setfill('0');

    auto check_flag = [&flag](const timer::TimeFormat & format)
	{ return (format & flag) == format; };


    // TODO: generalize
    if (check_flag(timer::TimeFormat::H))
	{
	    auto hh = chro::duration_cast<chro::hours>(dur);
	    os << std::setw(2) << hh.count() << ':';
	    dur -= hh;
	}

    if (check_flag(timer::TimeFormat::M))
    	{
    	    auto mm = chro::duration_cast<chro::minutes>(dur);
    	    os << std::setw(2) << mm.count() << ':';
    	    dur -= mm;
    	}

    if (check_flag(timer::TimeFormat::S))
    	{
    	    auto ss = chro::duration_cast<chro::seconds>(dur);
    	    os << std::setw(2) << ss.count() << '.';
    	    dur -= ss;
    	}

    if (check_flag(timer::TimeFormat::MS))
	{
    	    auto ms = chro::duration_cast<chro::milliseconds>(dur);
    	    os << std::setw(3) << ms.count();
    	    dur -= ms;
	}

    return os;
}
