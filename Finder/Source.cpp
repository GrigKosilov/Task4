int find_exit(beg* maze, int key) {
	enum Color { white, gray, black };

	enum Color* color = malloc(sizeof(int) * maze->size);
	int* len = malloc(sizeof(int) * maze->size);
	int* prev = malloc(sizeof(int) * maze->size);

	int t = 0;
	int* exit_rooms = malloc(sizeof(int) * 0);

	edge* queue = malloc(sizeof(edge) * 0);
	edge* last = queue;
	щ
		int i;
	for (i = 0; i < maze->size; ++i) {
		color[i] = white;
		len[i] = -1;
		prev[i] = 0;
	}

	color[key] = gray;
	len[key] = 0;
	prev[key] = 0;
	queue->key = key;
	queue->next = NULL;

	while (queue) {
		edge* p_e = maze->head[queue->key].first;
		for (; p_e; p_e = p_e->next)
			if (color[p_e->key] == white) {				//вылетает вот тут
				color[p_e->key] = gray;
				len[p_e->key] = len[queue->key] + 1;
				if (maze->head[p_e->key].type == exit) {
					t += 1;
					exit_rooms = realloc(exit_rooms, t * sizeof(int));
					exit_rooms[t - 1] = p_e->key;
				}
				prev[p_e->key] = queue->key;
				last->next = malloc(sizeof(edge));
				last = last->next;
				last->next = NULL;
				last->key = p_e->key;
			}
		color[queue->key] = black;
		queue = queue->next;
	}
	if (t > 0) {
		puts("These are the exit rooms and pathway lenght to them:");
		for (; t > 0; --t) {
			printf("* The room with key %d, lenth is %d \n", exit_rooms[t - 1], len[exit_rooms[t - 1]]);
			int j = exit_rooms[t - 1];
			printf("	The escape path way is: %d", exit_rooms[t - 1]);
			while (prev[j] != key) {
				printf(" <- %d", prev[j]);
				j = prev[j];
			}
			printf(" <- %d.\n", key);
		}
		return 1;
	}
	else
		return 0;
}