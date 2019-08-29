#ifndef __AUTO_ATTRIBUTE_H__
#define __AUTO_ATTRIBUTE_H__
#include <map>
using namespace std;

class AutoAttribute
{
public:
    AutoAttribute(): _addValueNo( 1 ), _addScaleNo( 1 ), _lastScale( 0 ),_baseValue(0) {}
    ~AutoAttribute() {}

    // 计算加成值（包含原始值）
    inline int ComputeAttributeWithBase() const
    {
        return ComputeAttributeWithoutBase() + _baseValue;
    }

    // 计算加成值（不包含原始值）
    inline int ComputeAttributeWithoutBase() const
    {
        int sumAttri = 0;
        map<int, double>::const_iterator scaleIt = _scale.begin();

        for ( ; scaleIt != _scale.end(); ++scaleIt )
        {
            sumAttri += _baseValue * scaleIt->second;
        }

        map<int, int>::const_iterator valueIt = _value.begin();

        for ( ; valueIt != _value.end(); ++valueIt )
        {
            sumAttri += valueIt->second;
        }

        return sumAttri;
    }

    // 计算加成值（不算value）
    inline int ComputerAttriButeWithoutValue( int originalAttri ) const
    {
        int sumAttri = 0;
        map<int, double>::const_iterator scaleIt = _scale.begin();

        for ( ; scaleIt != _scale.end(); ++scaleIt )
        {
            sumAttri += originalAttri * scaleIt->second;
        }

        return sumAttri;
    }

    // 添加值
    inline int AddValue( int value )
    {
        _value.insert( make_pair( _addValueNo, value ) );
        return _addValueNo++;
    }

    // 移除值
    inline void RemoveValue( int valueNo )
    {
        _value.erase( valueNo );
    }

    // 获取总值
    inline int GetTotalValue() const
    {
        int sumValue = 0;
        map<int, int>::const_iterator it = _value.begin();

        for ( ; it != _value.end(); ++it )
        {
            sumValue += it->second;
        }
        return sumValue;
    }

    // 添加比例
    inline int AddScale( double scale )
    {
        _lastScale = scale;
        _scale.insert( make_pair( _addScaleNo, scale ) );
        return _addScaleNo++;
    }

    // 移除比例
    inline void RemoveScale( int scaleNo )
    {
        _scale.erase( scaleNo );
    }

    // 获取总比例
    inline double GetTotalScale() const
    {
        if ( !_scale.size() )
        {
            return 0;
        }

        double sumScale = 1;
        map<int, double>::const_iterator it = _scale.begin();

        for ( ; it != _scale.end(); ++it )
        {
            sumScale *= it->second;
        }

        return sumScale;
    }
    // 获取比例数量
    inline size_t GetScaleSize() const
    {
        return _scale.size();
    }

    // 获取最近设置比例
    inline double GetLastScale() const
    {
        return _lastScale;
    }

    // 是否为空
    inline bool isEmpty() const
    {
        return !( _value.size() || _scale.size() );
    }

    int getValue(int valueNo)
    {
    	return _value[valueNo];
    }

    float getScale(int scaleNo)
    {
    	return _scale[scaleNo];
    }

    int32_t getBaseValue(){return _baseValue;};
    void setBaseValue(int32_t value){_baseValue = value;}
private:
    map<int, int> _value;
    map<int, double> _scale;
    int _addValueNo;
    double _addScaleNo;
    double _lastScale;
    int32_t _baseValue;
};

#endif
