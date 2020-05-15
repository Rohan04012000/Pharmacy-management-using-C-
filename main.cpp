#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
using namespace std;

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
void AddIteminStock();
void FindItemFromList();
void ShowItemList();
void decide();
void admin();
void pharmacistList();
void DeleteStockItem();
void user();
void pharm();
void customer();
void showmedic();
void BuyMedicine();
char exitSurity;
int imp=0;
int check=0;
int store[100];
int select1[100];
int storeIndex = 0;
int itemIndex = 0;
int tocheck=0;

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
        {
            cout<<"Database Connected"<<endl;
            cout<<"Press any key to continue..."<<endl;
            system("cls");
        }
        else
            cout<<"Failed To Connect!"<<mysql_errno(conn)<<endl;

        conn=mysql_real_connect(conn, "localhost", "rohan", "rohan", "dbms_project", 0, NULL, 0);
        if(conn)
        {
            cout<<"Database Connected To MySql"<<conn<<endl;
            cout<<"Press any key to continue..."<<endl;
            system("cls");
        }
        else
            cout<<"Failed To Connect!"<<mysql_errno(conn)<<endl;
    }
};
void Welcome()
{
    cout<<"Welcome To Pharmacy Management System"<<endl<<endl;
    cout<<"Menu"<<endl;
}
void Welcome1()
{
    cout<<"Welcome To Pharmacy Management System"<<endl<<endl;
}

int main()
{
    system("cls");
    system("title Pharamacy Management Program");
    system("color 0f");
    db_response::ConnectionFunction();
    Welcome();
    decide();
    return 0;
}
void decide()
{
    int one;
    char exitSurity;
    cout<<"\n1.Admin\n2.User\n3.Exit\n";
    cout<<"Pick One:";
    cin>>one;
    switch(one)
    {
        case 1:admin();
                break;
        case 2:user();
                break;
        case 3:ExitProgram:
                cout<<"Program terminating. Are you sure? (y/N): ";
                cin>>exitSurity;
                if(exitSurity=='y' || exitSurity=='Y')
                {
                    exit(0);
                }
                else if(exitSurity=='n' || exitSurity=='N')
                {
                    system("cls");
                    decide();
                }
                else
                {
                    cout<<"Next time choose after read the corresponding line."<<endl;
                    goto ExitProgram;
                }
                break;

        default:cout<<"Please choose between 1 - 7. Press Enter To Continue...";
                system("cls");
                decide();
                break;
    }
}
void admin()
{
    system("cls");
    int num = 1;
    string pwd="";
    int chooseOneFromMenu;
    char second;
    string adminname="";
    int fin = 0;
    Welcome1();
    cin.ignore(1, '\n');
    cout<<"Enter Admin name:";
    getline(cin, adminname);
    cout<<"Enter password: ";
    getline(cin,pwd);

    qstate=mysql_query(conn, "select adminname,pwd from admintable");
    if(!qstate)
    {
        res=mysql_store_result(conn);
        while((row=mysql_fetch_row(res)))
        {
            if((adminname==row[0])&&(pwd==row[1]))
            {
                system("cls");
                Welcome1();
                for (int i=0;i<1;i++)
                {
                    fin = num;
                    cout<<fin<<". Add Pharmacist"<<endl;
                    fin+=num;
                    cout<<fin<<". Show Item List"<<endl;
                    fin += num;
                    cout<<fin<<". Add Item in Stock"<<endl;
                    fin += num;
                    cout<<fin<<". Delete Stock Item"<<endl;
                    fin += num;
                    cout<<fin<<". Exit"<<endl;
                    cout<<"Choose One: ";
                }
                cin>>chooseOneFromMenu;

            switch(chooseOneFromMenu)
            {
                case 1:pharmacistList();
                        break;
                case 2:ShowItemList();
                        break;
                case 3:AddIteminStock();
                        break;
                case 4:DeleteStockItem();
                        break;
                case 5: ExitProgram:
                        cout<<"Program terminating. Are you sure? (y/N): ";
                        cin>>exitSurity;
                        if(exitSurity=='y' || exitSurity=='Y')
                        {
                            exit(0);
                        }
                        else if(exitSurity=='n' || exitSurity=='N')
                        {
                            system("cls");
                            admin();
                        }
                        else
                        {
                            cout<<"Next time choose after read the corresponding line."<<endl;
                            goto ExitProgram;
                        }
                        break;
                default:cout<<"Please choose between 1 - 7. Press Enter To Continue...";
                        system("cls");
                        admin();
                        break;
            }
            }
            else
            {
                cout<<"Something is not correct.check again........."<<endl<<endl;
                cout<<"Press a to try as Admin or other to Exit:";
                cin>>second;
                if(second=='a' || second=='A')
                {
                    admin();
                }
                else
                    exit(0);
            }
        }
    }
}
void pharmacistList()
{
    system("cls");
    int checkbit;
    string fname = "";
    string lname = "";
    string username = "";
    string phoneno="";
    string password="";
    char choose;
    Welcome1();
    cin.ignore(1, '\n');
    cout << "Enter first_Name: ";
    getline(cin, fname);
    cout << "Enter last_name: ";
    getline(cin, lname);
    cout<<"Enter User_name:";
    getline(cin,username);
    cout<<"Enter phone_number:";
    getline(cin,phoneno);
    cout<<"Enter common Password:";
    getline(cin,password);

    if(phoneno.size()!=10)
    {
        system("cls");
        Welcome1();
        cout<<"Entered length of phone number is either short or too long to store into Database";
        cout<<"\nPress 1 to retry or to any other key to exit";
        cin>>checkbit;
        if(checkbit==1)
        {
            pharmacistList();
        }
        else
            exit(0);
    }
    else
    {
        string insert_query="insert into pharmacist(fname,lname,username,phoneno,password) values ('"+fname+"','"+lname+"','"+username+"','"+phoneno+"','"+password+"')";
        const char* q=insert_query.c_str();
        qstate=mysql_query(conn, q);
        if (!qstate)
        {
            cout<<endl<<"Successfully added in database."<<endl;
        }
        else
        {
            cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
        }

        cout<<"Press 'm' to Admin and 'a' to Insert Again Or Any Other key to exit: ";
        cin>>choose;
        if (choose=='m' || choose=='M')
        {
            admin();
        }
        else if (choose=='a' || choose=='A')
        {
            pharmacistList();
        }
        else
        {
            exit(0);
        }
    }
}

void ShowItemList()
{
    system("cls");
    char choose;
    string input;
    Welcome1();
    qstate=mysql_query(conn, "select * from cppcode");
    if(!qstate)
    {
        res=mysql_store_result(conn);
        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n","Name","Company_name","Arival Date","Expire Date","Price_per_medic","Quantity");
        printf("-------------------------------------------------------------------------------------------------------------\n");
        while ((row=mysql_fetch_row(res)))
        {
            printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n",row[1],row[2],row[3],row[4],row[5],row[6]);
        }
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
    }

    cout<<"Press 'm' to Admin any other key to Exit: ";
    cin>>choose;
    if (choose=='m' || choose=='M')
    {
        admin();
    }
    else
    {
        exit(0);
    }
}

void AddIteminStock()
{
    system("cls");
    string name="";
    string company_name="";
    string arival_date="";
    string expire_date="";
    string price="";
    string quantity="";
    char choose;
    Welcome1();
    cin.ignore(1, '\n');
    cout<<"Enter Name: ";
    getline(cin, name);
    cout<<"Enter Company: ";
    getline(cin, company_name);
    cout<<"Enter Arrival Date (dd-mm-yyyy): ";
    getline(cin, arival_date);
    cout<<"Enter Expire Date (dd-mm-yyyy): ";
    getline(cin, expire_date);
    cout<<"Enter Price_per_medic: ";
    getline(cin, price);
    cout<<"Enter Quantity: ";
    getline(cin, quantity);

    string insert_query="insert into cppcode(name,company_name,arival_date,expire_date,price,quantity) values('"+name+"','"+company_name+"',STR_TO_DATE('"+arival_date+"', '%d-%m-%Y'),STR_TO_DATE('"+expire_date+"', '%d-%m-%Y'),'"+price+"','"+quantity+"')";
    const char* q=insert_query.c_str();
    qstate=mysql_query(conn, q);
    if(!qstate)
    {
        cout<<endl<<"Successfully added in database."<<endl;
    }
    else
    {
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
    }

    cout<<"Press 'm' to Admin and 'a' to Insert Again Or Any Other key to exit: ";
    cin>>choose;
    if(choose=='m' || choose=='M')
    {
        admin();
    }
    else if(choose=='a' || choose=='A')
    {
        AddIteminStock();
    }
    else
    {
        exit(0);
    }
}

void DeleteStockItem()
{
    system("cls");
    char choose;
    int itemId;
    string items[5000];
    int indexForId=0;
    bool HaveException=false,NotInDatabase=false;
    Welcome1();
    qstate=mysql_query(conn, "select * from cppcode");
    if(!qstate)
    {
        res=mysql_store_result(conn);
        printf("----------------------------------------------------------\n");
        printf("| %-10s | %-15s | %-10s | %-10s |\n","Column Id","Name","Price_per_medic","Quantity");
        printf("----------------------------------------------------------\n");
        while((row=mysql_fetch_row(res)))
        {
            printf("| %-10s | %-15s | %-10s | %-10s |\n",row[0],row[1],row[5],row[6]);
            items[indexForId] = row[0];
            indexForId++;
        }
        printf("----------------------------------------------------------\n");
    }
    else
    {
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
    }

    try
    {
        cout<<endl;
        cout<<"Enter Item ID: ";
        cin>>itemId;
        cout<<endl;
    }
    catch(exception e)
    {
        cout<<"Please Enter a valid NUMBER."<<endl;
        HaveException=true;
        goto ExitMenu;
    }
    if(HaveException==false)
    {
        stringstream streamid;
        string strid;
        streamid<<itemId;
        streamid>>strid;
        for(int i=0;i<indexForId;i++)
        {
            if(strid!=items[i])
            {
                NotInDatabase=true;
            }
            else
            {
                NotInDatabase=false;
                break;
            }
        }
        if(NotInDatabase==false)
        {
            string delete_query="delete from cppcode where id='"+strid+"'";
            const char* qd=delete_query.c_str();
            qstate=mysql_query(conn, qd);
            if(!qstate)
            {
                cout<<"Successfully Deleted."<<endl;
            }
            else
            {
                cout<<"Failed To Delete!"<<mysql_errno(conn)<<endl;
            }
        }
        else
        {
            cout<<"Item Not Found in database."<<endl;
        }
    }
    ExitMenu:
    cout<<"Press 'm' to Menu, 'd' to delete another item and any other key to Exit: ";
    cin>>choose;
    if(choose=='m' || choose=='M')
    {
        admin();
    }
    else if(choose=='d' || choose=='D')
    {
        DeleteStockItem();
    }
    else
    {
        exit(0);
    }
}

void user()
{
    system("cls");
    Welcome1();
    int one1;
    cout<<"\n1.Customer\n2.Pharmacist\n3.Exit\n";
    cout<<"pick one:";
    cin>>one1;
    switch(one1)
    {
        case 1:customer();
                break;
        case 2:pharm();
                break;
        case 3:ExitProgram:
                cout<<"Program terminating. Are you sure? (y/N): ";
                cin>>exitSurity;
                if(exitSurity=='y' || exitSurity=='Y')
                {
                    exit(0);
                }
                else if(exitSurity=='n' || exitSurity=='N')
                {
                    system("cls");
                    user();
                }
                else
                {
                    cout<<"Next time choose after read the corresponding line."<<endl;
                    goto ExitProgram;
                }
                break;
        default:cout<<"Please choose between 1 - 7. Press Enter To Continue...";
                system("cls");
                user();
                break;
    }

}
void customer()
{
    system("cls");
    Welcome1();
    int one2;
    char safe;
    //tocheck=1;
    if(tocheck==1)
    {
        cout<<"You need to visit Pharmacist to buy medicine";
        cout<<"Press b|B  to go back: ";
        cin>>safe;
        if(safe=='b' || safe=='B')
        {
            user();
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        cout<<"1.Search Medicine list\n2.Exit\n";
        cout<<"Enter your choice:";
        cin>>one2;
        switch(one2)
        {
            case 1:showmedic();
                    break;
            case 2:ExitProgram:
                    cout<<"Program terminating. Are you sure? (y/N): ";
                    cin>>exitSurity;
                    if(exitSurity=='y' || exitSurity=='Y')
                    {
                        exit(0);
                    }
                    else if(exitSurity=='n' || exitSurity=='N')
                    {
                        system("cls");
                        customer();
                    }
                    else
                    {
                        cout<<"Next time choose after read the corresponding line."<<endl;
                        goto ExitProgram;
                    }
                    break;
            default:cout<<"Please choose between 1 - 7. Press Enter To Continue...";
                    system("cls");
                    customer();
                    break;
        }
    }
}

void showmedic()
{
    system("cls");
    Welcome1();
    //tocheck=1;
    FindItemFromList();
}

void FindItemFromList()
{
    system("cls");
    string input="";
    char choose;
    Welcome();
    cin.ignore(1, '\n');
    cout<<"Enter Medicine Name: ";
    getline(cin, input);
    string findbyname_query="select id,name,company_name,price,quantity from cppcode where name like '"+input+"'";
    const char* qn=findbyname_query.c_str();
    qstate=mysql_query(conn, qn);
    cout<<endl;
    if(!qstate)
    {
        res=mysql_store_result(conn);
        while((row=mysql_fetch_row(res)))
        {
            check=1;
            tocheck=1;
            cout<<"\nId: "<<row[0]<<"\nMedicine Name: "<<row[1]<<"\nCompany Name: "<<row[2]<<"\nPrice_per_medic: "<<row[3]<<"\nQuantity: "<<row[4]<<endl<<endl;
        }
        if(check==0)
        {
            cout<<"Medicine name:"<<input<<":not found in list"<<endl<<endl;
        }
    }
    else
    {
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
    }

    cout<<"Press 'm' to Buy_it, 'a' to Search again and any other key to Exit: ";
    cin>>choose;
    if(choose=='m' || choose=='M')
    {
       user();
    }
    else if(choose=='a' || choose=='A')
    {
        FindItemFromList();
    }
    else
    {
        exit(0);
    }
}

void pharm()
{
    system("cls");
    Welcome1();
    char pick;
    string username="";
    string password="";
    if(check==0)
    {
        cout<<"Before buying you need to search your medicine"<<endl<<endl;
        cout<<"Enter u|U to go back to sub_menu: ";
        cin>>pick;
        if(pick=='u' || pick=='U')
        {
            user();
        }
    }
    else
    {
        cin.ignore();
        cout<<"Enter Your Username: ";
        getline(cin,username);
        cout<<"Enter your Password: ";
        getline(cin,password);
        string findbyname_query="select username,password from pharmacist ";
        const char* qn=findbyname_query.c_str();
        qstate=mysql_query(conn, qn);
        if(!qstate)
        {
            res=mysql_store_result(conn);
            while((row=mysql_fetch_row(res)))
            {
                if((username==row[0]) &&(password==row[1]))
                {
                    BuyMedicine();
                }
                else
                {
                    cout<<"YOU are not registered as Pharmacist"<<endl;
                }
            }
        }
    }
}

void BuyMedicine()
{
    system("cls");
    char choose;
    string getId="";
    string itemId[5000];
    string itemName[5000];
    char chooseEditOrBuy;
    int itemIndex=0;
    float totalPrice=0.0;
    bool purchase,itemFalse=false;
    string storeid[5000];
    string storename[5000];
    string storecompany[5000];
    string storearrival_date[5000];
    string storeexpire_date[5000];
    string storeprice[5000];
    string storequantity[5000];
    int storeIndex=0,storeIndexN=0;
    Welcome1();
    qstate=mysql_query(conn, "select * from cppcode");
    if(!qstate)
    {
        res=mysql_store_result(conn);

        while((row=mysql_fetch_row(res)))
        {
            if(atoi(row[6])>0)
            {
                storeid[storeIndex]=row[0];
                storename[storeIndex]=row[1];
                storecompany[storeIndex]=row[2];
                storearrival_date[storeIndex]=row[3];
                storeexpire_date[storeIndex]=row[4];
                storeprice[storeIndex]=row[5];
                storequantity[storeIndex]=row[6];
                storeIndex++;
            }
        }
        //printf("---------------------------------------------------------------------------------------------------------\n");
    }
    else
    {
        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
    }

    for (itemIndex=0;;itemIndex++)
    {
        cout<<"Enter medicine ID's or (q to exit): ";
        cin>>getId;
        if(getId=="q")
        {
            break;
        }
        else
        {
            for(int i=0;i<storeIndex;i++)
            {
                if(getId==storeid[i])
                {
                    itemId[itemIndex]=getId;
                    itemFalse=false;
                    break;
                }
                else
                {
                    itemFalse=true;
                }
            }
            if(itemFalse==true)
            {
                cout<<"Enter a valid number."<<endl;
                itemIndex--;
                itemFalse=false;
            }
        }
    }

    cout<<"You choose this item id's: ";
    for(int i=0;i<itemIndex;i++)
    {
        cout<<itemId[i]<<" ";
    }
    cout<<endl<<"Click b|B to Buy this items: ";
    cin>>chooseEditOrBuy;

    if(chooseEditOrBuy=='b' || chooseEditOrBuy=='B')
    {
        for(int i=0;i<itemIndex;i++)
        {
            for(int j=0;j<storeIndex;j++)
            {
                if(itemId[i]==storeid[j])
                {
                    qstate=mysql_query(conn, "select quantity from cppcode");
                    if(!qstate)
                    {
                        res=mysql_store_result(conn);
                        while((row=mysql_fetch_row(res)))
                        {
                            if(atoi(row[0])>0)
                            {
                                storequantity[storeIndexN]=row[0];
                                storeIndexN++;
                            }
                        }
                        storeIndexN=0;
                    }
                    else
                    {
                        cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
                    }
                    totalPrice += strtof((storeprice[j]).c_str(), 0);
                    float quan1 = strtof((storequantity[j]).c_str(), 0);
                    quan1 -= 1;
                    float quan2=strtof((storequantity[j]).c_str(), 0);
                    float quan=quan2 - quan1;
                    string getResult;
                    stringstream strquan;
                    strquan<<quan;
                    strquan>>getResult;
                    string getQuan1;
                    stringstream strquan1;
                    strquan1<<quan1;
                    strquan1>>getQuan1;
                    purchase=true;
                    string update_query="update cppcode set quantity = '"+getQuan1+"' where id = '"+storeid[j]+"'";
                    const char* qu=update_query.c_str();

                    qstate=mysql_query(conn, qu);
                    if(qstate)
                    {
                        cout<<"Failed To Update!"<<mysql_errno(conn)<<endl;
                    }
                }
            }
        }
        if(purchase==true)
        {
            cout<<endl<<"Purchase Successfully Done."<<endl;
            cout<<endl<<"Total Price: "<<totalPrice<<endl;
        }
    }
    cout<<endl<<"Press key x|X to Exit: ";
    cin>>choose;
    if(choose=='x' || choose=='X')
    {
        exit(0);
    }
}
