class WalletEntity {
	private:
		time_t time;
		string sign;
		double amount;
		string category;
		string currency;
		
	public:
		Wallet();
		time_t getTime();
		string getSign();
		double getAmount();
		string getCategory();
		string getCurrency();
		
		void setTime();
		void setSign();
		void setAmount();
		void setCategory();
		void setCurrency();
};