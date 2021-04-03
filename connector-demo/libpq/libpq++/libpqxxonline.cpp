#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;


class conndba 
{
    private:
      connection *c;
      work *w;

    public:
      conndba(string s)
      {
	c = new connection(s);
        w=nullptr;
	if(c->is_open()) 
        {
          cout<<"connection success!"<<endl;     
	} else 
	{
	  cout<<"connection failed!"<<endl;
	}
      }

      ~conndba()
      {
       try{
       c->close();
       delete c;
       cout<<"exit success"<<endl;
       exit(0);
       } catch (const std::exception &e){
         cerr << e.what() << std::endl;
       }
      }

      bool execDMLonTable(const string &sql) 
      {
	 try{
	     w = new work(*c);
             w->exec(sql);
   	     w->commit();
	 }catch (const std::exception &e){
	      cerr << e.what() << std::endl;
              w->abort();
              delete w;
              return false;
	 }
         return true;
      }
      
      bool displayRowsOrderByDesc(const string& s) 
      {
         try
	 {
	    w = new work(*c); 
	    pqxx::result res =  w->exec(s);

            //获取字段列表
	    int fields = res.columns();
            for(int i=0;i<fields;i++) 
            {
                cout<<"| "<<res.column_name(i)<<" ";
            }
            cout<<endl;
           
            for(int i=0;i<fields;i++) 
            {
               cout<<"--------";
            }
            cout<<endl;
             
            //获取每一行数据，每行数据按列顺序输出
            for(auto row : res)
	    {
	       for(auto c : row) 
	       {
	         cout<<"| "<<c.c_str()<<" ";
	       }
 	       cout<<endl;
	    }
            w->commit();
            delete w;
	 }catch (const std::exception &e){
	      cerr << e.what() << std::endl;
              w->abort();
              delete w;
              return false;
	  }
          return true;
      }
};


int main(int argc, char* argv[])
{
    string conninfo = "dbname=txdb_default user=txadmin password=txadmin@123 \
     hostaddr=127.0.0.1 port=6868";

    cout<<"welcome to use OCCI interface!"<<endl;
    conndba* con = new conndba(conninfo);
    cout<<"connection information is:"<<endl;
    cout<<conninfo<<endl;
    string input;

    int selector=-1;
    bool res=false;
    do {
       cout<<"please input your operation, support operation is: 0(CREATE TABLE), 1(INSERT), 2(UPDATE), 3(DELETE), 4(SELECT), 5(quit): ";
       cin>>selector;
       cin.clear();
       if(selector!=5)
       {
         cout<<"please input your sql according to your choice:"<<endl;
	 cin.get();
	 getline(cin,input);
	 cin.clear();
       }
       switch(selector)
       {
       case 0:
         res = con->execDMLonTable(input);
         if(res) 
         {
	   cout<<"create table success"<<endl;
         }
         break;
       case 1:
         res = con->execDMLonTable(input);
         if(res) 
         {
	   cout<<"insert success"<<endl;
         }
       	 break;
       case 2:
         res = con->execDMLonTable(input);
         if(res) 
         {
	   cout<<"update success"<<endl;
         }
       	 break;
       case 3:
         res = con->execDMLonTable(input);
         if(res) 
         {
	   cout<<"delete success"<<endl;
         }
	 break;
       case 4:
         con->displayRowsOrderByDesc(input);
	 break;
       case 5:
         con->~conndba();
         break;
       default:
	 cout<<"input is invalid for "<<selector<<endl;
         con->~conndba();
      }
  } while(1); 
  
  return 0;
}

