#ifndef MEMBER_H
#define MEMBER_H

template <typename T> struct Graph {
	DoublyLinkedList<Vertex<T>> members_list;

	void dijkstra(Vertex<T> origin, Vertex<T> target) {
		int max = 10000000;
		int n = this->members_count();
		int dist[n];
		int prev[n];
		Vertex<T> unvisited[n];
		int origin_index=0;
		int target_index=0;

		Vertex<T> empty;
		strcpy(empty.value, "EMPTY");

		Vertex<T> result;
		int index=0;

		for (int i = 0; i < n; ++i) {
			this->members_list.get(i, result);
			if(!strcmp(result.value, origin.value)) {
				origin_index=i;
			}

			if(!strcmp(result.value, target.value)) {
				target_index=i;
			}

			dist[i] = max;
			prev[i] = -1;
			unvisited[i] = result;
		}

		dist[origin_index] = 0;

		Vertex<T> u;
		while(true) {
			int min_distance = max;
			int u_index = -1;

			for (int i = 0; i < n; ++i) {
				if (strcmp(unvisited[i].value, empty.value) && dist[i] < min_distance) {
					min_distance = dist[i];
					u_index = i;
				}
			}

			if (u_index == -1) break;
			
			u = unvisited[u_index];
			unvisited[u_index] = empty;
			
			if(!strcmp(u.value, target.value)) break;  // 

			Arc<T> temp_arc;
			for (int i = 0; i < n; ++i) {
				if (strcmp(unvisited[i].value, empty.value) == 0) continue;

				bool connected = false;
				for (int j = 0; u.outgoing.get(j, temp_arc); ++j) {
					if (!strcmp(temp_arc.end.value, unvisited[i].value)) {
						connected = true;
						break;
					}
				}
				for (int j = 0; u.incoming.get(j, temp_arc); ++j) {
					if (!strcmp(temp_arc.start.value, unvisited[i].value)) {
						connected = true;
						break;
					}
				}

				if (connected && dist[u_index] != max && dist[u_index] + temp_arc.weight < dist[i]) {
					dist[i] = dist[u_index] + temp_arc.weight;
					prev[i] = u_index;
				}
			}
		}

		if(prev[target_index] == -1){
			printf("\nNo path between %s and %s", origin.value, target.value);
			return;
		}

		int path[n];
		int path_length = 0;
		for (int i = target_index; i != -1; i = prev[i]) {
			path[path_length] = i;  //
			path_length++;
		}

		printf("\nPath from %s to %s: \n", origin.value, target.value);
		for (int i = path_length - 1; i > 0; i--) {	
			this->members_list.get(path[i], result);
			printf("%s -> ", result.value);
		}
		printf("%s", target.value);
		printf("\nDistance = %d", dist[target_index]);
	}

	int members_count() {
		Vertex<T> result;
		int i=0;
		while(this->members_list.get(i, result)) i++;
		return i;
	}
};

#endif