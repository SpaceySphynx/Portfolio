using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_8A
{
    /*
     * Complete the Student class before attempting to complete any of Tests
     * 
     * Notes:
     * 
     * - Identifiers (method names and variables) are case sensitive. For example,
     *   SetIdNumber is not the same as SetIDNumber. If a specific name is provided, 
     *   you must use the exact name provided.
     * - For Tests 4 and 5, before attempting to access a Student class method from 
     *   an array element, you must ensure the array element contains a Student 
     *   object. If the element is null and you attempt to call a member method, the 
     *   program will throw an Exception and crash. To verify the element is not 
     *   empty, compare the element to null – if the element is not null, then it 
     *   contains a valid Student object.
     */

    public class Submission
    {
        public static Student[] enrollment = new Student[0];

        // Student object with the provided parameters
        public static Student Test1(string last, string first, int idNo)
        {
            // Return Student object
            return new Student(last, first, idNo);
        }

        public static Student Test2()
        {
            // Just returned Student() to get new Student object
            return new Student();
        }

        public static bool Test3(Student enrolled)
        {
            // for loop to go the whole length of the array
            for (int i = 0; i < enrollment.Length; i++)
            {
                // If the current element is null empty
                if (enrollment[i] == null)
                {
                    // Place the enrolled student in the empty slot and return true
                    enrollment[i] = enrolled;
                    return true;
                }
            }

            // If no empty slot then return false
            return false;
        }

        public static bool Test4(int idNumber)
        {
            // for loop to go the whole length of the array
            for (int i = 0; i < enrollment.Length; i++)
            {
                // If the current student is not null and their ID matches the given idNumber
                if (enrollment[i] != null && enrollment[i].GetIDNumber() == idNumber)
                {
                    // Set to null and return true
                    enrollment[i] = null;
                    return true;
                }
            }

            // If no student with the inputted ID was found, return false
            return false;
        }

        public static Student Test5(int idNumber)
        {
            // for loop to go the whole length of the array
            for (int i = 0; i < enrollment.Length; i++)
            {
                // If the current student is not null and their ID matches the given idNumber
                if (enrollment[i] != null && enrollment[i].GetIDNumber() == idNumber)
                {
                    // Return the student
                    return enrollment[i];
                }
            }

            // If no student with the given ID was found, return null
            return null;
        }
    }
}
