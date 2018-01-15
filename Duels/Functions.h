//Using a single header file for all function declarations to reduce clutter

///Interface Functions///
void DrawTitle(bool newGame);

//Initializes selection check function which confirms valid inputs against variable choices
char ValidateUserSelection(char select, std::string s);		

///IO Functions///


///Player Functions///

//initializes player status "reset" function
void playerStatus(double& p1H, double& p2H, double& p1M, double& p2M, double& p1S, double& p2S,
					int& p1HP, int& p1MP, int& p1PP, int &p2HP, int& p2MP, int& p2PP, char pH);

char SetPlayerHealth();

