#include "utf16_codecvt.hpp"
#include "endianness.hpp"
#include "CoreTypes.hpp"
#include "GeneratorTypes.hpp"
#include <fstream>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

namespace dsg {

    template <class DerivedT>
    int FileGenerator<DerivedT>::generate()
    {
        typename DerivedT::generator_t g;
        int ret = 0;
        UniDataModel* data = UniDataModel::getInstance();
        const UniWorkspace* wrk = &(data->getWorkspace());

        wstring out;
        bool exception = false;
        try 
        {
            generator::file_context context(wrk->beginFiles(), wrk->endFiles());
            g.template generate<generator::gen_info>(context);
            out = context.str();
        }
        catch (gen::generator_exception<wchar_t> & ex)
        {
            out = ex.buffer();
            exception = true;
        }

        if (!out.empty())
        {
            string subfilename = (m_dirname / FileGenerator<DerivedT>::m_filename)
                                 .generic_string();
            replace_all(subfilename, "{w}", encode<ucs,ansi>(wrk->getName()));
            if (write_file(subfilename.c_str(), m_encoding, out))
            {
                if (!exception)
                {
                    m_logger->noticeStream() << "Generation " << subfilename << " succeeded";
                }
                else
                {
                    m_logger->errorStream() << "A generator exception occurs during generation of "
                                            << m_filename.c_str()
                                            << " file.";
                    ret = -2;
                }
            }
            else 
            {
                m_logger->errorStream() << "Unable to write the file :" << m_filename.c_str();
                ret = -1;
            }
        }
        else
        {
            m_logger->noticeStream() << "No file " << m_filename.c_str() << " generated";
        }
        return ret;
    }
}
