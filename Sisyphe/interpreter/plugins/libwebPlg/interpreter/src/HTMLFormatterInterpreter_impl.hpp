/*
 * HTMLFormatterInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */

#include <cstdint>
#include "convert.hpp"
#include <cctype>

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
const std::set<typename EncodingT::string_t> HTMLFormatterInterpreter<EncodingT>::KEYWORDS = {
UCS("switch"), UCS("case"), UCS("break"), UCS("continue"), UCS("default"),
UCS("if"), UCS("else"),
UCS("while"), UCS("do"), UCS("for"),
UCS("return"), UCS("goto"),
UCS("try"), UCS("catch"), UCS("throw"),
UCS("inline"), UCS("sizeof"), UCS("typeof"), UCS("alignof"), UCS("explicit"),
UCS("typedef"), UCS("using"), UCS("namespace"),
UCS("new"), UCS("delete"), UCS("operator"), UCS("this"),
UCS("public"), UCS("protected"), UCS("private"), UCS("friend"),
UCS("true"), UCS("false"), UCS("NULL"), UCS("nullptr"),
UCS("import"), UCS("asm"), UCS("export"),
UCS("const_cast"), UCS("static_cast"), UCS("dynamic_cast"), UCS("reinterpret_cast"),
UCS("static_assert"), UCS("typeid"),
UCS("CALLBACK"), UCS("APIENTRY"), UCS("WINAPI")
};

template <class EncodingT>
const std::set<typename EncodingT::string_t> HTMLFormatterInterpreter<EncodingT>::TYPES = {
UCS("auto"), UCS("static"), UCS("virtual"), UCS("override"), UCS("final"),
UCS("const"), UCS("volatile"), UCS("extern"), UCS("register"), UCS("mutable"),
UCS("constexpr"), UCS("decltype"),
UCS("enum"), UCS("struct"), UCS("class"), UCS("union"), UCS("typename"), UCS("template"),
UCS("unsigned"), UCS("signed"),
UCS("void"), UCS("char"), UCS("short"), UCS("int"), UCS("long"), UCS("double"), UCS("float"), UCS("bool"), UCS("time_t"), UCS("size_t"), UCS("clock_t"),
UCS("std"), UCS("string"), UCS("wstring"), UCS("map"), UCS("set"), UCS("list"), UCS("vector"), UCS("multimap"), UCS("bitset"), UCS("array"), UCS("deque"), UCS("multiset"), UCS("forward_list"), UCS("queue"), UCS("priority_queue"), UCS("stack"), UCS("unordered_map"), UCS("unordered_set"), UCS("unordered_multimap"), UCS("unordered_multiset"), UCS("initializer_list"),
UCS("iterator"), UCS("const_iterator"), UCS("pair"), UCS("hash"), UCS("exception"), UCS("complex"), UCS("regex"), UCS("wregex"), UCS("cmatch"), UCS("wcmatch"), UCS("smatch"), UCS("wsmatch"), UCS("tuple"),
UCS("intmax_t"), UCS("int8_t"), UCS("int16_t"), UCS("int32_t"), UCS("int64_t"), UCS("int_least8_t"), UCS("int_least16_t"), UCS("int_least32_t"), UCS("int_least64_t"), UCS("int_fast8_t"), UCS("int_fast16_t"), UCS("int_fast32_t"), UCS("int_fast64_t"), UCS("intptr_t"),
UCS("uintmax_t"), UCS("uint8_t"), UCS("uint16_t"), UCS("uint32_t"), UCS("uint64_t"), UCS("uint_least8_t"), UCS("int_least16_t"), UCS("uint_least32_t"), UCS("uint_least64_t"), UCS("uint_fast8_t"), UCS("uint_fast16_t"), UCS("uint_fast32_t"), UCS("uint_fast64_t"), UCS("uintptr_t"),
UCS("BOOL"), UCS("BOOLEAN"), UCS("BYTE"), UCS("CCHAR"), UCS("CHAR"), UCS("COLORREF"), UCS("DWORD"), UCS("DWORDLONG"), UCS("DWORD_PTR"), UCS("DWORD32"), UCS("DWORD64"), UCS("FLOAT"), UCS("HACCEL"), UCS("HALF_PTR"), UCS("HANDLE"), UCS("HBITMAP"), UCS("HBRUSH"),
UCS("HCOLORSPACE"), UCS("HCONV"), UCS("HCONVLIST"), UCS("HCURSOR"), UCS("HDC"), UCS("HDDEDATA"), UCS("HDESK"), UCS("HDROP"), UCS("HDWP"), UCS("HENHMETAFILE"), UCS("HFILE"), UCS("HFONT"), UCS("HGDIOBJ"), UCS("HGLOBAL"), UCS("HHOOK"), UCS("HICON"), UCS("HINSTANCE"), UCS("HKEY"), UCS("HKL"), UCS("HLOCAL"),
UCS("HMENU"), UCS("HMETAFILE"), UCS("HMODULE"), UCS("HMONITOR"), UCS("HPALETTE"), UCS("HPEN"), UCS("HRESULT"), UCS("HRGN"), UCS("HRSRC"), UCS("HSZ"), UCS("HWINSTA"), UCS("HWND"), UCS("INT"), UCS("INT_PTR"), UCS("INT8"), UCS("INT16"), UCS("INT32"), UCS("INT64"), UCS("LANGID"), UCS("LCID"), UCS("LCTYPE"), UCS("LGRPID"),
UCS("LONG"), UCS("LONGLONG"), UCS("LONG_PTR"), UCS("LONG32"), UCS("LONG64"), UCS("LPARAM"), UCS("LPBOOL"), UCS("LPBYTE"), UCS("LPCOLORREF"), UCS("LPCSTR"), UCS("LPCTSTR"), UCS("LPCVOID"), UCS("LPCWSTR"), UCS("LPDWORD"), UCS("LPHANDLE"), UCS("LPINT"), UCS("LPLONG"), UCS("LPSTR"), UCS("LPTSTR"), UCS("LPVOID"), UCS("LPWORD"), UCS("LPWSTR"), UCS("LRESULT"),
UCS("PBOOL"), UCS("PBOOLEAN"), UCS("PBYTE"), UCS("PCHAR"), UCS("PCSTR"), UCS("PCTSTR"), UCS("PCWSTR"), UCS("PDWORD"), UCS("PDWORDLONG"), UCS("PDWORD_PTR"), UCS("PDWORD32"), UCS("PDWORD64"), UCS("PFLOAT"), UCS("PHALF_PTR"), UCS("PHANDLE"), UCS("PHKEY"), UCS("PINT"), UCS("PINT_PTR"), UCS("PINT8"), UCS("PINT16"), UCS("PINT32"),
UCS("PINT64"), UCS("PLCID"), UCS("PLONG"), UCS("PLONGLONG"), UCS("PLONG_PTR"), UCS("PLONG32"), UCS("PLONG64"), UCS("POINTER_32"), UCS("POINTER_64"), UCS("POINTER_SIGNED"), UCS("POINTER_UNSIGNED"), UCS("PSHORT"), UCS("PSIZE_T"), UCS("PSSIZE_T"), UCS("PSTR"), UCS("PTBYTE"), UCS("PTCHAR"), UCS("PTSTR"), UCS("PUCHAR"), UCS("PUHALF_PTR"), UCS("PUINT"), UCS("PUINT_PTR"), UCS("PUINT8"), UCS("PUINT16"), UCS("PUINT32"),
UCS("PUINT64"), UCS("PULONG"), UCS("PULONGLONG"), UCS("PULONG_PTR"), UCS("PULONG32"), UCS("PULONG64"), UCS("PUSHORT"), UCS("PVOID"), UCS("PWCHAR"), UCS("PWORD"), UCS("PWSTR"), UCS("QWORD"), UCS("SC_HANDLE"), UCS("SC_LOCK"), UCS("SERVICE_STATUS_HANDLE"), UCS("SHORT"), UCS("SIZE_T"), UCS("SSIZE_T"), UCS("TBYTE"), UCS("TCHAR"), UCS("UCHAR"), UCS("UHALF_PTR"), UCS("UINT"), UCS("UINT_PTR"), UCS("UINT8"),
UCS("UINT16"), UCS("UINT32"), UCS("UINT64"), UCS("ULONG"), UCS("ULONGLONG"), UCS("ULONG_PTR"), UCS("ULONG32"), UCS("ULONG64"), UCS("UNICODE_STRING"), UCS("USHORT"), UCS("USN"), UCS("VOID"), UCS("WCHAR"), UCS("WORD"), UCS("WPARAM"),
UCS("CString"), UCS("CList"), UCS("CArray"), UCS("CMap")
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
    typename EncodingT::string_t result = UCS("<ol class=\"linenums\"><li class=\"L0\"><span id=\"L0\">");
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
    typename EncodingT::string_t style = UCS("pln"), next_style = UCS("pln");
    typename EncodingT::string_t wordStyle = UCS("kwd");

    size_t end = content.size();
    const size_t beginNspaces = spaceLTR(content, 0U, end);
    const typename EncodingT::string_t beginSpaces = content.substr(0U, beginNspaces);
    if (!beginSpaces.empty())
    {
        result += UCS("<span class=\"pln\">") + beginSpaces + UCS("</span>");
    }
    result += UCS("<span id=\"T0\">");

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
                next_style = UCS("str");
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
                next_style = UCS("str");
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
            next_style = UCS("com");
            remainder = 2;
            change = EChange::style_change;
        }
        else if ((content[i] == '\n') && inCppComment)
        {
            inCppComment = false;
            next_style = UCS("pln");
            remainder = 1;
            change = EChange::style_change;
        }
        else if ((content[i] == '*') && startComment)
        {
            inCComment = true;
            inPuntuaction = false;
            betweenWord = false;
            next_style = UCS("com");
            remainder = 2;
            change = EChange::style_change;
        }
        else if ((content[i] == '/') && endCComment)
        {
            inCComment = false;
            if (inPreprocessor)
            {
                next_style = UCS("pre");
            }
            else
            {
                next_style = UCS("pln");
            }
            change = EChange::style_change;
        }
        else if ((content[i] == '#') && !inPreprocessor && !inCppComment && !inCComment && !inStringDblQuotes && !inStringSplQuote)
        {
            inPreprocessor = true;
            inPuntuaction = false;
            betweenWord = false;
            next_style = UCS("pre");
            remainder = 1;
            change = EChange::style_change;
        }
        else if ((content[i] == '\n') && inPreprocessor && !escaping)
        {
            inPreprocessor = false;
            next_style = UCS("pln");
            remainder = 1;
            change = EChange::style_change;
        }
        else if (((isdigit(content[i]) != 0) || ((content[i] == '.') && (isdigit(content[i + 1]) != 0))) && betweenWord && !inLiteral)
        {
            inLiteral = !inLiteral;
            inPuntuaction = false;
            betweenWord = false;
            next_style = UCS("lit");
            remainder = 1;
            change = EChange::style_change;
        }
        else if ((ispunct(content[i]) != 0) && (content[i] != '_') && ((content[i] != '.') || !inLiteral) && !inPuntuaction && !inPreprocessor && !inCppComment && !inCComment && !inStringDblQuotes && !inStringSplQuote)
        {
             inPuntuaction = !inPuntuaction;
             next_style = UCS("pun");
             remainder = 1;
             change = EChange::style_change;
        }
        else if ((ispunct(content[i]) == 0) && inPuntuaction && !inHtmlPuntuaction)
        {
             inPuntuaction = !inPuntuaction;
             next_style = UCS("pln");
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
                    wordStyle = UCS("kwd");
                    change = change | EChange::word_change;
                }
                typename std::set<typename EncodingT::string_t>::const_iterator t = TYPES.find(word);
                if (t != TYPES.end())
                {
                    remainder = wordSize + 1;
                    wordStyle = UCS("typ");
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
                inHtmlPuntuaction = ((htmlAmp.compare(UCS("&amp;")) == 0) ||
                    (htmLtGt.compare(UCS("&lt;")) == 0)  ||
                    (htmLtGt.compare(UCS("&gt;")) == 0));
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
                result += UCS("<span class=\"") + style + UCS("\">") + txt + UCS("</span>");
            }
            analysing -= size;
            analysed += size;
            if ((change & EChange::style_change) == EChange::style_change)
            {
                style = next_style;
                next_style = UCS("pln");
            }
            if ((change & EChange::word_change) == EChange::word_change)
            {
                const int wordSize = remainder - 1;
                const typename EncodingT::string_t word = content.substr(analysed, wordSize);
                if (!word.empty())
                {
                    result += UCS("<span class=\"") + wordStyle + UCS("\">") + word + UCS("</span>");
                }
                analysing -= wordSize;
                analysed += wordSize;
                remainder = remainder - wordSize;
            }
            if ((change & EChange::line_change) == EChange::line_change)
            {
                ++nline;
                result += UCS("</span>");
                const typename EncodingT::string_t rigthSpaces = content.substr(analysed, remainder - 1);
                if (!rigthSpaces.empty())
                {
                    result += UCS("<span class=\"pln\">") + rigthSpaces + UCS("</span>");
                }
                result += UCS("</span></li><li class=\"L") + Convert<typename EncodingT::string_t>::parse(nline % 10) + UCS("\"><span id=\"L") + Convert<typename EncodingT::string_t>::parse(nline) + UCS("\">");
                const size_t leftNspaces = spaceLTR(content, i, end);
                const typename EncodingT::string_t leftSpaces = content.substr(i, leftNspaces);
                if (!leftSpaces.empty())
                {
                    result += UCS("<span class=\"pln\">") + leftSpaces + UCS("</span>");
                }
                result += UCS("<span id=\"T") + Convert<typename EncodingT::string_t>::parse(nline) + UCS("\">");
                analysing -= remainder;
                analysed += remainder + leftNspaces;
                i += leftNspaces;
            }
            remainder = 0U;
            change = EChange::no_change;
        }
    }
    result += UCS("</span></span></li></ol>");
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
    return UCS("HTMLFormatter");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > HTMLFormatterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
    ParameterArray args, ret;
    if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, UCS("HTMLFormatter"), method, args, ret) ||
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
