class Wallet {
	private:
		string walletName;
		vector<WalletEntity> walletContent;
		
	public:
		Wallet(string walletName);
		bool readWalletFile();
		bool createWalletFile();
		bool appendWalletFile();
		bool existsWalletFile();
};