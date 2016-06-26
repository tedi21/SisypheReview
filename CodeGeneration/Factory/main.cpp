#include <iostream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include "ParameterArray.hpp"
#include "ClassManager.hpp"
#include "Prototype.hpp"
#include "Factory.hpp"
#include "Method.hpp"

using namespace std;
using namespace fctr;

//////////////////////////////////////////
// Macro helper
//////////////////////////////////////////

#define STRING(val) string(#val)

#define FACTORY_PROTOTYPE1(Name, P1) \
    typedef Prototype1< P1 > Name##1;

#define FACTORY_PROTOTYPE2(Name, P1, P2) \
    typedef Prototype2< P1, P2 > Name##2;

#define FACTORY_BEGIN_REGISTER    \
    static void register_class(){ \
    vector<string> parameters;

#define FACTORY_END_REGISTER\
    }

#define FACTORY_BEGIN_UNREGISTER    \
    static void unregister_class(){ \

#define FACTORY_END_UNREGISTER\
    }

#define CLASS_REGISTER2(Class, P1, P2) \
    {\
        typedef Factory2< void,Class,Class::Class##2,string,NamedParameterPolicy<string> > BOOST_PP_CAT(Class,Factory2);\
        BOOST_PP_CAT(Class,Factory2)* fact = new BOOST_PP_CAT(Class,Factory2)(STRING(Class##2));\
        fact->insertParameterName(0,P1);\
        fact->insertParameterName(1,P2);\
        ClassManager<void,string>::getInstance()->registerClass( fact );\
    }

#define CLASS_REGISTER1(Class, P1) \
    {\
        typedef Factory1< void,Class,Class::Class##1,string,NamedParameterPolicy<string> > BOOST_PP_CAT(Class,Factory1);\
        BOOST_PP_CAT(Class,Factory1)* fact = new BOOST_PP_CAT(Class,Factory1)(STRING(Class##1));\
        fact->insertParameterName(0,P1);\
        ClassManager<void,string>::getInstance()->registerClass( fact );\
    }

#define CLASS_REGISTER(Class) \
    ClassManager<void,string>::getInstance()\
    ->registerClass( new Factory0<void,Class,string>(STRING(Class##0)) );

#define CLASS_UNREGISTER2(Class) \
    ClassManager<void,string>::getInstance()\
    ->unRegisterClass( STRING(Class##2) );

#define CLASS_UNREGISTER1(Class) \
    ClassManager<void,string>::getInstance()\
    ->unRegisterClass( STRING(Class##1) );

#define CLASS_UNREGISTER(Class) \
    ClassManager<void,string>::getInstance()\
    ->unRegisterClass( STRING(Class##0) );

#define METHOD_REGISTER2(Class, Return, Method, Const, P1, P2) \
    {\
        typedef Method2<void,Class,Return,Class::Method##2,Const,string,NamedParameterPolicy<string> > BOOST_PP_CAT(Class,Method2);\
        BOOST_PP_CAT(Class,Method2)* fact = new BOOST_PP_CAT(Class,Method2)(STRING(Class::Method##2), &Class::Method);\
        fact->insertParameterName(0,P1);\
        fact->insertParameterName(1,P2);\
        ClassManager<void,string>::getInstance()->registerMethod( fact );\
    }

#define METHOD_REGISTER1(Class, Return, Method, Const, P1) \
    {\
        typedef Method1<void,Class,Return,Class::Method##1,Const,string,NamedParameterPolicy<string> > BOOST_PP_CAT(Class,Method1);\
        BOOST_PP_CAT(Class,Method1)* fact = new BOOST_PP_CAT(Class,Method1)(STRING(Class::Method##1), &Class::Method);\
        fact->insertParameterName(0,P1);\
        ClassManager<void,string>::getInstance()->registerMethod( fact );\
    }

#define METHOD_REGISTER(Class, Return, Method, Const) \
    ClassManager<void,string>::getInstance()\
    ->registerMethod( new Method0<void,Class,Return,Const,string>(STRING(Class::Method##0), &Class::Method) );

#define METHOD_UNREGISTER2(Class, Method) \
    ClassManager<void,string>::getInstance()\
    ->unRegisterMethod( STRING(Class::Method##2) );

#define METHOD_UNREGISTER1(Class, Method) \
    ClassManager<void,string>::getInstance()\
    ->unRegisterMethod( STRING(Class::Method##1) );

#define METHOD_UNREGISTER(Class, Method) \
    ClassManager<void,string>::getInstance()\
    ->unRegisterMethod( STRING(Class::Method##0) );

//////////////////////////////////////////
// Déclaration des classes
//////////////////////////////////////////

enum enum_t
{
    ENUM_1,
    ENUM_2
};

class AClass
{
public:
    AClass()
    {}

    FACTORY_PROTOTYPE2(AClass, In<int>, In<string>)
    AClass(int id, string name)
    {
        cout << "Construct AClass " << id << ", " << name << endl;
    }

    FACTORY_PROTOTYPE2(getValue, In<char>, Out<short>)
    int getValue(char code, short & error)
    {
        cout << "GetValue " << code << endl;
        error = 2103;
        return 100;
    }

    void getValue() const
    {
        cout << "GetValue " << endl;
    }

    FACTORY_PROTOTYPE1(testEnum, InOut<enum_t>)
    void testEnum(enum_t& e) const
    {
        cout << "testEnum " << endl;
    }

    FACTORY_BEGIN_REGISTER
        CLASS_REGISTER  (AClass)
        CLASS_REGISTER2 (AClass, "id", "name")
        METHOD_REGISTER (AClass, void, getValue, const_t)
        METHOD_REGISTER2(AClass, int, getValue, no_const_t, "code", "error")
        METHOD_REGISTER1(AClass, void, testEnum, const_t, "enum")
    FACTORY_END_REGISTER

    FACTORY_BEGIN_UNREGISTER
        CLASS_UNREGISTER  (AClass)
        CLASS_UNREGISTER2 (AClass)
        METHOD_UNREGISTER (AClass, getValue)
        METHOD_UNREGISTER2(AClass, getValue)
        METHOD_UNREGISTER1(AClass, testEnum)
    FACTORY_END_UNREGISTER
};

class BBase
{
public:
    virtual ~BBase(){}
    virtual string type() const = 0;
};

class BClass
: public BBase
{
public:
    BClass()
    {}

    FACTORY_PROTOTYPE1(name, In< shared_ptr<BBase> >)
    shared_ptr<BBase> name(const shared_ptr<BBase>& other) const
    {
        cout << "Invoke name()" << endl;
        return shared_ptr<BBase>(new BClass());
    }

    string type() const
    {
        return "BClass";
    }

    FACTORY_BEGIN_REGISTER
        CLASS_REGISTER   (BClass)
        METHOD_REGISTER1 (BClass, shared_ptr<BBase>, name, const_t, "other")
    FACTORY_END_REGISTER

    FACTORY_BEGIN_UNREGISTER
        CLASS_UNREGISTER   (BClass)
        METHOD_UNREGISTER1 (BClass, name)
    FACTORY_END_UNREGISTER
};

//////////////////////////////////////////
// Déclaration des Types sérialisables
//////////////////////////////////////////

FACTORY_PARAMETER_SERIAL2(string,int)
FACTORY_PARAMETER_SERIAL2(string,string)
FACTORY_PARAMETER_SERIAL2(string,char)
FACTORY_PARAMETER_SERIAL2(string,enum_t)

//////////////////////////////////////////
// Exportation des classes dans la factory
//////////////////////////////////////////

FACTORY_EXPORT(AClass)
FACTORY_EXPORT(BClass)

//////////////////////////////////////////
// Programme de test
//////////////////////////////////////////

int main()
{
    typedef void   Base_t;
    typedef string Key_t;
    typedef ClassManager<Base_t,Key_t> FactoryManager_t;
    typedef Prototype1< In<size_t> > Size_t;
    FactoryManager_t * manager = FactoryManager_t::getInstance();
    manager->registerClass( new FactoryArray<Base_t,int,Size_t,Key_t>("IntArray") );

    ParameterArray sizeArray;
    sizeArray.push_back(Parameter(size_t(0), size_t(5)));
    int* intArray = (int*)manager->create("IntArray", sizeArray);
    intArray[0] = 1;
    intArray[1] = 2;
    intArray[2] = 3;
    intArray[3] = 4;
    intArray[4] = 5;
    manager->release("IntArray", intArray);


    ParameterArray args;
    args.push_back(Parameter(string("id"), 123));
    args.push_back(Parameter(string("name"), string("Hello")));
    args.push_back(Parameter(string("code"), 'b'));
    args.push_back(Parameter(string("enum"), ENUM_2));
    cout << args[0].type() << endl << args[1].type() << endl << args[2].type() << endl;

    /// test serialize
    cout << "TEST " << endl;
    ofstream oss;
    oss.open("parameter.xml");
    boost::archive::xml_oarchive oar(oss);
    oar << boost::serialization::make_nvp("Parameters",args);
    oss.close();

    args.clear();

    ifstream iss;
    iss.open("parameter.xml");
    boost::archive::xml_iarchive iar(iss);
    iar >> boost::serialization::make_nvp("Parameters",args);
    iss.close();

    int i = 0;
    find_parameter(args, string("id"), i);
    string s = "";
    find_parameter(args, string("name"), s);
    cout << args[0].type() << ":" << i << endl << args[1].type() << ":" << s << endl;

    AClass* class1 = (AClass*)manager->create("AClass0");
    AClass* class2 = (AClass*)manager->create("AClass2", args);
    manager->invoke("AClass::getValue0", class2);
    manager->invoke("AClass::testEnum1", class2, args);
    ParameterArray ret = manager->invoke("AClass::getValue2", class2, args);
    short error;
    int   res;
    if (find_parameter(ret, string("error"), error) &&
        find_parameter(ret, FACTORY_RETURN_PARAMETER, res))
    {
        cout << "ret = " << res << ", " << error << endl;
    }
    manager->release("AClass0", class1);
    manager->release("AClass2", class2);

    BClass* class3 = (BClass*)manager->create("BClass0");
    args.push_back(Parameter(string("other"), shared_ptr<BBase>(new BClass())));
    ret = manager->invoke("BClass::name1", class3, args);
    shared_ptr<BBase> other;
    if (find_parameter(ret, FACTORY_RETURN_PARAMETER, other))
    {
        cout << "ret = " << other->type() << endl;
    }
    manager->release("BClass0", class3);

    system("pause");
}
