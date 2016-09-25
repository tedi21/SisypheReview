#include "utf8_codecvt.hpp"
#include "utf16BE_codecvt.hpp"
#include "utf16LE_codecvt.hpp"
#include "iso_8859_15_codecvt.hpp"
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost::archive::iterators;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    void File<EncodingT>::construct(const typename EncodingT::string_t& name, const typename EncodingT::string_t& mode, const typename EncodingT::string_t& format)
    {
        m_name   = name;
        m_mode   = mode;
        m_format = format;

        ios_base::openmode mde;
        if (m_mode == C("APPEND"))
        {
            mde = ios::app;
        }
        else if(m_mode == C("OVERWRITE"))
        {
            mde = ios::trunc;
        }
        else if(m_mode == C("NONE"))
        {
            mde = (ios_base::openmode) 0;
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "mode unknown : " << A(m_mode) << ".";
        }

        if (m_format != C("ANSI") && m_format != C("BASE64"))
        {
            std::locale old_locale;
            std::codecvt<wchar_t, char, std::mbstate_t>* codecvt_facet = NULL;
            if (m_format == C("UTF16-LE"))
            {
                codecvt_facet = new utf16LE_codecvt_facet;
            }
            else if(m_format == C("UTF16-BE"))
            {
                codecvt_facet = new utf16BE_codecvt_facet;
            }
            else if(m_format == C("UTF8"))
            {
                codecvt_facet = new utf8_codecvt_facet;
            }
            else if(m_format == C("ISO-8859-15"))
            {
                codecvt_facet = new iso_8859_15_codecvt_facet;
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Format unknown : " << A(m_format) << ".";
            }
            std::locale new_locale(old_locale,codecvt_facet);
            m_stream.imbue(new_locale);
        }

        m_stream.open(A(m_name).c_str(), ios::binary|ios::in|ios::out|mde);
        String<EncodingT>::setValue(m_name);
    }

    template <class EncodingT>
    File<EncodingT>::File()
    {}

    template <class EncodingT>
    File<EncodingT>::File(const typename EncodingT::string_t& name, const typename EncodingT::string_t& mode, const typename EncodingT::string_t& format)
    {
        construct(name, mode, format);
    }

    template <class EncodingT>
    File<EncodingT>::File(boost::shared_ptr< Base<EncodingT> > const& name, boost::shared_ptr< Base<EncodingT> > const& mode, boost::shared_ptr< Base<EncodingT> > const& format)
    {
        typename EncodingT::string_t nativeName, nativeMode, nativeFormat;
        if (check_string<EncodingT>(name, nativeName) && check_string<EncodingT>(mode, nativeMode) && check_string<EncodingT>(format, nativeFormat))
        {
            construct(nativeName, nativeMode, nativeFormat);
        }
    }

    template <class EncodingT>
    File<EncodingT>::~File()
    {
        if (m_stream.is_open())
        {
            m_stream.close();
        }
    }

    template <class EncodingT>
    typename EncodingT::string_t File<EncodingT>::toString() const
    {
        return m_name;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new File<EncodingT>(m_name, m_mode, m_format));
    }

    template <class EncodingT>
    typename EncodingT::string_t File<EncodingT>::getClassName() const
    {
        return C("File");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("File"), method, args, ret) ||
                tryInvoke(this, C("String"), method, args, ret))
            {
                find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
                for (size_t i = 0; i < params.size(); ++i)
                {
                    find_parameter(ret, i, params[i]);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in File, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::isOpen() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_stream.is_open()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::load(boost::shared_ptr< Base<EncodingT> >& val)
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t text;

        if (m_stream.is_open())
        {
            scoped_array<wchar_t> buffer;
            int start = 0, length = 0;
            // get length of file:
            m_stream.seekg (0, ios::end);
            length = m_stream.tellg();
            m_stream.seekg (0, ios::beg);

            // allocate memory: exact(latin-1) or larger than necessary(Unicode)
            buffer.reset( new wchar_t[length+1] );
            memset(buffer.get(), 0, (length+1)*sizeof(wchar_t));

            // read data as a block:
            m_stream.read(buffer.get(), length);
		
			if (m_format == C("BASE64"))
			{
				typedef 
                    base64_from_binary<
                       transform_width<
                            wchar_t *,
							6,
							8
						>
					> 
					base64_text;
				// Convert to Base64
				text.assign(base64_text(buffer.get()), base64_text(buffer.get() + length));
			}
			else
			{
				if (m_format == C("UTF16-LE") ||
					m_format == C("UTF16-BE"))
				{
					start = 1;
				}
			
				text = buffer.get() + start;
			}
            val.reset(new String<EncodingT>(text));
            res.reset(new Bool<EncodingT>(true));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::save(boost::shared_ptr< Base<EncodingT> > const& val)
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t text;
        if (check_string<EncodingT>(val, text))
        {
            if (m_stream.is_open())
            {
				vector<wchar_t> buffer;
				if (m_format == C("BASE64"))
				{
					typedef
                        transform_width<
                            binary_from_base64<
                                typename EncodingT::string_t::const_iterator
								>, 
							8, 
							6
						> 
						binary_text;
					buffer.assign(binary_text(text.begin()), binary_text(text.end()));
				}
				else
				{
					if (m_stream.tellg() == 0 &&
						(m_format == C("UTF16-LE") ||
						 m_format == C("UTF16-BE")))
					{
						m_stream << utf16_codecvt_facet<>::BOM;
					}
					buffer.assign(text.begin(), text.end());
				}
                m_stream.write(buffer.data(), (streamsize) buffer.size());
                res.reset(new Bool<EncodingT>(true));
            }
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::size()
    {
        boost::shared_ptr< Base<EncodingT> > res(new Numeric<EncodingT>(0));

        int length = 0;
        // get length of file:
        m_stream.seekg (0, ios::end);
        length = m_stream.tellg();
        m_stream.seekg (0, ios::beg);
        res.reset(new Numeric<EncodingT>(length));

        return res;
    }

NAMESPACE_END

#undef C
#undef A
