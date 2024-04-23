#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct seat_st;
struct customer_st
{
    string cnic = "";
    string name = "";
    string phone = "";
    string history = "";
    vector<seat_st> on_seat_no;
} customers[1200];

struct seat_st {
    bool reserved = false;
    customer_st* reserved_by = NULL;
    int no = 0;
};

struct bus_st
{
    bool is_empty = true;
    string name = "";
    string driver = "";
    string arrival = "";
    string departure = "";
    string to = "";
    int cost;
    seat_st seat[72];
    vector<customer_st> passengers;
} bus[10];


int bus_rear = 0, cus_rear = 0, bus_front = 0, cus_front = 0;
void add_bus()
{
    cout << "Enter bus no: ";

    cin >> bus[bus_rear].name;

    cout << "\nEnter Driver's name: ";

    cin >> bus[bus_rear].driver;

    cout << "\nArrival time: ";

    cin >> bus[bus_rear].arrival;

    cout << "\nDeparture: ";

    cin >> bus[bus_rear].departure;

    cout << "\nTo: \t\t\t";

    cin >> bus[bus_rear].to;


    cout << "\nCost: \t\t\t";

    cin >> bus[bus_rear].cost;

    bus_rear++;
}

void edit_bus(string name)
{
    int bus_no;
    for (size_t j = 0; j < 10; j++) {
        if (bus[j].name == name)
        {
            bus_no = j;
        }
    }
    cout << "Enter bus no: ";

    cin >> bus[bus_no].name;

    cout << "\nEnter Driver's name: ";

    cin >> bus[bus_no].driver;

    cout << "\nArrival time: ";

    cin >> bus[bus_no].arrival;

    cout << "\nDeparture: ";

    cin >> bus[bus_no].departure;

    cout << "\nTo: \t\t\t";

    cin >> bus[bus_no].to;


    cout << "\nCost: \t\t\t";

    cin >> bus[bus_no].cost;

}

void remove_customer()
{
    int bus_no;

    for (int i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < bus[i].passengers.size(); j++) {
            if (bus[i].passengers[j].cnic == customers[cus_front].cnic)
            {
                bus_no = j;
                goto skip;
            }
        }
    }
    cout << "\n No more Customers";
    return;

skip:

    for (size_t j = 0; j < customers[cus_front].on_seat_no.size(); j++) {

        customers[cus_front].on_seat_no[j].reserved = false;
        bus[bus_no].seat[j].reserved = false;
        customers[cus_front].on_seat_no[j].reserved_by = NULL;
        bus[bus_no].seat[j].reserved_by = NULL;

    }

    for (size_t j = 0; j < bus[bus_no].passengers.size(); j++) {

        if (bus[bus_no].passengers[j].cnic == customers[cus_front].cnic)
        {
            bus[bus_no].passengers.erase(bus[bus_no].passengers.begin() + j);
        }
    }
    customers[cus_front].on_seat_no.clear();
    cus_front++;
}
void remove_customer(string cnic)
{
    int bus_no, cus_no;

    for (int i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < bus[i].passengers.size(); j++) {
            if (bus[i].passengers[j].cnic == cnic)
            {
                bus_no = j;
                goto skip;
            }
        }
    }
    cout << "\n CNIC Not found!!!";
    return;

skip:
    for (size_t j = 0; j < cus_rear; j++) {
        if (customers[j].cnic == cnic)
        {
            cus_no = j;
        }
    }



    for (size_t j = 0; j < customers[cus_no].on_seat_no.size(); j++) {

        customers[cus_no].on_seat_no[j].reserved = false;
        bus[bus_no].seat[j].reserved = false;
        customers[cus_no].on_seat_no[j].reserved_by = NULL;
        bus[bus_no].seat[j].reserved_by = NULL;

    }

    for (size_t j = 0; j < bus[bus_no].passengers.size(); j++) {

        if (bus[bus_no].passengers[j].cnic == customers[cus_no].cnic)
        {
            bus[bus_no].passengers.erase(bus[bus_no].passengers.begin() + j);
        }
    }
    customers[cus_no].name = "";
    customers[cus_no].cnic = "";
    customers[cus_no].phone = "";
    customers[cus_no].history = "";
    customers[cus_no].on_seat_no.clear();
}

void remove_customer(int bus_no, int cst)
{



skip:

    for (size_t j = 0; j < customers[cst].on_seat_no.size(); j++) {

        customers[cst].on_seat_no[j].reserved = false;
        bus[bus_no].seat[j].reserved = false;
        customers[cst].on_seat_no[j].reserved_by = NULL;
        bus[bus_no].seat[j].reserved_by = NULL;


    }

    for (size_t j = 0; j < bus[bus_no].passengers.size(); j++) {

        if (bus[bus_no].passengers[j].cnic == customers[cst].cnic)
        {
            bus[bus_no].passengers.erase(bus[bus_no].passengers.begin() + j);
        }
    }
    customers[cst].on_seat_no.clear();
}

customer_st create_customer()
{

    customer_st cst;
    cout << "\nEnter Customer Name";
    cin >> cst.name;
    cout << "\nEnter Customer CNIC";
    cin >> cst.cnic;
    cout << "\nEnter Customer Phone";
    cin >> cst.phone;

    return(cst);
}

void clear_bus(int n)
{
    size_t k{};
    if (bus[n].is_empty)
    {
        return;
    }
    for (size_t i = cus_front; i <= cus_rear; i++) {
        if (customers[i].cnic == bus[n].passengers[0].cnic)
        {
            k = i;

            break;
        }
    }

    for (int j = 0; j < bus[n].passengers.size(); j++) {

        remove_customer(n, k);
        k++;
    }
    bus[n].is_empty = true;
}

void display_all_customers()
{
    for (int a = cus_front; a <= cus_rear; a++)
    {
        cout << endl << customers[a].name << " ";
        cout << customers[a].history;
    }
}

void display_seats(int bus_rear)
{
    for (int ra = 0; ra < 72; ra++)
    {

        if (ra % 6 == 0)
        {
            cout << "\n";
        }
        if (bus[bus_rear].seat[ra].reserved == true)
        {
            cout << " [rsvd]";
        }
        else
        {
            cout << " [free]";
        }
    }
}

int get_free_seats(int current_bus)
{
    int free_seats = 0;

    for (int i = 0; i < 72; i++)

    {




        if (bus[current_bus].seat[i].reserved == false)

        {

            free_seats++;

        }




    }

    return(free_seats);
}
void reserve_seats()

{

    int no_of_seats{};

    string bus_id;

top:

    cout << "Enter Bus ID: ";

    cin >> bus_id;

    int n;

    if (bus_rear == 0)
    {
        cout << "\nError!!! no busses have been added yet";
        return;
    }

    for (n = 0; n <= bus_rear; n++)

    {
        if (bus[n].name == bus_id)
        {

            break;
        }
    }

    while (n <= bus_rear)

    {
        bus[n].is_empty = false;
        display_seats(n);
        cout << "\n total free seats in bus are : " << to_string(get_free_seats(n)) << endl;
        cout << "How many seats are needed for reservations?";
        cin >> no_of_seats;

        if (no_of_seats > 1)
        {
            goto multiple;
        }

        for (int r = 0; r < 72; r++)

        {





            if (bus[n].seat[r].reserved == false)

            {
                customers[cus_rear] = create_customer();

                bus[n].seat[r].reserved_by = &customers[cus_rear];
                bus[n].seat[r].reserved = true;
                bus[n].seat[r].no = r;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r]);

                customers[cus_rear].history = customers[cus_rear].history + "\n Sat on bus " + bus[n].name + " on seat no " + to_string(r) + ", alone.";
                bus[n].passengers.push_back(customers[cus_rear]);


                customers[cus_rear].history = customers[cus_rear].history + "Costing " + to_string(bus[n].cost);
                cout << customers[cus_rear].history;
                cus_rear++;
                return;



            }

        }
        cout << "Cannot find empty seat!!!";
        return;

    }

    if (n > bus_rear)

    {

        cout << "Enter correct bus no.\n";

        goto top;

    }
multiple:
    if (no_of_seats > get_free_seats(n))
    {
        cout << "\nUnfortunately, not enough seats availible in this bus";
        return;
    }
    char adj;
    cout << "\n Would you like them adjacent?";
    cin >> adj;

    if (adj == 'y' || adj == 'Y')
    {

        int counter = 0;
        customers[cus_rear] = create_customer();
        customers[cus_rear].history = customers[cus_rear].history + "\n Sat on bus " + bus[n].name + " on seat no ";

        for (int r = 0; r < 72; r += 3)


        {



            if (bus[n].seat[r].reserved == false && bus[n].seat[r + 1].reserved == false && bus[n].seat[r + 2].reserved == false && no_of_seats > counter && (no_of_seats - counter) >= 3)

            {
                bus[n].seat[r].reserved_by = &customers[cus_rear];
                bus[n].seat[r].reserved = true;
                bus[n].seat[r].no = r;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r]);
                customers[cus_rear].history = customers[cus_rear].history + to_string(r) + ", ";
                counter++;

                bus[n].seat[r + 1].reserved_by = &customers[cus_rear];
                bus[n].seat[r + 1].reserved = true;

                bus[n].seat[r + 1].no = r + 1;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r + 1]);
                customers[cus_rear].history = customers[cus_rear].history + to_string(r + 1) + ", ";
                counter++;

                bus[n].seat[r + 2].reserved_by = &customers[cus_rear];
                bus[n].seat[r + 2].reserved = true;

                bus[n].seat[r + 2].no = r + 2;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r + 2]);
                customers[cus_rear].history = customers[cus_rear].history + to_string(r + 2) + ", ";

                counter++;
            }

            else if (bus[n].seat[r].reserved == false && bus[n].seat[r + 1].reserved == false && no_of_seats > counter && (no_of_seats - counter) >= 2)

            {

                bus[n].seat[r].reserved_by = &customers[cus_rear];
                bus[n].seat[r].reserved = true;

                bus[n].seat[r].no = r;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r]);
                customers[cus_rear].history = customers[cus_rear].history + to_string(r) + ", ";
                counter++;

                bus[n].seat[r + 1].reserved_by = &customers[cus_rear];
                bus[n].seat[r + 1].reserved = true;

                bus[n].seat[r + 1].no = r + 1;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r + 1]);
                customers[cus_rear].history = customers[cus_rear].history + to_string(r + 1) + ", ";
                counter++;

            }

            else if (bus[n].seat[r].reserved == false && no_of_seats > counter)

            {

                bus[n].seat[r].reserved_by = &customers[cus_rear];
                bus[n].seat[r].reserved = true;

                bus[n].seat[r].no = r;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r]);
                customers[cus_rear].history = customers[cus_rear].history + to_string(r) + ", ";
                counter++;

            }



            if (counter >= no_of_seats)
            {
                customers[cus_rear].history = customers[cus_rear].history + " with " + to_string(no_of_seats - 1) + " other people";
                bus[n].passengers.push_back(customers[cus_rear]);

                break;
            }
        }
        customers[cus_rear].history = customers[cus_rear].history + "Costing " + to_string((bus[n].cost) * no_of_seats);
        cout << customers[cus_rear].history;
        cus_rear++;
    }
    else
    {
        int counter = 0;
        customers[cus_rear] = create_customer();
        customers[cus_rear].history = customers[cus_rear].history + "\n Sat on bus " + bus[n].name + " on seat no ";
        for (int r = 0; r < 72; r++)

        {




            if (bus[n].seat[r].reserved == false && no_of_seats > counter)

            {
                bus[n].seat[r].reserved_by = &customers[cus_rear];
                bus[n].seat[r].reserved = true;

                bus[n].seat[r].no = r;
                customers[cus_rear].on_seat_no.push_back(bus[n].seat[r]);
                customers[cus_rear].history = customers[cus_rear].history + to_string(r) + ", ";
                counter++;
            }





            if (counter >= no_of_seats)
            {


                customers[cus_rear].history = customers[cus_rear].history + " with " + to_string(no_of_seats - 1) + " other people";
                bus[n].passengers.push_back(customers[cus_rear]);

                break;
            }
        }

        customers[cus_rear].history = customers[cus_rear].history + " Costing " + to_string((bus[n].cost) * no_of_seats);
        cout << customers[cus_rear].history;
        cus_rear++;

    }

}



void show_bus_data()

{
    int n;
    string given_id;

    cout << "Enter bus no: ";

    cin >> given_id;

    for (n = 0; n <= bus_rear; n++)

    {

        if (bus[n].name == given_id)

            break;

    }

    while (n <= bus_rear)

    {

        cout << "\n================================================================================";

        cout << "\nBus no: \t" << bus[n].name

            << "\nDriver: \t" << bus[n].driver << "\t\tArrival time: \t"

            << bus[n].arrival << "\tDeparture time:" << bus[n].departure

            << "\t\tTo: \t\t" << bus[n].to << "\n";

        cout << "\n================================================================================";

        display_seats(n);

        int free_seats = get_free_seats(n);

        cout << "\n total free_seats in bus are : " << to_string(free_seats) << endl;

        customer_st ctemp;


        for (size_t i = 0; i < bus[n].passengers.size(); i++) {

            cout << "\nCustomer " << bus[n].passengers[i].name << " has reserved seat no";

            ctemp = bus[n].passengers[i];

            for (size_t j = 0; j < bus[n].passengers[i].on_seat_no.size(); j++) {

                cout << to_string(ctemp.on_seat_no[j].no) << ", ";

            }

        }


        break;

    }

    if (n > bus_rear)

        cout << "Enter correct bus no: ";

}


void show_all_buses()

{


    for (int n = 0; n < bus_rear; n++)

    {

        cout << "\n================================================================================";

        cout << "Bus no: \t" << bus[n].name << "\nDriver: \t" << bus[n].driver

            << "\t\tArrival time: \t" << bus[n].arrival << "\tDeparture Time: \t"

            << bus[n].departure << "\t\tTo: \t\t\t"

            << bus[n].to << "\n";

        cout << "\n================================================================================";

    }

}

void main()
{

    system("cls");

    int w;

    while (1)

    {

        //system("cls");

        cout << "\n\n\n\n\n";

        cout << "\t\t\t1.Add Bus\n\t\t\t"

            << "2.Edit Bus\n\t\t\t"

            << "3.Reserve seats\n\t\t\t"

            << "4.Show Bus Data\n\t\t\t"

            << "5.Show all Buses\n\t\t\t"

            << "6.Display Customers\n\t\t\t"

            << "7.Clear Bus\n\t\t\t"

            << "8.Remove Customer\n\t\t\t"

            << "9.Exit";

        cout << "\n\t\t\tEnter your choice:-> ";

        cin >> w;

        switch (w)

        {

        case 1:  add_bus();

            break;
        case 2:
        {
            cout << "\nEnter Bus no.";
            string bn;
            cin >> bn;
            edit_bus(bn);

            break;
        }

        case 3:  reserve_seats();

            break;

        case 4:  show_bus_data();

            break;

        case 5:  show_all_buses();

            break;
        case 6:  display_all_customers();

            break;
        case 7:
        {
            cout << "\n Which bus will be dequeued?";
            string a;
            cin >> a;
            for (int b = 0; b < bus_rear; b++)
            {
                if (a == bus[b].name)
                {
                    cout << b;
                    clear_bus(b);
                }
            }

            break;
        }

        case 8:
        {
            cout << "\nEnter CNIC";
            string cnic;
            cin >> cnic;
            remove_customer(cnic);
            break;
        }
        case 9:  exit(0);

        }

    }

}
