
#include <iostream>

using namespace std;
#include <string>
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

const int cost=250;
const int N = 10;
vector<string> v;

class Customer{
public:
    char name[101];
    char contactNo[11];
    char movie[101];
    char time[6];
    int no_Tickets;
    int  payment;
    char seats[101];


    Customer(){

        strcpy(name, "Nan");
        strcpy(contactNo, "000000000");
        strcpy(movie, "NAN");
        strcpy(time, "00:00");
        no_Tickets = 0;
        payment = 0;
        strcpy(seats, "NAN");
    }

    void store_custDetails();

    bool get_custData(char[], char[]);

    bool get_custData();

    void add_Seats(vector<string>);

    void show_custData();

    void show_Seats();
};

void Customer::store_custDetails(){

    ofstream fout;
    fout.open("Customer.txt", ios::app | ios::binary);

    fout.write((char *)this, sizeof(*this));

    fout.close();
}

bool Customer::get_custData(char nam[], char m_num[]){

    bool flag = true;

    ifstream fin;
    fin.open("Customer.txt", ios::in | ios::binary);

    if (!fin)
    {
        cout << "\nData Not Found!!!";
    }

    while (fin.read((char *)this, sizeof(*this)))
    {
        if (!fin.eof())
        {

            if (strcmp(name, nam) == 0 && strcmp(contactNo, m_num) == 0)
            {
                show_custData();
                flag = false;
            }
        }
    }

    fin.close();

    if (flag)
        cout << "\nNO Data Found!!!";
    return flag;
    // cout << " show cust data completed" << endl;
}

bool Customer::get_custData(){
    bool flag = true;

    ifstream fin;
    fin.open("Customer.txt", ios::in | ios::binary);

    if (!fin)
    {
        cout << "\n No available bookings ";
    }

    while (fin.read((char *)this, sizeof(*this)))
    {

        if (!fin.eof())
        {
            show_custData();
            flag = false;
        }
    }

    fin.close();
    return flag;
}

void Customer::add_Seats(vector<string> vec){

    bool flag = true;

    for (string str : vec)
    {

        if (flag)
        {
            strcpy(seats, str.c_str());
            flag = false;
        }

        else
        {
            strcat(seats, str.c_str());
        }

        char ch[] = "*";
        strcat(seats, ch);
    }

    seats[strlen(seats) - 1] = '\0';

    no_Tickets = vec.size();
    payment= no_Tickets *cost;
}

void Customer::show_custData(){

    cout << "\n| " << setw(30) << left << name << " | " << setw(10) << contactNo << " | "
         << setw(30) << left << movie << " | " << setw(8) << time << " | " << setw(7) << no_Tickets << " | " ;

    show_Seats();
}

void Customer::show_Seats(){
    string str = "";

    for (int i = 0; i < strlen(seats); i++)
    {

        if (seats[i] == '*')
            str += " ";

        else
            str += seats[i];
    }

    cout << setw(40) << str << " | "<<setw(5)<<payment<<" | ";
}








class Movie{

public:
    char m_name[101];
    char duration[51];
    char genres[101];
    bool avail_timings[10];

    Movie()
    {
        strcpy(m_name, "NAN");
        strcpy(duration, "00:00");
        strcpy(genres, "XXX");
    }

    Movie(char m[], char d[], char t[], bool time[])

    {
        strcpy(m_name, m);
        strcpy(duration, d);
        strcpy(genres, t);

        for (int i = 0; i < 10; i++)
            avail_timings[i] = time[i];
    }

    vector<Movie> show_Movies();

    vector<string> show_Timings();

    void store_Data();

    void show_Details();
};

class Movie_Show{

public:
    char m_name[101];
    char show_time[6];
    bool seats[10][22];

    Movie_Show()
    {
        strcpy(m_name, "NAN");
        strcpy(show_time, "00:00");
    }

    Movie_Show(char time[], bool seat[10][22])
    {
        strcpy(show_time, time);
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 22; j++)
                seats[i][j] = seat[i][j];
    }

    void add_Data(char[], int i);
    vector<string> show_Data(char[], char[]);

    vector<string> show_Seats();
};

void Movie_Show::add_Data(char name[], int i){

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 22; j++)
            seats[i][j] = 1;

    strcpy(m_name, name);
    strcpy(show_time, v[i].c_str());

    ofstream fout;
    fout.open("Seats.txt", ios::app | ios::binary);

    fout.write((char *)this, sizeof(*this));

    fout.close();
}

vector<string> Movie_Show::show_Seats(){

    int no_Seats;

    while (true)
    {

        cout << "\nEnter the Number of Seats : ";
        cin >> no_Seats;

        if (!cin || no_Seats > 10)
        {
            system("cls");
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            if (no_Seats > 10)
                cout << "-------------------Cannot Select More than 10 Seats at a time---------------------------";

            else
                cout << "--------------------------INVALID Input enter again------------------ ";
        }

        else
        {
            break;
        }
    }

    system("cls");

    HANDLE col;
    col = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 10; i++)
    {
        SetConsoleTextAttribute(col, 7);
        cout << char('A' + i) << "  ";

        for (int j = 0; j < 22; j++)
        {

            if (i == 0 || (j != 4 && j != 5 && !(i > 4 && j <= 4) && j != 16 && j != 17))
            {

                if (seats[i][j])
                {

                    SetConsoleTextAttribute(col, 2); // if seats are available print it in  greeen;
                }

                else
                {
                    SetConsoleTextAttribute(col, 4);
                } // if not available print it in red;}

                cout << setw(4) << j + 1 << " ";
            }

            else
                cout << setw(4) << ""
                     << " ";
        }
        cout << endl
             << endl;
    }

    SetConsoleTextAttribute(col, 7);

    cout << "\nSelect your Seats from the above given Seats:";
    cout << "\n\n\nAvailable: \033[32mGreen Coloured Seats\033[0m" << endl;
    cout << "\nSold Out: \033[31mRed Coloured Seats\033[0m" << endl;

    vector<string> booked_seats;
    unordered_set<string> selected;

    for (int i = 0; i < no_Seats; i++)
    {
        string str;
        char row;
        int x;

        while (true)
        {

            cout << "\n select your seats in the  format A01 : ";
            cout << "\n select your " << i + 1 << "th seat and press enter :  ";

            cin >> str;
            bool flag = true;

            if (str.size() > 3 || str.size() < 2 || !isalpha(str[0]) || !isdigit(str[1]) || (str.size() == 3 && !isdigit(str[2])))

            {

                cin.clear();
                cin.ignore(INT_MAX, '\n');
                // system("cls");
                flag = false;

                cout << "-------------------------INVALID INPUT1---------------------" << endl;
            }

            else
            {

                row = str[0];

                x = str[1] - '0';
                if (str.size() == 3)
                    x = x * 10 + (str[2] - '0');

                if (!isupper(row))
                    row = toupper(row);

                if ((row < 'A' || row > 'J' || x > 22 || x == 0) || (row != 'A' && (x == 5 || x == 6 || x == 17 || x == 18))

                    || ((row == 'F' || row == 'G' || row == 'H' || row == 'I' || row == 'J') && (x == 1 || x == 2 || x == 3 || x == 4)))
                {

                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    // system("cls");

                    cout << "-------------------------INVALID INPUT2---------------------" << endl;
                    flag = false;
                }
            }

            if (flag)
            {
                str = row;
                if (x == 0 || x == 1 || x == 2 || x == 3 || x == 4 || x == 5 || x == 6 || x == 7 || x == 8 || x == 9)
                    str += '0';

                str += to_string(x);

                if (seats[row - 'A'][x - 1])
                {
                    seats[row - 'A'][x - 1] = 0;
                    break;
                }

                else
                {
                    cout << "-------------------------------- seat is already selectd ----------------------";
                }
            }
        }

        booked_seats.push_back(str);
    }

    return booked_seats;
}

vector<string> Movie_Show::show_Data(char name[], char time[]){

    fstream file;

    file.open("Seats.txt", ios::in | ios::out | ios::ate | ios::binary);

    file.seekg(0);

    if (!file)
    {
        cout << "Data Not Found!!!" << endl;
        return {};
    }

    vector<string> res;

    while (file.read((char *)this, sizeof(*this)))
    {

        if (!file.eof())
        {

            if (strcmp(m_name, name) == 0 && strcmp(show_time, time) == 0)
            {

                res = show_Seats();

                file.seekp(file.tellp() - (streamoff)sizeof(*this));

                file.write((char *)this, sizeof(*this));
            }
        }
    }

    file.close();
    return res; // cout << "Show_Data completed" << endl;
}

void Movie::store_Data(){

    ofstream fout;

    fout.open("Movie.txt", ios::app | ios::binary);

    fout.write((char *)this, sizeof(*this));

    fout.close();
    // cout << m_name << " +++++++++++++++++++++Data stored seats++++++++++++++++ " << endl;

    Movie_Show curr;

    for (int i = 0; i < 10; i++)
    {

        if (avail_timings[i])
        {
            curr.add_Data(m_name, i);
        }
    }
}

vector<string> Movie::show_Timings(){
    int count = 0;
    vector<string> res;
    for (int i = 0; i < 10; i++)
    {

        if (avail_timings[i])
        {

            cout << "\n| <" << count + 1 << "> |" << right << setw(20) << v[i] << right << setw(20) << " |";
            res.push_back(v[i]);
            count++;
        }
    }
    return res;
}

void Movie::show_Details(){

    cout << left << setw(30) << m_name << " | " << left << setw(10) << duration << " | " << left << setw(30) << genres << " | ";

    string s = "";

    for (int i = 0; i < 10; i++)
        if (avail_timings[i])
            s += v[i] + " ";

    cout << setw(35) << s << " | ";
}

vector<Movie> Movie::show_Movies(){

    ifstream fin;
    fin.open("Movie.txt", ios::in | ios::binary);

    if (!fin)
    {
        cout << "------------------------------Data Not Found!!!--------------------------------" << endl;
    }

    int i = 1;
    vector<Movie> res;

    while (fin.read((char *)this, sizeof(*this)))
    {

        if (!fin.eof())
        {

            cout << "\n| <" << setw(2) << right << i << setw(1) << ""
                 << "> | ";
            show_Details();
            i++;

            res.push_back(*this);
        }
    }

    fin.close();

    return res;
}












int main()
{

    v = {"12:30", "14:00", "15:30", "16:30", "18:00", "18:45", "19:30", "20:00", "21:30", "22:00"};

    string password;
    int count = 0;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n ";
        cout << "\t\t\t            MOVIE BOOKING SYSTEM               ";
        cout << endl;
        cout << "\t\t\t            Password -";
        cin >> password;
        count++;
    } while (password != "123456" && count < 4);
    if (count == 4)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\t\t\t\t         ------------------------DANGER------------------------- ";
        cout << "\n\t\t\t\t         |       YOU ENTERED 4 TIMES WRONG PASSWORD           |   ";
        cout << "\n\t\t\t\t         |       YOU ARE NOT A VALID USER                      |   ";
        cout << "\n\t\t\t\t         -------------------------------------------------------   " << endl;
        exit(0);
    }

    system("cls");

    while (true)
{

        vector<string> booked_seats;
        Customer Cust;

        cout << "\n\n\n\n\n\n--------------------XYZ MOVIES--------------------" << endl;

        cout << "<1> Book Movie Tickets " << endl
             << "<2> Booking Details " << endl
             << "<3> Inquery" << endl
             << "<4> Exit " << endl;

        int option;

        cout << "Select one Of the above Options (1 or 2 or 3 or 4 ) :  ";

        cin >> option;

        while (1)
        {
            if (cin.fail() || (option != 1 && option != 2 && option != 3 && option!=4)) // returns true when input fails
            {
                cin.clear(); // use to clear error state of buffer

                // ignores rest of the line
                // after first error occurs

                // skips to the next line
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter the valid input : ";
                cin >> option;
            }
            if (!cin.fail())
                break;
        }

        // handle invalid inputs

        system("cls");
        cin.ignore(INT_MAX, '\n');

        if (option == 4)
        {    system("CLS");
           cout<<"\n\t\t\t\tTHANK YOU AND VISIT AGAIN!\n\n\t\t\t\t";
           system("pause");
            break;
        }

        else if (option == 1)
        {
            vector<Movie> curr_movies;
            Movie m1;

            cout << "\n\n\n\n ------------------------------------------------------- Available Movies ---------------------------------------------------";

            cout << "\n|  " << setw(3) << ""
                 << "  | " << setw(15) << "Movie Name" << setw(15) << ""
                 << " | " << setw(10) << "Duration"
                 << " | " << setw(15) << "Genres" << setw(15) << ""
                 << " | " << setw(35) << left << "Available Timings"
                 << " | ";

            cout << "\n ----------------------------------------------------------------------------------------------------------------------------";

            curr_movies = m1.show_Movies();
            if (curr_movies.size() == 0)
            {
                system("cls");
                cout << "NO Movies Available";
                break;
            }

            cout << "\n -----------------------------------------------------------------------------------------------------------------------------";

            int M;
            cout << "\n\nEnter Your Choice for the Movie : ";
            cin >> M;

            while (1)
            {
                if (cin.fail() || M == 0 || M > curr_movies.size()) // returns true when input fails
                {
                    cin.clear(); // use to clear error state of buffer

                    // ignores rest of the line
                    // after first error occurs

                    // skips to the next line
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << " Please enter the valid input : ";
                    cin >> option;
                }
                if (!cin.fail())
                    break;
            }

            strcpy(Cust.movie, curr_movies[M - 1].m_name);
            system("cls");

            cout << "\n\n\n --------------- Select Timings --------------";

            vector<string> movie_Timing;
            movie_Timing = curr_movies[M - 1].show_Timings();

                 cout << "\n ---------------------------------------------";
            int time;

            cout << "\n\n Please Select the time : ";
            cin >> time;

            while (1)
            {
                if (cin.fail()) // returns true when input fails
                {
                    cin.clear(); // use to clear error state of buffer

                    // ignores rest of the line
                    // after first error occurs

                    // skips to the next line
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter the valid input : ";
                    cin >> time;
                }
                if (!cin.fail())
                    break;
            }

            system("cls");
            cin.ignore(INT_MAX, '\n');
            cout << "Enter Your Details: ";

            cout << "\nPlease Enter Your Name : ";
            cin.getline(Cust.name, 100);
            strcpy(Cust.time, movie_Timing[time - 1].c_str());

            cout << "\nPlease Enter Your Contact Number: ";
            cin.getline(Cust.contactNo,11);

            Movie_Show ms;
            booked_seats = ms.show_Data(Cust.movie, Cust.time);

            Cust.add_Seats(booked_seats);

            system("cls");

            if (Cust.no_Tickets == 1)
                cout << "Your Ticket is booked :\n";

            else
                cout << "Your Tickets Are booked :\n";

            cout << "\n\n ------------------------------------------------------------------------------------------------------------------------------------------------------";

            cout << "\n| " << setw(15) << "Name" << setw(15) << ""
                 << " | " << setw(10) << "ContactNO."
                 << " | " << setw(15) << "Movie" << setw(15) << ""
                 << " | "
                 << setw(4) << "Time" << setw(4) << ""
                 << " | " << setw(7) << "Tickets" 
                 << " | " << setw(20) << "Your Seats" << setw(20) << ""
                 << " | "<<setw(5)<<"BILL"<<" | ";

            Cust.show_custData();
            Cust.store_custDetails();

            cout << "\n ------------------------------------------------------------------------------------------------------------------------------------------------------";
        }

        else if (option == 2)
        {

            Customer c1;
            char nam[100], mob_num[11];

            cout << "Enter Customer Name : ";
            cin.getline(nam, 100);

            cout << "Enter  Your Contact Number : ";
            cin.getline(mob_num, 11);

            cout << "\n\n ------------------------------------------------------------------------------------------------------------------------------------------------------";

            cout << "\n| " << setw(15) << "Name" << setw(15) << ""
                 << " | " << setw(10) << "ContactNO."
                 << " | " << setw(15) << "Movie" << setw(15) << ""
                 << " | "
                 << setw(4) << "Time" << setw(4) << ""
                 << " | " << setw(7) << "Tickets" 
                 << " | " << setw(20) << "Your Seats" << setw(20) << ""
                 << " | "<<setw(5)<<"BILL"<<" | ";

            if (strcmp(nam, "showalldata") == 0 && strcmp(mob_num, "-1001-") == 0)
            {

                cout << "\n -----------------------------------------------------------------------------------------------------------------------------------------------------";
                if (c1.get_custData())
                {
                    system("cls");
                    cout << "NO Data Found!!!!!";
                    continue;
                }
            }

            else
            {
                   cout<<"\n";
                if (c1.get_custData(nam, mob_num))
                {
                    system("cls");
                    cout << "NO Available Bookings";
                    continue;
                }
            }

            cout << "\n ------------------------------------------------------------------------------------------------------------------------------------------------------";
        }

        else if(option == 3){

            cout<<" For further information about movies you can download our Application(from the  Google Play Store or from the iOS App Store) or\n contact us at 01234567896523";            //Finding out more about our cinemas
                cout<<"\n Do you want to choose another option(y/n)";
                system("pause");
                system("CLS");


        }

    }
}












//  int main()
//  {

// system("cls");
// v = {"12:30","14:00","15:30", "16:30","18:00", "18:45","19:30","20:00", "21:30", "22:00"};

//     int x = 0;
//     Movie m1;

//     while (x < 10)
//     {
//         x++;

//         cout << "----------------------------------Enter the available Movies -------------------------- " << endl;

//         cout << "Enter the Name of the Movie : ";
//         cin.getline(m1.m_name, 100);
//         cin.clear();

//         cout << "Enter the duration of the Moive : ";
//         cin.getline(m1.duration, 50);

//         cout << "Enter the gerne of the Movie : ";
//         cin.getline(m1.genres, 100);

//         cout << "Avail timings of the movie-> \n";

//         for (int i = 0; i < 10; i++)
//         {
//             cout << "Movie available at " << v[i] << " :";
//             cin >> m1.avail_timings[i];
//         }

//         // cout << " you Entered :" << endl;

//         // cout << m1.m_name << "  " << m1.duration << "  " << m1.genres << " ";

//         for (int i = 0; i < 10; i++)
//             if (m1.avail_timings[i])
//                 cout << v[i] << " ";

//         cout << endl;

//         m1.store_Data();
//         cout << " -----------------------DATA STORED-----------------";
//         m1.show_Movies();

//         int x;

//         while (true)
//         {

//             cout << "\nPress 1 to continue else press 0: ";
//             cin >> x;

//             if (!cin)
//             {
//                 system("cls");
//                 cin.clear();
//                 cin.ignore(INT_MAX, '\n');
//                 cout << "--------------------------INVALID Input enter again------------------ ";
//             }

//             else
//             {
//                 break;
//             }
//         }

//         if (x == 0)
//             break;

//         cin.ignore(INT_MAX, '\n');
//     }

//     cout << "\nout of loop" << endl;
// }
