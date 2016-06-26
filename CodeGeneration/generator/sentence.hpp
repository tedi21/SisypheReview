/**
 * @class sentence
 * @date 20/01/2008
 * @author Teddy DIDÉ
 * @version  1.0
 * @brief Handles expressions of the form a < b where a and b are generators.</br>
          The expresssion returns a composite generator that generate a and b in sequence separated by space.
 */

#ifndef GEN_SENTENCE_HPP
#define GEN_SENTENCE_HPP

#include "generator.hpp"
#include "actor.hpp"

namespace gen {


    ///////////////////////////////////////////////////////////////////////////
    //
    //  sentence class
    //
    //      Handles expressions of the form:
    //
    //          a < b
    //
    //      where a and b are generators. The sentence returns a composite
    //      generator that generate a and b in sequence separated by space.
    //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename A, typename B>
    struct sentence : public binary<A, B, generator<sentence<A, B> > >
    {
        DECLARE_CONTEXT(TYPE_GENERATOR_CONTEXT2(A, B))

        typedef sentence<A, B>                   self_t;
        typedef binary_generator_category        generator_category_t;
        typedef binary<A, B, generator<self_t> > base_t;
    
        /** Constructor
         * @param a first generator
         * @param b second generator
         */
        sentence(A const& a, B const& b)
        : base_t(a, b) {}
    
        /** generate function, call the first and the second embedded generators.</br>
            the result of the second generator is concatened after the result of the first generator
            separated by a space.
         * @param info contains information for generation and stores the result.
         */
        template <typename DataT>
        void
        generate(TYPE_CONTEXT(DataT) & context) const;

    };
    
    /** operator function, constructs sentence generator class.
     * @param a the first generator.
     * @param b the second generator.
     * @return sentence generator class.
     */
    template <typename A, typename B>
    sentence<A, B>
    operator<(generator<A> const& a, generator<B> const& b);

    /** operator function, constructs sentence generator class.
     * @param a the first generator.
     * @param b a character to append to the result.
     * @return sentence generator class.
     */
    template <typename A>
    sentence<A, chlit<char> >
    operator<(generator<A> const& a, char b);

    /** operator function, constructs sentence generator class.
     * @param a a character to append to the result.
     * @param b the second generator.
     * @return sentence generator class.
     */
    template <typename B>
    sentence<chlit<char>, B>
    operator<(char a, generator<B> const& b);

    /** operator function, constructs sentence generator class.
     * @param a the first generator.
     * @param b a characters string to append to the result.
     * @return sentence generator class.
     */
    template <typename A>
    sentence<A, strlit<char const*> >
    operator<(generator<A> const& a, char const* b);

    /** operator function, constructs sentence generator class.
     * @param a a characters string to append to the result.
     * @param b the second generator.
     * @return sentence generator class.
     */
    template <typename B>
    sentence<strlit<char const*>, B>
    operator<(char const* a, generator<B> const& b);

    /** operator function, constructs sentence generator class.
     * @param a the first generator.
     * @param b a wide character to append to the result.
     * @return sentence generator class.
     */    
    template <typename A>
    sentence<A, chlit<wchar_t> >
    operator<(generator<A> const& a, wchar_t b);

    /** operator function, constructs sentence generator class.
     * @param a a wide character to append to the result.
     * @param b the second generator.
     * @return sentence generator class.
     */
    template <typename B>
    sentence<chlit<wchar_t>, B>
    operator<(wchar_t a, generator<B> const& b);

    /** operator function, constructs sentence generator class.
     * @param a the first generator.
     * @param b a wide character string to append to the result.
     * @return sentence generator class.
     */      
    template <typename A>
    sentence<A, strlit<wchar_t const*> >
    operator<(generator<A> const& a, wchar_t const* b);

    /** operator function, constructs sentence generator class.
     * @param a a wide characters string to append to the result.
     * @param b the second generator.
     * @return sentence generator class.
     */    
    template <typename B>
    sentence<strlit<wchar_t const*>, B>
    operator<(wchar_t const* a, generator<B> const& b);

}
#include "impl/sentence_impl.hpp"
#endif
