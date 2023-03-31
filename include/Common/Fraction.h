#ifndef INTERPRETER_FRACTION_H
#define INTERPRETER_FRACTION_H

#include <cstdint>
#include <stdexcept>
#include <limits>

template<typename Value>
Value gcd(Value numerator, Value denominator);

template<typename value_type>
struct FractionV
{
    FractionV()
    {
        numerator = 0;
        denominator = std::numeric_limits<value_type>::max();
    }

    explicit FractionV(value_type num)
    {
        numerator = num;
        denominator = 1;
    }
    
    explicit FractionV(value_type num, value_type den)
    {
        numerator = num / gcd(num, den);
        if (den == 0)
        {
            throw std::logic_error("");
        } else
        {
            denominator = den / gcd(num, den);
        }
    }

    FractionV operator=(const FractionV & other)
    {
        numerator = other.numerator;
        denominator = other.denominator;
        return *this;
    }
    
    FractionV operator+(const FractionV & other)
    {
        value_type n = numerator * other.denominator + other.numerator * denominator;
        value_type d = denominator * other.denominator;
        return FractionV(n / gcd(n, d), d / gcd(n, d));
    }
    
    FractionV operator-(const FractionV & other)
    {
        value_type n = numerator * other.denominator - other.numerator * denominator;
        value_type d = denominator * other.denominator;
        return FractionV(n / gcd(n, d), d / gcd(n, d));
    }
    
    FractionV operator*(const FractionV & other)
    {
        value_type n = numerator * other.numerator;
        value_type d = denominator * other.denominator;
        return FractionV(n / gcd(n, d), d / gcd(n, d));
    }
    
    FractionV operator/(const FractionV & other)
    {
        value_type n = numerator * other.denominator;
        value_type d = denominator * other.numerator;
        return FractionV(n / gcd(n, d), d / gcd(n, d));
    }
    
    FractionV operator+=(const FractionV & other)
    {
        value_type n = numerator * other.denominator + other.numerator * denominator;
        value_type d = denominator * other.denominator;
        numerator = n / gcd(n, d);
        denominator = d / gcd(n, d);
        return *this;
    }
    
    bool operator>(const FractionV & other)
    {
        value_type first = numerator * other.denominator / gcd(numerator, denominator);
        value_type second = other.numerator * denominator / gcd(other.numerator, other.denominator);
        return first > second;
    }
    
    bool operator<(const FractionV & other)
    {
        value_type first = numerator * other.denominator / gcd(numerator, denominator);
        value_type second = other.numerator * denominator / gcd(other.numerator, other.denominator);
        return first < second;
    }
    
    bool operator==(const FractionV & other)
    {
        value_type first = numerator * other.denominator / gcd(numerator, denominator);
        value_type second = other.numerator * denominator / gcd(other.numerator, other.denominator);
        return first == second;
    }
    
    bool operator!=(const FractionV & other)
    {
        value_type first = numerator * other.denominator / gcd(numerator, denominator);
        value_type second = other.numerator * denominator / gcd(other.numerator, other.denominator);
        return first != second;
    }
    
    bool operator<=(const FractionV & other)
    {
        return (*this == other) || *this < other;
    }
    
    bool operator>=(const FractionV & other)
    {
        return (*this == other) || *this > other;
    }

    value_type num() const
    {
        return numerator;
    }
    value_type den() const
    {
        return denominator;
    }

private:

    value_type numerator;
    value_type denominator;
};

using Fraction = FractionV<std::uint32_t>;

template<typename Value>
Value gcd(Value numerator, Value denominator)
{
    Value remainder;
    while (denominator != 0)
    {
        remainder = numerator % denominator;
        numerator = denominator;
        denominator = remainder;
    }
    return numerator;
}


#endif //INTERPRETER_FRACTION_H
