#pragma once

#include <string>
#include <deque>

struct Model {
    using Deque = std::deque<std::string>;
    Deque items;
    Deque::iterator iterator = items.begin();
};
