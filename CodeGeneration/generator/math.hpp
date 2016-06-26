/**
 * @class math
 * @date 22/12/2011
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief 
 */

#ifndef GEN_MATH_HPP
#define GEN_MATH_HPP

#include "generator.hpp"

namespace gen {

    struct plus
    {
        template <typename T>
        T
        operator()(T value1, T value2) const
        {
            return value1+value2;
        }
    };

    struct minus
    {
        template <typename T>
        T
        operator()(T value1, T value2) const
        {
            return value1-value2;
        }
    };

    struct multiply
    {
        template <typename T>
        T
        operator()(T value1, T value2) const
        {
            return value1*value2;
        }
    };

    struct divide
    {
        template <typename T>
        T
        operator()(T value1, T value2) const
        {
            return value1/value2;
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  number class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename T, typename DerivedT>
    struct number
    {
        typedef number<T,DerivedT>  self_t;
        typedef DerivedT            derived_t;
        typedef DerivedT            embed_t;
        typedef T                   type_t;        

        number()
        {}

        DerivedT& derived()
        {
            return *static_cast<DerivedT*>(this);
        }

        DerivedT const& derived() const
        {
            return *static_cast<DerivedT const*>(this);
        }
    };

    template <typename A, typename B>
    struct number_compatibility
    {
        typedef typename boost::mpl::if_c< (sizeof(typename A::type_t) > sizeof(typename B::type_t)),
                        typename A::type_t,
                        typename B::type_t >::type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  constant class
    //
    //      Handles expressions of the form:
    //
    //          123
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename T>
    class constant 
    : public number<T,constant<T> >
    {
    public:
        DECLARE_EMPTY_CONTEXT()
        typedef constant<T> self_t;
        typedef T           type_t;

        constant(type_t value)
        : m_value(value)
        {}
    
        template <typename DataT>
        type_t
        calculate(TYPE_CONTEXT(DataT) & context) const;

    private:
        type_t m_value;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  operation class
    //
    //      Handles expressions of the form:
    //
    //          a + b
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename A, typename B, class OperatorT>
    class operation 
    : public binary<A,B,number<
        typename number_compatibility<A,B>::type,
        operation<A,B,OperatorT> > >
    {
    public:
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT2(A, B))
        typedef operation<A,B,OperatorT> self_t;
        typedef typename number_compatibility<A,B>::type type_t;
        typedef binary<A,B,number<type_t,self_t> > base_t;

        operation(A const& a, B const& b, OperatorT const& op)
        : base_t(a, b),
          m_op(op)
        {}
    
        template <typename DataT>
        type_t
        calculate(TYPE_CONTEXT(DataT) & context) const;

    private:
        OperatorT m_op;
    };

    template <typename T, typename A, typename B>
    operation<A,B,plus>
    operator+(number<T,A> const& a, number<T,B> const& b);

    template <typename T, typename A, typename B>
    operation<A,B,minus>
    operator-(number<T,A> const& a, number<T,B> const& b);

    template <typename T, typename A, typename B>
    operation<A,B,multiply>
    operator*(number<T,A> const& a, number<T,B> const& b);

    template <typename T, typename A, typename B>
    operation<A,B,divide>
    operator/(number<T,A> const& a, number<T,B> const& b);

    template <typename T, typename A>
    operation<constant<T>,A,minus>
    operator-(number<T,A> const& a);

    template <typename T, typename B>
    operation<constant<T>,B,plus>
    operator+(T a, number<T,B> const& b);

    template <typename T, typename B>
    operation<constant<T>,B,minus>
    operator-(T a, number<T,B> const& b);

    template <typename T, typename B>
    operation<constant<T>,B,multiply>
    operator*(T a, number<T,B> const& b);

    template <typename T, typename B>
    operation<constant<T>,B,divide>
    operator/(T a, number<T,B> const& b);

    template <typename T, typename A>
    operation<A,constant<T>,plus>
    operator+(number<T,A> const& a, T b);

    template <typename T, typename A>
    operation<A,constant<T>,minus>
    operator-(number<T,A> const& a, T b);

    template <typename T, typename A>
    operation<A,constant<T>,multiply>
    operator*(number<T,A> const& a, T b);

    template <typename T, typename A>
    operation<A,constant<T>,divide>
    operator/(number<T,A> const& a, T b);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  cast class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename T, typename S>
    struct cast 
    : public unary<S, number<T,cast<T,S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))
        typedef cast<T,S>  self_t;
        typedef T          type_t;
        typedef unary<S, number<type_t,self_t> > base_t;

        cast(S const& value)
        : base_t(value)
        {}
    
        template <typename DataT>
        type_t
        calculate(TYPE_CONTEXT(DataT) & context) const;
    };

    //////////////////////////////////
    template<typename T, typename S>
    cast<T,S>
    cast_g(generator<S> const& a);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  math class
    //
    ///////////////////////////////////////////////////////////////////////////

    template <typename S>
    struct math
    : public unary<S, generator<math<S> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT(S))
        typedef math<S>                     self_t;
        typedef plain_generator_category    generator_category_t;
        typedef unary<S, generator<self_t> > base_t;
    
        math(S const& a)
        : base_t(a) {}

        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;
    };

    //////////////////////////////////
    template <typename T, typename S>
    math<S>
    math_g(number<T,S> const& value);

}

#include "impl/math_impl.hpp"

#endif
