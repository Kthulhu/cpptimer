# CPPTimer
A simple header-only timer library for C++14

##Usage

```C++
#include <iostream>
#include <timer.hpp>

auto duration = timer::measure(YourFunction);

std::cout << timer::set_time_format(timer::TimeFormat::S | timer::TimeFormat::MS)
		  << duration << std::endl;
```

##TimeFormat flags

H - hours

M - minutes

S - seconds

MS - milliseconds
