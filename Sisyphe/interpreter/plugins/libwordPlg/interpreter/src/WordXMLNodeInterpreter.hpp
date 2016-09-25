/*
 * WordXMLNodeInterpreter.hpp
 *
 *
 * @date 23-08-2016
 * @author Teddy DIDE
 * @version 1.00
 * Word Interpreter generated by gensources.
 */

#ifndef _WORDXMLNODE_INTERPRETER_H_
#define _WORDXMLNODE_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "WordXMLNode.h"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;
using namespace libword;

NAMESPACE_BEGIN(interp)

	// Classe représentant un noeud XML du document Word.
	template <class EncodingT>
	class WordXMLNodeInterpreter
	: public Base<EncodingT>
	{
	private:
		WordXMLNode m_object;

		void initValue(const WordXMLNode& object);

		WordXMLNode& value();

		const WordXMLNode& value() const;

		void tidyValue();

	public:
		WordXMLNodeInterpreter();

		~WordXMLNodeInterpreter();

		WordXMLNodeInterpreter(const WordXMLNode& object);

		WordXMLNodeInterpreter(const WordXMLNodeInterpreter<EncodingT>& rhs);

		WordXMLNodeInterpreter<EncodingT>& operator=(const WordXMLNodeInterpreter<EncodingT>& rhs);

		const WordXMLNode& getValue() const;

		void setValue(WordXMLNode const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// Le nom du noeud *DOCUMENT*. 
		boost::shared_ptr< Base<EncodingT> > getDOCUMENT_TAG() const;

		// Le nom du noeud *BODY*. 
		boost::shared_ptr< Base<EncodingT> > getBODY_TAG() const;

		// Le nom du noeud *SECTION*. 
		boost::shared_ptr< Base<EncodingT> > getSECTION_TAG() const;

		// Le nom du noeud *SUBSECTION*. 
		boost::shared_ptr< Base<EncodingT> > getSUBSECTION_TAG() const;

		// Le nom du noeud *TABLE*. 
		boost::shared_ptr< Base<EncodingT> > getTABLE_TAG() const;

		// Le nom du noeud *ROW*. 
		boost::shared_ptr< Base<EncodingT> > getROW_TAG() const;

		// Le nom du noeud *CELL*. 
		boost::shared_ptr< Base<EncodingT> > getCELL_TAG() const;

		// Le nom du noeud *PARAGRAPH*. 
		boost::shared_ptr< Base<EncodingT> > getPARAGRAPH_TAG() const;

		// Le nom du noeud *REVISION*. 
		boost::shared_ptr< Base<EncodingT> > getREVISION_TAG() const;

		// Le nom du noeud *RUN*. 
		boost::shared_ptr< Base<EncodingT> > getRUN_TAG() const;

		// Valeur par défaut indiquant que le paramètre de la taille est à ignorer (cf. méthode *eraseString*). 
		boost::shared_ptr< Base<EncodingT> > getNO_LENGTH() const;

		// Retourne le nom du noeud.
		boost::shared_ptr< Base<EncodingT> > getTagName() const;

		// Execute une requête XPath.
		FACTORY_PROTOTYPE1(evaluate, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > evaluate(const boost::shared_ptr< Base<EncodingT> >& xpath) const;

		// Retourne les noeuds fils.
		boost::shared_ptr< Base<EncodingT> > getNodes() const;

		// Retourne les noeuds fils avec le nom *tagName*.
		FACTORY_PROTOTYPE1(getNodes, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getNodes(const boost::shared_ptr< Base<EncodingT> >& tagName) const;

		// Retourne le noeud suivant.
		boost::shared_ptr< Base<EncodingT> > getNextNode() const;

		// Retourne le noeud suivant avec le nom *tagName*.
		FACTORY_PROTOTYPE1(getNextNode, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getNextNode(const boost::shared_ptr< Base<EncodingT> >& tagName) const;

		// Retourne le noeud précèdent.
		boost::shared_ptr< Base<EncodingT> > getPreviousNode() const;

		// Retourne le noeud précèdent avec le nom *tagName*.
		FACTORY_PROTOTYPE1(getPreviousNode, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getPreviousNode(const boost::shared_ptr< Base<EncodingT> >& tagName) const;

		// Retourne le noeud parent.
		boost::shared_ptr< Base<EncodingT> > getParent() const;

		// Retourne le noeud parent avec le nom *tagName*.
		FACTORY_PROTOTYPE1(getParent, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getParent(const boost::shared_ptr< Base<EncodingT> >& tagName) const;

		// Retourne le contenu d'un noeud.
		boost::shared_ptr< Base<EncodingT> > getContent() const;

		// Indique si le noeud à un attribut *attrName*.
		FACTORY_PROTOTYPE1(hasAttribute, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > hasAttribute(const boost::shared_ptr< Base<EncodingT> >& attrName) const;

		// Retourne la valeur de l'attribut *attrName*.
		FACTORY_PROTOTYPE1(getAttribute, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getAttribute(const boost::shared_ptr< Base<EncodingT> >& attrName) const;

		// Retourne les noms des attributs du noeud.
		boost::shared_ptr< Base<EncodingT> > getAttributesNames() const;

		// Retourne le texte brut du noeud.
		boost::shared_ptr< Base<EncodingT> > getString() const;

		// Retourne le document.
		boost::shared_ptr< Base<EncodingT> > getDocument() const;

		// Indique si le noeud est valide.
		boost::shared_ptr< Base<EncodingT> > isValid() const;

		// Définit le contenu.
		FACTORY_PROTOTYPE1(setContent, In< boost::shared_ptr< Base<EncodingT> > >)
		void setContent(const boost::shared_ptr< Base<EncodingT> >& content);

		// Définit un attribut.
		FACTORY_PROTOTYPE2(setAttribute, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		void setAttribute(const boost::shared_ptr< Base<EncodingT> >& attrName, const boost::shared_ptr< Base<EncodingT> >& attrValue);

		// Supprime un attribut.
		FACTORY_PROTOTYPE1(eraseAttribute, In< boost::shared_ptr< Base<EncodingT> > >)
		void eraseAttribute(const boost::shared_ptr< Base<EncodingT> >& attrName);

		// Retourne le noeud Propriétés correspondant au noeud conteneur en cours ou crée le noeud si celui-ci n'existe pas.
		boost::shared_ptr< Base<EncodingT> > createPropertiesNode();

		// Définit le noeud *Propriétés*.
		FACTORY_PROTOTYPE1(setPropertiesNode, In< boost::shared_ptr< Base<EncodingT> > >)
		void setPropertiesNode(const boost::shared_ptr< Base<EncodingT> >& node);

		// Supprime le noeud *Propriétés*.
		void erasePropertiesNode();

		// Ajoute un nouveau noeud.
		FACTORY_PROTOTYPE1(append, In< boost::shared_ptr< Base<EncodingT> > >)
		void append(const boost::shared_ptr< Base<EncodingT> >& newChild);

		// Supprime le noeud.
		void erase();

		// Remplace un noeud.
		FACTORY_PROTOTYPE2(replace, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		void replace(const boost::shared_ptr< Base<EncodingT> >& newChild, const boost::shared_ptr< Base<EncodingT> >& oldChild);

		// Insère un nouveau noeud.
		FACTORY_PROTOTYPE2(insertBefore, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		void insertBefore(const boost::shared_ptr< Base<EncodingT> >& newChild, const boost::shared_ptr< Base<EncodingT> >& refChild);

		// Clone le noeud.
		FACTORY_PROTOTYPE1(cloneNode, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > cloneNode(const boost::shared_ptr< Base<EncodingT> >& deep) const;

		// Ajoute du texte.
		FACTORY_PROTOTYPE2(appendString, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > appendString(const boost::shared_ptr< Base<EncodingT> >& trackedChanges, const boost::shared_ptr< Base<EncodingT> >& str);

		// Supprime du texte.
		FACTORY_PROTOTYPE3(eraseString, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		void eraseString(const boost::shared_ptr< Base<EncodingT> >& trackedChanges, const boost::shared_ptr< Base<EncodingT> >& pos, const boost::shared_ptr< Base<EncodingT> >& length);

		// Insère du texte.
		FACTORY_PROTOTYPE3(insertString, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > insertString(const boost::shared_ptr< Base<EncodingT> >& trackedChanges, const boost::shared_ptr< Base<EncodingT> >& pos, const boost::shared_ptr< Base<EncodingT> >& str);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( WordXMLNodeInterpreter, C("WordXMLNode") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getDOCUMENT_TAG, const_t, C("WordXMLNode::DocumentTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getBODY_TAG, const_t, C("WordXMLNode::BodyTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSECTION_TAG, const_t, C("WordXMLNode::SectionTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getSUBSECTION_TAG, const_t, C("WordXMLNode::SubSectionTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getTABLE_TAG, const_t, C("WordXMLNode::TableTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getROW_TAG, const_t, C("WordXMLNode::RowTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCELL_TAG, const_t, C("WordXMLNode::CellTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getPARAGRAPH_TAG, const_t, C("WordXMLNode::ParagraphTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getREVISION_TAG, const_t, C("WordXMLNode::RevisionTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getRUN_TAG, const_t, C("WordXMLNode::RunTag") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getNO_LENGTH, const_t, C("WordXMLNode::NoLength") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getTagName, const_t, C("WordXMLNode::TagName") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, evaluate, const_t, C("WordXMLNode::Evaluate") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getNodes, const_t, C("WordXMLNode::Nodes") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getNodes, const_t, C("WordXMLNode::Nodes") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getNextNode, const_t, C("WordXMLNode::NextNode") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getNextNode, const_t, C("WordXMLNode::NextNode") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getPreviousNode, const_t, C("WordXMLNode::PreviousNode") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getPreviousNode, const_t, C("WordXMLNode::PreviousNode") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getParent, const_t, C("WordXMLNode::Parent") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getParent, const_t, C("WordXMLNode::Parent") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getContent, const_t, C("WordXMLNode::Content") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, hasAttribute, const_t, C("WordXMLNode::HasAttribute") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getAttribute, const_t, C("WordXMLNode::Attributes") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getAttributesNames, const_t, C("WordXMLNode::AttributesNames") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getString, const_t, C("WordXMLNode::GetString") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, getDocument, const_t, C("WordXMLNode::Document") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, isValid, const_t, C("WordXMLNode::Validity") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, void, setContent, no_const_t, C("WordXMLNode::Content") );
			METHOD_KEY_REGISTER2( WordXMLNodeInterpreter, void, setAttribute, no_const_t, C("WordXMLNode::Attributes") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, void, eraseAttribute, no_const_t, C("WordXMLNode::removeAttributes") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, createPropertiesNode, no_const_t, C("WordXMLNode::PropertiesNode") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, void, setPropertiesNode, no_const_t, C("WordXMLNode::PropertiesNode") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, void, erasePropertiesNode, no_const_t, C("WordXMLNode::removePropertiesNode") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, void, append, no_const_t, C("WordXMLNode::Append") );
			METHOD_KEY_REGISTER ( WordXMLNodeInterpreter, void, erase, no_const_t, C("WordXMLNode::Erase") );
			METHOD_KEY_REGISTER2( WordXMLNodeInterpreter, void, replace, no_const_t, C("WordXMLNode::Replace") );
			METHOD_KEY_REGISTER2( WordXMLNodeInterpreter, void, insertBefore, no_const_t, C("WordXMLNode::InsertBefore") );
			METHOD_KEY_REGISTER1( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, cloneNode, const_t, C("WordXMLNode::CloneNode") );
			METHOD_KEY_REGISTER2( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, appendString, no_const_t, C("WordXMLNode::AppendString") );
			METHOD_KEY_REGISTER3( WordXMLNodeInterpreter, void, eraseString, no_const_t, C("WordXMLNode::EraseString") );
			METHOD_KEY_REGISTER3( WordXMLNodeInterpreter, boost::shared_ptr< Base<EncodingT> >, insertString, no_const_t, C("WordXMLNode::InsertString") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("WordXMLNode") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::DocumentTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::BodyTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::SectionTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::SubSectionTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::TableTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::RowTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::CellTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::ParagraphTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::RevisionTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::RunTag") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::NoLength") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::TagName") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::Evaluate") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::Nodes") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::Nodes") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::NextNode") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::NextNode") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::PreviousNode") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::PreviousNode") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::Parent") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::Parent") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::Content") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::HasAttribute") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::Attributes") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::AttributesNames") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::GetString") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::Document") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::Validity") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::Content") );
			METHOD_KEY_UNREGISTER2( C("WordXMLNode::Attributes") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::removeAttributes") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::PropertiesNode") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::PropertiesNode") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::removePropertiesNode") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::Append") );
			METHOD_KEY_UNREGISTER ( C("WordXMLNode::Erase") );
			METHOD_KEY_UNREGISTER2( C("WordXMLNode::Replace") );
			METHOD_KEY_UNREGISTER2( C("WordXMLNode::InsertBefore") );
			METHOD_KEY_UNREGISTER1( C("WordXMLNode::CloneNode") );
			METHOD_KEY_UNREGISTER2( C("WordXMLNode::AppendString") );
			METHOD_KEY_UNREGISTER3( C("WordXMLNode::EraseString") );
			METHOD_KEY_UNREGISTER3( C("WordXMLNode::InsertString") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_WordXMLNode(boost::shared_ptr< Base<EncodingT> > const& val, WordXMLNode& a);

	template <class EncodingT>
	bool reset_WordXMLNode(boost::shared_ptr< Base<EncodingT> >& val, WordXMLNode const& a);

NAMESPACE_END

#undef A
#undef C
#include "WordXMLNodeInterpreter_impl.hpp"

#endif