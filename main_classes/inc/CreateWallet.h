class CreateWalletCmd : public Command {
	private:
		Wallet wallet;
	public:
		CreateWallet(string walletName, double amount);
		//methods from Command class
		void parseParams(vector<string> params) ;
		void validateParams(vector<string> &params) ;
		void executeCommand() ;
}