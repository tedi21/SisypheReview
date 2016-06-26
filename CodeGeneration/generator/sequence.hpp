/**
 * @class sequence
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief Handles expressions of the form a << b where a and b are generators.</br>
          The expresssion returns a composite generator that generate a and b in sequence.
 */

#ifndef GEN_SEQUENCE_HPP
#define GEN_SEQUENCE_HPP

#include "generator.hpp"
#include "actor.hpp"

namespace gen {


    ///////////////////////////////////////////////////////////////////////////
    //
    //  sequence class
    //
    //      Handles expressions of the form:
    //
    //          a << b
    //
    //      where a and b are generators. The expression returns a composite
    //      generator that generate a and b in sequence. One (not both) of the
    //      operands may be a literal char, wchar_t or a primitive string
    //      char const*, wchar_t const*.
    //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename A, typename B>
    struct sequence : public binary<A, B, generator<sequence<A, B> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT2(A, B))

        typedef sequence<A, B>                  self_t;
        typedef binary_generator_category       generator_category_t;
        typedef binary<A, B, generator<self_t> > base_t;
    
        /** Constructor
         * @param a first generator
         * @param b second generator
         */
        sequence(A const& a, B const& b)
        : base_t(a, b) {}
    
        /** generate function, call the first and the second embedded generators.</br>
            the result of the second generator is concatened after the result of the first generator.
         * @param info contains information for generation and stores the result.
         */
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

    };
    
    /** operator function, constructs sequence generator class.
     * @param a the first generator.
     * @param b the second generator.
     * @return sequence generator class.
     */
    template <typename A, typename B>
    sequence<A, B>
    operator<<(generator<A> const& a, generator<B> const& b);

    /** operator function, constructs sequence generator class.
     * @param a the first generator.
     * @param b a character to append to the result.
     * @return sequence generator class.
     */
    template <typename A>
    sequence<A, chlit<char> >
    operator<<(generator<A> const& a, char b);

    /** operator function, constructs sequence generator class.
     * @param a a character to append to the result.
     * @param b the second generator.
     * @return sequence generator class.
     */
    template <typename B>
    sequence<chlit<char>, B>
    operator<<(char a, generator<B> const& b);

    /** operator function, constructs sequence generator class.
     * @param a the first generator.
     * @param b a characters string to append to the result.
     * @return sequence generator class.
     */
    template <typename A>
    sequence<A, strlit<char const*> >
    operator<<(generator<A> const& a, char const* b);

    /** operator function, constructs sequence generator class.
     * @param a a characters string to append to the result.
     * @param b the second generator.
     * @return sequence generator class.
     */
    template <typename B>
    sequence<strlit<char const*>, B>
    operator<<(char const* a, generator<B> const& b);

    /** operator function, constructs sequence generator class.
     * @param a the first generator.
     * @param b a wide character to append to the result.
     * @return sequence generator class.
     */    
    template <typename A>
    sequence<A, chlit<wchar_t> >
    operator<<(generator<A> const& a, wchar_t b);

    /** operator function, constructs sequence generator class.
     * @param a a wide character to append to the result.
     * @param b the second generator.
     * @return sequence generator class.
     */
    template <typename B>
    sequence<chlit<wchar_t>, B>
    operator<<(wchar_t a, generator<B> const& b);

    /** operator function, constructs sequence generator class.
     * @param a the first generator.
     * @param b a wide character string to append to the result.
     * @return sequence generator class.
     */      
    template <typename A>
    sequence<A, strlit<wchar_t const*> >
    operator<<(generator<A> const& a, wchar_t const* b);

    /** operator function, constructs sequence generator class.
     * @param a a wide characters string to append to the result.
     * @param b the second generator.
     * @return sequence generator class.
     */    
    template <typename B>
    sequence<strlit<wchar_t const*>, B>
    operator<<(wchar_t const* a, generator<B> const& b);

}
#include "impl/sequence_impl.hpp"
#endif
