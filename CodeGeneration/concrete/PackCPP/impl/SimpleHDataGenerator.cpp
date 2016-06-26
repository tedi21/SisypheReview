#include "SimpleHDataGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHDataGenerator::SimpleHDataGenerator()
		{
				SourceH_R2 = 
					CreateFile_R2;

				CreateFile_R2 =
					CreateHeader_R2(call_g(getWorkspaceNameHandler()) << str_g("Data.h"))
                    << CreateHPPDefine_R2(str_g("_") << call_g(getWorkspaceNameHandler()) << str_g("_Data_h_"))
                    << CreateEnum_R2
					<< CreateInclude_R2
					<< CreateHPPEndDefine_R2;            

				CreateInclude_R2 =
					str_g("#include \"config.hpp\"\r\n")
                    << (str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Export.hpp\"\r\n")
                    << (str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << ".hpp\"\r\n")        [file0, fileN]
                    << (str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << "Access.hpp\"\r\n")  [file0, fileN]
					<< "\r\n";

                CreateEnum_R2 =
                       line_g(1) << "enum operation_access_t"
                    << line_g(1) << "{"
                    << line_g(1) << htab_g(1) << "OPERATION_ACCESS_INSERT,"
                    << line_g(1) << htab_g(1) << "OPERATION_ACCESS_UPDATE,"
                    << line_g(1) << htab_g(1) << "OPERATION_ACCESS_DELETE,"
                    << line_g(1) << htab_g(1) << "OPERATION_ACCESS_START,"
                    << line_g(1) << htab_g(1) << "OPERATION_ACCESS_COMMIT,"
                    << line_g(1) << htab_g(1) << "OPERATION_ACCESS_ROLLBACK"
                    << line_g(1) << "};"
                    << line_g(2);
		}
    }
}
