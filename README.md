Supermarket Cashier & Inventory Management System
A console-based object-oriented C++ application designed to simulate a real-world supermarket cashier and inventory workflow. This project focuses on core Object-Oriented Programming (OOP) principles, decoupled architecture, and interactive CLI management.

🚀 Features
Admin Authentication: Secure login system with credential validation to prevent unauthorized access.

Inventory Management:

Add new products with ID, name, price, and stock quantity.

Search for products instantly by ID.

Delete/remove items from inventory.

Real-time stock tracking and validation (prevents selling out-of-stock items).

Shopping Cart & Transactions:

Add desired quantities of products directly from the inventory.

Remove mistaken items from the cart.

Automatic calculation of item subtotals and grand totals using iomanip formatting.

Detailed receipt generation and inventory synchronization upon checkout.

Interactive CLI Menu: User-friendly, loop-driven interface for seamless navigation between admin and cashier tasks.

🏗️ System Architecture (OOP Design)
The project is structured into distinct, decoupled classes to ensure separation of concerns:

Product: Manages individual item states (name, id, price, quantity) and stock deduction logic (sell).

CartItem: Acts as a bridge connecting a specific Product with its purchased quantity.

Cart: Holds a collection of CartItem objects, handles subtotal/total calculations, and formats the final receipt.

Inventory: Manages the master list of available products, handles stock lookup (searchProduct), and coordinates sales (buyProduct).

Admin: Handles access control and authentication.

🛠️ Tech Stack & Concepts
Language: C++

Key Concepts: Classes & Objects, Encapsulation, Composition, Standard Template Library (std::vector), References & Pointers, Iterators, and Console Formatting (<iomanip>).

💻 How to Run
Clone or download the source code repository.

Open the .cpp file in any standard C++ IDE (such as Visual Studio, Code::Blocks, or VS Code).

Compile and run the program using a modern C++ compiler (supports C++11 or later).

Use the default login credentials when prompted:

Username: admin

Password: 1234


====================================================
     PROFESSIONAL CASHIER & INVENTORY SYSTEM        
====================================================
[+] LOGIN REQUIRED
Enter Username: admin
Enter Password: 1234
[✓] Access Granted! Welcome, admin.

=============== MAIN MENU ===============
1. Add Item to Cart (Sell)
2. Remove Item from Cart
3. Search Product by ID
4. Print Receipt & Checkout
5. Display Inventory
6. Add New Product to Inventory
7. Delete Product from Inventory (Admin)
8. Exit System
=========================================
