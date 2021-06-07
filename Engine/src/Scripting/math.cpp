#include "Scripting/modules.hpp"

#include "Math/Math.hpp"

namespace BwatEngine
{
    sol::table open_math(sol::this_state s)
    {
        sol::state_view lua(s);

        sol::table module = lua.create_table();

#define REGISTER_FUNC(utype, uclass, func) utype[#func] = &Math::uclass::func

#define REGISTER_VEC_COMMON_FUNC(utype, uclass)\
{\
REGISTER_FUNC(utype, uclass, DotProduct);\
REGISTER_FUNC(utype, uclass, Amplitude);\
REGISTER_FUNC(utype, uclass, Length);\
REGISTER_FUNC(utype, uclass, Scale);\
REGISTER_FUNC(utype, uclass, GetScaled);\
REGISTER_FUNC(utype, uclass, Normalize);\
REGISTER_FUNC(utype, uclass, GetNormalized);\
REGISTER_FUNC(utype, uclass, SafeNormalize);\
REGISTER_FUNC(utype, uclass, GetSafeNormalized);\
}

#define REGISTER_VEC3(uclass, type)                             \
    {                                                           \
    sol::constructors<Math::uclass(),                           \
                      Math::uclass(type),                       \
                      Math::uclass(type, type, type)> ctor;     \
    auto utype = lua.new_usertype<Math::uclass>(#uclass, ctor,  \
        sol::meta_function::addition,                               \
        &Math::uclass::operator+,                                   \
        sol::meta_function::subtraction,                            \
        &Math::uclass::operator-,                                       \
        sol::meta_function::multiplication,                                \
        &Math::uclass::operator*);                                   \
    REGISTER_VEC_COMMON_FUNC(utype, uclass);                    \
    REGISTER_FUNC(utype, uclass, CrossProduct);                 \
    utype["X"] = &Math::uclass::X;                              \
    utype["Y"] = &Math::uclass::Y;                              \
    utype["Z"] = &Math::uclass::Z;                              \
    }

#define REGISTER_VEC2(uclass, type)                             \
    {                                                           \
    sol::constructors<Math::uclass(),                           \
                      Math::uclass(type),                       \
                      Math::uclass(type, type)> ctor;           \
    auto utype = lua.new_usertype<Math::uclass>(#uclass, ctor,  \
        sol::meta_function::addition,                               \
        &Math::uclass::operator+,                                   \
        sol::meta_function::subtraction,                            \
        &Math::uclass::operator-,                                       \
        sol::meta_function::multiplication,                                \
        &Math::uclass::operator*);                                   \
    REGISTER_VEC_COMMON_FUNC(utype, uclass);                    \
    utype["X"] = &Math::uclass::X;                              \
    utype["Y"] = &Math::uclass::Y;                              \
    }

#define REGISTER_QUAT(uclass, type)                                 \
    {                                                               \
    sol::constructors<Math::uclass(),                               \
                      Math::uclass(type),                           \
                      Math::uclass(type, type, type),               \
                      Math::uclass(type, type, type, type)> ctor;   \
    auto utype = lua.new_usertype<Math::uclass>(#uclass, ctor,      \
        sol::meta_function::addition,                                   \
        &Math::uclass::operator+,                                       \
        sol::meta_function::subtraction,                                \
        &Math::uclass::operator-,                                       \
        sol::meta_function::multiplication,                                \
        &Math::uclass::Mul);                                      \
    REGISTER_FUNC(utype, uclass, Amplitude);                     \
    REGISTER_FUNC(utype, uclass, Norm);                     \
    REGISTER_FUNC(utype, uclass, DotProduct);                     \
    REGISTER_FUNC(utype, uclass, Scale);                     \
    REGISTER_FUNC(utype, uclass, GetScaled);                     \
    REGISTER_FUNC(utype, uclass, Normalize);                     \
    REGISTER_FUNC(utype, uclass, GetNormalized);                     \
    REGISTER_FUNC(utype, uclass, SafeNormalize);                     \
    REGISTER_FUNC(utype, uclass, GetSafeNormalized);                     \
    REGISTER_FUNC(utype, uclass, Conjugate);                     \
    REGISTER_FUNC(utype, uclass, GetConjugate);                     \
    REGISTER_FUNC(utype, uclass, Invert);                     \
    REGISTER_FUNC(utype, uclass, GetInverted);                     \
    REGISTER_FUNC(utype, uclass, GetEulerAngles);                     \
    REGISTER_FUNC(utype, uclass, Rotate);                           \
    REGISTER_FUNC(utype, uclass, LookAt);                                   \
    utype["X"] = &Math::uclass::X;                                  \
    utype["Y"] = &Math::uclass::Y;                                  \
    utype["Z"] = &Math::uclass::Z;                                  \
    utype["W"] = &Math::uclass::W;                                  \
    }

        REGISTER_VEC3(Vec3f, float);
        REGISTER_VEC3(Vec3d, double);

        REGISTER_VEC2(Vec2f, float);
        REGISTER_VEC2(Vec2d, double);

        REGISTER_QUAT(Quatf, float);
        REGISTER_QUAT(Quatd, double);

        module.new_usertype<Math::Transform>("Transform",
                                         "position", &Math::Transform::position,
                                         "rotation", &Math::Transform::rotation,
                                         "scale", &Math::Transform::scale
        );

#define REGISTER_MATH(func) module.set_function(#func, Math::func)

        REGISTER_MATH(Sin);
        REGISTER_MATH(Asin);
        REGISTER_MATH(Cos);
        REGISTER_MATH(Acos);
        REGISTER_MATH(Tan);
        REGISTER_MATH(Atan);
        REGISTER_MATH(ToRads);
        REGISTER_MATH(ToDegs);
        REGISTER_MATH(Clamp);
        REGISTER_MATH(Abs);
        REGISTER_MATH(Pow);
        REGISTER_MATH(Sqrt);
        REGISTER_MATH(Exp);
        REGISTER_MATH(Log);
        REGISTER_MATH(Log10);
        REGISTER_MATH(Log2);
        REGISTER_MATH(Floor);
        REGISTER_MATH(Ceil);
        REGISTER_MATH(Round);
        REGISTER_MATH(Trunc);

        module["PI"] = Math::PI;

        return module;
    }
}