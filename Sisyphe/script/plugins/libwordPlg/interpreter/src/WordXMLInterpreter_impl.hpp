/*
 * WordXMLInterpreter_impl.hpp
 *
 *
 * @date 21-06-2016
 * @author Teddy DIDE
 * @version 1.00
 * Word Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
WordXMLInterpreter<EncodingT>::WordXMLInterpreter()
{
}

template <class EncodingT>
void WordXMLInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
WordXMLInterpreter<EncodingT>::~WordXMLInterpreter()
{
	tidyValue();
}

template <class EncodingT>
typename EncodingT::string_t WordXMLInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > WordXMLInterpreter<EncodingT>::clone() const
{
	return shared_ptr< Base<EncodingT> >(new WordXMLInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t WordXMLInterpreter<EncodingT>::getClassName() const
{
	return C("WordXML");
}

template <class EncodingT>
shared_ptr< Base<EncodingT> > WordXMLInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
{
	shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("WordXML"), method, args, ret))
		{
			find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
			for (size_t i = 0; i < params.size(); ++i)
			{
				find_parameter(ret, i, params[i]);
			}
		}
		else
		{
			Category* logger = &Category::getInstance(LOGNAME);
			logger->errorStream() << "Unexpected call in WordXML, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Initialise le parseur XML.
template <class EncodingT>
void WordXMLInterpreter<EncodingT>::initialize() const
{
	WordXMLDocument::initialize();
}

// Libère les objets XML.
template <class EncodingT>
void WordXMLInterpreter<EncodingT>::terminate() const
{
	WordXMLDocument::terminate();
}


NAMESPACE_END

#undef A
#undef C