
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    GitBlameInterpreter<EncodingT>::GitBlameInterpreter()
    {
        m_value = nullptr;
        m_hunk = nullptr;
        m_line = 0;
    }

    template <class EncodingT>
    GitBlameInterpreter<EncodingT>::~GitBlameInterpreter()
    {
        m_hunk = nullptr;
        m_line = 0;
        if (m_value != nullptr)
        {
            git_blame_free(m_value);
        }
    }

    template <class EncodingT>
    GitBlameInterpreter<EncodingT>::GitBlameInterpreter(git_blame* value)
    {
        m_value = value;
        m_hunk = nullptr;
        m_line = 0;
    }

    template <class EncodingT>
    git_blame* GitBlameInterpreter<EncodingT>::value() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void GitBlameInterpreter<EncodingT>::value(git_blame* value)
    {
        if (m_value != nullptr)
        {
            git_blame_free(m_value);
        }
        m_value = value;
        m_hunk = nullptr;
        m_line = 0;
    }

    template <class EncodingT>
    typename EncodingT::string_t GitBlameInterpreter<EncodingT>::toString() const
    {
        return EncodingT::EMPTY;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitBlameInterpreter<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new GitBlameInterpreter<EncodingT>(m_value));
    }

    template <class EncodingT>
    typename EncodingT::string_t GitBlameInterpreter<EncodingT>::getClassName() const
    {
        return UCS("GitBlame");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitBlameInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, UCS("GitBlame"), method, args, ret)   ||
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
                logger->errorStream() << "Unexpected call in GitBlame, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitBlameInterpreter<EncodingT>::setLine(const boost::shared_ptr< Base<EncodingT> >& line)
    {
        boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(false);
        if (m_value)
        {
            boost::shared_ptr< Numeric<EncodingT> > nativeLine = dynamic_pointer_cast< Numeric<EncodingT> >(line);
            if (nativeLine != nullptr)
            {
                m_line = static_cast<size_t>(nativeLine->LLvalue());
                m_hunk = git_blame_get_hunk_byline(m_value, m_line);
                ret->value(m_hunk != nullptr);
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Numeric expected, got " << A(line->getClassName());
            }
        }
        return ret;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitBlameInterpreter<EncodingT>::getCommitId(boost::shared_ptr< Base<EncodingT> >& commitId) const
    {
        boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(false);
        if (m_hunk != nullptr)
        {
            boost::shared_ptr< String<EncodingT> > nativeId = dynamic_pointer_cast< String<EncodingT> >(commitId);
            if (nativeId != nullptr)
            {
                nativeId->value(C(git_oid_tostr_s(&m_hunk->orig_commit_id)));
                ret->value(true);
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "String expected, got " << A(commitId->getClassName());
            }
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->warnStream() << "No line specified";
        }
        return ret;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitBlameInterpreter<EncodingT>::getCommitDate(boost::shared_ptr< Base<EncodingT> >& commitDate) const
    {
        boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(false);
        if (m_hunk != nullptr)
        {
            boost::shared_ptr< String<EncodingT> > nativeDate = dynamic_pointer_cast< String<EncodingT> >(commitDate);
            if (nativeDate != nullptr)
            {
                char out[22];
                const git_time intime = m_hunk->orig_signature->when;
                time_t t = (time_t)intime.time + (intime.offset * 60);
                struct tm *intm = gmtime(&t);
                strftime(out, sizeof(out), "%Y-%m-%d %H:%M:%S", intm);

                nativeDate->value(C(out));
                ret->value(true);
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "String expected, got " << A(commitDate->getClassName());
            }
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->warnStream() << "No line specified";
        }
        return ret;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitBlameInterpreter<EncodingT>::getCommitAuthor(boost::shared_ptr< Base<EncodingT> >& commitAuthor) const
    {
        boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(false);
        if (m_hunk != nullptr)
        {
            boost::shared_ptr< String<EncodingT> > nativeAuthor = dynamic_pointer_cast< String<EncodingT> >(commitAuthor);
            if (nativeAuthor != nullptr)
            {
                nativeAuthor->value(C(m_hunk->orig_signature->name));
                ret->value(true);
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "String expected, got " << A(commitAuthor->getClassName());
            }
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->warnStream() << "No line specified";
        }
        return ret;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > GitBlameInterpreter<EncodingT>::getCommitLine(boost::shared_ptr< Base<EncodingT> >& commitLine) const
    {
        boost::shared_ptr< Bool<EncodingT> > ret = boost::make_shared< Bool<EncodingT> >(false);
        if (m_hunk != nullptr)
        {
            boost::shared_ptr< Numeric<EncodingT> > nativeLine = dynamic_pointer_cast< Numeric<EncodingT> >(commitLine);
            if (nativeLine != nullptr)
            {
                nativeLine->LLvalue(m_hunk->orig_start_line_number + (m_line - m_hunk->final_start_line_number));
                ret->value(true);
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "String expected, got " << A(commitLine->getClassName());
            }
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->warnStream() << "No line specified";
        }
        return ret;
    }

NAMESPACE_END

#undef A
#undef C
