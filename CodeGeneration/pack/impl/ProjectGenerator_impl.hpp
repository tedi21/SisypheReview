#include "utf16_codecvt.hpp"
#include <fstream>

using namespace std;

namespace dsg {

    template <class DerivedT>
    int ProjectGenerator<DerivedT>::generate()
    {
        typename DerivedT::generator_t g;
        int ret = 0;
        wofstream out_file;
        UniDataModel* data = UniDataModel::getInstance();
        const UniWorkspace* wrk = &(data->getWorkspace());

        set_locale(out_file, FileGenerator<DerivedT>::m_encoding);

        for (const_UniFileItr itr = wrk->beginFiles(); itr != wrk->endFiles(); ++itr)
        {
            bool exception = false;
            string subfilename = (FileGenerator<DerivedT>::m_dirname / FileGenerator<DerivedT>::m_filename)
                                 .generic_string();

            replace_all(subfilename, "{w}", encode<ucs,ansi>(wrk->getName()));
            replace_all(subfilename, "{f}", encode<ucs,ansi>(itr->hasAlias()? itr->getAlias() : itr->getName()));

            wstring out;
            try 
            {
                generator::file_context context(wrk->beginFiles(), wrk->endFiles());
                context.current(itr);
                g.template generate<generator::gen_info>(context);
                out = context.str();
            }
            catch (gen::generator_exception<wchar_t> & ex)
            {
                FileGenerator<DerivedT>::m_logger->errorStream() << "A generator exception occurs during generation of "
                                                                 << subfilename.c_str()
                                                                 << " file.";
                out = ex.buffer();
                exception = true;
                ret = -2;
            }

            if (!out.empty())
            {
                out_file.open(subfilename.c_str(), ios::binary);
                if (out_file.is_open())
                {
                    if (FileGenerator<DerivedT>::m_encoding == FILE_UTF_16LE ||
                        FileGenerator<DerivedT>::m_encoding == FILE_UTF_16BE)
                        out_file << utf16_codecvt_facet<>::BOM;
                    out_file.write(out.c_str(), (streamsize) out.size());
                    out_file.close();
                    if (!exception)
                    {
                        FileGenerator<DerivedT>::m_logger->noticeStream() << "Generation "
                                                                          << subfilename.c_str()
                                                                          << " succeeded";
                    }
                }
                else
                {
                    FileGenerator<DerivedT>::m_logger->errorStream() << "Unable to open the file :"
                                                                     << subfilename.c_str();
                    ret = -1;
                }
            }
            else
            {
                FileGenerator<DerivedT>::m_logger->noticeStream() << "No file "
                                                                  << subfilename.c_str()
                                                                  << " generated";                
            }
        }
        return ret;
    }
}
