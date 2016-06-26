#include "../chance.hpp"
#include <vector>
#include <iostream>
#include "../../Factory/convert.hpp"

using namespace std;
using namespace gen;

class Person
{
private:
    string last_name;
    string first_name;
    int age;

public:
    Person(const string& last_name_, const string& first_name_, int age_)
    : last_name(last_name_), first_name(first_name_), age(age_)
    {}

    const string& getLastName() const
    {
        return last_name;
    }

    const string& getFirstName() const
    {
        return first_name;
    }

    int getAge() const
    {
        return age;
    }

    bool operator<(const Person& p) const
    {
        return last_name < p.last_name;
    }
};

class Company
{
private:
    string name;
    Person CEO;
    vector<Person> employees;
    vector<Company> suppliers;

public:
    Company(const string& name_, const Person& CEO_, 
            const vector<Person>& employees_,
            const vector<Company>& suppliers_)
    : name(name_), CEO(CEO_), 
      employees(employees_),
      suppliers(suppliers_)
    {}

    const string& getName() const
    {
        return name;
    }

    const Person& getCEO() const
    {
        return CEO;
    }

    const vector<Person>& getEmployees() const
    {
        return employees;
    }

    const vector<Company>& getSuppliers() const
    {
        return suppliers;
    }

    bool operator<(const Company& c) const
    {
        return name < c.name;
    }
};

// Context declaration 
DEFINE_EMPTY_CONTEXT(char, StartContext)
DEFINE_CONTEXT_NODE(StartContext, Company, CompanyContext)
DEFINE_CONTEXT_RANGE(CompanyContext, vector<Person>, PersonContext)

// Functors
DECLARE_VALUE_ACCESS(CompanyContext, CompanyName)
IMPLEMENT_VALUE_ACCESS(CompanyContext, CompanyName, getName())

DECLARE_NODE_ACCESS(PersonContext, CEONode)
IMPLEMENT_NODE_ACCESS(PersonContext, CEONode, getCEO())

DECLARE_NODELIST_ACCESS(PersonContext, EmployeesNode)
IMPLEMENT_NODELIST_ACCESS(PersonContext, EmployeesNode, getEmployees())

struct SuppliersNode
{
    range<CompanyContext> operator()(const CompanyContext& c) const
    {
        return range<CompanyContext>(
            c.current()->getSuppliers().begin(),
            c.current()->getSuppliers().end());
    }
};

DECLARE_VALUE_ACCESS(PersonContext, PersonLastName)
IMPLEMENT_VALUE_ACCESS(PersonContext, PersonLastName, getLastName())

DECLARE_VALUE_ACCESS(PersonContext, PersonFirstName)
IMPLEMENT_VALUE_ACCESS(PersonContext, PersonFirstName, getFirstName())

DECLARE_VALUE_ACCESS(PersonContext, PersonAge)
IMPLEMENT_VALUE_ACCESS(PersonContext, PersonAge, getAge())

struct CompanyViewGenerator 
: public report<CompanyViewGenerator> 
{
    template <typename InfoT>
    struct etat 
    {
        format<InfoT>    CompanyView;
        format<InfoT>    PersonView;
        marker<EmployeesNode> Employees0, EmployeesN;
        marker<SuppliersNode> Suppliers0, SuppliersN;
        collection<PersonContext> Staff, EmployeesList;
        collection<CompanyContext> SuppliersList, CompaniesList;

        etat(CompanyViewGenerator const& me) 
        {
            typename marker<EmployeesNode>::factory_t factory((EmployeesNode()));
            Employees0 = factory.make(beg);
            EmployeesN = factory.make(end);

            typename marker<SuppliersNode>::factory_t factorySuppliers;
            Suppliers0 = factorySuppliers.make(beg);
            SuppliersN = factorySuppliers.make(end);

            Staff = beg_g(CEONode()) | (Employees0, EmployeesN);

            EmployeesList = list_g(EmployeesNode());

            SuppliersList = (Suppliers0, SuppliersN);//list_g(SuppliersNode());//(beg_g(SuppliersNode()), 1);//

            CompaniesList = SuppliersList | SuppliersList * CompaniesList;

            CompanyView =
                line_g(1) << "Company Name : " << call_g(CompanyName()) 
                << line_g(1) << "CEO : " 
                << PersonView   [beg_g(CEONode())]
                << (line_g(2) << "Employees list : " << "[total:" << size_g(EmployeesList) << "]")
                                [has_g(0, EmployeesList, gt_g())]
                << (line_g(1) << "Employee " << index_g()+1 << " : " 
                    << PersonView 
                    )           [EmployeesList]
                << line_g(2) << "Resume : "
                << PersonView   [Staff]
                << (line_g(2) << "Suppliers list : " << "[direct:" << size_g(SuppliersList) << " ;total:" << size_g(CompaniesList) << "]")
                                [has_g(0, SuppliersList, gt_g())]
                << CompanyView  [SuppliersList]
                << line_g(2)
            ;

            PersonView =
                   line_g(1) << htab_g(1) << "First name : " << call_g(PersonFirstName())
                << line_g(1) << htab_g(1) << "Last name  : " << call_g(PersonLastName())
                << line_g(1) << htab_g(1) << "Age        : " << call_g(PersonAge())
                << ~-line_g(1)
            ;
        }

        format<InfoT> const& start() const { return CompanyView; }
    };
};

int main()
{
    vector<Person> e1, e2;
    vector<Company> c0, c1, c2;
    c0.push_back(Company("Agribio", Person("MiniGraine", "Paul", 52), e2, c1));
    c2.push_back(Company("Locauto", Person("ChassisNeuf", "Stephane", 52), e2, c1));
    c2.push_back(Company("Securo", Person("GrandAngle", "Marc", 52), e2, c1));
    c0.push_back(Company("Aquaclear", Person("PaleRoche", "John", 52), e2, c2));
    
    e1.push_back(Person("GrosCarrote", "Philippe", 30));
    e1.push_back(Person("FinHaricot", "Luc", 25));
    Company legumo("Legumo", Person("PetitPois", "Charles", 50), e1, c0);

    CompanyViewGenerator companyView_g;
    string out = generate<char>(legumo , companyView_g);
    std::cout << out;
    system("pause");
}