
NAMESPACE_BEGIN(interp)

template <class EncodingT>
bool equal_symbol(typename EncodingT::string_t::const_iterator first1,
                  typename EncodingT::string_t::const_iterator last1,
                  typename EncodingT::string_t const& buf)
{
    typename EncodingT::string_t::const_iterator first2 = buf.begin();
    typename EncodingT::string_t::const_iterator last2 = buf.end();
    bool eq = ((last1-first1) == (last2-first2));
    while (first1!=last1 && first2!=last2 && eq)
    {
        eq = (*first1 == *first2);
        first1++; first2++;
    }
    return eq;
}

template <class EncodingT>
typename EncodingT::string_t::const_iterator find_symbol(typename EncodingT::string_t::const_iterator start,
                                                         typename EncodingT::string_t::const_iterator end,
                                                         typename EncodingT::string_t const& buf)
{
    return std::search(start, end, buf.begin(), buf.end());
}

template <class EncodingT>
typename EncodingT::string_t::const_iterator rfind_symbol(typename EncodingT::string_t::const_iterator start,
                                                          typename EncodingT::string_t::const_iterator end,
                                                          typename EncodingT::string_t const& buf)
{
    return std::find_end(start, end, buf.begin(), buf.end());
}

template <class EncodingT>
typename EncodingT::string_t::const_iterator next_space(typename EncodingT::string_t::const_iterator start,
                                                        typename EncodingT::string_t::const_iterator end)
{
     while (start<end && !isspace_(*start))
     {
           ++start;
     }
     return start;
}

template <class EncodingT>
typename EncodingT::string_t::const_iterator next_word(typename EncodingT::string_t::const_iterator start,
                                                       typename EncodingT::string_t::const_iterator end)
{
     while (start<end && isspace_(*start))
     {
           ++start;
     }
     return start;
}

template <class EncodingT>
typename EncodingT::string_t::const_iterator previous_space(typename EncodingT::string_t::const_iterator start,
                                                            typename EncodingT::string_t::const_iterator end)
{
     while (end>start && isspace_(*(end-1)))
     {
           --end;
     }
     return end;
}

template <class EncodingT>
typename EncodingT::string_t::const_iterator previous_word(typename EncodingT::string_t::const_iterator start,
                                                           typename EncodingT::string_t::const_iterator end)
{
     while (end>start && !isspace_(*(end-1)))
     {
           --end;
     }
     return end;
}

template <class EncodingT>
bool is_identifier(typename EncodingT::string_t const& identifier)
{
     typename EncodingT::string_t::const_iterator i = identifier.begin();
     while (i<identifier.end() && 
            (((isalnum_(*i) || *i == '_') && i>identifier.begin()) ||
             ((isalpha_(*i) || *i == '_') && i==identifier.begin())))
     {
           ++i;
     }
     return i==identifier.end() && 
            !identifier.empty() && 
            identifier != UCS("true")  &&
            identifier != UCS("false") &&
            identifier != UCS("null")  &&
            identifier != UCS("CrLf")  &&
            identifier != UCS("Cr")    &&
            identifier != UCS("Lf")    &&
            identifier != UCS("Tab")   &&
            identifier != UCS("DblQuotes");
}

template <class EncodingT>
bool is_space(typename EncodingT::string_t const& buf, size_t i)
{
    return i < 0 || i >= buf.size() || isspace_(buf[i]);
}

template <class EncodingT>
typename EncodingT::string_t eat_space_before(typename EncodingT::string_t const& buf)
{
     typename EncodingT::string_t::const_iterator i = next_word<EncodingT>(buf.begin(), buf.end());
     return typename EncodingT::string_t(i,buf.end());   
}

template <class EncodingT>
typename EncodingT::string_t eat_space_after(typename EncodingT::string_t const& buf)
{
     typename EncodingT::string_t::const_iterator j = previous_space<EncodingT>(buf.begin(), buf.end());
     return typename EncodingT::string_t(buf.begin(),j); 
}

template <class EncodingT>
typename EncodingT::string_t eat_space(typename EncodingT::string_t const& buf)
{
    typename EncodingT::string_t tmp = eat_space_before<EncodingT>(buf);
    return eat_space_after<EncodingT>(tmp);
}

template <class EncodingT>
inline bool always_true(typename EncodingT::string_t const&, size_t)
{
    return true;
}

template <class EncodingT, class PredicateT>
void tuple_op_if( typename EncodingT::string_t const& buf,
                  typename EncodingT::string_t const& op,
                  std::vector<typename EncodingT::string_t> & tab,
                  PredicateT pred,
                  bool space)
{
    typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
    typename EncodingT::string_t val;
    size_t npos = EncodingT::string_t::npos;
    size_t first = 0, last = 0, pos = 0;

    tab.clear();
    pred(expr, -1);
    while ((last = expr.find(op, pos))!=npos)
    {
        if (pred(expr, last))
        {
            // search spaces before and after separator
            if ((!space || (is_space<EncodingT>(expr, last-1) && is_space<EncodingT>(expr, last+op.size()))))
            {
                val = expr.substr(first, last-first);
                tab.push_back(eat_space<EncodingT>(val));
            }
            first = last + op.size();
        }
        pos = last + op.size();
    }
    // add last element
    val = expr.substr(first, expr.size()-first);
    tab.push_back(eat_space<EncodingT>(val));
}

template <class EncodingT>
void tuple_op( typename EncodingT::string_t const& buf,
               typename EncodingT::string_t const& op,
               std::vector<typename EncodingT::string_t> & tab,
               bool space)
{
    tuple_op_if<EncodingT>(buf, op, tab, always_true<EncodingT>, space);
}

template <class EncodingT>
bool hyphenation(typename EncodingT::string_t const& buf, 
                 typename EncodingT::string_t const& op,
                 typename EncodingT::string_t & left,
                 typename EncodingT::string_t & right,
                 size_t & start,
                 bool space)
{
    typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
    size_t npos = EncodingT::string_t::npos;

    // search spaces before and after separator
    while ((start = expr.find(op, start))!=npos &&
           (space && (!is_space<EncodingT>(expr,start-1) || !is_space<EncodingT>(expr,start+op.size()))))
    {
        start = start + op.size();
    }

    bool success =  start != 0                      &&  // no left expression
                    start != expr.size()-op.size()  &&  // no right expresssion
                    start != npos;                      // not found
    if (success)
    {
        left.assign(expr.begin(), expr.begin()+start);
        left = eat_space<EncodingT>(left);
        start += op.size();
        right.assign(expr.begin()+start,expr.end());
        right = eat_space<EncodingT>(right);
    }
    else
    {
        if (start != npos)
        {
            start += op.size();
        }
    }
    return success;
}

template <class EncodingT>
bool hyphenation(typename EncodingT::string_t const& buf,
                 typename EncodingT::string_t const& op,
                 typename EncodingT::string_t & left,
                 typename EncodingT::string_t & right,
                 bool space)
{
    size_t i = 0;
    return hyphenation<EncodingT>(buf, op, left, right, i, space);
}

template <class EncodingT>
bool reverse_hyphenation(typename EncodingT::string_t const& buf,
                         typename EncodingT::string_t const& op,
                         typename EncodingT::string_t & left,
                         typename EncodingT::string_t & right,
                         size_t & start,
						 bool space)
{
    typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
    size_t npos = EncodingT::string_t::npos;

    // search spaces before and after separator
    while ((start = expr.rfind(op, start))!=npos &&
           (space && (!is_space<EncodingT>(expr,start-1) || !is_space<EncodingT>(expr,start+op.size()))))
    {}

    bool success =  start != 0                      &&  // no left expression
                    start != expr.size()-op.size()  &&  // no right expresssion
                    start != npos;                      // not found
    if (success)
    {
        left.assign(expr.begin(), expr.begin()+start);
        left = eat_space<EncodingT>(left);
        right.assign(expr.begin()+start+op.size(),expr.end());
        right = eat_space<EncodingT>(right);
    }
    if (start != npos)
    {
        start -= 1;
    }
    return success;
}

template <class EncodingT>
bool reverse_hyphenation(typename EncodingT::string_t const& buf,
                         typename EncodingT::string_t const& op,
                         typename EncodingT::string_t & left,
                         typename EncodingT::string_t & right,
                         bool space)
{
    size_t i = EncodingT::string_t::npos;
    return reverse_hyphenation<EncodingT>(buf, op, left, right, i, space);
}

template <class EncodingT>
bool prefix  (typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& sym, 
              typename EncodingT::string_t & right,
              bool space)
{
    typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
    bool success = (expr.compare(0, sym.size(), sym) == 0) &&
                   (!space || is_space<EncodingT>(expr, sym.size()));
    if (success)
    {
        right.assign(expr.begin()+sym.size(),expr.end());
        right = eat_space_before<EncodingT>(right);
    }
    return success;
}

template <class EncodingT>
bool suffix  (typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& sym, 
              typename EncodingT::string_t & left,
              bool space)
{
    typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
    bool success = (expr.size()>=sym.size()) &&
                   (expr.compare(expr.size()-sym.size(), sym.size(), sym) == 0) &&
                   (!space || is_space<EncodingT>(expr, expr.size()-sym.size()-1));
    if (success)
    {
        left.assign(expr.begin(),expr.end()-sym.size());
        left = eat_space_after<EncodingT>(left);
    }
    return success;
}

template <class EncodingT>
bool embrace(typename EncodingT::string_t const& buf, 
             typename EncodingT::string_t const& left, 
             typename EncodingT::string_t const& right, 
             typename EncodingT::string_t & inside,
             bool space)
{
    return prefix<EncodingT>(buf, left, inside, space) &&
           suffix<EncodingT>(inside, right, inside, space);
}

template <class EncodingT>
bool binary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               size_t & start)
{
    return hyphenation<EncodingT>(buf, op, left, right, start, false);
}

template <class EncodingT>
bool binary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right)
{
    return hyphenation<EncodingT>(buf, op, left, right, false);
}

template <class EncodingT>
bool rbinary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right,
               size_t & start)
{
    return reverse_hyphenation<EncodingT>(buf, op, left, right, start, false);
}

template <class EncodingT>
bool rbinary_op(typename EncodingT::string_t const& buf, 
               typename EncodingT::string_t const& op, 
               typename EncodingT::string_t & left,
               typename EncodingT::string_t & right)
{
    return reverse_hyphenation<EncodingT>(buf, op, left, right, false);
}

template <class EncodingT>
bool unary_op(typename EncodingT::string_t const& buf, 
              typename EncodingT::string_t const& op, 
              typename EncodingT::string_t & right)
{
    return prefix<EncodingT>(buf, op, right, false);
}

NAMESPACE_END
