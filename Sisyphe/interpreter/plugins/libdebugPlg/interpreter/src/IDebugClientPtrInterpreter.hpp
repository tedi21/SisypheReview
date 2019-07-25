/*
 * IDebugClientPtrInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 * Debug Interpreter generated by gensources.
 */

#ifndef _IDEBUGCLIENTPTR_INTERPRETER_H_
#define _IDEBUGCLIENTPTR_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"
#include "Array.hpp"
#include "DebugPtr.h"
typedef CDebugPtr<IDebugClient> IDebugClientPtr;
#include "IDebugControlPtrInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

	// Classe permettant d'accéder à un client de débogage. 
	template <class EncodingT>
	class IDebugClientPtrInterpreter
	: public Base<EncodingT>
	{
	private:
		IDebugClientPtr m_object;

		void initValue(const IDebugClientPtr& object);

		IDebugClientPtr& refValue();

		const IDebugClientPtr& refValue() const;

		void tidyValue();

	public:
		IDebugClientPtrInterpreter();

		~IDebugClientPtrInterpreter();

		IDebugClientPtrInterpreter(const IDebugClientPtr& object);

		IDebugClientPtrInterpreter(const IDebugClientPtrInterpreter<EncodingT>& rhs);

		IDebugClientPtrInterpreter<EncodingT>& operator=(const IDebugClientPtrInterpreter<EncodingT>& rhs);

		const IDebugClientPtr& value() const;

		void value(IDebugClientPtr const& object);

		virtual typename EncodingT::string_t toString() const;

		virtual boost::shared_ptr< Base<EncodingT> > clone() const;

		virtual typename EncodingT::string_t getClassName() const;

		virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

		// La méthode CreateProcess crée un processus à partir de la ligne de commande en paramètre.
		FACTORY_PROTOTYPE2(createProcess, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > createProcess(const boost::shared_ptr< Base<EncodingT> >& commandLine, const boost::shared_ptr< Base<EncodingT> >& createFlags);

		// La méthode CreateProcess crée un processus à partir de la ligne de commande en paramètre et d'un répertoire courant spécifique.
		FACTORY_PROTOTYPE3(createProcess, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > createProcess(const boost::shared_ptr< Base<EncodingT> >& commandLine, const boost::shared_ptr< Base<EncodingT> >& createFlags, const boost::shared_ptr< Base<EncodingT> >& initialDirectory);

		// The GetRunningProcessSystemIds method returns the process ID.
		FACTORY_PROTOTYPE1(getRunningProcessSystemIds, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getRunningProcessSystemIds(boost::shared_ptr< Base<EncodingT> >& processId);

		// The GetRunningProcessDescription method returns a description of the process that includes the executable image name, the service names, the MTS package names, and the command line.
		FACTORY_PROTOTYPE4(getRunningProcessDescription, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >, InOut< boost::shared_ptr< Base<EncodingT> > >)
		boost::shared_ptr< Base<EncodingT> > getRunningProcessDescription(const boost::shared_ptr< Base<EncodingT> >& systemId, const boost::shared_ptr< Base<EncodingT> >& flags, boost::shared_ptr< Base<EncodingT> >& exeName, boost::shared_ptr< Base<EncodingT> >& description);

		FACTORY_BEGIN_REGISTER
			CLASS_KEY_REGISTER  ( IDebugClientPtrInterpreter, C("IDebugClientPtr") );
			METHOD_KEY_REGISTER2( IDebugClientPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, createProcess, no_const_t, C("IDebugClientPtr::CreateProcess") );
			METHOD_KEY_REGISTER3( IDebugClientPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, createProcess, no_const_t, C("IDebugClientPtr::CreateProcess") );
			METHOD_KEY_REGISTER1( IDebugClientPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, getRunningProcessSystemIds, no_const_t, C("IDebugClientPtr::GetRunningProcessSystemIds") );
			METHOD_KEY_REGISTER4( IDebugClientPtrInterpreter, boost::shared_ptr< Base<EncodingT> >, getRunningProcessDescription, no_const_t, C("IDebugClientPtr::GetRunningProcessDescription") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
			CLASS_KEY_UNREGISTER  ( C("IDebugClientPtr") );
			METHOD_KEY_UNREGISTER2( C("IDebugClientPtr::CreateProcess") );
			METHOD_KEY_UNREGISTER3( C("IDebugClientPtr::CreateProcess") );
			METHOD_KEY_UNREGISTER1( C("IDebugClientPtr::GetRunningProcessSystemIds") );
			METHOD_KEY_UNREGISTER4( C("IDebugClientPtr::GetRunningProcessDescription") );
		FACTORY_END_UNREGISTER
	};

	template <class EncodingT>
	bool check_IDebugClientPtr(boost::shared_ptr< Base<EncodingT> > const& val, IDebugClientPtr& a);

	template <class EncodingT>
	bool reset_IDebugClientPtr(boost::shared_ptr< Base<EncodingT> >& val, IDebugClientPtr const& a);

NAMESPACE_END

#undef A
#undef C
#include "IDebugClientPtrInterpreter_impl.hpp"

#endif