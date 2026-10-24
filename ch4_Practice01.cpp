#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

class NHAN_SU_Y_TE
{
protected:
    string ma_so;
    string ho_ten;
    double he_so_luong;
    static int so_luong_nhan_su;

public:
    NHAN_SU_Y_TE() : ma_so(""), ho_ten(""), he_so_luong(0.0)
    {
        so_luong_nhan_su++;
    }

    NHAN_SU_Y_TE(string ma, string ten, double hsl)
        : ma_so(ma), ho_ten(ten), he_so_luong(hsl)
    {
        so_luong_nhan_su++;
    }

    virtual ~NHAN_SU_Y_TE()
    {
        so_luong_nhan_su--;
    }

    virtual void nhap()
    {
        cout << "Nhap thong tin co ban:\n";
        cin.ignore();
        cout << "Ma so: ";
        getline(cin, ma_so);
        cout << "Ho ten: ";
        getline(cin, ho_ten);
        cout << "He so luong: ";
        cin >> he_so_luong;
    }

    virtual void xuat() const
    {
        cout << left
             << setw(15) << ma_so
             << setw(20) << ho_ten
             << setw(10) << fixed << setprecision(2) << he_so_luong;
    }

    virtual double tinh_diem_cong_hien() const = 0;

    bool operator<(const NHAN_SU_Y_TE &other) const
    {
        return this->tinh_diem_cong_hien() < other.tinh_diem_cong_hien();
    }

    static void in_so_luong()
    {
        cout << "So luong nhan su hien co trong bo nho: " << so_luong_nhan_su << endl;
    }
};
int NHAN_SU_Y_TE::so_luong_nhan_su = 0;

class BAC_SI_DIEU_TRI : public virtual NHAN_SU_Y_TE
{
protected:
    int so_ca_phau_thuat;
    double phu_cap_mo;

public:
    BAC_SI_DIEU_TRI() : NHAN_SU_Y_TE(), so_ca_phau_thuat(0), phu_cap_mo(0.0) {}

    BAC_SI_DIEU_TRI(string ma, string ten, double hsl, int so_ca, double pc)
        : NHAN_SU_Y_TE(ma, ten, hsl), so_ca_phau_thuat(so_ca), phu_cap_mo(pc) {}

    void nhap_dt()
    {
        cout << "So ca phau thuat: ";
        cin >> so_ca_phau_thuat;
        cout << "Phu cap mo: ";
        cin >> phu_cap_mo;
    }

    void xuat_dt() const
    {
        cout << setw(15) << so_ca_phau_thuat
             << setw(15) << fixed << setprecision(2) << phu_cap_mo;
    }
};

class NHA_NGHIEN_CUU_Y_HOC : public virtual NHAN_SU_Y_TE
{
protected:
    int so_bai_bao_isi;
    double kinh_phi_de_tai;

public:
    NHA_NGHIEN_CUU_Y_HOC() : NHAN_SU_Y_TE(), so_bai_bao_isi(0), kinh_phi_de_tai(0.0) {}

    NHA_NGHIEN_CUU_Y_HOC(string ma, string ten, double hsl, int bai_bao, double kp)
        : NHAN_SU_Y_TE(ma, ten, hsl), so_bai_bao_isi(bai_bao), kinh_phi_de_tai(kp) {}

    void nhap_nc()
    {
        cout << "So bai bao ISI: ";
        cin >> so_bai_bao_isi;
        cout << "Kinh phi de tai: ";
        cin >> kinh_phi_de_tai;
    }

    void xuat_nc() const
    {
        cout << setw(15) << so_bai_bao_isi
             << setw(15) << fixed << setprecision(2) << kinh_phi_de_tai;
    }
};

class BAC_SI_CHUYEN_GIA : public BAC_SI_DIEU_TRI, public NHA_NGHIEN_CUU_Y_HOC
{
public:
    BAC_SI_CHUYEN_GIA() : NHAN_SU_Y_TE(), BAC_SI_DIEU_TRI(), NHA_NGHIEN_CUU_Y_HOC() {}

    BAC_SI_CHUYEN_GIA(string ma, string ten, double hsl, int so_ca, double pc, int bai_bao, double kp)
        : NHAN_SU_Y_TE(ma, ten, hsl),
          BAC_SI_DIEU_TRI(ma, ten, hsl, so_ca, pc),
          NHA_NGHIEN_CUU_Y_HOC(ma, ten, hsl, bai_bao, kp) {}

    void nhap() override
    {
        NHAN_SU_Y_TE::nhap();
        cout << "--- Thong tin Bac si Dieu tri ---\n";
        nhap_dt();
        cout << "--- Thong tin Nha nghien cuu Y hoc ---\n";
        nhap_nc();
    }

    void xuat() const override
    {
        NHAN_SU_Y_TE::xuat();
        xuat_dt();
        xuat_nc();
        cout << setw(15) << fixed << setprecision(2) << tinh_diem_cong_hien() << endl;
    }
    double tinh_diem_cong_hien() const override
    {
        return (so_ca_phau_thuat * 2.0) + (so_bai_bao_isi * 15.0) + (he_so_luong * 5.0);
    }
};

int main()
{
    cout << "KHOI TAO HE THONG\n";
    NHAN_SU_Y_TE::in_so_luong();

    int n;
    cout << "\nNhap so luong bac si chuyen gia: ";
    cin >> n;

    NHAN_SU_Y_TE **ds_bac_si = new NHAN_SU_Y_TE *[n];
    for (int i = 0; i < n; i++)
    {
        ds_bac_si[i] = new BAC_SI_CHUYEN_GIA();
    }

    cout << "\nNHAP DU LIEU\n";
    for (int i = 0; i < n; i++)
    {
        cout << "\n--- Bac si thu " << i + 1 << " ---\n";
        ds_bac_si[i]->nhap();
    }

    cout << "\nSAU KHI NHAP\n";
    NHAN_SU_Y_TE::in_so_luong();

    sort(ds_bac_si, ds_bac_si + n, [](NHAN_SU_Y_TE *a, NHAN_SU_Y_TE *b)
         { return *b < *a; });

    cout << "\nDANH SACH BAC SI CHUYEN GIA (SAP XEP GIAM DAN THEO DIEM CONG HIEN)\n";
    cout << left
         << setw(15) << "Ma So"
         << setw(20) << "Ho Ten"
         << setw(10) << "HSL"
         << setw(15) << "So PT"
         << setw(15) << "Phu Cap"
         << setw(15) << "Bai ISI"
         << setw(15) << "Kinh Phi"
         << setw(15) << "Diem CH" << endl;
    cout << string(135, '-') << endl;

    for (int i = 0; i < n; i++)
    {
        ds_bac_si[i]->xuat();
    }

    for (int i = 0; i < n; i++)
    {
        delete ds_bac_si[i];
    }
    delete[] ds_bac_si;

    cout << "\nSAU KHI GIAI PHONG BO NHO\n";
    NHAN_SU_Y_TE::in_so_luong();

    return 0;
}