#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

namespace config
{
	inline constexpr float epsilon{ 0.000001f };
}

template<typename T>
class Vector3D
{
public:
	Vector3D()
	: x{ T(0.0) }
	, y{ T(0.0) }
	, z{ T(0.0) }
	{}

	Vector3D(T in_x, T in_y, T in_z)
	: x{ in_x }
	, y{ in_y }
	, z{ in_z }
	{}

	/* Operators */
	Vector3D operator+(const Vector3D& rhs) const
	{
		return Vector3D
		{ 
			x + rhs.x, 
			y + rhs.y, 
			z + rhs.z 
		};
	}

	Vector3D& operator+=(const Vector3D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3D operator-(const Vector3D& rhs) const
	{
		return Vector3D
		{
			x - rhs.x,
			y - rhs.y,
			z - rhs.z
		};
	}

	Vector3D& operator-=(const Vector3D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	// Vector scaling
	Vector3D& operator*=(const float scalar)
	{
		x * scalar;
		y * scalar;
		z * scalar;
		return *this;
	}

	// Vector multiply (non-uniform scale)
	Vector3D operator*(const Vector3D& rhs) const
	{
		return Vector3D
		{
			x * rhs.x,
			y * rhs.y,
			z * rhs.z
		};
	}

	Vector3D& operator*=(const Vector3D& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	T length_squared() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	T length() const
	{
		return T(sqrt(length_squared()));
	}

	Vector3D get_normalized() const
	{
		const T size{ length() };
		const T inverse_size{ T(1.0) / size };
		if (size > T(config::epsilon))
		{
			return Vector3D{ *this * inverse_size };
		}

		return Vector3D{};
	}

	Vector3D& normalize()
	{
		const T size{ length() };
		const T inverse_size{ T(1.0) / size };
		if (size > T(config::epsilon))
		{
			*this = *this * inverse_size;
		}

		return *this;
	}

	T dot(const Vector3D& rhs) const
	{
		// Positive result: the vectors point in the same directions
		// Negative result: the vectors point in opposite directions
		// Zero result: the vectors are perpendicular
		return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
	}

	static T dot(const Vector3D& lhs,const Vector3D& rhs)
	{
		// Positive result: the vectors point in the same directions
		// Negative result: the vectors point in opposite directions
		// Zero result: the vectors are perpendicular
		return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
	}

	Vector3D cross(const Vector3D& rhs) const
	{
		return Vector3D
		{
			(y * rhs.z) - (z * rhs.y),
			(z * rhs.x) - (x * rhs.z),
			(x * rhs.y) - (y * rhs.x)
		};
	}

	static Vector3D cross(const Vector3D& lhs, const Vector3D& rhs)
	{
		return Vector3D
		{
			(lhs.y * rhs.z) - (lhs.z * rhs.y),
			(lhs.z * rhs.x) - (lhs.x * rhs.z),
			(lhs.x * rhs.y) - (lhs.y * rhs.x)
		};
	}

public:
	T x;
	T y;
	T z;
};

// Vector scaling
template<typename T>
Vector3D<T> operator*(const Vector3D<T>& lhs, const float scalar)
{
	return Vector3D
	{
		lhs.x * scalar,
		lhs.y * scalar,
		lhs.z * scalar
	};
}

template<typename T>
Vector3D<T> operator*(const float scalar, const Vector3D<T>& rhs)
{
	return Vector3D
	{
		scalar * rhs.x,
		scalar * rhs.y,
		scalar * rhs.z
	};
}

// Aliases
typedef Vector3D<float> Vector3DF;
typedef Vector3D<double> Vector3DD;
typedef Vector3D<double> Vector3DI;

#endif