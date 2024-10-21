void menu() {
	char next='a';
	do {
		printf("\BDJ actions: \n[1=display, 2=add new vertex, 3=add new arc, 4=edit vertex, 5=edit arc, 6=delete vertex, 7=delete arc 0=exit]: ");
		scanf("%1s", &next);
		while((getchar()) != '\n') {}

		switch(next) {
			case '1': {
				p1.display();
				break;
			}
			case '2': {
				p1.add_phone();
				break;
			}
			case '3': {
				p1.edit_phone();
				break;
			}
			case '4': {
				p1.delete_phone();
				break;
			}
			case '5': {
				p1.add_phone_info();
				break;
			}
			case '6': {
				p1.settings();
				break;
			}
		}
	} while(next!='0');
}