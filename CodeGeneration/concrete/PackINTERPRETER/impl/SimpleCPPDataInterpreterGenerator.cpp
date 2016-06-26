#include "SimpleCPPDataInterpreterGenerator.hpp"

namespace dsg {

	namespace generator {

        SimpleCPPDataInterpreterGenerator::SimpleCPPDataInterpreterGenerator()
		{
            SourceCPP =
                   CreateFile;

            CreateFile =
                   CreateInclude
                << CreateNamespace
                << CreateExport;

            CreateInclude =
                                 str_g("#include <windows.h>")
                 << line_g(1) << str_g("#include \"ProgramInterpreter.hpp\"")
                 << ListFile
                    (
                        (line_g(1)
                     << "#include \"" << file_g(getFileNameHandler(KIND_ALIAS)) << "Interpreter.hpp\"")[Has_Class]
                    );

            CreateNamespace =
                    line_g(2) << "using namespace enc;"
                 << line_g(1) << "using namespace fctr;"
                 << line_g(1) << "using namespace interp;";

            CreateExport =
                    line_g(2) << "//////////////////////////////////////////"
                 << line_g(1) << "// Exportation des classes"
                 << line_g(1) << "//////////////////////////////////////////"
                 << ListFile
                    (
                        ListClass
                        (
                           (line_g(1)
                         << "FACTORY_EXPORT_FILE(" << ClassName << "Interpreter<ucs>, " << call_g(getWorkspaceNameHandler()) << ")")[Has_Constant || Has_Method]
                        )
                    );
		}
    }
}
