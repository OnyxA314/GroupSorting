#include <iostream>
#include <stdlib.h> //random num
#include <vector>
using namespace std;



//TODO:
//NICE TO HAVES:
    //1) read in a txt file of student names and shuffle that so instead of saying "this student was assigned to group X" it reads "*name* has been assigned to group X"
    //2) create an output table. top is group #, left is 'names'. columns are what names are in group X. 

int main (void)
{

    srand(time(NULL)); //setting up pseudo random seed
                       
    int max_groups, total_students, extra_students, rand_assignment, students_per_group;

    int student_counter = 0; //keep track how many students assigned to a group

    //double students_per_group;

    vector <int> group_nums; //vectors my beloved <3 (don't know how many groups are wanted so can't create an array so use a vector instead)

    cout << "How many groups do you want: ";
    cin >> max_groups;

    cout << "How students do you have: ";
    cin >> total_students;



    students_per_group = total_students / max_groups;
    extra_students = total_students % max_groups; //if the total students not a multiple of max groups then we have 'extra' students that need to join a group 


    //NOTE: setting total_students to only include non-'left over' students as those are added last
    total_students = total_students - extra_students; 
    

    cout << "Students per group: " << students_per_group << endl;
    cout << "There are " << extra_students << " students that are left over that need to join another group to create " << extra_students << " groups of " << students_per_group + 1 << endl;


    //creates a vector max_groups long to keep track of how students per group there are
    for (int i = 0; i < max_groups; i++)
    {
        group_nums.push_back(0); 
    }


    //NOTE: Theoretically this can create an infinite loop if we get really, *really* unluckly. like impossibly unlucky. if this happens play the lottery
    while (student_counter < total_students)
    {
        rand_assignment = rand() % max_groups; //randomly assign student student_counter to a group 
                                                   
        if (group_nums[rand_assignment] < students_per_group) // check that the group number assigned isn't already at max students before extra 
        {
            group_nums[rand_assignment]++;
            cout << "This student has been assigned to group " << rand_assignment + 1 << endl;
            student_counter++;
        }
    }


    //NOTE: see above note
    //if there is extra students do the following loop until there is none 
    while (extra_students != 0)
    {
        rand_assignment = rand() % max_groups; //assign student to a new group 
                                               
        if (group_nums[rand_assignment] < students_per_group + 1) //extra studnts means each group gets a maximum of 1 extra
        {
            group_nums[rand_assignment]++;
            cout << "This student has been assigned to group " << rand_assignment + 1 << endl;

            extra_students--; //an extra student got put into a group so we can subtract one
        }
    }
    

    for (int i = 0; i < max_groups; i++)
    {
        cout << "Group " << i + 1 << " has a total of " << group_nums[i] << " students " << endl;
    }
    

    return 0;

}
