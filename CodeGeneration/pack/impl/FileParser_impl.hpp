
namespace dsg {

    template <class DerivedT>
    int FileParser<DerivedT>::parse()
    {
        int ret = 0;
        std::wstring in;
        typename DerivedT::parser_t g;

        if (read_file(m_filename.c_str(), m_encoding, in))
        {
            // parse data
            parse_info<wchar_t const*> info = boost::spirit::classic::parse(in.c_str(), g, space_p);
            if (info.full)
            {
                m_logger->noticeStream() << "Parsing succeeded";
            } 
            else 
            {
                m_logger->noticeStream() << "Parsing failed";
                m_logger->noticeStream() << "stopped at: \" "
                                         << encode<ucs,ansi>(info.stop) << "\"";
                ret = -2;
            }
        }
        else
        {
            m_logger->errorStream() << "Unable to read the file :" << m_filename;
            ret = -1;
        }
        return ret;
    }

}
