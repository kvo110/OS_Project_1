/*
  main.cpp
  Operating Systems Project 1
  Process Scheduling Simulation (FCFS + Round Robin)

  - Reads process data from a file
  - Implements FCFS and Round Robin scheduling
  - Displays a text-based Gantt chart
  - Calculates WT, TAT, averages, and CPU utilization
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
  int pid;
  int arrival;
  int burst;
  int priority;

  int remaining;
  int completion;
  int waiting;
  int turnaround;
};

struct Segment {
  string label;
  int start;
  int end;
};

bool isNumber(const string& s) {
  for (char c : s) {
    if (!isdigit(c)) return false;
  }
  return true;
}

vector<Process> readProcesses(const string& filename) {
  ifstream fin(filename);
  vector<Process> processes;
  string line;

  while (getline(fin, line)) {
    if (line.empty()) continue;

    istringstream iss(line);
    string a, b, c, d;
    iss >> a;

    if (!isNumber(a)) continue;
    iss >> b >> c >> d;

    Process p;
    p.pid = stoi(a);
    p.arrival = stoi(b);
    p.burst = stoi(c);
    p.priority = stoi(d);
    p.remaining = p.burst;
    p.completion = p.waiting = p.turnaround = 0;

    processes.push_back(p);
  }

  return processes;
}

void reset(vector<Process>& p) {
  for (auto& x : p) {
    x.remaining = x.burst;
    x.completion = x.waiting = x.turnaround = 0;
  }
}

void printGantt(const vector<Segment>& g) {
  for (auto& s : g) cout << "| " << s.label << " ";
  cout << "|\n";

  cout << g[0].start;
  for (auto& s : g) cout << setw(5) << s.end;
  cout << "\n";
}

void calculateStats(vector<Process>& p) {
  for (auto& x : p) {
    x.turnaround = x.completion - x.arrival;
    x.waiting = x.turnaround - x.burst;
  }
}

void printResults(const vector<Process>& p, int finish, int busy) {
  double avgWT = 0, avgTAT = 0;

  cout << "\nPID  AT  BT  CT  WT  TAT\n";
  for (auto& x : p) {
    cout << setw(3) << x.pid
         << setw(4) << x.arrival
         << setw(4) << x.burst
         << setw(4) << x.completion
         << setw(4) << x.waiting
         << setw(5) << x.turnaround << "\n";

    avgWT += x.waiting;
    avgTAT += x.turnaround;
  }

  avgWT /= p.size();
  avgTAT /= p.size();

  cout << "\nAverage WT: " << fixed << setprecision(2) << avgWT << "\n";
  cout << "Average TAT: " << fixed << setprecision(2) << avgTAT << "\n";
  cout << "CPU Utilization: " << fixed << setprecision(2)
       << (double(busy) / finish) * 100 << "%\n";
}

void runFCFS(vector<Process> p) {
  reset(p);
  sort(p.begin(), p.end(), [](auto& a, auto& b) {
    return a.arrival < b.arrival;
  });

  vector<Segment> g;
  int time = 0, busy = 0;

  for (auto& x : p) {
    if (time < x.arrival) {
      g.push_back({"IDLE", time, x.arrival});
      time = x.arrival;
    }

    g.push_back({"P" + to_string(x.pid), time, time + x.burst});
    time += x.burst;
    busy += x.burst;
    x.completion = time;
  }

  calculateStats(p);
  cout << "\nFCFS Gantt Chart:\n";
  printGantt(g);
  printResults(p, time, busy);
}

void runRR(vector<Process> p, int q) {
  reset(p);
  sort(p.begin(), p.end(), [](auto& a, auto& b) {
    return a.arrival < b.arrival;
  });

  queue<int> rq;
  vector<Segment> g;

  int time = 0, busy = 0, i = 0, done = 0;

  while (done < p.size()) {
    while (i < p.size() && p[i].arrival <= time) {
      rq.push(i++);
    }

    if (rq.empty()) {
      time++;
      continue;
    }

    int idx = rq.front();
    rq.pop();

    int slice = min(q, p[idx].remaining);
    g.push_back({"P" + to_string(p[idx].pid), time, time + slice});

    time += slice;
    busy += slice;
    p[idx].remaining -= slice;

    while (i < p.size() && p[i].arrival <= time) {
      rq.push(i++);
    }

    if (p[idx].remaining > 0) {
      rq.push(idx);
    } else {
      p[idx].completion = time;
      done++;
    }
  }

  calculateStats(p);
  cout << "\nRound Robin (q = " << q << ") Gantt Chart:\n";
  printGantt(g);
  printResults(p, time, busy);
}

int main() {
  auto processes = readProcesses("processes.txt");

  cout << "Loaded " << processes.size() << " process(es)\n";

  while (true) {
    cout << "\n1) FCFS\n2) Round Robin\n3) Quit\nSelection: ";
    int c;
    cin >> c;

    if (c == 1) runFCFS(processes);
    else if (c == 2) {
      int q;
      cout << "Enter time quantum: ";
      cin >> q;
      runRR(processes, q);
    } else break;
  }

  return 0;
}
