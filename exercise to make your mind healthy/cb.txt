#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10
typedef struct {
    char LName[15];
    char FName[15];
    char Mi;
} Name;

typedef struct {
    Name name;
    int ID;
    int YrLvl;
    char Course[10];
} Studtype;

typedef struct {
	Studtype data;
	int next;
} stype, HeapSpace[MAX];

typedef struct {
	HeapSpace H;
	int avail;
} VHeap;

typedef int List;

void initHeap(VHeap *VH) {
    int i;
    for (i = 0; i < MAX - 1; i++) {
        VH->H[i].next = i + 1;
    }
    VH->H[i].next = -1;
    VH->avail = 0;
}

int allocSpace (VHeap *VH) {
    int retVal = VH->avail;
    if (VH->avail != -1) {
        VH->avail = VH->H[retVal].next;
    }
    return retVal;
}

void dealloc(VHeap *VH, int index) {
    if (index != -1 && index < MAX) {
        VH->H[index].next = VH->avail;
        VH->avail = index;
    }
}

bool cmp(Studtype a, Studtype b) {
    return strcmp(a.name.LName, b.name.LName) == 0 &&
        strcmp(a.name.FName, b.name.FName) == 0 &&
        (a.name.Mi == b.name.Mi);
}

void insertSorted (VHeap *VH, List *L, Studtype data) {
    List temp = allocSpace(VH);
    if (temp != -1) {
        VH->H[temp].data = data;
        VH->H[temp].next = -1;  
    } 

    int curr = *L, prev = -1;
    while (curr != -1 && cmp(VH->H[curr].data, data)) {
        prev = curr;
        curr = VH->H[curr].next;
    }

    if (prev == -1) {
        VH->H[temp].next = *L;
        *L = temp;
    } else {
        VH->H[temp].next = curr;
        VH->H[prev].next = temp;
    }
    printf("Added.\n");
}

void deleteValue(VHeap *VH, List *L, int ID) {
    if (VH->H[*L].data.ID == ID) { // first node
        List toDel = *L;
        *L = VH->H[*L].next;
        dealloc(VH, toDel);
        printf("Deleted.\n");
    } else {
        List curr = VH->H[*L].next;
        List prev = *L;
        
        while (curr != -1 && VH->H[curr].data.ID != ID) {
            prev = curr;
            curr = VH->H[curr].next;
        }
        
        if (curr == -1) {
            VH->H[prev].next = VH->H[curr].next;
            dealloc(VH, curr);
            printf("Deleted.\n");
        } else {
            printf("Not found.\n");
        }
    }
}

void displayList(VHeap VH, List L) {
    List curr = L;
    printf("\n%-10s%-15s%-15s%-5s%-10s%-10s\n", "ID", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
    while (curr != -1) {
        printf("%-10d%-15s%-15s%-5c%-10d%-10s\n", 
            VH.H[curr].data.ID,
            VH.H[curr].data.name.LName,
            VH.H[curr].data.name.FName,
            VH.H[curr].data.name.Mi,
            VH.H[curr].data.YrLvl,
            VH.H[curr].data.Course);
        curr = VH.H[curr].next;
    }
    printf("\n");
}

int main() {
    VHeap VH; 
    List L = -1;
    
    initHeap(&VH);

    Studtype data = {{"Gimenez", "Jules", 'L'}, 1001, 2, "BSIT"};
    Studtype data1 = {{"Doe", "John", 'T'}, 1002, 1, "BSCS"};
    Studtype data2 = {{"Garcia", "Geroge", 'Y'}, 1003, 3, "BSCS"};
    Studtype data3 = {{"Gonazles", "Tri", 'G'}, 1004, 4, "BSIS"};
    Studtype data4 = {{"Montaromas", "Yu", 'P'}, 1005, 2, "BSCS"};

    insertSorted(&VH, &L, data);
    insertSorted(&VH, &L, data1);
    insertSorted(&VH, &L, data2);
    insertSorted(&VH, &L, data3);
    insertSorted(&VH, &L, data4);

    displayList(VH, L);

    deleteValue(&VH, &L, 1005);
    
    displayList(VH, L);

    return 0;
}
