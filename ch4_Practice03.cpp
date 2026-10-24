#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class VAN_DONG_VIEN
{
protected:
    string ma_vdv;
    string ho_ten;
    int nam_sinh;
    static int dem_vdv;

public:
    VAN_DONG_VIEN() : ma_vdv(""), ho_ten(""), nam_sinh(0) { dem_vdv++; }
    VAN_DONG_VIEN(string id, string name, int year) : ma_vdv(id), ho_ten(name), nam_sinh(year) { dem_vdv++; }

    virtual void nhap()
    {
        cin.ignore();
        cout << "\nNhap ma van dong vien: ";
        getline(cin, ma_vdv);
        cout << "Nhap ho va ten: ";
        getline(cin, ho_ten);
        cout << "Nhap nam sinh: ";
        cin >> nam_sinh;
    }

    virtual void in() const
    {
        cout << left
             << setw(12) << ma_vdv
             << setw(18) << ho_ten
             << setw(10) << nam_sinh;
    }

    virtual double tinh_diem_xep_hang() const = 0;
    static void in_tong_so_vdv()
    {
        cout << "\nTong so VDV hien co: " << dem_vdv << endl;
    }
    bool operator<(const VAN_DONG_VIEN &other) const
    {
        return this->tinh_diem_xep_hang() < other.tinh_diem_xep_hang();
    }
    virtual ~VAN_DONG_VIEN() { dem_vdv--; };
};
int VAN_DONG_VIEN::dem_vdv = 0;

class VDV_DIEN_KINH : virtual public VAN_DONG_VIEN
{
protected:
    double so_km_chay_tuan;
    double thanh_tich_chay_s;

public:
    VDV_DIEN_KINH() : VAN_DONG_VIEN(), so_km_chay_tuan(0.0), thanh_tich_chay_s(0.0) {}
    void nhap_chay()
    {
        cout << "Nhap so km chay tuan: ";
        cin >> so_km_chay_tuan;
        cout << "Nhap thanh tich chay (s): ";
        cin >> thanh_tich_chay_s;
    }
    void xuat_chay() const
    {
        cout << setw(12) << fixed << setprecision(1) << so_km_chay_tuan
             << setw(12) << thanh_tich_chay_s;
    }
    ~VDV_DIEN_KINH() {}
};

class VDV_BOI_LOI : virtual public VAN_DONG_VIEN
{
protected:
    double so_km_boi_tuan;
    double thanh_tich_boi_s;

public:
    VDV_BOI_LOI() : VAN_DONG_VIEN(), so_km_boi_tuan(0.0), thanh_tich_boi_s(0.0) {}
    void nhap_boi()
    {
        cout << "Nhap so km boi tuan: ";
        cin >> so_km_boi_tuan;
        cout << "Nhap thanh tich boi (s): ";
        cin >> thanh_tich_boi_s;
    }
    void xuat_boi() const
    {
        cout << setw(12) << fixed << setprecision(1) << so_km_boi_tuan
             << setw(12) << thanh_tich_boi_s;
    }
    ~VDV_BOI_LOI() {}
};

class VDV_TRIATHLON : public VDV_DIEN_KINH, public VDV_BOI_LOI
{
private:
    double so_km_dap_xe_tuan;

public:
    VDV_TRIATHLON() : VAN_DONG_VIEN(), VDV_DIEN_KINH(), VDV_BOI_LOI(), so_km_dap_xe_tuan(0.0) {};

    void nhap() override
    {
        VAN_DONG_VIEN::nhap();
        nhap_chay();
        nhap_boi();
        cout << "Nhap so km dap xe tuan: ";
        cin >> so_km_dap_xe_tuan;
    }

    void in() const override
    {
        VAN_DONG_VIEN::in();
        xuat_chay();
        xuat_boi();
        cout << setw(12) << fixed << setprecision(1) << so_km_dap_xe_tuan;
        cout << setw(12) << fixed << setprecision(2) << tinh_diem_xep_hang() << endl;
    }

    double tinh_diem_xep_hang() const override
    {
        return (so_km_chay_tuan * 1.2) + (so_km_boi_tuan * 3.0) + (so_km_dap_xe_tuan * 0.5);
    }
    ~VDV_TRIATHLON() {}
};

int main()
{
    VAN_DONG_VIEN::in_tong_so_vdv();

    int n;
    cout << "Nhap so luong VDV: ";
    cin >> n;

    VDV_TRIATHLON *danh_sach_vdv_triathlon = new VDV_TRIATHLON[n];

    cout << "\nSAU KHI CAP PHAT\n";
    VAN_DONG_VIEN::in_tong_so_vdv();

    for (int i = 0; i < n; i++)
    {
        cout << "\nNHAP VDV THU " << i + 1 << "\n";
        danh_sach_vdv_triathlon[i].nhap();
    }

    sort(danh_sach_vdv_triathlon, danh_sach_vdv_triathlon + n, [](const VDV_TRIATHLON &a, const VDV_TRIATHLON &b)
         { return b < a; });

    cout << "\nDANH SACH VDV TRIATHLON (SAP XEP GIAM DAN)\n";
    cout << left
         << setw(12) << "Ma VDV"
         << setw(18) << "Ho Ten"
         << setw(10) << "Nam Sinh"
         << setw(12) << "KM Chay"
         << setw(12) << "TT Chay(s)"
         << setw(12) << "KM Boi"
         << setw(12) << "TT Boi(s)"
         << setw(12) << "KM Dap Xe"
         << setw(12) << "Diem XH" << endl;
    cout << string(110, '-') << endl;

    for (int i = 0; i < n; i++)
    {
        danh_sach_vdv_triathlon[i].in();
    }

    delete[] danh_sach_vdv_triathlon;

    cout << "\nSAU KHI GIAI PHONG BO NHO\n";
    VAN_DONG_VIEN::in_tong_so_vdv();

    return 0;
}