#include "SimpleHPPExportGenerator.hpp"

namespace dsg {

    namespace generator {

        SimpleHPPExportGenerator::SimpleHPPExportGenerator()
        {
                SourceHPP_R2 =
                    CreateFile_R2;

                CreateFile_R2 =
                    CreateHeader_R2(call_g(getWorkspaceNameHandler()) << "Export.hpp")
                    << CreateHPPDefine_R2("_" << call_g(getWorkspaceNameHandler()) << "_EXPORT_HPP_")
                    << CreateDefine_R2
                    << CreateHPPEndDefine_R2;

                CreateDefine_R2 =
                    "#ifdef HAS_" << upper_g(call_g(getWorkspaceNameHandler())) << "_DLL\r\n"
                    "#    define HAS_DB_DLL\r\n"
                    "#    ifdef BUILD_" << upper_g(call_g(getWorkspaceNameHandler())) << "_DLL\r\n"
                    "#        define BUILD_DB_DLL\r\n"
                    "#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)\r\n"
                    "#            define " << upper_g(call_g(getWorkspaceNameHandler())) << "_API __declspec(dllexport)\r\n"
                    "#               else\r\n"
                    "#            define " << upper_g(call_g(getWorkspaceNameHandler())) << "_API\r\n"
                    "#      endif\r\n"
                    "#    else\r\n"
                    "#        if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__MINGW32__)\r\n"
                    "#            define " << upper_g(call_g(getWorkspaceNameHandler())) << "_API __declspec(dllimport)\r\n"
                    "#               else\r\n"
                    "#            define " << upper_g(call_g(getWorkspaceNameHandler())) << "_API\r\n"
                    "#      endif\r\n"
                    "#    endif\r\n"
                    "#else\r\n"
                    "#    define " << upper_g(call_g(getWorkspaceNameHandler())) << "_API\r\n"
                    "#endif\r\n\r\n";
        }
    }
}

