
NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Null<EncodingT>::Null()
    {}

    template <class EncodingT>
    typename EncodingT::string_t Null<EncodingT>::toString() const
    {
        return UCS("null");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Null<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Null<EncodingT>());
    }

    template <class EncodingT>
    typename EncodingT::string_t Null<EncodingT>::getClassName() const
    {
        return UCS("Null");
    }

NAMESPACE_END

