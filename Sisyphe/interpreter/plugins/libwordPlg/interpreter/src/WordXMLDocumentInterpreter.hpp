/*
 * WordXMLDocumentInterpreter.hpp
 *
 *
 * @date 12-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * Word Interpreter generated by gensources.
 */

#ifndef _WORDXMLDOCUMENT_INTERPRETER_H_
#define _WORDXMLDOCUMENT_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"
#include "WordXMLDocument.h"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
using namespace libword;

NAMESPACE_BEGIN(interp)

	// Classe représentant un document XML.
	template <class EncodingT>
	class WordXMLDocumentInterpreter
	: public Base<EncodingT>
	{
	private:
WordXMLDocument* m_object;  
        bool m_allocated;

		void initValue(const WordXMLDocument& object);

		WordXMLDocument& refValue();

		const WordXMLDocument& refValue() const;

		void tidyValue();

	public:
		WordXMLDocumentInterpreter();

		~WordXMLDocumentInterpreter();

		WordXMLDocumentInterpreter(const WordXMLDocument& object);

		WordXMLDocumentInterpreter(const WordXMLDocumentInterpreter<EncodingT>& rhs);

		WordXMLDocumentInterpreter<EncodingT>& operator=(const WordXMLDocumentInterpreter<EncodingT>& rhs);

		const WordXMLDocument& value() const;

		void value(WordXMLDocument const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// Crée un nouveau noeud.
		FACTORY_PROTOTYPE1(createNode, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > createNode(const boost::shared_ptr< Base<EncodingT> >& tagName);

		// Crée un noeud texte.
		FACTORY_PROTOTYPE1(createTextNode, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > createTextNode(const boost::shared_ptr< Base<EncodingT> >& txt);

		// Retourne le noeud racine du document.
		boost::shared_ptr< Base<EncodingT> > getDocumentNode();

		// Ouvre un fichier Word XML.
		FACTORY_PROTOTYPE1(parse, In< boost::shared_ptr< Base<EncodingT> > >)
		void parse(const boost::shared_ptr< Base<EncodingT> >& doc);

		// Enregistre le document.
		void save() const;

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( WordXMLDocumentInterpreter, UCS("WordXMLDocument") );
			METHOD_KEY_REGISTER1( WordXMLDocumentInterpreter, boost::shared_ptr< Base<EncodingT> >, createNode, no_const_t, UCS("WordXMLDocument::CreateNode") );
			METHOD_KEY_REGISTER1( WordXMLDocumentInterpreter, boost::shared_ptr< Base<EncodingT> >, createTextNode, no_const_t, UCS("WordXMLDocument::CreateTextNode") );
			METHOD_KEY_REGISTER ( WordXMLDocumentInterpreter, boost::shared_ptr< Base<EncodingT> >, getDocumentNode, no_const_t, UCS("WordXMLDocument::DocumentNode") );
			METHOD_KEY_REGISTER1( WordXMLDocumentInterpreter, void, parse, no_const_t, UCS("WordXMLDocument::Parse") );
			METHOD_KEY_REGISTER ( WordXMLDocumentInterpreter, void, save, const_t, UCS("WordXMLDocument::Save") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("WordXMLDocument") );
			METHOD_KEY_UNREGISTER1( UCS("WordXMLDocument::CreateNode") );
			METHOD_KEY_UNREGISTER1( UCS("WordXMLDocument::CreateTextNode") );
			METHOD_KEY_UNREGISTER ( UCS("WordXMLDocument::DocumentNode") );
			METHOD_KEY_UNREGISTER1( UCS("WordXMLDocument::Parse") );
			METHOD_KEY_UNREGISTER ( UCS("WordXMLDocument::Save") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_WordXMLDocument(boost::shared_ptr< Base<EncodingT> > const& val, WordXMLDocument& a);

	template <class EncodingT>
	bool reset_WordXMLDocument(boost::shared_ptr< Base<EncodingT> >& val, WordXMLDocument const& a);

NAMESPACE_END

#undef A
#undef C
#include "WordXMLDocumentInterpreter_impl.hpp"

#endif