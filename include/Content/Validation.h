#pragma once

#include <string_view>
#include <regex>

#include <Formats/To.h>

namespace content
{
    struct Truck;
    struct Train;
    struct Plane;

    namespace detail {
        inline constexpr char plain[] = "^ADD Plane \\(\\d+, \\d+\\) \\(\\d+, \\d+\\)$";
        inline constexpr char train[] = "^ADD Train \\(\\d+, \\d+\\) \\(\\d+\\)$";
        inline constexpr char truck[] = "^ADD Truck \\(\\d+, \\d+\\) \\(\\d+, \\(\\d+/\\d+\\)\\)$";
    }

    inline auto validate(const std::string_view str, formats::parse::To<Truck>)
    {
        static std::regex pattern(detail::truck);
        return std::regex_match(str.data(), pattern);
    }

    inline auto validate(const std::string_view str, formats::parse::To<Train>)
    {
        static std::regex pattern(detail::train);
        return std::regex_match(str.data(), pattern);
    }

    inline auto validate(const std::string_view str, formats::parse::To<Plane>)
    {
        static std::regex pattern(detail::plain);
        return std::regex_match(str.data(), pattern);
    }
}
