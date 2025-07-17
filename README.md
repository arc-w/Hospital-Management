This project is homework from my university. The code is my solution. Here is the description:  
You are tasked with developing a patient management system for a small hospital. The hospital
has several wards, and each ward can accommodate a limited number of patients. To efficiently
manage patient admissions, transfers, and discharges across multiple wards, you decide to
implement a data structure that reflects the hospital's needs.  
Your data structure, HospitalManagementSystem, will manage a series of wards, where each
ward has a limited number of beds (up to a maximum of 4 beds per ward for simplicity). Each bed
has an occupancy status (occupied/vacant).  
Methods to implement:  
1. HospitalManagementSystem(): Initializes the management system  
2. void admitPatient(String patientName, String condition): Admits a patient by adding
their name and medical condition to the last available bed of the last ward in the system. If
the last ward is at full capacity, a new ward is created, and the patient is admitted to this
new ward.  
3. void dischargePatient(int bedIndex): Discharges the patient from the bed at the global
index (across all wards) bedIndex. This operation should not leave empty beds in the
arrays (wards). Therefore, subsequent patients must be shifted to fill the gap, possibly
across different wards.  
4. void transferPatient(int sourceBedIndex, int targetBedIndex): Transfers a patient from
one bed to another, adjusting all other patients as needed to maintain the no-empty-beds
requirement.  
5. void displaySystem(): Displays the current occupancy status of all wards, with each ward's
patients shown on a new line.  
6. String getPatientInfo(int bedIndex): Returns the name and condition of the patient in the
bed at the global index bedIndex
