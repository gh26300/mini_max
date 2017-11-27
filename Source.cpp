#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <stack>
using namespace std;
int **arr; // 0 for order // 1 for data  // 2 for father's order
int  mini_max(int node_order, int depth, int player_status);
int tree_nodes, final_layer;
int arr_size = 0;

int main(){
	std::stack <int*> unvisited; //put order
	int layer_counter = 1;
	//int **arr; // 0 for order // 1 for data  // 2 for father's order
	int layer_nodes = 1;
	int nodes_count = 0;
	int size_count[10]; //for dfs count
	//sample input
	int num[40] = {1,3,5,1,6,9,13,15,23,2,4,-1,3,-5,-9,3,4,3,6,4,2,5,3,4,2,0,-1,3,1,7,10,-7,6,-3,6,5,-1,-2,3,4};
	cout << "tree_nodes ";
	cin >> tree_nodes;
	cout << "final layer ";
	cin >> final_layer;
	for (int i = 0; i < final_layer; i++){  // calc the total value
		arr_size += std::pow(tree_nodes,i);
		size_count[i] = arr_size;
	}
	arr = new int *[arr_size];    // 0 for order // 1 for data  // 2 for father's order  //3 current layer //4-? for child
	for (int i = 0; i < arr_size; i++){
		arr[i] = new int [4 + tree_nodes];
		arr[i][0] = i + 1;
	}
	int layer_flag = 1;
	arr[0][2] = 0 ; //first fathers_order
	int flag = 2 ;
	for (int i = 1; i <= arr_size; i++){ //bulid  tree nodes & set the value 
		for (int j = 0; j < tree_nodes; j++){
			if (flag <= arr_size){         //avoid the leaves set child node
				arr[i - 1][4 + j] = flag;  //set the child
				arr[flag-1][2] = i ;       //set the father  會拖慢速度
				flag++;
			}
			else{
				arr[i - 1][4 + j] = NULL;
			}
		}
		arr[i - 1][1] = num[i - 1];
		arr[i - 1][3] = layer_counter;
		if (i==layer_flag){
			layer_counter++;
			layer_flag += pow(tree_nodes, layer_counter-1);
		}
	}


	/********                      DFS               ****************************/
	int layer = final_layer;
	int minimax_flag;
	//** ＤＦＳ  / mini max
		cout << "DFS order" << endl;
		int *current_order;
		unvisited.push(&arr[0][0]);
		while (!unvisited.empty()){  //DFS 
			current_order = unvisited.top();
			unvisited.pop();
			if (arr[*current_order - 1][4] != NULL){ //由於設立時於1開始，因此需減1配合正確順位  && 控制DFS深度
				for (int i = 0; i < tree_nodes; i++){
					unvisited.push(&arr[*current_order - 1][(4 + (tree_nodes - 1) - i)]);  //由右至左填入child order
				}
			}
			cout << "current order : " << *current_order << endl;
		}
		/*/******************************************************************************/
		//show layer data
		layer_nodes = 1;
		nodes_count = 0;
		layer_counter = 1;
		for (int i = 1; i <= arr_size; i++){ // order
			cout << setw(3) << arr[i - 1][1];
			nodes_count++;
			if (nodes_count == layer_nodes){
				layer_nodes *= tree_nodes;
				nodes_count = 0;
				cout << endl;
			}
		}

		cout <<"result "<< mini_max(1, 1, 1) << endl;


	//show layer data
	layer_nodes = 1;
	nodes_count = 0;
	layer_counter = 1;
	for (int i = 1; i <= arr_size; i++){ // order
		cout << setw(3) << arr[i - 1][1];
		nodes_count++;
		if (nodes_count == layer_nodes){
			layer_nodes *= tree_nodes;
			nodes_count = 0;
			cout << endl;
		}
	}

	system("pause");
}

int mini_max(int node_order, int depth, int player_status){
	if (depth == 4 || arr[node_order-1][4] == NULL){
		return arr[node_order-1][1];
	}
	if (player_status == 1){
		int value = -999;
		for (int i = 0; i < tree_nodes; i++){  //search all child node
			int v = mini_max(arr[node_order - 1][4 + i], depth + 1, 0);
				if (v>value) {
					value = v;
					arr[node_order - 1][1] = value;
				}
		}

		return value;
	}
	else if (player_status == 0){
		int value = 999 ;
		for (int i = 0; i < tree_nodes; i++){  //search all child node
			int v = mini_max(arr[node_order - 1][4 + i], depth + 1, 1);
			if (v<value) {
				value = v;
				arr[node_order - 1][1] = value;
			}
		}
		return value;
	}
}
