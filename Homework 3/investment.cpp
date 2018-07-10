

class Investment
{
public:
	Investment(string n, int p, string d)
	{
		m_name = n;
		m_price = p;
		m_description = d;
	}
	string name() const
	{
		return m_name;
	}
	virtual bool fungible() const = 0;
	string description() const
	{
		return m_description;
	}
	int purchasePrice() const
	{
		return m_price;
	}
	virtual ~Investment()
	{

	}
private:
	string m_name;
	int m_price;
	string m_description;
};

class Stock: public Investment
{
public:
	Stock(string comp, int price, string symbol)
		:Investment(comp, price, "stock trading as " + symbol)
	{
	}
	virtual bool fungible() const
	{
		return true;
	}
	~Stock()
	{
		cout << "Destroying " << name() << ", a stock holding" << endl;
	}
};

class Painting: public Investment
{
public:
	Painting(string name, int price)
		:Investment(name, price, "painting")
	{
	}
	virtual bool fungible() const
	{
		return false;
	}
	~Painting()
	{
		cout << "Destroying " << name() << ", a painting" << endl;
	}
};

class House: public Investment
{
public:
	House(string addy, int price)
		:Investment(addy, price, "house")
	{
	}
	virtual bool fungible() const
	{
		return false;
	}
	~House()
	{
		cout << "Destroying the house " << name() << endl;
	}
};

