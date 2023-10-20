//=============================================================================
// Program's Item class
//=============================================================================

namespace Shop
{
    //       Write a class called Item that contains 2 data members:
    //       A string called name and an int called cost.
    //       This class should have a default constructor that sets name to ""
    //       and cost to 0.
    //       It should also have an overloaded constructor that accepts 2
    //       parameters - a string and an int.
    //
    //       Write getters/accessors for each data member. They should be called
    //       GetName and GetCost.
    //
    //       Write setters/mutators for each data member. They should be called
    //       SetName and SetCost.
    
    // Item Class
    public class Item
    {
        // 2 data members string name and int cost.
        private string name;
        private int cost;

        // Default constructors set to default values of "" and 0.
        public Item()
        {
            this.name = "";
            this.cost = 0;
        }

        // Overload constructor set to the two values
        public Item(string name, int cost)
        {
            this.name = name;
            this.cost = cost;
        }

        // Getter name
        public string GetName()
        {
            return this.name;
        }

        // Setter name
        public void SetName(string name)
        {
            this.name = name;
        }

        // Getter Cost
        public int GetCost()
        {
            return this.cost;
        }

        // Setter Cost
        public void SetCost(int cost)
        {
            this.cost = cost;
        }

    }

}
