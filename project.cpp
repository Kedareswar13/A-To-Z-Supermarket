#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<algorithm>
#include<cctype> // for std::isspace
#include<cstdlib>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BOLD "\033[1m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
using namespace std;
string mobile_number,User_Name,Number;   //Global Declaration
double points;
// Function to remove spaces from a string
string removespaces(const string& str)
{
    string result = str;
    
    // Erase-remove idiom to remove spaces
    result.erase(remove_if(result.begin(), result.end(), [](char c) {
        return isspace(static_cast<unsigned char>(c));
    }), result.end());

    return result;
}
class node
{
    public:
    node *prev;
    int sno;
    string name;
    double price;
    int stock_quantity;
    node *next; 
};
class cart:public node //Inheritence
{
    public:
    cart * prev;
    int quantity;
    double totalprice;
    cart * next;
};
node * List[10000]={NULL};
class ProductList
{
    private:
        node* head;
    public:
        ProductList() { // constructor
        head = NULL;
    }
        void insert(int number,string product_name,double product_price,int product_quantity);
        void display();
        void Delete();
        node * accesshead()
        {
            return head;
        }
};
class SuperMarketBillingSystem    //Main Class
{
    private:
    int pcode;
    string pname;
    double price;
    int quantity;
    public:
    void menu();
    void admin();                //Administrator Function
        void add();
        void edit();
        void Remove();
    void buyer();                 //Buyer Display Function
    void exit4();
};
SuperMarketBillingSystem * obj;
ProductList * newlist;
double discountprice(double quantity,double price)
{
    double product_total=price*quantity;
    if(product_total>5000)
    {
        cout<<"\t\t\tYou are Getting 30% Discount on this Product"<<endl;
        product_total = product_total-(product_total*0.3);
    }
    else if(product_total>=5000)
    {
        cout<<"\t\t\tYou are Getting 25% Discount on this Product"<<endl;
        product_total = product_total - (product_total*0.25);
    }
    else if(product_total>=4000)
    {
        cout<<"\t\t\tYou are Getting 20% Discount on this Product"<<endl;
        product_total = product_total - (product_total*0.2);
    }
    else if(product_total>=3000)
    {
        cout<<"\t\t\tYou are Getting 15% Discount on this Product"<<endl;
        product_total = product_total - (product_total*0.15);
    }
    else if(product_total>=2000)
    {
        cout<<"\t\t\tYou are Getting 10% Discount on this Product"<<endl;
        product_total = product_total - (product_total*0.1);
    }
    else if(product_total >= 1000)
    {
        cout<<"\t\t\tYou are Getting 5% Discount on this Product"<<endl;
        product_total = product_total - (product_total*0.05);
    }
    else{
        cout<<"\t\t\tYou dont have any discount on this Product"<<endl;
    }
    return product_total;
}
class CartList
{
    private:
        cart * head;
        double TotalAmount;
        double Discount;
    public:
        CartList(){
            head = NULL;
            TotalAmount=0;
            Discount=0;
        }
        double Use_Total();
        void Update_Total(double total);
        double Use_Discount();
        void Update_Discount(double discount);
        void insert(int Temp);
        void Display_Items();
        void Delete(); 
        void searchnoadd();
};
double CartList::Use_Total()
{
    return TotalAmount;
}
void CartList::Update_Total(double total)
{
    TotalAmount = total;
}
double CartList::Use_Discount()
{
    return Discount;
}
void CartList::Update_Discount(double discount)
{
    Discount = Discount + discount;
}
void CartList::insert(int Temp)
{
    int number,ref; 
    if(Temp!=0)
    {
        number = Temp;
    }
    cart * newnode = new(cart);
    node * temp = List[number-1];
    cout<<"\t\t\t"<<endl;
    cout<<"\t\t\t The Details of the Product are:";
    cout<<"\t\t\t"<<endl;
    cout<<"\t\t\t Product Name: "<<temp->name<<endl;
    cout<<"\t\t\t Product Key: "<<temp->sno<<endl;
    cout<<"\t\t\t Price of each Product: Rs."<<temp->price<<endl;
    cout<<"\t\t\t"<<endl;
    cout<<"\t\t\tIf You Want to Add This Product into the Cart Press 1 or else if you want to Add Another Product Press 2 : ";
    cin>>ref;
   if(ref==1)
   {
    newnode->name=temp->name;
    newnode->price=temp->price;
    newnode->sno=temp->sno;
    newnode->stock_quantity=temp->stock_quantity;
    cout<<"\t\t\tPlease Enter the quantity of the product you want purchase: ";
    cin>>newnode->quantity;
    temp->stock_quantity -= newnode->quantity;
    newnode->totalprice = discountprice(newnode->quantity,newnode->price);
    TotalAmount+=newnode->totalprice;
    Discount=Discount+((newnode->price*newnode->quantity)-newnode->totalprice);
    if(head == NULL)
    {
        newnode->prev = NULL;
        newnode->next = NULL;
        head = newnode;
    }
    else
    {
        cart * ref = head;
        while(ref->next!=NULL)
        {
            ref = ref->next;
        }
        newnode->next = NULL;
        newnode->prev = ref;
        ref->next = newnode;
    }
    cout<<"\t\t\tThe Product: "<<temp->name<<" has been added to the Cart"<<endl;
  }
  else 
  {
    searchnoadd();
  }
}
void CartList::Display_Items()
{
    cart * ptr = head;
    if(ptr == NULL)
    {
        cout<<"\t\t\t Cart Is Empty"<<endl;
    }
    else
    {
        cout<<"\t\t\tProduct key"<<"\t\t\t"<<"ProductName"<<"\t\t\t\t\t\t"<<"Total Price"<<"\t\t\t"<<endl;
        while(ptr!= NULL)
        {
            cout<<"\t\t\t"<<ptr->sno<<"\t\t\t\t"<<ptr->name<<"\t\t\t"<<ptr->price<<"x"<<ptr->quantity<<"\t\t\t"<<ptr->totalprice<<"\t\t\t"<<endl;
            ptr=ptr->next;
        }
        cout<<"\t\t\t                                                                     \t\t\t"<<endl;
        cout<<"\t\t\tTotal Amount: "<<TotalAmount<<endl;
        cout<<"\t\t\tTotal Discount Price: "<<Discount<<endl;
        cout<<"\t\t\t                                                                     \t\t\t"<<endl;

    }
    
}
void CartList:: Delete() 
{
    m:
    int productcode, count = 0;
    cout << "\t\t\tEnter the Product Key To be deleted: ";
    cin >> productcode;
    cart *ptr = head;
    cart *ref = nullptr;
    
    if (ptr == NULL) 
    {
        cout << "\t\t\t Cart is Empty" << endl;
    }
    while (ptr != NULL) 
    {
        if (ptr->sno == productcode) 
        {
            ref = ptr;
            count++;
            break;
        }
        ptr = ptr->next;
    }
    if (count > 0)
    {
        if (ref->prev == NULL) 
        {
            // Node to be deleted is the head of the list
            head = ref->next;
            if (head != NULL) 
            {
                head->prev = NULL;
            }
        }
        else if (ref->next == NULL) {
            // Node to be deleted is the last node
            (ref->prev)->next = NULL;
        }
        else 
        {
            // Node to be deleted is somewhere in the middle
            (ref->next)->prev = ref->prev;
            (ref->prev)->next = ref->next;
        }
        cout << "\t\t\tSuccessfully Deleted the Product with key: " << ref->sno << endl;
        delete ref;
    } 
    else
    {
        cout << "\t\t\tInvalid Input Key" << endl;
        goto m;
    }
}
void CartList::searchnoadd()
{
    string productname,inputstring,cartstring;

    cout<<"\t\t\t                        "<<endl;
    cout<<"\t\t\tEnter the Product Name\t\t\t";
    cin.ignore();
    getline(cin,productname);
    node * ptr = newlist->accesshead();
    int number,ref,count = 0;
    inputstring = removespaces(productname);
    transform(inputstring.begin(), inputstring.end(), inputstring.begin(), ::tolower);
    while(ptr!=NULL)
    {
        cartstring = removespaces(ptr->name);
        transform(cartstring.begin(), cartstring.end(), cartstring.begin(), ::tolower);
        if(inputstring == cartstring)
        {
            number=ptr->sno;
            count++;
        }
        ptr = ptr->next;
    }
    if(count==0)
    {
        cout<<"\t\t\tNo Such Item is Present in our SuperMarket\t\t\t"<<endl;
    }
    else
    {
        insert(number);
    }
}
CartList * cart;
void ProductList::insert(int number,string product_name,double product_price,int product_quantity)
{
    node* newnode = new node();
    newnode->sno=number;
    newnode->name=product_name;
    newnode->price=product_price;
    newnode->stock_quantity=product_quantity;
    List[number-1] = newnode;
    if(head==NULL)
    {
        newnode->next = NULL;
        newnode->prev = NULL;        
        head = newnode;
    }
    else
    {
        node* ptr = head;
        while(ptr->next!=NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newnode;
        newnode->next = NULL;
        newnode->prev = ptr;
    }
}
void ProductList::display()
{
    node* ptr = head;
    cout<<"\t\t\t\t"<<endl;
    cout<<BOLD<<"\t\t\t                                       PRODUCT MENU"<<endl;
    cout<<"\t\t\t\t"<<endl;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
    cout<<"\t\t\t"<<endl;
    while(ptr!= NULL)
    {
        if(ptr->sno == 1011)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                DRY FRUITS  "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1021)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                CHOCOLATES "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1031)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                PHARMACY "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1041)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                SKIN CARE PRODUCTS "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1051)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                ACCESSORIES "<<endl; 
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1061)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                STATIONARY "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1071)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                FOOD ITEMS "<<endl;
            cout<<"\t\t\t\t\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1081)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                BEVERAGES "<<endl;
            cout<<"\t\t\t\t\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1091)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                ELECTRONICS "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1101)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                CHIPS "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1111)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                SOAP AND DETERGENT "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1121)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                FROZEN FOOD "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1131)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                               FRUITS "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1141)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                VEGETABLES "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1151)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                ICREAM "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1161)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                               CONDIMENTS AND SPICES "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;
        }
        else if( ptr->sno == 1171)
        {
            cout<<"\t\t"<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\t\t\t                                CEREALS AND PULSES "<<endl;
            cout<<"\t\t"<<endl;
            cout<<"\t\tProduct Key"<<"\t\t"<<"ProductName"<<setw(40)<<right<<"\t\t"<<" Price "<<"\t"<<endl;
            cout<<"\t\t"<<endl;        
        }

        cout<<"\t\t"<<ptr->sno<<"\t\t\t"<<ptr->name<<setw(40)<<right<<ptr->price<<"\t\t"<<endl;          
        ptr =ptr->next;  
    }
}
void ProductList::Delete()
{
    node * ptr = head;
    node * ref;
    while(ptr!=NULL)
    {
        ref = ptr;
        ptr = ptr->next;
        delete(ref);
    }
}
void SuperMarketBillingSystem::menu()
{
    menu:
    cout<<BOLD<<RED<<"\t\t                                /$$$$$$         /$$$$$$$$               /$$$$$$$$                             \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                               /$$__  $$       |__  $$__/              |_____ $$                              \t\t"<<RESET<<endl;                                                    
    cout<<BOLD<<RED<<"\t\t                              | $$  $ $$          | $$  /$$$$$$             /$$/                              \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$$$$$$$  /$$$$$$ | $$ /$$__  $$  /$$$$$$  /$$/                               \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$__  $$ |______/ | $$| $$  $ $$ |______  /$$/                                \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$  | $$          | $$| $$  | $$         /$$/                                 \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$  | $$          | $$|  $$$$$$/        /$$$$$$$$                             \t\t"<<RESET<<endl;                                                    
    cout<<BOLD<<RED<<"\t\t                              |__/  |__/          |__/ $_____/        |________/                              \t\t"<<RESET<<endl; 
    cout<<BOLD<<RED<<"\t\t                                                                                                                 \t\t"<<RESET<<endl;                                                                                                                                                                     
    cout<<BOLD<<RED<<"\t\t  /$$$$$$  /$$   /$$ /$$$$$$$  /$$$$$$$$ /$$$$$$$  /$$      /$$  /$$$$$$  /$$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$$$\t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t /$$__  $$| $$  | $$| $$__  $$| $$_____/| $$__  $$| $$$    /$$$ /$$__  $$| $$__  $$| $$  /$$/| $$_____/|__  $$__/\t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t| $$  $__/| $$  | $$| $$  $ $$| $$      | $$  $ $$| $$$$  /$$$$| $$  | $$| $$  } $$| $$ /$$/ | $$         | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t|  $$$$$$ | $$  | $$| $$$$$$$/| $$$$$   | $$$$$$$/| $$ $$/$$ $$| $$$$$$$$| $$$$$$$/| $$$$$/  | $$$$$      | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t $____  $$| $$  | $$| $$____/ | $$__/   | $$__  $$| $$  $$$| $$| $$__  $$| $$__  $$| $$  $$  | $$__/      | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t /$$  $ $$| $$  | $$| $$      | $$      | $$  $ $$| $$$    | $$| $$  | $$| $$  | $$| $$   $$ | $$         | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t|  $$$$$$/|  $$$$$$/| $$      | $$$$$$$$| $$  | $$| $$     | $$| $$  | $$| $$  | $$| $$   $$ | $$$$$$$$   | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t $______/  $______/ |__/      |________/|__/  |__/|__/     |__/|__/  |__/|__/  |__/|__/  __/ |________/   |__/   \t\t"<<RESET<<endl; 
    cout<<"\t\t\t                                                                                                           \t\t\t"<<endl;
    cout<<"\t\t\t                                                                                                           \t\t\t"<<endl;
    cout<<BLUE<<BOLD<<"\t\t\t\t\t\t\t\t\tMENU\t\t\t\t\t\t\t\t\t\t\t\t"<<RESET<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<BLUE<<BOLD<<"\t\t\t1.)ADMINISTRATOR\t\t\t"<<RESET<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<BLUE<<BOLD<<"\t\t\t2.)BUYER\t\t\t"<<RESET<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<BLUE<<BOLD<<"\t\t\t3.)EXIT\t\t\t"<<RESET<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
    cout<<"\t\t\t"<<endl;
    cout<<RED<<BOLD<<"\t\t\tPlease Enter your choice: "<<RESET;
    int choice;
    cin>>choice;
    cout<<endl;
    switch(choice)
    {
        case 1:admin();
            break;
        case 2:buyer();
            break;
        case 3:exit4();
            exit(0);
        default:
            cout<<"Invalid Choice,Please Enter again"<<endl;
            goto menu;
    }
}
void SuperMarketBillingSystem::admin()
{
    string emailid,password;
    cout<<"\t\t\t"<<endl;
    cout<<"\t\t\t    Please Login into your Account     \t\t\t"<<endl;
    cout<<"\t\t\tEnter your Email Id:                    \t";
    cin>>emailid;
    cout<<"\t\t\tEnter your Password:                    \t";
    cin>>password;
    ifstream file("Login.csv"); 
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
    }
    string mail,pass,line, token;
    int count =0;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, token, ',');
        string mail = token;
        getline(ss, token, ',');
        string pass = token;

        if(mail == emailid && password == pass)
        {
            cout<<"\t\t\t"<<endl;
            cout<<"\t\t\tWelcome Administrator, What task do you want to perform today."<<endl;
            count +=1;
            ajay:
            int choice;
            cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
            cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
            cout<<RED<<BOLD<<"\t\t\t\t\t\t\t\t\tADMINISTRATOR MENU\t\t\t\t\t\t\t\t\t\t\t\t"<<RESET<<endl;
            cout<<"\t\t\t"<<endl;
            cout<<BOLD<<BLUE"\t\t\t 1.) Add Product                                                                                                           \t\t\t"<<RESET<<endl;
            cout<<BOLD<<BLUE"\t\t\t                                                                                                                           \t\t\t"<<RESET<<endl;
            cout<<BOLD<<BLUE"\t\t\t 2.) Modify existing Product                                                                                                        \t\t\t"<<RESET<<endl;
            cout<<BOLD<<BLUE"\t\t\t                                                                                                                           \t\t\t"<<RESET<<endl;
            cout<<BOLD<<BLUE"\t\t\t 3.) Delete the Product                                                                                                         \t\t\t"<<RESET<<endl;
            cout<<BOLD<<BLUE"\t\t\t                                                                                                                           \t\t\t"<<RESET<<endl;
            cout<<BOLD<<BLUE"\t\t\t 4.) Exit                                                                                                                   \t\t\t"<<RESET<<endl;
            cout<<BOLD<<BLUE"\t\t\t                                                                                                                           \t\t\t"<<RESET<<endl;
            cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
            cout<<"\t\t\t"<<endl;
            cout<<BOLD<<RED<<"\t\t\tEnter your choice: "<<RESET;
            cin>>choice;
            switch(choice)
            {
                case 1 : add();
                    break;
                case 2: edit();
                    break;
                case 3: Remove();
                    break;
                case 4:exit4();
                    exit(0);
                default:cout<<"Invalid Choice"<<endl;
            }
            goto ajay;
        }
    }
    if(count==0)
    {
        cout<<"\t\t Invalid Email and Password "<<endl; 
        menu();
    }
    file.close();
}
void SuperMarketBillingSystem:: add()
{ 
    ifstream file("available_products.csv"); 
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
    }
    string pcode,pname,price,quantity;
    cout<<"\t\t\t"<<endl;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
    cout<<"\t\t\t"<<endl;
	cout<<"\n\n\t\t\t Add new product"<<endl;
	cout<<"\t\t\t"<<endl;
	cout<<"\t\t\t Enter the Product code: ";
	cin>>pcode;
	cout<<"\t\t\t"<<endl;
	cout<<"\t\t\t Name of the product: ";
    cin.ignore();
	getline(cin,pname);
	cout<<"\t\t\t"<<endl;
	cout<<"\t\t\t Price of the product: ";
	cin>>price;
	cout<<"\t\t\t"<<endl;
	cout<<"\t\t\t Quantity of the product in the stock Register: ";
	cin>>quantity;
    ofstream File("available_products.csv",ios::app);
    File<< pcode << "," << pname <<","<<price<<","<<quantity<<endl;
    cout<<"\t\t\t"<<endl;
	cout<<"\t\t\t Successfully Added a new Product"<<endl;
    cout<<"\t\t\t"<<endl;
	File.close();
}	
void SuperMarketBillingSystem::edit() {
    string pcode, name, price, quantity, line, token;
    string pkey, c, n, p, d;
    int token1 = 0;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
    cout<<"\t\t\t"<<endl;
    cout << "\n\t\t\t Modify the record";
    cout<<"\t\t\t"<<endl;
    cout << "\n\t\t\t Product code  :";
    cin >> pkey;

    ifstream inFile("available_products.csv");
    if (!inFile.is_open()) {
        cout << "Failed to open the file." << endl;
    } else {
        ofstream outFile("temp.csv", ios::app);

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, token, ',');
            string pcode = token;
            getline(ss, token, ',');
            string name = token;
            getline(ss, token, ',');
            string price = token;
            getline(ss, token, ',');
            string quantity = token;

            if (pkey == pcode) {
                cout<<"\t\t\t"<<endl;
                cout << "\t\t\t Product new code :";
                cin >> c;
                cout<<"\t\t\t"<<endl;
                cout << "\t\t\t Name of the product :";
                cin.ignore();
                getline(cin, n);
                cout<<"\t\t\t"<<endl;
                cout << "\t\t\t Price of the Product :";
                cin >> p;
                cout<<"\t\t\t"<<endl;
                cout << "\t\t\t Quantity:";
                cin >> d;

                outFile << c << "," << n << "," << p << "," << d << "\n";
                cout<<"\t\t\t"<<endl;
                cout << "\t\t\t Record edited "<<endl;
                token1++;
            } else {
                outFile << pcode << "," << name << "," << price << "," << quantity << "\n";
            }
        }
        inFile.close();
        outFile.close();

        if (token1 == 0) {
            cout << "\n\n\n Record not found sorry!"<<endl;
        } else {
            // Rename the temporary file to the original file
            remove("available_products.csv");
            rename("temp.csv", "available_products.csv");
        }
    }
}
void SuperMarketBillingSystem::Remove() {
    string pcode, name, price, quantity, line, token;
    string pkey;
    int token1 = 0;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
    cout<<"\t\t\t"<<endl;
    cout << "\n\t\t\t Remove the record";
    cout<<"\t\t\t"<<endl;
    cout << "\n\t\t\t Product code  :";
    cin >> pkey;

    ifstream inFile("available_products.csv");
    if (!inFile.is_open()) {
        cout << "Failed to open the file." << endl;
    } else {
        ofstream outFile("temp.csv");

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, token, ',');
            string pcode = token;
            getline(ss, token, ',');
            string name = token;
            getline(ss, token, ',');
            string price = token;
            getline(ss, token, ',');
            string quantity = token;

            if (pkey == pcode) {
                cout<<"\t\t\t"<<endl;
                cout << "\n\n\t\t Record deleted "<<endl;
                cout<<"\t\t\t"<<endl;
                token1++;
            } else {
                outFile << pcode << "," << name << "," << price << "," << quantity << "\n";
            }
        }

        inFile.close();
        outFile.close();

        if (token1 == 0) {
            cout << "\n\n Record not found sorry!";
        } else {
            // Rename the temporary file to the original file
            remove("available_products.csv");
            rename("temp.csv", "available_products.csv");
        }
    }
}
void Maintain_List()
{
    newlist = new(ProductList);
    ifstream file("available_products.csv"); 
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return;
    }
    string Name,Price,Quantity,pkey;
    double price;
    int quantity,Pkey;
    string line, token;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        getline(ss, token, ',');
        string pkey = token;
        istringstream(pkey) >> Pkey;   
        getline(ss, token, ',');
        string Name = token;
        getline(ss, token, ',');
        string Price = token;
        istringstream(Price) >> price;
        getline(ss, token, ',');
        string Quantity = token;
        istringstream(Quantity) >> quantity;   
        newlist->insert(Pkey,Name,price,quantity);
    }
    file.close();
}
void Receipt()
{
    int choice;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;cout<<"\t\t\t                                                                    \t\t\t"<<endl;
    cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
    cout<<RED<<BOLD<<"\t\t\t\t\t\t\t\tA-To-Z SuperMarket\t\t\t\t\t\t\t\t\t\t\t\t"<<RESET<<endl;
    cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;cout<<"\t\t\t                                                                    \t\t\t"<<endl;
    cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
    cout<<BLUE<<BOLD<<"\t\t\t\t\t\t\t\t\tRECIEPT\t\t\t\t\t\t\t\t\t\t\t\t"<<RESET<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<BLUE<<BOLD<<"\t\t\tName:           "<<RESET<<BOLD<<RED<<User_Name<<RESET<<"                                      \t\t\t"<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<BLUE<<BOLD<<"\t\t\tMobile Number: "<<RESET<<BOLD<<RED<<Number<<RESET<<"                                          \t\t\t"<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cart->Display_Items();
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;cout<<"\t\t\t                                                                    \t\t\t"<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<"\t\t\t Choose the Method you want to pay with                              \t\t\t"<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<"\t\t\t 1.)UPI                                                              \t\t\t"<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<"\t\t\t 2.)Cash                                                              \t\t\t"<<endl;
    cout<<"\t\t\t                                                                     \t\t\t"<<endl;
    cout<<RED<<BOLD<<"\t\t\tEnter Your Choice: "<<RESET;
    cin>>choice;
    if(choice == 1)
    {
        cout<<"\t\t\t Please Complete your Payment to "<<BOLD<<YELLOW<<" +91 9441754767 "<<RESET<<" using UPI"<<endl;
        obj->exit4();
    }
    else if(choice == 2)
    {
        cout<<"\t\t\t Complete your Payment through cash "<<endl;
        cout<<"\t\t\t The Total Amount is : Rs."<<BOLD<<YELLOW<<cart->Use_Total()<<RESET<<endl;
        obj->exit4();
    }
}

void reedem_points(int Points)
{
    if(cart==NULL)
    {
        cout<<"\t\t\tThe Cart is empty.So You cannot clain any discount"<<endl;
    }
    else
    {
        double total = cart->Use_Total();
        double discount;
        cout<<"\t\t\tThe Discount that can be applied by redeeming the Points are:"<<endl;
        if(Points >100 && Points<=200)
        {
            cout<<"\t\t\tSince the points are in the range 101 - 200 we have applied 5% Discount on the total Amount"<<endl;
            discount = (total*0.05);
            total = total - discount;
            Points = 0;
        }
        else if(Points >200 && Points <=300)
        {
            cout<<"\t\t\tSince the points are in the range 201 - 300 we have applied 10% Discount on the total Amount"<<endl;
            discount = (total*0.10);
            total = total - discount;
            Points = 0;
        }
        else if(Points >300 && Points <=400)
        {
        cout<<"\t\t\tSince the points are in the range 301 - 400 we have applied 15% Discount on the total Amount"<<endl;
        discount = (total*0.15);
        total = total - discount;
        Points = 0;
        }
        else if(Points >400 && Points <=500)
        {
            cout<<"\t\t\tSince the points are in the range 401 - 500 we have applied 20% Discount on the total Amount"<<endl;
            discount = (total*0.20);
            total = total - discount;
            Points = 0;
        }
        else if(Points >500 && Points <=1000)
        {
            cout<<"\t\t\tSince the points are in the range 501 - 1000 we have applied 25% Discount on the total Amount"<<endl;
            discount = (total*0.25);
            total = total - discount;
            Points = 0;
        }
        else if(Points >1000)
        {
            cout<<"\t\t\tSince the points are Greater than 1000,we have applied 30% Discount on the total Amount"<<endl;
            discount = (total*0.30);
            total = total - discount;
            Points = Points-1000;
        }
        else{
            cout<<"\t\t\tThe Points are too low to be redeemed"<<endl;
        }
        cart->Update_Total(total);
        cart->Update_Discount(discount);
        Receipt();
    }
    
}
void Gather_and_update_points()
{
    ifstream file("first1.csv"); 
    if (!file.is_open()) {
        cout <<"Failed to open the file." << endl;
    }
    string poi;
    int count=0;
    string line, token;
    string ref;
    while(1)
    {
        cout<<"\t\t\t"<<endl;
        cout<<BOLD<<BLUE<<"\t\t\tEnter your mobile number:"<<RESET;
        cin>>ref;
        if(ref.length()==10)
        {
            break;
        }
        else{
            cout<<BOLD<<BLUE<<"\t\t\tPlease enter a valid number"<<endl;
        }
    }
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, token, ',');
        string name = token;
        getline(ss, token, ',');
        string number = token;
        getline(ss, token, ',');
        string poi = token;
        istringstream(poi) >> points;
        if(number==ref)
        {
            cout<<"\t\t\t"<<endl;
            cout<<"\t\t\tWelcome back "<<BOLD<<YELLOW<<name<<RESET<<" your mobile number : "<<number<<" has "<<BOLD<<YELLOW<<points<<RESET<<" points in his account"<<endl;
            count +=1;
            number = ref;
            Number = ref;
            User_Name = name;
            break;
        }
    }
    if(count==0)
    {
        cout<<"\t\t\t"<<endl;
        cout<<"\t\t\tThe user doesn't have account"<<endl;
        cout<<"\t\t\t"<<endl;
        cin.ignore();
        getline(cin,User_Name);
        cout<<"\t\t\tWe are Creating a User account with initial balance of 10 points as sigining bonus."<<endl;
        cout<<"\t\t\t"<<endl;
        cout<<"\t\t\tPlease Enter your name: ";
        ofstream File("first1.csv",ios::app);
        points = 10;
        File << User_Name <<","<< ref << "," << 10 <<endl;
        File.close();
    }
    int choice;
    cout<<"\t\t\t"<<endl;
    cout<<endl<<"\t\t\tDo You want to use the points to get additional discount on the total bill"<<endl;
    cout<<"\t\t\t"<<endl;
    cout<<"\t\t\tTo use Points to get Discount Press 1"<<endl;
    cout<<"\t\t\tTo Continue to Recipt without Using points Press 2 : ";
    cin>>choice;
    if(choice==1)
    {
        reedem_points(points);
    }
    else if(choice==2){
        Receipt();
    }
    file.close();
}
void Add_Items()
{
    cart= new(CartList);
    int choice;
    while(1)
    {
        kedar:
        cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;cout<<"\t\t\t                                                                    \t\t\t"<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
        cout<<RED<<BOLD<<"\t\t\t\t\t\t\t\t\tMENU\t\t\t\t\t\t\t\t\t\t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t 1.)Display the available products                                  \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t 2.)Add the Product to the Cart                                     \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t 3.) Display the Cart                                               \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t 4.) Delete Product from the Cart                                   \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t 5.)Exit To Billing                                                 \t\t\t"<<RESET<<endl;
        cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
        cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;cout<<"\t\t\t"<<endl;
        cout<<RED<<BOLD<<"\t\t\tEnter your choice: "<<RESET;
        cin>>choice;
        if(choice==1)
        {
            newlist->display();
        }
        else if(choice == 2)
        {
            cart->searchnoadd();
        }
        else if(choice == 3)
        {
            cout<<BLUE<<BOLD<<"\t\t\t\t\t\t\t\t\tCART\t\t\t\t\t\t\t\t\t\t\t\t"<<RESET<<endl;
            cart->Display_Items();
        }
        else if(choice == 4)
        {
            cart->Delete();
        }
        else if(choice==5)
        {
            Gather_and_update_points();
            break;
        }
        else
        {
            cout<<"\t\t\tPlease Enter a valid option\n";
            goto kedar;
        }
    }
}
void SuperMarketBillingSystem::buyer()
{
    cout<<"\t\t\t"<<endl;
    cout<<"\t\t\t Welcome to A-To-Z SuperMarket , We have exiting Deals Today on variour Products."<<endl;
    cout<<"\t\t\t"<<endl;
    Maintain_List();
    Add_Items();
}
void SuperMarketBillingSystem::exit4()
{
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;cout<<"\t\t\t                                                                    \t\t\t"<<endl;
    cout<<BOLD<<BLUE<<"\t\t\t                                                                    \t\t\t"<<RESET<<endl;
    cout<<BLUE<<BOLD<<"\t\t\t\t\t\t\tTHANK YOU FOR VISITING \t\t\t\t\t\t\t\t\t\t\t\t"<<RESET<<endl;
    cout<<BOLD<<BLUE<<"\t\t\t                                                                                                                           \t\t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t                                /$$$$$$         /$$$$$$$$               /$$$$$$$$                             \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                               /$$__  $$       |__  $$__/              |_____ $$                              \t\t"<<RESET<<endl;                                                    
    cout<<BOLD<<RED<<"\t\t                              | $$  $ $$          | $$  /$$$$$$             /$$/                              \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$$$$$$$  /$$$$$$ | $$ /$$__  $$  /$$$$$$  /$$/                               \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$__  $$ |______/ | $$| $$  $ $$ |______  /$$/                                \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$  | $$          | $$| $$  | $$         /$$/                                 \t\t"<<RESET<<endl;                                                     
    cout<<BOLD<<RED<<"\t\t                              | $$  | $$          | $$|  $$$$$$/        /$$$$$$$$                             \t\t"<<RESET<<endl;                                                    
    cout<<BOLD<<RED<<"\t\t                              |__/  |__/          |__/ $_____/        |________/                              \t\t"<<RESET<<endl; 
    cout<<BOLD<<RED<<"\t\t                                                                                                                 \t\t"<<RESET<<endl;                                                                                                                                                                     
    cout<<BOLD<<RED<<"\t\t  /$$$$$$  /$$   /$$ /$$$$$$$  /$$$$$$$$ /$$$$$$$  /$$      /$$  /$$$$$$  /$$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$$$\t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t /$$__  $$| $$  | $$| $$__  $$| $$_____/| $$__  $$| $$$    /$$$ /$$__  $$| $$__  $$| $$  /$$/| $$_____/|__  $$__/\t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t| $$  $__/| $$  | $$| $$  $ $$| $$      | $$  $ $$| $$$$  /$$$$| $$  | $$| $$  } $$| $$ /$$/ | $$         | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t|  $$$$$$ | $$  | $$| $$$$$$$/| $$$$$   | $$$$$$$/| $$ $$/$$ $$| $$$$$$$$| $$$$$$$/| $$$$$/  | $$$$$      | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t $____  $$| $$  | $$| $$____/ | $$__/   | $$__  $$| $$  $$$| $$| $$__  $$| $$__  $$| $$  $$  | $$__/      | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t /$$  $ $$| $$  | $$| $$      | $$      | $$  $ $$| $$$    | $$| $$  | $$| $$  | $$| $$   $$ | $$         | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t|  $$$$$$/|  $$$$$$/| $$      | $$$$$$$$| $$  | $$| $$     | $$| $$  | $$| $$  | $$| $$   $$ | $$$$$$$$   | $$   \t\t"<<RESET<<endl;
    cout<<BOLD<<RED<<"\t\t $______/  $______/ |__/      |________/|__/  |__/|__/     |__/|__/  |__/|__/  |__/|__/  __/ |________/   |__/   \t\t"<<RESET<<endl; 
    cout<<"\t\t\t                                                                                                           \t\t\t"<<endl;
    cout<<BOLD<<BLUE<<"\t\t\t                                                                                                                           \t\t\t"<<RESET<<endl;        
    cout<<BOLD<<"\t\t_______________________________________________________________________________________________________________________\t\t"<<endl;
    newlist->Delete();
}
int main()
{
    system("cls");
    SuperMarketBillingSystem obj;
    obj.menu();
}