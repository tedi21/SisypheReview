#ifndef _EQUALITY_HPP_
#define _EQUALITY_HPP_

#include "primitives_char.hpp"

struct EqualityOperator {
    template<class Elem1, class Elem2>
    bool operator()(Elem1 e1, Elem2 e2)
    {
        return (e1 == e2);
    }
};

template<class InputIterator1, class InputIterator2, class Predicate>
bool equal(InputIterator1 _First1, InputIterator1 _Last1,
           InputIterator2 _First2, InputIterator2 _Last2,
           Predicate _Pred = EqualityOperator() )
{
    bool eq = ((_Last1-_First1) == (_Last2-_First2));
    while (_First1!=_Last1 && _First2!=_Last2 && eq)
    {
        eq = _Pred(*_First1, *_First2);
        _First1++; _First2++;
    }
    return eq;
}

struct NoCase {
    template<class Elem1, class Elem2>
    bool operator()(Elem1 e1, Elem2 e2)
    {
        return (chr::tolower_(e1)==chr::tolower_(e2));
    }
};

template<class CharIterator1, class CharIterator2>
bool equalNoCase(CharIterator1 _First1, CharIterator2 _First2)
{
    return equal(_First1, chr::get_last(_First1),
                 _First2, chr::get_last(_First2), 
                 NoCase());
}

#endif  // _EQUALITY_HPP_