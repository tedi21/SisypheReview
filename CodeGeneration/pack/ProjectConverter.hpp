#ifndef _PROJECT_CONVERTER_HPP_
#define _PROJECT_CONVERTER_HPP_

#include "ProjectGenerator.hpp"
#include "FileParser.hpp"

namespace dsg {

    template <class DerivedT>
    class ProjectConverter
    : public ProjectGenerator<DerivedT>, 
      public FileParser<DerivedT>
    {
    public:
        // constructor
        // factory need serializable object
        ProjectConverter(const string& filename, file_encoding_t encoding)
        : ProjectGenerator<DerivedT>(filename, encoding), 
          FileParser<DerivedT>(filename, encoding)
        {}

        // factory methods
        static void register_class()
        {
            ProjectGenerator<DerivedT>::register_class();
            FileParser<DerivedT>::register_class();
        }

        static void unregister_class()
        {
            ProjectGenerator<DerivedT>::unregister_class();
            FileParser<DerivedT>::unregister_class();
        }
    };

}

#endif // _PROJECT_CONVERTER_HPP_
