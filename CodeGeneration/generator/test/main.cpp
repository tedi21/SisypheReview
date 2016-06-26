#include "../chance.hpp"
#include <vector>
#include <iostream>
#include <time.h>

using namespace std;
using namespace gen;

//INITIALIZE_GENERATOR

/// Memory object

struct data {
    string name;
    string type;
};

struct table {
    string name;
    vector<data> attributs;
    vector<string> values;
};

// Context declaration 
DEFINE_EMPTY_CONTEXT(char, empty)
DEFINE_CONTEXT_NODE(empty, vector<table>, start_context)
DEFINE_CONTEXT_RANGE(start_context, vector<table>, table_context)
DEFINE_CONTEXT_RANGE(table_context, vector<data>, data_context)
DEFINE_CONTEXT_RANGE(table_context, vector<string>, value_context)

const char * program_name()
{
    return "PROGRAM TEST";
}

struct data_range {    
    range<data_context> operator()(vector<table>::const_iterator & ite) const
    {
        return range<data_context>(ite->attributs.begin(), ite->attributs.end());
    }
};
ACTOR_TYPE(data_range, table_context)

struct table_range {    
    range<table_context> operator()(start_context & c) const
    {
        return range<table_context>(c.current()->begin(), c.current()->end());
    }
};

struct value_range {    
    range<value_context> operator()(table_context & c) const
    {
        return range<value_context>(c.current()->values.begin(), c.current()->values.end());
    }
};

const char * table_name(vector<table>::const_iterator ite)
{
    return ite->name.c_str();
}
typedef const char * (*table_function)(vector<table>::const_iterator);
ACTOR_TYPE(table_function, table_context)

struct NameFormatter {
    const char * operator()(vector<table>::const_iterator ite) const
    {
        return ite->name.c_str();
    }    
};
ACTOR_TYPE(NameFormatter, table_context)

struct DataFormatter {
    const char * operator()(vector<data>::const_iterator ite) const
    {
        return ite->name.c_str();
    }
};
ACTOR_TYPE(DataFormatter, data_context)

struct ValueFormatter {
    string operator()(vector<table>::const_iterator it1, vector<string>::const_iterator it2) const
    {
        return *it2 + " in " + it1->name;
    }
};
ACTOR_TYPE(ValueFormatter, value_context)

struct TypeFormatter {
    const char * operator()(data_context const& c) const
    {
        return c.current()->type.c_str();
    }
};

struct ConditionalBranching {
    bool operator()(vector<table>::const_iterator ite) const
    {
        return false;
    }
};
ACTOR_TYPE(ConditionalBranching, table_context)

struct ConditionalName {
    bool operator()(const table_context & c) const
    {
        //cout << "ent :   " << c.current()->name << endl;
        return c.current() != (c.domain().end()-1);
    }
};

bool $else()
{
    //cout << " TRACE ___1___ ";
    return true;
}

bool $if()
{
    //cout << " TRACE ___2___ ";
    return true;
}

/// My SQL Format file
struct MySQLGenerator : public report<MySQLGenerator> {

    template <typename InfoT>
    struct etat {
        NameFormatter NameFormat;
        DataFormatter DataFormat;
        ValueFormatter ValueFormat;
        TypeFormatter TypeFormat;
        ConditionalBranching IsComment;
        ConditionalName IsName;

        format<InfoT>    ScriptSQL;
        format<InfoT,memo_policy>    CreateTable;
        format<InfoT>    CreateRecursif;
        format<InfoT>    CreateComment;
        format<InfoT>    Smiley;
        format<InfoT>    CreateAttribut;
        format<InfoT>    CreateValue;
        format<InfoT>    CreateSentence;
        condition<InfoT> If_IsComment, If_ExistValue, If_IsName;

        format<InfoT>        CreateSub;

        marker<data_range> data0;
        marker<data_range> dataN;

        marker<value_range> value0;
        marker<value_range> valueN;

        marker<table_range> table0;
        marker<table_range> tableN;

        etat(MySQLGenerator const& me) 
        {
            typename marker<data_range>::factory_t fdata((data_range()));
            data0 = fdata.make(beg);
            dataN = fdata.make(end);

            typename marker<value_range>::factory_t fvalue((value_range()));
            value0 = fvalue.make(beg);
            valueN = fvalue.make(end);

            typename marker<table_range>::factory_t ftable((table_range()));
            table0 = ftable.make(beg);
            tableN = ftable.make(end);

            FORMAT_NAME(ScriptSQL)
            FORMAT_NAME(CreateTable)
            FORMAT_NAME(CreateRecursif)
            FORMAT_NAME(CreateComment)
            FORMAT_NAME(Smiley)
            FORMAT_NAME(CreateAttribut)
            FORMAT_NAME(CreateValue)
            CONDITION_NAME(If_IsComment)
            CONDITION_NAME(If_ExistValue)
            CONDITION_NAME(If_IsName)

            If_IsComment = (false || !if_g(IsComment) || !callT_g<table_context>(IsComment)) && true;
            If_ExistValue = has_g(0,(value0,valueN),gt_g());
            If_IsName = if_g(IsName);

            ScriptSQL = 
                call_g(&program_name) << line_g(2)
                <<( str_g("-- ") << call_g(&table_name) << line_g(1)
                <<  CreateTable << line_g(1) 
                <<  CreateRecursif << line_g(1)
                <<  CreateSentence << line_g(1))                        [-2, table0+2];//[-3, tableN-0];//[table0+0, 2];//[0, tableN];//[table0, 1];//[table0, tableN];//
            
            Smiley =
                str_g(" -_- [") << $(0) << "] value : '" << $(1)[value0] << "'" ;

            CreateTable = 
                str_g("CREATE TABLE ") << act_g(NameFormat) << '('
                    << ( CreateAttribut << ~-(str_g(",\n") << htab_g(3)) )        [data0, dataN]
                    //<< ( '\t' << CreateAttribut )                    [dataN-1]//, dataN]
                    << ( ch_g('\t') << CreateComment(Smiley, index_g()) )        [If_IsComment] 
                    << ( '\t' << CreateValue << "\n" )                [value0, valueN][If_ExistValue && true] 
                    << CreateSub(str_g("pRint"), str_g("\t cout << \"hello\" << endl; "))
                << ");\n";

            CreateComment =
                str_g("-- un commentaire ") << " " << $(1) << Smiley(str_g("{") << $(1) << str_g("}"), CreateValue) << "\n";

            CreateAttribut = 
                act_g(DataFormat)[call_g(&$else)] << str_g(" ")[call_g(&$if)] << call_g(TypeFormat) ;

            CreateValue =
                str_g("# ") << actT_g<value_context>(ValueFormat);//act_g(ValueFormat);

            CreateRecursif =
                (str_g("{") << act_g(NameFormat) << "(" << index_g()+1 << ")" << "," 
                            << CreateRecursif[current_g<table_context>()+1] << "}")         [If_IsName]
                << (str_g("{") << act_g(NameFormat) << "(" << index_g()+1 << ")" << "}")    [else_g()]
                ;

            CreateSub = 
                str_g("void ") << upper_g(lower_g($(0),1),0,1) << "() { " << $(1) << " }\n"; 

            CreateSentence =
                STR_G(cout << "CREATE TABLE" <<) 
                < act_g(NameFormat) 
                < STR_G(<< hello() << endl;)
                << line_g(1);

        }

        format<InfoT> const& start() const { return ScriptSQL; }
    };
};

/// test program

int main(){
{
    vector<table> database;
    table person, company;
    data tel, address;

/*    vector<int> v(10, 5);
    domain<vector<int>::iterator> a(v.begin(), v.end(), true_initializator());
    domain<vector<int>::iterator> b(v.begin(), v.end(), true_initializator());
    if (a.equivalent(b))
    {
        cout << "OK" << endl;
    }
    else
    {
        cout << "NOK" << endl;
    }*/

    person.name = "personne";
    tel.name = "telephone";
    tel.type = "string";
    address.name = "adresse";
    address.type = "text";
    person.attributs.push_back(tel);
    person.attributs.push_back(address);
    person.values.push_back("val1");
    person.values.push_back("val2");
    database.push_back(person);

    for (int i=0; i<10; i++)
    {
        company = table();
        company.name = "company" + boost::lexical_cast<string>(i);
        company.attributs.push_back(tel);
        company.attributs.push_back(address);
        database.push_back(company);
    }

    MySQLGenerator sql_g;


    //wstring out = generate<wchar_t, data_range>(database.begin(), database.end(), sql_g);
    //wstring out = generate<wchar_t>(database.begin(), database.end(), sql_g);
    //std::wcout << out;
    
    //string out = generate<char,data_range>(database.begin(), database.end(), sql_g);
    clock_t t0 = clock();
    //string out = generate<char,data_range>(database.begin(), database.end(), sql_g);
    //wstring out = generate<wchar_t,data_range>(database.begin(), database.end(), sql_g);
    string out = generate<char>(database , sql_g);
    std::cout << out;
    
    clock_t t1 = clock();
    std::cout << endl << " : " << (t1-t0) /*/ CLOCKS_PER_SEC*/ << endl;

    t0 = clock();
    string buf;
    for(int i=0; i<database.size(); i++){
        buf += "CREATE TABLE " + database[i].name + '(';
        for (int j=0; j<database[i].attributs.size(); j++) {
            buf += database[i].attributs[j].name + ' ' + database[i].attributs[j].type;
            buf += ",\n\t\t";
        }
        buf += '\n';
    }
    std::cout << buf;
    t1 = clock();
    std::cout << endl << " : " << (t1-t0) /*/ CLOCKS_PER_SEC*/ << endl;
    }
    system("pause");
}
