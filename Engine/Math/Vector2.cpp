#include "Vector2.h"
#include <Windows.h>
#include <cmath>
#include <cassert>

namespace Blue
{
    const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
    const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
    const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
    const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);

    Vector2& Vector2::operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& Vector2::operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2& Vector2::operator/=(float scale)
    {
        // 나눌 값이 0이 아닌지 확인하는 것이 좋음.
        assert(scale != 0.0f);

        x /= scale;
        y /= scale;
        return *this;        
    }

    bool Vector2::operator==(const Vector2& other)
    {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2& other)
    {
        return x != other.x || y != other.y;
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    Vector2 operator+(const Vector2& left, const Vector2& right)
    {
        return Vector2(left.x + right.x, left.y + right.y);
    }

    Vector2 operator-(const Vector2& left, const Vector2& right)
    {
        return Vector2(left.x - right.x, left.y - right.y);
    }

    Vector2 operator*(const Vector2& vector, float scale)
    {
        return Vector2(vector.x * scale, vector.y * scale);
    }

    Vector2 operator*(float scale, const Vector2& vector)
    {
        return vector * scale;
    }

    Vector2 operator/(const Vector2& vector, float scale)
    {
        assert(scale != 0.0f);
        return Vector2(vector.x / scale, vector.y / scale);
    }

    std::wstring Blue::Vector2::ToString()
    {
        wchar_t buffer[256];
        swprintf_s(buffer, 256, TEXT("(%f,%f)"), x, y);

        return buffer;
    }

    float Blue::Vector2::Length()
    {
        return sqrtf(x * x + y * y);
    }

    Vector2 Blue::Vector2::Normalized()
    {
        float length = Length();
        return Vector2(x / length, y / length);
    }

    // friend선언이라 Vector2에 종속되지 않아서 Vector2:: 빠짐.
    float Dot(const Vector2& left, const Vector2& right)
    {
        return (left.x * right.x) + (left.y * right.y);
    }

    Vector2 Lerp(const Vector2& from, const Vector2& to, float t)
    {
        return (1.0f - t) * from + t * to;
    }

    bool Blue::Vector2::Equals(const Vector2& other)
    {
        // float 끼리의 비교는 부정확하다 ( 부동 소수점 ).
        return x == other.x && y == other.y;
    }
}
