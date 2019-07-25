/*
 * CPPParserInterpreter.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#ifndef _CPP_PARSER_INTERPRETER_H_
#define _CPP_PARSER_INTERPRETER_H_

#include "config.hpp"
#include "macros.hpp"
#include "Base.hpp"
#include "String.hpp"
#include <vector>
#include <functional>
#include <any>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

using namespace boost;

NAMESPACE_BEGIN(interp)

    using FlagSet = uint64_t;

    template <class EncodingT>
    class Information
    {
    private:
        std::optional<typename EncodingT::string_t> mName;
        std::optional<size_t> mType;

    public:
        Information(typename EncodingT::string_t& name, size_t type)
        : mName(name), mType(type)
        {}

        Information(typename EncodingT::string_t& name)
        : mName(name)
        {}

        bool hasName() const
        {
            return mName.has_value();
        }

        bool hasType() const
        {
            return mType.has_value();
        }

        const typename EncodingT::string_t& getName() const
        {
            return *mName;
        }

        size_t getType() const
        {
            return *mType;
        }
    };

    class Block
    {
    private:
        size_t mStart, mEnd;
        std::any mData;

    public:
        Block()
        : mStart(-1), mEnd(-1)
        {}

        Block(size_t start, size_t end)
        : mStart(start), mEnd(end)
        {}

        Block(size_t val)
        : mStart(val), mEnd(val)
        {}

        template <class T>
        Block(size_t start, size_t end, T data)
        : mStart(start), mEnd(end), mData(data)
        {}

        static bool compareStart(const Block& me, const Block& o)
        {
            return me.mStart <= o.mStart;
        }

        static bool compareEnd(const Block& me, const Block& o)
        {
            return me.mEnd < o.mEnd;
        }

        bool inRange(size_t val) const
        {
            return (mStart <= val) && (val < mEnd);
        }

        size_t Start() const
        {
            return mStart;
        }

        size_t End() const
        {
            return mEnd;
        }

        template <class T>
        T data() const
        {
            return std::any_cast<T>(mData);
        }
    };

	template <class EncodingT>
    class CPPParserInterpreter
	: public Base<EncodingT>
	{
    private:
        enum class FLAGS : std::uint8_t
        {
            IN_NO_CODE,
            IN_COMMENT,
            IN_CPP_COMMENT,
            IN_C_COMMENT,
            IN_STRING,
            IN_DBL_STRING,
            IN_SMPL_STRING,
            IN_ESC_STRING,
            IN_PREPROCESSOR,
            IN_PREPROCESSOR_DIRECTIVE,
            IN_CODE_BLOCK,
            IN_WORD,
            CLEAR_WORD,
            IN_CLASS,
            IN_CLASS_DECL,
            IN_CLASS_DECL_SPEC,
            IN_CLASS_ID,
            IN_CLASS_BLOCK,
            IN_CLASS_END,
            IN_CLASS_SPACE,
            IN_NAMESPACE,
            IN_NAMESPACE_ID,
            IN_NAMESPACE_BLOCK,
            IN_ENUM,
            IN_ENUM_ID,
            IN_ENUM_BLOCK,
            IN_ENUM_END,
            SET_TEMPLATE,
            IN_TEMPLATE,
            IN_TEMPLATE_DECL,
            IN_TYPEDEF,
            IN_MEMBER,
            IN_MEMBER_DECL,
            IN_MEMBER_ID,
            IN_ATTRIBUTE,
            IN_FUNCTION,
            IN_FUNCTION_BLOCK,
            IN_STATEMENT,
            CODE_BREAK
        };

        static bool IN_CODE(const FlagSet& flags);

        template <typename... T>
        static constexpr Block InfoBlock(size_t start, size_t end, T&&... args);

        void parse();

        boost::shared_ptr< Base<EncodingT> > mContentPtr;
        typename EncodingT::string_t mContent;

        boost::shared_ptr< Base<EncodingT> > mCodePtr;
        typename EncodingT::string_t mCode;

        std::vector<Block> mNoCode;     // String + Comment
        std::vector<Block> mComments;   // CppComment + CComment

        std::vector<Block> mLines;
        size_t mLineStart;
        void parseLine(size_t i, FlagSet& flags);

        std::vector<Block> mStrings;
        size_t mStringStart;
        void parseDblString(size_t i, FlagSet& flags);
        void parseSplString(size_t i, FlagSet& flags);

        std::vector<Block> mCppComments;
        size_t mCppCommentStart;
        void parseCppComment(size_t i, FlagSet& flags);

        std::vector<Block> mCComments;
        size_t mCCommentStart;
        void parseCComment(size_t i, FlagSet& flags);

        std::vector<Block> mPreprocessors;
        size_t mPreprocessorStart;
        typename EncodingT::string_t mPreprocessorName;
        void parsePreprocessor(size_t i, FlagSet& flags);

        std::vector<Block> mCodeBlocks;
        std::vector<size_t> mCodeBlockStart;
        void parseCodeBlock(size_t i, FlagSet& flags);

        void parseType(size_t i, FlagSet& flags);

        std::vector<Block> mComposition;
        std::vector<Block> mClass;
        std::vector<Block> mSpecifier;
        std::vector<Block> mStruct;
        std::vector<Block> mUnion;
        std::vector<size_t> mClassStart;
        std::vector<size_t> mSpecifierStart;
        std::vector<typename EncodingT::string_t> mClassName;
        std::vector<size_t> mClassBlock;
        std::vector<size_t> mType;
        std::vector<typename EncodingT::string_t> mSpecifierName;
        void parseClass(size_t i, FlagSet& flags);

        std::vector<Block> mNamespace;
        std::vector<size_t> mNamespaceStart;
        std::vector<typename EncodingT::string_t> mNamespaceName;
        std::vector<size_t> mNamespaceBlock;
        void parseNamespace(size_t i, FlagSet& flags);

        std::vector<Block> mEnum;
        size_t mEnumStart;
        typename EncodingT::string_t mEnumName;
        void parseEnum(size_t i, FlagSet& flags);

        std::vector<Block> mStatements;
        size_t mStatementStart;
        void parseStatement(size_t i, FlagSet& flags);

        size_t mWordStart;
        typename EncodingT::string_t mWord;
        void parseWord(size_t i, FlagSet& flags);

        size_t mTemplateDelcStart;
        std::vector<size_t> mTemplateStart;
        void parseTemplate(size_t i, FlagSet& flags);

        std::vector<Block> mFunctions;
        std::vector<Block> mAttributes;
        std::vector<size_t> mMemberStart;
        std::vector<bool> mIsFunction;
        std::vector<typename EncodingT::string_t> mMemberName;
        std::vector<size_t> mFunctionBlock;
        void parseMember(size_t i, FlagSet& flags);

        static constexpr size_t LINES_ID = 1U;
        static constexpr size_t STRINGS_ID = (1U << 2U);
        static constexpr size_t C_COMMENTS_ID = (1U << 3U);
        static constexpr size_t CPP_COMMENTS_ID = (1U << 4U);
        static constexpr size_t PREPROCESSORS_ID = (1U << 5U);
        static constexpr size_t CODE_BLOCKS_ID = (1U << 6U);
        static constexpr size_t CLASS_ID = (1U << 7U);
        static constexpr size_t CLASS_SPECIFIER_ID = (1U << 8U);
        static constexpr size_t NAMESPACE_ID = (1U << 9U);
        static constexpr size_t STRUCT_ID = (1U << 10U);
        static constexpr size_t ENUM_ID = (1U << 11U);
        static constexpr size_t FUNCTION_ID = (1U << 12U);
        static constexpr size_t ATTRIBUTE_ID = (1U << 13U);
        static constexpr size_t UNION_ID = (1U << 14U);
        static constexpr size_t STATEMENT_ID = (1U << 15U);
        static constexpr size_t COMPOSITION_ID = CLASS_ID + STRUCT_ID + UNION_ID;
        static constexpr size_t COMMENTS_ID = C_COMMENTS_ID + CPP_COMMENTS_ID;
        static constexpr size_t NO_CODE_ID = COMMENTS_ID + STRINGS_ID;
        static constexpr int NO_POS = -1;

        bool iterators(size_t blockId, std::vector<Block>::const_iterator& first, std::vector<Block>::const_iterator& last) const;

        long long find(size_t val, size_t blockId, Block& block) const;

        static typename EncodingT::string_t getNativeContent(const typename EncodingT::string_t& path);

	public:
        CPPParserInterpreter();

        virtual typename EncodingT::string_t toString() const;

        virtual boost::shared_ptr< Base<EncodingT> > clone() const;

        virtual typename EncodingT::string_t getClassName() const;

        virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

        FACTORY_PROTOTYPE1(getFileContent, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > getFileContent(const boost::shared_ptr< Base<EncodingT> >& path) const;

        FACTORY_PROTOTYPE1(parseFile, In< boost::shared_ptr< Base<EncodingT> > >)
        void parseFile(const boost::shared_ptr< Base<EncodingT> >& path);

        FACTORY_PROTOTYPE1(parse, In< boost::shared_ptr< Base<EncodingT> > >)
        void parse(const boost::shared_ptr< Base<EncodingT> >& content);

        boost::shared_ptr< Base<EncodingT> > getContent() const;

        boost::shared_ptr< Base<EncodingT> > getSourceCode() const;

        boost::shared_ptr< Base<EncodingT> > linesId() const;

        boost::shared_ptr< Base<EncodingT> > stringsId() const;

        boost::shared_ptr< Base<EncodingT> > CCommentsId() const;

        boost::shared_ptr< Base<EncodingT> > CppCommentsId() const;

        boost::shared_ptr< Base<EncodingT> > preprocessorsId() const;

        boost::shared_ptr< Base<EncodingT> > commentsId() const;

        boost::shared_ptr< Base<EncodingT> > noCodeId() const;

        boost::shared_ptr< Base<EncodingT> > codeBlockId() const;

        boost::shared_ptr< Base<EncodingT> > classId() const;

        boost::shared_ptr< Base<EncodingT> > classSpecifierId() const;

        boost::shared_ptr< Base<EncodingT> > namespaceId() const;

        boost::shared_ptr< Base<EncodingT> > structId() const;

        boost::shared_ptr< Base<EncodingT> > unionId() const;

        boost::shared_ptr< Base<EncodingT> > compositionId() const;

        boost::shared_ptr< Base<EncodingT> > enumId() const;

        boost::shared_ptr< Base<EncodingT> > functionId() const;

        boost::shared_ptr< Base<EncodingT> > attributeId() const;

        boost::shared_ptr< Base<EncodingT> > statementId() const;

        boost::shared_ptr< Base<EncodingT> > noPos() const;

        FACTORY_PROTOTYPE2(indexOf, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > indexOf(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(inRange, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > inRange(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(range, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > range(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(previous, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > previous(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE1(array, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > array(const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE1(size, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > size(const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(at, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > at(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(extract, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > extract(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(extractCode, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > extractCode(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(name, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > name(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE2(type, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > type(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const;

        FACTORY_PROTOTYPE4(include, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
        boost::shared_ptr< Base<EncodingT> > include(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId, const boost::shared_ptr< Base<EncodingT> >& origin, const boost::shared_ptr< Base<EncodingT> >& blockOrig) const;

		FACTORY_BEGIN_REGISTER
            CLASS_KEY_REGISTER  ( CPPParserInterpreter, C("CPPParser") );
            METHOD_KEY_REGISTER1( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, getFileContent, const_t, C("CPPParser::FileContent") );
            METHOD_KEY_REGISTER1( CPPParserInterpreter, void, parseFile, no_const_t, C("CPPParser::ParseFile") );
            METHOD_KEY_REGISTER1( CPPParserInterpreter, void, parse, no_const_t, C("CPPParser::Parse") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, getContent, const_t, C("CPPParser::Content") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, getSourceCode, const_t, C("CPPParser::SourceCode") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, linesId, const_t, C("CPPParser::Lines") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, stringsId, const_t, C("CPPParser::Strings") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, CCommentsId, const_t, C("CPPParser::CComments") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, CppCommentsId, const_t, C("CPPParser::CppComments") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, preprocessorsId, const_t, C("CPPParser::Preprocessors") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, commentsId, const_t, C("CPPParser::Comments") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, noCodeId, const_t, C("CPPParser::NoCode") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, codeBlockId, const_t, C("CPPParser::CodeBlock") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, classId, const_t, C("CPPParser::Class") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, structId, const_t, C("CPPParser::Struct") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, unionId, const_t, C("CPPParser::Union") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, classSpecifierId, const_t, C("CPPParser::ClassSpecifier") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, namespaceId, const_t, C("CPPParser::Namespace") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, compositionId, const_t, C("CPPParser::Composition") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, enumId, const_t, C("CPPParser::Enum") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, statementId, const_t, C("CPPParser::Statement") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, functionId, const_t, C("CPPParser::Function") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, attributeId, const_t, C("CPPParser::Attribute") );
            METHOD_KEY_REGISTER ( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, noPos, const_t, C("CPPParser::NoPos") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, indexOf, const_t, C("CPPParser::IndexOf") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, inRange, const_t, C("CPPParser::InRange") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, range, const_t, C("CPPParser::Range") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, previous, const_t, C("CPPParser::Previous") );
            METHOD_KEY_REGISTER1( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, array, const_t, C("CPPParser::Array") );
            METHOD_KEY_REGISTER1( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, size, const_t, C("CPPParser::Size") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, extract, const_t, C("CPPParser::Extract") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, extractCode, const_t, C("CPPParser::ExtractCode") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, at, const_t, C("CPPParser::At") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, name, const_t, C("CPPParser::Name") );
            METHOD_KEY_REGISTER2( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, type, const_t, C("CPPParser::Type") );
            METHOD_KEY_REGISTER4( CPPParserInterpreter, boost::shared_ptr< Base<EncodingT> >, include, const_t, C("CPPParser::Include") );
		FACTORY_END_REGISTER

		FACTORY_BEGIN_UNREGISTER
            CLASS_KEY_UNREGISTER  ( C("CPPParser") );
            METHOD_KEY_UNREGISTER1( C("CPPParser::FileContent") );
            METHOD_KEY_UNREGISTER1( C("CPPParser::ParseFile") );
            METHOD_KEY_UNREGISTER1( C("CPPParser::Parse") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Content") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::SourceCode") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Lines") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Strings") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::CComments") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::CppComments") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Preprocessors") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Comments") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::NoCode") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::CodeBlock") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Class") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Struct") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Union") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Composition") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Namespace") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::ClassSpecifier") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Enum") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Statement") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Function") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::Attribute") );
            METHOD_KEY_UNREGISTER ( C("CPPParser::NoPos") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::IndexOf") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::InRange") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::Range") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::Previous") );
            METHOD_KEY_UNREGISTER1( C("CPPParser::Array") );
            METHOD_KEY_UNREGISTER1( C("CPPParser::Size") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::Extract") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::ExtractCode") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::At") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::Name") );
            METHOD_KEY_UNREGISTER2( C("CPPParser::Type") );
            METHOD_KEY_UNREGISTER4( C("CPPParser::Include") );
		FACTORY_END_UNREGISTER
	};

NAMESPACE_END

#undef A
#undef C
#include "CPPParserInterpreter_impl.hpp"

#endif
