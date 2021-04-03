import java.sql.*;
import java.util.Scanner;

public class MySqlTest {

    static String driver = "org.txdb.Driver";
    static String url = "jdbc:txdb://127.0.0.1:6868/txdb_default";
    static String user = "txadmin";
    static String passwd = "txadmin@123";


    /**
     * main函数
     * 先输入操作序号，再输入操作sql
     * @param args
     */
    public static void main(String[] args) {

        int selector = -1;
        boolean res = false;
        System.out.println("Welcome to use JAVA-connect-postgresql-demo," +
                "your program's connection info is listed below");
        System.out.println("driver name :" + driver);
        System.out.println("url :" + url);
        System.out.println("username :" + user);
        System.out.println("password :" + passwd);
        do {
            System.out.println("please input your operation, support operation is:" +
                    " 0(CREATE TABLE), 1(INSERT), 2(UPDATE), 3(DELETE), 4(SELECT), 5(quit): ");
            Scanner scanner = new Scanner(System.in);
            String inputsql = "";
            try {
                selector = scanner.nextInt();
                if(5 != selector) {
                    System.out.println("please input your sql according to your choice");
                    scanner.nextLine();
                    inputsql = scanner.nextLine();
                }
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("input selector " + selector +  " is invalid , please try again");
                continue;
            }
            switch (selector) {
                case 0:
                    res = execDMLonTable(inputsql);
                    if(res) {
                        System.out.println("create table success");
                    }
                    break;
                case 1:
                    res = execDMLonTable(inputsql);
                    if(res) {
                        System.out.println("insert success");
                    }
                    break;
                case 2:
                    res = execDMLonTable(inputsql);
                    if(res) {
                        System.out.println("update success");
                    }
                    break;
                case 3:
                    res = execDMLonTable(inputsql);
                    if(res) {
                        System.out.println("delete success");
                    }
                    break;
                case 4:
                    res = execSELECTonTable(inputsql);
                    break;
                case 5:
                    scanner.close();
                    System.out.println("quit success");
                    return;
                default:
                    System.out.println("input is invalid for " + selector);
                    continue;
            }
            }while (true);
    }

    /**
     * 执行insert/update/delete
     * @param dmlsql
     * @return
     */
    public static boolean execDMLonTable( String dmlsql) {
        Connection conn=null;
        try {
            Class.forName(driver);
            conn = DriverManager.getConnection(url, user, passwd);
            PreparedStatement ps = conn.prepareStatement(dmlsql);
            int rs = ps.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try{
                conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return true;
    }


    /**
     * 执行select
     * @param dmlsql
     * @return
     */
    public static boolean execSELECTonTable( String dmlsql) {
        Connection conn=null;
        try {
            Class.forName(driver);
            conn = DriverManager.getConnection(url, user, passwd);
            conn.getMetaData();
            PreparedStatement ps = conn.prepareStatement(dmlsql);
            ResultSet rs = ps.executeQuery();
            //获取字段列表
            ResultSetMetaData metaData = rs.getMetaData();
            int columns = metaData.getColumnCount();
            for (int i = 1; i <= columns; i++) {
                String columnName = metaData.getColumnName(i);
                System.out.print(" " + columnName + " |");
            }
            System.out.println();
            for (int i = 0; i < columns; i++) {
                System.out.print("--------");
            }
            System.out.println();
            while(rs.next()) {
                String row = "";
                for (int i = 1; i <= columns; i++) {
                    row += rs.getString(i)+"   |    ";
                }
                System.out.print(row);
                System.out.println();
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try{
                conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return true;
    }
}
