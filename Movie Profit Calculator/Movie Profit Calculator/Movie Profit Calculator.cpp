//2.4.26-2.5.26
//This is a SIMPLE calculator to determine a movie's break-even point and net profit or losses for the production studio using only its production and marketing budgets. See the disclaimers below for additional details.

//Preprocessor Libraries
#include <iostream> //For input/output
#include <string> //For getline

using namespace std; //Declare standard namespace

const string INDENT = "\t\t\t"; //Size of indent in wait=3 tabs

void showDisclaimers(); //Prints off a series of information at the beginning to tell the user how the calculator works
void readValues(double&, double&, double&); //Gets the production and marketing values from the user
void calculateNet(double, double, double, double&, double&, string&); //Calculates the break-even point and net earnings or losses for the production studio
void printResults(double, double, string); //Print the break-even point, net gain/loss for the studio, and the rating for how it performed
void wait(); //Pause alternative
void clearCin(); //Clears cin field for wait function or wipe cin memory

int main() {
	double globalGross = 0; //Initialize all major variables
	double productionBudget = 0;
	double marketingBudget = 0;
	double breakEvenPoint = 0;
	double netGainOrLoss = 0;
	string performanceStatus;

	cout << "SIMPLE BREAK-EVEN POINT AND STUDIO THEATRICAL NET PROFIT/LOSS CALCULATOR FOR FILMS\n"; //Program title
	cout << "----------------------------------------------------------------------------------\n\n";

	showDisclaimers(); //Print information about the calculator and its logic before values are entered
	readValues(globalGross, productionBudget, marketingBudget); //Read in the film's box office gross and production and marketing budgets
	calculateNet(globalGross, productionBudget, marketingBudget, breakEvenPoint, netGainOrLoss, performanceStatus); //Calculate the film's break-even point and net gain or loss for the studio, while also rating its performance
	printResults(breakEvenPoint, netGainOrLoss, performanceStatus); //Print the data from calculateNet and end the program

	wait(); //Pause before ending
	return 0;
}








void showDisclaimers() { //Function to print information about the calculator and its logic before values are entered
	cout << "A FEW DISCLAIMERS AND LIMITATIONS:\n\n";
	cout << "-Production budgets are sometimes listed as a range (i.e. $150-200 million), and the TRUE production budget\nof a movie is sometimes underreported by as much as 25% for years after the film first releases.\nFor best results, ASSUME IT TO BE THE HIGHEST CURRENTLY-PUBLISHED VALUE.\n\n";
	cout << "-Marketing budgets aren't usually published, but a standard industry estimate is usually HALF the production budget.\nIF YOU DON'T KNOW THE MOVIE'S MARKETING BUDGET, EITHER ENTER HALF OF THE PRODUCTION BUDGET, OR \"?\" BELOW\n(WHICH WILL CAUSE IT TO DEFAULT TO HALF).\n\n";
	cout << "-This calculates the amount of money earned by just the production company, as a significant cut of the profits\n(regardless of whether or not the movie was successful) go to theaters. For American films,\nthis usually means the production company gets 50-55% of domestic revenue and 40% of international revenue,\naveraging to about 50% of worldwide revenue overall (WHICH IS WHAT THIS CALCULATOR ASSUMES).\n\n";
	cout << "-This calculator only factors in theater revenue and costs and NOT additional factors like streaming revenue,\nphysical media sales, or merch sales (that could increase a movie's revenue during and/or after its theatrical run).\n\n";
	cout << "-This calculator assumes only a single, modern release for the movie in question. If there's more then\nfive to ten years of inflation to take into account, than the calculated profits/losses could be\nsignificantly different than those for a more recent movie. However, you can take the net earnings from this and\nplug it into an inflation calculator to get a semi-accurate modern equivalent.\n\n";
	cout << "-Rereleases over the course of several decades will also increase a movie's lifetime box office gross,\nbut different degrees of inflation during each release would also further complicate things and therefore,\naren't considered in this.\n\n";
	cout << "-Other minor expenditures that could also further cut into or divide a studio's profits like distribution fees\nor backend deals are also not accounted for here.\n\n";
	cout << "-What constitutes a major or minor success or failure is somewhat subjective, but for the purposes of this calculator,\nI had it call it based on how well the film performed relative to its break-even point\n(and by extension, its production budget) and NOT in general. A $1 billion haul might be impressive for a film\nthat cost $200 million to make, but less so for a film that cost $300 million or more (if it even profited at all).\n\n";
	cout << "-The keyword with all of this is SIMPLE. As you can tell, there are a variety of metrics that determine\nhow much a studio makes from a movie, and this calculator exists to give a rough conservative approximation\nbased on the most crucial ones.\n";
	cout << "-------------------------------------------------------------------------------------------------------\n\n";
}








void readValues(double& globalGross, double& productionBudget, double& marketingBudget) { //Function to get the production and marketing values from the user
	//Read in the film's global box office gross
	cout << "Enter the film's global box office gross IN MILLIONS (Don't include trailing zeroes, and use\ndecimal values for anything less than a million.)\n(i.e. Enter 200 for 200 million or 1.5 for 1.5 million.): $ ";
	cin >> globalGross;
	while (cin.fail() || globalGross <= 0) { //Checks for invalid characters or amounts
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\nError. Global box office gross must be a positive number. Please try again: $ "; //Tells you if entry is invalid, and repeats until valid entry is entered
		cin >> globalGross; //Stores entered value
	}
	clearCin(); //Clear cin storage in case there's any trailing invalid characters


	//Read in the film's production budget
	cout << "\n\nEnter the film's production budget IN MILLIONS (Don't include trailing zeroes, and use\ndecimal values for anything less than a million.)\n(i.e. Enter 200 for 200 million or 1.5 for 1.5 million.): $ ";
	cin >> productionBudget;
	while (cin.fail() || productionBudget <= 0) { //Checks for invalid characters or amounts
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\nError. Production budget must be a positive number. Please try again: $ "; //Tells you if entry is invalid, and repeats until valid entry is entered
		cin >> productionBudget; //Stores entered value
	}
	clearCin(); //Clear cin storage in case there's any trailing invalid characters


	
	string temporaryMarketingBudgetEntry;
	double temporaryMarketingBudgetNumber = 0;
	//Read in the film's marketing budget
	cout << "\n\nEnter the film's marketing budget IN MILLIONS (Don't include trailing zeroes, and use\ndecimal values for anything less than a million.) (i.e. Enter 200 for 200 million or 1.5 for 1.5 million.).\nAdditionally, if the marketing budget isn't publicly disclosed, just type \"?\" and it will default\nto half the production budget: $ ";
	while (true) { //Keeps asking for a valid marketing budget value until one is given
		getline(cin, temporaryMarketingBudgetEntry); //Store entered marketing budget as a STRING

		if (temporaryMarketingBudgetEntry == "?") { //If the entry was a question mark, set the marketing budget to half the production budget and end the loop
			marketingBudget = productionBudget / 2.0;
			break;
		}

		try { //Attempt to convert the entered marketing budget to a double if it isn't a question mark
			temporaryMarketingBudgetNumber = stod(temporaryMarketingBudgetEntry);

			if (temporaryMarketingBudgetNumber > 0) { //If it's positive, set the value and end the loop
				marketingBudget = temporaryMarketingBudgetNumber;
				break;
			}
		}

		catch (exception&) {
			//Entry was invalid and prompt will repeat below
		}

		cout << "\nError. Marketing budget must be a positive number or \"?\". Please try again: $ "; //Tells you if entry is invalid, and repeats until valid entry is entered
	
	} //End while loop

} //End readValues function








void calculateNet(double globalGross, double productionBudget, double marketingBudget, double& breakEvenPoint, double& netGainOrLoss, string& performanceStatus) { //Function to calculate the break-even point and net earnings or losses for the production studio
	breakEvenPoint = 2 * (productionBudget + marketingBudget); //Calculate the break-even point, assuming theaters get half the revenue as explained above
	netGainOrLoss = (globalGross / 2) - (productionBudget + marketingBudget); //Calculate the film's net gain or loss at the box office, again using the metrics explained above

	//Appraise the film's box office performance by comparing its net gain/loss compared to its break-even point
	if ((globalGross >= breakEvenPoint) && (globalGross <= breakEvenPoint * 1.25)) { //If the film made more than its break-even point but only 25% more at most, call it a "modest success"
		performanceStatus = "Modest Success";
	}

	if (globalGross > breakEvenPoint * 1.25) { //If the film made more than 1.25x its break-even point, call it a "major hit"
		performanceStatus = "Major Hit";
	}

	if (globalGross == breakEvenPoint) { //If the film made back its budget EXACTLY, say it "just barely broke even"
		performanceStatus = "Just Barely Broke Even";
	}

	if ((globalGross < breakEvenPoint) && (globalGross > breakEvenPoint * .75)) { //If the film made less than its break-even point but more than 75% of it, call it a "minor failure"
		performanceStatus = "Minor Failure";
	}

	if (globalGross <= breakEvenPoint * .75) { //If the film made 75% of its break-even point or less, call it a "major flop"
		performanceStatus = "Major Flop";
	}
}








void printResults(double breakEvenPoint, double netGainOrLoss, string performanceStatus) { //Function to print the break-even point, net gain/loss for the studio, and the rating for how it performed
	//Print the break-even point
	if (breakEvenPoint < 1000) { //If the break-even point is less than ten figures, print "million" at the end
		cout << "\n\nBreak-Even Point: $ " << breakEvenPoint << " Million\n";
	}

	if (breakEvenPoint >= 1000) { //If the break-even point is ten figures or more, print "billion" at the end
		cout << "\nBreak-Even Point: $ " << breakEvenPoint / 1000 << " Billion\n";
	}

	//Print the net gain or loss
	if (netGainOrLoss < 1000) { //If the net gain or loss is less than ten figures, print "million" at the end
		cout << "Net Profit/Loss for Production Studio: $ " << netGainOrLoss << " Million\n";
	}

	if (netGainOrLoss >= 1000) { //If the net gain or loss is ten figures or more, print "billion" at the end
		cout << "Net Profit/Loss for Production Studio: $ " << netGainOrLoss / 1000 << " Billion\n";
	}

	//Print an appraisal of how the film performed
	cout << "Performance: " << performanceStatus << endl;
}








void wait() //Pause alternative
{
	clearCin();
	char ch;
	cout << endl << INDENT << "Press the Enter key to continue ... ";
	cin.get(ch);
}








void clearCin()
{
	//The following if-statement checks to see how many characters are in cin's buffer
	//If the buffer has characters in it, the ignore method gets rid of them.
	//If cin is in the fail state, clear puts it back to the ready state.
	//If cin is not already in the fail state, it still doesn't hurt to call the clear function.
	if (cin.rdbuf()->in_avail() > 0) //If the buffer is empty skip clear and ignore
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Clear the input buffer
	}
}