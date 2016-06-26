#include <vector>

namespace gen {

    #define DEFINE_EMPTY_CONTEXT(CharT, ContextName)      \
        typedef generator_type< CharT >::context_t ContextName;

    #define DEFINE_CONTEXT_RANGE(ParentContext, ContainerType, ContextName)  \
        typedef context< ContainerType, ParentContext > ContextName;

    #define DEFINE_CONTEXT_NODE(ParentContext, ChildType, ContextName)  \
        DEFINE_CONTEXT_RANGE(ParentContext, std::vector<ChildType>, ContextName)

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Generic generate function implementation
    //
    ///////////////////////////////////////////////////////////////////////////

      template <class CharT, class DerivedT, class ContainerT>
      inline typename generator_string< CharT >::str_t
      generate_range(ContainerT const& container,
                     generator<DerivedT> const& g)                    
      {    
        typedef generator_type<CharT>                                generator_t;
        typedef context<ContainerT, typename generator_t::context_t> context_t;

        context_t context(container.begin(), container.end());
        g.derived().generate<generator_t>(context);
        return context.str();
      } 

      template <class CharT, class DerivedT, class DataT>
      inline typename generator_string< CharT >::str_t
      generate(DataT const& data,
               generator<DerivedT> const& g)
      {
          const std::vector<DataT> listData(1, data);
          return generate_range<CharT>(listData, g);
      }
}
