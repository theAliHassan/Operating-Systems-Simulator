//==============================ESSENTIAL LIBRARIES===============
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <vector>
#include "Pacman.cpp"
#include "Time.cpp"
#include "Calendar.cpp"
#include "Minesweeper.cpp"
#include "Chess.cpp"
using namespace std;
//==============================ESSENTIAL LIBRARIES===============

//============================PROTOTYPES===================
int calculator();
void PCB_Control(int line_no);
void menu_selector(int choice);
void FCFS(int p1, int p2, int p3, int p4);
void ResourceAllocate();
void NewTerminal();
void *Avg(void *arg);
void *summ(void *arg);
void AverageCalc();
void Time();
void Del_File();
void NewFile();
void MoveFile();
void CopyFile();
void MultiTasking();
void Chat();
int calculator();
void menu_selector(int);
int menu();
void pacmanStarter();
void chessStarter();
double Ram;
//============================PROTOTYPES===================

//============================GLOBAL VARIABLES====================
int variables,
    function, print_document, alloc;
int mycount = 0;
int sum = 0;
bool flag = 0;
string processName;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
//============================VARIABLES====================

//==========================PCB========================
class PCB
{
public:
  int process_ID;
  string state;
  int current_line_pointer;
  int priority;
};
PCB Data[15];
void PCB_Control(int line_no)
{
  srand(time(NULL));
  Data[i].process_ID = rand() % 100;
  Data[i].state = "queue"; //POLICY
  Data[i].current_line_pointer = line_no;
  Data[i].priority = 1;
  i++;
}
//==========================PCB========================

/////////////////////  Main Menu /////////////////////////////

//////////////////  menu_selector ////////////////////////////

//////////////////////////////////FCFS/////////////////////////

class FCFS_Algo
{
public:
  int BurstTime;
  int ArrivalTime;
  int CompletionTime;
  int TurnAround;
  int WaitingTime;
};

FCFS_Algo proc[4];

void FCFS(int p1, int p2, int p3, int p4)
{

  proc[0].ArrivalTime = 0;
  proc[1].ArrivalTime = 1;
  proc[2].ArrivalTime = 2;
  proc[3].ArrivalTime = 3;

  proc[0].BurstTime = p1;
  proc[1].BurstTime = p2;
  proc[2].BurstTime = p3;
  proc[3].BurstTime = p4;

  proc[0].CompletionTime = 0;

  for (int i = 0, j = 0; i < 4; i++)
  {

    proc[i].CompletionTime = proc[j].CompletionTime + proc[i].BurstTime;

    if (i >= 1)
      j++;
  }

  for (int i = 0, j = 0; i < 4; i++)
  {

    proc[i].TurnAround = proc[i].CompletionTime - proc[i].ArrivalTime;
  }

  ///////////////////wait//////////////////////

  for (int i = 0, j = 0; i < 4; i++)
  {

    proc[i].WaitingTime = proc[i].TurnAround - proc[i].BurstTime;
  }

  ////////////////////////OutPut///////////////

  cout << "Arrival Time    " << endl;
  for (int i = 0, j = 0; i < 4; i++)
  {

    cout << "p" << i + 1 << "   " << proc[i].ArrivalTime << "     ..." << endl;
  }

  cout << "Burst Time    " << endl;
  for (int i = 0, j = 0; i < 4; i++)
  {

    cout << "p" << i + 1 << "    " << proc[i].BurstTime << "     ..." << endl;
  }

  cout << "Completion Time    " << endl;
  for (int i = 0, j = 0; i < 4; i++)
  {

    cout << "p" << i + 1 << "    " << proc[i].CompletionTime << "     ..." << endl;
  }

  cout << "TurnAround Time   " << endl;
  for (int i = 0, j = 0; i < 4; i++)
  {

    cout << "p" << i + 1 << "    " << proc[i].TurnAround << "     ..." << endl;
  }

  cout << "Waiting Time   " << endl;
  for (int i = 0, j = 0; i < 4; i++)
  {

    cout << "p" << i + 1 << "    " << proc[i].WaitingTime << "     ..." << endl;
  }
}

class Resource
{
public:
  string processName;
  int Ram_memory;
  int Stack_memory;
  int Printer;
  int cache;
  int Disks;
};

Resource process[100];

void ResourceAllocate()
{
  int i = 0;

  if (variables >= 2)
  {
    process[i].Ram_memory = 512;
  }
  if (function >= 2)
  {
    process[i].Stack_memory = 1024;
  }

  if (alloc == 1)
  {
    cout << "Resources Allocation" << endl;
    cout << "RAM=" << process[i].Ram_memory << endl;
    cout << "Stack=" << process[i].Stack_memory << endl;
  }
}

//==========================================DRIVER FUNTION========================================

int main(int argc, char **argv)
{
  cout << "===================================== OS =============================================" << endl;
  cout << endl
       << endl;
  cout << "====================================" << endl;
  cout << "|"
       << "RAM : " << argv[1] << "     |" << endl;
  cout << "|"
       << "HDD : " << argv[2] << "        |" << endl;
  cout << "|"
       << "CORES :" << argv[3] << "       |" << endl;
  cout << "====================================" << endl;
  Ram = atof(argv[1]);
  while (true)
  {
    menu_selector(menu());
  }
}
//==========================================DRIVER FUNTION========================================

//===================================FUNTION DEFINATIONS==================================
void NewTerminal()
{
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
  system("gnome-terminal \"./myOS\"");
  // system("g++ link.cpp -o mylinknew -lpthread");
  // system("gnome-terminal -- \"./mylinknew\"");
  return;
}
//=======================using Semaphore + mutex lock + conditional varaible
void *Avg(void *arg)
{
  pthread_mutex_lock(&mut);
  while (mycount == 0)
  {
    pthread_cond_wait(&con, &mut);
  }
  cout << "Average Thread REsult===" << sum / 10;
  pthread_mutex_unlock(&mut);
  pthread_exit(NULL);
}
void *summ(void *arg)
{
  pthread_mutex_lock(&mut);
  for (int i = 0; i < 10; i++)
  {
    sum = sum + i;
  }
  mycount++;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
  pthread_exit(NULL);
}
void AverageCalc()
{
  pthread_t summation, average;
  pthread_create(&summation, NULL, summ, NULL);
  pthread_create(&average, NULL, Avg, NULL);
  pthread_join(summation, NULL);
  pthread_join(average, NULL);
}
//=======================using Semaphore + mutex lock + conditional varaible
int menu()
{
  pthread_mutex_lock(&mut);
  double size = 0.9;
  if (Ram > size)
  {
    int check = 0;
    cout << endl
         << "========================================================" << endl
         << endl
         << "1  : NEW FILE " << endl
         << "2  : COPY FILE" << endl
         << "3  : MOVE FILE" << endl
         << "4  : DELETE FILE" << endl
         << "5  : CURRENT TIME" << endl
         << "6  : CALENDAR " << endl
         << "7  : CHAT" << endl
         << "8  : SCHEDULING ALGORITHM " << endl
         << "9  : MULTITASKING" << endl
         << "10 : CALCULATOR" << endl
         << "11 : AVERAGE TIME CALCULATOR" << endl
         << "12 : PACMAN" << endl
         << "13 : MINESWEEPER" << endl
         << "14 : CHESS" << endl
         << "0 : RESTART" << endl
         << "-1 : SHUT DOWN" << endl
         << endl
         << "========================================================" << endl
         << endl
         << "ENTER PROGRAM NUMBER : ";
    cin >> check;
    if (check >= -1 || check <= 14)
    {
      pthread_cond_signal(&con);
      pthread_mutex_unlock(&mut);
      return check;
    }
    else
    {
      cout << "===========ALL RAM EATEN================" << endl;
      cout << "===========NO RESOURCES AVAILABLE======" << endl;
      cout << "===========SYSTEM IN DEADLOCK==========" << endl;
    }
  }
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
  menu();
  return -1;
}
void menu_selector(int choice)
{
  clock_t t;
  int BurstTime;
  switch (choice)
  {
  case -1:
  {
    for (int i = 0; i < 100; i++)
    {
      cout << endl;
    }
    cout << "======================  SHUTTING DOWN  ======================" << endl;
    sleep(2);
    exit(0);
  }
  break;
  case 0:
  {
    NewTerminal();
  }
  break;
  case 1:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      NewFile();
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 2:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      CopyFile();
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 3:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      MoveFile();
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 4:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      Del_File();
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }

    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 5:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      pthread_mutex_lock(&mut);
      pthread_t pt1;
      pthread_create(&pt1, NULL, Time, NULL);
      pthread_join(pt1, NULL);
      pthread_create(&pt1, NULL, Timer, NULL);
      pthread_join(pt1, NULL);
      pthread_cond_signal(&con);
      pthread_mutex_unlock(&mut);
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 6:
  {

    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      pthread_mutex_lock(&mut);
      pthread_t pt1;
      pthread_create(&pt1, NULL, Display, NULL);
      pthread_join(pt1, NULL);
      pthread_create(&pt1, NULL, Timer, NULL);
      pthread_join(pt1, NULL);
      pthread_cond_signal(&con);
      pthread_mutex_unlock(&mut);
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 7:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      Chat();
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 8:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      pthread_mutex_lock(&mut);
      pthread_t pt1;
      pthread_create(&pt1, NULL, Scheduling_Algorithm, NULL);
      pthread_join(pt1, NULL);
      pthread_create(&pt1, NULL, Timer, NULL);
      pthread_join(pt1, NULL);
      pthread_cond_signal(&con);
      pthread_mutex_unlock(&mut);
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 9:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      MultiTasking();
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 10:
  {
    double size = 0.33;
    if (Ram > size)
    {
      calculator();
      alloc = -1;
      ResourceAllocate();
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 11:
  {
    double size = 0.33;
    if (Ram > size)
    {
      AverageCalc();
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 12:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      pacmanStarter();
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  case 13:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      pthread_mutex_lock(&mut);
      pthread_t pt1;
      pthread_create(&pt1, NULL, Minesweeper, NULL);
      pthread_join(pt1, NULL);
      pthread_create(&pt1, NULL, Timer, NULL);
      pthread_join(pt1, NULL);
      pthread_cond_signal(&con);
      pthread_mutex_unlock(&mut);
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  };
  break;
  case 14:
  {
    double size = 0.33;
    if (Ram > size)
    {
      t = clock();
      chessStarter();
      t = clock() - t;
      t = clock() - t;
      Ram = Ram - size;
      cout << "  RAM LEFT ==>  " << Ram << endl;
      cout << "TOTAL TIME CONSUMED BY THIS PROCESS :" << t << " ms " << endl;
    }
    else
    {
      cout << "NO SPACE AVAILABLE" << endl;
    }
  }
  break;
  default:
  {
    cout << endl
         << "================= INVALID INPUT -  INPUT BETWEEN 1-15 =================  " << endl
         << endl;
    menu();
  }
  break;
  }
}

//========================
void Time()
{
  pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  system("sh  time.sh");
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
}
void NewFile()
{

  pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  cout << "============  DUE TO CONTEXT SWITCHING CONTROL SHIFTED  ============" << endl;
  cout << " CURRENT CONTROL :  NEW FILE PROCESS " << endl;
  system("sh new.sh"); //mimicking
  PCB_Control(49);
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
}
void Del_File()
{
  pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  cout << "in Del File Process" << endl;
  system("sh del.sh");
  PCB_Control(76);
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
}
void MoveFile()
{
  pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  cout << "in Move File Process" << endl;
  system("sh move.sh");
  PCB_Control(80);
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
}
void CopyFile()
{
  pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  cout << "in Copy File Process" << endl;
  system("sh copy.sh");
  PCB_Control(84); //context switching
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
}
//========================
void MultiTasking()
{
  //pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  int a, b, c, d;
  int p1, p2, p3, p4, a1, a2, a3, a4;
  int time;
  clock_t t;
  cout << "Enter PROGRAM NUMBERS YOU WANT TO RUN : ";
  cin >> a >> b >> c >> d;

  t = clock();
  menu_selector(a);
  t = clock() - t;

  p1 = t / 30;

  t = clock();
  menu_selector(b);
  t = clock() - t;
  p2 = t / 30;

  t = clock();
  menu_selector(c);
  t = clock() - t;
  p3 = t / 30;

  t = clock();
  menu_selector(d);
  t = clock() - t;
  p4 = t / 30;

  FCFS(p1, p2, p3, p4);
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl;
  // pthread_cond_signal(&con);
  // pthread_mutex_unlock(&mut);
}
//========================
void Chat()
{
  pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  int pipefds[2];
  int returnstatus;
  char writemessages[2][20] = {"Fatima", "Hassan"};
  char readmessage[20];
  returnstatus = pipe(pipefds);
  if (returnstatus == -1)
  {
    printf("Unable to create pipe\n");
  }
  printf("Writing to pipe - Message 1 is %s\n", writemessages[0]);
  write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
  read(pipefds[0], readmessage, sizeof(readmessage));
  printf("Reading from pipe – Message 1 is %s\n", readmessage);
  printf("Writing to pipe - Message 2 is %s\n", writemessages[0]);
  write(pipefds[1], writemessages[1], sizeof(writemessages[0]));
  read(pipefds[0], readmessage, sizeof(readmessage));
  printf("Reading from pipe – Message 2 is %s\n", readmessage);
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
}
//========================
int calculator()
{
  pthread_mutex_lock(&mut);
  auto startT = high_resolution_clock::now();
  variables = 3, function = 0, print_document = 0;
  processName = "Calculator";
  alloc = 1;
  ResourceAllocate();
  char op;
  float num1, num2;
  int s = 0;

  cout << "Enter operator either + or - or * or /: ";
  cin >> op;

  cout << "Enter two operands: ";
  cin >> num1 >> num2;

  ///Context Switching///

  PCB_Control(88);
  {
    cout << "SHOWING CONTEXT SWITCHING" << endl;
    pthread_cond_signal(&con);
    pthread_mutex_unlock(&mut);
    NewFile();
    pthread_mutex_lock(&mut);
  }

  cout << endl
       << "  ============ ARRIVED BACK IN CALCULATOR PROCESS  =============  " << endl
       << endl;

  //////////////////
  int ans = 0;
  switch (op)
  {
  case '+':
    ans = num1 + num2;
    break;

  case '-':
    ans = num1 - num2;
    break;

  case '*':
    ans = num1 * num2;
    break;

  case '/':
    ans = num1 / num2;
    break;

  default:
    cout << "Error! operator is not correct";
    break;
  }
  cout << "RESULT OF ARITHMATIC OPERATION :" << ans << endl
       << endl;
  alloc = -1;
  auto stopT = high_resolution_clock::now();
  auto durationT = duration_cast<microseconds>(stopT - startT);
  cout << "Time taken by this Process = " << durationT.count() << " MicroSeconds" << endl
       << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
  return 0;
}
void pacmanStarter()
{
  //pthread_mutex_lock(&mut);
  auto start = high_resolution_clock::now();
  pthread_t pt1;
  int select;
  char Map[11][17];
  int power, g = 0, h = 0, r = 11, c = 17, x = 4, y = 8, a = 1, b = 8, lop = 1, e = 2, f = 2;
  srand(time(NULL));
  cout << "If you want to Run any other Process then Press 1" << endl;
  int n;
  cin >> n;
  if (n == 1)
  {
    NewTerminal();
  }
  cout << endl
       << " --------------------------------" << endl;
  cout << " |Press 1 : To see Instructions.|  " << endl;
  cout << " |Press 2 : To Play game.       |  " << endl;
  cout << " |Press 3 : To Check High Score.| " << endl;
  cout << " --------------------------------" << endl;
  cout << "  Type :  ";
  cin >> select;

  setup(Map, r, c, x, y, a, b, e, f);
  score = 0, Pcount = 0, lives = 3;
  if (select == 1)
  {
    Menu();
    char a;
    cout << endl
         << "Press any key to Return to Main Menu: ";
    cin >> a;
    system("clear");
    cout << endl;
    cout << " Press 2 : To Play game.  " << endl;
    cout << " Press 3 : To Check High Score.  " << endl;
    cout << " Type :  ";
    cin >> select;
  }
  if (select == 2)
  {
    cout << endl
         << "Enter the Numbers of Lives you want: ";
    cin >> power;
    while (lop == 1)
    {
      system("clear");

      print(Map, r, c);
      logic(Map, x, y, a, b, power, r, c, e, f, lives);
      lop = win(Map);
    }
  }
  else if (select == 3)
  {
    cout << " Your High Score is : " << score << endl;
  }

  pthread_create(&pt1, NULL, Timer, NULL);
  pthread_join(pt1, NULL);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by this Process = " << duration.count() << " MicroSeconds" << endl;
  //pthread_cond_signal(&con);
  //pthread_mutex_unlock(&mut);
}
void chessStarter()
{
  pthread_mutex_lock(&mut);
  auto start = high_resolution_clock::now();
  pthread_t pt1;
  int x1, x2;
  char y1, y2, choice;
  Chess *arr[8][8];
  cout << KRED << "If you want to Run any other Process then Press 1\e[0m" << endl;
  int n;
  cin >> n;
  if (n == 1)
  {
    NewTerminal();
  }
  cout << endl;
  cout << " -----------------------------------------" << endl;
  cout << " | Please Select an Option Below:         |" << endl;
  cout << " | Press N) to Start A New Game.          |" << endl;
  cout << " | Press L) to Load The Last Save Game.   | " << endl;
  cout << " -----------------------------------------" << endl;
  cout << "	Enter your Choice : ";
  cin >> choice;
  if (choice == 'n' || choice == 'N')
  {
    NewChessBoard(arr);
  }
  if (choice == 'l' || choice == 'L')
  {
    LoadChessBoard(arr);
  }
  system("clear");
  printchessboard(arr);
  cout << "Enter the values for any player whom you want to give First Turn" << endl;
  cin >> y1 >> x1 >> y2 >> x2;
  string isdif;
  while (1)
  {
    if (turn == true)
    {
      cout << endl
           << " Player-1 turn : ";
      cin >> y1 >> x1 >> y2 >> x2;
      if (y1 == 's' && x1 == 4 && y2 == 'v' && x2 == 3)
      {
        SaveChessBoard(arr);
        cout << "Game Saved Successfully" << endl;
        break;
      }
      else if (arr[x1][y1 - 97]->player == 1)
      {
        isdif = arr[x1][y1 - 97]->name;
        arr[x1][y1 - 97]->move(arr, y1 - 97, x1, y2 - 97, x2);
        if (isdif == arr[x2][y2 - 97]->name)
        {
          if (isdif != arr[x1][y1 - 97]->name)
            turn = false;
        }
      }
      system("clear");
      printchessboard(arr);
      bool Winner = true;
      for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
          if (arr[i][j]->name == "K")
            Winner = false;
        }
      if (Winner == true)
      {
        cout << endl
             << endl
             << "\t"
             << "PLAYER-1 Has Won This Hard Fought LEGENDARY Battle of CHESS!!" << endl;
        break;
      }
    }
    else if (turn == false)
    {
      cout << endl
           << "Player-2 turn : ";
      cin >> y1 >> x1 >> y2 >> x2;
      if (arr[x1][y1 - 97]->player == 2)
      {
        isdif = arr[x1][y1 - 97]->name;
        arr[x1][y1 - 97]->move(arr, y1 - 97, x1, y2 - 97, x2);
        if (isdif == arr[x2][y2 - 97]->name)
        {
          if (isdif != arr[x1][y1 - 97]->name)
          {
            turn = true;
          }
        }
      }
      system("clear");
      printchessboard(arr);
      bool Winner = true;
      for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
          if (arr[i][j]->name == "k")
            Winner = false;
        }
      if (Winner == true)
      {
        cout << endl
             << endl
             << "\tPlayer-2 Has Won This Hard Fought LEGENDARY Battle of CHESS!!" << endl;
        break;
      }
    }
  }

  pthread_create(&pt1, NULL, Timer, NULL);
  pthread_join(pt1, NULL);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by this Process = " << duration.count() << " MicroSeconds" << endl;
  pthread_cond_signal(&con);
  pthread_mutex_unlock(&mut);
}
//===================================FUNTION DEFINATIONS==================================
