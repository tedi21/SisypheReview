#ifndef _FILE_CONVERTER_HPP_
#define _FILE_CONVERTER_HPP_

#include "FileGenerator.hpp"
#include "FileParser.hpp"

namespace dsg {

    template <class DerivedT>
    class FileConverter
    : public FileGenerator<DerivedT>, 
      public FileParser<DerivedT>
    {
    public:
        // constructor
        // factory need serializable object
        FileConverter(const string & filename, file_encoding_t encoding)
        : FileGenerator<DerivedT>(filename, encoding), 
          FileParser<DerivedT>(filename, encoding)
        {}

        // factory methods
        static void register_class()
        {
            FileGenerator<DerivedT>::register_class();
            FileParser<DerivedT>::register_class();
        }

        static void unregister_class()
        {
            FileGenerator<DerivedT>::unregister_class();
            FileParser<DerivedT>::unregister_class();
        }
    };

}

#endif // _FILE_CONVERTER_HPP_
