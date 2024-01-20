#include "Format.h"

template <typename T>
struct Test
{
	Test(T val)
	: m_val(std::move(val))
	{
	}

	T m_val;
};

template <typename T> Test(T &&) -> Test<T>;

template <typename T>
struct fmt::formatter<Test<T>>
{
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const Test<T> &val, FormatContext& ctx)
	{
		 return fmt::format_to(ctx.out(), "Test({})", val.m_val);
	}
};

int main()
{
	fmt::print("The number is {}.\n", 123);
	fmt::print("The number is {}.\n", Test(123));
	fmt::print("The number is {}.\n", CFormatValueHolder(123, 456, Test(789)));
	fmt::print("The number is {}.\n", doFormat("{}, {}, {},", 123, 456, Test(789)));
	return 0;
}
