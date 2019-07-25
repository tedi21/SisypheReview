#include "boost/lexical_cast.hpp"

namespace gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  constant class implementation
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename T>
    template <typename DataT>
    inline typename constant<T>::type_t
    constant<T>::calculate(TYPE_CONTEXT(DataT) & context) const
    {
        return m_value;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  operation class implementation
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename A, typename B, typename OperatorT>
    template <typename DataT>
    inline typename operation<A,B,OperatorT>::type_t
    operation<A,B,OperatorT>::calculate(TYPE_CONTEXT(DataT) & context) const
    {
        return m_op(this->left().template calculate<DataT>(context),
                    this->right().template calculate<DataT>(context));
    }

    template <typename T, typename A, typename B>
    inline operation<A,B,plus>
    operator+(number<T,A> const& a, number<T,B> const& b)
    {
        return operation<A,B,plus>(a.derived(), b.derived(), plus());
    }

    template <typename T, typename A, typename B>
    inline operation<A,B,minus>
    operator-(number<T,A> const& a, number<T,B> const& b)
    {
        return operation<A,B,minus>(a.derived(), b.derived(), minus());
    }

    template <typename T, typename A, typename B>
    inline operation<A,B,multiply>
    operator*(number<T,A> const& a, number<T,B> const& b)
    {
        return operation<A,B,multiply>(a.derived(), b.derived(), multiply());
    }

    template <typename T, typename A, typename B>
    inline operation<A,B,divide>
    operator/(number<T,A> const& a, number<T,B> const& b)
    {
        return operation<A,B,divide>(a.derived(), b.derived(), divide());
    }

    template <typename T, typename A>
    inline operation<constant<T>,A,minus>
    operator-(number<T,A> const& a)
    {
        return operation<constant<T>,A,minus>(constant<T>(0), a.derived(), minus());
    }

    template <typename T, typename B>
    inline operation<constant<T>,B,plus>
    operator+(T a, number<T,B> const& b)
    {
        return operation<constant<T>,B,plus>(constant<T>(a), b.derived(), plus());
    }

    template <typename T, typename B>
    inline operation<constant<T>,B,minus>
    operator-(T a, number<T,B> const& b)
    {
        return operation<constant<T>,B,minus>(constant<T>(a), b.derived(), minus());
    }

    template <typename T, typename B>
    inline operation<constant<T>,B,multiply>
    operator*(T a, number<T,B> const& b)
    {
        return operation<constant<T>,B,multiply>(constant<T>(a), b.derived(), multiply());
    }

    template <typename T, typename B>
    inline operation<constant<T>,B,divide>
    operator/(T a, number<T,B> const& b)
    {
        return operation<constant<T>,B,divide>(constant<T>(a), b.derived(), divide());
    }

    template <typename T, typename A>
    inline operation<A,constant<T>,plus>
    operator+(number<T,A> const& a, T b)
    {
        return operation<A,constant<T>,plus>(a.derived(), constant<T>(b), plus());
    }

    template <typename T, typename A>
    inline operation<A,constant<T>,minus>
    operator-(number<T,A> const& a, T b)
    {
        return operation<A,constant<T>,minus>(a.derived(), constant<T>(b), minus());
    }

    template <typename T, typename A>
    inline operation<A,constant<T>,multiply>
    operator*(number<T,A> const& a, T b)
    {
        return operation<A,constant<T>,multiply>(a.derived(), constant<T>(b), multiply());
    }

    template <typename T, typename A>
    inline operation<A,constant<T>,divide>
    operator/(number<T,A> const& a, T b)
    {
        return operation<A,constant<T>,divide>(a.derived(), constant<T>(b), divide());
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  cast class implementation
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename T, typename S>
    template <typename DataT>
    inline typename cast<T,S>::type_t
    cast<T,S>::calculate(TYPE_CONTEXT(DataT) & context) const
    {
        size_t l = context.length();
        this->subject().template generate<DataT>(context);
        return boost::lexical_cast<type_t>(
            context.subtract(l, -1, true) );
    }

    template<typename T, typename S>
    inline cast<T,S>
    cast_g(generator<S> const& a)
    {
        return cast<T,S>(a.derived());
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  math class implementation
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename S>
    template <typename DataT>
    inline void
    math<S>::generate(TYPE_CONTEXT(DataT) & context) const
    {
        context.append(
            boost::lexical_cast<TYPE_CONTEXT(DataT)::str_t>(
                this->subject().template calculate<DataT>(context) ));
    }

    template <typename T, typename S>
    inline math<S>
    math_g(number<T,S> const& value)
    {
        return math<S>(value.derived());
    }

}
