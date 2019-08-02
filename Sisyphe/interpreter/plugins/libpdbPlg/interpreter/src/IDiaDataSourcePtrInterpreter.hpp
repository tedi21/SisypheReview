/*
 * IDiaDataSourcePtrInterpreter.hpp
 *
 *
 * @date 02-08-2019
 * @author Teddy DIDE
 * @version 1.00
 * Pdb Interpreter generated by gensources.
 */

#ifndef _IDIADATASOURCEPTR_INTERPRETER_H_
#define _IDIADATASOURCEPTR_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
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

		IDiaDataSourcePtr& refValue();

		const IDiaDataSourcePtr& refValue() const;

		void tidyValue();

	public:
		IDiaDataSourcePtrInterpreter();

		IDiaDataSourcePtrInterpreter(const IDiaDataSourcePtr& object);

		const IDiaDataSourcePtr& value() const;

		void value(IDiaDataSourcePtr const& object);

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
			CLASS_KEY_REGISTER  ( IDiaDataSourcePtrInterpreter, UCS("IDiaDataSourcePtr") );
			METHOD_KEY_REGISTER1( IDiaDataSourcePtrInterpreter, boost::shared_ptr< Base<EncodingT> >, loadDataFromPdb, no_const_t, UCS("IDiaDataSourcePtr::LoadDataFromPdb") );
			METHOD_KEY_REGISTER1( IDiaDataSourcePtrInterpreter, boost::shared_ptr< Base<EncodingT> >, openSession, no_const_t, UCS("IDiaDataSourcePtr::OpenSession") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( UCS("IDiaDataSourcePtr") );
			METHOD_KEY_UNREGISTER1( UCS("IDiaDataSourcePtr::LoadDataFromPdb") );
			METHOD_KEY_UNREGISTER1( UCS("IDiaDataSourcePtr::OpenSession") );
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