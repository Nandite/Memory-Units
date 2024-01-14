// Copyright (c) 2020 Papa Libasse Sow.
// https://github.com/Nandite/Memory-Units
// Distributed under the MIT Software License (X11 license).
//
// SPDX-License-Identifier: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef MEMORY_UNITS_HPP
#define MEMORY_UNITS_HPP
#include <cstdint>
#include <limits>
#include <ratio>
#include <type_traits>
namespace mu
{
    using INT_UNIT_TYPE = std::uint64_t;
    using FLOAT_UNIT_TYPE = double;
    namespace details
    {
        template<typename Tp>
        struct identity {
            using type = Tp;
        };

        template<bool Condition, typename Tp = void>
        using Precondition [[maybe_unused]] = typename std::enable_if<Condition, Tp>::type;

        template<typename... Args>
        using common_type_t = typename std::common_type<Args...>::type;

        template<bool Condition>
        struct bool_to_type;

        template<>
        struct bool_to_type<true> : std::true_type {};

        template<>
        struct bool_to_type<false> : std::false_type {};

        // Conjunction
        namespace impl
        {
            template<typename...>
            struct conjunction_impl : std::true_type {};

            template<typename B0>
            struct conjunction_impl<B0> : B0 {};

            template<typename B0, typename... Bn>
            struct conjunction_impl<B0, Bn...> : std::conditional<B0::value, conjunction_impl<Bn...>, B0>::type {};
        } // namespace impl

        template<typename... Bn>
        struct conjunction : impl::conjunction_impl<Bn...> {};

        template<typename... Bn>
        [[maybe_unused]] constexpr auto conjunction_v{conjunction<Bn...>::value};

        // Disjunction
        namespace impl
        {
            template<typename...>
            struct disjunction_impl : std::false_type {};

            template<typename B0>
            struct disjunction_impl<B0> : B0 {};

            template<typename B0, typename... Bn>
            struct disjunction_impl<B0, Bn...> : std::conditional<B0::value, B0, disjunction_impl<Bn...>>::type {};
        } // namespace impl

        template<typename... Bn>
        struct disjunction : impl::disjunction_impl<Bn...> {};

        template<typename... Bn>
        [[maybe_unused]] constexpr auto disjunction_v{disjunction<Bn...>::value};

        template<typename Tp>
        struct invert_bool_constant : std::integral_constant<bool, !static_cast<bool>(Tp::value)> {};
        template<typename Tp>
        using invert_bool_constant_t = typename invert_bool_constant<Tp>::type;

        // Negation
        template<typename B>
        struct negation : invert_bool_constant_t<B> {};

        template<typename B>
        [[maybe_unused]] constexpr auto negation_v{negation<B>::value};

        template<typename... Bn>
        using and_t = conjunction<Bn...>;

        template<typename... Bn>
        using or_t = disjunction<Bn...>;

        template<typename B>
        using not_t = negation<B>;

        template<typename... Bn>
        constexpr auto and_v{and_t<Bn...>::value};

        template<typename... Bn>
        constexpr auto or_v{or_t<Bn...>::value};

        template<typename B>
        constexpr auto not_v{not_t<B>::value};

        template<typename From, typename To>
        constexpr auto is_convertible_v{std::is_convertible<From, To>::value};
    } // namespace details

    template<typename Rep, typename Factor = std::ratio<1>>
    struct memory_size;

    namespace details
    {
        template<typename>
        struct is_ratio : std::false_type {};

        template<intmax_t Num, intmax_t Den>
        struct is_ratio<std::ratio<Num, Den>> : std::true_type {};

        template<typename>
        struct is_memory_size : std::false_type {};

        template<typename Rep, typename Factor>
        struct is_memory_size<memory_size<Rep, Factor>> : std::true_type {};

        template<typename To, typename CommonFactor, typename CommonRep, bool = false, bool = false>
        struct memory_size_cast_impl {
            template<typename Rep, typename Factor>
            static constexpr To cast(const memory_size<Rep, Factor> &from)
            {
                using to_rep = typename To::rep;
                return To(static_cast<to_rep>(static_cast<CommonRep>(from.count()) *
                                              static_cast<CommonRep>(CommonFactor::num) /
                                              static_cast<CommonRep>(CommonFactor::den)));
            }
        };

        template<typename To, typename CommonFactor, typename CommonRep>
        struct memory_size_cast_impl<To, CommonFactor, CommonRep, true, true> {
            template<typename Rep, typename Factor>
            static constexpr To cast(const memory_size<Rep, Factor> &from)
            {
                using toRep = typename To::rep;
                return To(static_cast<toRep>(from.count()));
            }
        };

        template<typename To, typename CommonFactor, typename CommonRep>
        struct memory_size_cast_impl<To, CommonFactor, CommonRep, true, false> {
            template<typename Rep, typename Factor>
            static constexpr To cast(const memory_size<Rep, Factor> &from)
            {
                using to_rep = typename To::rep;
                return To(static_cast<to_rep>(static_cast<CommonRep>(from.count()) /
                                              static_cast<CommonRep>(CommonFactor::den)));
            }
        };

        template<typename To, typename CommonFactor, typename CommonRep>
        struct memory_size_cast_impl<To, CommonFactor, CommonRep, false, true> {
            template<typename Rep, typename Factor>
            static constexpr To cast(const memory_size<Rep, Factor> &from)
            {
                using to_rep = typename To::rep;
                return To(static_cast<to_rep>(static_cast<CommonRep>(from.count()) *
                                              static_cast<CommonRep>(CommonFactor::num)));
            }
        };

    } // namespace details

    template<typename To, typename Rep, typename Factor>
    constexpr details::Precondition<details::is_memory_size<To>::value, To>
    memory_size_cast(const memory_size<Rep, Factor> &from)
    {
        using to_factor = typename To::factor;
        using to_rep = typename To::rep;
        using common_factor = typename std::ratio_divide<Factor, to_factor>::type;
        using common_rep = details::common_type_t<to_rep, Rep, std::intmax_t>;
        using cast_impl = details::memory_size_cast_impl<To, common_factor, common_rep, common_factor::num == 1,
                                                         common_factor::den == 1>;
        return cast_impl::cast(from);
    }


    template<typename Rep, typename Factor>
    struct memory_size {

        using rep = Rep;
        using factor = Factor;

        static_assert(details::not_v<details::is_memory_size<Rep>>, "The representation must not be a memory_size");
        static_assert(details::is_ratio<Factor>::value, "The factor must be a specialization of ratio");
        static_assert(Factor::num, "The factor must be positive");

        constexpr memory_size() = default;

        template<typename OtherRep, typename = details::Precondition<details::and_t<
                                            std::is_convertible<const OtherRep &, rep>,
                                            details::or_t<std::is_floating_point<rep>,
                                                          details::not_t<std::is_floating_point<OtherRep>>>>::value>>
        constexpr explicit memory_size(const OtherRep &other) : quantity(static_cast<rep>(other))
        {
        }

        template<typename OtherRep, typename OtherFactor,
                 typename = details::Precondition<details::or_t<
                         std::is_floating_point<rep>,
                         details::and_t<details::bool_to_type<std::ratio_divide<OtherFactor, factor>::den == 1>,
                                        details::not_t<std::is_floating_point<OtherRep>>>>::value>>
        constexpr explicit memory_size(const memory_size<OtherRep, OtherFactor> &m) :
            quantity(memory_size_cast<memory_size>(m).count())
        {
        }

        [[nodiscard]] constexpr rep count() const { return quantity; }

        constexpr memory_size operator+() const { return *this; }

        constexpr memory_size operator-() const { return memory_size(-quantity); }

        constexpr memory_size &operator++()
        {
            ++quantity;
            return *this;
        }

        constexpr memory_size operator++(int) { return memory_size(quantity++); }

        constexpr memory_size operator--()
        {
            --quantity;
            return *this;
        }

        constexpr memory_size operator--(int) { return memory_size(quantity--); }

        constexpr memory_size &operator+=(const memory_size &other)
        {
            quantity += other.count();
            return *this;
        }

        constexpr memory_size &operator-=(const memory_size &other)
        {
            quantity -= other.count();
            return *this;
        }

        constexpr memory_size &operator*=(const memory_size &other)
        {
            quantity *= other.count();
            return *this;
        }

        constexpr memory_size &operator/=(const memory_size &other)
        {
            quantity /= other.count();
            return *this;
        }

        template<typename OtherRep = rep>
        constexpr details::Precondition<details::not_v<std::is_floating_point<OtherRep>>, memory_size &>
        operator%=(const rep &rhs)
        {
            quantity %= rhs;
            return *this;
        }

        template<typename OtherRep = rep>
        constexpr details::Precondition<details::not_v<std::is_floating_point<OtherRep>>, memory_size &>
        operator%=(const memory_size &other)
        {
            quantity %= other.count();
            return *this;
        }

        static constexpr memory_size zero() noexcept { return memory_size(rep(0)); }

        static constexpr memory_size min() noexcept { return memory_size(std::numeric_limits<rep>::lowest()); }

        static constexpr memory_size max() noexcept { return memory_size(std::numeric_limits<rep>::max()); }

        ~memory_size() = default;

    private:
        rep quantity;
    };

    namespace details
    {
        template<typename Tp>
        struct success_t {
            using type = Tp;
        };
        struct failure_t {};

        template<typename Tp>
        struct detect_member_type {

            template<typename Up>
            static success_t<typename Up::type> test(int);

            template<typename>
            static failure_t test(...);

            using type = decltype(test<Tp>(0));
        };

        template<typename Tp>
        using detect_member_type_t = typename detect_member_type<Tp>::type;

        template<std::intmax_t X, std::intmax_t Y>
        struct static_gcd : static_gcd<Y, (X % Y)> {};

        template<std::intmax_t X>
        struct static_gcd<X, 0> : std::integral_constant<std::intmax_t, X> {};

        template<>
        struct static_gcd<0, 0> : std::integral_constant<std::intmax_t, 1> {};

        template<typename CommonType, typename Factor, typename OtherFactor>
        struct memory_size_common_type_impl {
            using gcdNum = static_gcd<Factor::num, OtherFactor::num>;
            using gcdDen = static_gcd<Factor::den, OtherFactor::den>;
            using commonRep = typename CommonType::type;
            using commonFactor = std::ratio<gcdNum::value, (Factor::den / gcdDen::value) * OtherFactor::den>;
            using type = success_t<memory_size<commonRep, commonFactor>>;
        };

        template<typename Factor, typename OtherFactor>
        struct memory_size_common_type_impl<failure_t, Factor, OtherFactor> {
            using type = failure_t;
        };

        template<typename, typename>
        struct memory_size_common_type {};

        template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
        struct memory_size_common_type<memory_size<Rep, Factor>, memory_size<OtherRep, OtherFactor>>
            : memory_size_common_type_impl<typename detect_member_type<std::common_type<Rep, OtherRep>>::type, Factor,
                                           OtherFactor>::type {};


        template<typename Rep, typename OtherRep,
                 bool = details::is_convertible_v<OtherRep, common_type_t<Rep, OtherRep>>>
        struct common_rep_type {};

        template<typename Rep, typename AnotherRep>
        struct common_rep_type<Rep, AnotherRep, true> : identity<common_type_t<Rep, AnotherRep>> {};
    } // namespace details

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr typename details::memory_size_common_type<memory_size<Rep, Factor>,
                                                        memory_size<OtherRep, OtherFactor>>::type
    operator+(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        using lhs_t = memory_size<Rep, Factor>;
        using rhs_t = memory_size<OtherRep, OtherFactor>;
        using common_type = typename details::memory_size_common_type<lhs_t, rhs_t>::type;
        return common_type(common_type(lhs).count() + common_type(rhs).count());
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr typename details::memory_size_common_type<memory_size<Rep, Factor>,
                                                        memory_size<OtherRep, OtherFactor>>::type
    operator-(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        using lhs_t = memory_size<Rep, Factor>;
        using rhs_t = memory_size<OtherRep, OtherFactor>;
        using common_type = typename details::memory_size_common_type<lhs_t, rhs_t>::type;
        return common_type(common_type(lhs).count() - common_type(rhs).count());
    }

    template<typename Rep, typename Factor, typename OtherRep>
    constexpr memory_size<typename details::common_rep_type<Rep, OtherRep>::type, Factor>
    operator*(const memory_size<Rep, Factor> &lhs, const OtherRep &rhs)
    {
        using common_type = memory_size<typename details::common_rep_type<Rep, OtherRep>::type, Factor>;
        return common_type(common_type(lhs).count() * rhs);
    }

    template<typename Rep, typename Factor, typename OtherRep>
    constexpr memory_size<typename details::common_rep_type<Rep, OtherRep>::type, Factor>
    operator*(const OtherRep &lhs, const memory_size<Rep, Factor> &rhs)
    {
        return rhs * lhs;
    }

    template<typename Rep, typename Factor, typename OtherRep>
    constexpr memory_size<typename details::common_rep_type<Rep, OtherRep>::type, Factor>
    operator/(const memory_size<Rep, Factor> &lhs, const OtherRep &rhs)
    {
        using common_type = memory_size<typename details::common_rep_type<Rep, OtherRep>::type, Factor>;
        return common_type(common_type(lhs).count() / rhs);
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr typename details::common_rep_type<Rep, OtherRep>::type
    operator/(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        using lhs_t = memory_size<Rep, Factor>;
        using rhs_t = memory_size<OtherRep, OtherFactor>;
        using common_type = typename details::memory_size_common_type<lhs_t, rhs_t>::type;
        return common_type(lhs).count() / common_type(rhs).count();
    }

    template<typename Rep, typename Factor, typename AnotherRep>
    constexpr memory_size<
            typename details::common_rep_type<
                    Rep, details::Precondition<details::not_v<details::is_memory_size<AnotherRep>>, AnotherRep>>::type,
            Factor>
    operator%(const memory_size<Rep, Factor> &lhs, const AnotherRep &rhs)
    {
        using common_type = memory_size<typename details::common_rep_type<Rep, AnotherRep>::type, Factor>;
        return common_type(common_type(lhs).count() % rhs);
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr typename details::memory_size_common_type<memory_size<Rep, Factor>,
                                                        memory_size<OtherRep, OtherFactor>>::type
    operator%(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        using lhs_t = memory_size<Rep, Factor>;
        using rhs_t = memory_size<OtherRep, OtherFactor>;
        using common_type = typename details::memory_size_common_type<lhs_t, rhs_t>::type;
        return common_type(common_type(lhs).count() % common_type(rhs).count());
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr bool operator==(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        using lhs_t = memory_size<Rep, Factor>;
        using rhs_t = memory_size<OtherRep, OtherFactor>;
        using common_type = typename details::memory_size_common_type<lhs_t, rhs_t>::type;
        return common_type(lhs).count() == common_type(rhs).count();
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr bool operator<(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        using lhs_t = memory_size<Rep, Factor>;
        using rhs_t = memory_size<OtherRep, OtherFactor>;
        using common_type = typename details::memory_size_common_type<lhs_t, rhs_t>::type;
        return common_type(lhs).count() < common_type(rhs).count();
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr bool operator!=(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        return !(rhs == lhs);
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr bool operator<=(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        return !(rhs < lhs);
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr bool operator>(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        return rhs < lhs;
    }

    template<typename Rep, typename Factor, typename OtherRep, typename OtherFactor>
    constexpr bool operator>=(const memory_size<Rep, Factor> &lhs, const memory_size<OtherRep, OtherFactor> &rhs)
    {
        return !(lhs < rhs);
    }

    namespace details
    {
        using b = std::ratio<1>;

        // Base 10 measurement system
        using kb = std::ratio<1000 * b::num>;
        using mb = std::ratio<1000 * kb::num>;
        using gb = std::ratio<1000 * mb::num>;
        using tb = std::ratio<1000 * gb::num>;
        using pb = std::ratio<1000 * tb::num>;
        using eb = std::ratio<1000 * pb::num>;

        // Base 2 measurement system
        using kib = std::ratio<1024 * b::num>;
        using mib = std::ratio<1024 * kib::num>;
        using gib = std::ratio<1024 * mib::num>;
        using tib = std::ratio<1024 * gib::num>;
        using pib = std::ratio<1024 * tib::num>;
        using eib = std::ratio<1024 * pib::num>;
    } // namespace details

    using bytes = memory_size<INT_UNIT_TYPE>;

    using kilobytes = memory_size<INT_UNIT_TYPE, details::kb>;
    using megabytes = memory_size<INT_UNIT_TYPE, details::mb>;
    using gigabytes = memory_size<INT_UNIT_TYPE, details::gb>;
    using terabytes = memory_size<INT_UNIT_TYPE, details::tb>;
    using petabytes = memory_size<INT_UNIT_TYPE, details::pb>;
    using exabytes = memory_size<INT_UNIT_TYPE, details::eb>;

    using kibibytes = memory_size<INT_UNIT_TYPE, details::kib>;
    using mebibytes = memory_size<INT_UNIT_TYPE, details::mib>;
    using gibibytes = memory_size<INT_UNIT_TYPE, details::gib>;
    using tebibytes = memory_size<INT_UNIT_TYPE, details::tib>;
    using pebibytes = memory_size<INT_UNIT_TYPE, details::pib>;
    using exbibytes = memory_size<INT_UNIT_TYPE, details::eib>;

    using f_bytes = memory_size<FLOAT_UNIT_TYPE>;

    using f_kilobytes = memory_size<FLOAT_UNIT_TYPE, details::kb>;
    using f_megabytes = memory_size<FLOAT_UNIT_TYPE, details::mb>;
    using f_gigabytes = memory_size<FLOAT_UNIT_TYPE, details::gb>;
    using f_terrabytes = memory_size<FLOAT_UNIT_TYPE, details::tb>;
    using f_petabytes = memory_size<FLOAT_UNIT_TYPE, details::pb>;
    using f_exabytes = memory_size<FLOAT_UNIT_TYPE, details::eb>;

    using f_kibibytes = memory_size<FLOAT_UNIT_TYPE, details::kib>;
    using f_mebibytes = memory_size<FLOAT_UNIT_TYPE, details::mib>;
    using f_gibibytes = memory_size<FLOAT_UNIT_TYPE, details::gib>;
    using f_tebibytes = memory_size<FLOAT_UNIT_TYPE, details::tib>;
    using f_pebibytes = memory_size<FLOAT_UNIT_TYPE, details::pib>;
    using f_exbibytes = memory_size<FLOAT_UNIT_TYPE, details::eib>;


    namespace literals
    {

        namespace parse_details
        {

            template<std::size_t Base, std::size_t Magnitude>
            struct digit_impl : std::true_type {
                static_assert(Base > Magnitude, "Invalid digit detected");
                using type = std::integral_constant<std::size_t, Magnitude>;
            };

            template<std::size_t, char>
            struct digit : std::false_type {};

            template<std::size_t Base>
            struct digit<Base, '0'> : digit_impl<Base, 0> {};

            template<std::size_t Base>
            struct digit<Base, '1'> : digit_impl<Base, 1> {};

            template<std::size_t Base>
            struct digit<Base, '2'> : digit_impl<Base, 2> {};

            template<std::size_t Base>
            struct digit<Base, '3'> : digit_impl<Base, 3> {};

            template<std::size_t Base>
            struct digit<Base, '4'> : digit_impl<Base, 4> {};

            template<std::size_t Base>
            struct digit<Base, '5'> : digit_impl<Base, 5> {};

            template<std::size_t Base>
            struct digit<Base, '6'> : digit_impl<Base, 6> {};

            template<std::size_t Base>
            struct digit<Base, '7'> : digit_impl<Base, 7> {};

            template<std::size_t Base>
            struct digit<Base, '8'> : digit_impl<Base, 8> {};

            template<std::size_t Base>
            struct digit<Base, '9'> : digit_impl<Base, 9> {};

            template<std::size_t Base>
            struct digit<Base, 'a'> : digit_impl<Base, 0xa> {};

            template<std::size_t Base>
            struct digit<Base, 'A'> : digit_impl<Base, 0xa> {};

            template<std::size_t Base>
            struct digit<Base, 'b'> : digit_impl<Base, 0xb> {};

            template<std::size_t Base>
            struct digit<Base, 'B'> : digit_impl<Base, 0xb> {};

            template<std::size_t Base>
            struct digit<Base, 'c'> : digit_impl<Base, 0xc> {};

            template<std::size_t Base>
            struct digit<Base, 'C'> : digit_impl<Base, 0xc> {};

            template<std::size_t Base>
            struct digit<Base, 'd'> : digit_impl<Base, 0xd> {};

            template<std::size_t Base>
            struct digit<Base, 'D'> : digit_impl<Base, 0xd> {};

            template<std::size_t Base>
            struct digit<Base, 'e'> : digit_impl<Base, 0xe> {};

            template<std::size_t Base>
            struct digit<Base, 'E'> : digit_impl<Base, 0xe> {};

            template<std::size_t Base>
            struct digit<Base, 'f'> : digit_impl<Base, 0xf> {};

            template<std::size_t Base>
            struct digit<Base, 'F'> : digit_impl<Base, 0xf> {};

            template<std::size_t Base>
            struct digit<Base, '\''> : std::false_type {
                using type = std::integral_constant<std::size_t, 0>;
            };

            template<unsigned long long Value>
            using big_constant = std::integral_constant<unsigned long long, Value>;

            template<std::size_t Base, char Digit, char... Rest>
            struct power_count_impl
                : big_constant<(digit<Base, Digit>::value ? Base : 1ULL) * power_count_impl<Base, Rest...>::value> {};

            template<std::size_t Base, char Digit>
            struct power_count_impl<Base, Digit> : big_constant<digit<Base, Digit>::value ? 1ULL : 0ULL> {};

            template<std::size_t Base, char... Digits>
            struct power_count : power_count_impl<Base, Digits...> {};

            template<std::size_t Base, unsigned long long Power, char Digit, char... Digits>
            struct number_impl {
                using digit_rep = digit<Base, Digit>;
                using digit_magnitude = typename digit_rep::type;
                constexpr static auto valid{digit_rep::value};
                using rest = typename number_impl<Base, valid ? Power / Base : Power, Digits...>::type;
                using type = big_constant<digit_magnitude::value * Power + rest::type::value>;
            };

            template<std::size_t Base, unsigned long long Power, char... Digits>
            struct number_impl<Base, Power, '\'', Digits...> : number_impl<Base, Power, Digits...> {
                using type = big_constant<0ULL>;
            };

            template<std::size_t Base, char Digit>
            struct number_impl<Base, 1ULL, Digit> {
                using digit_rep = digit<Base, Digit>;
                using digit_magnitude = typename digit_rep::type;
                using type = big_constant<digit_magnitude::value>;
            };

            template<std::size_t Base, char... Digits>
            struct number : number_impl<Base, power_count<Base, Digits...>::value, Digits...>::type {};

            template<std::size_t Base>
            struct number<Base> {
                using type = big_constant<0ULL>;
            };

            template<char... Digits>
            struct integral_parser : number<10U, Digits...>::type {};
            template<char... Digits>
            struct integral_parser<'0', 'b', Digits...> : number<2U, Digits...>::type {};
            template<char... Digits>
            struct integral_parser<'0', 'B', Digits...> : number<2U, Digits...>::type {};
            template<char... Digits>
            struct integral_parser<'0', 'x', Digits...> : number<16U, Digits...>::type {};
            template<char... Digits>
            struct integral_parser<'0', 'X', Digits...> : number<16U, Digits...>::type {};
            template<char... Digits>
            struct integral_parser<'0', Digits...> : number<8U, Digits...>::type {};

        } // namespace parse_details

        template<typename MemorySize, char... Digits>
        constexpr MemorySize construct_if_no_overflow()
        {
            using Value = parse_details::integral_parser<Digits...>;
            constexpr typename MemorySize::rep value{Value::value};
            static_assert(value >= 0 && value == Value::value,
                          "Literal value cannot be represented by memory size type");
            return MemorySize(value);
        }

        constexpr memory_size<long double> operator"" _B(const long double bytes)
        {
            return memory_size<long double>{bytes};
        }

        template<char... Digits>
        constexpr bytes operator""_B()
        {
            return construct_if_no_overflow<bytes, Digits...>();
        }

        constexpr memory_size<long double, details::kb> operator"" _kB(const long double kilobytes)
        {
            return memory_size<long double, details::kb>{kilobytes};
        }

        constexpr memory_size<long double, details::mb> operator"" _MB(const long double megabytes)
        {
            return memory_size<long double, details::mb>{megabytes};
        }

        constexpr memory_size<long double, details::gb> operator"" _GB(const long double gigabytes)
        {
            return memory_size<long double, details::gb>{gigabytes};
        }

        constexpr memory_size<long double, details::tb> operator"" _TB(const long double terabytes)
        {
            return memory_size<long double, details::tb>{terabytes};
        }

        constexpr memory_size<long double, details::pb> operator"" _PB(const long double petabytes)
        {
            return memory_size<long double, details::pb>{petabytes};
        }

        constexpr memory_size<long double, details::eb> operator"" _EB(const long double exabytes)
        {
            return memory_size<long double, details::eb>{exabytes};
        }

        template<char... Digits>
        constexpr kilobytes operator""_kB()
        {
            return construct_if_no_overflow<kilobytes, Digits...>();
        }

        template<char... Digits>
        constexpr megabytes operator""_MB()
        {
            return construct_if_no_overflow<megabytes, Digits...>();
        }

        template<char... Digits>
        constexpr gigabytes operator""_GB()
        {
            return construct_if_no_overflow<gigabytes, Digits...>();
        }

        template<char... Digits>
        constexpr terabytes operator""_TB()
        {
            return construct_if_no_overflow<terabytes, Digits...>();
        }

        template<char... Digits>
        constexpr petabytes operator""_PB()
        {
            return construct_if_no_overflow<petabytes, Digits...>();
        }

        template<char... Digits>
        constexpr exabytes operator""_EB()
        {
            return construct_if_no_overflow<exabytes, Digits...>();
        }

        constexpr memory_size<long double, details::kib> operator"" _kiB(const long double kilobytes)
        {
            return memory_size<long double, details::kib>{kilobytes};
        }

        constexpr memory_size<long double, details::mib> operator"" _MiB(const long double megabytes)
        {
            return memory_size<long double, details::mib>{megabytes};
        }

        constexpr memory_size<long double, details::gib> operator"" _GiB(const long double gigabytes)
        {
            return memory_size<long double, details::gib>{gigabytes};
        }

        constexpr memory_size<long double, details::tib> operator"" _TiB(const long double terabytes)
        {
            return memory_size<long double, details::tib>{terabytes};
        }

        constexpr memory_size<long double, details::pib> operator"" _PiB(const long double petabytes)
        {
            return memory_size<long double, details::pib>{petabytes};
        }

        constexpr memory_size<long double, details::eib> operator"" _EiB(const long double exabytes)
        {
            return memory_size<long double, details::eib>{exabytes};
        }

        template<char... Digits>
        constexpr kibibytes operator""_kiB()
        {
            return construct_if_no_overflow<kibibytes, Digits...>();
        }

        template<char... Digits>
        constexpr mebibytes operator""_MiB()
        {
            return construct_if_no_overflow<mebibytes, Digits...>();
        }

        template<char... Digits>
        constexpr gibibytes operator""_GiB()
        {
            return construct_if_no_overflow<gibibytes, Digits...>();
        }

        template<char... Digits>
        constexpr tebibytes operator""_TiB()
        {
            return construct_if_no_overflow<tebibytes, Digits...>();
        }

        template<char... Digits>
        constexpr pebibytes operator""_PiB()
        {
            return construct_if_no_overflow<pebibytes, Digits...>();
        }

        template<char... Digits>
        constexpr exbibytes operator""_EiB()
        {
            return construct_if_no_overflow<exbibytes, Digits...>();
        }

    } // namespace litterals


} // namespace mu

#endif // MEMORY_UNITS_HPP
