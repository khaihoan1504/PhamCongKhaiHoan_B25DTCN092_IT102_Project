#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#define MAX 100
#define MAX_BOOK 500

typedef struct {
	char roomId[5];
	int type;
	double price;
	int status;
} Room;

typedef struct {
    char bookId[10];
    char roomId[5];
    char cusName[50];
    int days;
    char checkInDate[11]; 
    double totalPrice;
} Booking;

void menu ();
void wait ();
void roomAdd (Room rooms[], int *n);
int checkRoomIdExist (Room rooms[], int n, char roomID[]);
void updateRoom(Room rooms[], int n);
void roomLock(Room rooms[], int n);
void roomShow(Room rooms[], int n);
int ctoi(char s[]);
int checkInput(char s[], char fieldName[]);
void searchEmptyRoom(Room rooms[], int n);
void sortRoomByPriceDesc(Room rooms[], int n);
void checkIn(Room rooms[], int n, Booking bookings[], int *m);
void showRoomHistory(Room rooms[], int n, Booking bookings[], int m);
int isLeapYear(int year);
int isValidDate(char date[]);
int isOnlySpaces(char *s);

int main () {
	
	int choice;
	char input[100];
	Room rooms[MAX] = {
    {"101", 1, 200.0, 0},
    {"102", 2, 350.0, 1},
    {"103", 1, 220.0, 0},
    {"104", 2, 400.0, 2},
    {"105", 1, 250.0, 0},
    {"106", 2, 380.0, 1},
    {"107", 1, 210.0, 0}
	};	
	Booking bookings[MAX_BOOK] = {
	{"B001", "102", "Dinh Duc Tu", 1, "01/12/2025", 350.0},
	{"B002", "106", "Vi Anh Dung", 1, "01/12/2025", 380.0},
	};
	int m = 2;
	int n = 7;
	
	while (1) {
		system("cls");
		menu();
		while (1) {
			printf("Moi ban nhap lua chon: ");
			fgets(input, sizeof(input), stdin);
			input[strcspn(input, "\n")] = '\0';
			if (!checkInput(input, "Lua chon")) {
				continue;
			}
			if (!isdigit(input[0])) {
				printf("\nChi duoc nhap so !\n\n");
				continue;
			}
	    	choice = atoi(input);
	    	break;
		}
		
		switch (choice) {
			case 1:{
				roomAdd(rooms, &n);
				wait();
				break;
			}
			case 2:{
				updateRoom(rooms, n);
				wait();
				break;
			} 
			case 3:{
				roomLock(rooms, n);
				wait();
				break;
			}
			case 4:{
				roomShow(rooms, n);
				wait();
				break;
			}
			case 5:{
				searchEmptyRoom(rooms, n);
				wait();
				break;
			} 
			case 6:{
				sortRoomByPriceDesc(rooms, n);
				wait();
				break;
			}
			case 7:{
				checkIn(rooms, n, bookings, &m);
				fflush(stdin);
				wait();
				break;
			}
			case 8:{
				showRoomHistory(rooms, n, bookings, m);
				wait();
				break;
			}
			case 0:{
				printf("\nDa thoat, Hen gap lai !\n");
				exit(0);
				break;
			}
			default:{
				printf("\nLua chon khong hop le, vui long chon lai !\n");
				wait();
				break;
			}
		}
	}
	
}

void wait () {
	printf("\nBam enter de tiep tuc ...\n");
	while (1) {
		char input = getch();
		if (input != 13) {
			printf("\nVui long nhap enter ...");
			continue;
		}
		break;
	}
}

void menu() {
    printf("+===========================================================+\n");
    printf("|                           MENU                            |\n");
    printf("+---------------------------+-------------------------------+\n");
    printf("| 1. Them phong moi         | 2. Cap nhat thong tin phong   |\n");
    printf("| 3. Bao tri phong          | 4. Hien thi danh sach         |\n");
    printf("| 5. Tim kiem               | 6. Sap xep ds phong (theo gia)|\n");
    printf("| 7. Thue phong             | 8. Lich su thue               |\n");
    printf("+---------------------------+-------------------------------+\n");
    printf("| 0. Thoat                                                  |\n");
    printf("+===========================================================+\n");
}

int checkInput(char s[], char fieldName[]) {
    s[strcspn(s, "\n")] = '\0';

    if (strlen(s) == 0) {
        printf("Loi: %s khong duoc de trong!\n", fieldName);
        return 0; 
    }

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' || s[i] == '\t') {
            printf("Loi: %s khong duoc chua khoang trang!\n", fieldName);
            return 0; 
        }
    }

    return 1; 
}


void roomAdd (Room rooms[], int *n) {
    char roomId[10];
    char inputType[100]; 
    char inputPrice[100];
    int type;
    double price;
	
    while (1) {
	    printf("\nNhap so phong (toi da 4 ky tu): ");
	    fflush(stdin);
	    fgets(roomId, sizeof(roomId), stdin);
	    roomId[strcspn(roomId, "\n")] = '\0';
	    if (!checkInput(roomId, "So phong")) {
	    	continue;
		}
		if (!isdigit(roomId[0])) {
				printf("\nChi duoc nhap so !\n");
				continue;
		}
		
		if (strlen(roomId) > 4) {
            printf("Loi: So phong khong duoc qua 4 ky tu!\n");
            continue;
        }
		
	    if (checkRoomIdExist(rooms, *n, roomId) != -1) {
	        printf("\nLoi: Phong %s da ton tai!\n", roomId);
	        continue;
	    }

    break; 
	}

    while (1) {
	    printf("Nhap loai phong (1: Don, 2: Doi): ");
	    fgets(inputType, sizeof(inputType), stdin);
	    inputType[strcspn(inputType, "\n")] = 0; 
	
	    if (!checkInput(inputType, "Loai phong")) {
	    	continue;
		}
	
	    type = atoi(inputType);
	
	    if (type != 1 && type != 2) {
	        printf("Loi: Loai phong chi duoc nhap 1 hoac 2!\n");
	        continue;
	    }
	
	    break;
	}

    while (1) {
        printf("Nhap gia phong moi dem (>0): ");
        fgets(inputPrice, sizeof(inputPrice), stdin);
	    inputPrice[strcspn(inputPrice, "\n")] = 0;
	
	    if (!checkInput(inputPrice, "Loai phong")) {
	    	continue;
		}
		
		if (!isdigit(inputPrice[0])) {
				printf("\nChi duoc nhap so !\n\n");
				continue;
		}
		
		price = atoi(inputPrice);

        if (price <= 0) {
            printf("Loi: Gia phong phai lon hon 0!\n");
            continue;
        }

        break;
    }

    strcpy(rooms[*n].roomId, roomId);
    rooms[*n].type = type;
    rooms[*n].price = price;
    rooms[*n].status = 0;

    (*n)++;

    printf("\nThem phong thanh cong! Phong %s da duoc tao voi trang thai Trong.\n", roomId);
}

int checkRoomIdExist (Room rooms[], int n, char roomId[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(rooms[i].roomId, roomId) == 0) {
			return i;
		}
	}
	return -1;
}

void updateRoom(Room rooms[], int n) {
    char roomId[10];
    int type;
    char inputType[100];
    char inputPrice[100];
    double price;
	int index; 
	 
    while (1) {
	    printf("\nNhap so phong can cap nhat: ");
	    fflush(stdin);
	    fgets(roomId, sizeof(roomId), stdin);
	    roomId[strcspn(roomId, "\n")] = 0;

        if (!checkInput(roomId, "So phong")) {
	    	continue;
		}
		
		if (!isdigit(roomId[0])) {
				printf("\nChi duoc nhap so !\n");
				continue;
		}
		
		if (strlen(roomId) > 4) {
            printf("Loi: So phong khong duoc qua 4 ky tu!\n");
            continue;
        }
        
        int k = 0;
		
		for (int i = 0; i < n; i++) {
			if (strcmp(roomId, rooms[i].roomId) == 0) {
				int k = i;
			}
		}
		
		if (rooms[k].status = 1) {
			printf("\nPhong da co nguoi o, khong duoc cap nhat !\n");
			return;
		}

	    index = checkRoomIdExist(rooms, n, roomId);
	
	    if (index == -1) {
	        printf("Loi: Khong tim thay phong %s!\n", roomId);
	        return;
	    }
	
	    printf("\nThong tin hien tai cua phong %s:\n", roomId);
	    printf("- Loai phong: %d\n", rooms[index].type);
	    printf("- Gia phong : %.2f\n\n", rooms[index].price);
	    
	    break;
	}
	
	while (1) {
	    printf("Nhap loai phong (1: Don, 2: Doi): ");
	    fgets(inputType, sizeof(inputType), stdin);
	    inputType[strcspn(inputType, "\n")] = 0; 
	
	    if (!checkInput(inputType, "Loai phong")) {
	    	continue;
		}
	
	    type = atoi(inputType);
	
	    if (type != 1 && type != 2) {
	        printf("Loi: Loai phong chi duoc nhap 1 hoac 2!\n");
	        continue;
	    }
	
	    break;
	}

    while (1) {
        printf("Nhap gia phong moi dem (>0): ");
        fgets(inputPrice, sizeof(inputPrice), stdin);
	    inputPrice[strcspn(inputPrice, "\n")] = 0; 
	
	    if (!checkInput(inputPrice, "Loai phong")) {
	    	continue;
		}
		
		if (!isdigit(inputPrice[0])) {
				printf("\nChi duoc nhap so !\n\n");
				continue;
		}
		
		price = atoi(inputPrice);

        if (price <= 0) {
            printf("Loi: Gia phong phai lon hon 0!\n");
            continue;
        }

        break;
        
    }

    rooms[index].type = type;
    rooms[index].price = price;

    printf("\nCap nhat thong tin phong %s thanh cong!\n", roomId);
    
}

void roomLock(Room rooms[], int n) {
    char roomId[10];
    
    while (1) {
    	
    	printf("\nNhap roomId muon bao tri (toi da 4 ky tu): ");
	    fgets(roomId, sizeof(roomId), stdin);
	    roomId[strcspn(roomId, "\n")] = 0;
		
		if(!checkInput(roomId, "So phong")) {
	    	continue;
		}
		
		if (!isdigit(roomId[0])) {
				printf("\nChi duoc nhap so !\n");
				continue;
		}
		
		if (strlen(roomId) > 4) {
            printf("Loi: So phong khong duoc qua 4 ky tu !\n");
            continue;
        }
		
		break;
		
	}
	
    int pos = checkRoomIdExist(rooms, n, roomId);
    if (pos == -1) {
        printf("\nLoi: Phong %s khong ton tai!\n", roomId);
        return;
    }

    if (rooms[pos].status == 1) {
        printf("\nLoi: Phong %s dang co khach o, khong the dua vao bao tri!\n", roomId);
        return;
    }

    rooms[pos].status = 2;
    printf("\nPhong %s da duoc dua vao trang thai BAO TRI.\n", roomId);
}

void roomShow(Room rooms[], int n) {
    if (n == 0) {
        printf("Danh sach phong rong!\n");
        return;
    }

    int pageSize = 10;
    int page = 0;
    int totalPages = (n + pageSize - 1) / pageSize; 
    int start, end;

    while (1) {
        system("cls");

        if (page < 0) {
        	page = 0;
		}
        if (page >= totalPages) {
        	page = totalPages - 1;
		}

        start = page * pageSize;
        end = start + pageSize;
        if (end > n) {
        	end = n;
		}

        printf("============= DANH SACH PHONG (Trang %d/%d) ==============\n", page + 1, totalPages);
        printf("|%-10s | %-10s | %-10s | %-15s|\n", "RoomID", "Type", "Price", "Status");
        printf("--------------------------------------------------------\n");

        for (int i = start; i < end; i++) {
            char *statusText;
            if (rooms[i].status == 0) {
            	statusText = "Trong";
			}
            else if (rooms[i].status == 1) {
            	statusText = "Dang o";
			}
            else {
            	statusText = "Bao tri";
			}

            printf("|%-10s | %-10d | %-10.2lf | %-15s|\n",
                   rooms[i].roomId,
                   rooms[i].type,
                   rooms[i].price,
                   statusText);
        }
        printf("========================================================");

        printf("\n(n: trang tiep theo, p: trang truoc, s: nhap so trang, ESC: thoat)\n");
        printf("\nNhap lua chon: ");

        char c = getch();
        if (c == 27) {
        	break; 
		}
        else if (c == 'n')  {
			page++;
		} 
        else if (c == 'p') {
			page--;
		}
        else if (c == 's') { 
            int inputPage = 0;
            int digits = 0;
            printf("\nNhap so trang (1-%d): ", totalPages);

            while (1) {
                char ch = getch();

                if (ch >= '0' && ch <= '9') {
                    inputPage = inputPage * 10 + (ch - '0');
                    digits++;
                    printf("%c", ch);
                } 
                else if (ch == '\b') { 
                    if (digits > 0) {
                        inputPage /= 10;
                        digits--;
                        printf("\b \b"); 
                    }
                }
                else if (ch == '\r') {
                    break;
                }
                else if (ch == 27) { 
                    inputPage = -1;
                    break;
                }
            }

            if (inputPage >= 1 && inputPage <= totalPages) {
                page = inputPage - 1;
            } else if (inputPage != -1) {
                printf("\nSo trang khong hop le! Nhan Enter de tiep tuc...");
                while(getch() != '\r');
            }
        }
    }
}

void searchEmptyRoom(Room rooms[], int n) {
    char input[10];
    int type;
    int found = 0;

    while (1) {
        printf("Nhap loai phong can tim (1: Don, 2: Doi): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (!checkInput(input, "Loai phong")) {
            continue;
        }

        type = atoi(input);

        if (type != 1 && type != 2) {
            printf("Loi: Chi duoc nhap 1 hoac 2!\n");
            continue;
        }

        break;
    }

    printf("\n============ DANH SACH PHONG TRONG (Loai %d) ============\n", type);
    printf("|%-10s | %-10s | %-10s | %-15s|\n", "RoomID", "Type", "Price", "Status");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (rooms[i].type == type && rooms[i].status == 0) {
            printf("|%-10s | %-10d | %-10.2lf | %-15s|\n",
                    rooms[i].roomId,
                    rooms[i].type,
                    rooms[i].price,
                    "Trong");
            found = 1;
        }
    }
    

    if (!found) {
    	printf("\nKhong co phong trong phu hop!\n");
	} else {
		for (int i = 0; i < 56; i++) {
			printf("=");
		}
	}
        
}

void sortRoomByPriceDesc(Room rooms[], int n) {
    Room temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rooms[i].price < rooms[j].price) {
                temp = rooms[i];
                rooms[i] = rooms[j];
                rooms[j] = temp;
            }
        }
    }

    printf("\nDa sap xep danh sach phong theo gia giam dan!\n");
}

void checkIn(Room rooms[], int n, Booking bookings[], int *m) {
    char roomId[10];
    char cusName[50];
    char daysStr[10];
    char checkInDate[11];
    int index;

    while (1) {
        printf("Nhap so phong muon nhan: ");
        fgets(roomId, sizeof(roomId), stdin);
        roomId[strcspn(roomId, "\n")] = 0;
        index = checkRoomIdExist(rooms, n, roomId);
        if (!checkInput(roomId, "So phong")) {
        	continue;
		}
		if (!isdigit(roomId[0])) {
				printf("\nChi duoc nhap so !\n\n");
				continue;
		}
        if (index == -1) {
            printf("Loi: Khong tim thay phong %s!\n", roomId);
            return;
        }
        if (rooms[index].status == 1) {
            printf("Loi: Phong %s da co khach!\n", roomId);
            return;
        }
        if (rooms[index].status == 2) {
            printf("Loi: Phong %s dang bao tri!\n", roomId);
            return;
        }
        break;
    }

    while (1) {
        printf("Nhap ten khach hang: ");
        fgets(cusName, sizeof(cusName), stdin);
        cusName[strcspn(cusName, "\n")] = 0;
        if (strlen(cusName) == 0) {
	        printf("Loi: Ten khach hang khong duoc de trong!\n");
	        continue;
		}
		if (isOnlySpaces(cusName)) {
        printf("Loi: Ten khach hang khong duoc chua khoang trang!\n");
        continue;
    	}
		break;
	}

    int days;
    while (1) {
        printf("Nhap so ngay o (>0): ");
        fgets(daysStr, sizeof(daysStr), stdin);
        daysStr[strcspn(daysStr, "\n")] = 0;
        if (!checkInput(daysStr, "So ngay o")) {
        	continue;
		}
		if (!isdigit(roomId[0])) {
				printf("\nChi duoc nhap so !\n\n");
				continue;
		}
        days = atoi(daysStr);
        if (days <= 0) {
            printf("Loi: So ngay o phai lon hon 0!\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Nhap ngay nhan phong (DD/MM/YYYY): ");
        fgets(checkInDate, sizeof(checkInDate), stdin);
        checkInDate[strcspn(checkInDate, "\n")] = 0;
        fflush(stdin);
        if (!checkInput(checkInDate, "Ngay nhan phong")) {
        	continue;
		}
        if (!isValidDate(checkInDate)) {
        printf("Loi: Ngay thang khong hop le!\n");
        continue;
    	}
        break;
    }

    Booking b;
    sprintf(b.bookId, "B%03d", *m + 1);
    strcpy(b.roomId, roomId);
    strcpy(b.cusName, cusName);
    b.days = days;
    strcpy(b.checkInDate, checkInDate);
    b.totalPrice = rooms[index].price * days;

    bookings[*m] = b;
    (*m)++;

    rooms[index].status = 1;

    printf("\nCheck-in thanh cong! Ma dat phong: %s\n", b.bookId);
    printf("\n====== Hoa don chi tiet ======\n");
    printf("Phong       : %s\n", b.roomId);
    printf("Khach hang  : %s\n", b.cusName);
    printf("Ngay nhan   : %s\n", b.checkInDate);
    printf("So ngay o   : %d\n", b.days);
    printf("Gia/Ngay    : %.2lf\n", rooms[index].price);
    printf("Tong tien   : %.2lf\n", b.totalPrice);
    printf("==============================\n");
}

void showRoomHistory(Room rooms[], int n, Booking bookings[], int m) {
    while (1) {
	    char roomId[10];
	    int found = 0;
	    printf("Nhap so phong can xem lich su: ");
	    fgets(roomId, sizeof(roomId), stdin);
	    roomId[strcspn(roomId, "\n")] = 0;
	    
	    if (!checkInput(roomId, "So phong")) {
	    	continue;
		}
		if (!isdigit(roomId[0])) {
				printf("\nChi duoc nhap so !\n\n");
				continue;
		}
		
	    int index = checkRoomIdExist(rooms, n, roomId);
	    if (index == -1) {
	        printf("Loi: Khong tim thay phong %s!\n", roomId);
	        return;
	    }
	
	    printf("\n======================== LICH SU THUE PHONG %s ========================================\n", roomId);
	    printf("|%-5s | %-15s | %-15s | %-12s | %-10s | %-14s|\n", "STT", "Ma dat phong", "Khach", "Ngay nhan", "So ngay", "Tong tien");
	    printf("----------------------------------------------------------------------------------------\n");
	
	    int stt = 0;
	    for (int i = 0; i < m; i++) {
	        if (strcmp(bookings[i].roomId, roomId) == 0) {
	            stt++;
	            found = 1;
	            printf("|%-5d | %-15s | %-15s | %-12s | %-10d | %-14lf|\n",
	                   stt, bookings[i].bookId, bookings[i].cusName,
	                   bookings[i].checkInDate, bookings[i].days, bookings[i].totalPrice);
	        }
	    }
	    for (int i = 0; i < 89; i++) {
	    	printf("=");
		}
		printf("\n");
	    if (!found) {
	        printf("Phong %s chua tung co khach thue!\n", roomId);
	    }
	    break;
	}
}

int isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int isValidDate(char date[]) {
    int d, m, y;

    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/') {
        return 0;
    }

    if (sscanf(date, "%d/%d/%d", &d, &m, &y) != 3) {
        return 0;
    }

    if (y < 1900 || y > 2100) {
    	return 0;
	}

    if (m < 1 || m > 12) {
    	return 0;
	}

    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if (m == 2 && isLeapYear(y)) {
        daysInMonth[2] = 29;
    }

    if (d < 1 || d > daysInMonth[m]) return 0;

    return 1;
}

int isOnlySpaces(char *s) {
    while (*s) {
        if (*s != ' ') return 0; 
        s++;
    }
    return 1; 
}



