/**
 * @file Llist.h
 * @class Llist
 * @author Michael
 * @brief a linked list which holds nodes of open positions a piece may move to
 */
#ifndef LLIST_H
#define LLIST_H
#include <vector>
/**
* @brief a struct which carries x and y co-ords and a pointer to the next XYcoords node
* 
*/
struct XYcoords
{

    /**
    * @brief the x co-ord
    * 
    */
    int x;

    /**
    * @brief the y co-ord
    * 
    */
    int y;

    /**
    * @brief a pointer to the next XYcoords node
    * 
    */
    struct XYcoords* next;
};

struct XYpos 
{
    int x;
    int y;
};

class Llist
{
    private:

        /**
        * @brief a pointer to the head node of the list
        * 
        */
        XYcoords* head;

        /**
        * @brief the current size of the list
        * 
        */
        int listSize;
    public:

        /**
        * @brief Llist constructor initialises the head pointer to NULL
        * @param none
        * 
        */
        Llist();

        /**
        * @brief Llist deconstructor destroys the list if it exists
        * 
        */
        ~Llist();

        /**
        * @brief returns the size of the list at the current moment
        * @param none
        * 
        * @return int
        */
        int size();

        /**
        * @brief returns a pointer to the head of the list
        * @param none
        * 
        * @return XYcoords*
        */
        XYcoords* gethead();

        /**
        * @brief clears all the nodes in the list iteratively
        * @param none
        * 
        * @return void
        */
        void clearList();

        /**
        * @brief clears all the nodes in the list recursively
        * @param currentNode a pointer to the current node being deleted
        * 
        * @return void
        */
        void clearList(XYcoords* currentNode);

        /**
        * @brief appends the passed in parameter to the back of the list iteratively
        * @param newData a struct created and initialised before being passed in as a parameter
        * 
        * @return void
        */
        void push_back(XYcoords newData);

        /**
        * @brief appends the passed in parameter to the back of the list recursively
        * @param newData a struct created and initialised before being passed in as a parameter
        * @param currentNode a pointer to the current node being used for traversal
        * 
        * @return void
        */
        void push_back(XYcoords newData, XYcoords* currentNode);

        /**
        * @brief returns a vector of struct objects containing open positions
        * @param none
        * 
        * @return std::vector<XYpos>
        */
        std::vector<XYpos> getOpenPositionsVec();
};

#endif