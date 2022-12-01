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
					
					
					posY = posY - 1;
				}
			}
		
		}

		void findPath(Sprite seekerSprite,SpritePos goal, SpritePos seeker, EntityComponentSystem& entities) {
			Sprite sprite;
			cout << "WE MADE IT HERE";
			//Goes through every sprite to determine goal position and position of spaces that are blocked off
			
			entities.ForEach<Sprite>([&](EntityID id) {

				sprite = entities.Get<Sprite>(id);
			

			if (sprite.position.x == goal.x && sprite.position.y == goal.y) {
				//The weird looking formula in the brackets is to translate the coordinate position to the matrix position (ex- coorinates 0,0 -> matrix position[99][99])
				gamePlane[(int)floor(99.5 * (sprite.position.x + 1))][(int)floor(-99.5 * (sprite.position.y - 1))]->isGoal = true;
				//cout << "CHECKPOINT 1 REACHED\n";
			}
			if ((sprite.position.x != goal.x && sprite.position.y != goal.y) || (sprite.position.x != seeker.x && sprite.position.y != seeker.y)) {
			//	cout << "CHECKPOINT 2 REACHED\n";
				gamePlane[(int)floor(99.5 * (sprite.position.x + 1))][(int)floor(-99.5 * (sprite.position.y - 1))]->isBlocked = true;
			}
			
				});
			//Sets up the heuristic and edge costs
			cout << "CHECKPOINT 3 REACHED\n";
			for (int x = 0; x < 200; x++) {
					
				for (int y = 0; y < 200; y++) {
					
					gamePlane[x][y]->nodesFromGoal = getNumNodesFrom(gamePlane[x][y]->position.x, gamePlane[x][y]->position.y, goal.x, goal.y);
					gamePlane[x][y]->goalDistance = calcDistance(gamePlane[x][y]->position, goal);
					
				}
			}

			Node *curNode = gamePlane[(int)floor(99.5*(seeker.x+1))][(int)floor(-99.5 * (seeker.y - 1))];
			/*
			cout << "Seeker X POS: ";
			cout << gamePlane[(int)floor(99.5 * (seeker.x + 1))][(int)floor(-99.5 * (seeker.y - 1))]->position.x;
			cout << ", Seeker Y POS: ";
			cout << gamePlane[(int)floor(99.5 * (seeker.x + 1))][(int)floor(-99.5 * (seeker.y - 1))]->position.y;
			cout << "\n";
			*/
			//Builds the path to the goal
			cout << "CHECKPOINT 4 REACHED\n";
			while (curNode->position.x != goal.x && curNode->position.y != goal.y) {



				curNode->nextInPath = findNextInPath(curNode);
				curNode = curNode->nextInPath;




			}

			cout << "CHECKPOINT 10 REACHED\n";
			//Returns node of the seeker's position and will use the nextInPath node pointer to move along the path to the goal
			
			moveToGoal(seekerSprite, gamePlane[(int)floor(99.5 * (seeker.x + 1))][(int)floor(-99.5 * (seeker.y - 1))],entities);
			cout << "Checkpoint 11 REACHED\n";
			
		}
		//Finds the next node in the path to the goal
		Node* findNextInPath(Node* node) {

			
			Node *next = NULL;
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

					if ((gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))]->goalDistance  + gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))]->nodesFromGoal) <= (next->goalDistance  + next->nodesFromGoal)) {
						next = gamePlane[(int)floor(99.5 * (neighbors[x].x + 1))][(int)floor(-99.5 * (neighbors[x].y - 1))];
						
					}
				}
			}

			//cout << "CHECKPOINT 7 REACHED\n";
			
			return next;
		}

		//This function moves the sprite along the path generated from findPath
		void moveToGoal(Sprite seekerSprite, Node* path, EntityComponentSystem& entities) {
			
			Node* nextInPath = getNextInPath(path);
			
			while (nextInPath != NULL) {
				//seekerSprite.x = nextInPath->position.x;
			//	seekerSprite.y = nextInPath->position.y;
				entities.Get<Sprite>(5).x = nextInPath->position.x;
				entities.Get<Sprite>(5).y = nextInPath->position.y;
				/*
				cout << "X Pos: ";
				cout << seekerSprite.x;
				cout << " Y Pos: ";
				cout << seekerSprite.y;
				cout << "\n";
				*/
				nextInPath = getNextInPath(nextInPath);
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
			float numNodesFrom;
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
		float calcDistance(SpritePos node, SpritePos goal) {
			float distance;
			int x = node.x - goal.x;
			int y = node.y - goal.y;
			distance = sqrt((x * x) + (y * y));
			return distance;
		}


	};



}