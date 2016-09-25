#include "../xstring.hpp"

namespace enc {

    const XMLCh* xml::EMPTY = L"";

    // conversion ucs <-> xml
    XENCODING_API xml::string_t 
    transcodeFrom(const ucs::char_t * from) 
    {
        // too complex, no efficient
        XMLTransService::Codes failReason;
        XMLSize_t eaten;
        unsigned int xml_len;
        // boost::scoped_ptr can be replace by static to improve performance
        XMLRecognizer::Encodings encoding = sizeof(ucs::char_t)==2?XMLRecognizer::UTF_16L:XMLRecognizer::UCS_4L;
        boost::scoped_ptr<XMLTranscoder> ucs4Transcoder
            (XMLPlatformUtils::fgTransService->makeNewTranscoderFor(encoding, failReason, 16*1024));
        size_t len = get_len(from);
        boost::scoped_array<XMLCh> xml(new XMLCh[len*2+1]);
        boost::scoped_array<unsigned char> char_sizes(new unsigned char[len*2+1]);
        memset(char_sizes.get(),sizeof(ucs::char_t),len);
        memset(char_sizes.get()+len,0,len+1);

        try {
            xml_len = 
                ucs4Transcoder->transcodeFrom((const XMLByte *)from, len*sizeof(ucs::char_t),
                                               xml.get(), len*2, eaten, char_sizes.get()); 
            xml[xml_len] = chNull;
        } catch (TranscodingException & /*ex*/) {
            //cout << XMLString::transcode(ex.getMessage()) << endl;
            xml[0] = chNull;
        }
        return xml::string_t(xml.get());
    }

    XENCODING_API ucs::string_t 
    transcodeTo(const xml::char_t * from) 
    {
        XMLTransService::Codes failReason;
        XMLSize_t eaten;
        unsigned int ucs4_len;
        // boost::scoped_ptr can be replace by static to improve performance
        XMLRecognizer::Encodings encoding = sizeof(ucs::char_t)==2?XMLRecognizer::UTF_16L:XMLRecognizer::UCS_4L;
        boost::scoped_ptr<XMLTranscoder> ucs4Transcoder
            (XMLPlatformUtils::fgTransService->makeNewTranscoderFor(encoding, failReason, 16*1024));

        size_t len = XMLString::stringLen(from);
        boost::scoped_array<XMLByte> ucs4(new XMLByte[len*4]);
        
        try {
            ucs4_len = 
                ucs4Transcoder->transcodeTo(from, len, ucs4.get(), len*4, eaten, XMLTranscoder::UnRep_Throw);
        } catch (TranscodingException & /*ex*/) {
            ucs4_len = 0;
        }
        return ucs::string_t((ucs::char_t*)ucs4.get(), (ucs::char_t*)(ucs4.get()+ucs4_len));
    }
}
