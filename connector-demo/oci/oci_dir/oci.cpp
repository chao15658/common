#include <oci.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include<stdio.h>
using namespace std;
//存放查询数据的结构体
struct result
{
    int userid;
    char ename[20];
    char cname[20];
    result()
    {
	userid=0;
        memset(ename, '\0', sizeof(ename));
        memset(cname, '\0', sizeof(cname));
    }
};

void initEnv(OCIEnv **envhpp, OCIServer **servhpp, OCIError **errhpp, OCISession **usrhpp, OCISvcCtx **svchpp, OCIStmt **stmthpp, string server) 
{
	sword swResult = OCIEnvCreate(envhpp, OCI_DEFAULT, NULL, NULL, NULL, NULL, 0, NULL);
    if (swResult != OCI_SUCCESS && swResult != OCI_SUCCESS_WITH_INFO)
    {
        cout << "Oracle environment initialization error!" << endl;
        exit(1);
    }
    cout << "Oracle environment initialization success!" << endl;
    // 创建错误句柄
    OCIHandleAlloc(*envhpp, (dvoid **)errhpp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0);
    // 创建服务句柄
    OCIHandleAlloc(*envhpp, (dvoid **)servhpp, OCI_HTYPE_SERVER, (size_t)0, (dvoid **)0);
    // 连接服务器，如果失败则获取错误码
    if (OCIServerAttach(*servhpp, *errhpp, (text *)server.c_str(), strlen(server.c_str()), 0) != OCI_SUCCESS)
    {
        int errcno;
        char errbuf[512] = "";
        sb4 errcode;
        // 获取错误指针和 OCI 错误代码
        OCIErrorGet(*errhpp, (ub4)1, (text *)NULL, &errcode, (ub1 *)errbuf, (ub4)sizeof(errbuf), OCI_HTYPE_ERROR);
        errcno = errcode;
        cout << "Oracle server attach error:" << errbuf << endl;
        OCIHandleFree(*envhpp,OCI_HTYPE_ENV);
        OCIHandleFree(*servhpp,OCI_HTYPE_SERVER);
        OCIHandleFree(*errhpp,OCI_HTYPE_ERROR);
        exit(1);
    }
    cout << "Oracle server attach success!"<< endl;
    /***************** 连接数据库 ****************/
    string user = "U1";
    string pas = "123456";
    *errhpp = NULL;
    // 创建错误句柄
    (void) OCIHandleAlloc(*envhpp, (dvoid **)errhpp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0);
    // 创建服务上下文句柄
    (void) OCIHandleAlloc(*envhpp, (dvoid **)svchpp, OCI_HTYPE_SVCCTX, (size_t) 0, (dvoid **)0);
    // 设置属性
    (void) OCIAttrSet(*svchpp, OCI_HTYPE_SVCCTX, *servhpp, (ub4)0, OCI_ATTR_SERVER, *errhpp);
    // 创建用户连接句柄
    (void) OCIHandleAlloc(*envhpp, (dvoid **)usrhpp, (ub4)OCI_HTYPE_SESSION, (size_t) 0, (dvoid **)0);
    // 设置用户名、密码
    (void) OCIAttrSet(*usrhpp, (ub4)OCI_HTYPE_SESSION, (dvoid *)user.c_str(), (ub4)strlen(user.c_str()), (ub4)OCI_ATTR_USERNAME, *errhpp);
    (void) OCIAttrSet(*usrhpp, (ub4)OCI_HTYPE_SESSION, (dvoid *)pas.c_str(), (ub4)strlen(pas.c_str()), (ub4)OCI_ATTR_PASSWORD, *errhpp);
    // 创建会话连接
    if(OCISessionBegin(*svchpp, *errhpp, *usrhpp, OCI_CRED_RDBMS, (ub4)OCI_DEFAULT) != OCI_SUCCESS)
    {
        int errcno;
        char errbuf[512]=
        {    '\0'};
        sb4 errcode;
        // 获取错误指针和 OCI 错误代码
        OCIErrorGet(*errhpp, (ub4)1, (text *)NULL, &errcode, (ub1 *)errbuf, (ub4)sizeof(errbuf), OCI_HTYPE_ERROR);
        errcno = errcode;
        cout << "User session error:" << errbuf << endl;
        OCIHandleFree(*errhpp,OCI_HTYPE_ERROR);
        OCIHandleFree(*usrhpp,OCI_HTYPE_SESSION);
        OCIHandleFree(*svchpp,OCI_HTYPE_SVCCTX);
        exit(1);
    }
    cout << "user session success!" << endl;
    (void) OCIAttrSet(*svchpp, (ub4) OCI_HTYPE_SVCCTX, *usrhpp, (ub4)0, (ub4)OCI_ATTR_SESSION, *errhpp);
    /***********************以上代码已经成建立了一条数据库连接************************/
    /*************** 以下代码是对数据库的各种操作     ***   执行 查询SQL 语句 ******************/
    *errhpp = NULL;
    // 创建一个表达式句柄
    if (OCIHandleAlloc(*envhpp, (dvoid **)stmthpp, OCI_HTYPE_STMT, (size_t)0, (dvoid **)0) != OCI_SUCCESS)
    {
        cout << "Create STMT error !" << endl;
        exit(1);
    }
    cout << "Create stmt success !" << endl;
    // 创建错误句柄
    OCIHandleAlloc(*envhpp, (dvoid **)errhpp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0);
    if (OCIHandleAlloc(*envhpp, (dvoid **)stmthpp, OCI_HTYPE_STMT, (size_t)0, (dvoid **)0) != OCI_SUCCESS)
    {
        cout << "Create STMT error !" << endl;
        exit(1);
    }
    cout << "Create stmt success !" << endl;
    OCIHandleAlloc(*envhpp, (dvoid **)errhpp, OCI_HTYPE_ERROR, (size_t)0, (dvoid **)0);
}

void displayAllRows(OCISvcCtx *svchpp, OCIStmt *stmthpp, OCIError *errhpp)
{
    // Select语句
    char sql1[255] = "select userid, username, loginname from t_user1";
    if (OCIStmtPrepare(stmthpp, errhpp, (text *)sql1, (ub4)strlen(sql1), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT) != OCI_SUCCESS)
    {
        cout << "Create prepare error!" << sql1 << endl;
        exit(1);
    }
    cout << "数据库中的记录："<<endl;
    /********* 绑定参数 ***********/
    // 申请绑定字段的句柄
    OCIDefine *bhp0 = NULL;
    OCIDefine *bhp1 = NULL;
    OCIDefine *bhp2 = NULL;
    // 存放数据的结构
    struct result rst;
    // 指定提取数据长度
    ub2 datalen = 0;
    // 定义指示器变量 , 用于取可能存在空值的字段
    char isnul[6] = "";
    // 定义输出变量 ,
    OCIDefineByPos(stmthpp, &bhp0, errhpp, 1, (dvoid *)&rst.userid, sizeof(rst.userid), SQLT_INT, NULL, &datalen, NULL, OCI_DEFAULT);
    OCIDefineByPos(stmthpp, &bhp1, errhpp, 2, (dvoid *)&rst.ename, sizeof(rst.ename), SQLT_CHR, NULL, &datalen, NULL, OCI_DEFAULT);
    OCIDefineByPos(stmthpp, &bhp2, errhpp, 3, (dvoid *)&rst.cname, sizeof(rst.cname), SQLT_STR, NULL, &datalen, NULL, OCI_DEFAULT);
    // 获取 SQL 语句类型
    ub2 stmt_type;
    OCIAttrGet ((dvoid *)stmthpp, (ub4)OCI_HTYPE_STMT, (dvoid *)&stmt_type, (ub4 *)0, (ub4)OCI_ATTR_STMT_TYPE, errhpp);
    // 执行 SQL 语句
    OCIStmtExecute(svchpp, stmthpp, errhpp, (ub4)0, (ub4)0, (OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_DEFAULT);
    // 获取查询信息
    int rows_fetched;
    while(OCIStmtFetch2(stmthpp, errhpp, 1, OCI_FETCH_NEXT, 1, OCI_DEFAULT) != OCI_NO_DATA)
    {

	cerr<< rst.userid<< "\t"<<rst.ename<< "\t"<<rst.cname<<endl;
    }
    // 获得记录条数
    OCIAttrGet((CONST void *)stmthpp, OCI_HTYPE_STMT, (void *)&rows_fetched, (ub4 *)sizeof(rows_fetched), OCI_ATTR_ROW_COUNT, errhpp);
    cout << " rows :" << rows_fetched << endl;
}


void insert(OCIStmt *stmthpp, OCIError *errhpp, OCISvcCtx *svchpp)
{
    //Insert语句
    char sql2[255] = "insert all into t_user1 (userid, username,loginname)"\
	" values('1', 'liming','ming') into t_user1"\
	" values('2', 'lihua','hua')  into t_user1"\
    " values('3', 'liulei','lei') select 1 from dual";
    // 准备Sql语句
    if (OCIStmtPrepare(stmthpp, errhpp, (text *)sql2, (ub4)strlen(sql2), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT) != OCI_SUCCESS)
    {
        cout << "Create prepare error!" << sql2 << endl;
        exit(1);
    }
    // 执行SQL 语句
    OCIStmtExecute(svchpp, stmthpp, errhpp, (ub4)1, (ub4)0, (OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_DEFAULT);
    cout<<"insert - Success"<<endl;
}

void update(OCIStmt *stmthpp, OCIError *errhpp, OCISvcCtx *svchpp)
{
    // Update语句
    char sql3[255] = "update t_user1 set userid='6' where username='liming'";
    // 准备Sql语句
    if (OCIStmtPrepare(stmthpp, errhpp, (text *)sql3, (ub4)strlen(sql3), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT) != OCI_SUCCESS)
    {
        cout << "Create prepare error!" << sql3 << endl;
        exit(1);
    }
    // 执行SQL 语句
    OCIStmtExecute(svchpp, stmthpp, errhpp, (ub4)1, (ub4)0, (OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_DEFAULT);
    cout<<"update - Success"<<endl;
}

void deleteRow(OCIStmt *stmthpp, OCIError *errhpp, OCISvcCtx *svchpp,int userid)
{
    char sql4[255];
    sprintf(sql4, "delete from t_user1  where userid=%d",userid);
    // 准备Sql语句
    if (OCIStmtPrepare(stmthpp, errhpp, (text *)sql4, (ub4)strlen(sql4), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT) != OCI_SUCCESS)
    {
        cout << "Create prepare error!" << sql4 << endl;
        exit(1);
    }
    // 执行SQL 语句
    OCIStmtExecute(svchpp, stmthpp, errhpp, (ub4)1, (ub4)0, (OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_DEFAULT);
    cout<<"delete - Success"<<endl;
}

void destroyEnv(OCIServer **servhpp, OCIError **errhpp, OCISvcCtx **svchpp, OCIStmt **stmthpp)
{
    // 断开用户会话
    OCILogoff(*svchpp, *errhpp);
    // 断开服务器连接
    OCIServerDetach(*servhpp, *errhpp, OCI_DEFAULT);
    // 释放资源
    OCIHandleFree(*stmthpp, OCI_HTYPE_STMT);
    OCIHandleFree(*svchpp, OCI_HTYPE_SVCCTX);
    OCIHandleFree(*servhpp, OCI_HTYPE_SERVER);
    OCIHandleFree(*errhpp, OCI_HTYPE_ERROR);
}

int main()
{
    // 初始化 OCI 环境句柄指针
    OCIEnv *envhpp = NULL;
    // 初始化服务器句柄
    OCIServer *servhpp = NULL;
    // 用于捕获 OCI 错误信息
    OCIError *errhpp = NULL;
    // 初始化会话句柄
    OCISession *usrhpp = NULL;
    // 初始化服务上下文句柄
    OCISvcCtx *svchpp = NULL;
    // 初始化表达式句柄
    OCIStmt *stmthpp = NULL;
    string server = "orcl";
    // 创建 OCI 环境 , 并设置环境句柄。
    initEnv(&envhpp, &servhpp, &errhpp, &usrhpp, &svchpp, &stmthpp,server);

    //insert、select语句
    insert(stmthpp,errhpp, svchpp);
    displayAllRows(svchpp, stmthpp, errhpp);

    //update语句
    update(stmthpp,errhpp, svchpp);
    displayAllRows(svchpp, stmthpp, errhpp);
	
    //delete语句
    cout << "删除指定的用户信息！请输入需要删除的用户id：" << endl;
    int id=0;
    cin>>id;
    deleteRow(stmthpp,errhpp, svchpp,id);
    displayAllRows(svchpp, stmthpp, errhpp);
    
    //销毁OCI环境
    destroyEnv(&servhpp, &errhpp, &svchpp, &stmthpp);
    return 0;
}
