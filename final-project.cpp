#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class hopdongthuexe {
private:
    string tennguoithue;
    string biensoxe;
    int thoigianthue;
    string loaixe;

public:
    hopdongthuexe() = default;

    hopdongthuexe(string name, string bienso, int time, string loai) {
        tennguoithue = name;
        biensoxe = bienso;
        thoigianthue = time;
        loaixe = loai;
    }

    string getten() const {
        return tennguoithue;
    }

    string getbiensoxe() const {
        return biensoxe;
    }

    int getthoigianthue() const {
        return thoigianthue;
    }

    string getloaixe() const {
        return loaixe;
    }

    void settennguoithue(const string& name) {
        tennguoithue = name;
    }

    void setbiensoxe(const string& bienso) {
        biensoxe = bienso;
    }

    void setthoigianthue(int time) {
        thoigianthue = time;
    }

    void setloaixe(const string& loai) {
        loaixe = loai;
    }

    void xuatthongtin() const {
        cout << "Nguoi thue: " << tennguoithue << ", Bien so xe: " << biensoxe << ", So ngay thue: " << thoigianthue << ", Loai xe: " << loaixe << endl;
    }
};

class quanlyhopdong {
private:
    hopdongthuexe* danhsachnguoithue;
    int soluong;
    int kichthuoc;

    void morongmang() {
        kichthuoc *= 2;
        hopdongthuexe* mangMoi = new hopdongthuexe[kichthuoc];
        for (int i = 0; i < soluong; ++i) {
            mangMoi[i] = danhsachnguoithue[i];
        }
        delete[] danhsachnguoithue;
        danhsachnguoithue = mangMoi;
    }

public:
    quanlyhopdong() : danhsachnguoithue(new hopdongthuexe[1]), soluong(0), kichthuoc(1) {}

    ~quanlyhopdong() {
        delete[] danhsachnguoithue;
    }

    void themhopdong(const hopdongthuexe& dulieu) {
        if (soluong == kichthuoc) {
            morongmang();
        }
        danhsachnguoithue[soluong++] = dulieu;
    }

    void xuatdanhsachnguoithue() const {
        cout << "Danh sach nguoi thue:\n";
        for (int i = 0; i < soluong; ++i) {
            danhsachnguoithue[i].xuatthongtin();
        }
    }

    void huyhopdong(const string& biensoxe) {
        for (int i = 0; i < soluong; ++i) {
            if (danhsachnguoithue[i].getbiensoxe() == biensoxe) {
                for (int j = i; j < soluong - 1; ++j) {
                    danhsachnguoithue[j] = danhsachnguoithue[j + 1];
                }
                soluong--;
                cout << "Huy hop dong thanh cong.\n";
                return;
            }
        }
        cout << "Khong the tim thay bien so xe: " << biensoxe << ".\n";
    }

    void suahopdong(const string& biensoxe) {
        for (int i = 0; i < soluong; ++i) {
            if (danhsachnguoithue[i].getbiensoxe() == biensoxe) {
                string tenmoi, loaimoi;
                int thoigianmoi;
                cout << "Nhap ten moi: ";
                cin.ignore();
                getline(cin, tenmoi);
                cout << "Nhap so ngay thue moi: ";
                cin >> thoigianmoi;
                cout << "Nhap loai xe moi: ";
                cin.ignore();
                getline(cin, loaimoi);
                danhsachnguoithue[i].settennguoithue(tenmoi);
                danhsachnguoithue[i].setthoigianthue(thoigianmoi);
                danhsachnguoithue[i].setloaixe(loaimoi);
                cout << "Thong tin da duoc cap nhat thanh cong.\n";
                return;
            }
        }
        cout << "Khong the tim thay hop dong thue xe voi bien so: " << biensoxe << ".\n";
    }

    void luuvaofile(const string& filename) const {
        ofstream outfile(filename);
        if (outfile.is_open()) {
            for (int i = 0; i < soluong; ++i) {
                outfile << danhsachnguoithue[i].getten() << "," << danhsachnguoithue[i].getbiensoxe() << "," << danhsachnguoithue[i].getthoigianthue() << "," << danhsachnguoithue[i].getloaixe() << "\n";
            }
            outfile.close();
            cout << "File da duoc luu thanh cong.\n";
        } else {
            cout << "Khong the mo file de luu.\n";
        }
    }

    void docdulieufile(const string& filename) {
        ifstream infile(filename);
        if (infile.is_open()) {
            delete[] danhsachnguoithue;
            danhsachnguoithue = new hopdongthuexe[1];
            soluong = 0;
            kichthuoc = 1;

            string line;
            while (getline(infile, line)) {
                size_t pos = line.find(',');
                if (pos != string::npos) {
                    string name = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    pos = line.find(',');
                    if (pos != string::npos) {
                        string bienso = line.substr(0, pos);
                        line.erase(0, pos + 1);

                        pos = line.find(',');
                        if (pos != string::npos) {
                            int time = stoi(line.substr(0, pos));
                            line.erase(0, pos + 1);

                            string loai = line;

                            themhopdong(hopdongthuexe(name, bienso, time, loai));
                        }
                    }
                }
            }
            infile.close();
            cout << "Doc du lieu tu file thanh cong.\n";
        } else {
            cout << "Khong the mo file de doc.\n";
        }
    }

    const hopdongthuexe* timhopdong(const string& biensoxe) const {
        for (int i = 0; i < soluong; ++i) {
            if (danhsachnguoithue[i].getbiensoxe() == biensoxe) {
                return &danhsachnguoithue[i];
            }
        }
        return nullptr;
    }
};

class thongtincon {
private:
    string loaixe;
    int socho;
    float giathue;

public:
    thongtincon() : loaixe(), socho(0), giathue(0.0f) {}

    thongtincon(string _loaixe, int _socho, float _giathue) {
        loaixe = _loaixe;
        socho = _socho;
        giathue = _giathue;
    }

    string xechon() const {
        return loaixe;
    }

    int chonsocho() const {
        return socho;
    }

    float tinhtien(float songaythue) const {
        return songaythue * giathue;
    }
};

class xulidulieu {
private:
    static const int kichthuocxe = 20;
    thongtincon danhsachcacxe[kichthuocxe];

public:
    xulidulieu() {
        danhsachcacxe[0] = thongtincon("Toyota", 4, 500.0);
        danhsachcacxe[1] = thongtincon("Honda", 4, 450.0);
        danhsachcacxe[2] = thongtincon("Ford", 7, 700.0);
         danhsachcacxe[3] = thongtincon(" huydai", 4, 500.0);
          danhsachcacxe[4] = thongtincon("lamborghini", 4 , 700.0);
           danhsachcacxe[5] = thongtincon("flat", 4, 500.0);
           danhsachcacxe[6] = thongtincon ("infinti",5 , 900.0);
            danhsachcacxe[2] = thongtincon(" jaguar", 5, 840.0);
    }

    void xuatcacloaixe(int socho) const {
        cout << "Danh sach cac xe voi so cho " << socho << ":\n";
        for (int i = 0; i < kichthuocxe; ++i) {
            if (danhsachcacxe[i].chonsocho() == socho) {
                cout << danhsachcacxe[i].xechon() << endl;
            }
        }
    }

    float tinhtienthuexe(const string& loaixe, int songaythue) const {
        for (int i = 0; i < kichthuocxe; ++i) {
            if (danhsachcacxe[i].xechon() == loaixe) {
                return danhsachcacxe[i].tinhtien(songaythue);
            }
        }
        return -1; 
    }
};

int main() {
    quanlyhopdong quanly;
    xulidulieu xulyxe;

    quanly.docdulieufile("pbl.txt");

    int choice;
    do {
        cout << "===============================\n";
        cout << "|          MENU CHINH         |\n";
        cout << "===============================\n";
        cout << "| 1. Them hop dong            |\n";
        cout << "| 2. Hien thi danh sach hd    |\n";
        cout << "| 3. Xoa hop dong             |\n";
        cout << "| 4. Sua thong tin hop dong   |\n";
        cout << "| 5. Xem danh sach xe         |\n";
        cout << "| 6. Tinh tien thue xe        |\n";
        cout << "| 7. Luu danh sach vao file   |\n";
        cout << "| 8. Thoat                    |\n";
        cout << "===============================\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string name, bienso, loaixe;
                int thoigian;
                cout << "Nhap ten nguoi thue: ";
                getline(cin, name);
                cout << "Nhap bien so xe: ";
                getline(cin, bienso);
                cout << "Nhap so ngay thue: ";
                cin >> thoigian;
                cout << "Nhap loai xe: ";
                cin.ignore();
                getline(cin, loaixe);
                quanly.themhopdong(hopdongthuexe(name, bienso, thoigian, loaixe));
                break;
            }
            case 2:
                quanly.xuatdanhsachnguoithue();
                break;
            case 3: {
                string xoabienso;
                cout << "Nhap bien so can xoa: ";
                getline(cin, xoabienso);
                quanly.huyhopdong(xoabienso);
                break;
            }
            case 4: {
                string suabienso;
                cout << "Nhap bien so can sua: ";
                getline(cin, suabienso);
                quanly.suahopdong(suabienso);
                break;
            }
            case 5: {
                int socho;
                cout << "Nhap so cho xe ban muon thue : ";
                cin >> socho;
                xulyxe.xuatcacloaixe(socho);
                break;
            }
            case 6: {
                string bienso;
                cout << "Nhap bien so xe: ";
                getline(cin, bienso);
                const hopdongthuexe* hd = quanly.timhopdong(bienso);
                if (hd) {
                    float money = xulyxe.tinhtienthuexe(hd->getloaixe(), hd->getthoigianthue());
                    if (money >= 0) {
                        cout << "Tien thue xe: " << money << " VND\n";
                    } else {
                        cout << "Oops! Khong co loai xe ban muon thue.\n";
                    }
                } else {
                    cout << "Khong tim thay bien so xe trong danh sach hop dong.\n";
                }
                break;
            }
            case 7:
                quanly.luuvaofile("pbl.txt");
                break;
            case 8:
                cout << "Tam biet! Hen gap lai.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (choice != 8);

    return 0;
}

