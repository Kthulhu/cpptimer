// -*- C++ -*-
// test.cpp -- 
#include <iostream>
#include "timer.hpp"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    auto check_dur = timer::measure([](){ sleep(15); });

    cout << timer::set_time_format(timer::TimeFormat::S | timer::TimeFormat::MS)
	 << check_dur << endl;
    return 0;
}
