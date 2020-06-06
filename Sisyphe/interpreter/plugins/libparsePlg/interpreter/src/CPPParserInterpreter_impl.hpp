/*
 * CPPParserInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#include <fstream>
#include <algorithm>
#include <type_traits>
#include <cctype>
#include "utf16BE_codecvt.hpp"
#include "utf16LE_codecvt.hpp"
#include "utf8_codecvt.hpp"
#include "iso_8859_15_codecvt.hpp"
#include "Numeric.hpp"
#include "String.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
bool CPPParserInterpreter<EncodingT>::IN_CODE(const FlagSet& flags)
{
    return !flags_test(flags, FLAGS::IN_NO_CODE) || flags_test(flags, FLAGS::CODE_BREAK);
}

template <class EncodingT>
template <typename... T>
ParserBlock CPPParserInterpreter<EncodingT>::InfoBlock(size_t start, size_t end, T&&... args)
{
    return ParserBlock(start, end, ParserInformation<EncodingT>(std::forward<T>(args)...));
}

template <class EncodingT>
typename EncodingT::string_t CPPParserInterpreter<EncodingT>::getNativeContent(const typename EncodingT::string_t& path)
{
    typename EncodingT::string_t content;
    std::ifstream in_file(A(path).c_str(), ios::binary);
    if (in_file.is_open())
    {
        char bom[3] = {0, 0, 0};
        in_file.read(bom, 3);
        in_file.close();
        std::codecvt<ucs::char_t, char, std::mbstate_t>* codecvt_facet = NULL;
        size_t offset_bom = 0U;
        if (0xEF == static_cast<unsigned char>(bom[0]) &&
            0xBB == static_cast<unsigned char>(bom[1]) &&
            0xBF == static_cast<unsigned char>(bom[2]))
        {
            codecvt_facet = new utf8_codecvt_facet;
            offset_bom = 3U;
        }
        else if (0xFF == static_cast<unsigned char>(bom[0]) &&
                 0xFE == static_cast<unsigned char>(bom[1]))
        {
            codecvt_facet = new utf16LE_codecvt_facet;
            offset_bom = 2U;
        }
        else if (0xFE == static_cast<unsigned char>(bom[0]) &&
                 0xFF == static_cast<unsigned char>(bom[1]))
        {
            codecvt_facet = new utf16BE_codecvt_facet;
            offset_bom = 2U;
        }
        else
        {
            codecvt_facet = new iso_8859_15_codecvt_facet;
        }

        std::basic_ifstream<ucs::char_t> file(A(path).c_str(), ios::binary);
        if (file.is_open())
        {
            std::locale old_locale;
            std::locale new_locale(old_locale,codecvt_facet);
            file.imbue(new_locale);
            // get length of file:
            file.seekg (0, ios::end);
            size_t length = static_cast<size_t>(file.tellg()) - offset_bom;
            file.clear();
            file.seekg(0, ios::beg);
            file.seekg(offset_bom);
            // allocate memory
            content.resize(length);
            // read data as a block:
            file.read(&content[0], length);
            content.erase(std::find(content.begin(), content.end(), '\0'), content.end());
            content.shrink_to_fit();
        }
    }
    return content;
}

template <typename E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}

template <typename E>
constexpr bool flags_test(const FlagSet& flags, E e)
{
    return (flags & (static_cast<FlagSet>(1) << to_underlying(e))) != static_cast<FlagSet>(0);
}

template <typename E>
constexpr void flags_set(FlagSet& flags, E e)
{
    flags |= (static_cast<FlagSet>(1) << to_underlying(e));
}

template <typename E>
constexpr void flags_reset(FlagSet& flags, E e)
{
    flags &= ~(static_cast<FlagSet>(1) << to_underlying(e));
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parse()
{
    size_t i = 0;
    size_t end = mContent.size();
    FlagSet flags = static_cast<FlagSet>(0);
    mLineStart = i;
    mLiteralStart = i;
    mStringStart = i;
    mCppCommentStart = i;
    mCCommentStart = i;
    mPreprocessorStart = i;
    mEnumStart = i;
    mStatementStart = i;
    mWordStart = i;
    mTemplateDelcStart = i;
    mLiterals.clear();
    mLines.clear();
    mNoCode.clear();
    mStrings.clear();
    mComments.clear();
    mCppComments.clear();
    mCComments.clear();
    mPreprocessors.clear();
    mCodeBlocks.clear();
    mClass.clear();
    mSpecifier.clear();
    mNamespace.clear();
    mStruct.clear();
    mUnion.clear();
    mComposition.clear();
    mEnum.clear();
    mFunctions.clear();
    mAttributes.clear();
    mStatements.clear();
    mCode.clear();
    mCode.reserve(mContent.size());
    while (i <= end)
    {
        if (flags_test(flags, FLAGS::CODE_BREAK))
        {
            flags_reset(flags, FLAGS::CODE_BREAK);
        }
        parseLine(i, flags);
        parseCppComment(i, flags);
        parseCComment(i, flags);
        parseDblString(i, flags);
        parseSplString(i, flags);
        parseWord(i, flags);
        parseLiteral(i, flags);
        parsePreprocessor(i, flags);
        parseCodeBlock(i, flags);
        parseType(i, flags);
        parseTemplate(i, flags);
        parseNamespace(i, flags);
        parseEnum(i, flags);
        parseClass(i, flags);
        parseMember(i, flags);
        parseStatement(i, flags);
        if (flags_test(flags, FLAGS::IN_NO_CODE) &&
            (isspace(mContent[i]) == 0) &&
            ((!flags_test(flags, FLAGS::IN_DBL_STRING)) || flags_test(flags, FLAGS::IN_ESC_STRING) || (mContent[i] != '"')) &&
            ((!flags_test(flags, FLAGS::IN_SMPL_STRING)) || flags_test(flags, FLAGS::IN_ESC_STRING) || (mContent[i] != '\'')))
        {
            mCode.append(1U, ' ');
        }
        else
        {
            mCode.append(1U, mContent[i]);
        }
        ++i;
    }
    mCodePtr =  boost::make_shared< String<EncodingT> >(mCode);
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseLine(size_t i, FlagSet&)
{
    if (i >= mContent.size())
    {
        mLines.push_back(ParserBlock(mLineStart, i));
    }
    else
    {
        if ((i > 0U) && (mContent[i - 1] == '\n'))
        {
            mLines.push_back(ParserBlock(mLineStart, i));
            mLineStart = i;
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseDblString(size_t i, FlagSet& flags)
{
    if (flags_test(flags, FLAGS::IN_DBL_STRING))
    {
        if (i > mStringStart + 1U)
        {
            if (!flags_test(flags, FLAGS::IN_ESC_STRING))
            {
                if (mContent[i - 1] == '"')
                {
                    mStrings.push_back(ParserBlock(mStringStart, i));
                    mNoCode.push_back(ParserBlock(mStringStart, i));
                    flags_reset(flags, FLAGS::IN_DBL_STRING);
                    flags_reset(flags, FLAGS::IN_STRING);
                    flags_reset(flags, FLAGS::IN_NO_CODE);
                }
                else if (mContent[i - 1] == '\\')
                {
                    flags_set(flags, FLAGS::IN_ESC_STRING);
                }
            }
            else
            {
                flags_reset(flags, FLAGS::IN_ESC_STRING);
            }
        }
    }
    if (IN_CODE(flags))
    {
        if (mContent[i] == '"')
        {
            mStringStart = i;
            flags_set(flags, FLAGS::IN_DBL_STRING);
            flags_set(flags, FLAGS::IN_STRING);
            flags_set(flags, FLAGS::IN_NO_CODE);
            flags_set(flags, FLAGS::CODE_BREAK);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseSplString(size_t i, FlagSet& flags)
{
    if (flags_test(flags, FLAGS::IN_SMPL_STRING))
    {
        if (i > mStringStart + 1U)
        {
            if (!flags_test(flags, FLAGS::IN_ESC_STRING))
            {
                if (mContent[i - 1] == '\'')
                {
                    mStrings.push_back(ParserBlock(mStringStart, i));
                    mNoCode.push_back(ParserBlock(mStringStart, i));
                    flags_reset(flags, FLAGS::IN_SMPL_STRING);
                    flags_reset(flags, FLAGS::IN_STRING);
                    flags_reset(flags, FLAGS::IN_NO_CODE);
                }
                else if (mContent[i - 1] == '\\')
                {
                    flags_set(flags, FLAGS::IN_ESC_STRING);
                }
            }
            else
            {
                flags_reset(flags, FLAGS::IN_ESC_STRING);
            }
        }
    }
    if (IN_CODE(flags))
    {
        if (mContent[i] == '\'')
        {
            mStringStart = i;
            flags_set(flags, FLAGS::IN_SMPL_STRING);
            flags_set(flags, FLAGS::IN_STRING);
            flags_set(flags, FLAGS::IN_NO_CODE);
            flags_set(flags, FLAGS::CODE_BREAK);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseCppComment(size_t i, FlagSet& flags)
{
    if (flags_test(flags, FLAGS::IN_CPP_COMMENT))
    {
        if (((i > 0U) && (mContent[i - 1] == '\n')) ||
                (i >= mContent.size()))
        {
            mCppComments.push_back(ParserBlock(mCppCommentStart, i));
            mComments.push_back(ParserBlock(mCppCommentStart, i));
            mNoCode.push_back(ParserBlock(mCppCommentStart, i));
            flags_reset(flags, FLAGS::IN_CPP_COMMENT);
            flags_reset(flags, FLAGS::IN_COMMENT);
            flags_reset(flags, FLAGS::IN_NO_CODE);
        }
    }
    if (IN_CODE(flags))
    {
        if (((i + 1) < mContent.size()) && (mContent[i] == '/') && (mContent[i + 1] == '/'))
        {
            mCppCommentStart = i;
            flags_set(flags, FLAGS::IN_CPP_COMMENT);
            flags_set(flags, FLAGS::IN_COMMENT);
            flags_set(flags, FLAGS::IN_NO_CODE);
            flags_set(flags, FLAGS::CODE_BREAK);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseCComment(size_t i, FlagSet& flags)
{
    if (flags_test(flags, FLAGS::IN_C_COMMENT))
    {
        if ((i > 1U) && (mContent[i - 2] == '*') && (mContent[i - 1] == '/'))
        {
            mCComments.push_back(ParserBlock(mCCommentStart, i));
            mComments.push_back(ParserBlock(mCCommentStart, i));
            mNoCode.push_back(ParserBlock(mCCommentStart, i));
            flags_reset(flags, FLAGS::IN_C_COMMENT);
            flags_reset(flags, FLAGS::IN_COMMENT);
            flags_reset(flags, FLAGS::IN_NO_CODE);
        }
    }
    if (IN_CODE(flags))
    {
        if (((i + 1) < mContent.size()) && (mContent[i] == '/') && (mContent[i + 1] == '*'))
        {
            mCCommentStart = i;
            flags_set(flags, FLAGS::IN_C_COMMENT);
            flags_set(flags, FLAGS::IN_COMMENT);
            flags_set(flags, FLAGS::IN_NO_CODE);
            flags_set(flags, FLAGS::CODE_BREAK);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseLiteral(size_t i, FlagSet& flags)
{
    if (flags_test(flags, FLAGS::IN_LITERAL))
    {
        if ((((ispunct(mContent[i]) != 0) || (isspace(mContent[i]) != 0)) &&
            (mContent[i] != '.') && (((i > 0U) && (mContent[i-1] != 'e') && (mContent[i-1] != 'E')) || ((mContent[i] != '+') && (mContent[i] != '-')))) ||
            (i >= mContent.size()))
        {
            mLiterals.push_back(ParserBlock(mLiteralStart, i));
            flags_reset(flags, FLAGS::IN_LITERAL);
        }
    }
    if (IN_CODE(flags))
    {
        if (!flags_test(flags, FLAGS::IN_LITERAL) && 
            ((i > 0U) && (((ispunct(mContent[i-1]) != 0) && (mContent[i-1] != '_')) || (isspace(mContent[i-1]) != 0))) &&
            ((isdigit(mContent[i]) != 0) || (((i + 1) < mContent.size()) && (mContent[i] == '.') && (isdigit(mContent[i + 1]) != 0))))
        {
            mLiteralStart = i;
            flags_set(flags, FLAGS::IN_LITERAL);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parsePreprocessor(size_t i, FlagSet& flags)
{
    if (flags_test(flags, FLAGS::IN_PREPROCESSOR))
    {
        if (((i > 1U) && (mContent[i - 1] == '\n') &&
                (mContent[i - 2] != '\\') &&
                ((mContent[i - 2] != '\r') || ((i > 2U) && (mContent[i - 3] != '\\')))) ||
              (i >= mContent.size()))
        {
            mPreprocessors.push_back(InfoBlock(mPreprocessorStart, i, mPreprocessorName));
            flags_reset(flags, FLAGS::IN_PREPROCESSOR);
        }
        if (flags_test(flags, FLAGS::IN_WORD))
        {
            if (mPreprocessorName.empty())
            {
                flags_set(flags, FLAGS::IN_PREPROCESSOR_DIRECTIVE);
            }
        }
        else
        {
            if (flags_test(flags, FLAGS::IN_PREPROCESSOR_DIRECTIVE))
            {
                mPreprocessorName = mWord;
                flags_reset(flags, FLAGS::IN_PREPROCESSOR_DIRECTIVE);
            }
        }
    }
    if (IN_CODE(flags))
    {
        if ((mContent[i] == '#') &&
                !flags_test(flags, FLAGS::IN_PREPROCESSOR))
        {
            mPreprocessorStart = i;
            mPreprocessorName.clear();
            flags_set(flags, FLAGS::IN_PREPROCESSOR);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseCodeBlock(size_t i, FlagSet& flags)
{
    if (IN_CODE(flags) &&
        !flags_test(flags, FLAGS::IN_PREPROCESSOR))
    {
        if (flags_test(flags, FLAGS::IN_CODE_BLOCK))
        {
            if ((i > 0U) && (mContent[i - 1] == '}'))
            {
                mCodeBlocks.push_back(ParserBlock(mCodeBlockStart.back(), i));
                mCodeBlockStart.pop_back();
                if (mCodeBlockStart.empty())
                {
                    flags_reset(flags, FLAGS::IN_CODE_BLOCK);
                }
            }
        }
        if (mContent[i] == '{')
        {
            mCodeBlockStart.push_back(i);
            flags_set(flags, FLAGS::IN_CODE_BLOCK);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseClass(size_t i, FlagSet& flags)
{
    static const typename EncodingT::string_t CLASS_KEYWORD = UCS("class");
    static const typename EncodingT::string_t STRUCT_KEYWORD = UCS("struct");
    static const typename EncodingT::string_t UNION_KEYWORD = UCS("union");
    static const typename EncodingT::string_t PRIVATE_KEYWORD = UCS("private");
    static const typename EncodingT::string_t PROTECTED_KEYWORD = UCS("protected");
    static const typename EncodingT::string_t PUBLIC_KEYWORD = UCS("public");
    static const std::set<typename EncodingT::string_t> SPEC_KEYWORDS = {
            UCS("alignas"), UCS("__declspec"), UCS("__attribute__")
    };
    if (flags_test(flags, FLAGS::IN_CLASS_DECL))
    {
        if (!flags_test(flags, FLAGS::IN_WORD) &&
                (SPEC_KEYWORDS.count(mWord) == 1U))
        {
            flags_set(flags, FLAGS::IN_CLASS_DECL_SPEC);
            flags_set(flags, FLAGS::CLEAR_WORD);
        }
    }
    else
    {
        if (!flags_test(flags, FLAGS::IN_PREPROCESSOR))
        {
            if (flags_test(flags, FLAGS::IN_CLASS_BLOCK))
            {
                if (!flags_test(flags, FLAGS::IN_WORD) &&
                     ((mWord == PRIVATE_KEYWORD) || (mWord == PROTECTED_KEYWORD) || (mWord == PUBLIC_KEYWORD)) &&
                     (!mType.empty() && mType.back() == CLASS_ID))
                {
                     mSpecifier.push_back(InfoBlock(mSpecifierStart.back(), mWordStart, mSpecifierName.back()));
                     mSpecifierStart.pop_back();
                     mSpecifierName.pop_back();
                     mSpecifierStart.push_back(i);
                     mSpecifierName.push_back(mWord);
                     flags_set(flags, FLAGS::CLEAR_WORD);
                }
            }
            if (!flags_test(flags, FLAGS::IN_ENUM) &&
                !flags_test(flags, FLAGS::IN_TEMPLATE))
            {
                if (!flags_test(flags, FLAGS::IN_WORD) &&
                    ((mWord == CLASS_KEYWORD) || (mWord == STRUCT_KEYWORD) || (mWord == UNION_KEYWORD)))
                {
                    if (mWord == CLASS_KEYWORD)
                    {
                        mType.push_back(CLASS_ID);
                    }
                    else if (mWord == STRUCT_KEYWORD)
                    {
                        mType.push_back(STRUCT_ID);
                    }
                    else
                    {
                        mType.push_back(UNION_ID);
                    }
                    if (flags_test(flags, FLAGS::IN_TEMPLATE_DECL))
                    {
                        mClassStart.push_back(mTemplateDelcStart);
                        flags_reset(flags, FLAGS::IN_TEMPLATE_DECL);
                    }
                    else
                    {
                        mClassStart.push_back(mWordStart);
                    }
                    flags_set(flags, FLAGS::CLEAR_WORD);
                    flags_set(flags, FLAGS::IN_CLASS);
                    flags_set(flags, FLAGS::IN_CLASS_DECL);
                    flags_set(flags, FLAGS::IN_CLASS_ID);
                }
            }
        }
    }
    if (IN_CODE(flags))
    {
        if (flags_test(flags, FLAGS::IN_CLASS_END))
        {
            if ((i > 0U) && (mContent[i - 1] == ';'))
            {
                flags_reset(flags, FLAGS::IN_CLASS_END);
                size_t start = mClassStart.back();
                typename EncodingT::string_t name = mClassName.back();
                size_t type = mType.back();
                mClassStart.pop_back();
                mClassName.pop_back();
                mType.pop_back();
                mComposition.push_back(InfoBlock(start, i, name, type));
                if (type == CLASS_ID)
                {
                    mClass.push_back(InfoBlock(start, i, name));
                }
                else if (type == STRUCT_ID)
                {
                    mStruct.push_back(InfoBlock(start, i, name));
                }
                else
                {
                    mUnion.push_back(InfoBlock(start, i, name));
                }
                if (mClassStart.empty())
                {
                    flags_reset(flags, FLAGS::IN_CLASS);
                }
            }
        }
        else if (flags_test(flags, FLAGS::IN_CLASS_DECL))
        {
            if (flags_test(flags, FLAGS::IN_CLASS_DECL_SPEC))
            {
                if ((i > 0U) && (mContent[i - 1] == ')') && (mContent[i] != ')'))
                {
                    flags_reset(flags, FLAGS::IN_CLASS_DECL_SPEC);
                }
            }
            if ((((mContent[i] == '(') || (mContent[i] == ')')) && !flags_test(flags, FLAGS::IN_CLASS_DECL_SPEC)) ||
                (mContent[i] == ';') ||
                (mContent[i] == '='))
            {
                mType.pop_back();
                mClassStart.pop_back();
                if (!flags_test(flags, FLAGS::IN_CLASS_ID))
                {
                    mClassName.pop_back();
                }
                else
                {
                    flags_reset(flags, FLAGS::IN_CLASS_ID);
                }
                flags_reset(flags, FLAGS::IN_CLASS_DECL);
                if (mClassStart.empty())
                {
                    flags_reset(flags, FLAGS::IN_CLASS);
                }
            }
            else
            {
                if (flags_test(flags, FLAGS::IN_CLASS_ID) &&
                    !flags_test(flags, FLAGS::IN_TEMPLATE))
                {
                    if (mContent[i] == '<')
                    {
                        mClassName.push_back(mWord);
                        flags_reset(flags, FLAGS::IN_CLASS_ID);
                        flags_set(flags, FLAGS::SET_TEMPLATE);
                    }
                    else if (mContent[i] == ':')
                    {
                        mClassName.push_back(mWord);
                        flags_reset(flags, FLAGS::IN_CLASS_ID);
                    }
                }
                if (mContent[i] == '{')
                {
                    if (flags_test(flags, FLAGS::IN_CLASS_ID))
                    {
                        mClassName.push_back(mWord);
                        flags_reset(flags, FLAGS::IN_CLASS_ID);
                    }
                    mClassBlock.push_back(i);
                    if (!mType.empty() && mType.back() == CLASS_ID)
                    {
                        mSpecifierStart.push_back(i + 1);
                        mSpecifierName.push_back(UCS("private"));
                    }
                    flags_set(flags, FLAGS::IN_CLASS_BLOCK);
                    flags_set(flags, FLAGS::IN_CLASS_SPACE);
                    flags_reset(flags, FLAGS::IN_CLASS_DECL);
                }
            }
        }
        else if (flags_test(flags, FLAGS::IN_CLASS_BLOCK))
        {
            if (!mCodeBlocks.empty() &&
                !mClassBlock.empty() &&
                (mClassBlock.back() == mCodeBlocks.back().Start()))
            {
                flags_set(flags, FLAGS::IN_CLASS_END);
                mClassBlock.pop_back();
                if (mClassBlock.empty())
                {
                    flags_reset(flags, FLAGS::IN_CLASS_SPACE);
                    flags_reset(flags, FLAGS::IN_CLASS_BLOCK);
                }
                if (!mType.empty() && mType.back() == CLASS_ID)
                {
                    mSpecifier.push_back(InfoBlock(mSpecifierStart.back(), i, mSpecifierName.back()));
                    mSpecifierStart.pop_back();
                    mSpecifierName.pop_back();
                }
            }
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseNamespace(size_t i, FlagSet& flags)
{
    static const typename EncodingT::string_t NAMESPACE_KEYWORD = UCS("namespace");
    if (!flags_test(flags, FLAGS::IN_NAMESPACE_ID))
    {
        if (!flags_test(flags, FLAGS::IN_PREPROCESSOR)  && !flags_test(flags, FLAGS::IN_TYPEDEF))
        {
            if (!flags_test(flags, FLAGS::IN_WORD) && (mWord == NAMESPACE_KEYWORD))
            {
                mNamespaceStart.push_back(mWordStart);
                flags_set(flags, FLAGS::CLEAR_WORD);
                flags_set(flags, FLAGS::IN_NAMESPACE);
                flags_set(flags, FLAGS::IN_NAMESPACE_ID);
            }
        }
    }
    if (IN_CODE(flags))
    {
        if (flags_test(flags, FLAGS::IN_NAMESPACE_ID))
        {
            if ((i > 0U) && (mContent[i - 1] == ';'))
            {
                flags_reset(flags, FLAGS::IN_NAMESPACE_ID);
                flags_reset(flags, FLAGS::IN_NAMESPACE);
            }
            if (mContent[i] == '{')
            {
                mNamespaceName.push_back(mWord);
                flags_reset(flags, FLAGS::IN_NAMESPACE_ID);
                mNamespaceBlock.push_back(i);
                flags_set(flags, FLAGS::IN_NAMESPACE_BLOCK);
            }
        }
        else if (flags_test(flags, FLAGS::IN_NAMESPACE_BLOCK))
        {
            if (!mCodeBlocks.empty() &&
                !mNamespaceBlock.empty() &&
                (mNamespaceBlock.back() == mCodeBlocks.back().Start()))
            {
                mNamespaceBlock.pop_back();
                if (mNamespaceBlock.empty())
                {
                    flags_reset(flags, FLAGS::IN_NAMESPACE_BLOCK);
                }
                size_t start = mNamespaceStart.back();
                typename EncodingT::string_t name = mNamespaceName.back();
                mNamespaceStart.pop_back();
                mNamespaceName.pop_back();
                mNamespace.push_back(InfoBlock(start, i, name));
                mComposition.push_back(InfoBlock(start, i, name, NAMESPACE_ID));
                if (mNamespaceStart.empty())
                {
                    flags_reset(flags, FLAGS::IN_NAMESPACE);
                }
            }
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseEnum(size_t i, FlagSet& flags)
{
    static const typename EncodingT::string_t ENUM_KEYWORD = UCS("enum");
    if (!flags_test(flags, FLAGS::IN_ENUM))
    {
        if (!flags_test(flags, FLAGS::IN_PREPROCESSOR))
        {
            if (!flags_test(flags, FLAGS::IN_WORD) && (mWord == ENUM_KEYWORD))
            {
                mEnumStart = mWordStart;
                flags_set(flags, FLAGS::CLEAR_WORD);
                flags_set(flags, FLAGS::IN_ENUM);
                flags_set(flags, FLAGS::IN_ENUM_ID);
            }
        }
    }
    if (IN_CODE(flags))
    {
        if (flags_test(flags, FLAGS::IN_ENUM_END))
        {
            if ((i > 0U) && (mContent[i - 1] == ';'))
            {
                flags_reset(flags, FLAGS::IN_ENUM_END);
                mEnum.push_back(InfoBlock(mEnumStart, i, mEnumName));
                mComposition.push_back(InfoBlock(mEnumStart, i, mEnumName, ENUM_ID));
                flags_reset(flags, FLAGS::IN_ENUM);
            }
        }
        else if (!flags_test(flags, FLAGS::IN_ENUM_BLOCK))
        {
            if (flags_test(flags, FLAGS::IN_ENUM_ID))
            {
                if ((mContent[i] == '(') ||
                    (mContent[i] == ')') ||
                    (mContent[i] == ';') ||
                    (mContent[i] == '='))
                {
                    flags_reset(flags, FLAGS::IN_ENUM_ID);
                    flags_reset(flags, FLAGS::IN_ENUM);
                }
                if (mContent[i] == ':')
                {
                    mEnumName = mWord;
                    flags_reset(flags, FLAGS::IN_ENUM_ID);
                }
            }
            if (flags_test(flags, FLAGS::IN_ENUM))
            {
                 if (mContent[i] == '{')
                 {
                     if (flags_test(flags, FLAGS::IN_ENUM_ID))
                     {
                         mEnumName = mWord;
                         flags_reset(flags, FLAGS::IN_ENUM_ID);
                     }
                     flags_set(flags, FLAGS::IN_ENUM_BLOCK);
                 }
            }
        }
        else if (flags_test(flags, FLAGS::IN_ENUM_BLOCK))
        {
            if ((i > 0U) && (mContent[i - 1] == '}'))
            {
                flags_set(flags, FLAGS::IN_ENUM_END);
                flags_reset(flags, FLAGS::IN_ENUM_BLOCK);
            }
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseType(size_t i, FlagSet& flags)
{
    static const typename EncodingT::string_t TYPEDEF_KEYWORD = UCS("typedef");
    static const typename EncodingT::string_t USING_KEYWORD = UCS("using");
    if (!flags_test(flags, FLAGS::IN_TYPEDEF))
    {
        if (!flags_test(flags, FLAGS::IN_PREPROCESSOR))
        {
            if (!flags_test(flags, FLAGS::IN_WORD) && ((mWord == TYPEDEF_KEYWORD) || (mWord == USING_KEYWORD)))
            {
                flags_set(flags, FLAGS::CLEAR_WORD);
                flags_set(flags, FLAGS::IN_TYPEDEF);
            }
        }
    }
    if (IN_CODE(flags))
    {
        if (flags_test(flags, FLAGS::IN_TYPEDEF))
        {
            if ((i > 0U) && (mContent[i - 1] == ';'))
            {
                flags_reset(flags, FLAGS::IN_TYPEDEF);
            }
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseMember(size_t i, FlagSet& flags)
{
    static const std::set<typename EncodingT::string_t> KEYWORDS = {
            UCS("typedef"), UCS("using"),
            UCS("namespace"),
            UCS("public"), UCS("protected"), UCS("private"),
            UCS("alignas"), UCS("__declspec"), UCS("explicit")
    };
    if (flags_test(flags, FLAGS::IN_MEMBER_DECL))
    {
        if ((!flags_test(flags, FLAGS::IN_WORD) && (KEYWORDS.count(mWord) == 1U)) ||
            (IN_CODE(flags) && (mContent[i] == '{') && (mIsFunction.empty() || !mIsFunction.back())) ||
            (!mClassBlock.empty() && (mClassBlock.back() == i)) ||
            (!mNamespaceBlock.empty() && (mNamespaceBlock.back() == i)) ||
            (flags_test(flags, FLAGS::IN_ENUM_BLOCK)) ||
            (flags_test(flags, FLAGS::IN_PREPROCESSOR)))
        {
            flags_reset(flags, FLAGS::IN_MEMBER_ID);
            flags_reset(flags, FLAGS::IN_ATTRIBUTE);
            flags_reset(flags, FLAGS::IN_MEMBER_DECL);
            flags_reset(flags, FLAGS::IN_FUNCTION_INIT);
            flags_reset(flags, FLAGS::IN_FUNCTION_SPACE);
            flags_reset(flags, FLAGS::IN_FUNCTION_PARAM);
            mMemberStart.pop_back();
            mIsFunction.pop_back();
            if (mMemberStart.empty())
            {
                flags_reset(flags, FLAGS::IN_MEMBER);
                flags_reset(flags, FLAGS::IN_FUNCTION);
            }
            if (flags_test(flags, FLAGS::IN_CLASS_BLOCK))
            {
                flags_set(flags, FLAGS::IN_CLASS_SPACE);
            }
        }
    }
    if (IN_CODE(flags))
    {
        if (flags_test(flags, FLAGS::IN_FUNCTION_BLOCK))
        {
            if (!mCodeBlocks.empty() &&
                !mFunctionBlock.empty() &&
                (mFunctionBlock.back() == mCodeBlocks.back().Start()))
            {
                size_t start = mMemberStart.back();
                typename EncodingT::string_t name = mMemberName.back();
                mFunctionBlock.pop_back();
                mIsFunction.pop_back();
                mMemberStart.pop_back();
                mMemberName.pop_back();
                mFunctions.push_back(InfoBlock(start, i, name));
                mComposition.push_back(InfoBlock(start, i, name, FUNCTION_ID));
                if (mMemberStart.empty())
                {
                    flags_reset(flags, FLAGS::IN_FUNCTION_BLOCK);
                    flags_reset(flags, FLAGS::IN_FUNCTION);
                    flags_reset(flags, FLAGS::IN_MEMBER);
                }
                if (flags_test(flags, FLAGS::IN_CLASS_BLOCK))
                {
                    flags_set(flags, FLAGS::IN_CLASS_SPACE);
                }
            }
        }
        if (flags_test(flags, FLAGS::IN_MEMBER_DECL))
        {
            if (!flags_test(flags, FLAGS::IN_TEMPLATE))
            {
                if ((i > 0U) && (mContent[i - 1] == ';'))
                {
                    if (flags_test(flags, FLAGS::IN_MEMBER_ID))
                    {
                        mMemberName.push_back(mWord);
                        flags_reset(flags, FLAGS::IN_MEMBER_ID);
                    }
                    size_t start = mMemberStart.back();
                    bool isFunction = mIsFunction.back();
                    typename EncodingT::string_t name = mMemberName.back();
                    mMemberStart.pop_back();
                    mIsFunction.pop_back();
                    mMemberName.pop_back();
                    if (isFunction)
                    {
                        mFunctions.push_back(InfoBlock(start, i, name));
                        mComposition.push_back(InfoBlock(start, i, name, FUNCTION_ID));
                        if (mMemberStart.empty())
                        {
                            flags_reset(flags, FLAGS::IN_FUNCTION);
                        }
                    }
                    else
                    {
                        mAttributes.push_back(InfoBlock(start, i, name));
                        mComposition.push_back(InfoBlock(start, i, name, ATTRIBUTE_ID));
                    }
                    flags_reset(flags, FLAGS::IN_MEMBER_DECL);
                    flags_reset(flags, FLAGS::IN_ATTRIBUTE);
                    flags_reset(flags, FLAGS::IN_FUNCTION_INIT);
                    flags_reset(flags, FLAGS::IN_FUNCTION_SPACE);
                    flags_reset(flags, FLAGS::IN_FUNCTION_PARAM);
                    if (mMemberStart.empty())
                    {
                        flags_reset(flags, FLAGS::IN_MEMBER);
                    }
                    if (flags_test(flags, FLAGS::IN_CLASS_BLOCK))
                    {
                        flags_set(flags, FLAGS::IN_CLASS_SPACE);
                    }
                }
                else if ((mContent[i] == '(')
                         && !flags_test(flags, FLAGS::IN_ATTRIBUTE)
                         && !flags_test(flags, FLAGS::IN_FUNCTION_PARAM)
                         && !flags_test(flags, FLAGS::IN_FUNCTION_SPACE)
                         && !flags_test(flags, FLAGS::IN_FUNCTION_INIT))
                {
                    if (flags_test(flags, FLAGS::IN_TEMPLATE_DECL))
                    {
                        mMemberStart.back() = mTemplateDelcStart;
                        flags_reset(flags, FLAGS::IN_TEMPLATE_DECL);
                    }
                    if (flags_test(flags, FLAGS::IN_MEMBER_ID))
                    {
                        if (mContent[i - mWord.size() - 1] == '~')
                        {
                            mWord.insert(0, UCS("~"));
                        }
                        mMemberName.push_back(mWord);
                        flags_reset(flags, FLAGS::IN_MEMBER_ID);
                    }
                    mIsFunction.back() = true;
                    flags_reset(flags, FLAGS::IN_ATTRIBUTE);
                    flags_set(flags, FLAGS::IN_FUNCTION);
                    mFctParamParenth = 1U;
                    flags_set(flags, FLAGS::IN_FUNCTION_PARAM);
                }
                else if ((mContent[i] == '(') && flags_test(flags, FLAGS::IN_FUNCTION) && flags_test(flags, FLAGS::IN_FUNCTION_PARAM))
                {
                    ++mFctParamParenth;
                }
                else if ((mContent[i] == ')') && flags_test(flags, FLAGS::IN_FUNCTION) && flags_test(flags, FLAGS::IN_FUNCTION_PARAM))
                {
                    --mFctParamParenth;
                    if (mFctParamParenth == 0U)
                    {
                        flags_set(flags, FLAGS::IN_FUNCTION_SPACE);
                        flags_reset(flags, FLAGS::IN_FUNCTION_PARAM);
                    }
                }
                else if ((mContent[i] == ':') && flags_test(flags, FLAGS::IN_FUNCTION_SPACE))
                {
                    flags_set(flags, FLAGS::IN_FUNCTION_INIT);
                    flags_reset(flags, FLAGS::IN_FUNCTION_SPACE);
                }
                else if (mContent[i] == '{')
                {
                    mFunctionBlock.push_back(i);
                    flags_set(flags, FLAGS::IN_FUNCTION_BLOCK);
                    flags_reset(flags, FLAGS::IN_MEMBER_DECL);
                    flags_reset(flags, FLAGS::IN_FUNCTION_INIT);
                    flags_reset(flags, FLAGS::IN_FUNCTION_SPACE);
                    flags_reset(flags, FLAGS::IN_FUNCTION_PARAM);
                }
                else
                {
                    if (flags_test(flags, FLAGS::IN_MEMBER_ID))
                    {
                        if ((mContent[i] == '<') &&
                            (mWord != UCS("operator")))
                        {
                            mMemberName.push_back(mWord);
                            flags_reset(flags, FLAGS::IN_MEMBER_ID);
                            flags_set(flags, FLAGS::SET_TEMPLATE);
                        }
                        else if (((mContent[i] == '[') || (mContent[i] == '=')) &&
                                 (mWord != UCS("operator")))
                        {
                            mMemberName.push_back(mWord);
                            flags_reset(flags, FLAGS::IN_MEMBER_ID);
                            flags_set(flags, FLAGS::IN_ATTRIBUTE);
                        }
                    }
                    else if (mIsFunction.empty() || !mIsFunction.back())
                    {
                        if ((mContent[i] == ':') ||
                            ((i > 0U) && (isspace(mContent[i - 1]) != 0) && ((isalnum(mContent[i]) != 0) || (mContent[i] == '_')) && !flags_test(flags, FLAGS::IN_ATTRIBUTE)))
                        {
                            mMemberName.pop_back();
                            flags_set(flags, FLAGS::IN_MEMBER_ID);
                        }
                    }
                }
            }
        }
        else if ((isspace(mContent[i]) == 0) &&
                (iscntrl(mContent[i]) == 0) &&
                (mContent[i] != '{') &&
                (mContent[i] != '}') &&
                (mContent[i] != ':') &&
                (mContent[i] != ';') &&
                !flags_test(flags, FLAGS::IN_NO_CODE) &&
                !flags_test(flags, FLAGS::IN_TEMPLATE) &&
                !flags_test(flags, FLAGS::IN_PREPROCESSOR) &&
                !flags_test(flags, FLAGS::IN_CLASS_END) &&
                !flags_test(flags, FLAGS::IN_ENUM_BLOCK) &&
                !flags_test(flags, FLAGS::IN_ENUM_END) &&
                !flags_test(flags, FLAGS::IN_NAMESPACE_ID) &&
                !flags_test(flags, FLAGS::IN_TYPEDEF) &&
                (!flags_test(flags, FLAGS::IN_MEMBER) || (flags_test(flags, FLAGS::IN_CLASS_SPACE))))
        {
            mMemberStart.push_back(i);
            mIsFunction.push_back(false);
            flags_set(flags, FLAGS::IN_MEMBER);
            flags_set(flags, FLAGS::IN_MEMBER_DECL);
            flags_set(flags, FLAGS::IN_MEMBER_ID);
            flags_reset(flags, FLAGS::IN_CLASS_SPACE);
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseTemplate(size_t i, FlagSet& flags)
{
    static const typename EncodingT::string_t TEMPLATE_KEYWORD = UCS("template");
    if (!flags_test(flags, FLAGS::IN_PREPROCESSOR))
    {
        if (!flags_test(flags, FLAGS::IN_WORD) && (mWord == TEMPLATE_KEYWORD) &&
            (((mWordStart > 0U) && (mContent[mWordStart - 1] != ':')) || (mWordStart == 0U)) &&
            !flags_test(flags, FLAGS::IN_TEMPLATE))
        {
            mTemplateDelcStart = mWordStart;
            flags_set(flags, FLAGS::CLEAR_WORD);
            flags_set(flags, FLAGS::IN_TEMPLATE_DECL);
            flags_set(flags, FLAGS::SET_TEMPLATE);
        }
        if (flags_test(flags, FLAGS::SET_TEMPLATE))
        {
            mTemplateStart.push_back(i);
            flags_set(flags, FLAGS::IN_TEMPLATE);
            flags_reset(flags, FLAGS::SET_TEMPLATE);
        }
    }
    if (IN_CODE(flags))
    {
        if (!flags_test(flags, FLAGS::IN_PREPROCESSOR))
        {
            if (flags_test(flags, FLAGS::IN_TEMPLATE) &&
                (i > 0U) && (mContent[i - 1] == '>'))
            {
                mTemplateStart.pop_back();
                if (mTemplateStart.empty())
                {
                    flags_reset(flags, FLAGS::IN_TEMPLATE);
                }
            }
            if (flags_test(flags, FLAGS::IN_TEMPLATE_DECL) &&
                    (i > 0U) && ((mContent[i - 1] == ';') || (mContent[i - 1] == '{')))
            {
                flags_reset(flags, FLAGS::IN_TEMPLATE_DECL);
            }
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseStatement(size_t i, FlagSet& flags)
{
    if (IN_CODE(flags) &&
        !flags_test(flags, FLAGS::IN_PREPROCESSOR))
    {
        if (flags_test(flags, FLAGS::IN_STATEMENT))
        {
            if (((i > 0U) && (mContent[i - 1] == ';')) ||
                (mContent[i] == '{') ||
                (mContent[i] == '}') ||
                (i >= mContent.size()))
            {
                mStatements.push_back(ParserBlock(mStatementStart, i));
                flags_reset(flags, FLAGS::IN_STATEMENT);
            }
        }
        if (flags_test(flags, FLAGS::IN_FUNCTION_BLOCK) && !flags_test(flags, FLAGS::IN_NO_CODE))
        {
            if ((isspace(mContent[i]) == 0) &&
                (mContent[i] != '{') &&
                (mContent[i] != '}') &&
                !flags_test(flags, FLAGS::IN_STATEMENT))
            {
                mStatementStart = i;
                flags_set(flags, FLAGS::IN_STATEMENT);
            }
        }
        if (flags_test(flags, FLAGS::IN_FUNCTION_INIT) && !flags_test(flags, FLAGS::IN_NO_CODE))
        {
            if ((isspace(mContent[i]) == 0) &&
                (mContent[i] != ':') &&
                (mContent[i] != '{') &&
                (mContent[i] != '}') &&
                !flags_test(flags, FLAGS::IN_STATEMENT))
            {
                mStatementStart = i;
                flags_set(flags, FLAGS::IN_STATEMENT);
            }
        }
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseWord(size_t i, FlagSet& flags)
{
    if (flags_test(flags, FLAGS::CLEAR_WORD))
    {
        mWord = UCS("");
        flags_reset(flags, FLAGS::CLEAR_WORD);
    }
    if (((ispunct(mContent[i]) != 0) || (isspace(mContent[i]) != 0)) &&
        (mContent[i] != '_') &&
        flags_test(flags, FLAGS::IN_WORD))
    {
        mWord = mContent.substr(mWordStart, i - mWordStart);
        flags_reset(flags, FLAGS::IN_WORD);
    }
    if (((isalnum(mContent[i]) != 0) ||
         (mContent[i] == '_')) &&
        !flags_test(flags, FLAGS::IN_WORD) &&
        IN_CODE(flags))
    {
        mWordStart = i;
        flags_set(flags, FLAGS::IN_WORD);
    }
}

template <class EncodingT>
bool CPPParserInterpreter<EncodingT>::iterators(size_t blockId, std::vector<ParserBlock>::const_iterator& first, std::vector<ParserBlock>::const_iterator& last) const
{
    bool initIt = false;
    switch (blockId)
    {
    case LINES_ID:
        first = mLines.cbegin();
        last = mLines.cend();
        initIt = true;
    break;
    case NO_CODE_ID:
        first = mNoCode.cbegin();
        last = mNoCode.cend();
        initIt = true;
    break;
    case STRINGS_ID:
        first = mStrings.cbegin();
        last = mStrings.cend();
        initIt = true;
    break;
    case C_COMMENTS_ID:
        first = mCComments.cbegin();
        last = mCComments.cend();
        initIt = true;
    break;
    case CPP_COMMENTS_ID:
        first = mCppComments.cbegin();
        last = mCppComments.cend();
        initIt = true;
    break;
    case COMMENTS_ID:
        first = mComments.cbegin();
        last = mComments.cend();
        initIt = true;
    break;
    case PREPROCESSORS_ID:
        first = mPreprocessors.cbegin();
        last = mPreprocessors.cend();
        initIt = true;
    break;
    case CODE_BLOCKS_ID:
        first = mCodeBlocks.cbegin();
        last = mCodeBlocks.cend();
        initIt = true;
    break;
    case CLASS_ID:
        first = mClass.cbegin();
        last = mClass.cend();
        initIt = true;
    break;
    case STRUCT_ID:
        first = mStruct.cbegin();
        last = mStruct.cend();
        initIt = true;
    break;
    case UNION_ID:
        first = mUnion.cbegin();
        last = mUnion.cend();
        initIt = true;
    break;
    case CLASS_SPECIFIER_ID:
        first = mSpecifier.cbegin();
        last = mSpecifier.cend();
        initIt = true;
    break;
    case NAMESPACE_ID:
        first = mNamespace.cbegin();
        last = mNamespace.cend();
        initIt = true;
    break;
    case ENUM_ID:
        first = mEnum.cbegin();
        last = mEnum.cend();
        initIt = true;
    break;
    case FUNCTION_ID:
        first = mFunctions.cbegin();
        last = mFunctions.cend();
        initIt = true;
    break;
    case ATTRIBUTE_ID:
        first = mAttributes.cbegin();
        last = mAttributes.cend();
        initIt = true;
    break;
    case STATEMENT_ID:
        first = mStatements.cbegin();
        last = mStatements.cend();
        initIt = true;
    break;
    case COMPOSITION_ID:
        first = mComposition.cbegin();
        last = mComposition.cend();
        initIt = true;
    break;
    case LITERAL_ID:
        first = mLiterals.cbegin();
        last = mLiterals.cend();
        initIt = true;
    break;
    default:
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Parsed category not found";
    }
    return initIt;
}

template <class EncodingT>
long long CPPParserInterpreter<EncodingT>::find(size_t val, size_t blockId, ParserBlock& block) const
{
    long long index = NO_POS;
    std::vector<ParserBlock>::const_iterator first, last;
    if (iterators(blockId, first, last))
    {
        auto it = std::upper_bound(first, last, ParserBlock(val), ParserBlock::compareEnd);
        while ((it != last) && !it->inRange(val)) ++it;
        if (it != last)
        {
            block = *it;
            index = it - first;
        }
    }
    return index;
}

template <class EncodingT>
CPPParserInterpreter<EncodingT>::CPPParserInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t CPPParserInterpreter<EncodingT>::toString() const
{
    return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new CPPParserInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t CPPParserInterpreter<EncodingT>::getClassName() const
{
    return UCS("CPPParser");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
    boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
    ParameterArray args, ret;
    if (check_parameters_array(params, args))
    {
        if (tryInvoke(this, UCS("CPPParser"), method, args, ret) ||
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
            logger->errorStream() << "Unexpected call in CPPParser, no method \"" << A(method) << "\" exists.";
        }
    }
    return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::getFileContent(const boost::shared_ptr< Base<EncodingT> >& path) const
{
    boost::shared_ptr< Base<EncodingT> > obj = boost::make_shared< String<EncodingT> >();
    boost::shared_ptr< String<EncodingT> > nativePath = dynamic_pointer_cast< String<EncodingT> >(path);
    if (nativePath != nullptr)
    {
        obj = boost::make_shared< String<EncodingT> >(getNativeContent(nativePath->value()));
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String expected, got " << A(path->getClassName());
    }
    return obj;
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parseFile(const boost::shared_ptr< Base<EncodingT> >& path)
{
    boost::shared_ptr< String<EncodingT> > nativePath = dynamic_pointer_cast< String<EncodingT> >(path);
    if (nativePath != nullptr)
    {
        mContent = getNativeContent(nativePath->value());
        mContentPtr =  boost::make_shared< String<EncodingT> >(mContent);
        parse();
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String expected, got " << A(path->getClassName());
    }
}

template <class EncodingT>
void CPPParserInterpreter<EncodingT>::parse(const boost::shared_ptr< Base<EncodingT> >& content)
{
    boost::shared_ptr< String<EncodingT> > nativeContent = dynamic_pointer_cast< String<EncodingT> >(content);
    if (nativeContent != nullptr)
    {
        mContentPtr = content;
        mContent = nativeContent->value();
        parse();
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String expected, got " << A(content->getClassName());
    }
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::getContent() const
{
    return mContentPtr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::getSourceCode() const
{
    return mCodePtr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::linesId() const
{
    static boost::shared_ptr< Base<EncodingT> > LINES_ID_PTR = boost::make_shared< Numeric<EncodingT> >(LINES_ID);
    return LINES_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::stringsId() const
{
    static boost::shared_ptr< Base<EncodingT> > STRINGS_ID_PTR = boost::make_shared< Numeric<EncodingT> >(STRINGS_ID);
    return STRINGS_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::CCommentsId() const
{
    static boost::shared_ptr< Base<EncodingT> > C_COMMENTS_ID_PTR = boost::make_shared< Numeric<EncodingT> >(C_COMMENTS_ID);
    return C_COMMENTS_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::CppCommentsId() const
{
    static boost::shared_ptr< Base<EncodingT> > CPP_COMMENTS_ID_PTR = boost::make_shared< Numeric<EncodingT> >(CPP_COMMENTS_ID);
    return CPP_COMMENTS_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::preprocessorsId() const
{
    static boost::shared_ptr< Base<EncodingT> > PREPROCESSORS_ID_PTR = boost::make_shared< Numeric<EncodingT> >(PREPROCESSORS_ID);
    return PREPROCESSORS_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::commentsId() const
{
    static boost::shared_ptr< Base<EncodingT> > COMMENTS_ID_PTR = boost::make_shared< Numeric<EncodingT> >(COMMENTS_ID);
    return COMMENTS_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::noCodeId() const
{
    static boost::shared_ptr< Base<EncodingT> > NO_CODE_ID_PTR = boost::make_shared< Numeric<EncodingT> >(NO_CODE_ID);
    return NO_CODE_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::codeBlockId() const
{
    static boost::shared_ptr< Base<EncodingT> > CODE_BLOCKS_ID_PTR = boost::make_shared< Numeric<EncodingT> >(CODE_BLOCKS_ID);
    return CODE_BLOCKS_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::classId() const
{
    static boost::shared_ptr< Base<EncodingT> > CLASS_ID_PTR = boost::make_shared< Numeric<EncodingT> >(CLASS_ID);
    return CLASS_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::structId() const
{
    static boost::shared_ptr< Base<EncodingT> > STRUCT_ID_PTR = boost::make_shared< Numeric<EncodingT> >(STRUCT_ID);
    return STRUCT_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::unionId() const
{
    static boost::shared_ptr< Base<EncodingT> > UNION_ID_PTR = boost::make_shared< Numeric<EncodingT> >(UNION_ID);
    return UNION_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::compositionId() const
{
    static boost::shared_ptr< Base<EncodingT> > COMPOSITION_ID_PTR = boost::make_shared< Numeric<EncodingT> >(COMPOSITION_ID);
    return COMPOSITION_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::classSpecifierId() const
{
    static boost::shared_ptr< Base<EncodingT> > CLASS_SPECIFIER_ID_PTR = boost::make_shared< Numeric<EncodingT> >(CLASS_SPECIFIER_ID);
    return CLASS_SPECIFIER_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::namespaceId() const
{
    static boost::shared_ptr< Base<EncodingT> > NAMESPACE_ID_PTR = boost::make_shared< Numeric<EncodingT> >(NAMESPACE_ID);
    return NAMESPACE_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::enumId() const
{
    static boost::shared_ptr< Base<EncodingT> > ENUM_ID_PTR = boost::make_shared< Numeric<EncodingT> >(ENUM_ID);
    return ENUM_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::functionId() const
{
    static boost::shared_ptr< Base<EncodingT> > FUNCTION_ID_PTR = boost::make_shared< Numeric<EncodingT> >(FUNCTION_ID);
    return FUNCTION_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::attributeId() const
{
    static boost::shared_ptr< Base<EncodingT> > ATTRIBUTE_ID_PTR = boost::make_shared< Numeric<EncodingT> >(ATTRIBUTE_ID);
    return ATTRIBUTE_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::statementId() const
{
    static boost::shared_ptr< Base<EncodingT> > STATEMENT_ID_PTR = boost::make_shared< Numeric<EncodingT> >(STATEMENT_ID);
    return STATEMENT_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::literalId() const
{
    static boost::shared_ptr< Base<EncodingT> > LITERAL_ID_PTR = boost::make_shared< Numeric<EncodingT> >(LITERAL_ID);
    return LITERAL_ID_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::noPos() const
{
    static boost::shared_ptr< Base<EncodingT> > NO_POS_PTR = boost::make_shared< Numeric<EncodingT> >(NO_POS);
    return NO_POS_PTR;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::indexOf(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Base<EncodingT> > index = boost::make_shared< Numeric<EncodingT> >(NO_POS);
    boost::shared_ptr< Numeric<EncodingT> > nativeVal = dynamic_pointer_cast< Numeric<EncodingT> >(val);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeVal != nullptr && nativeBlock != nullptr)
    {
        ParserBlock block;
        index = boost::make_shared< Numeric<EncodingT> >(find(nativeVal->LLvalue(), nativeBlock->LLvalue(), block));
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(val->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return index;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::inRange(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Base<EncodingT> > res = boost::make_shared< Bool<EncodingT> >(false);
    boost::shared_ptr< Numeric<EncodingT> > nativeVal = dynamic_pointer_cast< Numeric<EncodingT> >(val);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeVal != nullptr && nativeBlock != nullptr)
    {
        ParserBlock block;
        res = boost::make_shared< Bool<EncodingT> >(find(nativeVal->LLvalue(), nativeBlock->LLvalue(), block) != NO_POS);
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(val->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return res;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::range(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Array<EncodingT> > arr = boost::make_shared< Array<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeVal = dynamic_pointer_cast< Numeric<EncodingT> >(val);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeVal != nullptr && nativeBlock != nullptr)
    {
        ParserBlock block;
        if (find(nativeVal->LLvalue(), nativeBlock->LLvalue(), block) != NO_POS)
        {
            arr->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(block.Start())));
            arr->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(block.End())));
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(val->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::previous(const boost::shared_ptr< Base<EncodingT> >& val, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Base<EncodingT> > index = boost::make_shared< Numeric<EncodingT> >(NO_POS);
    boost::shared_ptr< Numeric<EncodingT> > nativeVal = dynamic_pointer_cast< Numeric<EncodingT> >(val);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeVal != nullptr && nativeBlock != nullptr)
    {
        std::vector<ParserBlock>::const_iterator first, last;
        if (iterators(nativeBlock->LLvalue(), first, last))
        {
            auto it = std::upper_bound(first, last, ParserBlock(nativeVal->LLvalue()), ParserBlock::compareEnd);
            if (it != first)
            {
                index = boost::make_shared< Numeric<EncodingT> >((it - 1) - first);
            }
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(val->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return index;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::array(const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Array<EncodingT> > arr = boost::make_shared< Array<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeBlock != nullptr)
    {
        std::vector<ParserBlock>::const_iterator first, last;
        if (iterators(nativeBlock->LLvalue(), first, last))
        {
            for (std::vector<ParserBlock>::const_iterator it = first; it != last; ++it)
            {
                boost::shared_ptr< Array<EncodingT> > r = boost::make_shared< Array<EncodingT> >();
                r->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(it->Start())));
                r->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(it->End())));
                arr->addValue(r);
            }
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Numeric expected, got " << A(blockId->getClassName());
    }
    return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::size(const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Numeric<EncodingT> > s = boost::make_shared< Numeric<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeBlock != nullptr)
    {
        std::vector<ParserBlock>::const_iterator first, last;
        if (iterators(nativeBlock->LLvalue(), first, last))
        {
            s = boost::make_shared< Numeric<EncodingT> >(last - first);
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Numeric expected, got " << A(blockId->getClassName());
    }
    return s;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::extract(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< String<EncodingT> > str = boost::make_shared< String<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeIndex = dynamic_pointer_cast< Numeric<EncodingT> >(index);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeIndex != nullptr && nativeBlock != nullptr)
    {
        std::vector<ParserBlock>::const_iterator first, last;
        if ((nativeIndex->LLvalue() >= 0) &&
                iterators(nativeBlock->LLvalue(), first, last) && (first + nativeIndex->LLvalue()) < last)
        {
            const ParserBlock& block = *(first + nativeIndex->LLvalue());
            str = boost::make_shared< String<EncodingT> >(mContent.substr(block.Start(), (block.End() - block.Start())));
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(index->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return str;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::extractCode(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< String<EncodingT> > str = boost::make_shared< String<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeIndex = dynamic_pointer_cast< Numeric<EncodingT> >(index);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeIndex != nullptr && nativeBlock != nullptr)
    {
        std::vector<ParserBlock>::const_iterator first, last;
        if ((nativeIndex->LLvalue() >= 0) &&
                iterators(nativeBlock->LLvalue(), first, last) && (first + nativeIndex->LLvalue()) < last)
        {
            const ParserBlock& block = *(first + nativeIndex->LLvalue());
            str = boost::make_shared< String<EncodingT> >(mCode.substr(block.Start(), (block.End() - block.Start())));
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(index->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return str;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::at(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Array<EncodingT> > arr = boost::make_shared< Array<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeIndex = dynamic_pointer_cast< Numeric<EncodingT> >(index);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeIndex != nullptr && nativeBlock != nullptr)
    {
        std::vector<ParserBlock>::const_iterator first, last;
        if ((nativeIndex->LLvalue() >= 0) &&
                iterators(nativeBlock->LLvalue(), first, last) && (first + nativeIndex->LLvalue()) < last)
        {
            const ParserBlock& block = *(first + nativeIndex->LLvalue());
            arr->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(block.Start())));
            arr->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(block.End())));
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(index->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return arr;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::name(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< String<EncodingT> > str = boost::make_shared< String<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeIndex = dynamic_pointer_cast< Numeric<EncodingT> >(index);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeIndex != nullptr && nativeBlock != nullptr)
    {
        if ((PREPROCESSORS_ID == nativeBlock->LLvalue()) ||
            (CLASS_ID == nativeBlock->LLvalue()) ||
            (STRUCT_ID == nativeBlock->LLvalue()) ||
            (UNION_ID == nativeBlock->LLvalue()) ||
            (COMPOSITION_ID == nativeBlock->LLvalue()) ||
            (CLASS_SPECIFIER_ID == nativeBlock->LLvalue()) ||
            (NAMESPACE_ID == nativeBlock->LLvalue()) ||
            (ENUM_ID == nativeBlock->LLvalue()) ||
            (FUNCTION_ID == nativeBlock->LLvalue()) ||
            (ATTRIBUTE_ID == nativeBlock->LLvalue()))
        {
            std::vector<ParserBlock>::const_iterator first, last;
            if ((nativeIndex->LLvalue() >= 0) &&
                    iterators(nativeBlock->LLvalue(), first, last) && (first + nativeIndex->LLvalue()) < last)
            {
                const ParserBlock& block = *(first + nativeIndex->LLvalue());
                try
                {
                    const ParserInformation<EncodingT>& data = block.data< ParserInformation<EncodingT> >();
                    if (data.hasName())
                    {
                        str = boost::make_shared< String<EncodingT> >(data.getName());
                    }
                }
                catch(const std::bad_any_cast& e)
                {
                    Category* logger = &Category::getInstance(LOGNAME);
                    logger->errorStream() << "name " << nativeBlock->LLvalue() << ": " << e.what();
                }
            }
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "ParserBlock has no name";
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(index->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return str;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::type(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId) const
{
    boost::shared_ptr< Numeric<EncodingT> > type = boost::make_shared< Numeric<EncodingT> >();
    boost::shared_ptr< Numeric<EncodingT> > nativeIndex = dynamic_pointer_cast< Numeric<EncodingT> >(index);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlock = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeIndex != nullptr && nativeBlock != nullptr)
    {
        if (COMPOSITION_ID == nativeBlock->LLvalue())
        {
            std::vector<ParserBlock>::const_iterator first, last;
            if ((nativeIndex->LLvalue() >= 0) &&
                    iterators(nativeBlock->LLvalue(), first, last) && (first + nativeIndex->LLvalue()) < last)
            {
                const ParserBlock& block = *(first + nativeIndex->LLvalue());
                try
                {
                    const ParserInformation<EncodingT>& data = block.data< ParserInformation<EncodingT> >();
                    if (data.hasType())
                    {
                        type = boost::make_shared< Numeric<EncodingT> >(data.getType());
                    }
                }
                catch(const std::bad_any_cast& e)
                {
                    Category* logger = &Category::getInstance(LOGNAME);
                    logger->errorStream() << "type: " << e.what();
                }
            }
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "ParserBlock has no type";
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric) expected, got (" << A(index->getClassName()) << ", " << A(blockId->getClassName()) << ")";
    }
    return type;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > CPPParserInterpreter<EncodingT>::include(const boost::shared_ptr< Base<EncodingT> >& index, const boost::shared_ptr< Base<EncodingT> >& blockId, const boost::shared_ptr< Base<EncodingT> >& origin, const boost::shared_ptr< Base<EncodingT> >& blockOrig) const
{
    boost::shared_ptr< Bool<EncodingT> > inc = boost::make_shared< Bool<EncodingT> >(false);
    boost::shared_ptr< Numeric<EncodingT> > nativeOrigin = dynamic_pointer_cast< Numeric<EncodingT> >(origin);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlockOrig = dynamic_pointer_cast< Numeric<EncodingT> >(blockOrig);
    boost::shared_ptr< Numeric<EncodingT> > nativeIndex = dynamic_pointer_cast< Numeric<EncodingT> >(index);
    boost::shared_ptr< Numeric<EncodingT> > nativeBlockId = dynamic_pointer_cast< Numeric<EncodingT> >(blockId);
    if (nativeOrigin != nullptr && nativeIndex != nullptr && nativeBlockOrig != nullptr && nativeBlockId != nullptr)
    {
        std::vector<ParserBlock>::const_iterator firstI, lastI, firstO, lastO;
        if ((nativeIndex->LLvalue() >= 0) &&
                (nativeOrigin->LLvalue() >= 0) &&
                iterators(nativeBlockId->LLvalue(), firstI, lastI) &&
                iterators(nativeBlockOrig->LLvalue(), firstO, lastO) &&
                (firstI + nativeIndex->LLvalue()) < lastI &&
                (firstO + nativeOrigin->LLvalue()) < lastO)
        {
            const ParserBlock& blockI = *(firstI + nativeIndex->LLvalue());
            const ParserBlock& blockO = *(firstO + nativeOrigin->LLvalue());
            inc = boost::make_shared< Bool<EncodingT> >(blockO.Start() <= blockI.Start() && blockI.End() <= blockO.End());
        }
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "(Numeric, Numeric, Numeric, Numeric) expected, got (" << A(index->getClassName())  << ", " << A(blockId->getClassName()) << ", " << A(origin->getClassName()) << ", " << A(blockOrig->getClassName()) << ")";
    }
    return inc;
}

NAMESPACE_END

#undef A
#undef C
