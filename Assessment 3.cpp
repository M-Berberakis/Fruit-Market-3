#include<stdio.h> // We call the library stdio.h for the use of printf and scanf.
#include<ctype.h> // We call the library ctype.h for converting lowecase letters entered to uppercase

const char POUND = 156; // The char POUND is assigned the ASCII code of 156 which is the pound sign.

int isItemExists(char itemPrefix, char itemPrefixes[]) //isItemExists begins here.
{
	for (int i = 0; i < 5; i++)
	{
		if (itemPrefix == itemPrefixes[i]) // We check if itemPrefix is already in itemPrefixes.
		{
			printf("Error: Item already  exists!\n"); // If the prefix already exists in the array, it asks the shopkeeper to enter another prefix.
			return i;
		}
	}
	return -1; // If the shopkeeper has entered a new prefix it returns the value -1;
} //isItemExists ends here.

int getItemPrice(char itemPurchased, char itemPrefixes[], int itemPrices[]) // getItemPrice begins here.
{
	for (int i = 0; i < 5; i++)
	{
		if (itemPurchased == itemPrefixes[i]) // Checks, if itemPurchased exists in itemPrefixes array.
		{
			return itemPrices[i]; // If the item exists, it returns the corresponding price of the item.
		}
	}
		return -1; // Otherwise it returns -1;
} //getItemPrice ends here.

void displayMenu(char itemPrefixes[], int itemPrices[], int n) // displayMenu begins here.
{
	printf("\n***** Shop Menu *****\n");
	printf("Item:  Price\n");
																	
	for (int i = 0; i < n; i++) // Depending on how many items were added to the menu, it will print out the corresponding amount of items.
	{																
		printf("%c: %c%i\n",itemPrefixes[i], POUND, itemPrices[i]); // first prints the prefix, then the pound sign and finally the price of the item.																												
	}															
} // displayMenu ends here.

int withinBudget(int budget, char itemPurchased, char itemPrefixes[], int itemPrices[]) //withinBudget begins here.
{
	int price = 0;
	price = getItemPrice(itemPurchased, itemPrefixes, itemPrices); // we assign the value of price to be the array of itemPrices.

	if (budget < price || price == -1) // Checks if the customer's budget is lower than the fruit chosen.
	{
		return 0; // The customer does not have enough money, thus returning the value 0.
	}

	else
	{
		return 1; // If the customer has enought money, it returns the value 1.
	}
} //withinBudget ends here

int purchaseItem(int budget, char itemPurchased, char itemPrefixes[], int itemPrices[]) // purchaseItem begins here.
{
	int price = 0;
	price = getItemPrice(itemPurchased, itemPrefixes, itemPrices); // we assign the value of price to be the array of itemPrices, just like before.

	if (withinBudget(budget, itemPurchased, itemPrefixes, itemPrices) == 1) // We check if the returned value of withinBudget is one, meaning that the customer has enough money.
	{
		printf("\nPURCHASE SUCCESS!\n");								

		printf("\nPurchase details\n");
		printf("-----------------\n");
		printf("Item: %c\n", itemPurchased); // We print the item chosen by the customer.
		printf("Price: %c%i\n", POUND, price); // We print the corresponding price of the item chosen.
		printf("Remaining budget: %c%i\n", POUND, budget - price); // We print the remaining budget of the customer.

		return budget - price; // We return the remaining budget back to the customer.
	}
	else
	{
		printf("PURCHASE FAILED!\n");
		printf("Low budget or missing item.\n");

		return budget; // The purchase was unsuccessful, because of a missing item or low budget, so we return the customer's budget back to them.
	}
} // purchaseItem ends here.

int main()
{
	printf("*** ItemPrefixes ***\n");

	const char NAMES[5][20] = { "Apple", "Orange", "Mango", "Pear", "Grapes"}; // We declare the full names of the fruit.
	for (int i = 0; i < 5; i++)
	{
		printf("%c: %s\n", NAMES[i][0], NAMES[i]); // First we print out the first character of the array NAMES, and then the full name of each fruit.
	}

	printf("******************\n\n");


	printf("*** SHOPEKEEPER PANEL ***\n");

	int amount = 0; 
	int itemPrices[5] = { 0, 0, 0, 0, 0 }; // The array of size five, will hold the prices of the fruit.
	char itemPrefixes[5]; // The array of size five, which will hold the prefixes added to the menu.
	printf("How many fruit items do you want to add to the shop:");
	scanf_s("%i", &amount); // We assign how many fruit the shopkeeper would like to add to his menu.

	char shopInput = 0;
	for (int i = 0; i < amount; i++) // Depending on how many fruit we chose to add, it will ask the shopkeeper n amount of times.
	{
		int duplicate = 1;
		while (duplicate) // A while which will not stop, unless a non duplicate prefix has been entered.
		{
			printf("\n(%i) enter item prefix:", i + 1);
			scanf_s(" %c", &shopInput, 1); // We ask for the shopkeeper which fruit he would like to add to his shop.

			shopInput = toupper(shopInput); // If the shopkeeper has entered a lowecase prefix, we convert it to an uppercase.

			if (isItemExists(shopInput, itemPrefixes) == -1) // If isItemExists returns a value of -1, we know that the item is not already in the list.
			{
				printf("Enter item (%c) price: %c", shopInput, POUND);
				scanf_s("%i", &itemPrices[i]); // The shopkeeper is asked to enter the price of the prefix chosen.
				itemPrefixes[i] = shopInput;
				duplicate = 0; // duplicate turns out to be false.
			}

			else
			{
				duplicate = 1; // The prefix chosen was a duplicate.
			}
		}
	}

	displayMenu(itemPrefixes, itemPrices, amount); // We call the function displayMenu, which will print out the menu items chosen by the shopkeeper.

	int budget = 0;
	printf("\n\n*** CUSTOMER PANEL ***\n");
	printf("Please enter your budget: %c", POUND);
	scanf_s("%i", &budget); // The customer enters their budget.

	char cstmrc = 0;
	char cont = 'y';
	while (cont == 'y') // A while loop which "automatically starts since we have assigned the var cont to always be the character 'y'.
	{
		printf("\nPlease enter Item Prefix from the Menu to purchase:");
		scanf_s(" %c", &cstmrc, 1); // The customer is asked to choose an item from the menu.

		cstmrc = toupper(cstmrc); // If the customer has entered a lowercase prefix, we convert it to an uppercase prefix.

		budget = purchaseItem(budget, cstmrc, itemPrefixes, itemPrices); // Budget is assigned to purchaseItem so that it checks whether the budget is greater or lower to the fruit chosen.

		printf("\nWhould you like to continue shopping? y/n:");
		scanf_s(" %c", &cont, 1); // The customer is asked whether they would like to continue shopping, and must enter either the character 'y' to continue or 'n' to stop.

		if (cont == 'n') // If the character 'n' is entered the loop breaks, and thanks the customer.
		{
			printf("\nThanks for shopping with us!\n");
		}
	}
	return 0;
}
