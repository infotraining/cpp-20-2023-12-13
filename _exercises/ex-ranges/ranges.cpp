#include <helpers.hpp>
#include <iostream>
#include <list>
#include <map>
#include <ranges>
#include <set>
#include <source_location>
#include <string>
#include <unordered_map>
#include <vector>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& p)
{
    out << "{" << p.first << "," << p.second << "}";
    return out;
}

#include <catch2/catch_test_macros.hpp>

using namespace std::literals;

std::pair<std::string_view, std::string_view> split(std::string_view line, std::string_view separator = "/")
{
    std::pair<std::string_view, std::string_view> result;

    if (std::string::size_type pos = line.find(separator.data()); pos != std::string::npos)
    {
        result.first = std::string_view{line.begin(), line.begin() + pos};
        result.second = std::string_view{line.begin() + pos + 1, line.end()};
    }

    return result;
}

TEST_CASE("split")
{
    std::string s1 = "324/44";
    CHECK(split(s1) == std::pair{"324"sv, "44"sv});

    std::string s2 = "4343";
    CHECK(split(s2) == std::pair{""sv, ""sv});

    std::string s3 = "345/";
    CHECK(split(s3) == std::pair{"345"sv, ""sv});

    std::string s4 = "/434";
    CHECK(split(s4) == std::pair{""sv, "434"sv});
}

TEST_CASE("Exercise - ranges")
{
    std::vector<std::string_view> lines = {
        "# Comment 1",
        "# Comment 2",
        "# Comment 3",
        "\n",
        "\n",
        "1/one",
        "2/two",
        "\n",
        "3/three",
        "4/four",
        "5/five",
        "\n",
        "\n",
        "6/six"};

    helpers::print(lines, "lines");

    auto result = std::views::counted(lines.begin(), lines.size())
        | std::views::drop_while([](std::string_view str) { return str.starts_with("#"); })
        | std::views::filter([](std::string_view str) { return str != "\n"; })
        | std::views::transform([](std::string_view str) { return split(str).second; });
        // | std::ranges::to<std::vector>(); // C++23

    auto expected_result = {"one"s, "two"s, "three"s, "four"s, "five"s, "six"s};
    CHECK(std::ranges::equal(result, expected_result));

    auto common_it_wrapper = std::views::common(result);
    std::vector<std::string_view> result_vec(common_it_wrapper.begin(), common_it_wrapper.end());

    helpers::print(result_vec, "result_vec");
}