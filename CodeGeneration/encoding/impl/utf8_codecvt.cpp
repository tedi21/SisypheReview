// for symbol export
#include "EncodingExport.hpp"

#define BOOST_UTF8_BEGIN_NAMESPACE \
     //namespace boost {
#define BOOST_UTF8_END_NAMESPACE //}
#define BOOST_UTF8_DECL             ENCODING_API

#include <boost/detail/utf8_codecvt_facet.ipp>


#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL
