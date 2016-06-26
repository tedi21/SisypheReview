#include "SimpleCFGHandler.hpp"
#include <boost/algorithm/string.hpp>
#include "Convert.hpp"

using namespace dsg;

namespace cfg
{

    simple_cfg_handler::simple_cfg_handler()
    {
        m_logger = &Category::getInstance(LOGNAME);
    }

    std::wstring simple_cfg_handler::decorateFunctionName(cfg::config_function const& function) const
    {
        std::wstring functionName = function.class_name + L":" + function.name;
        std::vector<fct_parameter>::const_iterator i;
        for(i = function.parameters.begin(); i < function.parameters.end(); ++i)
        {
            functionName += L"@" + *i;
        }
        functionName += L"@" + function.return_type;
        boost::trim(functionName);
        return functionName;
    }

    void simple_cfg_handler::handlePath(const config_path& path)
    {
        // Retrieve absolute path
        config_path aux;
        size_t i = 0;
        for (; i < path.size(); i++)
        {
            config_dot_element node = path[i];
            if ( const config_dot* d = boost::get<const config_dot>( &node ) )
            {
                if (i < last_path.size())
                {
                    // Determine node
                    aux.push_back(last_path[i]);
                }
                else
                {
                    m_logger->errorStream() << "Unable to find parent branch .";
                }
            }
            else if ( const config_element* e = boost::get<const config_element>( &node ) )
            {
                if (e->branch.size() > 0 && e->branch[0] == L'-')
                {
                    if (i < last_path.size())
                    {
                        // Determine branch
                        config_element last_element = *(boost::get<const config_element>( &last_path[i] ));
                        last_element.identifiers.erase(last_element.identifiers.begin() + e->branch.size(), last_element.identifiers.end());
                        last_element.identifiers.insert(last_element.identifiers.end(), e->identifiers.begin(), e->identifiers.end());
                        aux.push_back(last_element);
                    }
                    else
                    {
                         m_logger->errorStream() << "Unable to find parent identifier -";
                    }
                }
                else
                {
                    // Copy node
                    aux.push_back(node);
                }
            }
        }
        // Save path
        last_path = aux;
    }

    void simple_cfg_handler::generateConfig(const config_content& content) const
    {
        UniWorkspace& workspace = UniDataModel::getInstance()->getWorkspace();
        UniFile* file = NULL;
        UniEntity* entity = NULL;
        UniRelation* relation = NULL;
        UniAttribute* attribute = NULL;
        config_path::const_iterator node;
        for (node = last_path.begin(); node < last_path.end() - 1; node++)
        {
            const config_element* e = boost::get<const config_element>( &(*node) );
            if (e)
            {
                // Handle FILE node
                if (boost::iequals(e->branch, L"file") && e->identifiers.size() > 0)
                {
                    const std::wstring* str = boost::get<const std::wstring>( &(e->identifiers[0]) );
                    if (str)
                    {
                        UniFileNameEquality eq(*str);
                        UniFileItr iFile = std::find_if( workspace.beginFiles(), workspace.endFiles(), eq );
                        if (iFile == workspace.endFiles())
                        {
                            iFile = workspace.openFile(*str);
                        }
                        file = &(*iFile);
                    }
                }
                // Handle ENTITY node
                else if (boost::iequals(e->branch, L"entity") && e->identifiers.size() > 0 && file)
                {
                    const std::wstring* str = boost::get<const std::wstring>( &(e->identifiers[0]) );
                    if (str)
                    {
                        UniEntityNameEquality eq(*str);
                        UniEntityItr iEntity = std::find_if( file->beginEntities(), file->endEntities(), eq );
                        if (iEntity == file->endEntities())
                        {
                            iEntity = file->addNewEntity(*str);
                        }
                        entity = &(*iEntity);
                    }
                }
                // Handle RELATION node
                else if (boost::iequals(e->branch, L"relation") && e->identifiers.size() > 0 && file)
                {
                    const std::wstring* str = boost::get<const std::wstring>( &(e->identifiers[0]) );
                    if (str)
                    {
                        UniRelationNameEquality eq(*str);
                        UniRelationItr iRelation = std::find_if( file->beginRelations(), file->endRelations(), eq );
                        if (iRelation == file->endRelations())
                        {
                            iRelation = file->addNewRelation(*str);
                        }
                        relation = &(*iRelation);
                    }
                }
                // Handle ATTRIBUTE node
                else if (boost::iequals(e->branch, L"attribute") && e->identifiers.size() > 0 && entity)
                {
                    const std::wstring* str = boost::get<const std::wstring>( &(e->identifiers[0]) );
                    if (str)
                    {
                        UniAttributeNameEquality eq(*str);
                        UniAttributeItr iAttribute = std::find_if( entity->beginAttributes(), entity->endAttributes(), eq );
                        if (iAttribute == entity->endAttributes())
                        {
                            iAttribute = entity->addNewAttribute(*str);
                        }
                        attribute = &(*iAttribute);
                    }
                }    
                else
                {
                     m_logger->errorStream() << "Unknown node "  << std::string(e->branch.begin(), e->branch.end());
                }
            }
        }
        // Handle last node
        if (last_path.size() > 0)
        {
            const config_element* e = boost::get<const config_element>( &last_path.back() );
            const config_value* v = boost::get<const config_value>( &content );
            const config_text* t = boost::get<const config_text>( &content );
            if (e)
            {
                // Handle value
                if (v)
                {
                    if (boost::iequals(e->branch, L"modifier") && attribute)
                    {
                        if (v->value == L"Id")           		attribute->setModifier(ATTR_ID);
                        else if (v->value == L"Ref")     		attribute->setModifier(ATTR_REF);
                        else if (v->value == L"Auto")    		attribute->setModifier(ATTR_AUTO);
                        else if (v->value == L"Const")   		attribute->setModifier(ATTR_CONST);
                        else if (v->value == L"Contextual")     attribute->setModifier(ATTR_CONTEXTUAL);
                        else if (v->value == L"Base")    		attribute->setModifier(ATTR_BASE);
                        else if (v->value == L"Virtual") 		attribute->setModifier(ATTR_VIRTUAL);
                        else if (v->value == L"Static")  		attribute->setModifier(ATTR_STATIC);
                    }
                    else if (boost::iequals(e->branch, L"author"))
                    {
                        workspace.setAuthor(v->value);
                    }
                    else if (boost::iequals(e->branch, L"brief"))
                    {
                        workspace.setBrief(v->value);
                    }
                    else if (boost::iequals(e->branch, L"name"))
                    {
                        workspace.setName(v->value);
                    }
                    else if (boost::iequals(e->branch, L"option"))
                    {
                        workspace.setOption(fctr::ToInt::parse(v->value));
                    }
                    else if (boost::iequals(e->branch, L"type"))
                    {
                        if (boost::iequals(v->value, L"file"))
                        {
                            workspace.setType(WRK_FILE);
                        }
                        else
                        {
                            workspace.setType(WRK_PROJECT);
                        }
                    }
                    else if (boost::iequals(e->branch, L"version"))
                    {
                        workspace.setVersion(v->value);
                    }
                    else
                    {
                        m_logger->errorStream() << "Unknown attribute "  << std::string(e->branch.begin(), e->branch.end());
                    }
                }
                // Handle text
                else if (t)
                {
                    if (boost::iequals(e->branch, L"content") && e->identifiers.size() > 0 && file)
                    {
                        std::vector<std::wstring> args(e->identifiers.size());
                        for (int i = 0; i < e->identifiers.size(); ++i)
                        {
                            const cfg::config_attribute* attr = boost::get<const cfg::config_attribute>( &(e->identifiers[i]) );
                            const cfg::config_function* fct = boost::get<const cfg::config_function>( &(e->identifiers[i]) );
                            const std::wstring* type = boost::get<const std::wstring>( &(e->identifiers[i]) );
                            if (attr)
                            {
                                args[i] = attr->class_name;
                                args.push_back(attr->name);
                            }
                            else if (fct)
                            {
                                args[i] = decorateFunctionName(*fct);
                            }
                            else if (type)
                            {
                                args[i] = *type;
                            }
                        }
                        if (args.size() == 3)
                        {
                            file->addNewContent(args[1], t->text, args[0], args[2]);
                        }
                        else if (args.size() == 2)
                        {
                            if (boost::iequals(args[1], L"ReturnDescription"))
                            {
                                const cfg::config_function* fct = boost::get<const cfg::config_function>( &(e->identifiers[0]) );
                                if (fct)
                                {
                                    file->addNewContent(args[1], t->text, args[0], fct->name);
                                }
                                else
                                {
                                    m_logger->errorStream() << "Function expected ReturnDescription";
                                }
                            }
                            else
                            {
                                file->addNewContent(args[1], t->text, args[0]);
                            }
                        }
                        else
                        {
                            file->addNewContent(args[0], t->text);
                        }
                    }
                    else
                    {
                        m_logger->errorStream() << "Unknown attribute "  << std::string(e->branch.begin(), e->branch.end());
                    }
                }
            }
        }
    }

    void simple_cfg_handler::setData(const config_file& file)
    {
        config_file::const_iterator line;
        for (line = file.begin(); line != file.end(); line++)
        {
            if ( const config_path* p = boost::get<const config_path>( &(*line) ) )
            {
                handlePath(*p);
            }
            else if ( const config_property* o = boost::get<const config_property>( &(*line) ) )
            {
                handlePath(o->path);
                // Generate configuration
                generateConfig(o->content);
            }
        }
    }

}
