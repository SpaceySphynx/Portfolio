using PG2Input;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WarGame
{
    public class CardWars
    {

        static Random rando = new Random();
        static List<string> Shuffle(List<string> cards)
        {
            return cards.OrderBy(x => rando.Next()).ToList();
        }


        // Created the List LoadCards passing the filePath.
        public static List<string> LoadCards(string filePath)
        {
            // Empty variable cards = set to new string List for storage;
            var cards = new List<string>();
            // use the StreamReader on the filePath.
            using (var reader = new StreamReader(filePath))
            {
                // Read the file from beginning to end.
                var line = reader.ReadToEnd();
                // Split the conent into an Array using the ; as the split.
                var cardArray = line.Split(';');
                // Convert from Array to List.
                cards = cardArray.ToList();
            }
            // return the List to the cards variable.
            return cards;
        }

        private static int CompareCards(string card1, string card2)
        {
            int pValue = GetCardValue(card1);
            int cValue = GetCardValue(card2);
            if (pValue > cValue)
                return 1;//player wins
            else if (pValue < cValue)
                return -1;//npc wins 

            return 0;
        }

        private static int GetCardValue(string card)
        {
            int value;
            if (card.Length == 3) //10 card
                value = 10;
            else
            {
                string face = card[0].ToString();
                if (face == "A")
                    value = 1;
                else if (face == "J")
                    value = 11;
                else if (face == "Q")
                    value = 12;
                else if (face == "K")
                    value = 13;
                else
                    value = int.Parse(face);
            }

            return value;
        }

        // Created a public static void PlayGame Method taking in
        // String List cards, highScores List HighScore, and string file highScorefile.
        public static void PlayGame(List<string> cards, List<HighScore> highScores, string highScoreFile)
        {
            // The instructions for this next section were very detailed so going to use them for comments.
            // 1. Call shuffle passing in the list of cards.
            List<string> shuffledCards = Shuffle(cards);

            // 2. Take the shuffled list and split it into 2 equal lists: playerCards and npcCards.
            List<string> playerCards = shuffledCards.Take(shuffledCards.Count / 2).ToList();
            List<string> npcCards = shuffledCards.Skip(shuffledCards.Count / 2).ToList();

            // 3. Create 3 lists: playerPile, npcPile, unclaimedPile.
            List<string> playerPile = new List<string>();
            List<string> npcPile = new List<string>();
            List<string> unclaimedPile = new List<string>();

            // 4. Loop while the playerCards list is not empty.
            while (playerCards.Count > 0)
            {
                // a. Print out the first card from playerCards and npcCards. Added PadLeft to match formatting.
                Console.Write($"{playerCards[0].PadLeft(3)} vs {npcCards[0].PadLeft(3)}");

                // b. Add the first card from playerCards and npcCards to the unclaimed pile.
                unclaimedPile.Add(playerCards[0]);
                unclaimedPile.Add(npcCards[0]);

                // c. Call CompareCards and pass the first card from the playerCards and npcCards.
                int compareResult = CompareCards(playerCards[0], npcCards[0]);

                // d. If CompareCards returns -1, add the unclaimed pile to the npcPile. Clear the unclaimed pile. Print NPC wins.
                if (compareResult == -1)
                {
                    npcPile.AddRange(unclaimedPile);
                    unclaimedPile.Clear();
                    Console.WriteLine("   NPC wins");
                }
                // I added this even though it wasn't in the instructions so I could match the format of the video and clear piles for ties.
                if (compareResult == 0)
                {
                    unclaimedPile.Clear();
                    Console.WriteLine(" ");
                }

                // e. If CompareCards returns 1, add the unclaimed pile to the playerPile. Clear the unclaimed pile. Print player wins.
                else if (compareResult == 1)
                {
                    playerPile.AddRange(unclaimedPile);
                    unclaimedPile.Clear();
                    Console.WriteLine("   player wins");
                }

                // f. Remove the first card from the playerCards and npcCards.
                playerCards.RemoveAt(0);
                npcCards.RemoveAt(0);
            }

            // 5. After the loop, check who won. Print the counts from the playerPile and npcPile lists.
            // a. If the npcPile has more cards, print that the npc won the round.
            if (npcPile.Count > playerPile.Count)
            {
                Console.WriteLine($"NPC wins! {npcPile.Count} vs {playerPile.Count}");
            }
            // b. If the npcPile has the same number of cards as the playerPile, print that it was a tie.
            else if (npcPile.Count == playerPile.Count)
            {
                Console.WriteLine("TIE!");
            }
            // c. Else, the playerPile has more cards.
            else
            {
                Console.WriteLine($"Player wins! {playerPile.Count} vs {npcPile.Count}");

                // Check if it’s a new high score.
                // i. NOTE: the last score in the high score list is the smallest high score. 
                if (playerPile.Count > highScores.Last().Score)
                {
                    // ii. If the player’s score is a new high score,
                    // 1. Get the user’s name using Input.GetString.
                    string playerName = "";
                    Input.GetString("NEW HIGH SCORE! What is your name? ", ref playerName);

                    // 2. loop from the beginning of the high score list.
                    for (int i = 0; i < highScores.Count; i++)
                    {
                        // 3. If the player score is >= the high score in the list, then 
                        if (playerPile.Count >= highScores[i].Score)
                        {
                            // a. insert a new high score object into the list at that index.
                            HighScore newScore = new HighScore(playerName, playerPile.Count);
                            highScores.Insert(i, newScore);

                            // b. remove the last score in the list.
                            highScores.RemoveAt(highScores.Count - 1);

                            // c. call SaveHighScores (see part A-3).
                            HighScore.SaveHighScores(highScoreFile, highScores);

                            // d. Call ShowHighScores to display the new top 10.
                            HighScore.ShowHighScores(highScores);
                            // exit if statement.
                            break;
                        }
                    }
                }
            }
        }
    }
}
