#include<iostream>
#include<string>
#include<string.h>
using namespace std;

typedef struct student {
	int num;
	char name[30];
	int depiao;
	student* next;
};

typedef struct {
	char name[30];
	int depiao;
}electee;

student* CreateLink(int n) {
	int i = 0;
	student* head = (student*)malloc(sizeof(student));
	student* p = head;
	for (i = 0; i < n; i++) {
		student* s = (student*)malloc(sizeof(student));
		cin >> s->num;
		cin >> s->name;
		s->depiao = 0;
		p->next = s;
		s->next = NULL;
		p = s;
	}
	return head;
}

void InitLink(student* p, int n) {
	int i = 0;
	student* p1 = p->next;
	for (i = 0; i < n; i++) {
		p1->depiao = 0;
		p1 = p1->next;
	}
}
void returnticket(student* p, int* a, int nt, int n) {
	int i = 0;
	student* p1 = p->next;
	for (i = 0; i < nt; i++) {
		for (int j = 0; j < n && p1 != NULL; j++) {
			if (a[i] == p1->num) {
				(p1->depiao)++;
				p1 = p->next;
				break;
			}
			p1 = p1->next;
		}
	}
}

electee findmax(student* p, int n) {
	electee es;
	int maxdepiao = -100000;
	p = p->next;
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (maxdepiao < p->depiao) {
			strcpy(es.name, p->name);
			es.depiao = p->depiao;
			maxdepiao = p->depiao;
			p = p->next;
		}
	}
	return es;
}
void sort(student* p, int n) {
	int i = 0;
	int j = 0;
	student* p1, * p2, * p3, * p4;
	for (i = 0; i < n - 1; i++) {
		for (p1 = p->next->next, p2 = p->next, p4 = p; p1 && p2; p1 = p1->next, p2 = p2->next, p4 = p4->next) {
			if (p2->depiao < p1->depiao) {
				p2->next = p1->next;
				p1->next = p2;
				p3 = p1;
				p1 = p2;
				p2 = p3;
				p4->next = p2;
			}
		}
	}

}

int causumdepiao(student* p, int n) {
	int i = 0;
	int sum = 0;
	student* p1 = p->next;
	for (i = 0; i < n; i++) {
		sum += p1->depiao;
		p1 = p1->next;
	}
	return sum;

}

int GetMaxNum(student* p, int n) {
	int i = 0;
	student* p1 = p->next;
	int depiaomax = p1->depiao;
	int inum = 0;
	for (i = 0; i < n; i++) {
		if (p1->depiao == depiaomax) {
			inum++;
		}
		else {
			break;
		}
		p1 = p1->next;
	}
	return inum;
}

void print(student* p, int n) {
	int i = 0;
	student* p1 = p->next;
	for (i = 0; i < n; i++) {
		cout << p1->name << " " << p1->depiao << endl;
		p1 = p1->next;
	}
}

electee es;
electee es1;
int ii = 1;
electee GetElectee(student* p, int n, int n2) {
	if (GetMaxNum(p, n) == 1) {
		strcpy(es.name, p->next->name);
		es.depiao = p->next->depiao;
		return es;
	}
	else {
		int n1 = GetMaxNum(p, n);
		int i;
		student* p1 = p;
		cout << "下列参选者平票，请再次投票选择" << endl;
		for (i = 0, p1 = p1->next; i < n1; i++) {
			cout << p1->num << " " << p1->name << endl;
			p1 = p1->next;
		}
		int a[30];
		ii++;
		if (ii == 4) {
			cout << "平票次数过多本次投票无效" << endl;
			return es1;
		}
		cout << "请输入第" << ii << "次投票人的投票结果（以序号输入）" << endl;
		for (i = 0; i < n2; i++) {
			cin >> a[i];
		}
		InitLink(p, n1);
		returnticket(p, a, n2, n1);
		int sumpiao1 = causumdepiao(p, n1);
		if (sumpiao1 >= n2 * 0.2) {
			sort(p, n1);
			cout << "对排序之后进行输出" << endl;
			print(p, n1);
			return GetElectee(p, n1, n2);
		}
		else {
			cout << " 弃票率大于80 % 本次投票无效";
		}

	}

}




int main() {
	cout << "请输入本次竞选的总人数" << endl;
	int n = 0;
	cin >> n;
	cout << "请输入本次参加投票的总人数" << endl;
	int nt = 0;
	cin >> nt;
	cout << "请输入分别输入本次竞选人的序号，姓名" << endl;
	int i = 0;
	student* p = CreateLink(n);
	cout << "请输入本次投票人的投票结果（以序号输入）" << endl;
	int a[100];
	for (i = 0; i < nt; i++) {
		cin >> a[i];
	}
	returnticket(p, a, nt, n);
	int sumpiao = causumdepiao(p, n);
	if (sumpiao >= n * 0.8) {
		cout << "对排序之前进行输出" << endl;
		print(p, n);
		sort(p, n);
		cout << "对排序之后进行输出" << endl;
		print(p, n);
		electee es = GetElectee(p, n, nt);
		if (ii != 4 && es.depiao!=0) {
			cout << "最终当选人为：" << es.name << "  得票数为：" << es.depiao << endl;
		}

	}
	else {
		cout << "弃票率大于80%本次投票无效";
	}



	return 0;
}