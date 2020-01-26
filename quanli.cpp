#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

// Lệnh để xóa màn hình trên Unix và Windows là khác nhau nên cần kiểm tra để gán cho phù hợp
#ifdef __unix__         
	char clear[] = "clear";
#elif defined(_WIN32) || defined(WIN32) 
	char clear[] = "cls";
#endif

struct nguoi {
	string ten;
	int sotien = 0;
	string danhmuc;
	int mung = 0;
};

/* 
	Chú thích:
	ten: tên của người lì xì
	sotien: số tiền lì xì
	danhmuc: danh mục, vd: nhà nội, nhà ngoại, bạn ba mẹ, ...
	mung: mùng (mồng) nhận được lì xì từ người đó
*/

bool LaChuoiRong(string s) {
	for (char i : s) {
		if (i != ' ')return false;
	}
	return true;
}

void chuanHoa(string& s) {
	// Xóa các kí tự khoảng trắng ở đầu và cuối
	const char space = 32;
	while (s[0] == space) {
		s.erase(0, 1);
	}
	while (s[s.size() - 1] == space) s.erase(s.size() - 1, 1);

	// Kí tự đầu tiên luôn viết hoa
	if (islower(s[0])) s[0] = toupper(s[0]);

	// Xét từng kí tự 
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == space) {
			// Không có 2 khoảng trắng liên tiếp trong chuỗi
			while (s[i + 1] == space) s.erase(i + 1, 1);
			// Kí tự đầu tiên của 1 từ luôn viết hoa
			if (islower(s[i + 1])) s[i + 1] = toupper(s[i + 1]);
			i += 1;
		}
		// Các kí tự còn lại viết thường
		else if (isupper(s[i])) s[i] = tolower(s[i]);
	}
}

nguoi nhapThongtin(string danhmuc, int mung, bool& exit) {
	exit = false;
	nguoi n;
	cout << "\nNhap ten: ";
	getline(cin, n.ten);
	chuanHoa(n.ten);

	if (n.ten == "//") {
		exit = true;
		cout << "Ket thuc" << endl;
		return n;
	}
	else if (LaChuoiRong(n.ten)) {
		exit = true;
		cout << "Ban vua co tinh troll chuong trinh bang cach nhap mot chuoi rong. Chuong trinh se thoat." << endl;
		return n;
	}

	cout << "Nhap so tien: ";
	cin >> n.sotien;
	cin.ignore();
	n.danhmuc = danhmuc;
	n.mung = mung;
	return n;
}

vector<nguoi> docFile(ifstream& fin) {
	vector<nguoi> list;
	while (!fin.eof()) {
		nguoi temp;
		getline(fin, temp.ten);

		// Để tránh đọc những dòng rỗng
		if (temp.ten == "") break;

		fin >> temp.sotien;
		fin.ignore();
		getline(fin, temp.danhmuc);
		fin >> temp.mung;
		fin.ignore();

		list.push_back(temp);
	}
	return list;
}

void xuatNguoiRaFile(nguoi n) {
	ofstream fout;
	fout.open("data.txt", ios::app);

	fout << n.ten << endl;
	fout << n.sotien << endl;
	fout << n.danhmuc << endl;
	fout << n.mung << endl;

	fout.close();
}

void print(string stt, string ten, string sotien, string danhmuc, string mung, char fill) {
	cout << setfill(fill) 
		<< setw(3) << stt
		<< setw(20) << ten
		<< setw(10) << sotien
		<< setw(10) << danhmuc
		<< setw(7) << mung << endl;
}


void xuatDS(vector<nguoi> list, int criteriaCol, string criteria) {
	// criteriaCol: đk lọc danh sách

	/*
	Điều kiện lọc danh sách
		1 = Lọc theo danh mục
		2 = Lọc theo một mùng cố định (vd: xem số tiền kiếm được trong mùng 1)
		3 = Lọc theo khoảng mùng (vd: xem số tiền từ mùng 2-3 hoặc 1-2, ...)
	*/

	int stt = 1;
	int sum = 0;
	cout << endl;
	print("STT", "Ten", "Stien", "Dmuc", "Mung", ' ');
	print("", "", "", "", "", '-');

	if (criteriaCol == 0) {
		for (nguoi i : list) {
			print(to_string(stt), i.ten, to_string(i.sotien), i.danhmuc, to_string(i.mung), ' ');
			sum += i.sotien;
			stt++;
		}
	}
	else if (criteriaCol == 1) {
		for (nguoi i : list) {
			if (i.danhmuc == criteria) {
				print(to_string(stt), i.ten, to_string(i.sotien), i.danhmuc, to_string(i.mung), ' ');
				sum += i.sotien;
				stt++;
			}
		}
	}
	else if (criteriaCol == 2) {
		for (nguoi i : list) {
			if (i.mung == stoi(criteria)) {
				print(to_string(stt), i.ten, to_string(i.sotien), i.danhmuc, to_string(i.mung), ' ');
				sum += i.sotien;
				stt++;
			}
		}
	}
	else if (criteriaCol == 3) {
		// Criteria trong trường hợp này là 2 số nên cần tách ra
		stringstream ss;
		ss << criteria;
		int from, to;
		ss >> from;
		ss >> to;

		for (nguoi i : list) {
			if (i.mung >= from && i.mung <= to) {
				print(to_string(stt), i.ten, to_string(i.sotien), i.danhmuc, to_string(i.mung), ' ');
				sum += i.sotien;
				stt++;
			}
		}
	}

	print("", "", "", "", "", '-');
	print("", "Tong:", to_string(sum), "", "", ' ');
	cout << endl;
}

bool chinhSua(vector<nguoi>& list, nguoi n, nguoi m) {
	for (nguoi i : list) {
		if (i.ten == n.ten && i.danhmuc == n.danhmuc && i.mung == n.mung && i.sotien == n.sotien) {
			i = m;
			return true;
		}
	}
	return false;
}

// Tiêu đề đầu chương trình
void title() {
	system(clear);
	cout << "Chuong trinh quan li tien li xi" << endl;
	cout << "By Ngoc Phat" << endl;
	cout << "Version 1.6" << endl;
	cout << "OS: ";
	#ifdef __unix__         
	cout << "Unix" << endl;
	#elif defined(_WIN32) || defined(WIN32) 
	cout << "Windows" << endl;
	#endif
	cout << "=======================================================" << endl;
}
int main() {
	title();
	int choice;
	vector<nguoi> list;
	ifstream fin;
	fin.open("data.txt");

	if (fin.fail()) {
		cout << "Loi doc file. Vui long kiem tra lai!" << endl;
		cout << "Tao tap tin moi? (0/1) => ";
		int create;
		cin >> create;
		cin.ignore();
		if (create) {
			fin.close();
			ofstream fout;
			fout.open("data.txt");
			fout << "";
			fout.close();
			fin.open("data.txt");
		}
		else {
			return -1;
		}
	}

	list = docFile(fin);
	fin.close();

	nguoi nguoiGanNhat;

	if (list.size() != 0){
		nguoiGanNhat = list.at(list.size() - 1);
	}

	int cont = 0;

	do {
		title();
		cout << "Hay chon 1 trong cac tinh nang sau:" << endl;
		cout << "1. In danh sach thong ke" << endl;
		cout << "2. Nhap thong tin moi" << endl;
		cout << "3. Chinh sua danh sach" << endl;
		cout << "0. Thoat khoi chuong trinh" << endl;
		cout << "=> ";

		cin >> choice;
		cin.ignore();
		if (choice == 0) break;

		title();

		if (choice == 1) {
			int criteriaCol = 0;
			cout << "Dieu kien loc danh sach: " << endl;
			cout << "0 = Khong loc" << endl;
			cout << "1 = Loc theo danh muc " << endl;
			cout << "2 = Loc theo mung co dinh" << endl;
			cout << "3 = Loc theo khoang mung" << endl;
			cout << "=> ";
			cin >> criteriaCol;

			if (criteriaCol == 0) {
				title();
				xuatDS(list, 0, "");
			}
			else if (criteriaCol == 1) {
				string dmuc;
				cout << "Nhap danh muc can loc: ";
				getline(cin, dmuc);
				chuanHoa(dmuc);

				title();
				xuatDS(list, 1, dmuc);
			}
			else if (criteriaCol == 2) {
				int mung;
				cout << "Nhap mung can loc: ";
				cin >> mung;
				cin.ignore();
				title();
				xuatDS(list, 2, to_string(mung));
			}
			else if (criteriaCol == 3) {
				int from, to;
				string criteria;
				cout << "Nhap mung bat dau va ket thuc: ";
				cin >> from >> to;
				cin.ignore();
				criteria += to_string(from) + " " + to_string(to);
				title();
				xuatDS(list, 3, criteria);
			}
			else {
				cout << "Lua chon khong hop le!" << endl;
			}
		}
		else if (choice == 2) {
			string dmuc;
			int mung;

			cout << "Nhap danh muc la // de lay du lieu danh muc va mung tu ban ghi gan nhat.\n\n";

			cout << "Nhap danh muc: ";
			getline(cin, dmuc);
			chuanHoa(dmuc);
			
			if (dmuc == "//"){
				if (list.size() != 0){
					dmuc = nguoiGanNhat.danhmuc;
					mung = nguoiGanNhat.mung;
				}
				else{
					cout << "Loi: Danh sach rong nen khong ton tai 'ban ghi gan nhat'" << endl;
					goto end;
				}
			}
			else{
				cout << "Nhap mung: ";
				cin >> mung;
				cin.ignore();
			}
			
			cout << "Nhap ten la // de ket thuc" << endl;

			while (true) {
				bool exit;
				list.push_back(nhapThongtin(dmuc, mung, exit));
				if (exit) {
					list.pop_back();
					break;
				}
				else{
					xuatNguoiRaFile(list.at(list.size() - 1));
				}
			}
		}

		else if (choice == 3) {
			nguoi n, m;
			cout << "Hay nhap cac thong tin cu: " << endl;
			cout << "Nhap ten cu: ";
			getline(cin, n.ten);
			chuanHoa(n.ten);

			cout << "Nhap so tien cu: ";
			cin >> n.sotien;
			cin.ignore();

			cout << "Nhap danh muc cu: ";
			getline(cin, n.danhmuc);
			chuanHoa(n.danhmuc);

			cout << "Nhap mung cu: ";
			cin >> n.mung;
			cin.ignore();

			cout << "=======================================================" << endl;
			cout << "Hay nhap cac thong tin moi: " << endl;
			cout << "Nhap ten moi: ";
			getline(cin, m.ten);
			chuanHoa(m.ten);

			cout << "Nhap so tien moi: ";
			cin >> m.sotien;
			cin.ignore();

			cout << "Nhap danh muc moi: ";
			getline(cin, m.danhmuc);
			chuanHoa(m.danhmuc);

			cout << "Nhap mung moi: ";
			cin >> m.mung;
			cin.ignore();

			if (chinhSua(list, n, m) == false) {
				cout << "Nguoi da nhap khong ton tai trong danh sach" << endl;
			}
			xuatNguoiRaFile(m);
		}
		else {
			cout << "Lua chon khong hop le!" << endl;
		}

		end:
		cout << "=======================================================" << endl;
		cout << "Tiep tuc? (0/1) => ";
		cin >> cont;
		cin.ignore();
	} while (cont != 0);
	return 0;
}