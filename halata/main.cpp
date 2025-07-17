#include "list1.h"
#include <string>

class Bed {
public:
    bool occupancy = false;
    string patientName;
    string condition;
};

class Ward {
public:
    Ward() {
        beds.addLast(Bed());
        beds.addLast(Bed());
        beds.addLast(Bed());
        beds.addLast(Bed());
    }
    int size = 4;
    LinkedList<Bed> beds;
};

class HospitalManagementSystem {
public:
    HospitalManagementSystem() {

    }

    LinkedList<Ward> wards;
    void admitPatient(string patientName, string condition) {
        if (wards.isEmpty()) {
            wards.addLast(Ward());
            wards.pfirst->info.beds.pfirst->info.occupancy = true;
            wards.pfirst->info.beds.pfirst->info.condition = condition;
            wards.pfirst->info.beds.pfirst->info.patientName = patientName;
        }
        else if (wards.plast->info.beds.plast->info.occupancy)
        {
            wards.addLast(Ward());
            wards.plast->info.beds.pfirst->info.occupancy = true;
            wards.plast->info.beds.pfirst->info.condition = condition;
            wards.plast->info.beds.pfirst->info.patientName = patientName;
        }
        else
        {
            Node<Bed>* temp_bed = wards.plast->info.beds.pfirst;
            bool filled = false;
            while (temp_bed != nullptr && !filled)
            {
                if (!temp_bed->info.occupancy)
                {
                    temp_bed->info.occupancy = true;
                    temp_bed->info.condition = condition;
                    temp_bed->info.patientName = patientName;
                    filled = true;
                }
                temp_bed = temp_bed->next;
            }
        }
    }
    void dischargePatient(int bedIndex)
    {
        if (wards.pfirst == nullptr)
        {
            cout << "No wards created yet" << endl;
            return;
        }
        Node<Ward>* temp_ward = wards.pfirst;
        for (int i = 0; i < bedIndex / 4; i++)
        {
            temp_ward = temp_ward->next;
            if (temp_ward == nullptr)
            {
                cout << "Non existing patient" << endl;
                return;
            }
        }
        Node<Bed>* temp_bed = temp_ward->info.beds.pfirst;
        for (int i = 0; i < bedIndex % 4; i++)
        {
            temp_bed = temp_bed->next;
        }
        temp_bed->info.occupancy = false;
        temp_bed->info.condition = "";
        temp_bed->info.patientName = "";
        while (temp_ward != nullptr)
        {
            while (temp_bed != nullptr)
            {
                if (temp_ward == wards.plast && temp_bed == wards.plast->info.beds.plast)
                {
                    temp_bed->info.occupancy = false;
                    temp_bed->info.condition = "";
                    temp_bed->info.patientName = "";
                    break;
                }
                if (temp_bed != nullptr && temp_bed->next == nullptr)
                {
                    temp_bed->info.occupancy = temp_ward->next->info.beds.pfirst->info.occupancy;
                    temp_bed->info.condition = temp_ward->next->info.beds.pfirst->info.condition;
                    temp_bed->info.patientName = temp_ward->next->info.beds.pfirst->info.patientName;
                    break;
                }
                if (temp_bed != nullptr && temp_bed->next->info.occupancy == false)
                {
                    temp_bed->info.occupancy = false;
                    temp_bed->info.condition = "";
                    temp_bed->info.patientName = "";
                    break;
                }
                temp_bed->info.occupancy = temp_bed->next->info.occupancy;
                temp_bed->info.condition = temp_bed->next->info.condition;
                temp_bed->info.patientName = temp_bed->next->info.patientName;
                temp_bed = temp_bed->next;
            }
            temp_ward = temp_ward->next;
            if (temp_ward != nullptr)
            {
                temp_bed = temp_ward->info.beds.pfirst;
            }
        }
    }
    void transferPatient(int sourceBedIndex, int targetBedIndex)
    {
        if (wards.pfirst == nullptr)
        {
            cout << "No wards created yet" << endl;
            return;
        }
        Node<Ward>* temp_ward_source = wards.pfirst;
        for (int i = 0; i < ((sourceBedIndex) / wards.pfirst->info.size); i++)
        {
            temp_ward_source = temp_ward_source->next;
            if (temp_ward_source == nullptr)
            {
                cout << "Non existing patient" << endl;
                return;
            }
        }
        Node<Bed>* temp_bed_source = temp_ward_source->info.beds.pfirst;
        for (int i = 0; i < (sourceBedIndex % wards.pfirst->info.size); i++)
        {
            temp_bed_source = temp_bed_source->next;
        }
        if (!temp_bed_source->info.occupancy)
        {
            cout << "Non existing patient" << endl;
        }
        Node<Ward>* temp_ward_target = wards.pfirst;
        for (int i = 0; i < ((targetBedIndex) / wards.pfirst->info.size); i++)
        {
            temp_ward_target = temp_ward_target->next;
            if (temp_ward_target == nullptr)
            {
                Bed temp_bed;
                temp_bed.condition = temp_bed_source->info.condition;
                temp_bed.occupancy = temp_bed_source->info.occupancy;
                temp_bed.patientName = temp_bed_source->info.patientName;
                dischargePatient(sourceBedIndex);
                Node<Bed>* temp_pbed = wards.plast->info.beds.pfirst;
                while (temp_pbed->info.occupancy)
                {
                    temp_pbed = temp_pbed->next;
                }
                temp_pbed->info.condition = temp_bed.condition;
                temp_pbed->info.occupancy = temp_bed.occupancy;
                temp_pbed->info.patientName = temp_bed.patientName;
                break;
            }
        }
        if (temp_ward_target != nullptr)
        {
            Node<Bed>* temp_bed_target = temp_ward_target->info.beds.pfirst;
            for (int i = 0; i < (targetBedIndex % wards.pfirst->info.size); i++)
            {
                temp_bed_target = temp_bed_target->next;
            }
            if (temp_bed_target->info.occupancy && temp_bed_source->info.occupancy)
            {
                Bed temp_bed;
                temp_bed.condition = temp_bed_target->info.condition;
                temp_bed.occupancy = temp_bed_target->info.occupancy;
                temp_bed.patientName = temp_bed_target->info.patientName;
                temp_bed_target->info.condition = temp_bed_source->info.condition;
                temp_bed_target->info.occupancy = temp_bed_source->info.occupancy;
                temp_bed_target->info.patientName = temp_bed_source->info.patientName;
                temp_bed_source->info.condition = temp_bed.condition;
                temp_bed_source->info.occupancy = temp_bed.occupancy;
                temp_bed_source->info.patientName = temp_bed.patientName;
            }
            else
            {
                Bed temp_bed;
                temp_bed.condition = temp_bed_source->info.condition;
                temp_bed.occupancy = temp_bed_source->info.occupancy;
                temp_bed.patientName = temp_bed_source->info.patientName;
                dischargePatient(sourceBedIndex);
                Node<Bed>* temp_pbed = wards.plast->info.beds.pfirst;
                while (temp_pbed->info.occupancy)
                {
                    temp_pbed = temp_pbed->next;
                }
                temp_pbed->info.condition = temp_bed.condition;
                temp_pbed->info.occupancy = temp_bed.occupancy;
                temp_pbed->info.patientName = temp_bed.patientName;
            }
        }
    }
    void displaySystem()
    {
        Node<Ward>* temp_ward = wards.pfirst;
        int bed_count = 1;
        while (temp_ward != nullptr)
        {
            Node<Bed>* temp_bed = temp_ward->info.beds.pfirst;
            for (int i = 0; i < 4; i++)
            {
                if (temp_bed->info.occupancy)
                {
                    cout << "Bed " << bed_count << ":" << endl;
                    cout << "   Occupied" << endl;
                    cout << "   Name: " << temp_bed->info.patientName << endl;
                    cout << "   Condition: " << temp_bed->info.condition << endl;
                }
                else
                {
                    cout << "Not occupied" << endl;
                }
                bed_count++;
                temp_bed = temp_bed->next;

            }
            temp_ward = temp_ward->next;
        }
    }
    string getPatientInfo(int bedIndex)
    {
        Node<Ward>* temp_ward = wards.pfirst;
        for (int i = 0; i < ((bedIndex) / wards.pfirst->info.size); i++)
        {
            temp_ward = temp_ward->next;
            if (temp_ward == nullptr)
            {
                return "Patient not found";
            }
        }
        Node<Bed>* temp_bed = temp_ward->info.beds.pfirst;
        for (int i = 0; i < (bedIndex % wards.pfirst->info.size); i++)
        {
            temp_bed = temp_bed->next;
        }
        if (!temp_bed->info.occupancy)
        {
            return "Patient not found";
        }
        return (temp_bed->info.patientName + " " + temp_bed->info.condition);
    }
};


int main() 
{
    HospitalManagementSystem hms;
    hms.admitPatient("Roman", "First disease");
    hms.admitPatient("Dmytro", "Second disease");
    hms.admitPatient("Vladislav", "Third disease");
    hms.admitPatient("Sergiu", "Fourth disease");
    hms.admitPatient("Rares", "Fifth disease");
    hms.displaySystem();
    cout << hms.getPatientInfo(0) << endl;
    hms.dischargePatient(0);
    hms.transferPatient(1, 3);
    hms.displaySystem();
    return 0;
}
