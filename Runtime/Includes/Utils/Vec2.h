#ifndef MLX_UT_VEC2
#define MLX_UT_VEC2

namespace mlxut
{
	struct ivec2
	{
		int x;
		int y;

		constexpr ivec2() : x(0), y(0) {}
		constexpr ivec2(int _x, int _y) : x(_x), y(_y) {}
	};
}

#endif
