#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class myException: public exception
{
     virtual const char* what() const throw()
     {
        return "Error: list is empty";
     }
} myEx;

class Person
{
public:
       Person(int cod, string nm, string srnm, int point)
       {
           code=cod;
           name=nm;
           surname=srnm;
           points=point;
       }
       
       int code;
       string name;
       string surname;
       int points;
};

vector<Person> name_contains(vector<Person> old,int symbol)
{
     if(old.size()>0)
     {
         unsigned found;
         vector<Person> _new;
         for(int i=0; i<old.size(); i++)
         {
              found = old[i].name.find(char(symbol));
              if(found!=string::npos)
                  _new.push_back(old[i]);
         }
         return _new;
     }
     else
         throw myEx;
} 

vector<Person> points_greater_than(vector<Person> old, int points)
{
     if(old.size()>0)
     {
         vector<Person> _new;
         for(int i=0; i<old.size(); i++)
         {
              if(old[i].points>points)
                  _new.push_back(old[i]);
         }
         return _new;
     }
     else
         throw myEx;
}

vector<string> surname_name(vector<Person> old)
{
     if(old.size()>0)
     {
         vector<string> projection;
         string _new;
         for(int i=0; i<old.size(); i++)
         {
              _new=old[i].surname + " " + old[i].name;
              projection.push_back(_new);   
         }
         return projection;
     }
     else
         throw myEx;
}

vector<string> points_surname(vector<Person> old)
{
     if(old.size()>0)
     {
         vector<string> projection;
         string _new;
         for(int i=0; i<old.size(); i++)
         {
              ostringstream convert;
              convert << old[i].points;
              _new= convert.str() + " " + old[i].surname;
              projection.push_back(_new);   
         }
         return projection;
     }
     else
         throw myEx;
}

int sum_points(vector<Person> old)
{
     if(old.size()>0)
     {
         int sum=0;
         for(int i=0; i<old.size(); i++)
         {
              sum+=old[i].points;   
         }
         return sum;
     }
     else
         throw myEx;
}

int take_greater_points(vector<Person> old)
{
     if(old.size()>0)
     {
         int max=0;
         for(int i=0; i<old.size(); i++)
         {
              if(old[i].points>max)
                    max=old[i].points;  
         }
         return max;
     }
     else
         throw myEx;
}

vector<Person> readData()
{
    string code,name,surname,points;
    ifstream in("data.txt");
    vector<Person> people;
    
    while(!in.eof())
    {
        getline(in,code);
        getline(in,name);
        getline(in,surname);
        getline(in,points);
        Person nova(atoi(code.c_str()),name,surname,atoi(points.c_str()));
        people.push_back(nova);
    }
    in.close();
    
    return people;
}

vector<Person> _where(vector<Person> data, int value, vector<Person> (*filter)(vector<Person>,int))
{
     try
     {
        vector<Person> call;
        call=(*filter)(data,value);
        return (call);
     }  
     catch (exception& e)
     {
        cout<<e.what()<<endl;
        return data;
     }
}

vector<string> _select(vector<Person> data, vector<string> (*projection)(vector<Person>))
{
     try
     {
         vector<string> call;
         call=(*projection)(data);
         return call;
     }
     catch (exception& e)
     {
        vector<string> empty;
        cout<<e.what()<<endl;
        return empty;
     }
}

int _aggregate(vector<Person> data, int (*aggregation)(vector<Person>))
{
     try
     {
         int call;
         call=(*aggregation)(data);
         return call;
     }
     catch (exception& e)
     {
        cout<<e.what()<<endl;
        cout<<"Possible division by 0, ending"<<endl;
        system("PAUSE");
        exit (0);
     }
     
}

int main(int argc, char *argv[])
{
    vector<Person> data;
    vector<Person> result1a;
    vector<Person> result1b;
    vector<string> result4a;
    vector<string> result4b;
    int result6a;
    int result6b;
    int i;
    float avg;
    
    data=readData();
    
    result1a=_where(data,'1',name_contains);
    
    result6a=_aggregate(result1a,sum_points);
    result6b=_aggregate(result1a,take_greater_points);
    
    avg=(float)result6a/result1a.size();
    
    result1b=_where(result1a,(int)floor(avg),points_greater_than);
    
    result4a=_select(result1b,surname_name);
    result4b=_select(result1b,points_surname);
    
    cout<<"Students whose name contains the symbol '1':\n";
    for (i=0; i<result1a.size();i++)
    {
          cout<<result1a[i].code<<"\n";
          cout<<result1a[i].name<<"\n";
          cout<<result1a[i].surname<<"\n";
          cout<<result1a[i].points<<"\n";  
    }
    
    cout<<"\nThe sum of points of students:" <<result6a<<"\n";
    cout<<"Max number of points:" <<result6b<<"\n";
    cout<<"Avg number of points:" <<avg<<"\n";
    
    cout<<"\nStudents with a score higher than average:\n";
    for (i=0; i<result1b.size();i++)
    {
          cout<<result1b[i].code<<"\n";
          cout<<result1b[i].name<<"\n";
          cout<<result1b[i].surname<<"\n";
          cout<<result1b[i].points<<"\n";  
    }
    
    cout<<"\nsurname name:\n";
    for (i=0; i<result4a.size();i++)
    {
          cout<<result4a[i]<<"\n";
    }
    cout<<"\npoints surname:\n";
    for (i=0; i<result4b.size();i++)
    {
          cout<<result4b[i]<<"\n";
    }

    system("PAUSE");
    return EXIT_SUCCESS;
}
