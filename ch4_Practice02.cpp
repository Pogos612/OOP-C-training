#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class THIET_BI_VAN_TAI
{
protected:
    string ma_dinh_danh;
    string hang_san_xuat;
    double trong_luong_kg;
    static int tong_so_thiet_bi;

public:
    THIET_BI_VAN_TAI() : ma_dinh_danh(""), hang_san_xuat(""), trong_luong_kg(0.0)
    {
        tong_so_thiet_bi++;
    }

    THIET_BI_VAN_TAI(string ma, string hang, double tl)
        : ma_dinh_danh(ma), hang_san_xuat(hang), trong_luong_kg(tl)
    {
        tong_so_thiet_bi++;
    }

    virtual ~THIET_BI_VAN_TAI()
    {
        tong_so_thiet_bi--;
    }

    virtual void nhap()
    {
        cout << "Nhap thong tin co ban:\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ma dinh danh: ";
        getline(cin, ma_dinh_danh);
        cout << "Hang san xuat: ";
        getline(cin, hang_san_xuat);
        cout << "Trong luong (kg): ";
        cin >> trong_luong_kg;
    }

    virtual void xuat() const
    {
        cout << left
             << setw(15) << ma_dinh_danh
             << setw(20) << hang_san_xuat
             << setw(15) << fixed << setprecision(2) << trong_luong_kg;
    }

    virtual double tinh_hieu_suat_nang_luong() const = 0;

    bool operator>(const THIET_BI_VAN_TAI &other) const
    {
        return this->tinh_hieu_suat_nang_luong() > other.tinh_hieu_suat_nang_luong();
    }

    static void hien_thi_tong_thiet_bi()
    {
        cout << "[INFO] Tong so thiet bi hien co trong bo nho: " << tong_so_thiet_bi << endl;
    }
};

int THIET_BI_VAN_TAI::tong_so_thiet_bi = 0;

class PHUONG_TIEN_BAY : public virtual THIET_BI_VAN_TAI
{
protected:
    double do_cao_bay_toi_da_m;
    double toc_do_gio_kmh;

public:
    PHUONG_TIEN_BAY() : THIET_BI_VAN_TAI(), do_cao_bay_toi_da_m(0.0), toc_do_gio_kmh(0.0) {}

    PHUONG_TIEN_BAY(string ma, string hang, double tl, double dc, double td)
        : THIET_BI_VAN_TAI(ma, hang, tl), do_cao_bay_toi_da_m(dc), toc_do_gio_kmh(td) {}

    void nhap_bay()
    {
        cout << "Do cao bay toi da (m): ";
        cin >> do_cao_bay_toi_da_m;
        cout << "Toc do (km/h): ";
        cin >> toc_do_gio_kmh;
    }

    void xuat_bay() const
    {
        cout << setw(15) << fixed << setprecision(2) << do_cao_bay_toi_da_m
             << setw(15) << toc_do_gio_kmh;
    }
};

class PHUONG_TIEN_THUY : public virtual THIET_BI_VAN_TAI
{
protected:
    double do_sau_lan_m;
    double hai_ly_toi_da;

public:
    PHUONG_TIEN_THUY() : THIET_BI_VAN_TAI(), do_sau_lan_m(0.0), hai_ly_toi_da(0.0) {}

    PHUONG_TIEN_THUY(string ma, string hang, double tl, double ds, double hl)
        : THIET_BI_VAN_TAI(ma, hang, tl), do_sau_lan_m(ds), hai_ly_toi_da(hl) {}

    void nhap_thuy()
    {
        cout << "Do sau lan (m): ";
        cin >> do_sau_lan_m;
        cout << "Hai ly toi da: ";
        cin >> hai_ly_toi_da;
    }

    void xuat_thuy() const
    {
        cout << setw(15) << fixed << setprecision(2) << do_sau_lan_m
             << setw(15) << hai_ly_toi_da;
    }
};

class DRONE_LUONG_CU : public PHUONG_TIEN_BAY, public PHUONG_TIEN_THUY
{
public:
    DRONE_LUONG_CU() : THIET_BI_VAN_TAI(), PHUONG_TIEN_BAY(), PHUONG_TIEN_THUY() {}

    DRONE_LUONG_CU(string ma, string hang, double tl, double dc, double td, double ds, double hl)
        : THIET_BI_VAN_TAI(ma, hang, tl),
          PHUONG_TIEN_BAY(ma, hang, tl, dc, td),
          PHUONG_TIEN_THUY(ma, hang, tl, ds, hl) {}

    void nhap() override
    {
        THIET_BI_VAN_TAI::nhap();
        cout << "--- Thong tin Phuong tien Bay ---\n";
        nhap_bay();
        cout << "--- Thong tin Phuong tien Thuy ---\n";
        nhap_thuy();
    }

    void xuat() const override
    {
        THIET_BI_VAN_TAI::xuat();
        xuat_bay();
        xuat_thuy();
        cout << setw(15) << fixed << setprecision(4) << tinh_hieu_suat_nang_luong() << endl;
    }

    double tinh_hieu_suat_nang_luong() const override
    {
        if (trong_luong_kg == 0)
            return 0.0;
        return (do_cao_bay_toi_da_m * 0.6 + hai_ly_toi_da * 1.8) / trong_luong_kg;
    }
};

int main()
{
    cout << "KHOI TAO HE THONG\n";
    THIET_BI_VAN_TAI::hien_thi_tong_thiet_bi();

    int n;
    cout << "\nNhap so luong drone luong cu: ";
    cin >> n;

    DRONE_LUONG_CU *ds_drone = new DRONE_LUONG_CU[n];

    cout << "\nNHAP DU LIEU\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\n--- Drone thu " << i + 1 << " ---\n";
        ds_drone[i].nhap();
    }

    cout << "\nSAU KHI NHAP\n";
    THIET_BI_VAN_TAI::hien_thi_tong_thiet_bi();

    sort(ds_drone, ds_drone + n, [](const DRONE_LUONG_CU &a, const DRONE_LUONG_CU &b)
         { return b > a; });

    cout << "\nDANH SACH DRONE LUONG CU (SAP XEP TANG DAN THEO HIEU SUAT)\n";
    cout << left
         << setw(15) << "Ma Dinh Danh"
         << setw(20) << "Hang San Xuat"
         << setw(15) << "Trong Luong"
         << setw(15) << "Do Cao Bay"
         << setw(15) << "Toc Do"
         << setw(15) << "Do Sau Lan"
         << setw(15) << "Hai Ly"
         << setw(15) << "Hieu Suat" << endl;
    cout << string(140, '-') << endl;

    for (int i = 0; i < n; i++)
    {
        ds_drone[i].xuat();
    }

    delete[] ds_drone;

    cout << "\nSAU KHI GIAI PHONG BO NHO\n";
    THIET_BI_VAN_TAI::hien_thi_tong_thiet_bi();

    return 0;
}