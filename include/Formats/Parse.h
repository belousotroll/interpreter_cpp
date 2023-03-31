#pragma once

#include <Formats/To.h>

namespace formats::parse {

template<typename Value, typename T>
auto Parse(const Value, To<T>);

}