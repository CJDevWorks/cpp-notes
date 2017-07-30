
**When lambda should be used**

1. Its more performant. How?




**When bind Can be used in place of lambda**

// move objects >> cant be done in lambda in C++11, in C++14 it can be done via init capture

 std::vector<std::string> names;
 ...
 struct Widget{};
 std::unique_ptr<Widget> uptr = make_unique<Widget>();

 // C++14
 auto fun = [w = std::move(uptr)] (){ ...}

 // C++11
 auto fun = std::bind([](std::unique_ptr<Widget>& up) const {}, std::move(uptr));

 auto fun2 = std::bind([](const std::unique_ptr<Widget>& up) {}, std::move(uptr));