#pragma once

namespace App
{
template<typename T>
struct CurvePointWrapper
{
    float point;
    T value;
};

template<typename T>
struct CurveDataWrapper
{
    [[nodiscard]] Red::curveEInterpolationType GetInterpolationType() const
    {
        return curveData.interpolationType;
    }

    void SetInterpolationType(Red::curveEInterpolationType aValue)
    {
        curveData.interpolationType = aValue;
    }

    [[nodiscard]] Red::curveESegmentsLinkType GetLinkType() const
    {
        return curveData.linkType;
    }

    void SetLinkType(Red::curveESegmentsLinkType aValue)
    {
        curveData.linkType = aValue;
    }

    [[nodiscard]] uint32_t GetSize() const
    {
        return curveData.GetSize();
    }

    void SetSize(uint32_t aNewSize)
    {
        curveData.Resize(aNewSize);
    }

    [[nodiscard]] CurvePointWrapper<T> GetPoint(uint32_t aIndex) const
    {
        Red::CurvePoint<T> point = curveData.GetPoint(aIndex);

        return {point.point, point.value};
    }

    void GetPointValue(uint32_t aIndex, float* aPoint, T* aValue) const
    {
        Red::CurvePoint<T> point = curveData.GetPoint(aIndex);

        *aPoint = point.point;
        *aValue = point.value;
    }

    void SetPoint(uint32_t aIndex, const CurvePointWrapper<T>& acPoint)
    {
        curveData.SetPoint(aIndex, acPoint.point, acPoint.value);
    }

    void SetPointValue(uint32_t aIndex, float aPoint, const T& acValue)
    {
        curveData.SetPoint(aIndex, aPoint, acValue);
    }

    Red::CurveData<T> curveData;
};
}

#define RTTI_DEFINE_CURVEDATA(_type, _name) \
    RTTI_DEFINE_CLASS(App::CurvePointWrapper<_type>, "CurvePoint" #_name, { \
        RTTI_PROPERTY(point); \
        RTTI_PROPERTY(value); \
    }) \
    RTTI_DEFINE_CLASS(App::CurveDataWrapper<_type>, "CurveData" #_name, { \
        RTTI_METHOD(GetInterpolationType); \
        RTTI_METHOD(SetInterpolationType); \
        RTTI_METHOD(GetLinkType); \
        RTTI_METHOD(SetLinkType); \
        RTTI_METHOD(GetSize); \
        RTTI_METHOD(SetSize); \
        RTTI_METHOD(GetPoint); \
        RTTI_METHOD(GetPointValue); \
        RTTI_METHOD(SetPoint); \
        RTTI_METHOD(SetPointValue); \
    })

RTTI_DEFINE_CURVEDATA(float, Float)
RTTI_DEFINE_CURVEDATA(Red::Vector2, Vector2)
RTTI_DEFINE_CURVEDATA(Red::Vector3, Vector3)
RTTI_DEFINE_CURVEDATA(Red::Vector4, Vector4)
RTTI_DEFINE_CURVEDATA(Red::HDRColor, HDRColor)
