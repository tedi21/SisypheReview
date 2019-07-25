/*
 * HTMLFormatterInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#include <cstdint>
#include "Convert.hpp"
#include <cctype>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
const std::set<typename EncodingT::string_t> HTMLFormatterInterpreter<EncodingT>::KEYWORDS = {
C("switch"), C("case"), C("break"), C("continue"), C("default"),
C("if"), C("else"),
C("while"), C("do"), C("for"),
C("return"), C("goto"),
C("try"), C("catch"), C("throw"),
C("inline"), C("sizeof"), C("typeof"), C("alignof"), C("explicit"),
C("typedef"), C("using"), C("namespace"),
C("new"), C("delete"), C("operator"), C("this"),
C("public"), C("protected"), C("private"), C("friend"),
C("true"), C("false"), C("NULL"), C("nullptr"),
C("import"), C("asm"), C("export"),
C("const_cast"), C("static_cast"), C("dynamic_cast"), C("reinterpret_cast"),
C("static_assert"), C("typeid"),
C("CALLBACK"), C("APIENTRY"), C("WINAPI")
};

template <class EncodingT>
const std::set<typename EncodingT::string_t> HTMLFormatterInterpreter<EncodingT>::TYPES = {
C("auto"), C("static"), C("virtual"), C("override"), C("final"),
C("const"), C("volatile"), C("extern"), C("register"), C("mutable"),
C("constexpr"), C("decltype"),
C("enum"), C("struct"), C("class"), C("union"), C("typename"), C("template"),
C("unsigned"), C("signed"),
C("void"), C("char"), C("short"), C("int"), C("long"), C("double"), C("float"), C("bool"), C("time_t"), C("size_t"), C("clock_t"),
C("std"), C("string"), C("wstring"), C("map"), C("set"), C("list"), C("vector"), C("multimap"), C("bitset"), C("array"), C("deque"), C("multiset"), C("forward_list"), C("queue"), C("priority_queue"), C("stack"), C("unordered_map"), C("unordered_set"), C("unordered_multimap"), C("unordered_multiset"), C("initializer_list"),
C("iterator"), C("const_iterator"), C("pair"), C("hash"), C("exception"), C("complex"), C("regex"), C("wregex"), C("cmatch"), C("wcmatch"), C("smatch"), C("wsmatch"), C("tuple"),
C("intmax_t"), C("int8_t"), C("int16_t"), C("int32_t"), C("int64_t"), C("int_least8_t"), C("int_least16_t"), C("int_least32_t"), C("int_least64_t"), C("int_fast8_t"), C("int_fast16_t"), C("int_fast32_t"), C("int_fast64_t"), C("intptr_t"),
C("uintmax_t"), C("uint8_t"), C("uint16_t"), C("uint32_t"), C("uint64_t"), C("uint_least8_t"), C("int_least16_t"), C("uint_least32_t"), C("uint_least64_t"), C("uint_fast8_t"), C("uint_fast16_t"), C("uint_fast32_t"), C("uint_fast64_t"), C("uintptr_t"),
C("BOOL"), C("BOOLEAN"), C("BYTE"), C("CCHAR"), C("CHAR"), C("COLORREF"), C("DWORD"), C("DWORDLONG"), C("DWORD_PTR"), C("DWORD32"), C("DWORD64"), C("FLOAT"), C("HACCEL"), C("HALF_PTR"), C("HANDLE"), C("HBITMAP"), C("HBRUSH"),
C("HCOLORSPACE"), C("HCONV"), C("HCONVLIST"), C("HCURSOR"), C("HDC"), C("HDDEDATA"), C("HDESK"), C("HDROP"), C("HDWP"), C("HENHMETAFILE"), C("HFILE"), C("HFONT"), C("HGDIOBJ"), C("HGLOBAL"), C("HHOOK"), C("HICON"), C("HINSTANCE"), C("HKEY"), C("HKL"), C("HLOCAL"),
C("HMENU"), C("HMETAFILE"), C("HMODULE"), C("HMONITOR"), C("HPALETTE"), C("HPEN"), C("HRESULT"), C("HRGN"), C("HRSRC"), C("HSZ"), C("HWINSTA"), C("HWND"), C("INT"), C("INT_PTR"), C("INT8"), C("INT16"), C("INT32"), C("INT64"), C("LANGID"), C("LCID"), C("LCTYPE"), C("LGRPID"),
C("LONG"), C("LONGLONG"), C("LONG_PTR"), C("LONG32"), C("LONG64"), C("LPARAM"), C("LPBOOL"), C("LPBYTE"), C("LPCOLORREF"), C("LPCSTR"), C("LPCTSTR"), C("LPCVOID"), C("LPCWSTR"), C("LPDWORD"), C("LPHANDLE"), C("LPINT"), C("LPLONG"), C("LPSTR"), C("LPTSTR"), C("LPVOID"), C("LPWORD"), C("LPWSTR"), C("LRESULT"),
C("PBOOL"), C("PBOOLEAN"), C("PBYTE"), C("PCHAR"), C("PCSTR"), C("PCTSTR"), C("PCWSTR"), C("PDWORD"), C("PDWORDLONG"), C("PDWORD_PTR"), C("PDWORD32"), C("PDWORD64"), C("PFLOAT"), C("PHALF_PTR"), C("PHANDLE"), C("PHKEY"), C("PINT"), C("PINT_PTR"), C("PINT8"), C("PINT16"), C("PINT32"),
C("PINT64"), C("PLCID"), C("PLONG"), C("PLONGLONG"), C("PLONG_PTR"), C("PLONG32"), C("PLONG64"), C("POINTER_32"), C("POINTER_64"), C("POINTER_SIGNED"), C("POINTER_UNSIGNED"), C("PSHORT"), C("PSIZE_T"), C("PSSIZE_T"), C("PSTR"), C("PTBYTE"), C("PTCHAR"), C("PTSTR"), C("PUCHAR"), C("PUHALF_PTR"), C("PUINT"), C("PUINT_PTR"), C("PUINT8"), C("PUINT16"), C("PUINT32"),
C("PUINT64"), C("PULONG"), C("PULONGLONG"), C("PULONG_PTR"), C("PULONG32"), C("PULONG64"), C("PUSHORT"), C("PVOID"), C("PWCHAR"), C("PWORD"), C("PWSTR"), C("QWORD"), C("SC_HANDLE"), C("SC_LOCK"), C("SERVICE_STATUS_HANDLE"), C("SHORT"), C("SIZE_T"), C("SSIZE_T"), C("TBYTE"), C("TCHAR"), C("UCHAR"), C("UHALF_PTR"), C("UINT"), C("UINT_PTR"), C("UINT8"),
C("UINT16"), C("UINT32"), C("UINT64"), C("ULONG"), C("ULONGLONG"), C("ULONG_PTR"), C("ULONG32"), C("ULONG64"), C("UNICODE_STRING"), C("USHORT"), C("USN"), C("VOID"), C("WCHAR"), C("WORD"), C("WPARAM"),
C("CString"), C("CList"), C("CArray"), C("CMap")
};

template <class EncodingT>
typename EncodingT::string_t HTMLFormatterInterpreter<EncodingT>::purify(const typename EncodingT::string_t& str)
{
    typename EncodingT::string_t res = str;
    boost::algorithm::replace_all(res, "\r\n", "\n");
    boost::algorithm::replace_all(res, "\t", "    ");
    boost::algorithm::replace_all(res, "&", "&amp;");
    boost::algorithm::replace_all(res, "<", "&lt;");
    boost::algorithm::replace_all(res, ">", "&gt;");
    return res;
}

template <class EncodingT>
size_t HTMLFormatterInterpreter<EncodingT>::spaceRTL(const typename EncodingT::string_t& str, const size_t right, const size_t left)
{
    size_t ret = 0U;
    if (right > 0U)
    {
        size_t i = right - 1U;
        while (i >= left && isblank(str[i]) != 0)
        {
            --i;
        }
        ret = right - (i + 1U);
    }
    return ret;
}

template <class EncodingT>
size_t HTMLFormatterInterpreter<EncodingT>::spaceLTR(const typename EncodingT::string_t& str, const size_t left, const size_t right)
{
    size_t i = left;
    while (i < right && isblank(str[i]) != 0)
    {
        ++i;
    }
    return i - left;
}

enum class EChange: uint8_t
{
    no_change = 0U,
    style_change = 1U,
    word_change = 2U,
    line_change = 4U
};

constexpr enum EChange operator| (const enum EChange selfValue,
                                  const enum EChange inValue)
{
    return (enum EChange)(uint8_t(selfValue) | uint8_t(inValue));
}

constexpr enum EChange operator& (const enum EChange selfValue,
                                  const enum EChange inValue)
{
    return (enum EChange)(uint8_t(selfValue) & uint8_t(inValue));
}

template <class EncodingT>
typename EncodingT::string_t HTMLFormatterInterpreter<EncodingT>::formatCpp(const typename EncodingT::string_t& content)
{
    typename EncodingT::string_t result = C("<ol class=\"linenums\"><li class=\"L0\"><span id=\"L0\">");
    result.reserve(content.size() * 2U);
    bool escaping = false;
    bool startComment = false;
    bool endCComment = false;
    bool inStringDblQuotes = false;
    bool inStringSplQuote = false;
    bool inCppComment = false;
    bool inCComment = false;
    bool inPreprocessor = false;
    bool inPuntuaction = false;
    bool inHtmlPuntuaction = false;
    bool betweenWord = false;
    bool inLiteral = false;
    EChange change = EChange::no_change;
    int remainder = 0;
    int nline = 0;
    typename EncodingT::string_t style = C("pln"), next_style = C("pln");
    typename EncodingT::string_t wordStyle = C("kwd");

    size_t end = content.size();
    const size_t beginNspaces = spaceLTR(content, 0U, end);
    const typename EncodingT::string_t beginSpaces = content.substr(0U, beginNspaces);
    if (!beginSpaces.empty())
    {
        result += C("<span class=\"pln\">") + beginSpaces + C("</span>");
    }
    result += C("<span id=\"T0\">");

    size_t i = beginNspaces;
    size_t analysing = 0U;
    size_t analysed = i;
    size_t startWord = i;

    while (i < end)
    {
        if ((content[i] == '"') && !escaping && !inStringSplQuote && !inCppComment && !inCComment && !inPreprocessor)
        {
            inStringDblQuotes = !inStringDblQuotes;
            if (inStringDblQuotes)
            {
                inPuntuaction = false;
                betweenWord = false;
                next_style = C("str");
                remainder = 1;
            }
            change = EChange::style_change;
        }
        else if ((content[i] == '\'') && !escaping && !inStringDblQuotes && !inCppComment && !inCComment  && !inPreprocessor)
        {
            inStringSplQuote = !inStringSplQuote;
            if (inStringSplQuote)
            {
                inPuntuaction = false;
                betweenWord = false;
                next_style = C("str");
                remainder = 1;
            }
            change = EChange::style_change;
        }
        else if ((content[i] == '/') && startComment)
        {
            inCppComment = true;
            inPreprocessor = false;
            inPuntuaction = false;
            betweenWord = false;
            next_style = C("com");
            remainder = 2;
            change = EChange::style_change;
        }
        else if ((content[i] == '\n') && inCppComment)
        {
            inCppComment = false;
            next_style = C("pln");
            remainder = 1;
            change = EChange::style_change;
        }
        else if ((content[i] == '*') && startComment)
        {
            inCComment = true;
            inPuntuaction = false;
            betweenWord = false;
            next_style = C("com");
            remainder = 2;
            change = EChange::style_change;
        }
        else if ((content[i] == '/') && endCComment)
        {
            inCComment = false;
            if (inPreprocessor)
            {
                next_style = C("pre");
            }
            else
            {
                next_style = C("pln");
            }
            change = EChange::style_change;
        }
        else if ((content[i] == '#') && !inPreprocessor && !inCppComment && !inCComment && !inStringDblQuotes && !inStringSplQuote)
        {
            inPreprocessor = true;
            inPuntuaction = false;
            betweenWord = false;
            next_style = C("pre");
            remainder = 1;
            change = EChange::style_change;
        }
        else if ((content[i] == '\n') && inPreprocessor && !escaping)
        {
            inPreprocessor = false;
            next_style = C("pln");
            remainder = 1;
            change = EChange::style_change;
        }
        else if (((isdigit(content[i]) != 0) || ((content[i] == '.') && (isdigit(content[i + 1]) != 0))) && betweenWord && !inLiteral)
        {
            inLiteral = !inLiteral;
            inPuntuaction = false;
            betweenWord = false;
            next_style = C("lit");
            remainder = 1;
            change = EChange::style_change;
        }
        else if ((ispunct(content[i]) != 0) && (content[i] != '_') && ((content[i] != '.') || !inLiteral) && !inPuntuaction && !inPreprocessor && !inCppComment && !inCComment && !inStringDblQuotes && !inStringSplQuote)
        {
             inPuntuaction = !inPuntuaction;
             next_style = C("pun");
             remainder = 1;
             change = EChange::style_change;
        }
        else if ((ispunct(content[i]) == 0) && inPuntuaction && !inHtmlPuntuaction)
        {
             inPuntuaction = !inPuntuaction;
             next_style = C("pln");
             remainder = 1;
             change = EChange::style_change;
        }
        if (!betweenWord && (inPuntuaction || ((isspace(content[i]) != 0) && !inPuntuaction && !inPreprocessor && !inCppComment && !inCComment && !inStringDblQuotes && !inStringSplQuote)))
        {
            betweenWord = true;
            if (!inLiteral)
            {
                const size_t wordSize = i - startWord;
                const typename EncodingT::string_t word = content.substr(startWord, wordSize);
                typename std::set<typename EncodingT::string_t>::const_iterator k = KEYWORDS.find(word);
                if (k != KEYWORDS.end())
                {
                    remainder = wordSize + 1;
                    wordStyle = C("kwd");
                    change = change | EChange::word_change;
                }
                typename std::set<typename EncodingT::string_t>::const_iterator t = TYPES.find(word);
                if (t != TYPES.end())
                {
                    remainder = wordSize + 1;
                    wordStyle = C("typ");
                    change = change | EChange::word_change;
                }
            }
            inLiteral = false;
        }
        if (content[i] == '\n')
        {
            if (remainder == 0)
            {
                remainder = 1;
            }
            remainder = spaceRTL(content, i, analysed) + remainder;
            change = change | EChange::line_change;
        }
        escaping = ((content[i] == '\\') && !escaping);
        startComment = (content[i] == '/') && !inCppComment && !inCComment && !inStringDblQuotes && !inStringSplQuote;
        endCComment = (content[i] == '*') && inCComment;
        if (inPuntuaction)
        {
            if (!inHtmlPuntuaction)
            {
                const typename EncodingT::string_t htmlAmp = content.substr(i, 5U);
                const typename EncodingT::string_t htmLtGt = content.substr(i, 4U);
                inHtmlPuntuaction = ((htmlAmp.compare(C("&amp;")) == 0) ||
                    (htmLtGt.compare(C("&lt;")) == 0)  ||
                    (htmLtGt.compare(C("&gt;")) == 0));
            }
            else
            {
                inHtmlPuntuaction = (content[i] != ';');
            }
        }
        if (betweenWord && ((isalnum(content[i]) != 0) || (content[i] == '_')))
        {
            betweenWord = false;
            startWord = i;
        }
        // Add to analysing buffer
        ++analysing;
        ++i;
        // Apply change
        if ((i == end) || (change != EChange::no_change))
        {
            const int size = analysing - remainder;
            const typename EncodingT::string_t txt = content.substr(analysed, size);
            if (!txt.empty())
            {
                result += C("<span class=\"") + style + C("\">") + txt + C("</span>");
            }
            analysing -= size;
            analysed += size;
            if ((change & EChange::style_change) == EChange::style_change)
            {
                style = next_style;
                next_style = C("pln");
            }
            if ((change & EChange::word_change) == EChange::word_change)
            {
                const int wordSize = remainder - 1;
                const typename EncodingT::string_t word = content.substr(analysed, wordSize);
                if (!word.empty())
                {
                    result += C("<span class=\"") + wordStyle + C("\">") + word + C("</span>");
                }
                analysing -= wordSize;
                analysed += wordSize;
                remainder = remainder - wordSize;
            }
            if ((change & EChange::line_change) == EChange::line_change)
            {
                ++nline;
                result += C("</span>");
                const typename EncodingT::string_t rigthSpaces = content.substr(analysed, remainder - 1);
                if (!rigthSpaces.empty())
                {
                    result += C("<span class=\"pln\">") + rigthSpaces + C("</span>");
                }
                result += C("</span></li><li class=\"L") + Convert<typename EncodingT::string_t>::parse(nline % 10) + C("\"><span id=\"L") + Convert<typename EncodingT::string_t>::parse(nline) + C("\">");
                const size_t leftNspaces = spaceLTR(content, i, end);
                const typename EncodingT::string_t leftSpaces = content.substr(i, leftNspaces);
                if (!leftSpaces.empty())
                {
                    result += C("<span class=\"pln\">") + leftSpaces + C("</span>");
                }
                result += C("<span id=\"T") + Convert<typename EncodingT::string_t>::parse(nline) + C("\">");
                analysing -= remainder;
                analysed += remainder + leftNspaces;
                i += leftNspaces;
            }
            remainder = 0U;
            change = EChange::no_change;
        }
    }
    result += C("</span></span></li></ol>");
    return result;
}

template <class EncodingT>
HTMLFormatterInterpreter<EncodingT>::HTMLFormatterInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t HTMLFormatterInterpreter<EncodingT>::toString() const
{
    return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > HTMLFormatterInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new HTMLFormatterInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t HTMLFormatterInterpreter<EncodingT>::getClassName() const
{
    return C("HTMLFormatter");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > HTMLFormatterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
    ParameterArray args, ret;
    if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, C("HTMLFormatter"), method, args, ret) ||
			tryInvoke(this, C("Base"), method, args, ret))
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
            logger->errorStream() << "Unexpected call in HTMLFormatter, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > HTMLFormatterInterpreter<EncodingT>::prettyPrint(const boost::shared_ptr< Base<EncodingT> >& source) const
{
    boost::shared_ptr< Base<EncodingT> > obj = boost::make_shared< String<EncodingT> >();
    boost::shared_ptr< String<EncodingT> > nativeSource = dynamic_pointer_cast< String<EncodingT> >(source);
    if (nativeSource != nullptr)
    {
        obj = boost::make_shared< String<EncodingT> >(formatCpp(purify(nativeSource->value())));
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String expected, got " << A(source->getClassName());
    }
    return obj;
}

NAMESPACE_END

#undef A
#undef C
