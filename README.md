# 🏦 Banking-App  

A simple **file-backed banking system** built in C++ as a student project.  
This application models core banking operations and practices fundamental C++ concepts including STL, file I/O, data structures, and object-oriented programming.  

---

## ✨ Features  
- Open / Close accounts  
- Deposits & Withdrawals  
- Transfers between accounts  
- Balance checks  
- Persistent storage: records are written to disk and restored into memory  

---

## ⚙️ Implementation Details  
- **Data Persistence**: Account records are stored in files and reloaded on startup.  
- **Data Structures**: An in-memory `std::map` manages accounts, with iterators for traversal and lookups.  
- **OOP Design**: Classes model accounts and transactions for maintainable structure.  
- **STL Practice**: Iterators and containers provide efficient account/transaction handling.  

---

## 🚀 Getting Started  

### Prerequisites  
- A C++ compiler (e.g., g++, clang++, or MSVC)  
- Visual Studio (if using `.sln` / `.vcxproj`)  

### Build & Run (Command Line Example)  
```bash
# Clone the repo
git clone https://github.com/<your-username>/Banking-App.git
cd Banking-App

# Compile
g++ "Banking App.cpp" -o BankingApp

# Run
./BankingApp
```
## 📂 Project Structure  

```plaintext
Banking-App/
├── Banking App.cpp           # Main application source
├── Banking App.sln           # Visual Studio solution
├── Banking App.vcxproj       # Project definition
├── Banking App.vcxproj.filters
├── README.md                 # Documentation
└── LICENSE                   # License information
```

## 🎯 Learning Outcomes  
This project was more than an exercise in syntax — it helped me practice:  
- Designing data models for a real-world style app  
- Applying OOP principles in C++  
- Managing program state with file persistence  
- Thinking through structure and maintainability  
## 📜 License  
This project is licensed under the [MIT License](LICENSE).  

⚠️ **Important Note**:  
This repository was created as a **student portfolio project** for educational and demonstrative purposes.  
While it is released under the MIT License, it is **not intended for direct reuse in production systems**.  
If you reference or adapt this code, please treat it as a learning resource and apply significant modifications before using it in real-world applications.

