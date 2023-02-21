#include <catch2/catch_test_macros.hpp>

#include <core/mat.h>
#include <core/math.h>
#include <core/quat.h>
#include <core/vec.h>

TEST_CASE("Quaternion can rotate vectors", "[quaternion]")
{
    vec3 xAxis = { 1, 0, 0 };
    vec3 yAxis = { 0, 1, 0 };
    vec3 zAxis = { 0, 0, 1 };

    float rightAngle = M_PI / 2;

    SECTION("Around Y Axis")
    {
        vec3 vecToRotate = { 1, 0, 0 };
        quat q = quat_rotation(rightAngle, yAxis);
        vec3 rotated = (q * quat(vecToRotate) * q.Inverse()).ToVec3();

        REQUIRE(rotated.x == 0);
        REQUIRE(rotated.z == -1);
    }

    SECTION("Around X Axis") { vec3 vecToRotate = { 0, 1, 0 };
        quat q = quat_rotation(rightAngle, xAxis);
        vec3 rotated = (q * quat(vecToRotate) * q.Inverse()).ToVec3();

        REQUIRE(rotated.y == 0);
        REQUIRE(rotated.z == 1);
    }

    SECTION("Around Z Axis")
    {
        vec3 vecToRotate = { 0, 1, 0 };
        quat q = quat_rotation(rightAngle, zAxis);
        vec3 rotated = (q * quat(vecToRotate) * q.Inverse()).ToVec3();

        REQUIRE(rotated.y == 0);
        REQUIRE(rotated.x == -1);
    }
}