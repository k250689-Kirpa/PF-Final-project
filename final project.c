//stms
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define RED     FOREGROUND_RED
#define GREEN   FOREGROUND_GREEN
#define BLUE    FOREGROUND_BLUE
#define YELLOW  (FOREGROUND_RED | FOREGROUND_GREEN)
#define CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
#define WHITE   (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

// Function to print colored text
void printColor(const char* text, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);  // Set color
    printf("%s", text);                        // Print text
    SetConsoleTextAttribute(hConsole, WHITE);  // Reset to default
}
void rules();
void pattern(int arr[3][3]);
int readEnteredKey();
void move(int arr[3][3], int k, int *moves);
void showMatrix(int arr[3][3]);
int win(int arr[3][3]);

typedef struct {
    char ID[11];
    char Name[50];
    char Email[31];
    char Phone[21];
    int  NumberOfCourse;
} Students;

typedef struct{
    char StudentID[11];
    char Code[10];
    char Name[20];
}Courses;



const char* ACCOUNT_FILE = "data_new.dat";
const char* COURSE_FILE = "courses_new.dat";




void Menu();
void ExitProject();
void AddNewStudent();
void ClearInputBuffer(); 
void ShowAllStudents();
int SearchStudent(char StudentID[10]);
void DeleteStudent(char StudentID[11]);
void DeleteAllStudents();
int login();
void inputPassword(char *pass);
void EditStudent(char *StudentID);
void PlaySlidingPuzzle();








int i,j;
int TotalStudents = 0;
int TotalCourses = 0;
char StudentID[11];
char USERNAME[] = "student";
char PASSWORD[] = "Fast1234";


int main (void)
{
	system("cls");

    if(login() == 0) 
    {
       
        return 0;  
    }
	
	int choice;
	while(1)
	{
		Menu();
		scanf("%d", &choice);
		
		switch(choice)
		{
			case 0:
				ExitProject();
				return 0;
			case 1:
				system("cls");
				printf("\n\t\t **** Add A New Student ****\n\n");
				AddNewStudent();
				break;
			case 2:
				system("cls");
            	printf("\n\t\t **** All Students ****\n\n");
				ShowAllStudents();
				break;	
			case 3:
                system("cls");
	            printf("\n\t\t **** Search Students ****\n\n");
	            printf(" Enter The Student ID: ");
	            scanf("%s",StudentID);
	            int x = SearchStudent(StudentID);
	            break;
        	case 4:
	            system("cls");
	            printf("\n\t\t **** Edit a Student ****\n\n");
	            printf(" Enter The Student ID: ");
	            scanf("%s",StudentID);
	            int StudentFoundIndex = SearchStudent(StudentID);
	
	            if(StudentFoundIndex>=0)
	            {
	                EditStudent(StudentID);
	            }
	            else
	            {
	                printf(" No Student Found\n\n");
	            }
	            break;	            
			case 5:
				system("cls");
	            printf("\n\t\t **** Delete a Student ****\n\n");
	            printf(" Enter The Student ID: ");
	            scanf("%s",StudentID);
	
	            int DeleteStudentFoundIndex = SearchStudent(StudentID);
	
	            if(DeleteStudentFoundIndex>=0)
	            {
	                char Sure = 'N';
	                getchar();
	                printf("\n\n");
	                printf(" Are you sure want to delete this student? (Y/N): ");
	                scanf(" %c",&Sure);
	
	                if(Sure == 'Y' || Sure == 'y')
	                {
	                    DeleteStudent(StudentID);
	                }
	                else
	                {
	                    printf(" Your Data is Safe.\n\n");
	                }
	
	            }
	            else
	            {
	                printf(" No Student Found\n\n");
	            }
	
	            break;
			case 6:
				system("cls");
				char Sure = 'N';

	            printf("\n\t\t **** Delete ALL Students ****\n\n");
	
	            printf(" Are you sure want to delete all the students? (Y/N): ");
	            scanf(" %c",&Sure);
	            if(Sure == 'Y' || Sure == 'y')
	            {
	                DeleteAllStudents();
	            }
	            else
	            {
	                printf(" Your Data is Safe.\n\n");
	            }
	            break;	            
        	case 7:
	            system("cls");
	            break;
			case 8:
				 PlaySlidingPuzzle();  
				break;	
		}
	}
}

void ClearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Menu()
{
    printf("\n\n\t***Student Management System Using C***\n\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Add A New student.\n");
    printf("\t\t[2] Show All students.\n");
    printf("\t\t[3] Search A student.\n");
    printf("\t\t[4] Edit A student.\n");
    printf("\t\t[5] Delete A student.\n");
    printf("\t\t[6] Delete All students.\n");
    printf("\t\t[7] Clear The window.\n");
    printf("\t\t[8] Play 3x3 Puzzle Game\n");
    printf("\t\t[0] Exit the Program.\n");
    printf("\t\t=======================\n");
    printf("\t\tEnter The Choice: ");
}
void ExitProject()
{
	int i;
	system("cls");
	char t[] = "======THANK YOU======\n";
	char s[] = "======SEE YOU SOON======\n";
	
	for (i=0; i<strlen(t); i++)
	{
		printf("%c", t[i]);
		Sleep(40);
	 } 
	 for (i=0; i<strlen(s); i++)
	{
		printf("%c", s[i]);
		Sleep(40);
	 }
	 exit(0); 
}
void AddNewStudent()
{
    char Name[50];
    char ID[11];
    char Email[31];
    char Phone[21];
    int NumberOfCourses;
    char CourseCode[10];
    char CourseName[20];
    
    int exists;
    
    FILE *read_file = fopen(ACCOUNT_FILE, "rb");
    if (read_file == NULL) {
        printf("\nNOTE: Student data file not found or could not be opened for reading. Continuing...\n");
    }
    
    Students st;
    Courses cr;
    
    int IsValidID = 0;
    while(!IsValidID){
        if (read_file != NULL) rewind(read_file); 
        
        printf("Enter ID: ");
        scanf("%10s", ID);
        ClearInputBuffer();
        
        if (strlen(ID)<=0)
        {
            printf(" Error: ID cannot be empty.\n\n");
            continue;
        }
        
        exists= 0;
        if (read_file != NULL) {
            while(fread(&st, sizeof(st), 1, read_file))
            {
                if (strcmp(st.ID, ID) == 0)
                {
                    exists = 1;
                    break;
                }
            }
        }
        
        if (exists)
        {
            printf(" Error: This ID already exists.\n\n");
            continue;
        }
        IsValidID = 1;
    }
    
    int IsValidName = 0;
    while (!IsValidName)
    {
        printf("Enter student name: ");
        scanf(" %49[^\n]", Name);
        ClearInputBuffer();
        
        if (strlen(Name)<=0)
        {
            printf(" Error: Name cannot be empty.\n\n");
            continue;
        }
         else
        {
            IsValidName = 1;
        }
    }
    
    int IsValidEmail = 0;
    while(!IsValidEmail){
        
        if (read_file != NULL) rewind(read_file);
        
        printf("Enter Email: ");
        scanf("%30s", Email);
        ClearInputBuffer();
        
        if (strlen(Email)<=0)
        {
            printf(" Error: Email cannot be empty.\n\n");
            continue;
        }
        
        exists= 0;
        if (read_file != NULL) {
            while(fread(&st, sizeof(st), 1, read_file))
            {
                if (strcmp(st.Email, Email) == 0)
                {
                    exists = 1;
                    break;
                }
            }
        }
        
        if (exists)
        {
            printf(" Error: This Email already exists.\n\n");
            continue;
        }
        IsValidEmail = 1;
    }
    
    int IsValidPhone = 0;
    while(!IsValidPhone){
        
        if (read_file != NULL) rewind(read_file);
        
        printf("Enter Phone: ");
        scanf("%20s", Phone);
        ClearInputBuffer();
        
        if (strlen(Phone)<=0)
        {
            printf(" Error: Phone number cannot be empty.\n\n");
            continue;
        }
        
        exists= 0;
        if (read_file != NULL) {
            while(fread(&st, sizeof(st), 1, read_file))
            {
                if (strcmp(st.Phone, Phone) == 0)
                {
                    exists = 1;
                    break;
                }
            }
        }
        
        if (exists)
        {
            printf(" Error: This Phone number already exists.\n\n");
            continue;
        }
        IsValidPhone = 1;
    }
    
    if (read_file != NULL) {
        fclose(read_file);
    }
    
    int IsValidNumberOfCourse = 0;
    while(!IsValidNumberOfCourse)
    {
        printf(" Enter number of courses (1-4): ");
        if (scanf("%d",&NumberOfCourses) != 1) { 
            printf(" Error: Invalid input. Please enter a number.\n\n");
            ClearInputBuffer();
            continue;
        }
        
        if(NumberOfCourses <= 0 || NumberOfCourses > 4)
        {
            printf(" Error: Number of courses can not be more than 4 and less than 1.\n\n");
            IsValidNumberOfCourse = 0;
        }
        else
        {
            IsValidNumberOfCourse = 1;
        }
    }
    ClearInputBuffer();
    
    strcpy(st.ID, ID);
    strcpy(st.Name, Name);
    strcpy(st.Email, Email);
    strcpy(st.Phone, Phone);
    st.NumberOfCourse = NumberOfCourses;
    TotalStudents++;
    
    FILE *write_file = fopen(ACCOUNT_FILE, "ab"); // Open in append binary mode
    if (write_file == NULL) {
        printf("\nUnable to open file for writing data!!");
        return;
    }
    fwrite(&st, sizeof(st), 1, write_file);
    fclose(write_file); 
    
    FILE *cfile = fopen(COURSE_FILE, "ab");
    if(cfile == NULL){
        printf("\nUnable to open courses file!\n");
        return;
    }

    for(i = 0; i < NumberOfCourses; i++)
    {
        printf(" Enter Course %d Code (max 9 chars): ", i+1);
        scanf("%9s", CourseCode);
        ClearInputBuffer();

        printf(" Enter Course %d Name (max 19 chars): ", i+1);
        scanf(" %19[^\n]", CourseName);
        ClearInputBuffer();

        strcpy(cr.StudentID, ID);
        strcpy(cr.Code, CourseCode);
        strcpy(cr.Name, CourseName);
        TotalCourses++;

        fwrite(&cr, sizeof(cr), 1, cfile);
    }

    fclose(cfile);
    
    printf("\nAccount created successfully!");
    printf("\nPress ENTER to return to the menu...");
    getchar(); 
}

void ShowAllStudents()
{
	FILE *read_file = fopen(ACCOUNT_FILE, "rb");
	if (read_file == NULL)
	{
		printf("\n\n No student records found. File %s does not exist or is empty.\n", ACCOUNT_FILE);
    	printf("\nPress ENTER to return to the menu...");
    	getchar(); 
    	return;
	}
	Students st;
	int record_count = 0; 
	
    printf("|==========|====================|==============================|====================|=============|\n");
    
    printf("|  %-6s  |  %-16s  |  %-26s  |  %-16s  |  %-9s  |\n", "ID", "Name", "Email", "Phone", "NO.Course");
    
    printf("|==========|====================|==============================|====================|=============|\n");
	
    while (fread(&st, sizeof(st), 1, read_file) == 1) 
    {
        // Print Data Line: Use precise format specifiers to match column widths
        printf("|%-10s|%-20s|%-30s|%-20s|%-13d|\n", 
               st.ID, 
               st.Name, 
               st.Email, 
               st.Phone, 
               st.NumberOfCourse);
        
        // Print Separator Line after each record, as requested
        printf("|----------|--------------------|------------------------------|--------------------|-------------|\n");
    	record_count++;
	}

	// Close the file as soon as reading is done
    fclose(read_file); 

	if (record_count == 0)
	{
		printf("\n\nThe file was empty. No records to display.\n");
    } else {
    	printf("\nTotal Students: %d\n", record_count);
    }
    
    printf("\nPress ENTER to return to the menu...");
    getchar();
    
    
}
int SearchStudent(char StudentID[10])
{
	system("cls");
	Students st;
	Courses cr;
	int student_found = 0;
    int course_count = 0;
	
	FILE *student_file = fopen(ACCOUNT_FILE, "rb");
    if (student_file == NULL) {
        printf("\n Student data file not found or empty.\n");
        return 0;
    } 
	
	while (fread(&st, sizeof(st), 1, student_file) == 1)
	{
		if (strcmp(StudentID, st.ID) == 0)
		{
			student_found = 1;

            printf("\n One Student Found for ID: %s\n\n", StudentID);
            printf(" Student Information\n");
            printf("-------------------------\n");
            printf(" ID:    %s\n", st.ID);
            printf(" Name:  %s\n", st.Name);
            printf(" Email: %s\n", st.Email);
            printf(" Phone: %s\n", st.Phone);
            printf("\n Total Number of Courses: %d\n", st.NumberOfCourse);
            break;
		}
		
	}
	fclose(student_file);
	
	if (!student_found) {
        printf("\nError: Student with ID '%s' not found.\n", StudentID);
        return 0; 
    }
    
    FILE *course_file = fopen(COURSE_FILE, "rb");
    if (course_file == NULL) {
        printf("\n Course data file not found or empty.\n");
        return 0;
    } 
	
	 printf("\n Courses Enrolled:\n");
    printf("-------------------------\n");
    
    while (fread(&cr, sizeof(cr), 1, course_file) == 1)
    {
    	if (strcmp(StudentID, cr.StudentID) == 0) {
            course_count++;
            printf(" Course %d Code: %s\n", course_count, cr.Code);
            printf(" Course %d Name: %s\n", course_count, cr.Name);
        }
	}
	
	if (course_count == 0) {
        printf(" No courses found for this student.\n");
    }

    fclose(course_file);
    return 1; 

}

void EditStudent(char *StudentID)
{
	int i;
    system("cls");

    FILE *fp = fopen(ACCOUNT_FILE, "rb");
    if (!fp) {
        printf("\n Error: Student file not found.\n");
        return;
    }

    Students list[500];
    int count = 0;
    int foundIndex = -1;

    while (fread(&list[count], sizeof(Students), 1, fp) == 1)
    {
        if (strcmp(list[count].ID, StudentID) == 0)
        {
            foundIndex = count;
        }
        count++;
    }
    fclose(fp);

    if (foundIndex == -1)
    {
        printf("\n Student with ID %s not found!\n", StudentID);
        return;
    }

    Students st = list[foundIndex];
    char temp[100];

    printf("\n ==== EDITING STUDENT (ID: %s) ====\n\n", st.ID);

    // NAME
    printf(" New Name (0 = keep old) [Current: %s]: ", st.Name);
    scanf(" %[^\n]", temp);
    ClearInputBuffer();
    if (strcmp(temp, "0") != 0)
        strcpy(st.Name, temp);

    // EMAIL
    printf(" New Email (0 = keep old) [Current: %s]: ", st.Email);
    scanf(" %30s", temp);
    ClearInputBuffer();
    if (strcmp(temp, "0") != 0)
        strcpy(st.Email, temp);

    // PHONE
    printf(" New Phone (0 = keep old) [Current: %s]: ", st.Phone);
    scanf(" %20s", temp);
    ClearInputBuffer();
    if (strcmp(temp, "0") != 0)
        strcpy(st.Phone, temp);

    // NUMBER OF COURSES
    int nc;
    printf(" New Number of Courses (0 = keep old) [Current: %d]: ", st.NumberOfCourse);
    scanf("%d", &nc);
    ClearInputBuffer();
    if (nc >= 1 && nc <= 4)
        st.NumberOfCourse = nc;

    // Save back
    list[foundIndex] = st;

    fp = fopen(ACCOUNT_FILE, "wb");
    for (i = 0; i < count; i++)
        fwrite(&list[i], sizeof(Students), 1, fp);

    fclose(fp);

    printf("\n Student Updated Successfully!\n");
    printf(" Press ENTER to continue...");
    getchar();
}



void DeleteStudent(char StudentID[11])
{
	FILE *student_read = fopen(ACCOUNT_FILE,"rb");
	if (student_read == NULL)
	 {
	 	printf(" Error: Student file not found!\n");
        return;
	 }
	 
	 Students list[500];
     int count = 0;
     
     while(fread(&list[count], sizeof(Students), 1, student_read))
     {
     	count++;
	 }
	 fclose(student_read);
	 
	 
	 int found = 0;
	 
	 FILE *fout = fopen("temp.dat","wb");
	 
	 for (i=0; i<count; i++)
	 {
	 	if (strcmp(list[i].ID, StudentID) ==0)
	 	{
	 		found = 1;
	 		continue;
		 }fwrite(&list[i], sizeof(Students), 1, fout);
	 }
	 fclose(fout);
	 
	 if (!fout)
	 {
	 	printf("Student ID not found!\n");
        remove("temp.dat"); 
        return;
	 }
	 
	remove(ACCOUNT_FILE);
    rename("temp.dat", ACCOUNT_FILE);
    printf("Student deleted successfully.\n");
    
    
    
    
    
    FILE *courses_read = fopen(COURSE_FILE, "rb");
    if (courses_read == NULL)
	 {
	 	printf(" Error: Courses file not found!\n");
        return;
	 }
	 Courses clist[500];
	 int c=0;
	 while(fread(&clist[c], sizeof(Students), 1, courses_read))
     {
     	c++;
	 }
	 fclose(courses_read);
	 
	 FILE *cout = fopen("temp_courses.dat", "wb");
	 for (i=0; i<c; i++)
	 {
	 	if (strcmp(clist[i].StudentID, StudentID) !=0)
	 	{
	 		fwrite(&clist[i], sizeof(Courses), 1, cout);
	 		
		 }
		 
	 }
	 
	 fclose(cout);
	 
	 remove(COURSE_FILE);
    rename("temp_courses.dat", COURSE_FILE);
    
}
void DeleteAllStudents()
{
	FILE *f = fopen(ACCOUNT_FILE, "wb");
	if(f) fclose(f);
	FILE *c = fopen(COURSE_FILE, "wb");
	if(c) fclose(c);
	
	printf("All students and their courses deleted successfully.\n");
	
}

int login()
{
	char username[20];
    char password[20];
    int attempts = 0;  

    while(attempts < 3)
    {

	    printf("\nLogin to your account:\n\n");
		
		printf("Enter username: ");
		scanf("%s", &username);
		
		printf("Enter Password: ");
		inputPassword(password);  
		
		if(strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0)
	    {
	        printf("\n Login Successful! Access Granted.\n");
	        return 1;  
	    }
	    else
	    {
	    	attempts++;
	        printf("\n Invalid Username or Password! Access Denied.\n");
	          
	    }
	}
	
	printf("\n You have entered wrong credentials 3 times.\n");
    printf(" Access Denied. Exiting Program...\n\n");

    return 0;
	
	
}

void inputPassword(char *pass) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch(); 

        if (ch == 13) {
            pass[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 8 && i > 0) {  
            i--;
            printf("\b \b"); 
        }
        else {
            pass[i++] = ch;
            printf("*");   
        }
    }
}

void PlaySlidingPuzzle()
{
    srand(time(NULL));
    int moves=150;
    int arr[3][3];
    char exit, again;

    while(1){
        pattern(arr);
        system("cls");
        rules();
        system("cls");

        while(!win(arr))
        {	
            if (moves==0)
			{
				break;
			}

            printf("\t\t Moves left: %d\n\n\n", moves);
			showMatrix(arr);
				
			int k = readEnteredKey();

            // Exit game
			if (k== 101 || k == 69)
			{
				printf("Are you sure you want to exit the game (y/n): ");
				scanf(" %c", &exit);

				if (exit == 'y' || exit == 'Y')
				{
					return;   // return back to main menu
				}	
			}

			move(arr, k, &moves);  
			system("cls");
		}

		if (moves == 0)
		{
			printColor("YOU LOSE THE GAME, MOVES END\n", RED);
		}
		else{
			printColor("YOU WON!!\n", GREEN);
		}

		printf("Do you want to play again (y/n): ");
		scanf(" %c", &again);

		if (again == 'n' || again == 'N')
		{
			return; // go back to menu
		}
		else {
			moves = 150;
		}
	}
}


void rules(){
	char start;
	printColor("\tWELCOME TO TILES PUZZLE GAME\n\n", GREEN);
    printColor("\tRULES OF THE GAME\n", GREEN);
    printf("\n1)You can move only 1 step at a time with the arrow key.\n");
    printf("\nMove UP : UP ARROW");
    printf("\nMove DOWN : DOWN ARROW");
    printf("\nMove RIGHT : RIGHT ARROW");
    printf("\nMove LEFT : LEFT ARROW");
    printf("\n\n2)You can move numbers at an empty position only.");
    printf("\n\n3)For each valid move: Your total number of moves will be decrease by 1.");
    printf("\n\n4)Winning situation: Numbers should be arranged as shown below\n\n");
    printf("\t\t------------------\n");
    printf("\t\t| 1  |  2  |  3  |\n");
    printf("\t\t| 4  |  5  |  6  |\n");
    printf("\t\t| 7  |  8  |     |\n");
    printf("\t\t------------------\n");
    printf("\n5)You can exit the game at any time by pressing 'E' or 'e'\n\nEnter any key to start.....");
    getch();
}


void pattern(int arr[3][3])
{
	int i,j;
	int nums[8];
	for (i=0; i<8; i++)
	{
		nums[i] = i+1;
	}		
		
	for (i = 7; i > 0; i--)
    {
        int r = rand() % (i + 1);
        int temp = nums[i];
        nums[i] = nums[r];
        nums[r] = temp;
    }    
    
	
	int index = 0;	
	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (i == 2 && j==2)
			{
				arr[i][j]= 0;
				
			}
			else{
				arr[i][j] = nums[index++];
			}	
			
		}
	}
}

void showMatrix(int arr[3][3])
{
    int i,j;
    printf("\n\n");
    printf("--------------------\n");
    for(i=0;i<3;i++)
    {
        printf("|");
        for(j=0;j<3;j++)
        {
            if(arr[i][j]!=0)
                printf("%2d | ",arr[i][j]);
            else
                printf("   | ");
        }
        printf("\n");
    }
    printf("--------------------\n");
}


int readEnteredKey()
{
	char ch;
	ch=_getch();
	if (ch ==-32)
	{
		ch =_getch();
	}
	return ch;
}
void move(int arr[3][3], int k, int *moves){
	int i,j;
	for (i=0; i<3; i++)
	{
		for ( j=0; j<3; j++)
		{
			if (arr[i][j] == 0)
			{
				
				if (k==72 && i>0)
				{
					arr[i][j] = arr[i-1][j];
					arr[i-1][j] = 0;
					(*moves)--;
;
					return;
				
				}
				else if (k==80 && i<2)
				{
					arr[i][j] = arr[i+1][j];
					arr[i+1][j] = 0;
					(*moves)--;
;
					return;
				}
				else if (k==75 && j>0) //left
				{
					arr[i][j] = arr[i][j-1];
					arr[i][j-1] = 0;
					*moves--;
					return;
				}
				else if (k==77 && j<2)
				{
					arr[i][j] = arr[i][j+1];
					arr[i][j+1] = 0;
					(*moves)--;
;
					return;
				}
				
			}
			
		}
	}
	printf("Invalid Move");
} 

int win(int arr[3][3])
{
    int i,j, k = 1;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (i == 2 && j == 2)  
                return arr[i][j] == 0;  // final cell must be 0

            if (arr[i][j] != k)
                return 0;

            k++;
        }
    }

    return 1;
}

