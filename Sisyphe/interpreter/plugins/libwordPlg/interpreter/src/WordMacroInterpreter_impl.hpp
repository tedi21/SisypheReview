/*
 * WordMacroInterpreter_impl.hpp
 *
 *
 * @date 17-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * Word Interpreter generated by gensources.
 */

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)


template <class EncodingT>
WordMacroInterpreter<EncodingT>::WordMacroInterpreter()
{
}

template <class EncodingT>
void WordMacroInterpreter<EncodingT>::tidyValue()
{
}

template <class EncodingT>
void WordMacroInterpreter<EncodingT>::initValue(const WordMacro& object)
{
	m_object = object;
}

template <class EncodingT>
WordMacro& WordMacroInterpreter<EncodingT>::refValue()
{
	return m_object;
}

template <class EncodingT>
const WordMacro& WordMacroInterpreter<EncodingT>::refValue() const
{
	return m_object;
}

template <class EncodingT>
WordMacroInterpreter<EncodingT>::WordMacroInterpreter(const WordMacro& object)
{
	initValue(object);
}

template <class EncodingT>
const WordMacro& WordMacroInterpreter<EncodingT>::value() const
{
	return refValue();
}

template <class EncodingT>
void WordMacroInterpreter<EncodingT>::value(WordMacro const& object)
{
	if (&object != &refValue()) {
		tidyValue();
		initValue(object);
	}
}

template <class EncodingT>
typename EncodingT::string_t WordMacroInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > WordMacroInterpreter<EncodingT>::clone() const
{
	return boost::shared_ptr< Base<EncodingT> >(new WordMacroInterpreter<EncodingT>(*this));
}

template <class EncodingT>
typename EncodingT::string_t WordMacroInterpreter<EncodingT>::getClassName() const
{
	return C("WordMacro");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > WordMacroInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
		if (tryInvoke(this, C("WordMacro"), method, args, ret) ||
			tryInvoke(this, C("Base"), method, args, ret))
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
			logger->errorStream() << "Unexpected call in WordMacro, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

// Convertie un fichier en xml.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > WordMacroInterpreter<EncodingT>::convertToXML(const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& xmlFile, const boost::shared_ptr< Base<EncodingT> >& acceptAllRevisions) const
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	typename EncodingT::string_t nativeFile;
	typename EncodingT::string_t nativeXmlFile;
	bool nativeAcceptAllRevisions;
	if (check_string<EncodingT>(file, nativeFile) && 
		check_string<EncodingT>(xmlFile, nativeXmlFile) && 
		check_bool(acceptAllRevisions, nativeAcceptAllRevisions))
	{
		res.reset(new Bool<EncodingT>(refValue().convertToXML(nativeFile.c_str(), nativeXmlFile.c_str(), nativeAcceptAllRevisions)));
	}
	return res;
}

// Convertie un fichier en doc.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > WordMacroInterpreter<EncodingT>::convertToDOC(const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& docFile, const boost::shared_ptr< Base<EncodingT> >& acceptAllRevisions) const
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	typename EncodingT::string_t nativeFile;
	typename EncodingT::string_t nativeDocFile;
	bool nativeAcceptAllRevisions;
	if (check_string<EncodingT>(file, nativeFile) && 
		check_string<EncodingT>(docFile, nativeDocFile) && 
		check_bool(acceptAllRevisions, nativeAcceptAllRevisions))
	{
		res.reset(new Bool<EncodingT>(refValue().convertToDOC(nativeFile.c_str(), nativeDocFile.c_str(), nativeAcceptAllRevisions)));
	}
	return res;
}

// Convertie un fichier en pdf.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > WordMacroInterpreter<EncodingT>::convertToPDF(const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& pdfFile, const boost::shared_ptr< Base<EncodingT> >& acceptAllRevisions) const
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	typename EncodingT::string_t nativeFile;
	typename EncodingT::string_t nativePdfFile;
	bool nativeAcceptAllRevisions;
	if (check_string<EncodingT>(file, nativeFile) && 
		check_string<EncodingT>(pdfFile, nativePdfFile) && 
		check_bool(acceptAllRevisions, nativeAcceptAllRevisions))
	{
		res.reset(new Bool<EncodingT>(refValue().convertToPDF(nativeFile.c_str(), nativePdfFile.c_str(), nativeAcceptAllRevisions)));
	}
	return res;
}

// Convertie un fichier en xdoc.
template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > WordMacroInterpreter<EncodingT>::convertToXDOC(const boost::shared_ptr< Base<EncodingT> >& file, const boost::shared_ptr< Base<EncodingT> >& xdocFile, const boost::shared_ptr< Base<EncodingT> >& acceptAllRevisions) const
{
	boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());
	typename EncodingT::string_t nativeFile;
	typename EncodingT::string_t nativeXdocFile;
	bool nativeAcceptAllRevisions;
	if (check_string<EncodingT>(file, nativeFile) && 
		check_string<EncodingT>(xdocFile, nativeXdocFile) && 
		check_bool(acceptAllRevisions, nativeAcceptAllRevisions))
	{
		res.reset(new Bool<EncodingT>(refValue().convertToXDOC(nativeFile.c_str(), nativeXdocFile.c_str(), nativeAcceptAllRevisions)));
	}
	return res;
}


template <class EncodingT>
bool check_WordMacro(boost::shared_ptr< Base<EncodingT> > const& val, WordMacro& a)
{
	boost::shared_ptr< WordMacroInterpreter<EncodingT> > value  = dynamic_pointer_cast< WordMacroInterpreter<EncodingT> >(val);
	if (value)
	{
		a = value->value();
	}
	else
	{
		Category * logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "WordMacro expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

template <class EncodingT>
bool reset_WordMacro(boost::shared_ptr< Base<EncodingT> >& val, WordMacro const& a)
{
	boost::shared_ptr< WordMacroInterpreter<EncodingT> > value  = dynamic_pointer_cast< WordMacroInterpreter<EncodingT> >(val);
	if (value)
	{
		value->value(a);
	}
	else
	{
		Category* logger = &Category::getInstance(LOGNAME);
		logger->errorStream() << "WordMacro expected, got " << A(val->getClassName());
	}
	return (value != NULL);
}

NAMESPACE_END

#undef A
#undef C