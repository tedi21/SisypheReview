#include "utf8_codecvt.hpp"
#include "utf16BE_codecvt.hpp"
#include "utf16LE_codecvt.hpp"
#include "iso_8859_15_codecvt.hpp"
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#define A(str) encode<EncodingT,ansi>(str)

using namespace boost::archive::iterators;

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    template <class CharT>
    File<EncodingT>::FileStream<CharT>::FileStream()
    {}

    template <class EncodingT>
    template <class CharT>
    File<EncodingT>::FileStream<CharT>::~FileStream()
    {
        if (m_fstream.is_open())
        {
            m_fstream.close();
        }
    }

    template <class EncodingT>
    template <class CharT>
    void File<EncodingT>::FileStream<CharT>::open(const typename EncodingT::string_t& name, std::ios_base::openmode mode)
    {
        m_fstream.open(A(name).c_str(), mode);
    }

    template <class EncodingT>
    template <class CharT>
    void File<EncodingT>::FileStream<CharT>::imbue(const std::locale& locale)
    {
        m_fstream.imbue(locale);
    }

    template <class EncodingT>
    template <class CharT>
    bool File<EncodingT>::FileStream<CharT>::is_open() const
    {
        return m_fstream.is_open();
    }

    template <class EncodingT>
    template <class CharT>
    void File<EncodingT>::FileStream<CharT>::close()
    {
        m_fstream.close();
    }

    template <class EncodingT>
    template <class CharT>
    int File<EncodingT>::FileStream<CharT>::tellg()
    {
        return m_fstream.tellg();
    }

    template <class EncodingT>
    template <class CharT>
    void File<EncodingT>::FileStream<CharT>::seekg(int off, std::ios_base::seekdir dir)
    {
        m_fstream.seekg(off, dir);
    }

    template <class EncodingT>
    template <class CharT>
    void File<EncodingT>::FileStream<CharT>::clear()
    {
        m_fstream.clear();
    }

    template <class EncodingT>
    template <class CharT>
    size_t File<EncodingT>::FileStream<CharT>::size_of_char()
    {
        return sizeof(CharT);
    }

    template <class EncodingT>
    template <class CharT>
    void File<EncodingT>::FileStream<CharT>::read(std::vector<uint8_t>& b)
    {
        m_fstream.read(reinterpret_cast<CharT*>(b.data()), static_cast<std::streamsize>(b.size() / sizeof(CharT)));
    }

    template <class EncodingT>
    template <class CharT>
    void File<EncodingT>::FileStream<CharT>::write(const std::vector<uint8_t>& b)
    {
        m_fstream.write(reinterpret_cast<const CharT*>(b.data()), static_cast<std::streamsize>(b.size() / sizeof(CharT)));
    }

    template <class EncodingT>
    void File<EncodingT>::construct(const typename EncodingT::string_t& name, const typename EncodingT::string_t& mode, const typename EncodingT::string_t& format)
    {
        m_name   = name;
        m_mode   = mode;
        m_format = format;
        if (m_format != UCS("BASE64"))
        {
            m_stream.reset(new FileStream<typename EncodingT::char_t>());
        }
        else
        {
            m_stream.reset(new FileStream<char>());
        }

        ios_base::openmode mde;
        if (m_mode == UCS("APPEND"))
        {
            mde = ios::app;
        }
        else if(m_mode == UCS("OVERWRITE"))
        {
            mde = ios::trunc;
        }
        else if(m_mode == UCS("NONE"))
        {
            mde = (ios_base::openmode) 0;
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "mode unknown : " << A(m_mode) << ".";
        }

        if (m_format != UCS("ANSI") && m_format != UCS("BASE64"))
        {
            std::locale old_locale;
            std::codecvt<typename EncodingT::char_t, char, std::mbstate_t>* codecvt_facet = NULL;
            if (m_format == UCS("UTF16-LE"))
            {
                codecvt_facet = new utf16LE_codecvt_facet;
            }
            else if(m_format == UCS("UTF16-BE"))
            {
                codecvt_facet = new utf16BE_codecvt_facet;
            }
            else if(m_format == UCS("UTF8"))
            {
                codecvt_facet = new utf8_codecvt_facet;
            }
            else if(m_format == UCS("ISO-8859-15"))
            {
                codecvt_facet = new iso_8859_15_codecvt_facet;
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Format unknown : " << A(m_format) << ".";
            }
            std::locale new_locale(old_locale,codecvt_facet);
            m_stream->imbue(new_locale);
        }

        m_stream->open(m_name, ios::binary|ios::in|ios::out|mde);
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
        if (m_stream != nullptr && m_stream->is_open())
        {
            m_stream->close();
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
        return UCS("File");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, UCS("File"), method, args, ret)   ||
                tryInvoke(this, UCS("Base"), method, args, ret))
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
        return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_stream->is_open()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::load(boost::shared_ptr< Base<EncodingT> >& val)
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        boost::shared_ptr< String<EncodingT> > valPtr  = dynamic_pointer_cast< String<EncodingT> >(val);
        typename EncodingT::string_t text;

        if (m_stream != nullptr && m_stream->is_open() && valPtr != nullptr)
        {
            std::vector<uint8_t> buffer;
            int start = 0, length = 0;
            // get length of file:
            m_stream->clear();
            m_stream->seekg (0, ios::end);
            length = m_stream->tellg();
            m_stream->seekg (0, ios::beg);

            // allocate memory
            buffer.resize(length * m_stream->size_of_char());
            
            // read data as a block:
            m_stream->read(buffer);
		
            if (m_format != UCS("BASE64"))
            {
                if (length > 0)
                {
                    if (0xFF == buffer[0] &&
                        0xFE == buffer[1] &&
                        (m_format == UCS("UTF16-LE") ||
                         m_format == UCS("UTF16-BE") ||
                         m_format == UCS("UTF8")))
                    {
                        start = sizeof(typename EncodingT::char_t);
                    }
                    typename EncodingT::char_t* begin = reinterpret_cast<typename EncodingT::char_t*>(buffer.data() + start);
                    typename EncodingT::char_t* end = reinterpret_cast<typename EncodingT::char_t*>(buffer.data() + buffer.size());
                    text.assign(begin, std::find(begin, end, '\0'));
                }
            }
            else
            {
                typedef 
                    base64_from_binary<
                       transform_width<
                            std::vector<uint8_t>::const_iterator,
                            6,
                            8
                        >
                    > 
                    base64_text;
                // Convert to Base64
                text.assign(base64_text(buffer.begin()), base64_text(buffer.end()));
            }
            valPtr->value(text);
            res->value(true);
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::save(boost::shared_ptr< Base<EncodingT> > const& val)
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t text;
        if (check_string<EncodingT>(val, text))
        {
            if (m_stream != nullptr && m_stream->is_open())
            {
                std::vector<uint8_t> buffer;
                if (m_format != UCS("BASE64"))
                {
                    if (m_stream->tellg() == 0)
                    {
                        if (m_format == UCS("UTF16-LE") ||
                            m_format == UCS("UTF16-BE")||
                            m_format == UCS("UTF8"))
                        {
                            buffer.push_back(0xFF);
                            buffer.push_back(0xFE);
                            for (size_t i = buffer.size(); i < sizeof(typename EncodingT::char_t); ++i)
                            {
                                buffer.push_back(0x00);
                            }
                        }
                    }
                    buffer.insert(buffer.end(),
                                  reinterpret_cast<uint8_t*>(text.data()),
                                  reinterpret_cast<uint8_t*>(text.data() + text.size()));
                }
                else
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

                m_stream->write(buffer);
                res->value(true);
            }
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > File<EncodingT>::size()
    {
        boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>(0));

        if (m_stream != nullptr && m_stream->is_open())
        {
            int length = 0;
            // get length of file:
            m_stream->seekg (0, ios::end);
            length = m_stream->tellg();
            m_stream->seekg (0, ios::beg);
            res->LLvalue(length);
        }

        return res;
    }

NAMESPACE_END

#undef A
