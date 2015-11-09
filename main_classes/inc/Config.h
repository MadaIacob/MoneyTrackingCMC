class Config {
	private:
		string configName;
		string default_wallet; // = my.wallet
		string default_currency; // = RON
		string default_income_category; // = salary
		string default_spending_category; // = other
		string currencies; // = RON, EUR, USD
		string rate_EUR_RON; // = 4.42
		string rate_RON_EUR; // = 0.23
		string rate_USD_RON; // = 3.92
		string rate_EUR_USD; // = 1.13 
		
	public:
		Config(string configName);
		void setDefaultWallet(string walletName);
		string getDefaultWallet();
		string getDefaultIncomeCategory();
		string getDefaultSpendingCategory();
		bool readConfigFile();
		bool writeConfigFile();
};
