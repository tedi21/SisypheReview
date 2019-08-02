/*
 * DiffInterpreter.hpp
 *
 *
 * @date 07-10-2017
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _DIFF_INTERPRETER_H_
#define _DIFF_INTERPRETER_H_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"
#include "Predicate.hpp"
#include "DiffTypeInterpreter.hpp"
#include "DiffValueInterpreter.hpp"
#include <list>
#include <vector>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

    struct Sequence
    {
        int offset;
        size_t len;
    };

    struct SequencePair
    {
        Sequence sequence1;
        Sequence sequence2;
    };

    // Classe représentant l'algorithme diff.
	template <class EncodingT>
    class DiffInterpreter
	: public Base<EncodingT>
	{
	private:
       std::list< DiffValueInterpreter<EncodingT> > DiffList;
       std::list<SequencePair> SequenceList;
       std::vector<int> DiagF;
       std::vector<int> DiagB;
       std::vector<int>::iterator IDiagF;
       std::vector<int>::iterator IDiagB;
       std::vector< boost::shared_ptr< Base<EncodingT> > > Array1;
       std::vector< boost::shared_ptr< Base<EncodingT> > > Array2;
       boost::shared_ptr< Predicate<EncodingT> > FnEqual;
       size_t Matches;
       size_t Adds;
       size_t Deletes;
       size_t Modifies;
       DiffValueInterpreter<EncodingT> LastDiff;

       void PushSequence(int offset1, size_t len1, int offset2, size_t len2);
       bool PopSequence();

       void InitDiagArrays(size_t len1, size_t len2);

       void DiffItem(int offset1, size_t len1, int offset2, size_t len2);
       bool SnakeChrF(int k, int offset1, size_t len1, int offset2, size_t len2);
       bool SnakeChrB(int k, int offset1, size_t len1, int offset2, size_t len2);
       void AddDiff(int offset1, size_t range, DiffType type);

       void Clear();

	public:
        DiffInterpreter();

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        // Réalise la comparaison.
        FACTORY_PROTOTYPE3(compare, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        void compare(const boost::shared_ptr< Base<EncodingT> >& sequence1,
                     const boost::shared_ptr< Base<EncodingT> >& sequence2,
                     const boost::shared_ptr< Base<EncodingT> >& fnEqual);

        // Retourne la liste des diff
        boost::shared_ptr< Base<EncodingT> > getList() const;

        // Retourne le nombre de correspondances
        boost::shared_ptr< Base<EncodingT> > getMatches() const;

        // Retourne le nombre d'insertion
        boost::shared_ptr< Base<EncodingT> > getAdds() const;

        // Retourne le nombre de suppression
        boost::shared_ptr< Base<EncodingT> > getDeletes() const;

        // Retourne le nombre de modification
        boost::shared_ptr< Base<EncodingT> > getModifies() const;

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( DiffInterpreter, UCS("Diff") );
            METHOD_KEY_REGISTER3( DiffInterpreter, void, compare, no_const_t, UCS("Diff::Compare") );
            METHOD_KEY_REGISTER ( DiffInterpreter, boost::shared_ptr< Base<EncodingT> >, getList, const_t, UCS("Diff::List") );
            METHOD_KEY_REGISTER ( DiffInterpreter, boost::shared_ptr< Base<EncodingT> >, getMatches, const_t, UCS("Diff::Matches") );
            METHOD_KEY_REGISTER ( DiffInterpreter, boost::shared_ptr< Base<EncodingT> >, getAdds, const_t, UCS("Diff::Adds") );
            METHOD_KEY_REGISTER ( DiffInterpreter, boost::shared_ptr< Base<EncodingT> >, getDeletes, const_t, UCS("Diff::Deletes") );
            METHOD_KEY_REGISTER ( DiffInterpreter, boost::shared_ptr< Base<EncodingT> >, getModifies, const_t, UCS("Diff::Modifies") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( UCS("Diff") );
            METHOD_KEY_UNREGISTER3( UCS("Diff::Compare") );
            METHOD_KEY_UNREGISTER ( UCS("Diff::List") );
            METHOD_KEY_UNREGISTER ( UCS("Diff::Matches") );
            METHOD_KEY_UNREGISTER ( UCS("Diff::Adds") );
            METHOD_KEY_UNREGISTER ( UCS("Diff::Deletes") );
            METHOD_KEY_UNREGISTER ( UCS("Diff::Modifies") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "DiffInterpreter_impl.hpp"

#endif
