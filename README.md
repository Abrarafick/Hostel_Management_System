# 🏨 Hostel Management System (C Project)

This is a terminal-based **Hostel Management System** written in C. It helps manage students, room allocations, payments, and complaints using simple file I/O.

---

## 📌 Features

- Add, update, delete student records
- Allocate/reallocate hostel rooms
- Track payment status
- Report and view complaints
- Room availability tracking
- University email-based login

---

## 🧠 Function Descriptions

Below are all functions in the program with explanations of what they do:

---

### 🔐 `int login()`

Prompts user to enter an email. Returns `1` if the email ends with `@versity.edu`, otherwise returns `0`. Ensures only university users can access the system.

---

### 👤 `void addStudent()`

Takes input for a new student (ID, name, email, age, room, fee status) and appends it to `students.txt`. Ensures selected room is available.

---

### 📝 `void updateStudent()`

Searches for a student by ID and allows the admin to update their data (name, email, age, room, fee status). Rewrites the `students.txt` file with updated info.

---

### ❌ `void deleteStudent()`

Removes a student by ID from `students.txt`. Uses a temporary file to rewrite all records except the one being deleted.

---

### 🚪 `void allocateRoom()`

Displays room status to help with manual room allocation. Does not perform actual assignment — just shows occupancy.

---

### 🔁 `void reallocateRoom()`

Changes the room of an existing student after checking availability. Updates the room number in `students.txt`.

---

### 💰 `void trackPayments()`

Reads all student records and prints each student's fee payment status (Paid or Not Paid).

---

### 🛠️ `void reportComplaint()`

Takes input for a complaint (student ID, issue type, description). Sets status to `"Pending"` and saves it in `complaints.txt`.

---

### 📋 `void viewComplaints()`

Reads all complaints from `complaints.txt` and displays each with student ID, issue, status, and description.

---

### 🚨 `int isRoomAvailable(int room)`

Counts how many students are already in the given room. Returns `1` (true) if less than 4 students are assigned to that room.

---

### 📊 `void showRoomStatus()`

Displays each room's number and how many students are currently assigned to it (up to room number 99).

---

## 🧾 File Formats

### `students.txt`

Stores student data in this format:

id,name,email,age,room_number,fee_paid

makefile
Copy
Edit

Example:
101,Jane Srijon,saif@versity.edu,21,12,1

yaml
Copy
Edit

---

### `complaints.txt`

Stores complaint data in this format:

student_id,issue_type,description,status

makefile
Copy
Edit

Example:
101,Fan,Fan not working in Room 12,Pending

yaml
Copy
Edit

---

## ⚙️ Technologies Used

- C language (GCC)
- File I/O: `fopen`, `fprintf`, `fscanf`
- CLI / Terminal-based interface

---

## 🧪 How to Compile & Run

### 🔧 Compile

```bash
gcc main.c -o hostel
▶️ Run
bash
Copy
Edit
```

./hostel
<h3>
🚫 Limitations
</h3>


```bash
No password-based authentication

No database (file-based only)

No GUI — CLI only

Max 4 students per room
```
<h3>
📁 Files
</h3>

```bash
main.c — Source code

students.txt — Student data

complaints.txt — Complaint records
```
  ==========================================the end==========================================



