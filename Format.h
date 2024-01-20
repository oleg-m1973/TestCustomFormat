#pragma once
#include "fmt/format.h"

template <typename... TT>
struct CFormatValueHolder: std::tuple<TT...>
{
	using std::tuple<TT...>::tuple;
	
	constexpr const std::tuple<TT...> &tuple() const noexcept
	{
		return *this;
	}
};

template <typename... TT> CFormatValueHolder(TT&&...) -> CFormatValueHolder<TT...>;

struct FormatString: std::string_view {using std::string_view::string_view;};

template <typename... TT>
struct fmt::formatter<CFormatValueHolder<TT...>>
{
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx) const noexcept
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const CFormatValueHolder<TT...> &val, FormatContext& ctx) const
	{
		return std::apply([&](auto&&... vals)
		{
			return ((fmt::format_to(ctx.out(), "{}", vals)), ...);
		}, val.tuple());
	}
};

template <typename... TT>
struct fmt::formatter<CFormatValueHolder<FormatString, TT...>>
{
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx) const noexcept
	{
		return ctx.begin();
	}

	template <typename THolder, typename FormatContext>
	auto format(const THolder &val, FormatContext& ctx) const
	{
		return std::apply([&](std::string_view fmt, auto&&... vals)
		{
			return fmt::format_to(ctx.out(), fmt::runtime(fmt), vals...);
		}, val.tuple());
	}
};

template <typename... TT>
auto doFormat(FormatString fmt, TT&&... args) noexcept
{
	return CFormatValueHolder(std::move(fmt), std::forward<TT>(args)...);
}
