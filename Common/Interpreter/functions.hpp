#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

#include "config.hpp"
#include "primitives_char.hpp"
#include "encoding.hpp"
#include <algorithm>

using namespace chr;
using namespace enc;

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
bool equal_symbol(typename EncodingT::string_t::const_iterator first1,
                  typename EncodingT::string_t::const_iterator last1,
                  typename EncodingT::string_t const& buf);

template <class EncodingT>
typename EncodingT::string_t::const_iterator find_symbol(typename EncodingT::string_t::const_iterator start,
                                                         typename EncodingT::string_t::const_iterator end,
                                                         typename EncodingT::string_t const& buf);

template <class EncodingT>
typename EncodingT::string_t::const_iterator rfind_symbol(typename EncodingT::string_t::const_iterator start,
                                                         typename EncodingT::string_t::const_iterator end,
                                                         typename EncodingT::string_t const& buf);

template <class EncodingT>
typename EncodingT::string_t::const_iterator next_space(typename EncodingT::string_t::const_iterator start,
                                                        typename EncodingT::string_t::const_iterator end);

template <class EncodingT>
typename EncodingT::string_t::const_iterator next_word(typename EncodingT::string_t::const_iterator start,
                                                       typename EncodingT::string_t::const_iterator end);

template <class EncodingT>
typename EncodingT::string_t::const_iterator previous_space(typename EncodingT::string_t::const_iterator start,
                                                            typename EncodingT::string_t::const_iterator end);

template <class EncodingT>
typename EncodingT::string_t::const_iterator previous_word(typename EncodingT::string_t::const_iterator start,
                                                           typename EncodingT::string_t::const_iterator end);

template <class EncodingT>
bool is_identifier(typename EncodingT::string_t const& identifier);

template <class EncodingT>
bool is_space(typename EncodingT::string_t const& buf, size_t i);

template <class EncodingT>
typename EncodingT::string_t eat_space_before(typename EncodingT::string_t const& buf);

template <class EncodingT>
typename EncodingT::string_t eat_space_after(typename EncodingT::string_t const& buf);

template <class EncodingT>
typename EncodingT::string_t eat_space(typename EncodingT::string_t const& buf);

template <class EncodingT>
void tuple_op(typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& op, 
              std::vector<typename EncodingT::string_t> & tab,
              bool is_word = false);

template <class EncodingT>
bool hyphenation(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               size_t & start,
               bool is_word = false);

template <class EncodingT>
bool hyphenation(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               bool is_word = false);

template <class EncodingT>
bool reverse_hyphenation(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               size_t & start,
               bool is_word = false);

template <class EncodingT>
bool reverse_hyphenation(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               bool is_word = false);

template <class EncodingT>
bool prefix  (typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& sym, 
              typename EncodingT::string_t & right,
              bool is_word = false);

template <class EncodingT>
bool suffix  (typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& sym, 
              typename EncodingT::string_t & left,
              bool is_word = false);

template <class EncodingT>
bool embrace(typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& left, 
              typename EncodingT::string_t const& right, 
              typename EncodingT::string_t & inside,
              bool is_word = false);

template <class EncodingT>
bool binary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               size_t & start);

template <class EncodingT>
bool rbinary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right);

template <class EncodingT>
bool rbinary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               size_t & start);

template <class EncodingT>
bool binary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right);

template <class EncodingT>
bool unary_op(typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& op, 
              typename EncodingT::string_t & right);

NAMESPACE_END

#include "Functions_impl.hpp"

#undef C
#undef A

#endif
