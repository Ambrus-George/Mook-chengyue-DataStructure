#include <iostream>
#include <vector>

using namespace std;

typedef int ElementType;

void Input_connection(vector<ElementType>& D);
void Check_connection(vector<ElementType>& D);
void Check_network(vector<ElementType>& D);
int FindRoot(vector<ElementType>& D, ElementType tmp);
void UnionTrees(vector<ElementType>& D, int r1, int r2);

int main()
{
    int N = 0;
    char w;

    cin >> N;
    
    //initialize the Group which save data
    vector<ElementType> Data(N+1, -1);

    //read the input until w == 'S'
    do
    {
        cin >> w;
        /* check the w */
        switch (w){
            case 'I': Input_connection(Data);   break;      
            case 'C': Check_connection(Data);   break;      
            case 'S': Check_network(Data);      break;
        }

    } while (w != 'S');
    

    return 0;
}

void Input_connection(vector<ElementType>& D){
    //read two elements and build the connection
    ElementType e1, e2;
    cin >> e1 >> e2;

    //Find two roots
    int root1, root2;
    root1 = FindRoot(D, e1);
    root2 = FindRoot(D, e2);

    //union two trees
    UnionTrees(D, root1, root2);
}

void Check_connection(vector<ElementType>& D){
    ElementType e1, e2;
    cin >> e1 >> e2;

    int root1 = FindRoot(D, e1);
    int root2 = FindRoot(D, e2);

    if (root1 == root2)     cout << "yes" << endl;
    else                    cout << "no"  << endl;
    
}

void Check_network(vector<ElementType>& D){
    int length = D.size();

    int count = 0;
    for (int i = 1; i < length; i++)
    {
        if (D[i] < 0)   count++;
    }

    if (count == 1){
        cout << "The network is connected." << endl;    
        return;
    }    

    cout << "There are " << count << " components.";
}

int FindRoot(vector<ElementType>& D, ElementType tmp){
    if (D[tmp] < 0)
        return tmp;
    else
        return D[tmp] = FindRoot(D, D[tmp]);

}

void UnionTrees(vector<ElementType>& D, int r1, int r2){
    if (D[r1] < D[r2])
    {
        /* Tree 1 is the bigger tree */
        D[r1] += D[r2];
        D[r2] = r1;
    }else{
        /* Tree 2 is the bigger tree */
        D[r2] += D[r1];
        D[r1] = r2;
    }
    
}