#include <iostream>
#include <string>
using namespace std;

//1. khai báo cấu trúc dữ liệu dạng DSLK đơn để lưu danh sách sinh viên nói trên.
struct SinhVien {
	string MSSV;
	string Ten;
	double DTB;
};

typedef struct tagNode {
	SinhVien info;
	struct tagNode* pNext;
}Node;

Node* CreateNode(SinhVien x) {
	Node* p;
	p = new Node;
	if (p == NULL) exit(1);
	p->info = x;
	p->pNext = NULL;
	return p;
}

typedef struct tagList {
	Node* pHead;
	Node* pTail;
}LIST;

void CreateList(LIST& l) {
	l.pHead = NULL;
	l.pTail = NULL;
}

//2. Nhập danh sách các sinh viên, và thêm từng sinh viên vào đầu danh sách (việc nhập kết thúc khi tên của một sinh viên bằng khoảng trắng)
void Nhap(SinhVien &x) {
	cout << "Nhap ten sinh vien: "; getline(cin, x.Ten);
	cout << "Nhap ma so sinh vien: "; cin >> x.MSSV;
	cout << "Nhap diem trung binh: "; cin >> x.DTB;
	cin.ignore();
}

void AddHead(LIST& l, Node* p) {
	if (l.pHead == NULL) {
		l.pHead = p;
		l.pTail = p;
	}
	else {
		p->pNext = l.pHead;
		l.pHead = p;
	}
}

void AddList(LIST& l) {
	CreateList(l);
	while (true) {
		SinhVien x;
		Nhap(x);
		if (x.Ten == "") break;
		AddHead(l, CreateNode(x));
	}
}

//3. Tìm một sinh viên có trong lớp học hay không ?
Node* SearchByMSSV(LIST& l, string MSSV) {
	Node* search = l.pHead;
	while ((search!=NULL) && (search->info.MSSV != MSSV)) {
		search = search->pNext;
	}
	return search;
}

void CheckSinhVien(LIST& l) {
	string MSSV;
	cout << "Nhap vao MSSV can tim: "; cin >> MSSV;
	Node* check = SearchByMSSV(l, MSSV);
	if (check) cout << "Co hoc sinh mang MSSV " << MSSV << " trong lop.\n";
	else cout << "Khong co hoc sinh mang MSSV " << MSSV << " trong lop.\n";
}

//4. Xoá một sinh viên có MSSV bằng x (x nhập từ bàn phím).
int RemoveHead(LIST& l, SinhVien& x) {
	Node* p;
	if (l.pHead != NULL) {
		p = l.pHead;
		l.pHead = p->pNext;
		p->info = x;
		delete p;
		if (l.pHead == NULL)
			l.pTail = NULL;
		return 1;
	}
	return 0;
}
int RemoveAfter(LIST& l, Node* q, SinhVien& x) {
	Node* p;
	if (q != NULL) {
		p = q->pNext;
		if (p != NULL) {
			if (p == l.pTail)
				q = l.pTail;
			q->pNext = p->pNext;
			p->info = x;
			delete p;
		}
		return 1;
	}
	return 0;
}
int RemoveX(LIST& l, string MSSV) {
	Node* p, * q = NULL;
	SinhVien x;
	p = l.pHead;
	while ((p) and p->info.MSSV != MSSV) {
		q = p;
		p = p->pNext;
	}
	if (p == NULL)
		return 0;
	if (q != NULL)
	{
		RemoveAfter(l, q, x);
		return 1;
	}
	else 
	{
		RemoveHead(l, x);
		return 1;
	}
}
void RemoveSinhVien(LIST& l) {
	string MSSV;
	cout << "Nhap ma so sinh vien can xoa: "; cin >> MSSV;
	int check = RemoveX(l, MSSV);
	if (check)
		cout << "Xoa thanh cong sinh vien co ma so: "<<MSSV<<"\n";
	else cout << "Khong tim thay sinh vien co ma so: "<<MSSV<<" de xoa.\n";
}

//5. Liệt kê thông tin của các sinh viên có điểm trung bình lớn hơn hay bằng 5.
void DisplayListHigherThan5(LIST &list) {
	Node* p = list.pHead;
	while (p) {
		if (p->info.DTB >= 5)
		{
			cout << "Thong tin cac sinh vien co DTB >= 5 la: ";
			cout << "MSSV: " << p->info.MSSV << ", Ten: " << p->info.Ten << ", DTB: " << p->info.DTB << endl;
		}
		p = p->pNext;
	}
}

//6. Xếp loại và in ra thông tin của từng sinh viên.
string Level(Node*p) {
	if (p->info.DTB < 3.6)
		return "Kem";
	else if (p->info.DTB >= 3.6 and p->info.DTB < 5)
		return "Yeu";
	else if (p->info.DTB >= 5 and p->info.DTB < 6.5)
		return "Trung binh";
	else if (p->info.DTB >= 6.5 and p->info.DTB < 7)
		return "Trung binh kha";
	else if (p->info.DTB >= 7 and p->info.DTB < 8)
		return "Kha";
	else if (p->info.DTB >= 8 and p->info.DTB < 9)
		return "Gioi";
	else if (p->info.DTB >= 9)
		return "Xuat sac";
}

void DisplayOnLevel(LIST &list) {
	Node* p = list.pHead;
	while (p) {
		string level = Level(p);
		cout << "MSSV: " << p->info.MSSV << ", Ten: " << p->info.Ten << ", DTB: " << p->info.DTB <<", Xep loai:"<<level<< endl;
		p = p->pNext;
	}
}

//7. Sắp xếp và in ra danh sách sinh viên tăng theo điểm trung bình.
void BubleSort(LIST& l) {
	Node* p;
	bool check = false;
	do {
		p = l.pHead;
		check = false;
		while (p->pNext != NULL) {
			if (p->info.DTB > p->pNext->info.DTB) {
				swap(p->info,p->pNext->info);
				check = true;
			}
			p = p->pNext;
		}
	} while (check);
}
void DisplayList(LIST &list) {
	Node* p = list.pHead;
	while (p) {
		cout << "MSSV: " << p->info.MSSV << ", Ten: " << p->info.Ten << ", DTB: " << p->info.DTB << endl;
		p = p->pNext;
	}
}

//8. Chèn một sinh viên vào danh sách sinh viên tăng theo điểm trung bình nói trên, sao cho sau khi chèn danh sách sinh viên vẫn tăng theo điểm trung bình
void AddSinhVienIntoList(LIST& l) {
	SinhVien x;
	cout << "Nhap vao thong tin sinh vien can chen:\n";
	cin.ignore();
	Nhap(x);
	Node* p = CreateNode(x);

	if (l.pHead == NULL) {
		l.pHead = p;
		l.pTail = p;
	}
	else if (p->info.DTB < l.pHead->info.DTB) {
		AddHead(l, p);
	}
	else {
		Node* q = l.pHead;
		while (q->pNext != NULL && q->pNext->info.DTB < p->info.DTB) {
			q = q->pNext;
		}
		if (q->pNext == NULL) {
			q->pNext = p;
			l.pTail = p;
		}
		else {
			p->pNext = q->pNext;
			q->pNext = p;
		}
	}
}


int main() {
	LIST l;
	AddList(l);
	CheckSinhVien(l);
	RemoveSinhVien(l);
	DisplayListHigherThan5(l);
	DisplayOnLevel(l);
	BubleSort(l);
	DisplayList(l);
	AddSinhVienIntoList(l);
	DisplayList(l);
	return 0;
}
