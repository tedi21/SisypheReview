#ifndef _SIMPLE_HPP_EXPORT_GENERATOR_HPP_
#define _SIMPLE_HPP_EXPORT_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

    namespace generator {

        struct SimpleHPPExportGenerator
        : public SimpleCPPCommonGenerator,
          public report<SimpleHPPExportGenerator> {

            format<gen_info>    SourceHPP_R2,
                                CreateFile_R2,
                                CreateDefine_R2;

            SimpleHPPExportGenerator();

            template <typename InfoT>
            struct etat {
                format<InfoT> const& EtatStart;

                etat(SimpleHPPExportGenerator const& me)
                : EtatStart(me.SourceHPP_R2)
                {}

                format<InfoT> const& start() const { return EtatStart; }
            };
        };

    }
}

#endif // _SIMPLE_HPP_EXPORT_GENERATOR_HPP_
