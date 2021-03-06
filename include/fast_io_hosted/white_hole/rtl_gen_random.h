#pragma once

namespace fast_io
{

template<std::integral ch_type>
class basic_rtl_gen_random
{
public:
	using char_type = ch_type;
};

namespace details
{

extern "C" int __stdcall SystemFunction036(void*,std::uint32_t);
inline void rtl_gen_random_read(void* ptr,std::size_t sz)
{
	if constexpr(sizeof(std::uint32_t)<sizeof(std::size_t))
	{
		for(;sz;)
		{
			std::size_t mn = std::min(sz,static_cast<std::size_t>(std::numeric_limits<std::uint32_t>::max()));
			if(!SystemFunction036(ptr,static_cast<std::uint32_t>(mn)))
				throw_win32_error();
			sz-=mn;
		}
	}
	else
	{
		if(!SystemFunction036(ptr,static_cast<std::uint32_t>(sz)))
			throw_win32_error();
	}
}

}

template<std::integral char_type,std::contiguous_iterator Iter>
inline Iter read(basic_rtl_gen_random<char_type>,Iter bg,Iter ed)
{
	details::rtl_gen_random_read(std::to_address(bg),(ed-bg)*sizeof(*bg));
	return ed;
}

template<std::integral char_type>
inline std::size_t scatter_read(basic_rtl_gen_random<char_type>,std::span<io_scatter_t const> sp)
{
	std::size_t total_bytes{};
	for(auto const& e : sp)
	{
		details::rtl_gen_random_read(const_cast<void*>(e.base),e.len);
		total_bytes+=e.len;
	}
	return total_bytes;
}
using rtl_gen_random = basic_rtl_gen_random<char>;

template<std::integral char_type>
inline constexpr void require_secure_clear(basic_rtl_gen_random<char_type>){}

}