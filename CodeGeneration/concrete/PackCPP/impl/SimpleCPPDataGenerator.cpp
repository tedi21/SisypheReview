#include "SimpleCPPDataGenerator.hpp"

namespace dsg {

    namespace generator {

        SimpleCPPDataGenerator::SimpleCPPDataGenerator()
        {
                SourceCPP_R2 =
                    CreateFile_R2;

                CreateFile_R2 =
                    CreateInclude_R2
                    << CreateNamespace_R2
                    << CreateExport_R2;

                CreateInclude_R2 =
                    str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Data.h\"\r\n"
                    << "\r\n";

                CreateNamespace_R2 =
                    str_g("using namespace entity;\r\n"
                          "using namespace data_access;\r\n\r\n");

                CreateExport_R2 =
                    str_g("//////////////////////////////////////////\r\n"
                          "// Instanciation des classes\r\n"
                          "//////////////////////////////////////////\r\n")
                    << (str_g("template class _") << UEntity_R2 << "<ucs>;\r\n"
                    <<  str_g("template class _") << UEntity_R2 << "Access<ucs>;\r\n")
                    [ent0, entN]
                    [file0, fileN]
                    << str_g("template class _DataConnection<ucs>;\r\n")
                    << "\r\n";
        }
    }
}

