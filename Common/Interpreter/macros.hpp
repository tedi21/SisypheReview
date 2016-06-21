#ifndef _MACROS_HPP_
#define _MACROS_HPP_

#include "bebop.hpp"
#include "encoding.hpp"

using namespace fctr;
using namespace enc;

#define KEY(val) encode<ansi,EncodingT>(#val)

#define FACTORY_PROTOTYPE1(Name, P1) \
    typedef Prototype1< P1 > Name##1;

#define FACTORY_PROTOTYPE2(Name, P1, P2) \
    typedef Prototype2< P1, P2 > Name##2;

#define FACTORY_PROTOTYPE3(Name, P1, P2, P3) \
    typedef Prototype3< P1, P2, P3 > Name##3;

#define FACTORY_PROTOTYPE4(Name, P1, P2, P3, P4) \
    typedef Prototype4< P1, P2, P3, P4 > Name##4;

#define FACTORY_PROTOTYPE5(Name, P1, P2, P3, P4, P5) \
    typedef Prototype5< P1, P2, P3, P4, P5 > Name##5;

#define FACTORY_PROTOTYPE6(Name, P1, P2, P3, P4, P5, P6) \
    typedef Prototype6< P1, P2, P3, P4, P5, P6 > Name##6;

#define FACTORY_PROTOTYPE7(Name, P1, P2, P3, P4, P5, P6, P7) \
    typedef Prototype7< P1, P2, P3, P4, P5, P6, P7 > Name##7;

#define FACTORY_PROTOTYPE8(Name, P1, P2, P3, P4, P5, P6, P7, P8) \
    typedef Prototype8< P1, P2, P3, P4, P5, P6, P7, P8 > Name##8;

#define FACTORY_PROTOTYPE9(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9) \
    typedef Prototype9< P1, P2, P3, P4, P5, P6, P7, P8, P9 > Name##9;

#define FACTORY_PROTOTYPE10(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) \
    typedef Prototype10< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10 > Name##10;

#define FACTORY_PROTOTYPE11(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11) \
    typedef Prototype11< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11 > Name##11;

#define FACTORY_PROTOTYPE12(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12) \
    typedef Prototype12< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12 > Name##12;

#define FACTORY_PROTOTYPE13(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13) \
    typedef Prototype13< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13 > Name##13;

#define FACTORY_PROTOTYPE14(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14) \
    typedef Prototype14< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14 > Name##14;

#define FACTORY_PROTOTYPE15(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15) \
    typedef Prototype15< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15 > Name##15;

#define FACTORY_PROTOTYPE16(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16) \
    typedef Prototype16< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16 > Name##16;

#define FACTORY_PROTOTYPE17(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17) \
    typedef Prototype17< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17 > Name##17;

#define FACTORY_PROTOTYPE18(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18) \
    typedef Prototype18< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18 > Name##18;

#define FACTORY_PROTOTYPE19(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19) \
    typedef Prototype19< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19 > Name##19;

#define FACTORY_PROTOTYPE20(Name, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20) \
    typedef Prototype20< P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15, P16, P17, P18, P19, P20 > Name##20;

#define FACTORY_BASE\
    Base<EncodingT>

#define FACTORY_KEY\
    typename EncodingT::string_t

#define FACTORY_PARAMETER_POLICY\
    IndexedParameterPolicy

#define FACTORY_MANAGER\
    ClassManager<FACTORY_BASE,FACTORY_KEY>

#define FACTORY_BEGIN_REGISTER    \
    static void register_class(){

#define FACTORY_END_REGISTER\
    }

#define FACTORY_BEGIN_UNREGISTER    \
    static void unregister_class(){ \

#define FACTORY_END_UNREGISTER\
    }

#define CLASS_KEY_REGISTER20(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory20<FACTORY_BASE,Class,Class::Class##20,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(20)) );

#define CLASS_KEY_REGISTER19(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory19<FACTORY_BASE,Class,Class::Class##19,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(19)) );

#define CLASS_KEY_REGISTER18(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory18<FACTORY_BASE,Class,Class::Class##18,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(18)) );

#define CLASS_KEY_REGISTER17(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory17<FACTORY_BASE,Class,Class::Class##17,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(17)) );

#define CLASS_KEY_REGISTER16(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory16<FACTORY_BASE,Class,Class::Class##16,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(16)) );

#define CLASS_KEY_REGISTER15(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory15<FACTORY_BASE,Class,Class::Class##15,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(15)) );

#define CLASS_KEY_REGISTER14(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory14<FACTORY_BASE,Class,Class::Class##14,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(14)) );

#define CLASS_KEY_REGISTER13(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory13<FACTORY_BASE,Class,Class::Class##13,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(13)) );

#define CLASS_KEY_REGISTER12(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory12<FACTORY_BASE,Class,Class::Class##12,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(12)) );

#define CLASS_KEY_REGISTER11(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory11<FACTORY_BASE,Class,Class::Class##11,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(11)) );

#define CLASS_KEY_REGISTER10(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory10<FACTORY_BASE,Class,Class::Class##10,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(10)) );

#define CLASS_KEY_REGISTER9(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory9<FACTORY_BASE,Class,Class::Class##9,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(9)) );

#define CLASS_KEY_REGISTER8(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory8<FACTORY_BASE,Class,Class::Class##8,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(8)) );

#define CLASS_KEY_REGISTER7(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory7<FACTORY_BASE,Class,Class::Class##7,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(7)) );

#define CLASS_KEY_REGISTER6(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory6<FACTORY_BASE,Class,Class::Class##6,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(6)) );

#define CLASS_KEY_REGISTER5(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory5<FACTORY_BASE,Class,Class::Class##5,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(5)) );

#define CLASS_KEY_REGISTER4(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory4<FACTORY_BASE,Class,Class::Class##4,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(4)) );

#define CLASS_KEY_REGISTER3(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory3<FACTORY_BASE,Class,Class::Class##3,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(3)) );

#define CLASS_KEY_REGISTER2(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory2<FACTORY_BASE,Class,Class::Class##2,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(2)) );

#define CLASS_KEY_REGISTER1(Class, Key)  \
    FACTORY_MANAGER::getInstance()\
    ->registerClass(\
        new Factory1<FACTORY_BASE,Class,Class::Class##1,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(Key + KEY(1)) );

#define CLASS_KEY_REGISTER(Class, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerClass( new Factory0<FACTORY_BASE,Class,FACTORY_KEY>(Key + KEY(0)) );

#define CLASS_KEY_UNREGISTER20(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(20) );

#define CLASS_KEY_UNREGISTER19(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(19) );

#define CLASS_KEY_UNREGISTER18(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(18) );

#define CLASS_KEY_UNREGISTER17(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(17) );

#define CLASS_KEY_UNREGISTER16(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(16) );

#define CLASS_KEY_UNREGISTER15(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(15) );

#define CLASS_KEY_UNREGISTER14(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(14) );

#define CLASS_KEY_UNREGISTER13(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(13) );

#define CLASS_KEY_UNREGISTER12(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(12) );

#define CLASS_KEY_UNREGISTER11(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(11) );

#define CLASS_KEY_UNREGISTER10(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(10) );

#define CLASS_KEY_UNREGISTER9(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(9) );

#define CLASS_KEY_UNREGISTER8(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(8) );

#define CLASS_KEY_UNREGISTER7(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(7) );

#define CLASS_KEY_UNREGISTER6(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(6) );

#define CLASS_KEY_UNREGISTER5(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(5) );

#define CLASS_KEY_UNREGISTER4(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(4) );

#define CLASS_KEY_UNREGISTER3(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(3) );

#define CLASS_KEY_UNREGISTER2(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(2) );

#define CLASS_KEY_UNREGISTER1(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(1) );

#define CLASS_KEY_UNREGISTER(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterClass( Key + KEY(0) );

#define METHOD_KEY_REGISTER20(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method20<FACTORY_BASE,Class,Return,Class::Method##20,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(20), &Class::Method) );

#define METHOD_KEY_REGISTER19(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method19<FACTORY_BASE,Class,Return,Class::Method##19,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(19), &Class::Method) );

#define METHOD_KEY_REGISTER18(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method18<FACTORY_BASE,Class,Return,Class::Method##18,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(18), &Class::Method) );

#define METHOD_KEY_REGISTER17(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method17<FACTORY_BASE,Class,Return,Class::Method##17,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(17), &Class::Method) );

#define METHOD_KEY_REGISTER16(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method16<FACTORY_BASE,Class,Return,Class::Method##16,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(16), &Class::Method) );

#define METHOD_KEY_REGISTER15(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method15<FACTORY_BASE,Class,Return,Class::Method##15,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(15), &Class::Method) );

#define METHOD_KEY_REGISTER14(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method14<FACTORY_BASE,Class,Return,Class::Method##14,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(14), &Class::Method) );

#define METHOD_KEY_REGISTER13(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method13<FACTORY_BASE,Class,Return,Class::Method##13,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(13), &Class::Method) );

#define METHOD_KEY_REGISTER12(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method12<FACTORY_BASE,Class,Return,Class::Method##12,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(12), &Class::Method) );

#define METHOD_KEY_REGISTER11(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method11<FACTORY_BASE,Class,Return,Class::Method##11,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(11), &Class::Method) );

#define METHOD_KEY_REGISTER10(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method10<FACTORY_BASE,Class,Return,Class::Method##10,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(10), &Class::Method) );

#define METHOD_KEY_REGISTER9(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method9<FACTORY_BASE,Class,Return,Class::Method##9,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(9), &Class::Method) );

#define METHOD_KEY_REGISTER8(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method8<FACTORY_BASE,Class,Return,Class::Method##8,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(8), &Class::Method) );

#define METHOD_KEY_REGISTER7(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method7<FACTORY_BASE,Class,Return,Class::Method##7,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(7), &Class::Method) );

#define METHOD_KEY_REGISTER6(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method6<FACTORY_BASE,Class,Return,Class::Method##6,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(6), &Class::Method) );

#define METHOD_KEY_REGISTER5(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method5<FACTORY_BASE,Class,Return,Class::Method##5,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(5), &Class::Method) );

#define METHOD_KEY_REGISTER4(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method4<FACTORY_BASE,Class,Return,Class::Method##4,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(4), &Class::Method) );

#define METHOD_KEY_REGISTER3(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method3<FACTORY_BASE,Class,Return,Class::Method##3,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(3), &Class::Method) );

#define METHOD_KEY_REGISTER2(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method2<FACTORY_BASE,Class,Return,Class::Method##2,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(2), &Class::Method) );

#define METHOD_KEY_REGISTER1(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method1<FACTORY_BASE,Class,Return,Class::Method##1,Const,FACTORY_KEY,FACTORY_PARAMETER_POLICY>(\
            Key + KEY(1), &Class::Method) );

#define METHOD_KEY_REGISTER(Class, Return, Method, Const, Key) \
    FACTORY_MANAGER::getInstance()\
    ->registerMethod(\
        new Method0<FACTORY_BASE,Class,Return,Const,FACTORY_KEY>(\
            Key + KEY(0), &Class::Method) );

#define METHOD_KEY_UNREGISTER20(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(20) );

#define METHOD_KEY_UNREGISTER19(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(19) );

#define METHOD_KEY_UNREGISTER18(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(18) );

#define METHOD_KEY_UNREGISTER17(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(17) );

#define METHOD_KEY_UNREGISTER16(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(16) );

#define METHOD_KEY_UNREGISTER15(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(15) );

#define METHOD_KEY_UNREGISTER14(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(14) );

#define METHOD_KEY_UNREGISTER13(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(13) );

#define METHOD_KEY_UNREGISTER12(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(12) );

#define METHOD_KEY_UNREGISTER11(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(11) );

#define METHOD_KEY_UNREGISTER10(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(10) );

#define METHOD_KEY_UNREGISTER9(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(9) );

#define METHOD_KEY_UNREGISTER8(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(8) );

#define METHOD_KEY_UNREGISTER7(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(7) );

#define METHOD_KEY_UNREGISTER6(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(6) );

#define METHOD_KEY_UNREGISTER5(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(5) );

#define METHOD_KEY_UNREGISTER4(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(4) );

#define METHOD_KEY_UNREGISTER3(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(3) );

#define METHOD_KEY_UNREGISTER2(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(2) );

#define METHOD_KEY_UNREGISTER1(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(1) );

#define METHOD_KEY_UNREGISTER(Key) \
    FACTORY_MANAGER::getInstance()\
    ->unRegisterMethod( Key + KEY(0) );

#define CLASS_REGISTER3(Class) \
    CLASS_KEY_REGISTER3(Class, KEY(Class))

#define CLASS_REGISTER2(Class) \
    CLASS_KEY_REGISTER2(Class, KEY(Class))

#define CLASS_REGISTER1(Class)  \
    CLASS_KEY_REGISTER1(Class, KEY(Class))

#define CLASS_REGISTER(Class) \
    CLASS_KEY_REGISTER(Class, KEY(Class))

#define CLASS_UNREGISTER3(Class) \
    CLASS_KEY_UNREGISTER3(KEY(Class))

#define CLASS_UNREGISTER2(Class) \
    CLASS_KEY_UNREGISTER2(KEY(Class))

#define CLASS_UNREGISTER1(Class) \
    CLASS_KEY_UNREGISTER1(KEY(Class))

#define CLASS_UNREGISTER(Class) \
    CLASS_KEY_UNREGISTER(KEY(Class))

#define METHOD_REGISTER2(Class, Return, Method, Const) \
    METHOD_KEY_REGISTER2(Class, Return, Method, Const, KEY(Class::Method))

#define METHOD_REGISTER1(Class, Return, Method, Const) \
    METHOD_KEY_REGISTER1(Class, Return, Method, Const, KEY(Class::Method))

#define METHOD_REGISTER(Class, Return, Method, Const) \
    METHOD_KEY_REGISTER(Class, Return, Method, Const, KEY(Class::Method))

#define METHOD_UNREGISTER2(Class, Method) \
    METHOD_KEY_UNREGISTER2(KEY(Class::Method))

#define METHOD_UNREGISTER1(Class, Method) \
    METHOD_KEY_UNREGISTER1(KEY(Class::Method))

#define METHOD_UNREGISTER(Class, Method) \
    METHOD_KEY_UNREGISTER(KEY(Class::Method))

#endif
