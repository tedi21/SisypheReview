#ifndef _SIMPLE_CFG_HANDLER_HPP_
#define _SIMPLE_CFG_HANDLER_HPP_

#include <SimpleCFGStructure.hpp>
#include "CoreTypes.hpp"

namespace cfg
{

    class simple_cfg_handler
    {
    private:
        cfg::config_path last_path;
        log4cpp::Category*   m_logger;

        std::wstring decorateFunctionName(cfg::config_function const& function) const;
        void handlePath(const config_path& path);
        void generateConfig(const config_content& content) const;

    public:
        simple_cfg_handler();

        void setData(const config_file& file);
    };

}

#endif // _SIMPLE_CFG_HANDLER_HPP_
