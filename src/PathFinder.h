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
				gamePlane[i] = new Node*[400];
			}

			float posX = -1;
			float posY = 1;
			for (int x = 0; x < 1000; x++) {
					posX = posX + 0.01;
					posY = 1;
				for (int y = 0; y < 1000; y++) {
					gamePlane[x][y] = new Node();
					gamePlane[x][y]->position.x = x;
					gamePlane[x][y]->position.y = y;
					posY = posY - 0.01;
				}
			}
		}

		Node* findPath(SpritePos goal, SpritePos seeker, EntityComponentSystem& entities) {
			Sprite sprite;
			float posX = -1;
			float posY = 1;
			//Goes through every sprite to determine goal position and position of spaces that are blocked off
			entities.ForEach<Sprite>([&](EntityID id) {

				sprite = entities.Get<Sprite>(id);
			if (sprite.position.x == goal.x && sprite.position.y == goal.y) {
			//	gamePlane[sprite.position.x][sprite.position.y]->isGoal = true;
			}
			if ((sprite.position.x != goal.x && sprite.position.y != goal.y) || (sprite.position.x != seeker.x && sprite.position.y != seeker.y)) {
			//	gamePlane[sprite.position.x][sprite.position.y]->isBlocked = true;
			}

				});
			//Sets up the heuristic and edge costs
			for (int x = 0; x < 1000; x++) {
					
				for (int y = 0; y < 1000; y++) {
					gamePlane[x][y]->nodesFromGoal = getNumNodesFrom(x, y, goal.x, goal.y);
					gamePlane[x][y]->goalDistance = calcDistance(gamePlane[x][y]->position, goal);
					
				}
			}

			Node *curNode = gamePlane[/*seeker.x*/1][/*seeker.y*/1];
			//Builds the path to the goal
			while (curNode->position.x != goal.x && curNode->position.y != goal.y) {



				curNode->nextInPath = findNextInPath(curNode);
				curNode = curNode->nextInPath;




			}


			//Returns node of the seeker's position and will use the nextInPath node pointer to move along the path to the goal
			return gamePlane[/*seeker.x*/1][/*seeker.y*/1];
		}
		//Finds the next node in the path to the goal
		Node* findNextInPath(Node* node) {
			Node *next = NULL;
			SpritePos neighbors[8];
			neighbors[0].x = node->position.x - 1;
			neighbors[0].y = node->position.y + 1;

			neighbors[1].x = node->position.x;
			neighbors[1].y = node->position.y + 1;

			neighbors[2].x = node->position.x + 1;
			neighbors[2].y = node->position.y + 1;

			neighbors[3].x = node->position.x - 1;
			neighbors[3].y = node->position.y;

			neighbors[4].x = node->position.x + 1;
			neighbors[4].y = node->position.y;

			neighbors[5].x = node->position.x - 1;
			neighbors[5].y = node->position.y - 1;

			neighbors[6].x = node->position.x;
			neighbors[6].y = node->position.y - 1;

			neighbors[7].x = node->position.x + 1;
			neighbors[7].y = node->position.y - 1;

			for (int x = 0; x < 8; x++) {
				if ((neighbors[x].x < 1000 && neighbors[x].x >= 0) && (neighbors[x].y < 1000 && neighbors[x].y >= 0)) {
					if (next == NULL) {
					//	next = gamePlane[neighbors[x].x][neighbors[x].y];
					}

					//if ((gamePlane[neighbors[x].x][neighbors[x].y]->goalDistance + gamePlane[neighbors[x].x][neighbors[x].y]->nodesFromGoal) <= (next->goalDistance + next->nodesFromGoal)) {
					//	next = gamePlane[neighbors[x].x][neighbors[x].y];
					//}
				}
			}


			return next;
		}

		//This function moves the sprite along the path generated from findPath
		void moveToGoal(Sprite seekerSprite, Node* path) {
			Node* nextInPath = getNextInPath(path);
			while (nextInPath != NULL) {
				seekerSprite.position.x = nextInPath->position.x;
				seekerSprite.position.y = nextInPath->position.y;
				nextInPath = getNextInPath(nextInPath);
			}


		}

		//Returns the next node in the path to the goal
		Node* getNextInPath(Node* node) {
			Node* next;
			if (node->nextInPath != NULL) {
				next = node->nextInPath;

				return next;
			}

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