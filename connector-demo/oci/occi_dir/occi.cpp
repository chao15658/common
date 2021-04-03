#include <iostream>
#include <string>
#include <vector>
#include <occi.h>
 
using namespace oracle::occi;
using std::vector;
using namespace std;
 
class conndba
{
    private:
        Environment *env; 
        Connection *conn; 
        Statement *stmt; 
    public:	
        conndba(string user, string password, string db) 
        { 
            env = Environment::createEnvironment(Environment::DEFAULT); 
            conn = env->createConnection(user, password, db); 
        }
		
        ~conndba() 
        { 
            env->terminateConnection(conn); 
            Environment::terminateEnvironment(env);
        }
		
        void insertBind(string s1, string s2, string s3)
        {
             string sqlStmt = "INSERT INTO t_user(userid, username, loginname) VALUES (:1, :2, :3)";  
            stmt=conn->createStatement (sqlStmt);
            try
            { 
                stmt->setString(1, s1); 
                stmt->setString(2, s2);
                stmt->setString(3, s3); 
                stmt->executeUpdate();
                cout << "insert - Success" << endl;
            }
            catch (SQLException ex)
            {
                cout << "Exception thrown for insertBind" << endl;
                cout << "Error number: " << ex.getErrorCode() << endl;
                cout << ex.getMessage() << endl;
            }
            conn->terminateStatement(stmt);
        }
		
        void updateRow(string s1, string s2)
        {
            string sqlStmt = "UPDATE t_user SET userid = :x WHERE username = :y";
            stmt = conn->createStatement(sqlStmt);
            try
            {
                stmt->setString(1, s2);
                stmt->setString(2, s1);
                stmt->executeUpdate();
                cout << "update - Success" << endl;
            }
            catch (SQLException ex)
            {
                cout << "Exception thrown for updateRow" << endl;
                cout << "Error number: " << ex.getErrorCode() << endl;
                cout << ex.getMessage() << endl;
            }
            conn->terminateStatement(stmt);
        }
		
        void deleteRow(string s1)
        {
            string sqlStmt = "DELETE FROM t_user WHERE userid = :x";
            stmt = conn->createStatement(sqlStmt);
            try
            {
                stmt->setString(1, s1);
                stmt->executeUpdate();
                cout << "delete - Success" << endl;
            }
            catch (SQLException ex)
            {
                cout << "Exception thrown for deleteRow" << endl;
                cout << "Error number: " << ex.getErrorCode() << endl;
                cout << ex.getMessage() << endl;
            }
            conn->terminateStatement(stmt);
        }
		
        void displayAllRows()
        {
            string sql =
                    "select userid, username, loginname from t_user";
            stmt = conn->createStatement(sql);
            ResultSet *rs = stmt->executeQuery();
            try
            {
                while (rs->next())
                {
                    cout << "userid: " << rs->getInt(1) << "\t";
                    cout << "username: " << rs->getString(2) << "\t";
                    cout << "loginname: " << rs->getString(3) << "\t";
                    cout<<endl;
                }
            }
            catch (SQLException ex)
            {
                cout << "Exception thrown for displayAllRows" << endl;
                cout << "Error number: " << ex.getErrorCode() << endl;
                cout << ex.getMessage() << endl;
            }
            stmt->closeResultSet(rs);
            conn->terminateStatement(stmt);
        }
		
        void displayAllRowsDesc()
        {
            string sql =
                    "select userid, username, loginname from t_user order by userid desc";
            stmt = conn->createStatement(sql);
            ResultSet *rs = stmt->executeQuery();
            try
            {
                while (rs->next())
                {
                    cout << "userid: " << rs->getInt(1) << "\t";
                    cout << "username: " << rs->getString(2) << "\t";
                    cout << "loginname: " << rs->getString(3) << "\t";
                    cout<<endl;
                }
            }
            catch (SQLException ex)
            {
                cout << "Exception thrown for displayAllRows" << endl;
                cout << "Error number: " << ex.getErrorCode() << endl;
                cout << ex.getMessage() << endl;
            }
            stmt->closeResultSet(rs);
            conn->terminateStatement(stmt);
        }
};

int main(int argc, char *argv[])
{
    string user = "U1";
    string password = "123456";
    string db = "orcl";
    conndba *demo = new conndba(user, password, db);

    demo->insertBind("1","john","jj");
	demo->insertBind("2","rose","rs");
	demo->insertBind("3","jack","jk");
    cout << "数据库中的记录：" << endl;
    demo->displayAllRowsDesc();
	
	
	demo->updateRow("jack","6");
	demo->displayAllRowsDesc();

	
    cout << "删除指定id的用户信息！请输入需要删除的用户id：" << endl;
    string id="";
    cin>>id;
    demo->deleteRow(id);
    cout << "删除指定id的用户信息后！" << endl;
    demo->displayAllRows();
    cout << "调用析构函数进行处理！"<<endl;
    delete (demo);
}