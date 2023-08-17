#include <iostream>
using namespace std;

class Node
{
    Node *ptrnext;
    int duration = 30;
    float time;
    bool flag;

public:
    friend class Appointment;
};

class Appointment
{
    Node *start = nullptr;
    int num_of_slots = 8;
    float starttime;

public:
    Appointment()
    {
        cout << "The clinic opens at 9 am in morning and closes at 1 pm in the afternoon." << endl;
        cout << "Each time slot is of 30 mins.." << endl;

        start = new Node;
        start->time = 12.5f;
        start->ptrnext = nullptr;
        start->flag = false;

        starttime = 12.5f;
        Node *currentnode = start;
        for (int i = 1; i < num_of_slots; i++)
        {
            starttime -= 0.5f;
            Node *newnode = new Node;
            newnode->time = starttime;
            newnode->flag = false;
            currentnode->ptrnext = newnode;
            currentnode = newnode;
        }
    }

    ~Appointment()
    {
        Node *node = start;
        for (int i = 1; i <= num_of_slots; i++)
        {
            Node *del = node->ptrnext;
            delete node;
            node = del;
        }
    }

    void book_appointment()
    {
        float t;
        cout << "Enter the time you wish to book the appointment: ";
        cin >> t;
        Node *self = start;
        while (self->time != t)
        {
            self = self->ptrnext;
        }
        if (self->flag == true)
        {
            cout << "Sorry appointment slot is booked already. Enter different slot from mentioned slot" << endl;
            Appointment::display_free_slots();
        }
        else
        {
            cout << "Yours appointment is booked successfully for time " << t << " ." << endl;
            cout << "Duration of appointment is 30 minutes." << endl;
            self->flag = true;
        }
    }

    Node *get(int index)
    {
        Node *self = start;
        for (int i = 0; i < num_of_slots; i++)
        {
            if (i == index)
            {
                return self;
            }
            self = self->ptrnext;
        }
        return nullptr;
    }

    void sorting()
    {
        Node *first, *second;
        for (int i = 0; i < num_of_slots; i++)
        {
            for (int j = 0; j < num_of_slots - i - 1; j++)
            {
                first = get(j);
                second = get(j + 1);
                if (first->time > second->time)
                {
                    float timer = first->time;
                    first->time = second->time;
                    second->time = timer;

                    bool flags = first->flag;
                    first->flag = second->flag;
                    second->flag = flags;
                }
            }
        }
    }

    void display_free_slots()
    {

        cout << "Following time slots are available for appointment......." << endl;
        Node *current = start;
        for (int i = 1; i <= num_of_slots; i++)
        {
            if (current->flag == false)
            {
                cout << "Appointment time: " << current->time << endl;
            }

            current = current->ptrnext;
        }
    }

    void display_booked_slots()
    {
        cout<<"Following slots are booked......."<<endl;
        Node *current = start;
        for (int i = 1; i <= num_of_slots; i++)
        {
            if (current->flag == true)
            {
                cout << "Appointment time: " << current->time << endl;
            }

            current = current->ptrnext;
        }        
    }

    void cancel_appointment()
    {
        float t;
        cout << "Enter the time slot u wish to cancel the appointment: ";
        cin >> t;

        Node *self = start;
        while (self->time != t)
        {
            self = self->ptrnext;
        }

        self->flag = false;
        cout << "Your appointment for time slot " << t << " has been successfully cancelled." << endl;
    }
};

int main()
{
    int option = 1;
    cout << "This is system program for making and cancelling appointments....." << endl;
    Appointment a;
    a.sorting();
    while (option == 1)
    {
        int choice;
        cout << "What you wish to do?" << endl;
        cout << "Press 1 for booking appointment and 2 for cancelling an appointment..";
        cin >> choice;

        if (choice == 1)
        {
            a.display_free_slots();
            a.book_appointment();
        }

        if (choice == 2)
        {
            a.display_booked_slots();
            a.cancel_appointment();
        }

        cout << "If u wish to continue again press 1 else press 0...";
        cin >> option;
    }
}
