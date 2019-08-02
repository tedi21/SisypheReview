/*
 * DiffInterpreter_impl.hpp
 *
 *
 * @date 07-10-2017
 * @author Teddy DIDE
 * @version 1.00
 */

#include "FunctionInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
DiffInterpreter<EncodingT>::DiffInterpreter()
{
    Matches = 0;
    Adds = 0;
    Deletes = 0;
    Modifies = 0;
}

template <class EncodingT>
typename EncodingT::string_t DiffInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new DiffInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t DiffInterpreter<EncodingT>::getClassName() const
{
    return UCS("Diff");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, UCS("Diff"), method, args, ret) ||
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
			Category* logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Unexpected call in Diff, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
void DiffInterpreter<EncodingT>::PushSequence(int offset1, size_t len1, int offset2, size_t len2)
{
    SequencePair pair;
    pair.sequence1.offset = offset1;
    pair.sequence1.len = len1;
    pair.sequence2.offset = offset2;
    pair.sequence2.len = len2;
    SequenceList.push_back(pair);
}

template <class EncodingT>
bool DiffInterpreter<EncodingT>::PopSequence()
{
    if (!SequenceList.empty())
    {
        std::list<SequencePair>::const_iterator iPair = std::prev(SequenceList.end());
        DiffItem(iPair->sequence1.offset, iPair->sequence1.len,
                 iPair->sequence2.offset, iPair->sequence2.len);
        SequenceList.erase(iPair);
    }
    return !SequenceList.empty();
}

template <class EncodingT>
void DiffInterpreter<EncodingT>::InitDiagArrays(size_t len1, size_t len2)
{
    size_t len = len1 + len2 + 3;
    DiagF.assign(len, -INT_MAX);
    DiagB.assign(len, INT_MAX);

    IDiagF = DiagF.begin()+len1+1;
    IDiagB = DiagB.begin()+len1+1;
    *(IDiagF+1) = -1;
    *(IDiagB+len2-len1+1) = (int) len2;
}

template <class EncodingT>
void DiffInterpreter<EncodingT>::DiffItem(int offset1, size_t len1, int offset2, size_t len2)
{
    // Trim matching bottoms ...
    while (len1 > 0 && len2 > 0 && (*FnEqual)(Array1[offset1], Array2[offset2]))
    {
        ++offset1;
        ++offset2;
        --len1;
        --len2;
    }
    // Trim matching tops
    while (len1 > 0 && len2 > 0 && (*FnEqual)(Array1[offset1+len1-1], Array2[offset2+len2-1]))
    {
        --len1;
        --len2;
    }
    // Stop diff'ing if minimal conditions reached ...
    if (len1 == 0)
    {
        AddDiff(offset1, len2, DIFF_TYPE_ADD);
    }
    else if (len2 == 0)
    {
        AddDiff(offset1, len1, DIFF_TYPE_DELETE);
    }
    else if (len1 == 1 && len2 ==1)
    {
        AddDiff(offset1, len1, DIFF_TYPE_DELETE);
        AddDiff(offset1, len2, DIFF_TYPE_ADD);
    }
    else
    {
        int p = -1;
        int delta = (int) (len2 - len1);
        int sign = 1;
        int usDelta = delta;
        if (delta < 0)
        {
            sign = -1;
            usDelta = -delta;
        }
        InitDiagArrays(len1, len2);
        bool loop = true;
        do
        {
            ++p;
            for (int k=-p; loop && k<usDelta; ++k)
            {
                loop = !(SnakeChrF(k*sign, offset1, len1, offset2, len2));
            }
            for (int k=p+usDelta; loop && k>usDelta; --k)
            {
                loop = !(SnakeChrF(k*sign, offset1, len1, offset2, len2));
            }
            for (int k=p+usDelta; loop && k>0; --k)
            {
                loop = !(SnakeChrB(k*sign, offset1, len1, offset2, len2));
            }
            for (int k=-p; loop && k<0; ++k)
            {
                loop = !(SnakeChrB(k*sign, offset1, len1, offset2, len2));
            }
            loop = loop && !(SnakeChrF(delta, offset1, len1, offset2, len2));
            loop = loop && !(SnakeChrB(0, offset1, len1, offset2, len2));
        }
        while (loop);
    }
}

template <class EncodingT>
bool DiffInterpreter<EncodingT>::SnakeChrF(int k, int offset1, size_t len1, int offset2, size_t len2)
{
    int x, y;
    if (*(IDiagF+k+1) > *(IDiagF+k-1))
    {
        y = *(IDiagF+k+1);
    }
    else
    {
        y = *(IDiagF+k-1) + 1;
    }
    x = y - k;
    while (x<(int)(len1-1) && y<(int)(len2-1) &&
           (*FnEqual)(Array1[offset1+x+1], Array2[offset2+y+1]))
    {
        ++x;
        ++y;
    }
    *(IDiagF+k) = y;
    bool result = (*(IDiagF+k) >= *(IDiagB+k));
    if (result)
    {
        ++x;
        ++y;
        PushSequence(offset1+x, len1-x, offset2+y, len2-y);
        PushSequence(offset1, x, offset2, y);
    }
    return result;
}

template <class EncodingT>
bool DiffInterpreter<EncodingT>::SnakeChrB(int k, int offset1, size_t len1, int offset2, size_t len2)
{
    int x, y;
    if (*(IDiagB+k-1) < *(IDiagB+k+1))
    {
        y = *(IDiagB+k-1);
    }
    else
    {
        y = *(IDiagB+k+1) - 1;
    }
    x = y - k;
    while (x >= 0 && y >= 0 &&
           (*FnEqual)(Array1[offset1+x], Array2[offset2+y]))
    {
        --x;
        --y;
    }
    *(IDiagB+k) = y;
    bool result = (*(IDiagB+k) <= *(IDiagF+k));
    if (result)
    {
        ++x;
        ++y;
        PushSequence(offset1+x, len1-x, offset2+y, len2-y);
        PushSequence(offset1, x, offset2, y);
    }
    return result;
}

template <class EncodingT>
void DiffInterpreter<EncodingT>::AddDiff(int offset1, size_t range, DiffType type)
{
    while (LastDiff.Index1 < offset1-1)
    {
        LastDiff.Type = DIFF_TYPE_NONE;
        ++LastDiff.Index1;
        ++LastDiff.Index2;
        LastDiff.Item1 = Array1[LastDiff.Index1];
        LastDiff.Item2 = Array2[LastDiff.Index2];
        DiffList.push_back(LastDiff);
        ++Matches;
    }

    switch (type)
    {
    case DIFF_TYPE_NONE:
        for (size_t i=0; (i<range) && (LastDiff.Index1<static_cast<int>(Array1.size())-1) && (LastDiff.Index2<static_cast<int>(Array2.size())-1); ++i)
        {
            LastDiff.Type = DIFF_TYPE_NONE;
            ++LastDiff.Index1;
            ++LastDiff.Index2;
            LastDiff.Item1 = Array1[LastDiff.Index1];
            LastDiff.Item2 = Array2[LastDiff.Index2];
            DiffList.push_back(LastDiff);
            ++Matches;
        }
        break;
    case DIFF_TYPE_ADD:
        for (size_t i=0; (i<range) && (LastDiff.Index2<static_cast<int>(Array2.size())-1); ++i)
        {
            //check if a range of adds are following a range of deletes
            //and convert them to modifies ...
            if (LastDiff.Type == DIFF_TYPE_DELETE)
            {
                typename std::list<DiffValueInterpreter<EncodingT> >::reverse_iterator jDiff = DiffList.rbegin();
                while (jDiff != DiffList.rend() && std::next(jDiff)->Type == DIFF_TYPE_DELETE) ++jDiff;
                jDiff->Type = DIFF_TYPE_MODIFY;
                --Deletes;
                ++Modifies;
                ++LastDiff.Index2;
                jDiff->Index2 = LastDiff.Index2;
                jDiff->Item2 = Array2[LastDiff.Index2];
                if (jDiff == DiffList.rbegin())
                {
                    LastDiff.Type = DIFF_TYPE_MODIFY;
                }
            }
            else
            {
                LastDiff.Type = DIFF_TYPE_ADD;
                LastDiff.Item1 = boost::shared_ptr< Base<EncodingT> >(new Base<EncodingT>());
                ++LastDiff.Index2;
                LastDiff.Item2 = Array2[LastDiff.Index2];

                DiffList.push_back(LastDiff);
                ++Adds;
            }
        }
        break;
    case DIFF_TYPE_DELETE:
        for (size_t i=0; (i<range) && (LastDiff.Index1<static_cast<int>(Array1.size())-1); ++i)
        {
            //check if a range of deletes are following a range of adds
            //and convert them to modifies ...
            if (LastDiff.Type == DIFF_TYPE_ADD)
            {
                typename std::list<DiffValueInterpreter<EncodingT> >::reverse_iterator jDiff = DiffList.rbegin();
                while (jDiff != DiffList.rend() && std::next(jDiff)->Type == DIFF_TYPE_ADD) ++jDiff;
                jDiff->Type = DIFF_TYPE_MODIFY;
                --Adds;
                ++Modifies;
                ++LastDiff.Index1;
                jDiff->Index1 = LastDiff.Index1;
                jDiff->Item1 = Array1[LastDiff.Index1];
                if (jDiff == DiffList.rbegin())
                {
                    LastDiff.Type = DIFF_TYPE_MODIFY;
                }
            }
            else
            {
                LastDiff.Type = DIFF_TYPE_DELETE;
                LastDiff.Item2 = boost::shared_ptr< Base<EncodingT> >(new Base<EncodingT>());
                ++LastDiff.Index1;
                LastDiff.Item1 = Array1[LastDiff.Index1];

                DiffList.push_back(LastDiff);
                ++Deletes;
            }
        }
        break;
    case DIFF_TYPE_MODIFY:
        break;
    }
}

template <class EncodingT>
void DiffInterpreter<EncodingT>::Clear()
{
    DiffList.clear();
    LastDiff.Type = DIFF_TYPE_NONE;
    LastDiff.Index1 = -1;
    LastDiff.Index2 = -1;
    Matches = 0;
    Adds = 0;
    Deletes = 0;
    Modifies = 0;
    Array1.clear();
    Array2.clear();
}

template <class EncodingT>
void DiffInterpreter<EncodingT>::compare(const boost::shared_ptr< Base<EncodingT> >& sequence1,
                                         const boost::shared_ptr< Base<EncodingT> >& sequence2,
                                         const boost::shared_ptr< Base<EncodingT> >& fnEqual)
{

    FnEqual  = dynamic_pointer_cast< Predicate<EncodingT> >(fnEqual);
    if (FnEqual)
    {
        try
        {
            Clear();

            if (check_array(sequence1, Array1, check_base<EncodingT>) &&
                check_array(sequence2, Array2, check_base<EncodingT>))
            {
                int lastIndex1 = (int) Array1.size()-1;

                // Initialize SequenceList
                PushSequence(0, Array1.size(), 0, Array2.size());
                // Process SequenceList
                while (PopSequence()) {}
                //correct the occasional missed match ...
                typename std::list<DiffValueInterpreter<EncodingT> >::iterator iDiff;
                for (iDiff = DiffList.begin(); iDiff != DiffList.end(); ++iDiff)
                {
                    if (iDiff->Type == DIFF_TYPE_MODIFY &&
                        (*FnEqual)(iDiff->Item1, iDiff->Item2))
                    {
                        iDiff->Type = DIFF_TYPE_NONE;
                        --Modifies;
                        ++Matches;
                    }
                }
                //finally, append any trailing matches onto DiffList ...
                AddDiff(LastDiff.Index1, lastIndex1-LastDiff.Index1, DIFF_TYPE_NONE);
            }
        }
        catch(...)
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "unexpected error in comparison algorithm.";
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Predicate expected, got " << A(FnEqual->getClassName());
    }
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffInterpreter<EncodingT>::getList() const
{
    boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
    typename std::list<DiffValueInterpreter<EncodingT> >::const_iterator iDiff;
    for (iDiff = DiffList.begin(); iDiff != DiffList.end(); ++iDiff)
    {
        arr->addValue(boost::shared_ptr< Base<EncodingT> > (new DiffValueInterpreter<EncodingT>(*iDiff)));
    }
    return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffInterpreter<EncodingT>::getMatches() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(Matches));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffInterpreter<EncodingT>::getAdds() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(Adds));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffInterpreter<EncodingT>::getDeletes() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(Deletes));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > DiffInterpreter<EncodingT>::getModifies() const
{
    return boost::shared_ptr< Base<EncodingT> > (new Numeric<EncodingT>(Modifies));
}

NAMESPACE_END

#undef A
#undef C
