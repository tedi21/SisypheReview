
#define A(str) encode<EncodingT,enc::ansi>(str)
#define P(str) encode<EncodingT,enc::path>(str)
#define C(str) encode<enc::path,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Folder<EncodingT>::Folder()
    {}

    template <class EncodingT>
    Folder<EncodingT>::Folder(const typename EncodingT::string_t& path)
    {
        m_path = P(path);
    }

    template <class EncodingT>
    Folder<EncodingT>::Folder(boost::shared_ptr< Base<EncodingT> > const& path)
    {
        typename EncodingT::string_t nativePath;
        if (check_string<EncodingT>(path, nativePath))
        {
            m_path = P(nativePath);
        }
    }

    template <class EncodingT>
    typename EncodingT::string_t Folder<EncodingT>::toString() const
    {
        return C(m_path.native());
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Folder<EncodingT>(C(m_path.native())));
    }

    template <class EncodingT>
    typename EncodingT::string_t Folder<EncodingT>::getClassName() const
    {
        return UCS("Folder");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, UCS("Folder"), method, args, ret) ||
                tryInvoke(this, UCS("Base"), method, args, ret))
            {
                find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
                for (size_t i = 0; i < params.size(); ++i)
                {
                    find_parameter(ret, i, params[i]);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in Folder, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::getPath() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(toString()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::getAbsolutePath() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(
               C(files::system_complete( m_path ).native())));
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::getParentPath() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(
               C(m_path.parent_path().native())));
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::getFilename() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(
               C(m_path.filename().native())));
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::getFiles() const
    {
        boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
        if (files::exists(m_path) && files::is_directory(m_path))
        {
            files::directory_iterator end_iter;
            for (files::directory_iterator dir_iter(m_path); dir_iter!=end_iter; ++dir_iter)
            {
                if (files::is_regular_file(dir_iter->status()))
                {
                    arr->addValue(boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(C(dir_iter->path().filename().native()))));
                }
            }
        }
        return arr;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::getFolders() const
    {
        boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
        if (files::exists(m_path) && files::is_directory(m_path))
        {
            files::directory_iterator end_iter;
            for (files::directory_iterator dir_iter(m_path); dir_iter!=end_iter; ++dir_iter)
            {
                if (files::is_directory(dir_iter->status()))
                {
                    arr->addValue(boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(C(dir_iter->path().filename().native()))));
                }
            }
        }
        return arr;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::exists() const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>(false));
        try
        {
            res.reset(new Bool<EncodingT>(files::exists(m_path)));
        }
        catch (files::filesystem_error& ex)
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << ex.what();
        }
        return res;
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::createFolder(boost::shared_ptr< Base<EncodingT> > const& newName)
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>(false));
        typename EncodingT::string_t nativeName;
        if (check_string<EncodingT>(newName, nativeName))
        {
            try
            {
                res.reset(new Bool<EncodingT>(files::create_directory(m_path/P(nativeName))));
            }
            catch (files::filesystem_error& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
        return res;
    }

    template <class EncodingT>
    void Folder<EncodingT>::copyTo(boost::shared_ptr< Base<EncodingT> > const& name, boost::shared_ptr< Base<EncodingT> > const& folder)
    {
        typename EncodingT::string_t nativeName, nativeFolder;
        if (check_string<EncodingT>(name, nativeName) && check_string<EncodingT>(folder, nativeFolder))
        {
            try
            {
                files::copy(m_path/P(nativeName), P(nativeFolder));
            }
            catch (files::filesystem_error& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::remove(boost::shared_ptr< Base<EncodingT> > const& name)
    {
        boost::shared_ptr< Numeric<EncodingT> > res(new Numeric<EncodingT>(0));
        typename EncodingT::string_t nativeName;
        if (check_string<EncodingT>(name, nativeName))
        {
            try
            {
                res.reset(new Numeric<EncodingT>(files::remove_all(m_path/P(nativeName))));
            }
            catch (files::filesystem_error& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
        return res;
    }

    template <class EncodingT>
    void Folder<EncodingT>::rename(boost::shared_ptr< Base<EncodingT> > const& oldName, boost::shared_ptr< Base<EncodingT> > const& newName)
    {
        typename EncodingT::string_t nativeOldName, nativeNewName;
        if (check_string<EncodingT>(oldName, nativeOldName) && check_string<EncodingT>(newName, nativeNewName))
        {
            try
            {
                files::rename(m_path/P(nativeOldName), m_path/P(nativeNewName));
            }
            catch (files::filesystem_error& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Folder<EncodingT>::getModificationDate() const
    {
        typedef boost::date_time::time_facet<boost::posix_time::ptime, char> time_facet_t;
        static std::locale old_locale;
        static std::locale new_locale(old_locale, new time_facet_t("%Y/%m/%d %H:%M:%S"));

        std::basic_stringstream<char> ss;
        ss.imbue(new_locale);
        ss << boost::posix_time::from_time_t(files::last_write_time(m_path));
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(encode<ansi,EncodingT>(ss.str())));
    }

NAMESPACE_END

#undef P
#undef C
#undef A
