#include "SimpleCPPInterpreterDataGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPInterpreterDataGenerator::SimpleCPPInterpreterDataGenerator()
		{
				SourceCPP_R2 = 
					CreateFile_R2;

				CreateFile_R2 =
					CreateInclude_R2
					<< CreateNamespace_R2
					<< CreateExport_R2;            

				CreateInclude_R2 =
					str_g("#include \"ProgramInterpreter.hpp\"\r\n")
                    << (str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << "Interpreter.hpp\"\r\n"
                    <<  str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << "InterpreterAccess.hpp\"\r\n")    [file0, fileN]
					<< "\r\n";

				CreateNamespace_R2 =
					str_g("using namespace enc;\r\n"
						  "using namespace fctr;\r\n"
						  "using namespace interp;\r\n\r\n");

				CreateExport_R2 =
					str_g("//////////////////////////////////////////\r\n"
						  "// Exportation des classes\r\n"
						  "//////////////////////////////////////////\r\n")
					<< (str_g("FACTORY_EXPORT(") << UEntity_R2 << "Interpreter<ucs>)\r\n"
					<<  str_g("FACTORY_EXPORT(") << UEntity_R2 << "InterpreterAccess<ucs>)\r\n") 
					[ent0, entN]
					[file0, fileN]
					<< "\r\n";
		}
    }
}
