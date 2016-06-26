#ifndef _PROJECT_GENERATOR_HPP_
#define _PROJECT_GENERATOR_HPP_

#include "FileGenerator.hpp"

namespace dsg {

    template <class DerivedT>
    class ProjectGenerator
    : public FileGenerator<DerivedT> {
    public:
        // constructor
        // factory need serializable object
        ProjectGenerator(const string & filename, file_encoding_t encoding, const string & dirname = "")
        : FileGenerator<DerivedT>(filename, encoding, dirname)
        {}

        // generation method
        int generate();

        // factory methods
        static void register_class()
        {
            std::string className = std::string(DerivedT::Family_Name) + "::" + DerivedT::Format_Name;
            GeneratorManager* manager = GeneratorManager::getInstance();
            manager->registerClass( new fctr::Factory3
                     <Generator,                                                  // Base
                      ProjectGenerator<DerivedT>,                                 // Class
                      fctr::Prototype3< fctr::In<string>, fctr::In<file_encoding_t>, fctr::In<string> > > // Parameters
                      (className) );                                  // Name

            FamilyManager* family = FamilyManager::getInstance();
            vector<string>* tab;
            if (family->existKey(DerivedT::Family_Name))
            {
                tab = family->getObject(DerivedT::Family_Name);
            }
            else 
            {
                tab = new vector<string>;
                family->registerObject(DerivedT::Family_Name, tab);
            }
            tab->push_back(DerivedT::Format_Name);
        }

        static void unregister_class()
        {
            GeneratorManager* manager = GeneratorManager::getInstance();
            manager->unRegisterClass(DerivedT::Format_Name);

            FamilyManager* family = FamilyManager::getInstance();
            vector<string>* tab = family->getObject(DerivedT::Family_Name);
            tab->erase( std::find(tab->begin(), tab->end(), DerivedT::Format_Name) );
            if (tab->size() == 0) family->unRegisterObject(DerivedT::Family_Name);
        }
    };

}

#include "impl/ProjectGenerator_impl.hpp"

#endif // _PROJECT_GENERATOR_HPP_
