#include "SimpleHPPLogGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPLogGenerator::SimpleHPPLogGenerator()
		{
				SourceHPP_R2 = 
					CreateFile_R2;

				CreateFile_R2 =
					CreateHeader_R2(str_g("config.hpp"))
					<< CreateHPPDefine_R2(str_g("_config_hpp_"))
					<< CreateInclude_R2
					<< CreateDefine_R2
					<< CreateHPPEndDefine_R2;            

				CreateInclude_R2 =
					str_g("#include <log4cpp/Category.hh>\r\n\r\n");

				CreateDefine_R2 =
					str_g("// necessary for use log4cpp with boost\r\n")
					<< "#undef int64_t\r\n\r\n"
					"static const char* LOGNAME = \"" << call_g(getWorkspaceNameHandler()) << "\";\r\n\r\n"
					"// Avoid putting \"data_access::\" in front of everything in Doxygen output\r\n"
					"#ifdef " << upper_g(call_g(getWorkspaceNameHandler())) << "_DOXYGEN_PROCESSING\r\n"
					"#    define data_access\r\n"
                    "#    define entity\r\n"
					"#    define NAMESPACE_BEGIN(x)\r\n"
					"#    define NAMESPACE_END\r\n"
					"#else\r\n"
					"#    define NAMESPACE_BEGIN(x) namespace x {\r\n"
					"#    define NAMESPACE_END }\r\n"
                    "#endif\r\n\r\n";
		}
    }
}
