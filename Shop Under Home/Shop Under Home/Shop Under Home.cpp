#include <iostream>
#include <vector>
#include <iomanip>

#define st starline();
using namespace std;

// ==================== 1. Product Class ====================
class Product {
private:
	string _name;
	int _id;
	float _price;
	int _quantity;

public:
	Product(string name, int id, float price, int quantity)
		: _name(name), _id(id), _price(price), _quantity(quantity) {
	}

	void sell(int amount) {
		if (amount > _quantity) {
			cout << "--> [!] Error: Not enough quantity in stock!\n";
		}
		else if (amount <= 0) {
			cout << "--> [!] Error: Invalid quantity!\n";
		}
		else {
			_quantity -= amount;
		}
	}

	void display() const {
		cout << "========================================\n";
		cout << left << setw(12) << "Name" << " : " << _name << endl;
		cout << left << setw(12) << "Price" << " : " << _price << " EGP\n";
		cout << left << setw(12) << "Quantity" << " : " << _quantity << endl;
		cout << left << setw(12) << "ID" << " : " << _id << endl;
		cout << "========================================\n";
	}

	int getid() const { return _id; }
	string getName() const { return _name; }
	float getPrice() const { return _price; }
	int getQuantity() const { return _quantity; }
};

// ==================== 2. CartItem Class ====================
class CartItem {
private:
	Product p;
	int _quantity;

public:
	CartItem(Product prod, int quantity) : p(prod), _quantity(quantity) {}

	void DisplayCartItem() const {
		cout << left << setw(15) << p.getName()
			<< setw(10) << _quantity
			<< setw(10) << p.getPrice()
			<< setw(10) << GetSubtotal() << " EGP\n";
	}

	float GetSubtotal() const {
		return p.getPrice() * _quantity;
	}

	int getProductId() const {
		return p.getid();
	}
};

// ==================== 3. Cart Class ====================
class Cart {
private:
	vector<CartItem> Vci;

public:
	void AddItem(CartItem i) {
		Vci.push_back(i);
	}

	
	bool removeItem(int id) {
		for (auto it = Vci.begin(); it != Vci.end(); ++it) {
			if (it->getProductId() == id) {
				Vci.erase(it);
				cout << "--> [✓] Item removed from cart successfully.\n";
				return true;
			}
		}
		cout << "--> [×] Item not found in cart!\n";
		return false;
	}

	float CalcTotal() const {
		float sum = 0;
		for (const auto& item : Vci) {
			sum += item.GetSubtotal();
		}
		return sum;
	}

	bool isEmpty() const {
		return Vci.empty();
	}

	void clearCart() {
		Vci.clear();
	}

	void displayReceipt() const {
		if (Vci.empty()) {
			cout << "\n[!] Cart is empty! No receipt to print.\n";
			return;
		}

		cout << "\n============================== RECEIPT ==============================\n";
		cout << left << setw(15) << "Item" << setw(10) << "Qty" << setw(10) << "Price" << setw(10) << "Subtotal" << endl;
		cout << "---------------------------------------------------------------------\n";
		for (const auto& item : Vci) {
			item.DisplayCartItem();
		}
		cout << "---------------------------------------------------------------------\n";
		cout << left << setw(35) << "TOTAL AMOUNT:" << CalcTotal() << " EGP\n";
		cout << "=====================================================================\n\n";
	}
};

// ==================== 4. Inventory Class ====================
class Inventory {
private:
	vector<Product> Vp;

public:
	void AddProduct(Product p) {
		Vp.push_back(p);
	}

	bool deleteProduct(int id) {
		for (auto it = Vp.begin(); it != Vp.end(); ++it) {
			if (it->getid() == id) {
				cout << "--> [✓] Product '" << it->getName() << "' deleted from inventory.\n";
				Vp.erase(it);
				return true;
			}
		}
		cout << "--> [×] Product with ID " << id << " not found in inventory!\n";
		return false;
	}

	Product* searchProduct(int id) {
		for (auto& product : Vp) {
			if (product.getid() == id) {
				return &product;
			}
		}
		return nullptr;
	}

	bool buyProduct(int id, int quantity, Cart& cart) {
		Product* prod = searchProduct(id);

		if (prod == nullptr) {
			cout << "--> [×] Product with ID " << id << " Not Found!\n";
			return false;
		}

		if (quantity <= 0 || quantity > prod->getQuantity()) {
			cout << "--> [×] Insufficient Stock! Available: " << prod->getQuantity() << endl;
			return false;
		}

		prod->sell(quantity);
		CartItem item(*prod, quantity);
		cart.AddItem(item);
		cout << "--> [✓] Added " << quantity << "x " << prod->getName() << " to Cart successfully.\n";
		return true;
	}

	void displayProducts() const {
		if (Vp.empty()) {
			cout << "\n[!] Inventory is empty.\n";
			return;
		}

		cout << "\n--- CURRENT INVENTORY ---\n";
		for (const auto& product : Vp) {
			product.display();
		}
	}
};

// ==================== 5. Admin Class ====================
class Admin {
private:
	string _username;
	string _password;

public:
	Admin(string user, string pass) : _username(user), _password(pass) {}

	bool login(string user, string pass) const {
		return (user == _username && pass == _password);
	}
};

void starline() {
	for (int i = 0; i < 60; i++) cout << '*';
	cout << endl;
}

// ==================== MAIN PROGRAM ====================
int main() {
	Admin systemAdmin("admin", "1234");
	Inventory inv;
	Cart currentCart;

	inv.AddProduct(Product("PEPSI", 1, 20.0, 100));
	inv.AddProduct(Product("CHEEPSY", 2, 10.0, 150));
	inv.AddProduct(Product("MILK", 3, 35.0, 50));

	cout << "====================================================\n";
	cout << "     PROFESSIONAL CASHIER & INVENTORY SYSTEM        \n";
	cout << "====================================================\n";

	string user, pass;
	int attempts = 0;
	bool loggedIn = false;

	while (attempts < 3 && !loggedIn) {
		cout << "\n[+] LOGIN REQUIRED\n";
		cout << "Enter Username: ";
		cin >> user;
		cout << "Enter Password: ";
		cin >> pass;

		if (systemAdmin.login(user, pass)) {
			cout << "\n[✓] Access Granted! Welcome, " << user << ".\n";
			loggedIn = true;
		}
		else {
			attempts++;
			cout << "[×] Invalid credentials! Remaining attempts: " << 3 - attempts << endl;
		}
	}

	if (!loggedIn) {
		cout << "\n[!] System locked due to multiple failed login attempts.\n";
		return 0;
	}

	st;

	
	int choice = 0;
	do {
		cout << "\n=============== MAIN MENU ===============\n";
		cout << "1. Add Item to Cart (Sell)\n";
		cout << "2. Remove Item from Cart\n";
		cout << "3. Search Product by ID\n";
		cout << "4. Print Receipt & Checkout\n";
		cout << "5. Display Inventory\n";
		cout << "6. Add New Product to Inventory\n";
		cout << "7. Delete Product from Inventory (Admin)\n";
		cout << "8. Exit System\n";
		cout << "=========================================\n";
		cout << "Select Option [1-8]: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			int id, qty;
			cout << "\nEnter Product ID to sell: ";
			cin >> id;
			cout << "Enter Quantity: ";
			cin >> qty;
			inv.buyProduct(id, qty, currentCart);
			break;
		}
		case 2: {
			int id;
			cout << "\nEnter Product ID to remove from cart: ";
			cin >> id;
			currentCart.removeItem(id);
			break;
		}
		case 3: {
			int id;
			cout << "\nEnter Product ID to search: ";
			cin >> id;
			Product* p = inv.searchProduct(id);
			if (p != nullptr) {
				cout << "\n[Product Details Found]:\n";
				p->display();
			}
			else {
				cout << "\n[×] Product Not Found!\n";
			}
			break;
		}
		case 4:
			currentCart.displayReceipt();
			if (!currentCart.isEmpty()) {
				char confirm;
				cout << "Complete checkout and clear cart? (y/n): ";
				cin >> confirm;
				if (confirm == 'y' || confirm == 'Y') {
					currentCart.clearCart();
					cout << "--> Transaction completed successfully. Cart cleared.\n";
				}
			}
			break;
		case 5:
			inv.displayProducts();
			break;
		case 6: {
			string name;
			int id, qty;
			float price;
			cout << "\nEnter Product Name: ";
			cin >> name;
			cout << "Enter Product ID: ";
			cin >> id;
			cout << "Enter Product Price: ";
			cin >> price;
			cout << "Enter Product Quantity: ";
			cin >> qty;
			inv.AddProduct(Product(name, id, price, qty));
			cout << "--> [✓] Product added to inventory successfully!\n";
			break;
		}
		case 7: {
			int id;
			cout << "\nEnter Product ID to delete from inventory: ";
			cin >> id;
			inv.deleteProduct(id);
			break;
		}
		case 8:
			cout << "\nExiting system... Great job on your project!\n";
			break;
		default:
			cout << "\n[!] Invalid choice, please try again.\n";
		}

	} while (choice != 8);

	return 0;
}