/*
 * IDiaDataSourcePtrInterpreter.hpp
 *
 *
 * @date 03-09-2016
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIADATASOURCEPTR_INTERPRETER_H_
#define _IDIADATASOURCEPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
#include "Array.hpp"
#include "DiaPtr.h"
typedef CDiaPtr<IDiaDataSource> IDiaDataSourcePtr;
#include "IDiaSessionPtrInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe permettant d'accéder à une source de symboles de débogage. 
	template <class EncodingT>
	class IDiaDataSourcePtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDiaDataSourcePtr m_object;

		void initValue(const IDiaDataSourcePtr& object);

		IDiaDataSourcePtr& value();

		const IDiaDataSourcePtr& value() const;

		void tidyValue();

	public:
		IDiaDataSourcePtrInterpreter();

		~IDiaDataSourcePtrInterpreter();

		IDiaDataSourcePtrInterpreter(const IDiaDataSourcePtr& object);

		IDiaDataSourcePtrInterpreter(const IDiaDataSourcePtrInterpreter<EncodingT>& rhs);

		IDiaDataSourcePtrInterpreter<EncodingT>& operator=(const IDiaDataSourcePtrInterpreter<EncodingT>& rhs);

		const IDiaDataSourcePtr& getValue() const;

		void setValue(IDiaDataSourcePtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// Ouvre et prépare un fichier de base de données du programme (.pdb) comme source de données de débogage.
		FACTORY_PROTOTYPE1(loadDataFromPdb, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > loadDataFromPdb(const boost::shared_ptr< Base<EncodingT> >& pdbPath);

		// Ouvre une session pour obtenir des symboles.
		FACTORY_PROTOTYPE1(openSession, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > openSession(boost::shared_ptr< Base<EncodingT> >& ppSession);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDiaDataSourcePtrInterpreter, C("IDiaDataSourcePtr") );
			METHOD_KEY_REGISTER1( IDiaDataSourcePtrInterpreter, boost::shared_ptr< Base<EncodingT> >, loadDataFromPdb, no_const_t, C("IDiaDataSourcePtr::LoadDataFromPdb") );
			METHOD_KEY_REGISTER1( IDiaDataSourcePtrInterpreter, boost::shared_ptr< Base<EncodingT> >, openSession, no_const_t, C("IDiaDataSourcePtr::OpenSession") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDiaDataSourcePtr") );
			METHOD_KEY_UNREGISTER1( C("IDiaDataSourcePtr::LoadDataFromPdb") );
			METHOD_KEY_UNREGISTER1( C("IDiaDataSourcePtr::OpenSession") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDiaDataSourcePtr(boost::shared_ptr< Base<EncodingT> > const& val, IDiaDataSourcePtr& a);

	template <class EncodingT>
	bool reset_IDiaDataSourcePtr(boost::shared_ptr< Base<EncodingT> >& val, IDiaDataSourcePtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDiaDataSourcePtrInterpreter_impl.hpp"

#endif