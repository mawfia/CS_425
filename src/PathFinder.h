#pragma once
#include "Component.h"
#include "EntityComponentSystem.h"
using namespace std;



namespace engine {


	class PathFinder {

	public:
		//2D array of nodes to act as adjacency matrix
		// each [x][y] is a node and its neighbors are all the adjacent positions
		//Node* gamePlane[801][801];
		Node*** gamePlane;
		//std::vector<std::vector<Node*>> gamePlane(801,std::vector<Node*>(801));


		void initializePlane() {
			//Used to initialize game plane with position values
			gamePlane = new Node** [200];
			for (int i = 0; i < 200; i++) {
				gamePlane[i] = new Node*[200];
			}
			
			
			double posX = -100;
			double posY = 100;
			for (int x = 0; x < 200; x++) {
					posX = posX + 1;
					posY = 100;
				for (int y = 0; y < 200; y++) {
					gamePlane[x][y] = new Node();
					
					gamePlane[x][y]->position.x = (posX/100);
					gamePlane[x][y]->position.y = (posY/100);
					/*
					cout << "y POS: ";
					cout << (float)gamePlane[x][y]->position.y;
					cout << "\n";
					*/
					posY = posY - 1;
				}
			}
		}

		void findPath(Sprite seekerSprite,SpritePos goal, SpritePos seeker, EntityComponentSystem& entities) {
			Sprite sprite;
			
			//Goes through every sprite to determine goal position and position of spaces that are blocked off
			
			entities.ForEach<Sprite>([&](EntityID id) {

				sprite = entities.Get<Sprite>(id);
			if (sprite.x == seeker.x && sprite.y == seeker.y) {
				
			}

			if (sprite.position.x == goal.x && sprite.position.y == goal.y) {
				//The weird looking formula in the brackets is to translate the coordinate position to the matrix position (ex- coorinates 0,0 -> matrix position[99][99])
				gamePlane[(int)floor(99.5 * (sprite.position.x + 1))][(int)floor(-99.5 * (sprite.position.y - 1))]->isGoal = true;
				//cout << "CHECKPOINT 1 REACHED\n";
			}
			
			if ((sprite.position.x != goal.x && sprite.position.y != goal.y) || (sprite.position.x != seeker.x && sprite.position.y != seeker.y)) {
				
				gamePlane[(int)floor(99.5 * (sprite.position.x + 1))][(int)floor(-99.5 * (sprite.position.y - 1))]->isBlocked = true;
			}
			
				});
			//Sets up the heuristic and edge costs
			//cout << "CHECKPOINT 3 REACHED\n";
			for (int x = 0; x < 200; x++) {
					
				for (int y = 0; y < 200; y++) {
					
					gamePlane[x][y]->nodesFromGoal = getNumNodesFrom(x, y, (int)floor(99.5 * (goal.x + 1)), (int)floor(-99.5 * (goal.y - 1)));
					gamePlane[x][y]->goalDistance = calcDistance(gamePlane[x][y]->position, goal);
					/*
					cout << "DISTANCE FROM GOAL";
					cout << gamePlane[x][y]->goalDistance;
					cout << "\n";
					*/
				}
			}

			Node *curNode = gamePlane[(int)floor(99.5*(seeker.x+1))][(int)floor(-99.5 * (seeker.y - 1))];
			
			//Builds the path to the goal
			vector<Node*> list;
			/**
			while (curNode->position.x != goal.x ) {
				list.push_back(curNode);
				/*
				cout << "J: ";
				cout << (int)floor(99.5 * (curNode->position.x + 1)) ;
				cout << ", ";
				cout << "Y: ";
				cout << (int)floor(-99.5 * (curNode->position.y - 1));
				cout << "\n";
				
				
				curNode = findNextInPath(curNode , goal);
				

				
				
				
				curNode = gamePlane[(int)floor(99.5 * (curNode->position.x + 1))][(int)floor(-99.5 * (curNode->position.y - 1)) + 2];
				
				

			}


			
			while (curNode->position.y != goal.y ) {
				list.push_back(curNode);

				


				curNode = findNextInPath(curNode, goal);



				
				curNode = gamePlane[(int)floor(99.5 * (curNode->position.x + 1))][(int)floor(-99.5 * (curNode->position.y - 1))+4];



			}
			*/
			while (curNode->position.x != goal.x) {
				list.push_back(curNode);
				SpritePos neighbors[8];

				neighbors[0].x = curNode->position.x - 0.01;
				neighbors[0].y = curNode->position.y + 0.01;

				neighbors[1].x = curNode->position.x;
				neighbors[1].y = curNode->position.y + 0.01;

				neighbors[2].x = curNode->position.x + 0.01;
				neighbors[2].y = curNode->position.y + 0.01;

				neighbors[3].x = curNode->position.x - 0.01;
				neighbors[3].y = curNode->position.y;

				neighbors[4].x = curNode->position.x + 0.01;
				neighbors[4].y = curNode->position.y;

				neighbors[5].x = curNode->position.x - 0.01;
				neighbors[5].y = curNode->position.y - 0.01;

				neighbors[6].x = curNode->position.x;
				neighbors[6].y = curNode->position.y - 0.01;

				neighbors[7].x = curNode->position.x + 0.01;
				neighbors[7].y = curNode->position.y - 0.01;

				for (int x = 0; x < 8; x++) {

					if ((neighbors[x].x < 1 && neighbors[x].x >= -1) && (neighbors[x].y < 1 && neighbors[x].y >= -1)) {

						if ((gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))]->goalDistance + gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))]->nodesFromGoal) < (curNode->goalDistance + curNode->nodesFromGoal)) {
							curNode = gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))];




						}
					}
				}
				
			}
			cout << "Y: ";
			cout << (int)floor(-99.5 * (curNode->position.y - 1));
			cout << "\n";
			SpritePos next;
			while (curNode->position.y != goal.y) {
				list.push_back(curNode);
				
			
				if (curNode->position.y < goal.y) {
					next.y = curNode->position.y + 0.01;
					curNode = gamePlane[(int)floor(99.5 * (curNode->position.x + 1))][(int)floor(-99.5 * (next.y - 1))];
			
					
				}
				else if (curNode->position.y > goal.y) {
					next.y = curNode->position.y - 0.02;
					curNode = gamePlane[(int)floor(99.5 * (curNode->position.x + 1))][(int)floor(-99.5 * (next.y - 1))];
					cout << (int)floor(-99.5 * (next.y - 1));
					cout << "\n";
					cout << (int)floor(-99.5 * (curNode->position.y - 1));
					cout << "\n";
					
				}
				/*
				cout << "J: ";
				cout << (int)floor(99.5 * (curNode->position.x + 1));
				cout << ", ";
				cout << "Y: ";
				cout << (int)floor(-99.5 * (curNode->position.y - 1));
				cout << "\n";
				*/


			}




			list.push_back(curNode);
			
			
			//Returns node of the seeker's position and will use the nextInPath node pointer to move along the path to the goal
			
			moveToGoal(seekerSprite, list,entities);
			//cout << "Checkpoint 11 REACHED\n";
			
		}
		//Finds the next node in the path to the goal
		Node* findNextInPath(Node* node, SpritePos goal) {

			
			Node *next = NULL;
			/*
			cout << "NODE POS IS: ";
			cout << node->position.x;
			cout << " ,";
			cout << node->position.y;
			cout << "\n";
			*/
			if (node->position.x != goal.x) {
				if (node->position.x < goal.x) {

					next = gamePlane[(int)floor(99.5 * (node->position.x + 1)) + 1][(int)floor(-99.5 * (node->position.y - 1))];
					/*
					cout << "J: ";
					cout << (int)floor(99.5 * (node->position.x + 1)) + 1;
					cout << ", ";
					cout << "Y: ";
					cout << (int)floor(-99.5 * (node->position.y - 1));
					cout << "\n";
					*/

					return next;
				}
				else if(node->position.x > goal.x) {
					next = gamePlane[(int)floor(99.5 * (node->position.x + 1))-1][(int)floor(-99.5 * (node->position.y - 1))];
					/*
					cout << "J: ";
					cout << (int)floor(99.5 * (node->position.x + 1)) + 1;
					cout << ", ";
					cout << "Y: ";
					cout << (int)floor(-99.5 * (node->position.y - 1));
					cout << "\n";
					*/

					return next;
				}
			}
			else {
				
				if (node->position.y < goal.y) {

					next = gamePlane[(int)floor(99.5 * (node->position.x + 1))][(int)floor(-99.5 * (node->position.y - 1))+1];
					/*
					cout << "J: ";
					cout << (int)floor(99.5 * (node->position.x + 1)) + 1;
					cout << ", ";
					cout << "Y: ";
					cout << (int)floor(-99.5 * (node->position.y - 1));
					cout << "\n";
					*/

					return next;
				}
				else if(node->position.y > goal.y) {
				
					next = gamePlane[(int)floor(99.5 * (node->position.x + 1))][(int)floor(-99.5 * (node->position.y - 1))-1];
					/*
					cout << "J: ";
					cout << (int)floor(99.5 * (node->position.x + 1)) + 1;
					cout << ", ";
					cout << "Y: ";
					cout << (int)floor(-99.5 * (node->position.y - 1));
					cout << "\n";
					*/

					return next;
				}

			}

			/*
			SpritePos neighbors[8];
			
			neighbors[0].x = node->position.x - 0.01;
			neighbors[0].y = node->position.y + 0.01;
			
			neighbors[1].x = node->position.x;
			neighbors[1].y = node->position.y + 0.01;

			neighbors[2].x = node->position.x + 0.01;
			neighbors[2].y = node->position.y + 0.01;

			neighbors[3].x = node->position.x - 0.01;
			neighbors[3].y = node->position.y;

			neighbors[4].x = node->position.x + 0.01;
			neighbors[4].y = node->position.y;

			neighbors[5].x = node->position.x - 0.01;
			neighbors[5].y = node->position.y - 0.01;

			neighbors[6].x = node->position.x;
			neighbors[6].y = node->position.y - 0.01;

			neighbors[7].x = node->position.x + 0.01;
			neighbors[7].y = node->position.y - 0.01;
			
			for (int x = 0; x < 8; x++) {
				
				if ((neighbors[x].x < 1 && neighbors[x].x >= -1) && (neighbors[x].y < 1 && neighbors[x].y >= -1)) {
					
					if (next == NULL) {
						next = gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))];
						
					}
					
					if ((gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))]->goalDistance   + gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))]->nodesFromGoal) <= (next->goalDistance  + next->nodesFromGoal)) {
						next = gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))];
						/*
						cout << "X VALUE IS: ";
						cout << x;
						cout << "\n";
						
						
						cout << "THE HUERISTIC VALUE IS: ";
						cout <<  next->goalDistance;
						cout << "\n";
						*/
						/*
						cout << "THE X POS IS";
						cout << next->position.x;
						cout << "\n";
						
						
						
					}
				}
			}
			*/
			//cout << "CHECKPOINT 7 REACHED\n";
			/*
			cout << "NEXT X POS: ";
			cout << next->position.x;
			cout << ", NEXT Y POS: ";
			cout << next->position.y;
			cout << "\n";
			*/
		
			return next;
		}

		//This function moves the sprite along the path generated from findPath
		void moveToGoal(Sprite seekerSprite, vector<Node*> list, EntityComponentSystem& entities) {
			
			
			
			 for(Node* nextInPath : list) {
				//seekerSprite.x = nextInPath->position.x;
			//	seekerSprite.y = nextInPath->position.y;
				 for (double x=0; x <= nextInPath->position.x; x = x + 0.00000001) {
					
					 entities.Get<Sprite>(5).x = nextInPath->position.x;

				 }
				 for (double y=0; y <= nextInPath->position.y; y = y + 0.0001) {
					 entities.Get<Sprite>(5).y = nextInPath->position.y;

				 }
				//entities.Get<Sprite>(5).x = nextInPath->position.x;
				//entities.Get<Sprite>(5).y = nextInPath->position.y;
				
				cout << "X Pos: ";
				cout << nextInPath->position.x;
				cout << " Y Pos: ";
				cout << nextInPath->position.y;
				cout << "\n";
				
				
				
			}
			
			
		}

		//Returns the next node in the path to the goal
		Node* getNextInPath(Node* node) {
			Node* next;
			//cout << node->nextInPath->position.x;
			if (node->nextInPath != NULL) {
				next = node->nextInPath;

				return next;
			}
			//cout << "CHECKPOINT 12\n";
			return NULL;
		}

		//Calculates the number of nodes away from the goal node(Counts horizontal and vertical distance, DOES NOT DO DIAGONAL)
		int getNumNodesFrom(int nodeX, int nodeY, int goalX, int goalY) {
			int numNodesFrom;
			int x;
			int y;

			if (nodeX > goalX) {
				x = nodeX - goalX;
			}
			else {
				x = goalX - nodeX;
			}

			if (nodeY > goalY) {
				y = nodeY - goalY;
			}
			else {
				y = goalY - nodeY;
			}

			numNodesFrom = x + y;


			return numNodesFrom;

		}

		//Calculates the distance from the position of the node to the position of the goal
		double calcDistance(SpritePos node, SpritePos goal) {
			double distance;
			double x = node.x - goal.x;
			double y = node.y - goal.y;
			distance = sqrt((x * x) + (y * y));
			return distance;
		}


	};



}