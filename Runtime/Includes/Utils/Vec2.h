#ifndef MLX_UT_VEC2
#define MLX_UT_VEC2

namespace mlxut
{
	template <typename T>
	struct Vec2
	{
		T x;
		T y;
		constexpr Vec2() : x(T(0)), y(T(0)) {}
		constexpr Vec2(T x, T y) : x(x), y(y) {}
	};

	using Vec2i = Vec2<int>;
	using Vec2ui = Vec2<unsigned int>;
	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
}

#endif
