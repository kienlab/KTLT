#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>
#include <iomanip>


using namespace std;

struct HV {
    char    HoLot[30];
    char    Ten[30];
    char    Ngaysinh[30];
    char    Noisinh[40];
	int 	D_WIN;
	int 	D_WORD;
	int 	D_EXCEL;
	int 	TONGDIEM;
	char	X_LOAI[20];
	HV() 
	{
		memset(this, 0, sizeof(HV));
	}
	void 	checkConstraint()
	{
		assert(D_WIN < 10 && D_WIN >= 0);
		assert(D_WORD < 10 && D_WORD >= 0);
		assert(D_EXCEL < 10 && D_EXCEL >= 0);		
	}
} __attribute__ ((packed));

vector<HV> dshv;

HV nhap()
{
	HV t;
	cout << "["<< dshv.size() <<"] Nhap Ho lot: ";
	// std::cin.ignore(1000,'\n') ;
	cin.getline(t.HoLot, 30);
	cout << "["<< dshv.size() <<"] Nhap Ten: ";
	// std::cin.ignore(1000,'\n') ;
	cin.getline(t.Ten, 30);
	cout << "["<< dshv.size() <<"] Nhap Ngay sinh: ";
	// std::cin.ignore(1000,'\n') ;
	cin.getline(t.Ngaysinh, 30);
	return t;
}

void ghi_danh() 
{
	int c;
	do {
		dshv.push_back(nhap());
		do {
			cout << "Tiep tuc nhap ? (Y/n): ";
			// while ((c = getchar()) != '\n' && c != EOF) { }
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			c = getchar();
		} while (
			c != 'y' &&
			c != 'Y' &&
			c != 'n' &&
			c != 'N'
		);
		stdin->_IO_read_ptr = stdin->_IO_read_end;
	} while (c!='n' && c!='N');

}

void nhap_diem()
{
	int c;
	do {
		for(int i=0; i<dshv.size(); i++) {
			cout << i+1 << ". " << dshv[i].HoLot << ' ' << dshv[i].Ten << endl;
		}
		cout << "Chon STT de nhap diem: ";
		int stt;
		
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		cin >> stt;
		assert(stt <= dshv.size());
		cout << "1. Nhap diem Windows" << endl;
		cout << "2. Nhap diem Word" << endl;
		cout << "3. Nhap diem Excel" << endl;
		cout << "Chon mon nhap (1-3): ";

		int diems;
		cin >> diems;
		assert(diems <= 3);

		cout << "Nhap diem (0-10): " ;
		int diem;
		cin >> diem;
		assert(diem <= 10);

		if(diems == 1) dshv[stt-1].D_WIN = diem;
		if(diems == 2) dshv[stt-1].D_WORD = diem;
		if(diems == 3) dshv[stt-1].D_EXCEL = diem;

	
		do {
			cout << "Tiep tuc nhap ? (Y/n): ";
			stdin->_IO_read_ptr = stdin->_IO_read_end;
			c = getchar();
		} while (
			c != 'y' &&
			c != 'Y' &&
			c != 'n' &&
			c != 'N'
		);
		stdin->_IO_read_ptr = stdin->_IO_read_end;
	} while (c!='n' && c!='N');
	
}

void inds() 
{
	cout << "DANH SACH HOC VIEN: " << endl;
	for(int i=0; i<dshv.size(); i++) {
		cout << i+1 << ". " << setw(20) << dshv[i].HoLot << ' '<< dshv[i].Ten 
		<< ' ' << setw(15) << dshv[i].Ngaysinh << " " << endl;
	}
}

void rank_process()
{
	for(int i=0; i<dshv.size(); i++) {
		dshv[i].TONGDIEM = dshv[i].D_WIN + dshv[i].D_WORD + dshv[i].D_EXCEL;
		if(dshv[i].TONGDIEM > 24) {
			strcpy(dshv[i].X_LOAI, "LOAI GIOI");
		}else if(dshv[i].TONGDIEM > 18) {
			strcpy(dshv[i].X_LOAI,"LOAI KHA");
		}else if(dshv[i].TONGDIEM > 15){ 
			strcpy(dshv[i].X_LOAI,"LOAI TB");
		}else strcpy(dshv[i].X_LOAI, "KEM");
	}
}

void ketqua() 
{
	cout << "KET QUA THI: " << endl;
	for(int i=0; i<dshv.size(); i++) {
		cout << i+1 << ". " << setw(25) << dshv[i].HoLot << ' '<< dshv[i].Ten 
		<< ' ' << setw(4) << dshv[i].D_EXCEL << ' ' << setw(4)<< dshv[i].D_WIN << ' ' << setw(4) << dshv[i].D_WORD << ' ' 
		 << setw(4)<< dshv[i].TONGDIEM << ' ' <<setw(10) << dshv[i].X_LOAI
		<< endl;
	}
}

void savedata() 
{
	FILE *f = fopen("data", "w+");
	for(int i=0; i<dshv.size(); i++)
		fwrite(&dshv[i], sizeof(HV), 1, f);
	fclose(f);
}
void readdata() 
{
	FILE *f = fopen("data", "r+");
	if (!f) { // if the file is not exist, create one.
		f = fopen("data", "w+"); 
		fclose(f);
		return;
	}
	while(1) {
		HV t;
		fread(&t, sizeof(HV), 1, f);
		if (feof(f)) break;
		dshv.push_back(t);
	}
	fclose(f);
}

int main(int argc, char const *argv[])
{
	HV *hv = new HV;
	hv->checkConstraint();
	readdata();

	if(argc == 2) {
		if(!strcmp(argv[1], "-ghidanh")) {
			ghi_danh();
			inds();
			savedata();
		} else if (!strcmp(argv[1], "-inds")) {
			inds();
			return 0;
		} else if (!strcmp(argv[1], "-kq")) {
			rank_process();
			ketqua();
			return 0;
		} else if (!strcmp(argv[1], "-nhapdiem")) {
			nhap_diem();
			rank_process();
			ketqua();
			savedata();
			return 0;
		}
	}
	// HV t;
	// strcpy(t.HoLot, "Nguyen Van");
	// strcpy(t.Ten, "A");
	// strcpy(t.Ngaysinh, "23/02/2002");
	// dshv.push_back(t);
	// strcpy(t.HoLot, "Vo Le");
	// strcpy(t.Ten, "B");
	// dshv.push_back(t);
	// strcpy(t.HoLot, "Vo Le Trong");
	// strcpy(t.Ten, "C");
	// dshv.push_back(t);
	// strcpy(t.HoLot, "Vu Van");
	// strcpy(t.Ten, "D");
	// dshv.push_back(t); 
	inds();
	ketqua();
	savedata();
    return 0;
}