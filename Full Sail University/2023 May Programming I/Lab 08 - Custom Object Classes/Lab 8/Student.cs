using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_8A
{
    public class Student
    {
        // Add member fields here
        private string last;
        private string first;
        private int idNo;

        // Add default and overloaded constructors here
        public Student()
        {
            this.last = "";
            this.first = "";
            this.idNo = 1000000;
        }

        public Student(string last, string first, int idNo)
        {
            this.last = last;
            this.first = first;
            this.idNo = idNo;
        }

        // add Getters and Setters here
        public string GetFirstName()
        {
            return this.first;
        }

        // Setter for the first name
        public void SetFirstName(string first)
        {
            this.first = first;
        }

        // Getter for the last name
        public string GetLastName()
        {
            return this.last;
        }

        // Setter for the last name
        public void SetLastName(string last)
        {
            this.last = last;
        }

        // Getter for the ID number
        public int GetIDNumber()
        {
            return this.idNo;
        }

        // Setter for the ID number
        public void SetIDNumber(int idNo)
        {
            this.idNo = idNo;
        }





















        /******************************************************************************************************
        *                                                                                                     *
        *                                                                                                     *
        *                                                                                                     *
        *                                                                                                     *
        *                      do not modify any of the following code                                        *
        *                                                                                                     *
        *                                                                                                     *
        *                                                                                                     *
        *                                                                                                     *
        *                                                                                                     *
        ******************************************************************************************************/
        public override string ToString()
        {
            return "ID #: " + GetIDNumber() + "\tName: " + GetLastName() + ", " + GetFirstName();
        }

        public override bool Equals(object obj)
        {
            bool same = true;
            Student s2 = (Student)obj;
            if (this.GetLastName() != s2.GetLastName() || this.GetFirstName() != s2.GetFirstName() || this.GetIDNumber() != s2.GetIDNumber())
            {
                same = false;
            }
            return same;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
