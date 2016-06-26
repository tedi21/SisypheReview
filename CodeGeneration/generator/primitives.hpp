/**
 * primitives
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 */

#ifndef GEN_PRIMITIVES_HPP
#define GEN_PRIMITIVES_HPP

#include <boost/call_traits.hpp>
#include <boost/compressed_pair.hpp>

namespace gen {

    /**
     * @class unary class
     * @date 20/01/2008
     * @author Teddy DIDÉ
     * @version  1.0
     * @brief Composite class composed of a single subject.
     */
    ///////////////////////////////////////////////////////////////////////////
    //
    //  unary class.
    //
    //      Composite class composed of a single subject. This template class
    //      is parameterized by the subject type S and a base class to
    //      inherit from, BaseT. The unary class is meant to be a base class
    //      to inherit from. The inheritance structure, given the BaseT
    //      template parameter places the unary class in the middle of a
    //      linear, single parent hierarchy. For instance, given a class S
    //      and a base class B, a class D can derive from unary:
    //
    //          struct D : public unary<S, B> {...};
    //
    //      The inheritance structure is thus:
    //
    //            B
    //            |
    //          unary (has S)
    //            |
    //            D
    //
    //      The subject can be accessed from the derived class D as:
    //      this->subject();
    //
    //      Typically, the subject S is specified as typename S::embed_t.
    //      embed_t specifies how the subject is embedded in the composite
    //      (See generator.hpp for details).
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename S, typename BaseT>
    class unary : public BaseT
    {
    public:

        typedef BaseT                                           base_t;
        typedef typename boost::call_traits<S>::param_type      param_t;
        typedef typename boost::call_traits<S>::const_reference return_t;
        typedef S                                               subject_t;
        typedef typename S::embed_t                             subject_embed_t;

        /** Constructor
         * @param subj_ a generator
         */
        unary(param_t subj_)
        : base_t(), subj(subj_) {}

        /** Constructor
         * @param base base generator
         * @param subj_ embedded generator
         */
        unary(BaseT const& base, param_t subj_)
        : base_t(base), subj(subj_) {}

        /** return the embedded generator
         * @return the embedded generator
         */
        return_t
        subject() const
        { return subj; }

    private:

        subject_embed_t subj;
    };

    /**
     * @class binary class
     * @date 20/01/2008
     * @author Teddy DIDÉ
     * @version  1.0
     * @brief Composite class composed of a pair (left and right).
     */
    ///////////////////////////////////////////////////////////////////////////
    //
    //  binary class.
    //
    //      Composite class composed of a pair (left and right). This
    //      template class is parameterized by the left and right subject
    //      types A and B and a base class to inherit from, BaseT. The binary
    //      class is meant to be a base class to inherit from. The
    //      inheritance structure, given the BaseT template parameter places
    //      the binary class in the middle of a linear, single parent
    //      hierarchy. For instance, given classes X and Y and a base class
    //      B, a class D can derive from binary:
    //
    //          struct D : public binary<X, Y, B> {...};
    //
    //      The inheritance structure is thus:
    //
    //            B
    //            |
    //          binary (has X and Y)
    //            |
    //            D
    //
    //      The left and right subjects can be accessed from the derived
    //      class D as: this->left(); and this->right();
    //
    //      Typically, the pairs X and Y are specified as typename X::embed_t
    //      and typename Y::embed_t. embed_t specifies how the subject is
    //      embedded in the composite (See parser.hpp for details).
    //
    ///////////////////////////////////////////////////////////////////////////////
    template <typename A, typename B, typename BaseT>
    class binary : public BaseT
    {
    public:

        typedef BaseT                                           base_t;
        typedef typename boost::call_traits<A>::param_type      left_param_t;
        typedef typename boost::call_traits<A>::const_reference left_return_t;
        typedef typename boost::call_traits<B>::param_type      right_param_t;
        typedef typename boost::call_traits<B>::const_reference right_return_t;
        typedef A                                               left_t;
        typedef typename A::embed_t                             left_embed_t;
        typedef B                                               right_t;
        typedef typename B::embed_t                             right_embed_t;

        /** Constructor
         * @param a the first generator
          * @param b the second generator
         */
        binary(left_param_t a, right_param_t b)
        : base_t(), subj(a, b) {}

        /** return the first embedded generator
         * @return the first embedded generator
         */
        left_return_t
        left() const
        { return subj.first(); }

        /** return the second embedded generator
         * @return the second embedded generator
         */
        right_return_t
        right() const
        { return subj.second(); }

    private:

        boost::compressed_pair<left_embed_t, right_embed_t> subj;
    };


}

#endif
