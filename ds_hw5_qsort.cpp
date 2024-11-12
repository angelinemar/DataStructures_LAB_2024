#include <iostream>
#include <string>
#include <vector>

using namespace std;
int n, m;
struct patient{
    string name;
    int age, money;
    int membershipStatus; // 1 member, 0 bukan member
    int joinDate, joinMonth, joinYear, nomorAntri; // Format: YYYY-MM-DD and could be “NaN”
    int datevalue;
};

class Hospital{
public:
    vector<patient> patients;
    void daftarPasienBaru(string name, int age, int money,
                            int isMember, int year, int month, int date, int &noAntri){
        patient newPatient = {name, age, money, isMember, date, month , year, noAntri++, year*365+month*30+date};
        patients.push_back(newPatient);
    }

    void cetak()
    {
        for(int i = 0; i < patients.size(); i++){
            cout << "===== pasien "<< i+1 << ": " << endl;
            cout << "nama: " <<patients[i].name << endl;
            cout << "umur: " << patients[i].age << endl;
            cout << "jumlah uang: " << patients[i].money << endl;
            cout << "member? (0 ga/ 1 iya): " <<patients[i].membershipStatus << endl;
            cout << "tanggal join member: " << patients[i].joinYear << "-" << patients[i].joinMonth
                                        << "-" << patients[i].joinDate << endl;
            cout << "--------------------------------------------------------" << endl;
        }
    }

    void swap(patient& a, patient& b)
    {
        patient temp = a;
        a = b;
        b = temp;
    }
    //People with Hospital Membership
    int partitionPanda(int l, int r){
        patient x = patients[r];
        int i = (l - 1);
        for (int j = l; j <= r - 1; j++) {
            // kalau mereka value yang beda
            if (patients[j].membershipStatus != x.membershipStatus) {
                // if dapet priority 
                if(patients[j].membershipStatus > x.membershipStatus){
                    i++;
                    swap(patients[i], patients[j]);
                }
            }
            // kalau mereka value yang sama cari dengan cara bandingin priority kedua
            else if(patients[j].datevalue != x.datevalue){
                if(patients[j].datevalue < x.datevalue){
                    i++;
                    swap(patients[i], patients[j]);
                }
            }
            else if(patients[j].name != x.name){
                if(patients[j].name < x.name){
                    i++;
                    swap(patients[i], patients[j]);
                }
            }
            else if(patients[j].nomorAntri != x.nomorAntri){
                if(patients[j].nomorAntri < x.nomorAntri){
                    i++;
                    swap(patients[i], patients[j]);
                }
            }            
        }
        swap(patients[i + 1], patients[r]);
        return (i + 1);
    }

    void quickSortPanda(int l, int r)
    {
        if (l < r) {
            int p = partitionPanda(l, r);
            quickSortPanda(l, p - 1);
            quickSortPanda(p + 1, r);
        }
    }

    int partitionBear(int l, int r){
        patient x = patients[r];
        int i = (l - 1);
        for(int j = l; j <= r - 1; j++){
            // kalau mereka value yang berbeda
            if(patients[j].money != x.money){
                if(patients[j].money > x.money){
                    i++;
                    swap(patients[i], patients[j]);
                }
            }
            // kalau mereka value yang sama cari dengan cara bandingin priority kedua
            else if(patients[j].nomorAntri != x.nomorAntri){
                if(patients[j].nomorAntri < x.nomorAntri){
                    i++;
                    swap(patients[i], patients[j]);
                }
            }
        }
        swap(patients[i + 1], patients[r]);
        return (i + 1);
    }

    void quickSortBear(int l, int r){
        if(l < r){
            int b = partitionBear(l, r);
            quickSortBear(l, b - 1);
            quickSortBear(b + 1, r);
        }
    }
    void listOutPatients(int hariKe, int jatahBear, int jatahPanda){
        // List out patients after sorted
        int totalDailyIncome = 0;
        cout << "DAY #" << hariKe << endl;
        if(jatahPanda != 0){
            for(int day = 0; day < jatahPanda; day++){
                cout << patients[day].name << " " << patients[day].age << endl;
                totalDailyIncome += patients[day].money; 
            }
            patients.erase(patients.begin(), patients.begin()+jatahPanda);

            cout << "------------------------" << endl;
            // pastiin isi waiting list skrg 
            cout << "sise pasien: " << patients.size() << endl;
        }
        if(jatahBear != 0){
            for(int day = 0; day < jatahBear; day++){
                // sementara
                cout << patients[day].name << " " << patients[day].age << endl;
                totalDailyIncome += patients[day].money; 
            }
            patients.erase(patients.begin(), patients.begin()+1);
            cout << "-------------------------" << endl;
        }
        // print sisa
        for(int i = 0; i < patients.size(); i++){
            cout <<"sisa: " << patients[i].name << endl;
        }
        // print income today 
        cout << "INCOME TODAY: " << (totalDailyIncome * 90) / 100 << endl;
    }
    void sortFunction(int hariKe, int jatahPanda, int jatahBear){
        // PANDA POLICY
        if(jatahPanda != 0){
            quickSortPanda(0, patients.size()-1);
            // debug
            cetak();
        }

        // BEAR POLICY
        if(jatahBear != 0){
            cout << "harusnya ga masuk sini"<< endl;
            quickSortBear(0, patients.size()-1);
            // debug 
            cetak();
            for(int day = 0; day < jatahBear; day++){

            }
        }
    }
};
//vector<vector<Hospital>> hospitalData;
/*
2 4
Gerraldo Chandra
55 40000 0 NaN
Vivian
20 100000 1 2018-03-12

*/
int main(){
    string name;
    string dateStr;
    int age, money, isMember;
    int nomorAntri = 0;
    int hariKe = 0;
    string date, month, year;
    cin >> n >> m;
    Hospital callHospital;
    cin.ignore();
    for(int i = 0; i < n; i++){
        getline(cin, name);
        cin >> age >> money >> isMember;
        cin.ignore();
        if(isMember == 0){
            cin>> dateStr;
            cin.ignore();
            callHospital.daftarPasienBaru(name, age, money, isMember, 0, 0, 0, nomorAntri);
        }
        else if(isMember == 1){
            getline(cin, year, '-');// cout<<"year = "<<year<<endl;
            getline(cin, month, '-');// cout<<"month = "<<month<<endl;
            getline(cin, date);// cout<<"date = "<<date<<endl;

            int tgl, bln, thn;
            tgl = stoi(date);
            bln = stoi(month);
            thn = stoi(year);
            callHospital.daftarPasienBaru(name, age, money, isMember, thn, bln, tgl, nomorAntri);
        }

    }

//callHospital.sortPanda();
    cout << "enter sort panda" << endl;
    // xtra patients
    for(int day = 0; day < m; day++){
        hariKe += 1;
        cout << "-- HARI EKSTRA KE " << day << endl;
        int p, x, k; // p = xtra pasien, x = pasien prioritas panda, k = pas. prior. bear
        cin >> p >> x >> k;
        if(day > 1){
            //callHospital.sortFunction(hariKe, x, k);
            callHospital.listOutPatients(hariKe, k, x);
        }

        cin.ignore();
        // if gada pasien xtra
        if(p == 0) {
            cout << "HARI INI GADA PASIEN EKSTRA" << endl;
            callHospital.sortFunction(hariKe, x, k);
        }
        else{
            for(int i = 0; i < p; i++){
                cout << "INPUT pasien tambahan ke " << i << endl;
                // ini biar input getlinenya berfungsi ketika loop kali kedua dst
                if(i > 0) cin.ignore();
                getline(cin, name);
                cout << "error" << endl;
                cin >> age >> money >> isMember;
                cout << "error" << endl;
                cin.ignore();
                if(isMember == 0){
                    cin>> dateStr;
                    //cin.ignore();
                    callHospital.daftarPasienBaru(name, age, money, isMember, 0, 0, 0, nomorAntri);
                }
                else if(isMember == 1){
                    cout << "ismember masuk" << endl;
                    getline(cin, year, '-');// cout<<"year = "<<year<<endl;
                    getline(cin, month, '-');// cout<<"month = "<<month<<endl;
                    getline(cin, date);// cout<<"date = "<<date<<endl;
                    int tgl, bln, thn;
                    tgl = stoi(date);
                    bln = stoi(month);
                    thn = stoi(year);
                    callHospital.daftarPasienBaru(name, age, money, isMember, thn, bln, tgl, nomorAntri);
                }
                cout << "ADA TAMBAHAN PASIEN EKSTRA" << endl;
                callHospital.cetak();
            }
        }
        if(day == 0){
            callHospital.listOutPatients(hariKe, k, x);
        }
    }
    return 0;
}
/*

9 4
Gerraldo Chandra
55 40000 0 NaN
Vivian
20 100000 1 2018-03-12
Prof. Chen Yi Shin
19 999990 1 2020-06-13
Kuan Hao Yeh
24 200000 0 NaN
Arthur
30 40500 1 1999-08-29
Nguyen Dang Hoang Khang
17 60000 0 NaN
Achita Kenjiiii
5 700000 1 2020-08-22
Aurick Daniel
45 2000 0 NaN
Angelina Panyananda
11 20200 1 2022-01-01
0 5 0
10 6 6
Mr. Meow
19 2000 0 NaN
Mr. Meow
17 2000 0 NaN
Mr. Meow
99 2000 1 2023-12-01
Mr. Meow
23 2000 0 NaN
Mr. Meow
5 2000 0 NaN
Mr. Meow
16 2000 1 2023-12-01
Mr. Meow
35 2000 1 1992-11-23
Mr. Meow
22 2000 0 NaN
Mr. Meow
19 2000 1 2023-12-01
Mr. Meow
99 2000 1 1983-03-14
1 0 1
Red Version Ultraman
100 10 1 1880-09-12
0 400 300


*/
