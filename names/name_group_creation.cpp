#include <iostream>
#include <stdlib.h> //random num
#include <vector>
#include <fstream> //files :3

#include <algorithm> //for the shuffle to shuffle the names 
#include <random> //required for the shuffle algorithm imported above
using namespace std;



//TODO:
//NICE TO HAVES:
    //2) create an output table. top is group #, left is 'names'. columns are what names are in group X. 

int main (void)
{

    //Opening the file, getting the names into memory and closing the file

    ifstream name_file ("names.txt"); //open the txt file containing all the names 
    
    vector <string> names;

    string current_name; //variable to allow names from file to be put into memory 

    while (getline (name_file, current_name))
    {
        names.push_back(current_name); 
    }
    
    name_file.close();

    
    //DEBUG: verifying lines were read in right - It works :3

/*
    for (auto output_name : names)
    {
        cout << output_name << endl;
    }
*/


    //setting up practically everything not related to names directly
    srand(time(NULL)); //setting up pseudo random seed
                       
    int max_groups, total_students, extra_students, rand_assignment, students_per_group;

    int student_counter = 0; //keep track how many students assigned to a group

    //double students_per_group;

    vector <int> group_nums; //vectors my beloved <3 (don't know how many groups are wanted so can't create an array so use a vector instead)
            
    vector <vector <string>> final_groups; //vector that is ordered by groups that contains the names of all people belonging to that group
    string temp_name_storage; //string to hold names[current_student] to prevent array errors

    cout << "How many groups do you want: ";
    cin >> max_groups;

    total_students = names.size();


    students_per_group = total_students / max_groups;
    extra_students = total_students % max_groups; //if the total students not a multiple of max groups then we have 'extra' students that need to join a group 



    //shuffling the names vector to potentially avoid bias
    random_device rd; //seed 
    mt19937 g(rd()); //creates a mt19937 number generator using rd as the seed 
    shuffle(names.begin(), names.end(), g); //actually shuffle the names 
    
    //DEBUG - testing shuffle worked
/*
    for (auto output_name : names)
    {
        cout << output_name << endl;
    }
*/


    //NOTE: setting total_students to only include non-'left over' students as those are added last
    total_students = total_students - extra_students; 
    

    cout << "Students per group: " << students_per_group << endl;
    cout << "There are " << extra_students << " students that are left over that need to join another group to create " << extra_students << " groups of " << students_per_group + 1 << endl;


    //creates a vector max_groups long to keep track of how students per group there are
    for (int i = 0; i < max_groups; i++)
    {
        group_nums.push_back(0);
    }

    
    //resizing final_groups to be the same size as max_groups to prevent seg fault, it took me so long to figure this out... (thanks GPT)
    final_groups.resize(max_groups);


    //whitespace to make reading easier
    cout << "\n\n";

    //NOTE: Theoretically this can create an infinite loop if we get really, *really* unluckly. like impossibly unlucky. if this happens play the lottery
    while (student_counter < total_students)
    {
        rand_assignment = rand() % max_groups; //randomly assign student student_counter to a group 
                                                   
        if (group_nums[rand_assignment] < students_per_group) // check that the group number assigned isn't already at max students before extra 
        {
            group_nums[rand_assignment]++;
            cout << names[student_counter] << " has been assigned to group " << rand_assignment + 1 << endl;
           
            //NEXT LINE IS NEW CODE, IF IT BREAKS COMMENT THIS            
            //temp_name_storage just makes things easier instead of having to type out names[student_counter] every time, makes things less confusing IMO
            temp_name_storage = names[student_counter];
            

            //debug to test that temp_storage is fine
            //cout << "Temp name storage has value : " << temp_name_storage << endl << endl;


            //NOTE: THIS DOES NOT WORK
            final_groups[rand_assignment].push_back(temp_name_storage);

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
            cout << names[student_counter] << " has been assigned to group " << rand_assignment + 1 << endl;
            
            //cout << "This student has been assigned to group " << rand_assignment + 1 << endl;
          
            //NEW CODE COMMENT OUT IF BROKEN
            temp_name_storage = names[student_counter];
            
            //debug to make sure temp_name_storage is fineeeee
            //cout << "Temp name storage has name : " << temp_name_storage << endl << endl;
            final_groups[rand_assignment].push_back(temp_name_storage);

            
            student_counter++;

            extra_students--; //an extra student got put into a group so we can subtract one. can probably just be done with student_counter but eh
        }
    }
    


    cout << "\n\nNumber of students per group:\n";
    for (int i = 0; i < max_groups; i++)
    {
        cout << "Group " << i + 1 << " has a total of " << group_nums[i] << " students " << endl;
    }


    //more whitespace for better looking 
    cout << "\n\n";

    for (int i = 0; i < max_groups; i++)
    {
        cout << "Group " << i+1 << " Members:\n";
        for (auto group_members : final_groups[i])
        {
            cout << group_members << endl;
        }


        cout << "\n\n";
    }
    

    return 0;

}
