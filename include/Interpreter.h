#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H

#include <string_view>
#include <variant>

#include <Formats/Parse.h>
#include <Storage/Components/List.h>

#include <Content/Cars.h>

#include <map>
#include <functional>

#include <Storage/Components/ListIterator.h>
#include <Content/Validation.h>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


template<typename Storage>
struct Interpreter
{
    using Content = typename Storage::value_type;

    template<typename T>
    using Predicat = std::function<bool(const T &)>;

    template<typename T>
    using Comparator = std::function<bool(const T &, const T &)>;

public:

    void operator()(Storage & storage, const std::string_view expression) const
    {

        auto pos = expression.find(space);
        auto command = expression.substr(0, pos);

        if (command == "SORT")
        {
            auto comparator = [expression, &pos]() -> Comparator<Content>
            {
                auto type = expression.substr(pos + 1);
                auto comp = Comparator<Content>{};

                if (type == "speed")
                {
                    comp = [](const auto & lhs, const auto & rhs)
                    {
                        return std::visit(
                            [](const auto & lhs, const auto & rhs){ return lhs.speed < rhs.speed; }
                            , lhs, rhs
                        );
                    };
                }
                else if (type == "distance")
                {
                    comp = [](const auto & lhs, const auto & rhs)
                    {
                        return std::visit(
                            [](const auto & lhs, const auto & rhs){ return lhs.distance < rhs.distance; }
                            , lhs, rhs
                        );
                    };
                }

                return comp;
            }();

            sort(storage, std::move(comparator));
        }
        else if (command == "PRINT")
        {
            for (const auto & item : storage) {
                std::visit(
                    [](const auto & item){ print(item); }
                    , item
                );
            }
        }
        else if (command.starts_with("ADD"))
        {
            auto content = parseContent<content::Train, content::Truck, content::Plane>(expression);

            if (!content.has_value())
            {
                throw std::runtime_error(
                    std::string() +
                    "There is no supported structures with such description: <" + expression.data() + '>'
                );
            }

            add(storage, std::move(content.value()));
        }
        else if (command == "REM")
        {
            auto comparator = [expression, &pos]() -> Predicat<Content>
            {
                static constexpr auto equal_symbol = char{'\x3D'};

                const auto line = expression.substr(pos + 1);
                auto op = line.substr(0, line.find(equal_symbol));

                if (op.starts_with("if"))
                {
                    const auto condition_description = line.substr(line.find(space) + 1, line.find(equal_symbol));
                    const auto left = condition_description.substr(0, condition_description.find(equal_symbol));
                    const auto right = condition_description.substr(condition_description.find(equal_symbol) + 1);

                    auto value = std::int32_t{0};

                    try
                    {
                        value = std::stoi(right.data());
                    }
                    catch (const std::exception & exc)
                    {
                        throw std::runtime_error(std::string() + "Can't convert <" + right.data() + "> to an integer\n");
                    }

                    if (left == "speed")
                    {
                        return [value](const auto & item)
                        {
                            return std::visit(
                                [value](const auto & item){ return item.speed == value; }
                                , item
                            );
                        };
                    }
                    else if (left == "distance")
                    {
                        return [value](const auto & item)
                        {
                            return std::visit(
                                [value](const auto & item){ return item.distance == value; }
                                , item
                            );
                        };
                    }

                    throw std::runtime_error(std::string() + "Using unsupported comparator: " + left.data());
                }

                throw std::runtime_error(std::string() + "Using unsupported operator: " + op.data());
            }();

            remove_if(storage, comparator);
        }
    }

private:

    template<typename ... Args>
    auto parseContent(std::string_view expression) const noexcept -> std::optional<Content>
    {
        const auto position = expression.find(space) + 1;

        auto result = std::optional<Content>{};
        ((result = (result)
            ? result
            : validate(expression, formats::parse::To<Args>{})
                ? std::optional<Content>{Parse(expression.substr(position), formats::parse::To<Args>{})}
                : std::nullopt), ...);

        return result;
    }

private:

    static inline constexpr char space = '\x20';
};


#endif //INTERPRETER_INTERPRETER_H
