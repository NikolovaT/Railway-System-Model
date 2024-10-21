#ifndef BDJ_H
#define BDJ_H

#include "defs.h"

template <typename T> struct Bdj {
	Graph<T> railway;
	char vertex_filname[16];
	char arc_filname[16];

	void menu() {
		strcpy(vertex_filname, "vertex.bin");
		strcpy(arc_filname,"arc.bin");
		this->load_from_file(vertex_filname, arc_filname);

		char next='a';
		do {
			printf("\nBDJ actions: \n[d=dijkstra, 1=display, 2=add new stantion, 3=add new arc, 4=edit stantion, \n5=delete stantion, 6=delete arc, 7=display arcs, 8=save, 9=load, 0=exit]: ");
			scanf("%1s", &next);
			while((getchar()) != '\n') {}

			switch(next) {
				case 'd': {
					this->shortest_path();
					break;
				}
				case '1': {
					this->display();
					break;
				}
				case '2': {
					this->add_stantion();
					break;
				}
				case '3': {
					this->add_arc();
					break;
				}
				case '4': {
					this->edit_stantion();
					break;
				}
				case '5': {
					this->remove_stantion();
					break;
				}
				case '6': {
					this->remove_arc();
					break;
				}
				case '7': {
					this->display_arcs();
					break;
				}
				case '8': {
					this->make_new_save();
					break;
				}
				case '9': {
					this->load_from_save();
					break;
				}
			}
		} while(next!='0');
		
		printf("\nGoodbye.");
	}

	void add_stantion() {
		bool free;
		char name[16]="";
		do {
			free=true;
			printf("\nEnter stantion name: ");
			scanf("%15s", name);
			while((getchar()) != '\n') {}

			Vertex<T> result;
			int i=0;
			while(this->railway.members_list.get(i, result)) {
				if(!strcmp(result.value, name)) {
					free=false;
					break;
				}
				i++;
			}

			if(!free) printf("\nThis stantion name is taken, try again");
		} while(!free);

		Vertex<T> temp;
		strcpy(temp.value, name);

		this->railway.members_list.add(temp);
		this->save_to_file(vertex_filname, arc_filname);
		printf("\nStantion added successfully");

		char next;
		printf("\nDo you want to connect this stantion to another one [y/n]");
		scanf("%1s", &next);

		if(next != 'y') return;

		char second_name[16]="";
		Vertex<T>* first = new Vertex<T>();
		Vertex<T>* second = new Vertex<T>();
		int first_index;
		int second_index;
		int weight;

		char oneway='0';
		do {
			printf("\nIs the arc oneway=1 or twoway=2: ");
			scanf("%1s", &oneway);
			while((getchar()) != '\n') {}

			if(oneway!='1' && oneway!='2') {
				printf("\nInvalid. Enter oneway=1 or twoway=2: ");
			}
		} while(oneway!='1' && oneway!='2');

		bool found1;
		bool found2;
		do {
			found1=false;
			found2=false;

			printf("\nEnter second stantion name: ");
			scanf("%15s", second_name);
			while((getchar()) != '\n') {}

			Vertex<T> result;
			int i=0;
			while(this->railway.members_list.get(i, result)) {
				if(!strcmp(result.value, name)) {
					found1=true;
					*first = result;
					first_index=i;
				}
				if(!strcmp(result.value, second_name)) {
					found2=true;
					*second = result;
					second_index=i;
				}
				if(found1 && found2) break;
				i++;
			}

			if(!found2) printf("\nNo second stantion found. try again");
		} while(!found2);

		printf("\nEnter distance: ");
		scanf("%d", &weight);

		this->connect(first, second, weight);
		if(oneway=='2') this->connect(second, first, weight);

		this->railway.members_list.remove_at(first_index);
		this->railway.members_list.insert(first_index, *first);

		this->railway.members_list.remove_at(second_index);
		this->railway.members_list.insert(second_index, *second);

		this->save_to_file(vertex_filname, arc_filname);
		delete(first);
		delete(second);
		printf("\nArc added successfully");
	}

	void connect(Vertex<T>* start_v, Vertex<T>* end_v, int w) {
		Arc<T>* temp_arc = new Arc<T>();

		temp_arc->start = *start_v;
		temp_arc->end = *end_v;
		temp_arc->weight = w;

		Arc<T> result;
		int i=0;
		bool out_repeat=false;
		while(start_v->outgoing.get(i, result)) {
			if(!strcmp(result.end.value, temp_arc->end.value)) {
				out_repeat=true;
				break;
			}
			i++;
		}

		int j=0;
		bool in_repeat=false;
		while(end_v->incoming.get(j, result)) {
			if(!strcmp(result.start.value, temp_arc->start.value)) {
				in_repeat=true;
				break;
			}
			j++;
		}

		if(!out_repeat) start_v->outgoing.add(*temp_arc);
		if(!in_repeat )end_v->incoming.add(*temp_arc);
	}

	void disconnect(Vertex<T>* start_v, Vertex<T>* end_v) {
		Arc<T> out_res;
		int i=0;
		while(start_v->outgoing.get(i, out_res)) {
			if(!strcmp(out_res.end.value, end_v->value)) {
				start_v->outgoing.remove_at(i);
				break;
			}
			i++;
		}

		Arc<T> in_res;
		int j=0;
		while(end_v->incoming.get(j, in_res)) {
			if(!strcmp(in_res.start.value, start_v->value)) {
				end_v->incoming.remove_at(i);
				break;
			}
			j++;
		}

	}

	void add_arc() {
		printf("\nAdding arc");
		bool found1;
		bool found2;
		char first_name[16]="";
		char second_name[16]="";
		Vertex<T>* first = new Vertex<T>();
		Vertex<T>* second = new Vertex<T>();
		int first_index;
		int second_index;
		int weight=0;

		char oneway='0';
		do {
			printf("\nIs the arc oneway=1 or twoway=2: ");
			scanf("%1s", &oneway);
			while((getchar()) != '\n') {}

			if(oneway!='1' && oneway!='2') {
				printf("\nInvalid. Enter oneway=1 or twoway=2: ");
			}
		} while(oneway!='1' && oneway!='2');

		do {
			found1=false;
			found2=false;
			printf("\nEnter first stantion name: ");
			scanf("%15s", first_name);
			while((getchar()) != '\n') {}

			printf("\nEnter second stantion name: ");
			scanf("%15s", second_name);
			while((getchar()) != '\n') {}

			Vertex<T> result;
			int i=0;
			while(this->railway.members_list.get(i, result)) {
				if(!strcmp(result.value, first_name)) {
					found1=true;
					*first = result;
					first_index=i;
				}
				if(!strcmp(result.value, second_name)) {
					found2=true;
					*second = result;
					second_index=i;
				}
				if(found1 && found2) break;
				i++;
			}

			if(!found1) printf("\nNo first stantion found. try again");
			if(!found2) printf("\nNo second stantion found. try again");
		} while(!found1 || !found2);

		printf("\nEnter distance: ");
		scanf("%d", &weight);

		this->connect(first, second, weight);
		if(oneway=='2') this->connect(second, first, weight);

		this->railway.members_list.remove_at(first_index);
		this->railway.members_list.insert(first_index, *first);

		this->railway.members_list.remove_at(second_index);
		this->railway.members_list.insert(second_index, *second);

		this->save_to_file(vertex_filname, arc_filname);
		delete(first);
		delete(second);
		printf("\nArc added successfully");
	}

	void edit_stantion() {
		bool found;
		char edit_name[16]="";
		int edit_index;
		Vertex<T>* new_vertex = new Vertex<T>();
		char new_name[16]="";

		do {
			found=false;
			printf("\nEnter stantion name to edit it: ");
			scanf("%15s", edit_name);
			while((getchar()) != '\n') {}

			Vertex<T> result;
			int i=0;
			while(this->railway.members_list.get(i, result)) {
				if(!strcmp(result.value, edit_name)) {
					found=true;
					edit_index=i;
					*new_vertex = result;


					bool free;
					do {
						free=true;
						printf("\nEnter new stantion name: ");
						scanf("%15s", new_name);
						while((getchar()) != '\n') {}

						Vertex<T> result;
						int i=0;
						while(this->railway.members_list.get(i, result)) {
							if(!strcmp(result.value, new_name)) {
								free=false;
								break;
							}
							i++;
						}
						if(!free) printf("\nThis stantion name is taken, try again");
					} while(!free);
					strcpy(new_vertex->value, new_name);

				} else {
					Arc<T> temp_arc;
					int j=0;
					while(result.outgoing.get(j, temp_arc)) {
						if(!strcmp(temp_arc.end.value, edit_name)) {
							temp_arc.end = *new_vertex;
							result.outgoing.remove_at(j);
							result.outgoing.insert(j, temp_arc);
						}
						j++;
					}

					Arc<T> temp_arc2;
					int j2=0;
					while(result.incoming.get(j2, temp_arc2)) {
						if(!strcmp(temp_arc2.start.value, edit_name)) {
							temp_arc.start = *new_vertex;
							result.incoming.remove_at(j2);
							result.incoming.insert(j2, temp_arc);
						}
						j2++;
					}

					this->railway.members_list.remove_at(i);
					this->railway.members_list.insert(i, result);
				}
				i++;
			}
			if(!found) printf("\nNo such stantion found try again");
		} while(!found);

		this->railway.members_list.remove_at(edit_index);
		this->railway.members_list.insert(edit_index, *new_vertex);

		this->save_to_file(vertex_filname, arc_filname);
		delete(new_vertex);
		printf("\nVertex edited successfully");

	}

	void display() {
		Vertex<T> res;
		int i=0;
		while(this->railway.members_list.get(i, res)) {
			printf("\n\n%s points to:", res.value);
			Arc<T> a_out;
			int j=0;
			while(res.outgoing.get(j, a_out)) {
				printf("%s, ", a_out.end.value);
				j++;
			}

			printf("\n%s is pointed to by:", res.value);
			Arc<T> a_in;
			int x=0;
			while(res.incoming.get(x, a_in)) {
				printf("%s, ", a_in.start.value);
				x++;
			}
			i++;
		}
	}

	void remove_arc() {
		printf("\nRemoving arc");
		bool found1;
		bool found2;
		char first_name[16]="";
		char second_name[16]="";
		Vertex<T>* first = new Vertex<T>();
		Vertex<T>* second = new Vertex<T>();
		int first_index;
		int second_index;

		char oneway='0';
		do {
			printf("\nIs the arc oneway=1 or twoway=2: ");
			scanf("%1s", &oneway);
			while((getchar()) != '\n') {}

			if(oneway!='1' && oneway!='2') {
				printf("\nInvalid. Enter oneway=1 or twoway=2: ");
			}
		} while(oneway!='1' && oneway!='2');

		do {
			found1=false;
			found2=false;
			printf("\nEnter first stantion name: ");
			scanf("%15s", first_name);
			while((getchar()) != '\n') {}

			printf("\nEnter second stantion name: ");
			scanf("%15s", second_name);
			while((getchar()) != '\n') {}

			Vertex<T> result;
			int i=0;
			while(this->railway.members_list.get(i, result)) {
				if(!strcmp(result.value, first_name)) {
					found1=true;
					*first = result;
					first_index=i;
				}
				if(!strcmp(result.value, second_name)) {
					found2=true;
					*second = result;
					second_index=i;
				}
				if(found1 && found2) break;
				i++;
			}

			if(!found1) printf("\nNo first stantion found. try again");
			if(!found2) printf("\nNo second stantion found. try again");
		} while(!found1 || !found2);

		this->disconnect(first, second);
		if(oneway=='2') this->disconnect(second, first);

		this->railway.members_list.remove_at(first_index);
		this->railway.members_list.insert(first_index, *first);

		this->railway.members_list.remove_at(second_index);
		this->railway.members_list.insert(second_index, *second);

		this->save_to_file(vertex_filname, arc_filname);
		delete(first);
		delete(second);
		printf("\nArc removed successfully");
	}

	void remove_stantion() {
		Arc<T>* temp_arc = new Arc<T>();
		Arc<T>* temp_arc2 = new Arc<T>();
		bool found;
		char remove_name[16]="";
		int remove_index;
		do {
			found=false;
			printf("\nEnter stantion name to remove it: ");
			scanf("%15s", remove_name);
			while((getchar()) != '\n') {}

			Vertex<T> result;
			int i=0;
			while(this->railway.members_list.get(i, result)) {
				if(!strcmp(result.value, remove_name)) {
					found=true;
					remove_index=i;
				} else {
					int j=0;
					while(result.outgoing.get(j, *temp_arc)) {
						if(!strcmp(temp_arc->end.value, remove_name)) {
							result.outgoing.remove_at(j);
						}
						j++;
					}

					int j2=0;
					while(result.incoming.get(j2, *temp_arc2)) {
						if(!strcmp(temp_arc2->start.value, remove_name)) {
							result.incoming.remove_at(j2);
						}
						j2++;
					}

					this->railway.members_list.remove_at(i);
					this->railway.members_list.insert(i, result);


				}
				i++;
			}

			if(!found) printf("\nNo such stantion found try again");
		} while(!found);

		this->railway.members_list.remove_at(remove_index);

		this->save_to_file(vertex_filname, arc_filname);
		delete(temp_arc); 									//chaged
		delete(temp_arc2);
		printf("\nVertex removed successfully");
	}

	void display_arcs() {
		Vertex<T> result;
		int i=0;
		while(this->railway.members_list.get(i, result)) {
			Arc<T> out_arc;
			int j=0;
			while(result.outgoing.get(j, out_arc)) {
				printf("\n%s ---%d--> %s ", result.value, out_arc.weight, out_arc.end);
				j++;
			}
			i++;
		}
	}

	void shortest_path() {
		printf("\nFinding shortest path");
		bool found1;
		bool found2;
		char first_name[16]="";
		char second_name[16]="";
		Vertex<T>* first = new Vertex<T>();
		Vertex<T>* second = new Vertex<T>();

		do {
			found1=false;
			found2=false;
			printf("\nEnter first stantion name: ");
			scanf("%15s", first_name);
			while((getchar()) != '\n') {}

			printf("\nEnter second stantion name: ");
			scanf("%15s", second_name);
			while((getchar()) != '\n') {}

			Vertex<T> result;
			int i=0;
			while(this->railway.members_list.get(i, result)) {
				if(!strcmp(result.value, first_name)) {
					found1=true;
					*first = result;
				}
				if(!strcmp(result.value, second_name)) {
					found2=true;
					*second = result;
				}
				if(found1 && found2) break;
				i++;
			}

			if(!found1) printf("\nNo first stantion found. try again");
			if(!found2) printf("\nNo second stantion found. try again");
		} while(!found1 || !found2);

		this->railway.dijkstra(*first, *second);
		delete(first);
		delete(second);
	}

	void make_new_save() {
		printf("\nEnter vertex filname(.bin): ");
		scanf("%15s", vertex_filname);
		while((getchar()) != '\n') {}

		printf("\nEnter arc filname(.bin): ");
		scanf("%15s", arc_filname);
		while((getchar()) != '\n') {}

		this->save_to_file(vertex_filname, arc_filname);
		
		printf("\nSuccessfully saved to %s and %s: ", vertex_filname, arc_filname);
	}

	void load_from_save() {
		printf("\nEnter vertex filname(.bin): ");
		scanf("%15s", vertex_filname);
		while((getchar()) != '\n') {}

		printf("\nEnter arc filname(.bin): ");
		scanf("%15s", arc_filname);
		while((getchar()) != '\n') {}

		Graph<T>* new_railway = new Graph<T>();
		this->railway = *new_railway;
		this->load_from_file(vertex_filname, arc_filname);
		delete(new_railway);
		printf("\nSuccessfully loaded from %s and %s: ", vertex_filname, arc_filname);
	}

	void save_to_file(char* vertex_filename, char* arc_filename) {
		FILE* vertex_file;
		vertex_file = fopen(vertex_filename, "wb");
		if (vertex_file == NULL) {
			printf("\nError opening vertex file");
			exit(1);
		}
		FILE* arc_file;
		arc_file = fopen(arc_filename, "wb");
		if (arc_file == NULL) {
			printf("\nError opening arc file");
			exit(1);
		}

		Vertex<T> result;
		int i=0;
		while(this->railway.members_list.get(i, result)) {
			int flag_v=0;
			flag_v = fwrite(result.value, sizeof(result.value), 1, vertex_file);
			if(!flag_v) printf("\nError. Vertex entry not writen.");

			Arc<T> out_arc;
			int x=0;
			while(result.outgoing.get(x, out_arc)) {
				int flag_a=0;
				flag_a = fwrite(result.value, sizeof(result.value), 1, arc_file);
				flag_a = fwrite(out_arc.end.value, sizeof(out_arc.end.value), 1, arc_file);
				flag_a = fwrite(&out_arc.weight, sizeof(int), 1, arc_file);
				if(!flag_a) printf("\nError. Arc entry not writen.");
				x++;
			}
			i++;
		}

		fclose(vertex_file);
		fclose(arc_file);
	}

	void load_from_file(char* vertex_filename, char* arc_filename) {
		FILE* vertex_file;
		vertex_file = fopen(vertex_filename, "rb");
		if (vertex_file == NULL) {
			printf("\nError opening phone file (no such vertex file)");
			exit(1);
		}
		FILE* arc_file;
		arc_file = fopen(arc_filename, "rb");
		if (arc_file == NULL) {
			printf("\nError opening phone file (no such arc file)");
			exit(1);
		}

		int vertex_counter=0;
		int c;
		while ((c = fgetc(vertex_file)) != EOF) {
			vertex_counter++;
		}
		vertex_counter /= 16;

		rewind(vertex_file);

		int arc_counter=0;
		int b;
		while ((b = fgetc(arc_file)) != EOF) {
			arc_counter++;
		}
		arc_counter /= 32+sizeof(int);

		rewind(arc_file);

		Vertex<T>* temp_vertex = new Vertex<T>();
		Arc<T>* temp_arc = new Arc<T>();
		for(int i=0; i<vertex_counter; i++) {
			fread(temp_vertex->value, sizeof(temp_vertex->value), 1, vertex_file);
			this->railway.members_list.add(*temp_vertex);
		}

		rewind(arc_file);
		Vertex<T>* temp_start = new Vertex<T>();
		Vertex<T>* temp_end = new Vertex<T>();
		int temp_weight=0;
		for(int j=0; j<arc_counter; j++) {
			fread(temp_start->value, sizeof(temp_start->value), 1, arc_file);
			fread(temp_end->value, sizeof(temp_end->value), 1, arc_file);
			fread(&temp_weight, sizeof(temp_weight), 1, arc_file);

			Vertex<T> result;
			int x=0;
			int start_index=0;
			int end_index=0;
			while(this->railway.members_list.get(x, result)) {
				if(!strcmp(result.value, temp_start->value)) {
					*temp_start = result;
					start_index=x;
				}
				if(!strcmp(result.value, temp_end->value)) {
					*temp_end = result;
					end_index=x;
				}
				x++;
			}
			this->connect(temp_start, temp_end, temp_weight);

			this->railway.members_list.remove_at(start_index);
			this->railway.members_list.insert(start_index, *temp_start);

			this->railway.members_list.remove_at(end_index);
			this->railway.members_list.insert(end_index, *temp_end);
		}
		fclose(vertex_file);
		fclose(arc_file);
		delete(temp_vertex);
		delete(temp_start);
		delete(temp_end);
	}
};

#endif